#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "chesspiece.h"
class Board
{
public:
    Board();

    //dibuja los cuadros
    void drawBoxes(int x, int y);

    //incluye las piezas blancas
    void setUpWhite();

    //incluye las piezas negras
    void setUpBlack();

    //agrega las piezas al tablero
    void addChessPiece();
    void reset();
private:
    QList <ChessPiece *> whitePieces;
    QList <ChessPiece *> blackPieces;
};

#endif // CHESSBOARD_H
