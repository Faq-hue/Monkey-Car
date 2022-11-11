
#include "Gusano.h"

void Gusano::dibujar(RenderWindow &window) {

    //delay para la animacion
    delay++;

    if (delay >= 4){
        delay = 0;
        anim_actualg++;
        anim_actualg = anim_actualg % 4;
    }

    spg.setPosition(spg.getPosition().x-5,spg.getPosition().y);

    spg.setTextureRect({anim_actualg * 173, 0, 173, 80});

    window.draw(spg);
}

Gusano::Gusano(float x_inicial, float y_inicial, Texture &tex) {
    anim_actualg = 0;

    spg.setPosition(x_inicial,y_inicial);

    spg.setTexture(tex);
}

Rect<float> Gusano::getBound() {
    return spg.getGlobalBounds();
}
