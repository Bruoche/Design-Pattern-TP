// ConsoleApplication.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#pragma once
#include <iostream>
#include "Resources.cpp"
#include "Particle.cpp"

int main()
{
	Image* image = new Image("smoke.png");
	IShader* shader = new Shader();
	IParticleFactory* factory = new ParticleFactory(image, shader);
	std::vector<IParticle*> particles;
	for (int i = 0; i < 5; ++i)
	{
		particles.push_back(factory->getInitial(rand() % 1000, rand() % 1000));
	}
	for (IParticle* particle : particles) {
		particle->show();
		delete particle;
	}
	particles.clear();
    delete image;
    delete shader;
    delete factory;
}