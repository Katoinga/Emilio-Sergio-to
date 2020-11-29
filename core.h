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

    void displayDeadsFrame( int x, int y);
    void showBoard();
    void showDeadWhites();
    void showDeadBlack();
    void placeInDeadPlace(ChessPiece *piece);

    //metodos para manejar la escena
    void aggregateToScene(QGraphicsItem *item);      //agrega a la escena
    void deleteToScene(QGraphicsItem *item); //elminina de la escena

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
    //verifica las piezas vivas
    QList <ChessPiece *> piecesInGame;
    void displayDeadWhite();
    void displayDeadBlack();

    //dibuja el menu principal
    void displayMainMenu();
    //to implement, cuando el juego acabe
    void gameOver();
    //elimina todo
    void removeAll();

public slots:
    void start();
private:
    QGraphicsScene *chessScene;
    QTimer *timer;
    QList <ChessPiece *> whiteDead;
    QList <ChessPiece *> blackDead;
    QGraphicsRectItem * deadHolder;
    QString turn;
    Board *chess;
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * frameTurn;

};

#endif // CORE_H
