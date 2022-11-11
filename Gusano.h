#include <SFML/Graphics.hpp>

using namespace sf;
#ifndef CODIGO_GUSANO_H
#define CODIGO_GUSANO_H

class Gusano {
private:

    int anim_actualg;
    Sprite spg;
    int delay=0;

public:
    Gusano(float xp_inicial, float yp_inicial, Texture &tex);
    void dibujar(RenderWindow &window);
    int getX(){return spg.getPosition().x;};
    void setX(int x){
        spg.setPosition(x,getY());
    }

    int getY(){return spg.getPosition().y;};
    Rect<float> getBound();
};


#endif //CODIGO_GUSANO_H
