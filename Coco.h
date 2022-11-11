#include <SFML/Graphics.hpp>

using namespace sf;

#ifndef CODIGO_COCO_H
#define CODIGO_COCO_H


class Coco {
private:
    int xc;
    int yc;
    Sprite spc;
public:
    Coco(int x, int y, Texture &tex);
    bool mover();
    void dibujar(RenderWindow &window);
    Rect<float> getBound();
};


#endif //CODIGO_COCO_H
