#pragma once
#include <iostream>
#include "Resources.cpp"

class IParticle
{
public:
	virtual void show() = 0;
};

class Particle : public IParticle
{
private:
	int x;
	int y;
	IShader* shader;
	Image* image;

public:
	Particle(Image* image, IShader* shader, int x, int y) : 
		image(image), shader(shader), x(x), y(y)
	{}

	void show() override
	{
		image->afficher(x, y);
	}
};
