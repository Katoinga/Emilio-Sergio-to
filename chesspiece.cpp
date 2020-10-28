#include "chesspiece.h"
#include "core.h"
#include <QDebug>
#include <memory>
#include "king.h"
#include <QColor>

extern std::unique_ptr<Core> core;

ChessPiece::ChessPiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    Moved = true;
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == core->pieceToMove){
        core->pieceToMove->getCurrentCell()->resetOriginalColor();
        core->pieceToMove->recolor();
        core->pieceToMove = NULL;
       return;
    }
    if((!getMoved() )|| ( (core->getTurn() != this->getSide())&& (!core->pieceToMove)) )
        return;
    //selecting
    if(!core->pieceToMove){

        core->pieceToMove = this;
        core->pieceToMove->getCurrentCell()->setColor(QColor(42,157,143));
        core->pieceToMove->move();
    }
    //Consuming counterPart of the CHessCell
    else if(this->getSide() != core->pieceToMove->getSide()){
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
