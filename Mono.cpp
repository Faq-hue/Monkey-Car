
#include "Mono.h"

void Mono::mover(int x, int y) {
    this->x += x;
    this->y += y;

    if (this->x < 0)
        this->x = 0;
    if(this->x > 1014)
        this->x =1014;
    if (this->x > 1280 - sp.getTexture()->getSize().x)
        this->x = 1280 - sp.getTexture()->getSize().x;
    if (this->y < 0)
        this->y = 0;
    if (this->y > 800 - sp.getTexture()->getSize().y)
        this->y = 800 - sp.getTexture()->getSize().y;


}

void Mono::dibujar(RenderWindow &window) {
    sp.setPosition(this->x, this->y);
    //Delay para la animacion

    delay++;
    if (delay >= 6){
        delay = 0;
        animacion ++;
        animacion = animacion % 2;
    }

    window.draw(sp);

    sp.setTextureRect({animacion * 281, 0, 281, 145});


    //Gravedad
    float grav= 1;

    vel_y= vel_y + grav;
    y= y + vel_y + grav /2;

    if(y > 530){
        y = 530;
        vel_y = 0;
    }

}

Mono::Mono(int x_inicial, int y_inicial, Texture &tex) {
    x = x_inicial;
    y = y_inicial;
    vel_y = 0;
    sp.setTexture(tex);
}

void  Mono::init(int x_inicial, int y_inicial, Texture &tex) {
    x = x_inicial;
    y = y_inicial;
    vel_y = 0;
    sp.setTexture(tex);
}

bool Mono::colision_gus(Gusano &gus) {

    Rect<float> rect_mono = sp.getGlobalBounds();

    Rect<float> rect_gusano = gus.getBound();

    return rect_mono.intersects(rect_gusano);
}

bool Mono::colision_pie(Piedra &pie) {

    Rect<float> rect_mono = sp.getGlobalBounds();

    Rect<float> rect_pie = pie.getBound();

    return rect_mono.intersects(rect_pie);
}
