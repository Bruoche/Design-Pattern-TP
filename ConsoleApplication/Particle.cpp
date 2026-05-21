#pragma once
#include <iostream>
#include <mutex>
#include <map>
#include "Resources.cpp"

// Particles

class IParticle
{
public:
	virtual void show() = 0;
};

class Particle : public IParticle
{
protected:
	int x;
	int y;
	IShader* shader;
	Image* image;

public:
	Particle(Image* image, IShader* shader, int x, int y) : 
		image(image), shader(shader), x(x), y(y)
	{}

	void setPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void show() override
	{
		image->afficher(x, y);
	}
};

class IPrototype
{
	virtual IPrototype* clone() = 0;
};

class ParticlePrototype : public Particle, public IPrototype
{
public:
	ParticlePrototype(Image* image, IShader* shader, int x, int y) : 
		Particle(image, shader, x, y) 
	{}

	bool match(Image* image, IShader* shader, int x, int y)
	{
		if ((this->image != image) 
			|| (this->shader != shader)
			|| (this->x != x)
			|| (this->y != y)
		) {
			return false;
		}
		return true;
	}
	
	ParticlePrototype* clone() override
	{
		return new ParticlePrototype(*this);
	}
};

// Factories

class IParticleFactory {
public:
	virtual IParticle* get(Image*, IShader*, int x, int y) = 0;
};
