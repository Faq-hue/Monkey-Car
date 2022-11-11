
#include "Coco.h"

Coco::Coco(int x, int y, Texture &tex) {
    this->xc = x;
    this->yc = y;
    spc.setTexture(tex);
}

bool Coco::mover() {
    this->xc += 100;//velocidad del coco
    if (this->xc > 1260)//distancia del coco
        return true;
    else
        return false;
}

void Coco::dibujar(RenderWindow &window) {
    spc.setPosition(this->xc, this->yc);
    window.draw(spc);
}

Rect<float> Coco::getBound() {
    return spc.getGlobalBounds();
}