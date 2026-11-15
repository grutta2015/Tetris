#include "Board.hpp"

using namespace std;
using namespace sf;

Board::Board()
{
    memset(board, 0, sizeof(board));
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            boardShapes[i][j] = RectangleShape(Vector2f(blockSize, blockSize));
            boardShapes[i][j].setPosition({j * (float)blockSize, i * (float)blockSize});
            boardShapes[i][j].setFillColor(Color(50, 50, 50));
            boardShapes[i][j].setOutlineThickness(-1.4f);
            boardShapes[i][j].setOutlineColor(Color(1, 1, 1));
            
        }
    }
    indNextPart = rand() % 7;
}

bool Board::InstallPart(){
 //   srand(time(NULL)); // lo pase a main 
    indNewPart = indNextPart;
    indNextPart = rand() % 7; // Genera la siguiente

    currentPart = parts.ConsultPart(indNewPart);
    int sz = (int) currentPart.size();

    indY = 0;
    indX = 5 - sz/2;

    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            if(currentPart[i][j]){
                if(board[i+indY][j+indX] > 0) return false;
                board[i+indY][j+indX]=-1;
            }
        }
    }

    indColorNewPart = indNewPart + 1;
    newPartColor = colors[indColorNewPart];  
    return true;

}

bool Board::UpdateBoard(){
    bool limit=0;
    int aux;

    if(timer>=limitTimer){
        aux=0;
        for(int i=18; i>=0; i--){
            for(int j=0; j<10; j++){
                if (board[i][j]==-1){
                    if(board[i+1][j]<=0) aux++;
                }
            }
        }
        if (aux==4){
            indY++;
            for(int i=18; i>=0; i--){
                for(int j=0; j<10; j++){
                    if (board[i][j]==-1){
                        board[i][j]=0;
                        board[i+1][j]=-1;                     
                    }
                }
            }
            
        }else{
            for(int i=19; i>=0; i--){
                for(int j=0; j<10; j++){
                    if(board[i][j]==-1) board[i][j]=indColorNewPart;                    
                }
            }
            limit=1;
        }

        timer=0;
    }

    timer++;
    return limit;
}


void Board::UpdateBoardColors(){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j] < 0) boardShapes[i][j].setFillColor(newPartColor);
            else boardShapes[i][j].setFillColor(colors[board[i][j]]);
        }
    }
}

void Board::UpdateLimitTimer(int l){
    limitTimer=l;
}
void Board::RotatePart(){
    int sz = (int)currentPart.size();
    vector<vector<bool>> rotated(sz, vector<bool>(sz, 0));
    
    // Rotar 90 grados en sentido horario
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++){
            rotated[j][sz - 1 - i] = currentPart[i][j];
        }
    }

    // Intentos de Wall Kick (desplazamientos de prueba en X)
    int kicksX[] = {0, -1, 1, -2, 2};
    bool success = false;
    int bestX = indX, bestY = indY;

    for(int k=0; k<5; k++){
        int testX = indX + kicksX[k];
        int testY = indY;
        bool collision = false;

        for(int i=0; i<sz; i++){
            for(int j=0; j<sz; j++){
                if(rotated[i][j]){
                    if(testY + i < 0 || testY + i >= 20 || testX + j < 0 || testX + j >= 10 || board[testY + i][testX + j] > 0){
                        collision = true;
                        break;
                    }
                }
            }
            if(collision) break;
        }

        if(!collision){
            bestX = testX;
            bestY = testY;
            success = true;
            break;
        }
    }

    if(success){
        for(int i=0; i<20; i++){
            for(int j=0; j<10; j++){
                if(board[i][j]==-1) board[i][j]=0;
            }
        }

        currentPart = rotated;
        indX = bestX;
        indY = bestY;

        for(int i=0; i<sz; i++){
            for(int j=0; j<sz; j++){
                if(currentPart[i][j]){
                    board[indY+i][indX+j]=-1;
                }
            }
        }
    }
}

void Board::Right(){
    int aux = 0;

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == -1){
                if(board[i][j + 1] <= 0){
                    aux++;
                }
            }
        }
    }

    if(aux == 4){
        indX++;

        for(int i = 0; i < 20; i++){
            for(int j = 9; j >= 0; j--){
                if(board[i][j] == -1)
                    board[i][j] = 0, board[i][j + 1] = -1;
            }
        }
    }
}

void Board::Left(){
    int aux = 0;

    for(int i = 0; i < 20; i++){
        for(int j = 1; j < 10; j++){
            if(board[i][j] == -1){
                if(board[i][j - 1] <= 0){
                    aux++;
                }
            }
        }
    }

    if(aux == 4){
        indX--;

        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 10; j++){
                if(board[i][j] == -1)
                    board[i][j] = 0, board[i][j - 1] = -1;
            }
        }
    }
}

//###### implementacion de la barra

int Board::HardDrop(){
    while (true) {
        int aux = 0;
        // 1. Verificar si la pieza actual (-1) tiene espacio libre abajo
        for (int i = 18; i >= 0; i--){
            for (int j = 0; j < 10; j++) {
                if (board[i][j] == -1) {
                    if (board[i +1][j] <= 0) aux++;
                }
            }
        }
        // 2. Si las 4 casillas pueden bajar, desplazamos la pieza un nivel abajo
        if (aux==4) {
            indY++;
            for (int i = 18; i >= 0; i--) {
                for (int j = 0; j < 10; j++) {
                    if (board[i][j] == -1) {
                        board[i][j] = 0;
                        board[i + 1][j] = -1;
                    }
                }
            }
        }
        // 3. Cuando ya no puede bajar más, la fijamos en el tablero con su color
        else {
            for (int i = 19; i >= 0; i--) {
                for (int j = 0; j < 10; j++) {
                    if (board[i][j] == -1) board[i][j] = indColorNewPart;
                }
            }
            return 1;  // Retorna 1 para avisar que la pieza se asentó
        }
    }    
}

int Board::CheckLines(){
    int aux=0, lines=0;

    for(int i = 19; i >=0; i--){
        aux=0;
        for(int j = 0; j < 10; j++){
            if(board[i][j] > 0) aux++;  
            if(lines>0) board[i+lines][j] = board[i][j], board[i][j] = 0;    
        }
        if (aux==10){
            for(int j = 0; j < 10; j++) board[i][j]=0;
            lines++;
        }
    }
    return lines;

}

void Board::GameOverFillRow(int row, int color){
    for(int j = 0; j < 10; j++) board[row][j] = color;
}

void Board::StartGameOverAnimation(){
    animPhase = 0;
    animRow = 0;
    rowClock.restart();
}

// Devuelve true una sola vez, al terminar la animación
bool Board::UpdateGameOverAnimation(){
    if(animPhase >= 2) return false;
    if(rowClock.getElapsedTime().asMilliseconds() < 50) return false;
    rowClock.restart();

    GameOverFillRow(animRow, animPhase == 0 ? 1 + animRow % 7 : 0);
    UpdateBoardColors();

    if(++animRow >= 20){
        animRow = 0;
        animPhase++;
    }
    return animPhase == 2;
}

void Board::ClearBoard(){
    memset(board,0,sizeof(board));

}

//  Dibujar la siguiente pieza (Next Piece) adaptado a SFML 3
void Board::DrawNextPart(RenderTarget& rt) const {
    // Obtenemos la matriz de la pieza en cola
    vector<vector<bool>> nextPartMat = const_cast<Parts&>(parts).ConsultPart(indNextPart);
    int sz = (int)nextPartMat.size();

    // Posición en píxeles del panel lateral derecho (Tablero termina en X=210px)
    float offsetX = 405.f;
    float offsetY = 100.f;

    // Bloque individual en SFML 3
    RectangleShape block(Vector2f((float)blockSize, (float)blockSize));
    block.setFillColor(colors[indNextPart + 1]);
    block.setOutlineThickness(-1.03f * ((float)blockSize / 20.f));
    block.setOutlineColor(Color(1, 1, 1));

    // Dibujamos solo las posiciones con valor 1 (bloques activos)
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if (nextPartMat[i][j]) {
                block.setPosition({offsetX + j * (float)blockSize, offsetY + i * (float)blockSize});
                rt.draw(block);
            }
        }
    }
}

void Board::draw(RenderTarget& rt, RenderStates rs) const{
    rs.transform.translate({17.f, 17.f}); // aqui doy un poco el marco
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            rt.draw(boardShapes[i][j], rs);
        }
    }
}