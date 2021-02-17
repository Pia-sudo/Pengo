#include "../../include/entidades/snowBee.h"
#include "../../include/estados/juegoStatus.h"

SnowBee::SnowBee(int col, int fila){
    xInicio = coordX =  col;
    yInicio = coordY = fila;
    coordX0 = coordY0 =  0;
    vida = 1;
    x = x0 = x1 = col*40+280;
    y = y0 = y1 = fila*40+100;
    velocidad = 45;
    delta = 0;
    aturdido = false;
    bloque = false;
    huida = false;
    movimiento = elegirDireccion();
    sprite = new Sprite("resources/bees.png",{0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1},{1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,4,4,4,4,4,4,4,5,5},40,40,x,y);
    sprite->setSprite(17);
    estado = 5; //Huevo
    respawn.restart();  
}
SnowBee::~SnowBee(){
    delete sprite;
    sprite = NULL;
}

void SnowBee::update(float t){
    if(vida == 1){
        switch(estado){
            case 0:
            //Spawn
                animacionNacer();
            break;
            case 1:
                delta = t * velocidad;
                if(aturdido){
                        if(stun.getElapsedTime().asSeconds() < 5){
                            if(reloj.getElapsedTime().asSeconds()>0.25){
                                switch(sprite->getActual()){
                                    case 20:
                                        sprite->setSprite(21);
                                    break;
                                    case 21:
                                        sprite->setSprite(20);                
                                    break;
                                    default:
                                        sprite->setSprite(20);
                                    break;                    
                                }
                            reloj.restart();
                            }
                        }else{
                            aturdido = false;
                        }
                }


                switch(movimiento){
                        //Andar 
                        case 0:
                        //Quieto
                        if(!bloque && !aturdido) movimiento = elegirDireccion();
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
                            if(!Mundo::Instance()->getMapa()->colision(coordX,coordY+1)){
                                if(y <= ((coordY+1)*40+100)){
                                    y0 = y1;
                                    y1 = y1 + delta;
                                }else{
                                    coordY++;
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

                            if(!Mundo::Instance()->getMapa()->colision(coordX-1,coordY)){
                                if(x > ((coordX-1)*40+280)){
                                    x0 = x1;
                                    x1 = x1 - delta;  
                                }else{
                                    coordX--;                          
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
                            if(!Mundo::Instance()->getMapa()->colision(coordX,coordY-1)){
                                if(y >= ((coordY-1)*40+100)){

                                    y0 = y1;
                                    y1 = y1 - delta;
                                }else{
                                    coordY--;                             
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
                            if(!Mundo::Instance()->getMapa()->colision(coordX+1,coordY)){
                                if(x <= ((coordX+1)*40+280)){
                                    x0 = x1;
                                    x1 = x1 + delta;  
                                }else{
                                    coordX++;                                         
                                }         
                            }else{
                                movimiento = 0;
                            }
                            break;
                        case 6:
                        //Romper
                            movimiento = direccion;
                            
                            switch(direccion){
                                case 1: //abajo
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
                                    
                                Mundo::Instance()->getMapa()->moverBloque(coordX,coordY+1,-1);
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
                                Mundo::Instance()->getMapa()->moverBloque(coordX-1,coordY,-1);                          
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
                                Mundo::Instance()->getMapa()->moverBloque(coordX,coordY-1,-1);                                                                    
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
                                Mundo::Instance()->getMapa()->moverBloque(coordX+1,coordY,-1);                                                                         
                                break;  
                    }
                break;                        
                    
            }          
                break;
            case 2:
            //Huir
                delta = t * velocidad;

                if(coordX == 0 ||coordX == 12 || coordY == 0 || coordY == 14 )
                    huida = true;

                switch(movimiento){
                        //Andar 
                        case 0:
                        //Quieto
                        if(!bloque) movimiento = elegirDireccion();
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
                            if(!Mundo::Instance()->getMapa()->colision(coordX,coordY+1)){
                                if(y <= ((coordY+1)*40+100)){
                                    y0 = y1;
                                    y1 = y1 + delta;
                                }else{
                                    coordY++;
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

                            if(!Mundo::Instance()->getMapa()->colision(coordX-1,coordY)){
                                if(x > ((coordX-1)*40+280)){
                                    x0 = x1;
                                    x1 = x1 - delta;  
                                }else{
                                    coordX--;                          
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
                            if(!Mundo::Instance()->getMapa()->colision(coordX,coordY-1)){
                                if(y >= ((coordY-1)*40+100)){

                                    y0 = y1;
                                    y1 = y1 - delta;
                                }else{
                                    coordY--;                             
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
                            if(!Mundo::Instance()->getMapa()->colision(coordX+1,coordY)){
                                if(x <= ((coordX+1)*40+280)){
                                    x0 = x1;
                                    x1 = x1 + delta;  
                                }else{
                                    coordX++;                                         
                                }         
                            }else{
                                movimiento = 0;
                            }
                            break;
                        case 6:
                        //Romper
                            movimiento = direccion;
                            
                            switch(direccion){
                                case 1: //abajo
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
                                    
                                Mundo::Instance()->getMapa()->moverBloque(coordX,coordY+1,-1);
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
                                Mundo::Instance()->getMapa()->moverBloque(coordX-1,coordY,-1);                          
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
                                Mundo::Instance()->getMapa()->moverBloque(coordX,coordY-1,-1);                                                                    
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
                                Mundo::Instance()->getMapa()->moverBloque(coordX+1,coordY,-1);                                                                         
                                break;  
                    }
                break;                        
                    
            }          
            break;
            case 3:
            //Muere
                animacionMorir();    
            break;
            case 5:
            //Fase huevo
            if(respawn.getElapsedTime().asSeconds()>2){
                if(reloj.getElapsedTime().asSeconds()>0.25){
                        switch(sprite->getActual()){
                            case 17:
                                Mundo::Instance()->getMapa()->moverBloque(coordX,coordY,-1);                        
                                sprite->setSprite(30);
                                respawn.restart();
                            break;
                            case 30:
                                
                                sprite->setSprite(31);                                   
                            
                            break;
                            case 31:
                                estado = 0; 
                                sprite->setSprite(17);                            
                                
                            break;                                                      
                    }
                    reloj.restart();
                    }           
            }
            break; 
       
        }
    }
    colisionPengo();      
}

void SnowBee::animacionMorir(){
    switch(direccion){
        case 0:
        //Derecha
            if(reloj.getElapsedTime().asSeconds()>0.25){
                switch(sprite->getActual()){
                    case 24:
                        sprite->setSprite(25);
                    break;
                    case 25:
                        vida   = 0;  
                        JuegoStatus::Instance()->addPuntos(100);
                        Mundo::Instance()->removeMalo();
                        respawn.restart();             
                    break;   
                    default:
                        sprite->setSprite(24);                    
                    break;                                                                       
            }
            reloj.restart();
            }    
        break;
        case 1:
        //Izq   
            if(reloj.getElapsedTime().asSeconds()>0.25){
                switch(sprite->getActual()){
                    case 28:
                        sprite->setSprite(29);
                    break;
                    case 29:
                        vida   = 0; 
                        Mundo::Instance()->removeMalo();
                        JuegoStatus::Instance()->addPuntos(100);                        
                        respawn.restart();  
                    break;      
                    default:
                        sprite->setSprite(28);                    
                    break;                                                                    
            }
            reloj.restart();
            }            
        break;
        case 3:
        //Abajo
            if(reloj.getElapsedTime().asSeconds()>0.25){
                switch(sprite->getActual()){
                    case 26:
                        sprite->setSprite(27);
                    break;
                    case 27:
                        vida   = 0;    
                        Mundo::Instance()->removeMalo();
                        JuegoStatus::Instance()->addPuntos(100);                        
                        respawn.restart();  
                    break;   
                    default:
                        sprite->setSprite(26);                    
                    break;                                                                       
            }
            reloj.restart();
            }          

        break;
        case 2:
        //Arriba
            if(reloj.getElapsedTime().asSeconds()>0.25){
                switch(sprite->getActual()){
                    case 22:
                        sprite->setSprite(23);
                    break;
                    case 23:
                        vida   = 0; 
                        Mundo::Instance()->removeMalo();
                        JuegoStatus::Instance()->addPuntos(100);                        
                        respawn.restart();  
                      
                    break;  
                    default:
                        sprite->setSprite(22);                    
                    break;

            }
            reloj.restart();
            }          

        break;      
    }
}

void SnowBee::matar(int d){
    direccion = d;
    estado = 3;
    switch(d){
        case 0:
            sprite->setSprite(24); 
        break;        
        case 1:
            sprite->setSprite(28); 
        break;
        case 2:
            sprite->setSprite(26); 
        break;        
        case 3:
            sprite->setSprite(22); 
        break;

    }

}

void SnowBee::animacionNacer(){
    if(reloj.getElapsedTime().asSeconds()>0.25){
        switch(sprite->getActual()){
            case 17:
                sprite->setSprite(18);
            break;
            case 18:
                sprite->setSprite(19);                
            break;
            case 19:
                sprite->setSprite(20);                
            break;
            case 20:
                sprite->setSprite(21);                
            break;    
            case 21:
                sprite->setSprite(22);                
            break;     
            case 22:
                sprite->setSprite(1);                
                estado = 1;  //En movimiento (ataque)     
                movimiento = 0;                         
            break;                                                                                       
    }
    reloj.restart();
    }
}
void SnowBee::interpolar(float tick){
    x = x0 * (1-tick) + x1 * tick;
    y = y0 * (1-tick) + y1 * tick;
    
    sprite->setPosicion(trunc(x),trunc(y));
}
void SnowBee::render(float t){
    if(vida == 1){ 
        if(movimiento != 0)interpolar(t);
        sprite->pintar();
    }
}

bool SnowBee::comprobarEstrella(int x, int y){
    bool res = false;

    if(Mundo::Instance()->getMapa()->getBloque(coordX,coordY) != NULL && Mundo::Instance()->getMapa()->getBloque(coordX,coordY)->getTipo() == 1)
        res = true;

    return res;
}

int SnowBee::elegirDireccion(){
    int res = 0;
    int xPengo = Pengo::Instance()->getX();
    int yPengo = Pengo::Instance()->getY();

    switch(estado){
        case 1:
        //Ataque
        //Elegimos x o y
        //Primero intentamos ir hacia el pengo
        if(abs(coordY-yPengo) < abs(xPengo-coordX) && coordY != yPengo){
        //y
            if(!lastDireccion != 1 && coordY+1 != coordY0 && coordY < yPengo && coordX >= 0 && coordX < 13 && coordY+1 >= 0 && coordY+1 < 15  && !comprobarEstrella(coordX,coordY+1)){
            //hacia abajo
                if(Mundo::Instance()->getMapa()->colision(coordX,coordY+1) && Mundo::Instance()->getMapa()->colision(coordX,coordY+1)){
                    res = 6;
                    direccion = 1; 
                }else{
                    res = 1; 
                    coordX0 = coordX;
                    coordY0 = coordY + 1;                     
                }           
               
            }else if(!lastDireccion != 3 && coordY-1 != coordY0 && coordY > yPengo && coordX >= 0 && coordX < 13 && coordY-1 >= 0 && coordY-1 < 15 && !comprobarEstrella(coordX,coordY-1)){
            //Hacia arriba
                if(Mundo::Instance()->getMapa()->colision(coordX,coordY-1)){
                    res = 6;
                    direccion = 3; 
                }else{
                    res = 3; 
                    coordX0 = coordX;
                    coordY0 = coordY - 1;                       
                }   

            }else if(coordX >= 0 && coordX < 13 && coordY+1 >= 0 && coordY+1 < 15 && !comprobarEstrella(coordX,coordY+1)){
            //hacia abajo
                if(Mundo::Instance()->getMapa()->colision(coordX,coordY+1)){
                    res = 6;
                    direccion = 1; 
                }else{
                    res = 1; 
                    coordX0 = coordX;
                    coordY0 = coordY + 1;                       
                }    
      
            }else if(coordX >= 0 && coordX < 13 && coordY-1 >= 0 && coordY-1 < 15 && !comprobarEstrella(coordX,coordY-1)){
            //Hacia arriba
                if(Mundo::Instance()->getMapa()->colision(coordX,coordY-1)){
                    res = 6;
                    direccion = 3; 
                }else{
                    res = 3; 
                    coordX0 = coordX;
                    coordY0 = coordY - 1;    
                }   
               
            }
        }else{
        //x
            if(!lastDireccion != 4 && coordX+1 != coordX0 && coordX < xPengo && coordX+1 >= 0 && coordX+1 <13 && coordY >= 0 && coordY < 15 && !comprobarEstrella(coordX+1,coordY)){
            //Hacia la der
                if(Mundo::Instance()->getMapa()->colision(coordX+1,coordY)){
                    res = 6;
                    direccion = 4; 
                }else{
                    res = 4;
                    coordX0 = coordX + 1;
                    coordY0 = coordY;    
                }             
            }else if(!lastDireccion != 4 && coordX-1 != coordX0 && coordX > xPengo && coordX-1 >= 0 && coordX-1 < 13 && coordY >= 0 && coordY < 15 && !comprobarEstrella(coordX-1,coordY)){
            //hacia la izq
                if(Mundo::Instance()->getMapa()->colision(coordX-1,coordY)){
                    res = 6;
                    direccion = 2; 
                }else{
                    res = 2;  
                    coordX0 = coordX - 1;
                    coordY0 = coordY; 
                }                        
            }else if(coordX+1 >= 0 && coordX+1 <13 && coordY >= 0 && coordY < 15 && !comprobarEstrella(coordX+1,coordY)){
            //Hacia la der
                if(Mundo::Instance()->getMapa()->colision(coordX+1,coordY)){
                    res = 6;
                    direccion = 4; 
                }else{
                    res = 4;
                    coordX0 = coordX + 1;
                    coordY0 = coordY;            
                }
                 
            }else if(coordX-1 >= 0 && coordX-1 < 13 && coordY >= 0 && coordY < 15 && !comprobarEstrella(coordX-1,coordY)){
            //hacia la izq
                if(Mundo::Instance()->getMapa()->colision(coordX-1,coordY)){
                    res = 6;
                    direccion = 2; 
                }else{
                    res = 2;
                    coordX0 = coordX - 1;
                    coordY0 = coordY;  
                }  
                         
            }
        }
        break;
        lastDireccion = res;
        case 2:
        //Huida
        //Primer cuadrante
            if(coordX < 6 && coordY < 7){
                //Hacia arriba
                if(coordY < coordX && !comprobarEstrella(coordX,coordY-1)){
                    if(Mundo::Instance()->getMapa()->colision(coordX,coordY-1)){
                        res = 6;
                        direccion = 3; 
                    }else{
                        res = 3; 
                        coordX0 = coordX;
                        coordY0 = coordY - 1;    
                    }                      
                }else if(!comprobarEstrella(coordX-1,coordY)){
                //Hacia izq
                    if(Mundo::Instance()->getMapa()->colision(coordX-1,coordY)){
                        res = 6;
                        direccion = 2; 
                    }else{
                        res = 2;
                        coordX0 = coordX - 1;
                        coordY0 = coordY;  
                    }  
                }

        //Segundo cuadrante
            }else if(coordX > 6 && coordY < 7){
               //Hacia arriba 
                if(coordY < (13 - coordX) && !comprobarEstrella(coordX,coordY-1)){
                    if(Mundo::Instance()->getMapa()->colision(coordX,coordY-1)){
                        res = 6;
                        direccion = 3; 
                    }else{
                        res = 3; 
                        coordX0 = coordX;
                        coordY0 = coordY - 1;    
                    }                      
                }else if(!comprobarEstrella(coordX + 1,coordY)){
                //Hacia la derecha
                    if(Mundo::Instance()->getMapa()->colision(coordX+1,coordY)){
                        res = 6;
                        direccion = 4; 
                    }else{
                        res = 4;
                        coordX0 = coordX + 1;
                        coordY0 = coordY;            
                    }
                }   
        //Tercer cuadrante             
            }else if(coordX > 6 && coordY > 7){

                if((coordY -15) < (13 - coordX) && !comprobarEstrella(coordX,coordY+1)){
               //Hacia abajo 
                    if(Mundo::Instance()->getMapa()->colision(coordX,coordY+1)){
                        res = 6;
                        direccion = 1; 
                    }else{
                        res = 1; 
                        coordX0 = coordX;
                        coordY0 = coordY + 1;                       
                    }                       
               }else if(!comprobarEstrella(coordX+1,coordY)){
                //Hacia la derecha
                    if(Mundo::Instance()->getMapa()->colision(coordX+1,coordY)){
                        res = 6;
                        direccion = 4; 
                    }else{
                        res = 4;
                        coordX0 = coordX + 1;
                        coordY0 = coordY;            
                    }   
                }  
            }else{
                //Cuarto cuadrante
                if((coordY - 15) < coordX && !comprobarEstrella(coordX,coordY+1)){
               //Hacia abajo 
                    if(Mundo::Instance()->getMapa()->colision(coordX,coordY+1)){
                        res = 6;
                        direccion = 1; 
                    }else{
                        res = 1; 
                        coordX0 = coordX;
                        coordY0 = coordY + 1;                       
                    }                       
               }else if(!comprobarEstrella(coordX-1,coordY)){
                //Hacia la izq
                    if(Mundo::Instance()->getMapa()->colision(coordX-1,coordY)){
                        res = 6;
                        direccion = 2; 
                    }else{
                        res = 2;
                        coordX0 = coordX - 1;
                        coordY0 = coordY;  
                    }  
                }  

            }

        break;
    }

    return res;
}





void SnowBee::colisionPengo(){
    if(vida == 1){
       // if(Pengo::Instance()->getSprite()->getSprite().getGlobalBounds().intersects(sprite->getSprite().getGlobalBounds())){
        if(Pengo::Instance()->getX() == coordX && Pengo::Instance()->getY() == coordY){
            if(aturdido){
                matar(Pengo::Instance()->getDireccion());
            }else{
                Pengo::Instance()->quitarVida();
            }
        }
    }
}

void SnowBee::reinicio(){
    coordX0 = coordY0 =  0;
    vida = 1;
    x = x0 = x1 = xInicio*40+280;
    y = y0 = y1 = yInicio*40+100;
    velocidad = 45;
    delta = 0;
    aturdido = false;
    huida = false;
    movimiento = elegirDireccion();
    sprite->setSprite(17);
    estado = 0; 
}