#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include "bmpReader.h"

BMPReader::BMPReader()
{

}

BMPReader::~BMPReader()
{

}


void BMPReader::loadBitMap(char* fileName, char* outFileName) 
{
	BITMAPINFOHEADER bitMapInfo;
	bmpfile_ft magic;
	bmpfile_header header;
	int row, col;
	bmp_colour * image_buffer;

	FILE * inFile, * outFile;
	inFile = fopen(fileName, "rb");
	outFile = fopen(outFileName, "wb");
	if (inFile == NULL)
	{
		printf("\ncan't open input %s\n", fileName);
		exit (1);
	}
	printf("\nOpened file\n");
	fread(&magic, sizeof(bmpfile_ft), 1, inFile);
	fread(&header, sizeof(bmpfile_header), 1, inFile);
	fread(&bitMapInfo, sizeof(BITMAPINFOHEADER), 1, inFile);
	if (bitMapInfo.width != bitMapInfo.height)
	{
		printf("\nBitmap is not square\n");
			exit (1);
	}

	// create a buffer to hold each line as it is read in
	image_buffer = (bmp_colour *)malloc(sizeof(bmp_colour) * bitMapInfo.width);

	for (row = 0; row < bitMapInfo.height; row++) {
		fread(image_buffer, sizeof(bmp_colour), bitMapInfo.width, inFile);
		// bmp files store colours in the order blue, green, red
		// need to rearrange to the order red, green, blue 
		for (col = 0; col < bitMapInfo.width; col++)
		{
			putc(image_buffer[col].r, outFile);
			putc(image_buffer[+col].g, outFile);
			putc(image_buffer[col].b, outFile);
		}
	}

	// close the .bmp file and free up memory
	fclose(inFile);
	fclose(outFile);
	free(image_buffer);
}