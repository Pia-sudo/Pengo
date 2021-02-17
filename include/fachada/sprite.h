#include <SFML/Graphics.hpp>
#include <vector>
#include "iostream"
#include "motorGrafico.h"

using namespace std;

#pragma once
//Clase interfaz para acceder a los metodos de sfml de los sprites
class Sprite{

    public:
        Sprite();
        Sprite(string urlTextura,vector<int> col,vector<int> row,int w,int h, float x, float y);
        ~Sprite();
        void pintar();
        void setPosicion(float x,float y);
        void setSprite(int n){actual = n;}
        int getActual(){return actual;}
        sf::Sprite getSprite(){return sprites[actual];}
        sf::Sprite getSprite(int n){return sprites[n];}

    private:
        float x;
        float y;
        sf::Texture* textura;  
        vector<sf::Sprite> sprites;
        int actual;
};