#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>


//constructor explicito que recibe el nombre del boton yun qgraphicsitem que puede ser null
Button::Button(QString nombre, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    //dibujar el cuadro que contiene el boton
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);

    //insertar el texto del boton
    texto = new QGraphicsTextItem(nombre,this);
    int xPos = rect().width()/2 - texto->boundingRect().width()/2;
    int yPos = rect().height()/2 - texto->boundingRect().height()/2;
    texto->setPos(xPos,yPos);
    texto->setDefaultTextColor(Qt::white);

    setAcceptHoverEvents(true);
}

//metodo para verificar cuando el boton es presionado
void Button::mousePressEvent(QGraphicsSceneMouseEvent *evento)
{
    //cuando el boton es presionado, enviar la señal
    if(evento)
    emit clicked();

}

//metodo para cambiar el color de un boton a rojo
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *evento)
{
    //cambiar el color a rojo
    if(evento){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    }
}

//metodo para cambiar el color de un boton a rojo ocscuro
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *evento) {

    //cambiar el color a rojo oscuro
    if(evento){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);
    }
}
