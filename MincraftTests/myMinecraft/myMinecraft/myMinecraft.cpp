// myMinecraft.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
using namespace sf;

#define DW 800
#define DH 600

int main()
{
	RenderWindow window(VideoMode(DW,DH), "My Minecraft 2.0");

	GLuint texture = 0;
	{
		Image image;
		image.loadFromFile("text.jpg");

		glGenTextures(1, &texture);
		glBlindTexture(GL_TEXTURE_2D, texture);


	}


	return 0;
}

