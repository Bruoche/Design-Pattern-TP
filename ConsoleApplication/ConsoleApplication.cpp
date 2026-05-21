// ConsoleApplication.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#pragma once
#include <iostream>
#include "Resources.cpp"
#include "Particle.cpp"

// Elements statiques :

std::mutex cloneFactoryMutex;

// Permets l'obtention d'une particule clonable unique au lieu de refaire le constructeur pour chaque instance
class ParticleCloneFactory : public IParticleFactory {
private:
	static ParticleCloneFactory instance;
	std::vector<ParticlePrototype*> prototypes;

	ParticleCloneFactory()
	{
		const std::lock_guard<std::mutex> lock(cloneFactoryMutex);
	}

public:
	~ParticleCloneFactory()
	{
		for (ParticlePrototype* prototype : prototypes) {
			delete prototype;
		}
		prototypes.clear();
	}

	static ParticleCloneFactory* getInstance()
	{
		return &instance;
	}

	// Return a clone of it's prototype particle.
	// Return null if no corresponding prototype is found.
	IParticle* get(Image* image, IShader* shader, std::string color) override
	{
		for (ParticlePrototype* prototype : prototypes)
		{
			if (prototype->match(image, shader, color))
			{
				return prototype->clone();
			}
		}
		ParticlePrototype* newPrototype = new ParticlePrototype(image, shader, 0, 0, 0, 0, color);
		prototypes.push_back(newPrototype);
		return newPrototype->clone();
	}
};

ParticleCloneFactory ParticleCloneFactory::instance;

// Main:

int main()
{
	IParticleFactory* factory = ParticleCloneFactory::getInstance();
	Image* image = new Image("smoke.png");
	IShader* shader = new Shader();	
	std::vector<IParticle*> particles;
	for (int i = 0; i < 5; ++i)
	{
		IParticle* particle = factory->get(image, shader, "110e0e");
		particle->setVelocity(rand()%1000, rand()%1000);
		particles.push_back(particle);
	}
	for (int i = 0; i < 4; ++i)
	{
		std::cout << "FRAME " << i << std::endl;
		for (IParticle* particle : particles)
		{
			particle->show();
			particle->physicEvent();
		}
	}
	for (IParticle* particle : particles) {
		delete particle;
	}
	particles.clear();
    delete image;
    delete shader;
}
