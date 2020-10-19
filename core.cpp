#include "core.h"
#include "button.h"
#include <QPixmap>
#include "king.h"
#include <QDebug>
Core::Core(QWidget *parent ):QGraphicsView(parent)
{
    //construyendo la escena
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,1400,900);

    //costruyendo la vista
    setFixedSize(1400,900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
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
    check->setDefaultTextColor(Qt::red);
    check->setFont(QFont("",18));
    check->setPlainText("CHECK!");
    check->setVisible(false);
    setTurn("WHITE");

}

void Core::drawChessBoard()
{
    chess = new Board();
    drawDeadHolder(0,0,Qt::lightGray);
    drawDeadHolder(1100,0,Qt::lightGray);
    chess->drawBoxes(width()/2-400,50);

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
    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(70,10);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::white);
    whitePiece->setFont(QFont("",14));
    whitePiece->setPlainText("WHITE PIECE");
    addToScene(whitePiece);
    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();

    blackPiece->setPos(1170,10);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::black);
    blackPiece->setFont(QFont("",14));
    blackPiece->setPlainText("BLACK PIECE");
    addToScene(blackPiece);
    addToScene(check);
    chess->addChessPiece();
}

void Core::drawDeadHolder(int x, int y,QColor color)
{

}



void Core::displayMainMenu()
{

    //titulo c:
    QGraphicsTextItem *titleText = new QGraphicsTextItem("Ajedrez TO");
    QFont titleFont("arial" , 50);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 160;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);
    //boton para juagr
    Button * playButton = new Button("Jugar");
    int pxPos = width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 350;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));
    addToScene(playButton);
    listG.append(playButton);

    //boton para cerrar
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
