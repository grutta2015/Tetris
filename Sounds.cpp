#include "Sounds.hpp"

using namespace std;
using namespace sf;

Sounds::Sounds() {
    // Cargar música correctamente (con minúscula y comillas)
    if (!music.openFromFile("Footage/tetrardo.mp3")) {
        std::cout << "Error al cargar la musica" << std::endl;
    }
    music.setLooping(true);
    music.setVolume(25.f);

    // Cargar los efectos de sonido en sus respectivos buffers
    if (!lineSoundBuffer.loadFromFile("Footage/line.ogg")) {
        std::cout << "Error al cargar sonido line.ogg" << std::endl;
    }
    if (!newScoreSoundBuffer.loadFromFile("Footage/newscore.mp3")) {
        std::cout << "Error al cargar sonido newScore.ogg" << std::endl;
    }
    if (!gameOverSoundBuffer.loadFromFile("Footage/gameover.mp3")) {
        std::cout << "Error al cargar sonido gameOver.ogg" << std::endl;
    }
}

void Sounds::PlayMusic() {
    music.play();
}

void Sounds::PauseMusic() {
    music.pause();
}

void Sounds::PlayLine() {
    lineSound.play();
}

void Sounds::PlayGameOver() {
    gameOverSound.play();
}

void Sounds::PlayNewScore() {
    newScoreSound.play();
}