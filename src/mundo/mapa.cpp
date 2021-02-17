#include "../../include/mundo/mapa.h"
#include "../../include/mundo/mundo.h"
#include "../../include/entidades/pengo.h"
#include "../../include/fachada/motorGrafico.h"


Mapa::Mapa(int n){
    bloquesTotal = 0;
    estado = 0;
    TiXmlDocument doc;
    switch(n){
        case 0:
            doc.LoadFile("resources/mapas/map1.tmx");
        break;
        case 1:
            doc.LoadFile("resources/mapas/map2.tmx");
        break;
        case 2:
            doc.LoadFile("resources/mapas/map3.tmx");
        break;
        case 3:
            doc.LoadFile("resources/mapas/map4.tmx");
        break;
        case 4:
            doc.LoadFile("resources/mapas/map5.tmx");
        break;
        default:
            doc.LoadFile("resources/mapas/mapa1.tmx");
        break;
    }

   TiXmlElement* map = doc.FirstChildElement("map");
    if(map != NULL){
            map->QueryIntAttribute("width",&alto);
            map->QueryIntAttribute("height",&ancho);
            map->QueryIntAttribute("tilewidth",&tileAncho);     
            map->QueryIntAttribute("tileheight",&tileAlto);                
    }

    numCapas = 1;
    tilemap = new int**[numCapas];
   for (int i = 0; i < numCapas; i++){
       tilemap[0] = new int*[alto];
    }

    for(unsigned c=0; c<numCapas; c++){
        for(unsigned j = 0; j < alto; j++){
            tilemap[c][j] = new int[ancho];
        }
    }

    tilemapBloques = new Bloque***[numCapas]; 

    for (unsigned i = 0; i < numCapas; i++){
       tilemapBloques[i] = new Bloque**[alto];
    }

    for(unsigned c=0; c<numCapas; c++){
        for(unsigned j = 0; j < alto; j++){
            tilemapBloques[c][j] = new Bloque*[ancho];
            for(unsigned k = 0; k < ancho; k++){
                tilemapBloques[c][j][k] = new Bloque();
            }
        }
    }
    TiXmlElement *data[1];
    data[0] = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");

    for(unsigned c = 0; c < numCapas; c++){
        for(unsigned y = 0; y < alto; y++){
            for(unsigned k = 0; k < ancho; k++){
                data[c]->QueryIntAttribute("gid",&tilemap[c][y][k]);
                data[c] = data[c]->NextSiblingElement("tile");
            }
        }
    }



    for(unsigned c = 0; c < numCapas; c++){
        for(unsigned y = 0; y < alto; y++){
            for(unsigned k = 0; k < ancho; k++){
                int gid = tilemap[c][y][k];
                if(gid == 2){//Bloque de hielo
                    tilemapBloques[c][y][k] = new Bloque(0,y,k);
                    bloquesTotal++;
                }else if(gid == 3){//Bloque estrella
                   tilemapBloques[c][y][k] = new Bloque(1,y,k);
                }else{//Nada
                    tilemapBloques[c][y][k] = NULL;
                }
            }
        }
    }

    //Creamos los bordes
    bordeArr = new Sprite("resources/barraArr.png",{0,0},{0,1},600,40, 520,60);
    bordeAbj = new Sprite("resources/barraBajo.png",{0,0},{0,1},600,40, 520,700);
    bordeIzq = new Sprite("resources/barraIzq.png",{0,1},{0,0},40,600, 240,380);
    bordeDer = new Sprite("resources/barraDer.png",{0,1},{0,0},40,600, 800,380);
}

Mapa::~Mapa(){

    for(unsigned c=0; c<numCapas; c++){
        for(unsigned j = 0; j < alto; j++){
            delete[] tilemap[c][j];
        }
        delete[] tilemap[c];    
    }
    
    delete[] tilemap;    

    for(unsigned c=0; c<numCapas; c++){
     for(unsigned j = 0; j < alto; j++){
        for(unsigned k = 0; j < ancho; k++){
            delete[] tilemapBloques[c][j][k];
        }
        delete[] tilemapBloques[c][j];
     }
     delete[] tilemapBloques[c];    
    }
    
    delete[] tilemap;    
}

void Mapa::render(float time){
    switch(estado){
        case 0:
        //llenamos la pantalla

            for(unsigned i = 0; i < alto; i++){
                for(unsigned j = 0; j < ancho; j++){
                    if(tilemapBloques[0][i][j] != NULL){
                        Sprite* sp = new Sprite("resources/bloqueHielo2.png",{0,1},{0,0},40,40, 40*i+280,40*j+100); 
                        sp->pintar();                 
                    }else{
                        Sprite* sp = new Sprite("resources/bloqueHielo2.png",{0,1},{0,0},40,40, 40*i+280,40*j+100);
                        camino.push_back(sp);
                        sp->pintar();
                    }  
                }
            } 
            bordeDer->pintar();
            bordeIzq->pintar();
            bordeArr->pintar();
            bordeAbj->pintar();
            MotorGrafico::Instance()->pintarVentana(); 
            delay.restart();
            cont = 0;
            while(cont<camino.size()-1){
                if(delay.getElapsedTime().asSeconds()>0.02){
                    cont++;
                    delay.restart();
                    bool snowbee = false;

                    for(SnowBee* bee: Mundo::Instance()->getMalos()){
                        if(camino[cont] != NULL && bee->getSprite()->getSprite().getGlobalBounds().intersects(camino[cont]->getSprite().getGlobalBounds())){
                            snowbee = true;
                        }
                    }

                    if(camino[cont] != NULL && !snowbee)camino[cont]->setSprite(1);                    
                }
                for(Sprite* sp: camino)
                sp->pintar();
    
                MotorGrafico::Instance()->pintarVentana();          
            } 
        estado = 1;    
        break;
            
                        
        break;
        case 1:
            for(unsigned i = 0; i < alto; i++){
                for(unsigned j = 0; j < ancho; j++){
                    if(tilemapBloques[0][i][j] != NULL)
                        tilemapBloques[0][i][j]->render(time);
                }
            }
            bordeDer->pintar();
            bordeIzq->pintar();
            bordeArr->pintar();
            bordeAbj->pintar();
        break;
    }

}

void Mapa::comprobarBorde(int x, int y){
    if(y < 0){
    //Animar borde arriba
        borde = 1;
    }else if(y > ancho-1){
    //Animar borde bajo
        borde = 2;
    }else if(x < 0){
    //Animar borde izq
        borde = 3;
    }else if(x > alto-1){
    //Animar borde der
        borde = 4;
    }else{
        borde = 0; //Default para los bordes
    }

    if(borde != 0) Mundo::Instance()->aturdirSnowbees(x,y);
}



bool Mapa::colision(int x, int y){
    bool res = true;

    //Comprobar colision
    if(y >= 0 && y < ancho && x >= 0 && x < alto && tilemapBloques[0][x][y] == NULL)
        res = false;       
    

    return res;
}

void Mapa::update(float t){

    for(unsigned i = 0; i < alto; i++){
        for(unsigned j = 0; j < ancho; j++){     
            if(tilemapBloques[0][i][j] != NULL){
                    tilemapBloques[0][i][j]->update(t);
            }
        }
    }
    switch(borde){
        case 0:
            bordeArr->setSprite(0);
            bordeAbj->setSprite(0);
            bordeDer->setSprite(0);
            bordeIzq->setSprite(0);                                    
            break;
        case 1:
            Mundo::Instance()->aturdirSnowbees(0,-1);
            if(reloj.getElapsedTime().asSeconds()>0.25){
                switch(bordeArr->getActual()){
                    case 0:
                        bordeArr->setSprite(1);
                    break;
                    case 1:
                        bordeArr->setSprite(0);                
                    break;
                    default:
                        bordeArr->setSprite(0);
                    break;                    
                }
            reloj.restart();
            }
            if(tiempo.getElapsedTime().asSeconds()>5){
                borde = 0;
                tiempo.restart();
            }         
        break;
        case 2:
            Mundo::Instance()->aturdirSnowbees(0,15);
            if(reloj.getElapsedTime().asSeconds()>0.25){
                switch(bordeAbj->getActual()){
                    case 0:
                        bordeAbj->setSprite(1);
                    break;
                    case 1:
                        bordeAbj->setSprite(0);                
                    break;
                    default:
                        bordeAbj->setSprite(0);
                    break;                    
                }
            reloj.restart();
            }
            if(tiempo.getElapsedTime().asSeconds()>5){
                borde = 0;
                tiempo.restart();
            }                          
        break;   
        case 3:
            Mundo::Instance()->aturdirSnowbees(-1,0);        
            if(reloj.getElapsedTime().asSeconds()>0.25){
                switch(bordeIzq->getActual()){
                    case 0:
                        bordeIzq->setSprite(1);
                    break;
                    case 1:
                        bordeIzq->setSprite(0);                
                    break;
                    default:
                        bordeIzq->setSprite(0);
                    break;                    
                }
            reloj.restart();
            }
            if(tiempo.getElapsedTime().asSeconds()>5){
                borde = 0;
                tiempo.restart();
            }                          
        break;
        case 4:
            Mundo::Instance()->aturdirSnowbees(13,0);    
            if(reloj.getElapsedTime().asSeconds()>0.25){
                switch(bordeDer->getActual()){
                    case 0:
                        bordeDer->setSprite(1);
                    break;
                    case 1:
                        bordeDer->setSprite(0);                
                    break;
                    default:
                        bordeDer->setSprite(0);
                    break;                    
                }
            reloj.restart();
            }
            if(tiempo.getElapsedTime().asSeconds()>5){
                borde = 0;
                tiempo.restart();
            }                          
        break;              
    }
}

void Mapa::moverBloque(int x, int y, int direccion){
    if(x >= 0 && x <= alto-1 && y >= 0 && y < ancho && tilemapBloques[0][x][y] != NULL){
            Bloque* bloque = tilemapBloques[0][x][y];

            switch(direccion){
                case 1: //Abajo
                    if(y < ancho && tilemapBloques[0][x][y+1] == NULL) y++;
                        while((tilemapBloques[0][x][y] == NULL)){
                            tilemapBloques[0][x][y] = bloque;
                            tilemapBloques[0][x][y-1] = NULL;
                            
                            if(y < ancho-1 && tilemapBloques[0][x][y+1] == NULL) y++;
                        }
                break;

                case 2: //Izq
                    if(x > 0 && tilemapBloques[0][x-1][y] == NULL) x--;
                        while(tilemapBloques[0][x][y] == NULL){
                            tilemapBloques[0][x][y] = bloque;
                            tilemapBloques[0][x+1][y] = NULL;

                            if(x > 0 && tilemapBloques[0][x-1][y] == NULL) x--;
                        }
                break;      
                case 3: //Arr
                    if(y > 0 && tilemapBloques[0][x][y-1] == NULL) y--;
                        while(tilemapBloques[0][x][y] == NULL){
                            tilemapBloques[0][x][y] = bloque;
                            tilemapBloques[0][x][y+1] = NULL;

                            if(y > 0 && tilemapBloques[0][x][y-1] == NULL) y--;
                        }
                break;    
                case 4: //Der
                    if(x < alto-1 && tilemapBloques[0][x+1][y] == NULL) x++;
                        while((tilemapBloques[0][x][y] == NULL)){
                            tilemapBloques[0][x][y] = bloque;
                            tilemapBloques[0][x-1][y] = NULL;

                            if(x < alto-1 && tilemapBloques[0][x+1][y] == NULL) x++;
                        }
                    
                break;                                               
            }
            //animacion romper bloque
            tilemapBloques[0][x][y]->romper(x,y); 
            bloquesTotal--;
        }else if(direccion != -1){
            comprobarBorde(x,y);
        }
    }

void Mapa::buscarBloque(){
    srand(0);
    bool salir = false;
    int fil = rand()%15;
    int col = rand()%13;
    while(!salir){
        if(getBloque(col,fil) != NULL && getBloque(col,fil)->getTipo() == 0 && !getBloque(col,fil)->getBee()){
            getBloque(col,fil)->setSnowbee();
            salir = true;
        }
        fil = rand()%15;
        col = rand()%13;       
    }
}

int Mapa::comprobarEstrella(int x, int y){
    int cont = 0;

    if(x < alto-1 && tilemapBloques[0][x+1][y]!= NULL && tilemapBloques[0][x+1][y]->getTipo() == 1){
        cont++;
    } 
    if(x > 0 && tilemapBloques[0][x-1][y]!= NULL && tilemapBloques[0][x-1][y]->getTipo() == 1){
        cont++;
    } 
    if(y < ancho-1 && tilemapBloques[0][x][y+1]!= NULL && tilemapBloques[0][x][y+1]->getTipo() == 1){
        cont++;
    } 
    if(y > 0 && tilemapBloques[0][x][y-1]!= NULL && tilemapBloques[0][x][y-1]->getTipo() == 1){
        cont++;
    } 
    if(x > 0 && y < ancho-1 && tilemapBloques[0][x-1][y+1]!= NULL && tilemapBloques[0][x-1][y+1]->getTipo() == 1){
        cont++;
    }  
    if(x < alto-1 && y > 0 && tilemapBloques[0][x+1][y-1]!= NULL && tilemapBloques[0][x+1][y-1]->getTipo() == 1){
        cont++;
    }   
    if(x > 0 && y > 0 && tilemapBloques[0][x-1][y-1]!= NULL &&  tilemapBloques[0][x-1][y-1]->getTipo() == 1){
        cont++;
    }  
    if(x < alto-1 && y < ancho-1 && tilemapBloques[0][x+1][y+1]!= NULL && tilemapBloques[0][x+1][y+1]->getTipo() == 1){
        cont++;
    } 

    return cont;
}

void Mapa::buscarSnowBee(){
    srand(0);
    bool salir = false;

    for(unsigned i = 0; i < alto && !salir; i++){
        for(unsigned j = 0; j < ancho && !salir; j++){     
            if(tilemapBloques[0][i][j] != NULL && tilemapBloques[0][i][j]->getBee()){
                    tilemapBloques[0][i][j]->removeSnowbee();
                    Mundo::Instance()->addenemigo(new SnowBee(i,j));
                    salir = true;
            }
        }
    }
}

void Mapa::borrarBloque(int x,int y){
    bloquesTotal--;
    if(tilemapBloques[0][x][y] != NULL && tilemapBloques[0][x][y]->getBee()){
        tilemapBloques[0][x][y]->removeSnowbee();
        Mundo::Instance()->removeMalo();
    }
    tilemapBloques[0][x][y] = NULL;
}