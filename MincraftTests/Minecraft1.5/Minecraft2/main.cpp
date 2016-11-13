//Построение с VS2015 и SFML-2.3.2
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
using namespace sf;
using namespace std;

GLuint LoadTexture(String name)
{
	Image image;
	if (!image.loadFromFile(name))
		return EXIT_FAILURE;

	image.flipVertically();

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	//glTexImage2D(GL_TEXTURE_2D, GL_RGBA, GL_RGBA, image.getSize().x, image.getSize().y, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); //GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); //GL_CLAMP_TO_EDGE);

	return texture;
}


int main()
{
	cout << "Loading..." << endl << endl;
	RenderWindow window(VideoMode(1920, 1080), "MyMinecraft", Style::Fullscreen);

	Texture tex;
	tex.loadFromFile("sprite.jpg");
	Sprite background(tex);

	GLuint mytexture = LoadTexture("paper.jpg");

	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Right);// mRight = 1;
				if (event.key.code == Mouse::Left);//  mLeft = 1;
			}
		}
		window.draw(background);

		window.display();
	}
	cout << endl << "Finished.";

}