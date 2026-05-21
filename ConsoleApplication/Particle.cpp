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

class IParticleFactory {
public:
	virtual IParticle* build(int x, int y) = 0;
	virtual void show(int amount, int width, int height)
	{
		std::vector<IParticle*> particles;
		for (int i = 0; i < amount; ++i)
		{
			particles.push_back(build(rand() % width, rand() % height));
		}
		for (IParticle* particle : particles) {
			particle->show();
			delete particle;
		}
		particles.clear();
	};
};

class ParticleFactory : public IParticleFactory {
private:
	Image* image;
	IShader* shader;

public:
	ParticleFactory(Image* image, IShader* shader) : image(image), shader(shader) {};
	
	IParticle* build(int x, int y) override
	{
		return new Particle(image, shader, x, y);
	}
};