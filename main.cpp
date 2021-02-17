#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "include/fachada/motorGrafico.h"
#include "include/entidades/pengo.h"
#include "include/estados/juegoStatus.h"
#include "include/mundo/mapa.h"


using namespace std;

const float kTiempoUpdate = 1000/15;
int main() {

  MotorGrafico* motor = MotorGrafico::Instance();
  JuegoStatus* juego  = JuegoStatus::Instance();
  

  sf::Clock reloj;
  sf::Clock relojUpdate;

  sf::Time tiempo;

  //Bucle del juego
  while (motor->getVentana()->isOpen()) {
    juego->handle();

    if(relojUpdate.getElapsedTime().asMilliseconds() > kTiempoUpdate){
      tiempo = relojUpdate.restart();
      juego->update(tiempo.asSeconds());
    }

  //para la interpolación del render
    float percentTick = fmin(1.0f,relojUpdate.getElapsedTime().asMilliseconds());
    juego->render(tiempo.asSeconds());

    motor->pintarVentana();  
  }
  return 0;
}