#include "../../include/mundo/mundo.h"
#include "../../include/estados/juegoStatus.h"

Mundo* Mundo::mundo = 0;

Mundo* Mundo::Instance(){
if(mundo == 0){
    mundo = new Mundo();
}
return mundo;
}

Mundo::Mundo(){
    srand(time(0));
    idMapa = rand()%5;
    mapa = new Mapa(idMapa);
    mapasJugados.push_back(idMapa);
    nEnemigos = 0;
    bloque = false;
    estado = 0;
    srand(0);
    //Cargamos los 4 primeros enemigos
    int fil = rand()%15;
    int col = rand()%13;
    while(nEnemigos < 4){
        if(mapa->getBloque(col,fil) == NULL){
            //Si esa posicion del mapa esta vacía, creamos un enemigo
            SnowBee* bee = new SnowBee(col,fil);
            bee->setEstado(0);
            enemigos.push_back(bee);
            nEnemigos++;
        }
        fil = rand()%15;
        col = rand()%13;       
    }
    srand(time(0));
    n = (rand()%4)+1;
    int aux = n;
    nEnemigos = nEnemigos + n;

    //Bloques que tendran snowbees
    while(aux>0){
        mapa->buscarBloque();
        aux--;
    }
}

void Mundo::render(float time){
    if(mapa->getEstado() != 0){
        for(SnowBee* bee : enemigos)
            bee->render(time);
    }
    mapa->render(time);
}

void Mundo::update(float time){
    mapa->update(time);
    if(nEnemigos <= 0){
        JuegoStatus::Instance()->setEstado(3);
    }else{
        for(SnowBee* bee : enemigos){
            bee->update(time);    
        }

    }
}

void Mundo::reinicio(){
    mapa = NULL;
    mapa = new Mapa(idMapa);
    bloque = false;
    estado = 0;

    enemigos.clear();
    srand(0);
    //Cargamos los 4 primeros enemigos
    int fil = rand()%15;
    int col = rand()%13;
    nEnemigos = 0;
    while(nEnemigos < 4){
        if(mapa->getBloque(col,fil) == NULL){
            //Si esa posicion del mapa esta vacía, creamos un enemigo
            SnowBee* bee = new SnowBee(col,fil);
            bee->setEstado(0);
            enemigos.push_back(bee);
            nEnemigos++;
        }
        fil = rand()%15;
        col = rand()%13;       
    }

    //Bloques que tendran snowbees
    int aux = n;
    nEnemigos = nEnemigos + n;

    //Bloques que tendran snowbees
    while(aux>0){
        mapa->buscarBloque();
        aux--;
    } 
}

void Mundo::siguiente(){
    srand(time(0));
    int next = rand()%5;
 
    bool salir = false;
    while(mapasJugados.size()<5 && !salir){
        next = rand()%5;
        salir = true;

        for(int i : mapasJugados){
            if(i == next)
                salir = false;
        }
    }
    idMapa = next;
    mapa = new Mapa(idMapa);
    bloque = false;
    estado = 0;
    enemigos.clear();
    srand(0);
    //Cargamos los 4 primeros enemigos
    int fil = rand()%15;
    int col = rand()%13;
    nEnemigos = 0;
    while(nEnemigos < 4){
        if(mapa->getBloque(col,fil) == NULL){
            //Si esa posicion del mapa esta vacía, creamos un enemigo
            SnowBee* bee = new SnowBee(col,fil);
            bee->setEstado(0);
            enemigos.push_back(bee);
            nEnemigos++;
        }
        fil = rand()%15;
        col = rand()%13;       
    }
    srand(time(0));
    int aux = n;
    nEnemigos = nEnemigos + n;

    //Bloques que tendran snowbees
    while(aux>0){
        mapa->buscarBloque();
        aux--;
    }
}

void Mundo::aturdirSnowbees(){
     for(SnowBee* bee : enemigos)
       if(bee->getEstado()==1) bee->aturdir();       
}

void Mundo::mostrarSnowbees(){
    for(int i = 0; i < 13; i++){
        for(int j = 0; j< 15; j++){
            if(mapa->getBloque(i,j) != NULL && mapa->getBloque(i,j)->getBee())
                mapa->getBloque(i,j)->getSprite()->setSprite(9);
        }
    }
}

void Mundo::aturdirSnowbees(int x, int y){
    if(y < 0){
    //Animar borde arriba
        for(SnowBee* bee : enemigos)
        if(bee->getCoords()[1] == y+1 ) bee->aturdir();   

    }else if(y > 14){
    //Animar borde bajo
        for(SnowBee* bee : enemigos)
        if(bee->getCoords()[1] == y-1 ) bee->aturdir();   

    }else if(x < 0){
    //Animar borde izq
        for(SnowBee* bee : enemigos)
        if(bee->getCoords()[0] == x+1) bee->aturdir();   

    }else if(x > 12){
    //Animar borde der
        for(SnowBee* bee : enemigos)
        if(bee->getCoords()[0] == x-1) bee->aturdir();   
    }
  
}

bool Mundo::getHuida(){
    int cont = 0;
    bool res = false;
    for(SnowBee* bee : enemigos)
       if(bee->getHuida() == true )cont++;   

    if(cont >= nEnemigos)
        res = true;

    return res;
}


void Mundo::setHuida(){
    for(SnowBee* bee : enemigos)
       bee->setEstado(2);
}