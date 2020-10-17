#include "chesspiece.h"

#include "chesspiece.h"
#include "game.h"
#include <QDebug>
#include "king.h"

extern Game *game;
ChessPiece::ChessPiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    Moved = true;
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == game->pieceToMove){
        game->pieceToMove->getCurrentCell()->resetOriginalColor();
        game->pieceToMove->decolor();
        game->pieceToMove = NULL;
       return;
    }
    //if it is already consumed or not the respective color's turn
    if((!getMoved() )|| ( (game->getTurn() != this->getSide())&& (!game->pieceToMove)) )
        return;
    //selecting
    if(!game->pieceToMove){

        game->pieceToMove = this;
        game->pieceToMove->getCurrentCell()->setColor(Qt::red);
        game->pieceToMove->moves();
    }
    //Consuming counterPart of the CHessCell
    else if(this->getSide() != game->pieceToMove->getSide()){
        this->getCurrentCell()->mousePressEvent(event);
    }


}
/*Cambia la celda actual en donde se encuentra el obj*/
void ChessPiece::setCurrentCell(ChessCell *Cell)
{

    currentCell = Cell;
}
/*Obtiene la celda actual en donde se encuentra el obj*/
ChessCell *ChessPiece::getCurrentCell()
{
    return currentCell;
}
/*obtiene el bando (equipo) donde se encuentra black or white*/
QString ChessPiece::getSide()
{
    return side;
}
/*asigna el bando (equipo) donde se encuentra black or white*/
void ChessPiece::setSide( QString value)
{
    side = value;
}
/*comprueba si se movio la pieza*/
bool ChessPiece::getMoved()
{
    return Moved;
}
/*comprueba si se movio la pieza*/
void ChessPiece::setMoved(bool value)
{
    Moved = value;

}
/*Retorna la ubcacion para moverlo */
QList<ChessCell *> ChessPiece::moveLocation()
{
    return location;
}
/**/
void ChessPiece::recolor()
{

}
/*Monta la celda donde se encuentra*/
bool ChessPiece::CellSetup(ChessCell *Cell)
{
    return true;
}
