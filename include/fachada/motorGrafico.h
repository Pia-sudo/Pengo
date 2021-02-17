#include <SFML/Graphics.hpp>
using namespace std;
#pragma once

class MotorGrafico{
//La clase motor es una clase singleton
    private:
        sf::RenderWindow *ventana;
        static MotorGrafico *motor;
    
    protected:
        MotorGrafico(); //Constructor por defecto
        MotorGrafico(const MotorGrafico&); //Contructor de copia

    public:
        static MotorGrafico* Instance();
        void pintarVentana();
        void pintarSprite(sf::Sprite);
        void pintarTexto(sf::Text);
        void limpiar();
        void cerrarVentana();
        sf::RenderWindow* getVentana();
        void setVentana(sf::RenderWindow*);
        sf::Clock createReloj(){return sf::Clock();}
        void pintarFondo();
};
