#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Sounds{
private:
    Music music;
    
    // 1. Declarar los buffers PRIMERO
    SoundBuffer gameOverSoundBuffer;
    SoundBuffer lineSoundBuffer;
    SoundBuffer newScoreSoundBuffer;
    
    // 2. Declarar los Sound pasando su buffer correspondiente para cumplir SFML 3
    Sound gameOverSound{gameOverSoundBuffer}; // Si también necesitas el sonido de game over
    Sound lineSound{lineSoundBuffer};
    Sound newScoreSound{newScoreSoundBuffer};


public:
    Sounds();
    void PlayMusic();
    void PauseMusic();
    void PlayLine();
    void PlayGameOver();
    void PlayNewScore();
};