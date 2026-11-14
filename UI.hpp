#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class UI : public Drawable{
    private:
        Font font;
        Text scoreTextTitle{font};
        Text scoreText{font};
        Text maxScoreTextTitle{font};
        Text maxScoreText{font};
        Text gameOverText{font};
        Text NextText{font};
        Text byTextTitle{font};
        Text _newScoreText{font};
        bool newScore=0;
        bool gameOver=0;
        Text newScoreText;
    public:
        UI();
        void SetScore(int);
        void SetMaxScore(int);
        void GameOver();
        void NewScore();
        void _NewScore(int x);
        virtual void draw(RenderTarget&, RenderStates) const;
        //void Next();
};
