
#include <SFML/Graphics.hpp>
#include <string>

#ifndef CODIGO_PUNTUACION_H
#define CODIGO_PUNTUACION_H


class Puntuacion {
private:
    sf::Font font;
    sf::Text puntuacion;

    sf::Text hi_puntuacion;

public:
    Puntuacion();

    ~Puntuacion();

    void draw(sf::RenderWindow &window);

    void incremento(int score);

    void savescore(int);

    std::string prev_score();

};


#endif //CODIGO_PUNTUACION_H
