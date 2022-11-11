#include <SFML/Graphics.hpp>
#include "Coco.h"

using namespace sf;
#ifndef CODIGO_PIEDRA_H
#define CODIGO_PIEDRA_H


class Piedra {
private:
    int anim_actualp;
    Sprite spp;

public:
    Piedra(float xp_inicial, float yp_inicial, Texture &tex);
    void dibujar(RenderWindow &window);
    int getX(){return spp.getPosition().x;};
    void setX(int x){
        spp.setPosition(x,getY());
    }
    int getY(){return spp.getPosition().y;};
    Rect<float> getBound();
    bool colision_coco(Coco *coco);
};


#endif //CODIGO_PIEDRA_H
