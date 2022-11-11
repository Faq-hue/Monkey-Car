#include <SFML/Graphics.hpp>
#include "Gusano.h"
#include "Piedra.h"

using namespace sf;
#ifndef CODIGO_MONO_H
#define CODIGO_MONO_H


class Mono {
private:
    int x;
    int y;
    int vel_y;
    int animacion;
    Sprite sp;
    int delay=0;

public:

    Mono(int x_inicial, int y_inicial, Texture &tex);
    Mono(){}
    void init(int x_inicial, int y_inicial, Texture &tex);
    void mover(int x, int y);
    void dibujar(RenderWindow &window);
    int getX(){return x;};
    int getY(){return y;};
    bool colision_gus(Gusano &gus);
    bool colision_pie(Piedra &pie);
};


#endif //CODIGO_MONO_H
