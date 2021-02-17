#include "../../include/fachada/sprite.h"

Sprite::Sprite(){}

Sprite::Sprite(string imagenTex,vector<int> col,vector<int> row,int w,int h, float px, float py){
    sf::Texture* tex = new sf::Texture();

    if (!tex->loadFromFile(imagenTex)) {
        exit(0);
    }

  for(unsigned i = 0; i < row.size(); i++){
    textura = tex;
    sf::Sprite sp;
    sp.setTexture(*tex);
    sp.setOrigin(w/2,h/2);
    x = px;
    y = py;
    sp.setTextureRect(sf::IntRect(col[i] * w, row[i] * h, w,h));
    sp.setPosition(x,y);

    actual = 0;
        
    sprites.push_back(sp);
  }
}

Sprite::~Sprite(){
  delete textura;
  textura = NULL;

}

void Sprite::pintar(){
  MotorGrafico::Instance()->pintarSprite(sprites[actual]);
}

void Sprite::setPosicion(float px, float py){
  x = px;
  y = py;
  for(int i = 0; i<sprites.size(); i++){
    sprites[i].setPosition(x,y);
  }
}

