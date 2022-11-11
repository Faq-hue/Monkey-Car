#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Mono.h"
#include "Gusano.h"
#include "Piedra.h"
#include "Coco.h"
#include "Puntuacion.h"
#include "LinkedList.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <ctime>

using namespace sf;

enum estados{
    MENU,
    JUEGO,
    GAMEOVER
};


class Menu{
private:
    //texturas y sprites
    Texture tex_logo;
    Sprite sp_logo;
    Texture tex_play;
    Sprite sp_play;

    //sonidos
    SoundBuffer sb_inicio; //tiene el archivo de sonido
    Sound snd_inicio; // sonido va cargar en buffer


public:

    Menu(){
        if (!tex_logo.loadFromFile("logo.png")) {
            std::cout << "No se puedo cargar logo.png, verifique el WorkinDir" << std::endl;
            exit(EXIT_FAILURE) ;
        }
        if (!tex_play.loadFromFile("play.png")) {
            std::cout << "No se puedo cargar play.png, verifique el WorkinDir" << std::endl;
            exit(EXIT_FAILURE) ;
        }
        sp_logo.setTexture(tex_logo);
        sp_logo.setPosition(340,0);
        sp_play.setTexture(tex_play);
        sp_play.setPosition(430,500);

        //sonido
        if(!sb_inicio.loadFromFile("sonido.wav")){
            std::cout <<"No se pudo cargar el arc. sonido"<< std::endl;
        }
        snd_inicio.setBuffer(sb_inicio);

        snd_inicio.play();
    }

    estados eventos(Window &w){

        Rect<float>boton = sp_play.getGlobalBounds();

        Vector2<int>puntero = Mouse::getPosition(w);

        if (Mouse::isButtonPressed(sf::Mouse::Left)){
            if (boton.contains(puntero.x,puntero.y)){



                return JUEGO;
            }
        }

        return MENU;
    }

    void dibujar(RenderWindow &window){
        window.draw(sp_logo);
        window.draw(sp_play);
    }
};

class Juego{

    Texture tex_mono;
    Texture tex_gusano;
    Texture tex_piedra;
    Texture tex_coco;

    int x_juego=0;

    std::list <Gusano*> l_gus;
    std::list <Piedra*> l_pie;
    LinkedList <Coco*> l_coco;

    std::queue <Gusano*> c_gus;
    std::queue <Piedra*> c_pie;

    Mono mono;

    //sonido del motor
    SoundBuffer sb_inicio; //tiene el archivo de sonido
    Sound snd_inicio; // sonido va cargar en buffer

public:
    Juego(){

        if (!tex_mono.loadFromFile("mono.png")) {
            std::cout << "No se puedo cargar mono.png, verifique el WorkinDir" << std::endl;
           exit(EXIT_FAILURE) ;
        }
        if (!tex_gusano.loadFromFile("gusano.png")) {
            std::cout << "No se puedo cargar gusano.png, verifique el WorkinDir" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (!tex_piedra.loadFromFile("piedra.png")) {
            std::cout << "No se puedo cargar piedra.png, verifique el WorkinDir" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (!tex_coco.loadFromFile("coco.png")) {
            std::cout << "No se puedo cargar coco.png, verifique el WorkinDir" << std::endl;
            exit(EXIT_FAILURE);
        }


        c_gus.push(new Gusano (2000,600,tex_gusano));
        c_gus.push(new Gusano (3000,600,tex_gusano));

        c_pie.push(new Piedra (1000,500,tex_piedra));
        c_pie.push(new Piedra (4000,500,tex_piedra));

        mono.init(100, 530, tex_mono);

        //sonido del motor
        if(!sb_inicio.loadFromFile("motor.wav")){
            std::cout <<"No se pudo cargar el arc. sonido"<< std::endl;
        }
        snd_inicio.setBuffer(sb_inicio);

        snd_inicio.play();
        snd_inicio.setLoop(true);//funcion de repeticion de sonido
        snd_inicio.setVolume(20);//funcion de subir y bajar el volumen

    }

    estados eventos(int &k, Puntuacion &punt, int &score){
        srand(time(NULL));

        //Controles

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            mono.mover(-7, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            mono.mover(7, 0);
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            mono.mover(0, -25);
        }

        if(k%10==0) {
            if (Keyboard::isKeyPressed(Keyboard::Space)) { // Disparo y creo un nuevo proyectil
                l_coco.push_front(new Coco(mono.getX() + 130, mono.getY() + 45, tex_coco));
            }

            for (int i = 0; i < l_coco.size(); ++i) {
                if (l_coco.get(i)->mover()) {
                    l_coco.erase(i);
                }
            }
        }

        //puntuacion
        punt.incremento(score);

        score++;

        x_juego+=5;

        //Colisiones
        for (auto g: l_gus){

            if (mono.colision_gus(*g)) {

                snd_inicio.stop();

                return GAMEOVER;
            }

            if(g->getX() < 0){

                g->setX(x_juego+(2000+rand()%3000)); //puede ser un random entre 2000 y 3000

                c_gus.push(g);
            }

        }

        for (auto p: l_pie){

            if (mono.colision_pie(*p)) {

                return GAMEOVER;
            }

        }

        std:: stack<int>toDelete;
        for (int i = 0; i < l_coco.size(); ++i) {

            for (auto p=l_pie.begin();p!=l_pie.end();){

                if ((*p)->colision_coco(l_coco.get(i))){
                    toDelete.push(i);

                    (*p)->setX(x_juego+(2000+rand()%3000)); //puede ser un random entre 2000 y 3000

                    c_pie.push(*p);

                    p=l_pie.erase(p);
                } else{
                    p++;
                }


            }


        }

        while (!toDelete.empty()){
            l_coco.erase(toDelete.top());
            toDelete.pop();
        }

        if(!c_gus.empty() && c_gus.front()->getX() <= x_juego){

            Gusano *punt = c_gus.front();

            c_gus.pop();

            punt->setX(1280);

            l_gus.push_front(punt);


        }
                                                                                                                                                                                                                                                             

        if(!c_pie.empty() && c_pie.front()->getX() <= x_juego){

            Piedra *punt = c_pie.front();

            c_pie.pop();

            punt->setX(1280);

            l_pie.push_front(punt);


        }

        return JUEGO;
    }

    void dibujar(RenderWindow &window, Puntuacion &punt, int &score){

        for (auto &g: l_gus) {
            g->dibujar(window);

        }

        for (auto &p: l_pie) {
            p->dibujar(window);

        }

        for (l_coco.loopStart(); !l_coco.loopEnd(); l_coco.loopNext()) {
            l_coco.loopGet()->dibujar(window);
        }

        punt.draw(window);
        mono.dibujar(window);

    }

};

class Gameover{
private:
    Texture tex_over;
    Sprite sp_over;
    Texture tex_score1;
    Sprite sp_score1;

public:

    Gameover(){
        if (!tex_over.loadFromFile("over.png")) {
            std::cout << "No se puedo cargar over.png, verifique el WorkinDir" << std::endl;
            exit(EXIT_FAILURE) ;
        }
        if (!tex_score1.loadFromFile("score1.png")) {
            std::cout << "No se puedo cargar score1.png, verifique el WorkinDir" << std::endl;
            exit(EXIT_FAILURE) ;
        }
        sp_over.setTexture(tex_over);
        sp_over.setPosition(380,250);
        sp_score1.setTexture(tex_score1);
        sp_score1.setPosition(750,20);
    }

    estados eventos(){

        Rect<float>boton = sp_score1.getGlobalBounds();

        Vector2<int>puntero = Mouse::getPosition();

        if (Mouse::isButtonPressed(sf::Mouse::Left)){
            if (boton.contains(puntero.x,puntero.y)){
                return JUEGO;
            }
        }

        return GAMEOVER;
    }

    void dibujar(RenderWindow &window, Puntuacion &punt){
        window.draw(sp_over);
        window.draw(sp_score1);
        punt.draw(window);
    }
};



int main() {
    int k=0;
    float jungla_x = 0;
    int score=0;

    RenderWindow window(VideoMode(1280, 800), "Monkey's Car");

    Texture tex_jungla;
    if (!tex_jungla.loadFromFile("jungla.png")) {
        std::cout << "No se puedo cargar jungla.png, verifique el WorkinDir" << std::endl;
        return EXIT_FAILURE;
    }

    estados estado_actual=MENU;

    Menu menu;
    Juego juego;
    Gameover gameover;

    Puntuacion punt;
    Sprite sp_jungla;
    Sprite sp_jungla2;
    sp_jungla.setTexture(tex_jungla);
    sp_jungla2.setTexture(tex_jungla);

    window.setFramerateLimit(60);


    while (window.isOpen()) {

        k++;

        Event event;
        while (window.pollEvent(event)) {

            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
            }
        }


        //Fondo
        jungla_x-=2;

        if ((-1)*jungla_x > tex_jungla.getSize().x) {
            jungla_x+= tex_jungla.getSize().x;
        }
        sp_jungla.setPosition( jungla_x,0);
        sp_jungla2.setPosition(jungla_x + tex_jungla.getSize().x, 0);


        //Dibujar

        window.clear();
        window.draw(sp_jungla);
        window.draw(sp_jungla2);

        switch (estado_actual) {
            case MENU:
                estado_actual=menu.eventos(window);
                menu.dibujar(window);
                break;
            case JUEGO:
                estado_actual=juego.eventos(k, punt, score);
                juego.dibujar(window, punt, score);
                break;
            case GAMEOVER:
                estado_actual=gameover.eventos();
                gameover.dibujar(window, punt);
                break;
        }

       window.display();


    }
    //guardar puntuacion
    punt.savescore(score);

    return 0;
}


//imagenes obtenidas en http://www.raywenderlich.com