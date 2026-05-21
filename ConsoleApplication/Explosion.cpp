#pragma once
#include <iostream>
#include "Particle.cpp"

class ExplosionConfig
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

public:
	ExplosionConfig(
		int x, int y,
		std::string color, int particleCount,
		int spreadX, int spreadY,
		int lifetime
	) : // Explosion est un objet immuable, donc seul le constructeur permettra de set ses champs. 
		x(x), y(y), 
		color(color), particleCount(particleCount), 
		spreadX(spreadX), spreadY(spreadY), 
		lifetime(lifetime)
	{}

	int getX() { return x; }
	int getY() { return y; }
	std::string getColor() { return color; }
	int getParticleCount() { return particleCount; }
	int getSpreadX() { return spreadX; }
	int getSpreadY() { return spreadY; }
	int getLifetime() { return lifetime; }
};

class ExplosionConfigBuilder
{
private:
	int x = 0;
	int y = 0;
	std::string color = "000000";
	int particleCount;
	int spreadX = 0;
	int spreadY = 0;
	int lifetime;

public:
	ExplosionConfigBuilder(int particleCount, int lifetime) : particleCount(particleCount), lifetime(lifetime) {}

	ExplosionConfigBuilder* withCoordinates(int x, int y) 
	{
		this->x = x;
		this->y = y;
		return this;
	}

	ExplosionConfigBuilder* withColor(std::string color)
	{
		this->color = color;
		return this;
	}

	ExplosionConfigBuilder* withSpread(int x, int y) 
	{
		this->spreadX = x;
		this->spreadY = y;
		return this;
	}

	ExplosionConfig* build()
	{
		return new ExplosionConfig(x, y, color, particleCount, spreadX, spreadY, lifetime);
	}
};

class IExplosion
{
public:
	virtual void play() = 0;
};

class Explosion : public IExplosion
{
private:
	std::vector<IParticle*> particles;
	int lifetime;

public:
	Explosion(std::vector<IParticle*> particles, int lifetime) : lifetime(lifetime), particles(particles) {}

	~Explosion()
	{
		for (IParticle* particle : particles) {
			delete particle;
		}
		particles.clear();
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

class IExplosionFactory
{
public:
	virtual IExplosion* get(IParticleFactory* particleFactory, ExplosionConfig* config) = 0;
};

class ExplosionFactory : public IExplosionFactory
{
private:
	Image* image = new Image("smoke.png");
	IShader* shader = new Shader();

public:
	~ExplosionFactory()
	{
		delete image;
		delete shader;
	}

	virtual IExplosion* get(IParticleFactory* particuleFactory, ExplosionConfig* config)
	{
		std::vector<IParticle*> particles;
		for (int i = 0; i < config->getParticleCount(); ++i)
		{
			IParticle* particle = particuleFactory->get(image, shader, config->getColor());
			particle->setVelocity(rand() % config->getSpreadX(), rand() % config->getSpreadY());
			particles.push_back(particle);
		}
		return new Explosion(particles, config->getLifetime());
	}
};