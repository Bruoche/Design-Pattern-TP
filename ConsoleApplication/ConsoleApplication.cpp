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
	IParticle* get(Image* image, IShader* shader, int x, int y) override
	{
		for (ParticlePrototype* prototype : prototypes)
		{
			if (prototype->match(image, shader, x, y))
			{
				return prototype->clone();
			}
		}
		ParticlePrototype* newPrototype = new ParticlePrototype(image, shader, x, y);
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
		particles.push_back(factory->get(image, shader, rand() % 1000, rand() % 1000));
	}
	for (IParticle* particle : particles) {
		particle->show();
		delete particle;
	}
	particles.clear();
    delete image;
    delete shader;
}
