#include "Game.hpp"
#include <fstream>

Game::Game() : window(VideoMode({715, 595}), "Tetris")
{
    window.setFramerateLimit(60);
    srand(time(NULL));
    board.InstallPart();

    ifstream in("Footage/maxScore.txt"); // ver si el uso de ifstream esta en otro lado porque refactorice carpeta
    if(in.is_open()){
        in >> maxScore;
        ui.SetMaxScore(maxScore);
    }
    ui.SetScore(score);
    sounds.PlayMusic();
}

// CheckLinesAddScore
void Game::CheckLinesAddScore(){
    int lines = board.CheckLines();
    if (lines > 0) {
        score += lines * 5;
        ui.SetScore(score);
        sounds.PlayLine();
    }
}

// Se llama al perder: arranca la animación
void Game::LoseGame(){
    isLive = false;
    sounds.PauseMusic();
    board.StartGameOverAnimation();
    sounds.PlayGameOver();
    
}

// Se llama al terminar la animación
void Game::GameOver(){
    if (score > maxScore) {
        maxScore = score;
        ui.GameOver();
                                         
        Draw();                          

        ofstream out("Footage/maxScore.txt");    // aca guardo y le mando out tambien asi aseguro que se guarde ante  de la pausa x cualquier cosa
        out << score;
        out.close();
        sleep(seconds(1));                 // para que el texto se vea durante la pausa     
        sounds.PlayNewScore();           // escribe el número en el texto _newScoreText (con ceros a la izquierda, tipo 0070).
        ui.NewScore();                   // activa la bandera newScore = 1. Eso le dice a draw que muestre los textos “New Score:” y la cifra.
        ui._NewScore(score); 



    } else {
        ui.GameOver();
    }
}

void Game::HandleInput(){
    // Rotación
    if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !up){
        board.RotatePart();
        up = 1;
    } else if (!Keyboard::isKeyPressed(Keyboard::Key::Up)) {
        up = 0;
    }

    // Velocidad de caída
    if (Keyboard::isKeyPressed(Keyboard::Key::Down))
        board.UpdateLimitTimer(5);
    else
        board.UpdateLimitTimer(30);

    // Derecha
    if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !right){
        board.Right();
        right = 1;
    } else if(!Keyboard::isKeyPressed(Keyboard::Key::Right)) {
        right = 0;
    } else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right){
        right++;
        if(right == transMove) right = 0;
    }

    // Izquierda
    if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !left){
        board.Left();
        left = 1;
    } else if(!Keyboard::isKeyPressed(Keyboard::Key::Left)) {
        left = 0;
    } else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left){
        left++;
        if(left == transMove) left = 0;
    }

    // Caída rápida (Espacio)
    if (Keyboard::isKeyPressed(Keyboard::Key::Space) && !space) {
        if (board.HardDrop() == 1) {
            CheckLinesAddScore();
            if (!board.InstallPart()) LoseGame();
        }
        space = 1;
    } else if (!Keyboard::isKeyPressed(Keyboard::Key::Space)) {
        space = 0;
    }
}

// Actualización automática por tiempo
void Game::Update(){
    if(board.UpdateBoard()){
        CheckLinesAddScore();
        if(!board.InstallPart()) LoseGame();
    }
}

void Game::Draw(){
    window.clear(Color(20, 20, 20));
    window.draw(board);
    window.draw(ui);
    board.DrawNextPart(window);
    window.display();
}

void Game::Run(){
    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        if(isLive){
            HandleInput();
            if(isLive) Update();   // HandleInput puede haber terminado la partida
            board.UpdateBoardColors();
        }
        else if(board.UpdateGameOverAnimation())
            GameOver();

        Draw();
    }
}