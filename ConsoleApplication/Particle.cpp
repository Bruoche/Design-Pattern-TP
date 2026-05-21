#pragma once
#include <iostream>
#include <mutex>
#include <map>
#include "Resources.cpp"

// Particles

class IParticle
{
public:
	virtual void setVelocity(int x, int y) = 0;
	virtual void show() = 0;
	virtual void physicEvent() = 0;
};

class Particle : public IParticle
{
protected:
	int x;
	int y;
	int velocityX;
	int velocityY;
	std::string color; // Idieally I'd use an actual color type but it's just for POC.
	IShader* shader;
	Image* image;

public:
	Particle(Image* image, IShader* shader, int x, int y, int velocityX, int velocityY, std::string color) :
		image(image), shader(shader), x(x), y(y), velocityX(velocityX), velocityY(velocityY), color(color)
	{}

	void setVelocity(int x, int y) override
	{
		this->velocityX = x;
		this->velocityY = y;
	}

	void setPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void show() override
	{
		image->afficher(x, y);
		std::cout << "-> #" << color << std::endl;
	}

	void physicEvent()
	{
		x += velocityX;
		y += velocityY;
	}
};

class IPrototype
{
	virtual IPrototype* clone() = 0;
};

class ParticlePrototype : public Particle, public IPrototype
{
public:
	ParticlePrototype(Image* image, IShader* shader, int x, int y, int velocityX, int velocityY, std::string color) :
		Particle(image, shader, x, y, velocityX, velocityY, color)
	{}

	// Check if particle style matches
	bool match(Image* image, IShader* shader, std::string color)
	{
		if ((this->image != image) 
			|| (this->shader != shader)
			|| (this->color != color)
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
	virtual IParticle* get(Image*, IShader*, std::string color) = 0;
};
