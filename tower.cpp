#include "tower.h"
#include "core.h"
extern Core *core;
Tower::Tower(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    //se inicializa poniendo su imagen
    setImage();
}

/*Se encarga de colocar la imagen al objeto mediante Qpixmap*/

void Tower::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/img/img/tower_w.png"));
    else
        setPixmap(QPixmap(":/img/img/tower_b.png"));
}
/*Se encarga de como se mueve la pieza*/

void Tower::move()
{

}


