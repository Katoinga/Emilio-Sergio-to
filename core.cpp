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
    gameScene->setSceneRect(0,0,1460,720);

    //costruyendo la vista
    setFixedSize(1460,720);
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

void Core::drawChessBoard()
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

    //titulo c:
    QGraphicsTextItem *Menu = new QGraphicsTextItem("Ajedrez");
    QFont titleFont("arial" , 50);
    Menu->setFont( titleFont);
    int xPos = width()/2 - Menu->boundingRect().width()/2;
    int yPos = 160;
    Menu->setPos(xPos,yPos);
    addToScene(Menu);
    listG.append(Menu);
    //boton para juagr
    Button * playButton = new Button("Jugar");
    int pxPos = width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 350;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));
    addToScene(playButton);
    listG.append(playButton);

    //boton para salir
    Button * quitButton = new Button("Salir");
    int qxPos = width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 425;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(quitButton);
    drawChessBoard();
    listG.append(quitButton);

}

void Core::gameOver()
{


}

void Core::removeAll(){

}
