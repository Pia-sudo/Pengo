#include "math.h"
#include "../fachada/sprite.h"
#include "../mundo/mundo.h"

#pragma once

class Pengo{
    private:
        static Pengo* pengo;
        Sprite* sprite;
        sf::Clock reloj;       
        float x; //respecto a la pantalla
        float y;
        float x0;
        float y0;
        float x1;
        float y1;
        float delta;
        int vida;
        int velocidad;
        int movimiento;
        int direccion;
        int estado;
        int coordX; //respecto a la matriz mapa
        int coordY; //respecto a la matriz mapa
        bool bloque;
        bool inmortal;

    protected:
        Pengo();
        Pengo(const Pengo&);
    public:
        static Pengo* Instance();
        Pengo* getPengo();        
        void render(float);
        void update(float);
        void interpolar(float);
        void setBloque(bool n){bloque = n;}
        void setEstado(int n){estado = n;}        
        bool colision(int x, int y){return Mundo::Instance()->getMapa()->colision(x,y);}
        void setMovimiento(int n){movimiento = n;}        
        void setVelocidad(int v){velocidad = v;}
        int getEstado(){return movimiento;}
        int getX(){return coordX;}
        int getY(){return coordY;}
        Sprite* getSprite(){return sprite;}
        int getDireccion(){return direccion;}
        void quitarVida();
        void setInmortal();
        void reinicio();
        void reinicioVidas(){vida = 3;}
        int getVidas(){return vida;}
};
 