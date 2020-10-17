#include "queen.h"

Queen::Queen(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    //se inicializa poniendo su imagen
    setImage();
}
/*Se encarga de colocar la imagen al objeto mediante Qpixmap*/

void Queen::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/img/queen_w.png"));
    else
        setPixmap(QPixmap(":/img/queen_b.png"));
}

/*Se encarga de como se mueve la pieza*/

void Queen::move()
{



}
