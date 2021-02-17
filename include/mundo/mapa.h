#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

#include "../entidades/bloque.h"
#include <string.h>

using namespace std;
#pragma once
class Mapa{

    private:
        int ***tilemap;
        Bloque ****tilemapBloques;
        int numCapas;
        int alto;
        int ancho;
        int tileAncho;
        int tileAlto;
        int borde;
        int bloquesTotal;
        int estado;
        Sprite* bordeArr;
        Sprite* bordeAbj;
        Sprite* bordeIzq;
        Sprite* bordeDer;        
        sf::Clock reloj;       
        sf::Clock tiempo; 
        sf::Clock delay;
        vector<Sprite*> camino;
        int cont;
    public:
        Mapa(int n);
        ~Mapa();
        void render(float);
        void update(float);
        bool colision(int x, int y);
        bool esEstrella(int x, int y);        
        void animarBorde(int);
        void moverBloque(int,int,int);
        void borrarBloque(int x,int y);
        void comprobarBorde(int x, int y);
        Bloque* getBloque(int x, int y){return tilemapBloques[0][x][y];}
        void setEstado(int n){estado = n;}
        int getEstado(){return estado;}
        int getBloques(){return bloquesTotal;}
        void buscarBloque();
        int comprobarEstrella(int x, int y);
        void buscarSnowBee();
};