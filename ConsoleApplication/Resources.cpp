#pragma once
#include <iostream>
#include <string>
#include <vector>

class IShader {}; // Interface POC pour simuler l'utilisation d'un shader

class Shader : public IShader {};

class Image
{
private:

    std::string cheminFichier;

    std::vector<char> donneesImage;

public:

    Image(const std::string& cheminFichier)
    {
        this->cheminFichier = cheminFichier;

        // Simulation d'une image lourde de 5 Mo
        donneesImage.resize(5 * 1024 * 1024);

        std::cout << "[Chargement] Image "
            << cheminFichier
            << " chargee en memoire ("
            << donneesImage.size() / (1024 * 1024)
            << " Mo)"
            << std::endl;
    }

    void afficher(int x, int y)
    {
        std::cout << "Affichage de "
            << cheminFichier
            << " en position ("
            << x
            << ", "
            << y
            << ")"
            << std::endl;
    }
};
