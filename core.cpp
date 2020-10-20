#include "core.h"
#include "button.h"
#include <QPixmap>
#include "king.h"
#include <QDebug>
#include <QColor>
Core::Core(QWidget *parent ):QGraphicsView(parent)
{
    //construyendo la escena
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,1360,695);

    //costruyendo la vista
    setFixedSize(1360,695);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0,0,55));
    setBackgroundBrush(brush);
    pieceToMove = NULL;

    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Turn : WHITE");

    check = new QGraphicsTextItem();
    check->setPos(width()/2-100,860);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::white);
    check->setFont(QFont("",18));
    check->setPlainText("CHECK!");
    check->setVisible(false);
    setTurn("WHITE");

}

void Core::displayboard()
{
    chess = new Board();
    drawDeadHolder(0,0);
    drawDeadHolder(1111,0);
    chess->drawCell(width()/2-320,50);

}

void Core::displayDeadWhite()
{

}

void Core::displayDeadBlack()
{

}

void Core::placeInDeadPlace(ChessPiece *piece)
{


}

void Core::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}

void Core::removeFromScene(QGraphicsItem *item)
{
    gameScene->removeItem(item);

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
        removeFromScene(listG[i]);

    addToScene(turnDisplay);
    QGraphicsTextItem* whiteArr = new QGraphicsTextItem();
    whiteArr->setPos(70,10);
    whiteArr->setZValue(1);
    whiteArr->setDefaultTextColor(Qt::white);
    whiteArr->setFont(QFont("",14));
    whiteArr->setPlainText("WHITE PIECES");
    addToScene(whiteArr);
    QGraphicsTextItem *blackArr = new QGraphicsTextItem();
    blackArr->setDefaultTextColor(Qt::white);
    blackArr->setFont(QFont("",14));
    blackArr->setPlainText("BLACK PIECES");
    blackArr->setPos(1170,10);
    blackArr->setZValue(1);
    addToScene(blackArr);
    addToScene(check);
    chess->addChessPiece();
}
//barras para las jugadas y retener las piezas comidas
void Core::drawDeadHolder( int x, int y)
{
    deadHolder = new QGraphicsRectItem(x,y,300,900);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor((55));
    deadHolder->setBrush(brush);
    addToScene(deadHolder);
}



void Core::displayMainMenu()
{

    //titulo
    /*QGraphicsTextItem *titulo = new QGraphicsTextItem("Ajedreeeez");
    QFont titleFont("arial" , 50);
    titulo->setFont( titleFont);
    int xPos = width()/2 - titulo->boundingRect().width()/2;
    int yPos = 160;
    titulo->setPos(xPos,yPos);
    addToScene(titulo);
    listG.append(titulo);
*/

    QGraphicsPixmapItem *title = new QGraphicsPixmapItem();
    title->setPixmap(QPixmap(":/img/img/titleChess.png"));
    title->setPos(490,70);
    title->setTransformationMode(Qt::SmoothTransformation);
    addToScene(title);
    listG.append(title);

    //boton para jugar
    Button * jugar = new Button("Jugar");
    int pxPos = width()/2 - jugar->boundingRect().width()/2;
    int pyPos = 350;
    jugar->setPos(pxPos,pyPos);
    connect(jugar,SIGNAL(clicked()) , this , SLOT(start()));
    addToScene(jugar);
    listG.append(jugar);

    //boton para salir
    Button * salir = new Button("Salir");
    int qxPos = width()/2 - salir->boundingRect().width()/2;
    int qyPos = 600;
    salir->setPos(qxPos,qyPos);
    connect(salir, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(salir);

    displayboard();
    listG.append(salir);

}

void Core::gameOver()
{


}

void Core::removeAll(){

}
