#include "../../include/entidades/bloque.h"
#include "../../include/mundo/mundo.h"
#include "../../include/entidades/pengo.h"

Bloque::Bloque(int t, int x, int y){

    Sprite* sp = new Sprite();
    switch(t){
        //bloqueHielo
        case 0: 
            sp = new Sprite("resources/bloqueHielo.png",{0,1,2,3,4,5,6,7,8,9},{0,0,0,0,0,0,0,0,0,0},40,40, 40*x+280,40*y+100);
        break;
        //bloqueEstrella
        case 1:
            sp = new Sprite("resources/bloqueEstrella1.png",{0,1},{0,0},40,40, 40*x+280,40*y+100);
        break;
    }
    sprite = sp;
    tipo = t;
    roto = 0;
    snowbee = false;
    coordx = x;
    coordy = y;
    activado = false;
    this->x = x0 = x1 = 40*x+280;
    this->y = y0 = y1 = 40*y+100;
}
Bloque::~Bloque(){
//Borrar los punteros, liberar memoria
    delete sprite;
    sprite = NULL;
}
void Bloque::romper(int x, int y){
    //animación de romper bloque

    coordx1 = x;
    coordy1 = y;

    //Primero movimiento
    if(x == coordx && y == coordy){
       if(tipo == 0) roto = 2;
    }else{
        Mundo::Instance()->setBloque(true);
        Pengo::Instance()->setBloque(true);
        roto = 1;
    }
}
int Bloque::getDireccion(){
    if(coordx1 > coordx){
    //Derecha
        direccion = 0;
    }else if(coordx1 < coordx){
    //Izq   
        direccion = 1;
    }else if(coordy1 > coordy){
    //Abajo
        direccion = 2;
    }else if(coordy1 < coordy){
    //Arriba
        direccion = 3;
    }
    return direccion;
}
void Bloque::update(float t){

    if(roto == 1){
        int delta = 100 * t;
        switch(getDireccion()){
            case 0:
            //Derecha
                if(x <= (coordx1*40+280)){
                    x0 = x1;
                    x1 = x1 + delta;
                    Mundo::Instance()->setBloque(true);
                    Pengo::Instance()->setBloque(true);
                }else{
                    roto = 0;
                    x0 = coordx1*40+280;
                    y1 = y0;                    
                    y0 = coordy1*40+100;
                    y1 = y0;
                    coordx = coordx1;
                    coordy = coordy1;                                    
                }                           
            break;
            case 1:
            //Izq
                if(x > (coordx1*40+280)){
                    x0 = x1;
                    x1 = x1 - delta;

                }else{
                    roto = 0;
                    x0 = coordx1*40+280;
                    y1 = y0;                    
                    y0 = coordy1*40+100;
                    y1 = y0;
                    coordx = coordx1;
                    coordy = coordy1;                      
                }               
            break;                          
            case 2:
            //Abajo
                if(y <= (coordy1*40+100)){
                    y0 = y1;
                    y1 = y1 + delta;
                    Mundo::Instance()->setBloque(true);
                    Pengo::Instance()->setBloque(true);
                }else{
                    roto = 0;
                    x0 = coordx1*40+280;
                    y1 = y0;                    
                    y0 = coordy1*40+100;
                    y1 = y0;
                    coordx = coordx1;
                    coordy = coordy1;                     
                }               
                break;
            case 3:
            //Arriba
                if(y >= (coordy1*40+100)){
                    y0 = y1;
                    y1 = y1 - delta;
                    Mundo::Instance()->setBloque(true);
                    Pengo::Instance()->setBloque(true);
                }else{
                    roto = 0;
                    x0 = coordx1*40+280;
                    y1 = y0;                    
                    y0 = coordy1*40+100;
                    y1 = y0;
                    coordx = coordx1;
                    coordy = coordy1;
                    
                }               
                break;                
        }      
    }else{
        x0 = coordx*40+280;
        x1 = x0;                    
        y0 = coordy*40+100;
        y1 = y0;         
    } 
    if(roto == 2){
        //Animacion de romper bloque
        if(reloj.getElapsedTime().asSeconds()>0.1){
            switch(sprite->getActual()){
                case 0:
                    sprite->setSprite(1);
                break;
                case 1:
                    sprite->setSprite(2);                
                break;
                case 2:
                    sprite->setSprite(3);                
                break;
                case 3:
                    sprite->setSprite(4);                
                break;    
                case 4:
                    sprite->setSprite(5);                
                break;     
                case 5:
                    sprite->setSprite(6);                
                break;   
                case 6:
                    sprite->setSprite(7);                
                break;        
                case 7:
                    roto = 0;
                    Mundo::Instance()->getMapa()->borrarBloque(coordx1,coordy1);                                                           
                break;  
                case 9:
                    roto = 0;
                    Mundo::Instance()->getMapa()->borrarBloque(coordx1,coordy1);                                                           
                break;                    
                default:
                    sprite->setSprite(1);
                break;                                                                                    
        }
        reloj.restart();
        }
        x0 = coordx1*40+280;
        x1 = x0;                    
        y0 = coordy1*40+100;
        y1 = y0;
    }
    if(tipo == 1){
//Bloque estrella
    //Miramos en las 8 direcciones adyacentes si hay otro bloque estrella
    int estrellas = Mundo::Instance()->getMapa()->comprobarEstrella(coordx,coordy);
    if(estrellas > 0){
        //Animacion
        if(reloj.getElapsedTime().asSeconds()>0.1){
            switch(sprite->getActual()){
                case 0:
                    sprite->setSprite(1);
                break;
                case 1:
                    sprite->setSprite(0);                
                break;
                                                                                    
        }
        reloj.restart();
        }            

    }
    if(estrellas == 2){
        //Aturdir snowbees
        Mundo::Instance()->aturdirSnowbees();
        Mundo::Instance()->mostrarSnowbees();
    }

    }
}

void Bloque::render(float tick){
    if(roto == 1){ 
        interpolar(tick);
    }else{
        Mundo::Instance()->setBloque(false);
        Pengo::Instance()->setBloque(false);
    }
    sprite->pintar();
}

void Bloque::interpolar(float tick){

    x = x0 * (1-tick) + x1 * tick;
    y = y0 * (1-tick) + y1 * tick;

    sprite->setPosicion(trunc(x),trunc(y));    
        comprobarSnowBee();
}

void Bloque::comprobarSnowBee(){
    vector<SnowBee*> enemigos = Mundo::Instance()->getMalos();
    for(SnowBee* bee : enemigos){
        if(bee->getSprite()->getSprite().getGlobalBounds().intersects(sprite->getSprite().getGlobalBounds())){
            bee->matar(direccion);
        }
    }
}