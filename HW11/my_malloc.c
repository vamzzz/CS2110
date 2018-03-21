/*
 * CS 2110 Spring 2017
 * Author: Vamshi Adimulam
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this for my_sbrk */
#include "my_sbrk.h"
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"

/* You *MUST* use this macro when calling my_sbrk to allocate the
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* All sizes will be in multiples of the word size defined below */
#define WORD_SIZE 8

/* This is the size of the metadata struct and canary footer in words */
#define TOTAL_METADATA_SIZE ((sizeof(metadata_t) + sizeof(long)) / WORD_SIZE)

/* This is the minimum size of a block in words, where it can
 * store the metadata, canary footer, and at least 1 word of data
 */
#define MIN_BLOCK_SIZE (TOTAL_METADATA_SIZE + 1)

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you may receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf(x)
#else
#define DEBUG_PRINT(x)
#endif

/* Our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t* freelist;

void* get_smallest_available(size_t);
void add_to_freelist(metadata_t*);
int calculateCanary(metadata_t* block);
void setCanary(metadata_t* block, size_t request);
int getCanary(metadata_t* block, size_t request);
void* split_block(metadata_t* block, size_t size);
int should_split(metadata_t* block, size_t size);
void remove_from_freelist(metadata_t* block);

/* MALLOC
 * See my_malloc.h for documentation
 */
void* my_malloc(size_t size) {

	if (size == 0) {
		ERRNO = NO_ERROR;
		return NULL;
	}
	int real_size = size;
	int remainder = 0;
	real_size += TOTAL_METADATA_SIZE * WORD_SIZE;

	if (real_size % WORD_SIZE != 0) {
		remainder = real_size % WORD_SIZE;
		real_size += WORD_SIZE - remainder;
	}
	ERRNO = NO_ERROR;

	if (real_size > SBRK_SIZE) {
		ERRNO = SINGLE_REQUEST_TOO_LARGE;
		return NULL;
	}

    metadata_t* smallest_Avail = get_smallest_available(real_size / WORD_SIZE);
    //if no block is found, allocate some more space

    if (smallest_Avail == NULL) {
    	metadata_t* new_block = my_sbrk(SBRK_SIZE);

    	if (new_block == NULL) {
    		ERRNO = OUT_OF_MEMORY;
    		return NULL;
    	}
    	new_block->size = SBRK_SIZE;
    	new_block->next = NULL;
    	add_to_freelist(new_block);
    	return my_malloc(size);
    } else {
    	//if the block is found - split it if what is left is big enough
    	if (should_split(smallest_Avail, size) == 1) {
    		metadata_t* block = split_block(smallest_Avail, size);
    		setCanary(block, size);
    		return	block + 1;
    	} else {
    		//since it is not big enough, remove smallest from list
    		setCanary(smallest_Avail, size);
    		remove_from_freelist(smallest_Avail);
    		return smallest_Avail + 1;
    	}
    }
}

/* Get smallest
 * this method helps get the smallest block that satifies the passed in condition
 */
void* get_smallest_available(size_t size) {
	metadata_t* current = freelist;
	metadata_t* minBlock = NULL;
	metadata_t* no_split = NULL;
	while (current != NULL) {
		if (current->size == size) {
			return current;
		} else if (current->size >= size + MIN_BLOCK_SIZE) {
			if (minBlock != NULL) {
				if (current->size < minBlock->size) {
					minBlock = current;
				}
			} else {
				minBlock = current;
			}
		} else if (current->size > size && current->size < size + MIN_BLOCK_SIZE) {
			if (no_split != NULL) {
				if (current->size < no_split->size) {
					no_split = current;
				} 
			} else {
				no_split = current;
			}
		}
		current = current->next;
	}
	if (minBlock != NULL) {
		return minBlock;
	} else if (no_split != NULL) {
		return no_split;
	} else {
		return NULL;
	}
}

/* tells if we should split (1) or not (0)
 * @return an int
 */
int should_split(metadata_t* block, size_t size) {
	if (block->size > size + MIN_BLOCK_SIZE) {
		return 1;
	} else {
		return 0;
	}
}

/* Splits the block
 * @return the right part pointer
 */
void* split_block(metadata_t* block, size_t size) {
	metadata_t* new_block = (metadata_t*) (((char*) block) + (block->size - size));
	new_block->next = NULL;
	new_block->size = size;
	block->size -= new_block->size;
	unsigned int canary = calculateCanary(new_block);

	//set metadata's canar
	new_block->canary = canary;
	unsigned long* locCan = (unsigned long*) (size + (char*)(new_block) - sizeof(long));
	*locCan = canary;
	return new_block;
}

/* Once you return block to the user, you must remove it from the free list
 * since it is no longer available for us to use
 */
void remove_from_freelist(metadata_t* block) {
	if (block == freelist) {
		freelist = block->next;
	} else {
		metadata_t* current = freelist;
		while (current->next != NULL) {
			if (current->next == block) {
				current->next = current->next->next;
				block->next = NULL;
			}
			current = current->next;
		}
	}
}

/* Caluclating the canary
 * @return int of canary
 */
int calculateCanary(metadata_t* block) {
	int canary = (uintptr_t)block ^ block->size;
	return canary;
}

/* Sets the canary of the block
 */
void setCanary(metadata_t* block, size_t request) {
	unsigned long* canLoc = (unsigned long*)((char*)(block) + sizeof(metadata_t) + request);
	int canary = calculateCanary(block);
	block->canary = canary;
	*canLoc = canary;
}

/* Get the canary of the block
 * @return int of the canary
 */
int getCanary(metadata_t* block, size_t request) {
	unsigned long* canLoc = (unsigned long*)((char*)(block) + sizeof(metadata_t) + request);
	return *canLoc;
}

/* Add back to the freelist if you free the block
 * Or add to the freelist if you create a new look
 */
void add_to_freelist(metadata_t* block) {
	if (freelist == NULL) {
		freelist = block;
		block->next = NULL;
		return;
	}
	//if it is in the front of the list
	metadata_t* current = freelist;
	if ((uintptr_t) block < (uintptr_t) current) {
		block->next = current;
		freelist = block;
		//check to see if needs to merge - if end of the block
		//matches head of next
		if ((metadata_t*)((char*)block + block->size) == current) {
			block->size = block->size + current->size;
			block->next = current->next;
			current = block;
		}
		return;
	}
	//iterate through the block that should be in the list
	while (current->next != NULL) {
		if ((uintptr_t) block < (uintptr_t) current->next) {
			metadata_t* newB = current->next;
			current->next = block;
			block->next = newB;
			//left merge
			if ((metadata_t*)((char*)current + current->size) == block) {
				current->size = current->size + block->size;
				current->next = block->next;
				block = current;
			}
			//right merge
			if ((metadata_t*) ((char*)block + block->size) == newB) {
				block->size = block->size + newB->size;
				block->next = newB->next;
				newB = block;
			}
			return;
		}
		current = current->next;
	}
	current->next = block;
	//left merge
	if ((metadata_t*)((char*)current + current->size) == block) {
		current->size = current->size + block->size;
		current->next = block->next;
		block = current;
	}
}


/* REALLOC
 * See my_malloc.h for documentation
 */
void* my_realloc(void* ptr, size_t size) {
	void *newpointer;
	//if size = 0 -> free block
	if (size == 0) {
		my_free(ptr);
		return NULL;
	}
	//if ptr = null
	if (ptr == NULL) {
		newpointer = my_malloc(size);
		if (!newpointer) {
			return NULL;
		}
	} else {
		metadata_t* location = ((metadata_t*) ptr) - 1;
		if (location->size - TOTAL_METADATA_SIZE < size) {
			newpointer = my_malloc(size);
			if (!newpointer) {
				return	NULL;
			}
			memcpy(newpointer, ptr, location->size);
			my_free(ptr);
		}
	}
    return newpointer;
}

/* CALLOC
 * See my_malloc.h for documentation
 */
void* my_calloc(size_t nmemb, size_t size) {
	if (size <= 0 || nmemb <= 0) {
		return NULL;
	}
	size_t calc_size = nmemb * size;
	void *newpointer = my_malloc(calc_size);
	if (!newpointer) {
		return NULL;
	}
	memset(newpointer, 0, calc_size);
    return newpointer;
}

/* FREE
 * See my_malloc.h for documentation
 */
void my_free(void* ptr) {
	ERRNO = NO_ERROR;
	if (!ptr) {
		return;
	}
	metadata_t* block = ((metadata_t*) ptr - 1);
	block->next = NULL;

	//check canaries
	if (block->canary != calculateCanary(block)) {
		ERRNO = CANARY_CORRUPTED;
		return;
	} else {
		if (getCanary(block, block->size) != calculateCanary(block)) {
			ERRNO = CANARY_CORRUPTED;
			return;
		}
	}
	add_to_freelist(block);
}
