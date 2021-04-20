#include "Texture2D.h"

#include <iostream>
#include <fstream>
using namespace std;

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData; 
	int fileSize; 
	ifstream inFile;

	_width = width;
	_height = height;

	inFile.open(path, ios::binary);
	if (!inFile.good())
	{
		cerr << "Tex2d: Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); //Finds end of file
	fileSize = (int)inFile.tellg(); //Get current position in file (the end) for total file size
	tempTextureData = new char[fileSize]; //Creates an array to store data
	inFile.seekg(0, ios::beg); //Back to beginning of file
	inFile.read(tempTextureData, fileSize); //Reads in all the data in one go
	inFile.close(); //Closes the file

	cout << path << " loaded." << endl;

	glGenTextures(1, &_ID); //Get next Texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); //Bind the texture to the ID
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData); // Specify details of texture image
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData); //specify details of texture image
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] tempTextureData; //Clear up the data
	return true;

}