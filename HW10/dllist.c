/**
 * CS 2110 - Spring 2017 - Homework #10
 *
 * @author Vamshi Adimulam
 *
 * dllist.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"

/* The node struct. Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO */
/* Design consideration: Only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION, DO NOT PUT IT IN OTHER FILES */
typedef struct dnode
{
    struct dnode* prev; /* Pointer to previous node */
    struct dnode* next; /* Pointer to next node */
    void* data; /* User data */
} node;

/* Do not create any global variables here. Your dllist library should obviously
 * work for multiple concurrent dllists */

// This function is declared as static since you should only be calling this
// function from inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the dllist
  * @return a node
  */
static node* create_node(void* data)
{
    /// @todo Implement changing the return value!
    node *newNode = malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/** create_dllist
  *
  * Creates a dllist by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty dllist
  */
dllist* create_dllist(void)
{
    /// @todo Implement changing the return value!
    dllist *newList = malloc(sizeof(dllist));
    newList->head = NULL;
    newList->size = 0;
    newList->tail = NULL;
    return newList;
}

/** push_front
  *
  * Adds the data to the front of the dllist.
  *
  * @param d a pointer to the dllist structure.
  * @param data pointer to data the user wants to store in the dllist.
  */
void push_front(dllist *d, void *data)
{
    /// @todo Implement
    node *newNode = create_node(data);
    if (d->head == NULL) {
    	newNode->next = NULL;
    	newNode->prev = NULL;
    	d->head = newNode;
    	d->tail = newNode;
    	d->size += 1;
    } else {
    	newNode->next = d->head;
    	d->head->prev = newNode;
    	d->head = newNode;
    	d->size += 1;
    }
}

/** push_back
  *
  * Adds the data to the back of the dllist.
  *
  * @param d a pointer to the dllist structure.
  * @param data pointer to data the user wants to store in the dllist.
  */
void push_back(dllist *d, void *data)
{
    /// @todo Implement
    node *newNode = create_node(data);
    if (d->tail == NULL) {
    	newNode->next = NULL;
    	newNode->prev = NULL;
    	d->head = newNode;
    	d->tail = newNode;
    	d->size += 1;
    } else {
    	newNode->prev = d->tail;
    	d -> tail -> next = newNode;
    	d->tail = newNode;
    	d->size += 1;
    }
}

/** front
  *
  * Gets the data at the front of the dllist
  * If the dllist is empty return NULL.
  *
  * @param d a pointer to the dllist
  * @return The data at the first node in the dllist or NULL.
  */
void *front(dllist *d)
{
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember, the
    /// user should never deal with the dllist nodes.
    if (d == NULL) {
    	return 0;
    }
    if (is_empty(d)) {
    	return NULL;
    }
    return d->head->data;
}

/** back
  *
  * Gets the data at the "end" of the dllist
  * If the dllist is empty return NULL.
  *
  * @param d a pointer to the dllist structure
  * @return The data at the last node in the dllist or NULL.
  */
void *back(dllist *d)
{
    /// @todo Implement changing the return value!
    if (d == NULL) {
    	return 0;
    }
    if (is_empty(d)) {
    	return NULL;
    }
    return d->tail->data;
}

/** get
  *
  * Gets the data at the specified index in the dllist
  *
  * @param d a pointer to the dllist structure
  * @param index 0-based, starting from the head.
  * @return The data from the specified index in the dllist or NULL if index is
  *         out of range of the dllist.
  */
void *get(dllist *d, int index)
{
    /// @todo Implement changing the return value!
    if (index >= d->size || index < 0) {
    	return NULL;
    }
    if (is_empty(d)) {
    	return NULL;
    }
    node *current = d->head;
    for (int i = 0; i < index; i++) {
    	current = current->next;
    }
    return current->data;
}
/** add
  *
  * Adds the data at the specified index in the dllist.
  * Adding at index size should have the same behavior as push_back
  *
  * @param d a pointer to the dllist structure
  * @param index 0-based, starting from the head, to size.
  * @return true if insertion was successful or false if index is
  *         out of range of the dllist.
  */
bool add(dllist *d, void* data, int index)
{
    /// @todo Implement changing the return value!
    if (d == NULL) {
    	return 0;
    }
    if (index > d->size || index < 0) {
    	return false;
    }
    if (is_empty(d)) {
    	push_front(d, data);
    } else if (d->size == index) {
    	push_back(d, data);
    } else if (index == 0) {
    	push_front(d, data);
    } else {
    	node *new_node = create_node(data);
    	node *current = d->head;
    	node *temp = NULL;
    	for (int i = 0; i < index - 1; i++) {
    		current = current->next;
    	}
    	temp = current->next;
    	temp->prev = new_node;
    	current->next = new_node;
    	new_node->next = temp;
    	new_node->prev = current;
    	d->size += 1;
    }
    return true;
}

/** contains
  *
  * Traverses the dllist, trying to see if the dllist contains some data.
  * Since non-NULL values are considered true, this can be used like a boolean
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * eq_func says is equal. For instance, if you have a dllist of person structs:
  *   (Andrew, 26), (Nick, 24), (Collin, 23), (Marie, 23)
  * And you want to return any person whose age is 22, you could create a new
  * person struct (<NULL>, 24) with an eq_func that returns age == 24 and pass
  * that into this function as "data". contains() would then return (Nick, 24)
  *
  * If there are multiple pieces of data in the dllist which are equal to the
  * "data" parameter, return any one of them.
  *
  * @param d a pointer to the dllist structure
  * @param data The data, to see if it exists in the dllist
  * @param eq_func A function written by the user that will tell if two pieces
  *                of data are equal. Returns 0 if equal, something else
  *                otherwise. Imagine subtracting two numbers.
  * @return The data contained in the dllist, or NULL if it doesn't exist
  */
void *contains(dllist *d, void *data, dllist_eq eq_func) {
    /// @todo Implement
    if (d == NULL) {
    	return 0;
    }
    node *current = d->head;
    while (current != NULL) {
    	if (eq_func(data, current->data) == 0) {
    		return current->data;
    	}
    	current = current->next;
    }
    return NULL;
}

/** pop_front
  *
  * Removes the node at the front of the dllist, and returns its data to the user
  *
  * @param d a pointer to the dllist.
  * @return The data in the first node, or NULL if the dllist is NULL or empty
  */
void *pop_front(dllist *d)
{
    /// @todo Implement
    if (d == NULL) {
    	return 0;
    }
    if (d->size == 0 && d->head == NULL) {
    	return NULL;
    }
    if (is_empty(d)) {
    	return NULL;
    }
    void* tempData;
    node *next;
    node *temp = d->head;
    if (d->size == 1) {
    	next = NULL;
    	d->tail = NULL;
    } else {
    	next = temp->next;
    	temp->next->prev = NULL;
    }
    tempData = temp->data;
    free(temp);
    d->head = next;
    d->size -= 1;
    return tempData;
}

/** pop_back
  *
  * Removes the node at the end of the dllist, and returns its data to the user
  *
  * @param d a pointer to the dllist.
  * @return The data in the first node, or NULL if the dllist is NULL or empty
  */
void *pop_back(dllist *d)
{
    /// @todo Implement
    if (d == NULL) {
    	return 0;
    }
    if (d->size == 0 && d->head == NULL) {
    	return NULL;
    }
    if (is_empty(d)) {
    	return NULL;
    }
    void* tempData;
    node *prev;
    node *temp = d->tail;
    if (d->size == 1) {
    	prev = NULL;
    	d->head = NULL;
    } else {
    	prev = temp->prev;
    	temp->prev->next = NULL;
    }
    tempData = temp->data;
    free(temp);
    d->tail = prev;
    d->size -= 1;
    return tempData;
}

/** copy_dllist
  *
  * Create a new dllist structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param d A pointer to the dllist structure to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *                  data that's being used in this dllist, allocating space for
  *                  every part of that data on the heap. This is some function
  *                  you must write yourself for testing, tailored specifically
  *                  to whatever context you're using the dllist for in your test
  * @return The dllist structure created by copying the old one, or NULL if the
  *         structure passed in is NULL.
  */
dllist* copy_dllist(dllist *d, dllist_copy copy_func)
{
	/// @todo implement
	if (d == NULL) {
		return 0;
	}
	dllist *newList = create_dllist();
	node *current = d -> head;
	while (current != NULL) {
		push_back(newList, copy_func(current->data));
		current = current->next;
	}
	return newList;
}

/** size
  *
  * Gets the size of the dllist
  *
  * @param d a pointer to the dllist structure
  * @return The size of the dllist
  */
int size(dllist *d)
{
    ///@note simply return the size of the dllist. It's that easy!
    if (d == NULL) {
    	return 0;
    }
    return d->size;
}

/** is_empty
  *
  * Checks to see if the dllist is empty.
  *
  * @param d a pointer to the dllist structure
  * @return true if the dllist is indeed empty, or false otherwise.
  */
bool is_empty(dllist *d)
{
    /// @note an empty dllist should have a size of zero and head points to NULL.
    if (d == NULL) {
    	return 0;
    }
    if (d->size == 0 && d->head == NULL) {
    	return true;
    } else {
    	return false;
    }
}

/** empty_dllist
  *
  * Empties the dllist. After this is called, the dllist should be empty.
  * This does not free the dllist struct itself, just all nodes and data within.
  *
  * @param d a pointer to the dllist structure
  * @param free_func function used to free the nodes' data.
  */
void empty_dllist(dllist *d, dllist_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes, not the dllist structure itself.
    /// @note do not free the dllist structure itself.
    while (d->size > 0) {
    	free_func(pop_front(d));
    }
}

/** traverse
  *
  * Traverses the dllist, calling a function on each node's data.
  *
  * @param d a pointer to the dllist structure
  * @param do_func a function that does something to each node's data.
  */
void traverse(dllist *d, dllist_op do_func)
{
    /// @todo Implement
    node *current = d->head;
    while (current != NULL) {
    	do_func(current->data);
    	current = current->next;
    }
}

/** reverse
  * Reverses the dllist
  * Should do nothing if d is NULL
  * @param d a pointer to the dllist structure
  */
void reverse(dllist *d) {
    /// @todo Implement
    if (d == NULL) {
    	return;
    }
    node *current = d->head;
    node *temp = NULL;
    while (current != NULL) {
    	temp =current->prev;
    	current->prev = current->next;
    	current->next = temp;
    	if (current -> next == NULL) {
    		d -> tail = current;
    	} else if (current -> prev == NULL) {
    		d -> head = current;
    	}
    	current = current->prev;
    }
}
