#include "../fachada/sprite.h"

#pragma once

class Bloque{
    private:
        Sprite* sprite;
        sf::Clock reloj;
        int tipo;
        int roto;
        int coordx;
        int coordy;
        float x;
        float y;
        float x0;
        float y0;
        float x1;
        float y1;
        int coordx1;
        int coordy1;
        int direccion;
        bool activado;
        bool snowbee;

    public:
        Bloque(){};
        Bloque(int tipo, int col, int fila);
        ~Bloque();
        void interpolar(float);
        void romper(int,int);
        void render(float);
        void update(float);
        void comprobarSnowBee(); 
        int getTipo(){return tipo;};
        int getDireccion();
        Sprite* getSprite(){return sprite;};
        vector<int> getCoords(){return {coordx,coordy};}
        void setSnowbee(){snowbee = true;}
        void removeSnowbee(){snowbee = false;}
        bool getBee(){return snowbee;}
};
 