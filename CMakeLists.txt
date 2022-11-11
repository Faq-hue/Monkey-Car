cmake_minimum_required(VERSION 3.17)
project(codigo)

set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS system window graphics audio)

add_executable(codigo main.cpp mono.cpp mono.h Gusano.cpp Gusano.h Piedra.cpp Piedra.h Coco.cpp Coco.h Puntuacion.cpp Puntuacion.h LinkedList.h Node.h)
target_link_libraries(codigo sfml-system sfml-window sfml-graphics sfml-audio)