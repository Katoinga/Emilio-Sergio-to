#include "horse.h"
#include "core.h"
extern Core *core;
Horse::Horse(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    //se inicializa poniendo su imagen
    setImage();
}
/*Se encarga de colocar la imagen al objeto mediante Qpixmap*/

void Horse::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/img/img/horse_w.png"));
    else
        setPixmap(QPixmap(":/img/img/horse_b.png"));
}
/*Se encarga de como se mueve la pieza*/

void Horse::move()
{
}

