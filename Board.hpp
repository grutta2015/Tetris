#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <time.h>
#include "Parts.hpp"

using namespace std;
using namespace sf;

class Board : public Drawable
{
    private:
        Parts parts;
        int indNewPart, indColorNewPart;
        int indNextPart;
        
        int indX, indY;
        int blockSize = 28;

        int timer=0;       // contador de tiempo para el movimiento de la pieza
        int limitTimer=30; // limitador de ese tiempo

        int board[20][10];

        RectangleShape boardShapes[20][10];
        Color newPartColor;
        inline static const Color colors[8] = {
            Color(50, 50, 50),    // rgb(50, 50, 50)    0 vacío
            Color(240, 240, 0),   // rgb(240, 240, 0)   1 O amarillo
            Color(0, 0, 240),     // rgb(0, 0, 240)     2 J azul
            Color(240, 160, 0),   // rgb(240, 160, 0)   3 L naranja
            Color(0, 240, 0),     // rgb(0, 240, 0)     4 S verde
            Color(240, 0, 0),     // rgb(240, 0, 0)     5 Z rojo
            Color(160, 0, 240),   // rgb(160, 0, 240)   6 T púrpura
            Color(0, 240, 240)    // rgb(0, 240, 240)   7 I cian
        };


    private:
        vector<vector<bool>> currentPart;

    public:
        Board();
        bool InstallPart();
        bool UpdateBoard(); // actualiza tablero, para ver si hay lineas completas, la pieza se ha colocado, se perdio, etc
        void UpdateBoardColors();
        void UpdateLimitTimer(int l);
        void Right();
        void Left();
        int HardDrop(); //#########
        void RotatePart();
        int CheckLines();
        void ClearBoard();
        void GameOverFillRow(int row, int color);
        void DrawNextPart(RenderTarget& rt) const;
        virtual void draw(RenderTarget& rt, RenderStates rs) const override; 
};