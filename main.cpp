#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>
#include "Board.hpp"
#include "UI.hpp"
#include <fstream>

using namespace std;
using namespace sf;

// Función para manejar el fin de juego y guardar la puntuación máxima
void GameOverHandler(RenderWindow& window, int score, int& maxScore, UI& ui, bool& isLive, Board& board) {
    isLive = false;
    board.ClearBoard();
    if (score > maxScore) {
        maxScore = score;
        ui.NewScore();
        ui._NewScore(score);
        ofstream out("maxScore.txt");
        out << score;
    } else {        
        ui.GameOver();
    }     
}

void checkLines_addScore(Board& board, int& score, UI& ui) {
    int lines = board.CheckLines();
    if (lines > 0) {
        score += lines * 5;
        ui.SetScore(score);
    }
}

int main(){
    bool isLive = true;
    Board board;
    UI ui;
    RenderWindow window(VideoMode({715, 595}), "Tetris");
    window.setFramerateLimit(60);
    srand(time(NULL)); 
    board.InstallPart();

    int right = 0, left = 0, up = 0;
    int space = 0;
    int transMove = 6;
    int score = 0;
    int maxScore = 0;

    Clock rowClock;
    int currentRow = 0;

    // Cargar la puntuación máxima al iniciar
    ifstream in("maxScore.txt");
    if(in.is_open()){
        in >> maxScore;
        ui.SetMaxScore(maxScore);        
    }
    ui.SetScore(score);

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }
        
        if(isLive){

            // Control de rotación
            if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !up){
                board.RotatePart(); 
                up = 1;
            } else if (!Keyboard::isKeyPressed(Keyboard::Key::Up)) {
                up = 0;
            }

            // Control de velocidad de caída
            if (Keyboard::isKeyPressed(Keyboard::Key::Down)) 
                board.UpdateLimitTimer(5);
            else 
                board.UpdateLimitTimer(30);

            // Movimiento a la derecha con repetición (transMove)
            if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !right){
                board.Right();
                right = 1;
            } else if(!Keyboard::isKeyPressed(Keyboard::Key::Right)) {
                right = 0;
            } else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right){
                right++;
                if(right == transMove) right = 0;
            }

            // Movimiento a la izquierda con repetición (transMove)
            if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !left){
                board.Left();
                left = 1;
            } else if(!Keyboard::isKeyPressed(Keyboard::Key::Left)) {
                left = 0;
            } else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left){
                left++;
                if(left == transMove) left = 0;
            } 

            // Control de caída rápida (Espacio)
            if (Keyboard::isKeyPressed(Keyboard::Key::Space) && !space) {
                if (board.HardDrop() == 1) {
                    checkLines_addScore(board, score, ui);
                    if (!board.InstallPart()) {
                        GameOverHandler(window, score, maxScore, ui, isLive, board);
                    }
                }
                space = 1;
            } else if (!Keyboard::isKeyPressed(Keyboard::Key::Space)) {
                space = 0;
            }

            // Actualización automática por tiempo
            if(board.UpdateBoard()){ 
                checkLines_addScore(board, score, ui);
                if(!board.InstallPart()){
                    GameOverHandler(window, score, maxScore, ui, isLive, board);               
                }
            }

            // Renderizado
            
            board.UpdateBoardColors();
            
        
        }else if (currentRow < 20 && rowClock.getElapsedTime().asMilliseconds() >= 50){
                board.GameOverFillRow(currentRow, 1 + currentRow % 7);
                board.UpdateBoardColors();
                currentRow++;
                rowClock.restart();
        }

        window.clear(Color(20, 20, 20));
        window.draw(board);
        window.draw(ui);
        board.DrawNextPart(window);
        window.display();
    }

    return 0;
}