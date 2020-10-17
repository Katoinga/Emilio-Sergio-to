#include "bishop.h"
#include <QDebug>


Bishop::Bishop(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    //se inicializa poniendo su imagen
    setImage();
}
/*Se encarga de colocar la imagen al objeto mediante Qpixmap*/
void Bishop::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/img/bishop_w.png"));
    else
        setPixmap(QPixmap(":/img/bishop_b.png"));
}
/*Se encarga de como se mueve la pieza*/
void Bishop::move()
{


}
