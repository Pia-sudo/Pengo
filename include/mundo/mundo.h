#include "../mundo/mapa.h"
#include "../entidades/snowBee.h"
#pragma once

class Mundo{
     private:
        static Mundo* mundo;
        Mapa* mapa; 
        vector<SnowBee*> enemigos;
        int nEnemigos;
        bool bloque;
        sf::Clock tiempo;
        int idMapa;
        int estado;
        int n;
        vector<int> mapasJugados;

    protected:
        Mundo();
        ~Mundo();
        Mundo(const Mundo&);
        
    public:
        static Mundo* Instance();
        Mundo* getMundo(){return mundo;} 
        Mapa*  getMapa(){return mapa;}
        vector<SnowBee*> getMalos(){return enemigos;}
        void setBloque(bool n){bloque = n;}
        void render(float);
        void update(float);   
        void reinicio(); 
        void siguiente();     
        void addMalo(){nEnemigos++;}
        void removeMalo(){mapa->buscarSnowBee(); nEnemigos = nEnemigos-1;}    
        int getEnemigoS(){return nEnemigos;}
        void aturdirSnowbees();
        void aturdirSnowbees(int x, int y);
        void mostrarSnowbees();
        void addenemigo(SnowBee* bee){enemigos.push_back(bee);}
        bool getHuida();
        void setHuida();
};