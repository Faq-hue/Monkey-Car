#include <iostream>
#include "Puntuacion.h"
#include <fstream>

Puntuacion::Puntuacion() {

    if (!font.loadFromFile("stocky.ttf")){
        std::cout<<"Error en la fuente"<<std::endl;
    }

    puntuacion.setFont(font);
    puntuacion.setFillColor(sf::Color::White);
    puntuacion.setString("0");
    puntuacion.setPosition(1050,50);
    puntuacion.setCharacterSize(70);

    hi_puntuacion.setFont(font);
    hi_puntuacion.setFillColor(sf::Color::Yellow);
    hi_puntuacion.setString("Hi:");
    hi_puntuacion.setPosition(50,50);
    hi_puntuacion.setCharacterSize(70);

}

void Puntuacion::draw(sf::RenderWindow &window) {
    window.draw(puntuacion);
    window.draw(hi_puntuacion);
}

Puntuacion::~Puntuacion() {

}

void Puntuacion::incremento(int score) {

    puntuacion.setString(std::to_string(score));
    hi_puntuacion.setString(prev_score());


}

void Puntuacion::savescore(int score) {
    std::ofstream archive;
    std::ifstream read;
    std::string note=" ",comp=std::to_string(score);


    archive.open("Prevscores.txt");

    if(!archive.is_open()){
       std::cout<<"Error en Prevscores.txt"<<std::endl;
    }

    read.open("Prevscores.txt");

    if(!read.is_open()){
        std::cout<<"Error en Prevscores.txt"<<std::endl;
    }



    while (!read.eof()){
        std::getline(read,note);

            archive<<"PrevScore: "<<comp<<std::endl;



    }

    archive.close();
    read.close();
}

std::string Puntuacion::prev_score() {
    std::ifstream read;
    std::string hi="algo";

    read.open("Prevscores.txt");

    if(!read.is_open()){
        std::cout<<"Error en Prevscores.txt"<<std::endl;
    }

    while (!read.eof()){
        std::getline(read,hi);

        return hi;
    }

    read.close();

    return hi;
}

