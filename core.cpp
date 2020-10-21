#include "core.h"
#include "button.h"
#include <QPixmap>
#include "king.h"
#include <QDebug>
#include <QColor>
Core::Core(QWidget *parent ):QGraphicsView(parent)
{
    //construyendo la escena
    chessScene = new QGraphicsScene();
    chessScene->setSceneRect(0,0,695,695);

    //costruyendo la vista
    setFixedSize(695,695);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(chessScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0,0,55));
    setBackgroundBrush(brush);
    pieceToMove = NULL;

    frameTurn = new QGraphicsTextItem();
    frameTurn->setPos(width()/2-100,10);
    frameTurn->setZValue(1);
    frameTurn->setDefaultTextColor(Qt::white);
    frameTurn->setFont(QFont("",18));
    frameTurn->setPlainText("Turno : WHITE");

    check = new QGraphicsTextItem();
    check->setPos(width()/2-100,860);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::white);
    check->setFont(QFont("",18));
    check->setPlainText("CHECK!");
    check->setVisible(false);
    setTurn("WHITE");

}

void Core::showBoard()
{
    chess = new Board();

    chess->initializeBoard(width()/2-320,50);

}



void Core::aggregateToScene(QGraphicsItem *item)
{
    chessScene->addItem(item);
}

void Core::deleteToScene(QGraphicsItem *item)
{
    chessScene->removeItem(item);

}

QString Core::getTurn()
{
    return turn;
}

void Core::setTurn(QString value)
{
    turn = value;
}



void Core::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++)
        deleteToScene(listG[i]);

    aggregateToScene(frameTurn);
    chess->addPieces();
}



void Core::displayMainMenu()
{

    QGraphicsPixmapItem *title = new QGraphicsPixmapItem();
    title->setPixmap(QPixmap(":/img/img/titleChess.png"));
    title->setPos(160,90);
    title->setTransformationMode(Qt::SmoothTransformation);
    aggregateToScene(title);
    listG.append(title);

    //boton para jugar
    Button * jugar = new Button("Jugar");
    uint16_t jXPos = width()/2 - jugar->boundingRect().width()/2;
    uint16_t jYPos = 350;
    jugar->setPos(jXPos,jYPos);
    connect(jugar,SIGNAL(clicked()) , this , SLOT(start()));
    aggregateToScene(jugar);
    listG.append(jugar);

    //boton para salir
    Button * salir = new Button("Salir");
    uint16_t sXPos = width()/2 - salir->boundingRect().width()/2;
    uint16_t sYPos = 600;
    salir->setPos(sXPos,sYPos);
    connect(salir, SIGNAL(clicked()),this,SLOT(close()));
    aggregateToScene(salir);

    showBoard();
    listG.append(salir);

}


