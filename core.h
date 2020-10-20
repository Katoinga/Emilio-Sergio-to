#ifndef CORE_H
#define CORE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <board.h>
#include "chesspiece.h"
class Core:public QGraphicsView
{
    Q_OBJECT
public:
    //Constructor
    Core(QWidget *parent = 0);

    void drawDeadHolder( int x, int y);
    void displayboard();
    void displayDeadWhite();
    void displayDeadBlack();
    void placeInDeadPlace(ChessPiece *piece);

    //metodos para manejar la escena
    void addToScene(QGraphicsItem *item);      //agrega a la escena
    void removeFromScene(QGraphicsItem *item); //elminina de la escena

    //pieza a mover
    ChessPiece *pieceToMove;

    //conocer el turno
    QString getTurn() ;
    //setea de turno
    void setTurn( QString value);
    //cambia de turno
    void changeTurn();


    //coleccion de celdas
    ChessCell *collection[8][8];
    QGraphicsTextItem *check;
    //verifica si una pieza esta viva
    QList <ChessPiece *> alivePiece;
    //dibuja el menu principal
    void displayMainMenu();

    void gameOver();
    void removeAll();
public slots:
    void start();
private:
    QGraphicsScene *gameScene;
    QList <ChessPiece *> whiteDead;
    QList <ChessPiece *> blackDead;
    QGraphicsRectItem * deadHolder;
    QString turn;
    Board *chess;
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * turnDisplay;


};

#endif // CORE_H
