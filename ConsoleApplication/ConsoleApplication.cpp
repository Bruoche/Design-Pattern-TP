// ConsoleApplication.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#pragma once
#include <iostream>
#include <mutex>
#include "Resources.cpp"
#include "Particle.cpp"
#include "Explosion.cpp"

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
				std::cout << "Already existing particle requested. Cloning." << std::endl;
				return prototype->clone();
			}
		}
		ParticlePrototype* newPrototype = new ParticlePrototype(image, shader, 0, 0, 0, 0, color);
		prototypes.push_back(newPrototype);
		std::cout << "New prototype requested. Creating before cloning." << std::endl;
		return newPrototype->clone();
	}
};

ParticleCloneFactory ParticleCloneFactory::instance;

// Main:

int main()
{
	IParticleFactory* factory = ParticleCloneFactory::getInstance();
	Explosion* explosion = (new ExplosionBuilder(factory, 5, 4))
		->withColor("110e0e")
		->withSpread(1000, 1000)
		->build();
	explosion->play();
	delete explosion;
	return 0;
}
