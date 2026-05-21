#pragma once
#include <iostream>
#include "Particle.cpp"

class IExplosion
{
	virtual void play() = 0;
};

class Explosion : public IExplosion
{
private:
	int x;
	int y;
	std::string color;
	int particleCount;
	int spreadX;
	int spreadY;
	int lifetime;
	std::vector<IParticle*> particles;
	Image* image = new Image("smoke.png");
	IShader* shader = new Shader();

public:
	Explosion(
		int x, int y,
		std::string color, int particleCount,
		int velocityX, int velocityY,
		int lifetime,
		IParticleFactory* factory
	) : // Explosion est un objet immuable, donc seul le constructeur permettra de set ses champs. 
		x(x), y(y), 
		color(color), particleCount(particleCount), 
		spreadX(velocityX), spreadY(velocityY), 
		lifetime(lifetime)
	{
		std::cout << "Building explosion..." << std::endl;
		for (int i = 0; i < particleCount; ++i)
		{
			IParticle* particle = factory->get(image, shader, color);
			particle->setVelocity(rand() % spreadX, rand() % spreadY);
			particles.push_back(particle);
		}
		std::cout << "Explosion built..." << std::endl;
	}

	~Explosion()
	{
		for (IParticle* particle : particles) {
			delete particle;
		}
		particles.clear();
		delete image;
		delete shader;
	}

	void play() override 
	{
		for (int i = 0; i < lifetime; ++i)
		{
			std::cout << "FRAME " << i << std::endl;
			for (IParticle* particle : particles)
			{
				particle->show();
				particle->physicEvent();
			}
		}
	}
};