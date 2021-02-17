#include "status.h"
#include "../mundo/mundo.h"
#include "../fachada/motorGrafico.h"
#include "../entidades/pengo.h"
#pragma once

class JuegoStatus : public Status{

    private:
        static JuegoStatus* juego;
        Mundo* mundo;
        Pengo* pengo;
        int estado;
        int niveles;
        bool restart;
        sf::Clock espera;   
        sf::Clock transicion;
        sf::Clock tiempo;
        sf::Font fuente;
        sf::Text textoVida;
        sf::Text textoPuntos;
        sf::Text textoNivel;  
        sf::Text textoTransicion;  
        sf::Text textoTiempo;  
        sf::Text textoEnemigos;              
        int puntos;      
    protected:
        JuegoStatus();
        JuegoStatus(const JuegoStatus&);
        JuegoStatus &operator=(const JuegoStatus &);

    public:
        static JuegoStatus* Instance();
        void handle();
        void update(float);
        void render(float);
        void setEstado(int n){estado = n;}
        void addPuntos(int n){puntos = puntos + n;}
        void restartTiempo(){tiempo.restart();}
};