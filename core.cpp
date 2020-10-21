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
    chessScene->setSceneRect(0,0,1360,695);

    //costruyendo la vista
    setFixedSize(1360,695);
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
    displayDeadsFrame(0,0);
    displayDeadsFrame(1111,0);
    chess->initializeBoard(width()/2-320,50);

}

void Core::showDeadWhites()
{

}

void Core::showDeadBlack()
{

}

void Core::placeInDeadPlace(ChessPiece *piece)
{


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

void Core::changeTurn()
{

}

void Core::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++)
        deleteToScene(listG[i]);

    aggregateToScene(frameTurn);
    QGraphicsTextItem* whiteArr = new QGraphicsTextItem();
    whiteArr->setPos(70,10);
    whiteArr->setZValue(1);
    whiteArr->setDefaultTextColor(Qt::white);
    whiteArr->setFont(QFont("",14));
    whiteArr->setPlainText("Piezas Blancas");
    aggregateToScene(whiteArr);
    QGraphicsTextItem *blackArr = new QGraphicsTextItem();
    blackArr->setDefaultTextColor(Qt::white);
    blackArr->setFont(QFont("",14));
    blackArr->setPlainText("Piezas negras");
    blackArr->setPos(1170,10);
    blackArr->setZValue(1);
    aggregateToScene(blackArr);
    aggregateToScene(check);
    chess->addPieces();
}

//barras para las jugadas y retener las piezas comidas
void Core::displayDeadsFrame( int x, int y)
{
    deadHolder = new QGraphicsRectItem(x,y,300,900);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor((55));
    deadHolder->setBrush(brush);
    aggregateToScene(deadHolder);
}



void Core::displayMainMenu()
{

    QGraphicsPixmapItem *title = new QGraphicsPixmapItem();
    title->setPixmap(QPixmap(":/img/img/titleChess.png"));
    title->setPos(490,70);
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

void Core::gameOver()
{


}

void Core::removeAll(){

}
