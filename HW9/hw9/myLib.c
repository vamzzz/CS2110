#include "myLib.h"
#include <stdlib.h>
#include <stdio.h>

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int i = 0; i < height; i++)	{
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row + i, col, 240)];
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}

void delay(int n)
{
	volatile int x = 0;
	for(int i=0; i<n*8000; i++)
	{
		x++;
	}
}

void drawImage3(int r, int c, int width, int height, const u16 *image) {
	for(int i = 0; i < height; i++)	{
		DMA[3].src = image + (i * width);
		DMA[3].dst = videoBuffer + (r * 240) + (i * 240) + c;
		DMA[3].cnt = width | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
	}
}

void clearscreen() {
	volatile short black = 0;
	DMA[DMA_CHANNEL_3].src = &black;
	DMA[DMA_CHANNEL_3].dst = videoBuffer;
	DMA[DMA_CHANNEL_3].cnt = (240 * 160) | DMA_ON | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT;
}

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 159);
}

