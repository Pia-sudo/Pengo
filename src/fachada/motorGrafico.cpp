#include "../../include/fachada/motorGrafico.h"

MotorGrafico* MotorGrafico::motor = 0; //0 es lo mismo que poner NULL

//Se deja vacío el constructor, solo se puede instanciar 1 vez (singleton)
MotorGrafico::MotorGrafico(){}

MotorGrafico* MotorGrafico::Instance(){
    if(motor == 0){ //Si es null es que no se ha instanciado
    //instanciamos la clase motor y creamos su ventana
        motor = new MotorGrafico();
        sf::RenderWindow *ptr =  new sf::RenderWindow(sf::VideoMode(1080, 720), "P0. PENGO");
        motor->ventana = ptr;
    }
}

void MotorGrafico::pintarVentana(){
    ventana->display();
}

void MotorGrafico::pintarSprite(sf::Sprite s){
    ventana->draw(s);
}

void MotorGrafico::pintarTexto(sf::Text t){
    ventana->draw(t);
}

void MotorGrafico::limpiar(){
    ventana->clear();
}

void MotorGrafico::cerrarVentana(){
    ventana->close();
}

sf::RenderWindow* MotorGrafico::getVentana(){
    return ventana;
}

void MotorGrafico::setVentana(sf::RenderWindow* v){
    ventana = v;
}

void MotorGrafico::pintarFondo(){
    sf::Texture tex;
    tex.loadFromFile("resources/fondo.png");
    sf::Sprite sp(tex);
    pintarSprite(sp);
}
