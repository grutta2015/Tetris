#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "UI.hpp"
#include "Sounds.hpp"

class Game
{
    private:
        Board board;
        UI ui;
        Sounds sounds;
        RenderWindow window;

        bool isLive = true;
        int score = 0, maxScore = 0;
        int right = 0, left = 0, up = 0, space = 0;
        int transMove = 6;

        void CheckLinesAddScore();
        void LoseGame();
        void GameOver();
        void HandleInput();
        void Update();
        void Draw();

    public:
        Game();
        void Run();
};