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

        //se seleeciona pieza
        if(core->pieceToMove){
            //si esta en el mismo equipo no se puede mover si ya ha movido
            if(this->getChessPieceColor() == core->pieceToMove->getSide())
                return;
            //eliminando si esta muerta esta pieza
            QList <ChessCell *> movLoc = core->pieceToMove->moveLocation();
            //chekea que esta en una de las celdas donde si se puede mover
            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) {
                    check++;

                }
            }
            // si no retorna
            if(check == 0)
                return;
            //cambia el color a normal
             core->pieceToMove->recolor();
             //hace el primer movimiento falta para peones
             core->pieceToMove->firstMove = false;
             //realiza la accion de comer una fiiicha
            if(this->getHasChessPiece()){
                this->currentPiece->setMoved(false);
                this->currentPiece->setCurrentCell(NULL);
                core->placeInDeadPlace(this->currentPiece);
            }
            //resetando la region previa
            core->pieceToMove->getCurrentCell()->setHasChessPiece(false);
            core->pieceToMove->getCurrentCell()->currentPiece = NULL;
            core->pieceToMove->getCurrentCell()->resetOriginalColor();
            placePiece(core->pieceToMove);

            core->pieceToMove = NULL;
            //cambiando el turno
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

//se encarga de checkear continuamente si hay algun jake mate
void ChessCell::checkForCheck()
{
    int c = 0;
        QList <ChessPiece *> pList = core->piecesInGame;
        for(size_t i = 0,n=pList.size(); i < n; i++ ) {

            King * p = dynamic_cast<King *> (pList[i]);
            if(p){
                continue;
            }
            pList[i]->getMoved();
            pList[i]->recolor();
            QList <ChessCell *> bList = pList[i]->moveLocation();
            for(size_t j = 0,n = bList.size(); j < n; j ++) {
                King * p = dynamic_cast<King *> (bList[j]->currentPiece);
                if(p) {
                    if(p->getSide() == pList[i]->getSide())
                        continue;
                    bList[j]->setColor(Qt::blue);
                    pList[i]->getCurrentCell()->setColor(Qt::darkRed);
                    if(!core->check->isVisible())
                        core->check->setVisible(true);
                    else{
                        bList[j]->resetOriginalColor();
                        pList[i]->getCurrentCell()->resetOriginalColor();
                        core->gameOver();
                    }
                    c++;

                }
            }
        }
        if(!c){
            core->check->setVisible(false);
            for(size_t i = 0,n=pList.size(); i < n; i++ )
                pList[i]->getCurrentCell()->resetOriginalColor();
        }
}

//onbtener el color de la pieza que se contiene
QString ChessCell::getChessPieceColor()
{
    return chessPieceColor;
}

//cambiaso el color de la pieza que se contiene
void ChessCell::setChessPieceColor(QString value)
{
    chessPieceColor = value;
}
