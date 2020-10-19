#include "king.h"
#include "pawn.h"
#include "core.h"
extern Core *core;
King::King(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    //se inicializa poniendo su imagen
    setImage();
}
/*Se encarga de colocar la imagen al objeto mediante Qpixmap*/

void King::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/img/img/king_w.png"));
    else
        setPixmap(QPixmap(":/img/img/king_b.png"));
}

/*Se encarga de como se mueve la pieza*/

void King::move()
{



}
/*se encarga de realizar un check para ver si el rey se encuentra en jaque*/
void King::findUnSafeLocation() {

}
