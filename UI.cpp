#include "UI.hpp"

using namespace std;
using namespace sf;

UI::UI() 
    : scoreText(font), 
      NextText(font), 
      scoreTextTitle(font), 
      maxScoreTextTitle(font), 
      maxScoreText(font), 
      gameOverText(font), 
      byTextTitle(font),
      _newScoreText(font),
      newScoreText(font) 
{

if(!font.openFromFile("Footage/ka1.ttf")){
        std::cout << "Error al cargar fuente texto" << std::endl;
    }

    // Configuración de propiedades que no requieren la fuente
    NextText.setString("Next");
    NextText.setCharacterSize(50);
    NextText.setFillColor(sf::Color(187, 34, 0)); // rgb(187, 34, 0)
    NextText.setPosition(sf::Vector2f(365, 18));

    scoreTextTitle.setString("Score:");
    scoreTextTitle.setCharacterSize(40);
    scoreTextTitle.setFillColor(sf::Color(0, 11, 165)); // rgb(0, 11, 165)
    scoreTextTitle.setPosition(sf::Vector2f(365, 220));

    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color(255, 176, 0)); // rgb(255, 176, 0)
    scoreText.setPosition(sf::Vector2f(365, 275));

    maxScoreTextTitle.setString("Max-Score:");
    maxScoreTextTitle.setCharacterSize(40);
    maxScoreTextTitle.setFillColor(sf::Color(71, 133, 0)); // rgb(71, 133, 0)
    maxScoreTextTitle.setPosition(sf::Vector2f(365, 395));

    maxScoreText.setCharacterSize(20);
    maxScoreText.setFillColor(sf::Color(255, 176, 0)); // rgb(255, 176, 0) 
    maxScoreText.setPosition(sf::Vector2f(365, 450));

    byTextTitle.setString("by: MMG");
    byTextTitle.setCharacterSize(20);
    byTextTitle.setFillColor(sf::Color(0, 91, 177)); // rgb(0, 91, 177)
    byTextTitle.setPosition(sf::Vector2f(566, 540));

    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(37);
    gameOverText.setFillColor(sf::Color(255, 233, 168)); // rgb(255, 233, 168)
    gameOverText.setPosition(sf::Vector2f(17, 275));

    newScoreText.setString("New Score:");
    newScoreText.setCharacterSize(25);
    newScoreText.setFillColor(sf::Color(255, 233, 168)); // rgb(255, 233, 168)
    newScoreText.setPosition(sf::Vector2f(65, 340));

    _newScoreText.setCharacterSize(25);
    _newScoreText.setFillColor(sf::Color(255, 233, 168)); // rgb(255, 233, 168)
    _newScoreText.setPosition(sf::Vector2f(105, 377));

    // rgb(255, 233, 168)
}

void UI::SetScore(int x){
    if (x <= 9)        scoreText.setString("000" + to_string(x));
    else if (x <= 99)  scoreText.setString("00" + to_string(x));
    else if (x <= 999) scoreText.setString("0" + to_string(x));  // Aquí iba un solo "0"
    else if (x <= 9999)scoreText.setString(to_string(x));
    else scoreText.setString("Rompiste Tetris!");
    
}

void UI::SetMaxScore(int x){
    if (x <= 9)        maxScoreText.setString("000" + to_string(x));
    else if (x <= 99)  maxScoreText.setString("00" + to_string(x));
    else if (x <= 999) maxScoreText.setString("0" + to_string(x));  // Aquí iba un solo "0"
    else if (x <= 9999)maxScoreText.setString(to_string(x));
    else maxScoreText.setString("Rompiste Tetris!");
    
}

void UI::_NewScore(int x) {
    if (x <= 9)        _newScoreText.setString("000" + to_string(x));
    else if (x <= 99)  _newScoreText.setString("00" + to_string(x));
    else if (x <= 999) _newScoreText.setString("0" + to_string(x));
    else if (x <= 9999)_newScoreText.setString(to_string(x));
    else _newScoreText.setString("Rompiste Tetris!");
}

void UI::GameOver(){
    gameOver=1;
}

void UI::NewScore(){
    newScore=1;
}

void UI::draw(RenderTarget& rt, RenderStates rs) const{
    rt.draw(NextText,rs);
    rt.draw(scoreTextTitle,rs);
    rt.draw(scoreText,rs);
    rt.draw(maxScoreTextTitle,rs);
    rt.draw(maxScoreText,rs);
    rt.draw(byTextTitle,rs);
    if(gameOver) rt.draw(gameOverText,rs);
    if(newScore){
        rt.draw(_newScoreText, rs);
        rt.draw(newScoreText, rs);
    }
}

