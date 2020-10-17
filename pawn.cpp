#include "pawn.h"
#include <QDebug>
#include <typeinfo>
#include "king.h"
Pawn::Pawn(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    //se inicializa poniendo su imagen
    setImage();
    firstMove = true;
}
/*Se encarga de colocar la imagen al objeto mediante Qpixmap*/

void Pawn::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/img/pawn_w.png"));
    else
        setPixmap(QPixmap(":/img/pawn_b.png"));
}

/*Se encarga de como se mueve la pieza*/

void Pawn::move()
{


}


