#pragma once
#include <stdio.h>

GLuint loadBMP_custom(const char* imagepath) {
	unsigned char Header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* data;

	FILE* file;
	fopen_s(&file, imagepath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(Header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	if (Header[0] != 'B' || Header[1] != 'M') {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}

	if (*(int*)&(Header[0x1E]) != 0) { printf("Not a correct BMP file\n"); return 0; }
	if (*(int*)&(Header[0x1C]) != 24) { printf("Not a correct BMP file\n"); return 0; }
	if (Header[0] != 'B' || Header[1] != 'M') {
		printf("Not a correct BMP file\n");
		fclose(file);
	}

	dataPos = *(int*)&(Header[0x0A]);
	imageSize = *(int*)&(Header[0x22]);
	width = *(int*)&(Header[0x12]);
	height = *(int*)&(Header[0x16]);

	if (imageSize == 0) imageSize = width * height * 3;
	if (dataPos == 0)dataPos = 54;

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

	delete[]data;

	return textureID;
}