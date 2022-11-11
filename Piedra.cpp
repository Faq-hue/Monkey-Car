#include "Piedra.h"

void Piedra::dibujar(RenderWindow &window) {

    spp.setPosition(spp.getPosition().x-5,spp.getPosition().y);

    spp.setTextureRect({anim_actualp * 140, 0, 140, 184});

    window.draw(spp);
}

Piedra::Piedra(float x_inicial, float y_inicial, Texture &tex) {
    anim_actualp = 0;

    spp.setPosition(x_inicial,y_inicial);

    spp.setTexture(tex);
}

Rect<float> Piedra::getBound() {
    return spp.getGlobalBounds();
}

bool Piedra::colision_coco(Coco *coco) {

    Rect<float> rect_piedra = spp.getGlobalBounds();

    Rect<float> rect_coco = coco->getBound();

    return rect_piedra.intersects(rect_coco);
}