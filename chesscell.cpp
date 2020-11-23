#include "chesscell.h"
#include "core.h"
#include <memory>
#include <QDebug>
#include "king.h"

extern Core *core;
ChessCell::ChessCell(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //cibujar la celda
    setRect(0,0,80,80);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setChessPieceColor("NONE");
    currentPiece = NULL;
}

ChessCell::~ChessCell()
{
    delete this;
}

void ChessCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
        if(currentPiece == core->pieceToMove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        if(core->pieceToMove){
                    //if es del mismo team
                    if(this->getChessPieceColor() == core->pieceToMove->getSide())
                        return;
                    //quitar la pieza comida
                    QList <ChessCell *> movLoc = core->pieceToMove->moveLocation();

                    int check = 0;
                    for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                        if(movLoc[i] == this) {
                            check++;

                        }
                    }
                    // if no hay return
                    if(check == 0)
                        return;
                    //cambiar el color a normal
                     core->pieceToMove->recolor();
                     //hacer que el primer movimiento solo sea de peones
                     core->pieceToMove->firstMove = false;
                     //para poder comer a una pieza
                    if(this->getHasChessPiece()){
                        this->currentPiece->setMoved(false);
                        this->currentPiece->setCurrentCell(NULL);
                        core->placeInDeadPlace(this->currentPiece);

                    }
                    //cambiando el nuevo estado
                    core->pieceToMove->getCurrentCell()->setHasChessPiece(false);
                    core->pieceToMove->getCurrentCell()->currentPiece = NULL;
                    core->pieceToMove->getCurrentCell()->resetOriginalColor();
                    placePiece(core->pieceToMove);

                    core->pieceToMove = NULL;
                    //cambiando de turno
                    core->changeTurn();
                    checkForCheck();
                }

                else if(this->getHasChessPiece())
                {
                    this->currentPiece->mousePressEvent(event);
                }
}

//cambia el color por uno que se le indique
void ChessCell::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

//se encarga de poner las piezas en un lugar deseado del pixman
void ChessCell::placePiece(ChessPiece *piece)
{
    piece->setPos(x()+40- piece->pixmap().width()/2  ,y()+40-piece->pixmap().width()/2);
    piece->setCurrentCell(this);
    setHasChessPiece(true,piece);
    currentPiece = piece;
}

//resetea el color al original
void ChessCell::resetOriginalColor()
{
    setColor(originalColor);
}


//cambia el color originar
void ChessCell::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

//returna si es que tiene o no una pieza
bool ChessCell::getHasChessPiece()
{
    return hasChessPiece;
}

//obtiene el valor del lugar de la pieza
void ChessCell::setHasChessPiece(bool value, ChessPiece *piece)
{
    hasChessPiece = value;
    if(value)
        setChessPieceColor(piece->getSide());
    else
        setChessPieceColor("NONE");
}

void ChessCell::checkForCheck()
{

}

//onbtener el color de la pieza que se contiene
QString ChessCell::getChessPieceColor()
{
    return chessPieceColor;
}

void ChessCell::setChessPieceColor(QString value)
{
    chessPieceColor = value;
}
