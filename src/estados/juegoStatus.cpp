#include "../../include/estados/juegoStatus.h"

JuegoStatus* JuegoStatus::juego = 0;

JuegoStatus* JuegoStatus::Instance(){
    if(juego == 0){
        juego = new JuegoStatus;
    }
    return juego;
}
JuegoStatus::JuegoStatus(){
    mundo = Mundo::Instance();
    pengo = Pengo::Instance();
    niveles = 1;
    fuente.loadFromFile("resources/Letra.ttf");
    textoTiempo.setFont(fuente);
    textoTiempo.setColor(sf::Color::White);
    textoTiempo.setPosition(830,200);
    textoTiempo.setCharacterSize(18);   
    textoVida.setFont(fuente);
    textoVida.setColor(sf::Color::White);
    textoVida.setPosition(830,250);
    textoVida.setCharacterSize(18);
    textoPuntos.setFont(fuente);   
    textoPuntos.setColor(sf::Color::White);
    textoPuntos.setPosition(830,300);
    textoPuntos.setCharacterSize(18); 
    textoEnemigos.setFont(fuente);   
    textoEnemigos.setColor(sf::Color::White);
    textoEnemigos.setPosition(830,350);
    textoEnemigos.setCharacterSize(18); 
    textoNivel.setFont(fuente);   
    textoNivel.setColor(sf::Color::White);
    textoNivel.setPosition(830,400);
    textoNivel.setCharacterSize(18);     
    textoTransicion.setFont(fuente);   
    textoTransicion.setColor(sf::Color::Black);
    textoTransicion.setPosition(300,200);
    textoTransicion.setCharacterSize(32);     
    textoTransicion.setString("Buen trabajo!\nPasas al siguiente nivel");
    estado = 1;
    restart = false;
}
void JuegoStatus::handle(){ 
    sf::Event event;
    MotorGrafico* motor = MotorGrafico::Instance();
    if(estado == 1 || estado == 5){
            while (motor->getVentana()->pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        MotorGrafico::Instance()->cerrarVentana();
                    break;
                    case sf::Event::KeyReleased:

                        switch (event.key.code){
                            case sf::Keyboard::Escape:
                                MotorGrafico::Instance()->cerrarVentana();
                            break;
                            case sf::Keyboard::D:
                                if(pengo->getEstado() == 0) pengo->setMovimiento(5);
                            break;
                            case sf::Keyboard::Space:
                                if(pengo->getEstado() == 0) pengo->setMovimiento(6);
                            break; 
                            case sf::Keyboard::G:
                                pengo->setInmortal();
                            break; 
                            case sf::Keyboard::X:
                                estado = 2;
                            break;                                               
                            case sf::Keyboard::N:
                                estado = 3;
                            break;                                       

                        }//Fin de switch teclas
                    break; //De keyReleased

                    case sf::Event::KeyPressed:
                        switch (event.key.code){
                            case sf::Keyboard::Down:
                                if(pengo->getEstado() == 0) pengo->setMovimiento(1);
                            break;
                            case sf::Keyboard::Left:
                                if(pengo->getEstado() == 0) pengo->setMovimiento(2);
                            break;
                            case sf::Keyboard::Up:
                                if(pengo->getEstado() == 0) pengo->setMovimiento(3);
                            break;
                            case sf::Keyboard::Right:
                                if(pengo->getEstado() == 0) pengo->setMovimiento(4);
                            break;                                   

                        }//Fin de switch teclas
                    break;//De KeyPressed
                }//De event type
            }//De getWindow
     
    }//De switch estado
}
void JuegoStatus::update(float t){

    switch(estado){
        case 0:
                if(!restart){
                    espera.restart();
                    restart = true;
                }
                if(espera.getElapsedTime().asSeconds()>2){
                    estado = 1;
                    pengo->update(t);
                    mundo->update(t);
                    espera.restart();
                    tiempo.restart();
                }
        break;
        case 1:

                pengo->update(t);
                mundo->update(t);
            
                if(tiempo.getElapsedTime().asSeconds()>=120 &&  mundo->getEnemigoS()<= 4){              
                    estado = 5; 
                    mundo->setHuida();
                } 

        break;
        case 2:
                mundo->reinicio();
                pengo->reinicio();
                pengo->reinicioVidas();
                puntos = 0;
                tiempo.restart();
                estado = 1;
        break;
        case 3:
                mundo->siguiente();
                pengo->reinicio();
                puntos = puntos + 2000;
                estado = 4;
                transicion.restart();
                tiempo.restart();
                niveles++;
        break;
        case 4:
        //Transicion
            if(transicion.getElapsedTime().asSeconds() > 2){
                estado = 1;
            }
        break;
        case 5:
                pengo->update(t);
                mundo->update(t);
                if(mundo->getHuida())
                    estado = 3;
        break;
    }
}
void JuegoStatus::render(float t){
    if(estado == 1 || estado == 5){
        MotorGrafico::Instance()->limpiar();
        mundo->render(t);
        pengo->render(t);
    }else{
        MotorGrafico::Instance()->limpiar();       
    }
    //HUD
    if(estado == 4){
        MotorGrafico::Instance()->pintarFondo();
        MotorGrafico::Instance()->pintarTexto(textoTransicion);
    }else{
        int stiempo = 120 - tiempo.getElapsedTime().asSeconds();
     //   textoTiempo.setString("Tiempo restante: "+to_string(stiempo));        
        textoVida.setString("Vidas: "+to_string(pengo->getVidas()));
        textoPuntos.setString("Puntos: "+to_string(puntos));
        textoEnemigos.setString("Enemigos restantes: "+to_string(mundo->getEnemigoS()));         
        textoNivel.setString("Nivel: "+to_string(niveles)); 
        MotorGrafico::Instance()->pintarTexto(textoVida);
        MotorGrafico::Instance()->pintarTexto(textoPuntos);
        MotorGrafico::Instance()->pintarTexto(textoEnemigos);
        MotorGrafico::Instance()->pintarTexto(textoNivel);
    }
};  