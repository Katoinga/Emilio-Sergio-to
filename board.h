#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "chesspiece.h"
class Board
{
public:
    Board();

    //dibuja los cuadros
    void initializeBoard(int x, int y);

    //agrega las piezas al tablero
    void addPieces();

    //incluye las piezas blancas
    void initializeWhite();

    //incluye las piezas negras
    void initializeBlack();

    void reset();
private:
    QList <ChessPiece *> whitePieces;
    QList <ChessPiece *> blackPieces;
};

#endif // CHESSBOARD_H
