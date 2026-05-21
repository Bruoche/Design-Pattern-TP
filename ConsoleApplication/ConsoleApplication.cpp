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
    factory->show(5, 1000, 1000);
}