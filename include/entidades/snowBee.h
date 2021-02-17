#include "../fachada/sprite.h"

#pragma once

class SnowBee{
    private:
        Sprite* sprite;
        int coordX;
        int coordY;
        int coordX0;
        int coordY0;        
        int velocidad;
        int vida;
        int movimiento;
        int direccion;
        int xInicio;
        int yInicio;
        float x;
        float y;
        float x0;
        float x1;
        float y0;
        float y1;
        float delta;
        int estado;
        int lastDireccion;
        bool aturdido;
        bool bloque;
        bool huida;
        sf::Clock reloj; //para la animacion
        sf::Clock respawn; //reaparecer

    public:
        SnowBee(){};
        SnowBee(int col, int fila);
        ~SnowBee();
        void render(float);
        void update(float);
        void interpolar(float);
        Sprite* getSprite(){return sprite;}
        sf::Clock stun;
        vector<int> getCoords(){return {coordX,coordY};}
        void animacionNacer();    
        void animacionMorir();            
        void animacionHuevo();
        void setEstado(int n){estado = n;}
        void matar(int d);
        int elegirDireccion(); 
        bool colisionBee(int x, int y);
        void colisionPengo();
        void reinicio();
        void setBloque(bool n){bloque = n;}
        void aturdir(){stun.restart();estado = 1; movimiento = 0; aturdido = true;}
        bool comprobarEstrella(int x, int y);
        bool getHuida(){return huida;}
        int getEstado(){return estado;}
};
 