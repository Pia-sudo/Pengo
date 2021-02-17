#include "../../include/entidades/pengo.h"
#include "../../include/estados/juegoStatus.h"

Pengo* Pengo::pengo = 0; //NULL


Pengo::Pengo(){    
    coordX = coordY =  0;
    vida = 3;
    direccion = 1;   
    estado = 1;
    inmortal = false;
    x = x0 = x1  = 280;
    y = y0 =  y1 = 100; 
                                                        //fila                                            columna
    sprite = new Sprite("resources/animacionPengo.png",{0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7},{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2},40,40,x,y);
}
Pengo* Pengo::Instance(){
    if(pengo == 0){
        pengo = new Pengo();
        pengo->velocidad = 55;   
        pengo->movimiento = 0;
    }
    return pengo;
}


Pengo* Pengo::getPengo(){
    return pengo;
}

void Pengo::update(float t){

    if(!bloque){
        switch(estado){
            case 0:
                if(reloj.getElapsedTime().asSeconds()>0.25){
                    switch(sprite->getActual()){
                        case 15:
                            sprite->setSprite(16);
                        break;
                        case 16:
                            sprite->setSprite(17);       
                            JuegoStatus::Instance()->setEstado(0);
                            estado = 1;            
                            coordX = coordY =  0;
                            direccion = 1;   
                            movimiento = 0;
                            x = x0 = x1  = 280;
                            y = y0 =  y1 = 100; 
                            sprite->setPosicion(trunc(x),trunc(y));                                      
                        break;
                        default:
                            sprite->setSprite(15);
                        break;                    
                    }
                reloj.restart();
                }
   
            break;
            case 1:
                delta = t * velocidad;

                    switch(movimiento){
                        case 0:
                        //Quieto
                        if(sprite->getActual() == 17 || sprite->getActual() == 18){
                            if(reloj.getElapsedTime().asSeconds()>0.25){
                                switch(sprite->getActual()){
                                    case 17:
                                        sprite->setSprite(18);
                                    break;
                                    case 18:
                                        sprite->setSprite(1);                                    
                                    break;
                                }
                            }
                            reloj.restart();
                        }else{
                            y0 = (coordY)*40+100;
                            x0 = (coordX)*40+280;
                            x1 = x0;                    
                            y1 = y1; 
                        }
     

                            break;
                        case 1:
                        //Abajo
                            direccion = 1;

                            if(reloj.getElapsedTime().asSeconds()>0.25){
                                switch(sprite->getActual()){
                                    case 0:
                                        sprite->setSprite(1);
                                    break;
                                    case 1:
                                        sprite->setSprite(0);                
                                    break;
                                    default:
                                        sprite->setSprite(1);
                                    break;                    
                                }
                            reloj.restart();
                            }

                            if(!colision(coordX,coordY+1)){
                                if(y <= ((coordY+1)*40+100)){
                                    x0 = x1;
                                    x1 = x0;
                                    y0 = y1;
                                    y1 = y1 + delta;
                                }else{
                                    coordY++;
                                    y0 = (coordY)*40+100;
                                    x0 = (coordX)*40+280;
                                    x1 = x0;                    
                                    y1 = y1;                   
                                    movimiento = 0;
                                }
                            }else{
                                movimiento = 0;
                            }
                            break;
                        case 2:
                        //Izq
                            direccion = 2;

                            if(reloj.getElapsedTime().asSeconds()>0.25){
                                switch(sprite->getActual()){
                                    case 3:
                                        sprite->setSprite(2);
                                    break;
                                    case 2:
                                        sprite->setSprite(3);                
                                    break;
                                    default:
                                        sprite->setSprite(2);
                                    break;                    
                                }
                            reloj.restart();
                            }
                            
                            if(!colision(coordX-1,coordY)){
                                if(x > ((coordX-1)*40+280)){
                                    x0 = x1;
                                    x1 = x1 - delta;  
                                }else{
                                    coordX--;
                                    y0 = (coordY)*40+100;
                                    x0 = (coordX)*40+280;
                                    x1 = x0;
                                    y1 = y1;                      
                                    movimiento = 0;
                                }        
                            }else{
                                movimiento = 0;
                            }
                            break;

                        case 3:
                        //Arriba
                            direccion = 3;
                            if(reloj.getElapsedTime().asSeconds()>0.25){
                                switch(sprite->getActual()){
                                    case 5:
                                        sprite->setSprite(4);
                                    break;
                                    case 4:
                                        sprite->setSprite(5);                
                                    break;
                                    default:
                                        sprite->setSprite(4);
                                    break;                    
                                }
                            reloj.restart();
                            }            
                            if(!colision(coordX,coordY-1)){
                                if(y >= ((coordY-1)*40+100)){

                                    y0 = y1;
                                    y1 = y1 - delta;
                                }else{
                                    coordY--;
                                    y0 = (coordY)*40+100;
                                    x0 = (coordX)*40+280;
                                    x1 = x0;                    
                                    y1 = y1;                      
                                    movimiento = 0;
                                }
                            }else{
                                movimiento = 0;
                            }
                            break;

                        case 4:
                        //Derecha
                            direccion = 4;
                            if(reloj.getElapsedTime().asSeconds()>0.25){
                                switch(sprite->getActual()){
                                    case 7:
                                        sprite->setSprite(6);
                                    break;
                                    case 6:
                                        sprite->setSprite(7);                
                                    break;
                                    default:
                                        sprite->setSprite(6);
                                    break;                    
                                }   
                                    reloj.restart();
                                }
                            if(!colision(coordX+1,coordY)){
                                if(x <= ((coordX+1)*40+280)){
                                    x0 = x1;
                                    x1 = x1 + delta;  
                                }else{
                                    coordX++;   
                                    y0 = (coordY)*40+100;
                                    x0 = (coordX)*40+280;
                                    x1 = x0;                    
                                    y1 = y1;                                 
                                    movimiento = 0;
                                }         
                            }else{
                                movimiento = 0;
                            }
                            break;
                        case 5:
                        //Bailar
                            if(reloj.getElapsedTime().asSeconds()>0.25){
                                switch(sprite->getActual()){
                                    case 20:
                                        sprite->setSprite(21);
                                    break;
                                    case 21:
                                        sprite->setSprite(20); 
                                        estado = 1;               
                                    break;
                                    default:
                                        sprite->setSprite(21);
                                    break;
                                }   
                            reloj.restart();
                            }
                        break;
                        case 6:
                        //Empujar
                            movimiento = 0;
                            switch(direccion){
                                case 1: //bajo
                                    if(reloj.getElapsedTime().asSeconds()>0.25){
                                        switch(sprite->getActual()){
                                            case 8:
                                                sprite->setSprite(9);

                                            break;
                                            case 9:
                                                sprite->setSprite(8);                
                                            break;
                                            default:
                                                sprite->setSprite(9);
                                            break;
                                        }   
                                    reloj.restart();
                                    }
                                    Mundo::Instance()->getMapa()->moverBloque(coordX,coordY+1,1);
                                break;
                                case 2://izq
                                    if(reloj.getElapsedTime().asSeconds()>0.25){
                                    switch(sprite->getActual()){
                                        case 10:
                                            sprite->setSprite(11);

                                        break;
                                        case 11:
                                            sprite->setSprite(10);                
                                        break;
                                        default:
                                            sprite->setSprite(11);
                                        break;
                                    }   
                                reloj.restart();
                                }                
                                    Mundo::Instance()->getMapa()->moverBloque(coordX-1,coordY,2);
                                break;
                                case 3://Arriba

                                    if(reloj.getElapsedTime().asSeconds()>0.25){
                                        switch(sprite->getActual()){
                                            case 12:
                                                sprite->setSprite(13);
                                            break;
                                            case 13:
                                                sprite->setSprite(12);                
                                            break;
                                            default:
                                                sprite->setSprite(13);
                                            break;
                                        }   
                                        reloj.restart();
                                    }                    
                                    Mundo::Instance()->getMapa()->moverBloque(coordX,coordY-1,3);
                                break;
                                case 4://Derecha
                                    if(reloj.getElapsedTime().asSeconds()>0.25){
                                        switch(sprite->getActual()){
                                            case 14:
                                                sprite->setSprite(15);

                                            break;
                                            case 15:
                                                sprite->setSprite(14);                
                                            break;
                                            default:
                                                sprite->setSprite(15);
                                            break;
                                        }   
                                        reloj.restart();
                                    }                 
                                    Mundo::Instance()->getMapa()->moverBloque(coordX+1,coordY,4);
                                break;

                            }


                    }
            break;
        }
    }
}

void Pengo::render(float tick){
    if(movimiento != 0) interpolar(tick);
    sprite->pintar();
}

void Pengo::interpolar(float tick){

    x = x0 * (1-tick) + x1 * tick;
    y = y0 * (1-tick) + y1 * tick;
    
    sprite->setPosicion(trunc(x),trunc(y));
}

void Pengo::quitarVida(){
    if(estado != 0 && !inmortal){ 
        vida--;
        if(vida > 0){
            estado = 0;    
            JuegoStatus::Instance()->restartTiempo();     
        }else{
            JuegoStatus::Instance()->setEstado(2);       
        }
    }

}

void Pengo::setInmortal(){
    if(inmortal){
        inmortal = false;
    }else{
        inmortal = true;
    }
    cout<<"inmortal: "<<inmortal<<endl;
}

void Pengo::reinicio(){            
    coordX = coordY =  0;
    direccion = 1;   
    estado = 1;
    inmortal = false;
    x = x0 = x1  = 280;
    y = y0 =  y1 = 100; 
    sprite->setSprite(0);    
    sprite->setPosicion(x,y);
}

