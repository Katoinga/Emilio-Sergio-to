#include "core.h"
#include "button.h"
#include <QPixmap>
#include "king.h"
#include <QDebug>
#include <QColor>
#include <iostream>

Core::Core(QWidget *parent ):QGraphicsView(parent)
{
    //construyendo la escena
    chessScene = new QGraphicsScene();
    chessScene->setSceneRect(0,0,1350,695);

    //costruyendo la vista
    setFixedSize(1350,695);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(chessScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0,0,55));
    setBackgroundBrush(brush);
    pieceToMove = NULL;
    //se encarga de mostrar turno de quien es
    frameTurn = new QGraphicsTextItem();
    frameTurn->setPos(width()/2-100,10);
    frameTurn->setZValue(1);
    frameTurn->setDefaultTextColor(Qt::white);
    frameTurn->setFont(QFont("",18));
    frameTurn->setPlainText("Turno : WHITE");
    // muestra el check (jaque)
    check = new QGraphicsTextItem();
    check->setPos(width()/2-100,860);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::red);
    check->setFont(QFont("",18));
    check->setPlainText("CHECK!");
    check->setVisible(false);
    setTurn("WHITE");

}

//muestra e inicializa el board
void Core::showBoard()
{
    chess = new Board();
    chess->initializeBoard(width()/2-320,50);

}

//dibuja el cuadro que contendra a las piezas blancas muertas
void Core::displayDeadWhite()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = whiteDead.size(); i<n; i++) {
            if(j == 4){
                k++;
                j = 0;
            }
            whiteDead[i]->setPos(40+SHIFT*j++,100+SHIFT*2*k);
    }
}

//dibuja el cuadro que contendra a las piezas negras muertas
void Core::displayDeadBlack()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = blackDead.size(); i<n; i++) {
        if(j == 4){
            k++;
            j = 0;
        }
        blackDead[i]->setPos(1140+SHIFT*j++,100+SHIFT*2*k);
    }
}

//verifica si se ha acabado el juego
void Core::placeInDeadPlace(ChessPiece *piece)
{
    if(piece->getSide() == "WHITE") {
        whiteDead.append(piece);
        King *g = dynamic_cast <King *>(piece);
        if(g){
            check->setPlainText("Black Won");
            gameOver();
        }
        displayDeadWhite();
    }
    else{
        blackDead.append(piece);
        King *g = dynamic_cast <King *>(piece);
        if(g){
            check->setPlainText("White Won");
            gameOver();
        }
        displayDeadBlack();
    }
    piecesInGame.removeAll(piece);
}

//agrega un item a la escena
void Core::aggregateToScene(QGraphicsItem *item)
{
    chessScene->addItem(item);
}

//elimina un dterminado item de la escena
void Core::deleteToScene(QGraphicsItem *item)
{
    chessScene->removeItem(item);

}

//devuelve el turno actual
QString Core::getTurn()
{
    return turn;
}

//cambiamos el turno
void Core::setTurn(QString value)
{
    turn = value;
}

//para cambiar de turno
void Core::changeTurn()
{
    if(getTurn() == "WHITE")
        setTurn("BLACK");
    else
        setTurn("WHITE");
    frameTurn->setPlainText("Turn : " + getTurn());
}

//para empezar el juego, agregamos lo necesario
void Core::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++)
            deleteToScene(listG[i]);

        aggregateToScene(frameTurn);
        QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
        whitePiece->setPos(70,10);
        whitePiece->setZValue(1);
        whitePiece->setDefaultTextColor(Qt::white);
        whitePiece->setFont(QFont("",14));
        whitePiece->setPlainText("WHITE PIECE'S DEAD");
        aggregateToScene(whitePiece);
        QGraphicsTextItem *blackPiece = new QGraphicsTextItem();

        blackPiece->setPos(1170,10);
        blackPiece->setZValue(1);
        blackPiece->setDefaultTextColor(Qt::black);
        blackPiece->setFont(QFont("",14));
        blackPiece->setPlainText("BLACK PIECE'S DEAD");
        aggregateToScene(blackPiece);
        aggregateToScene(check);
        chess->addPieces();
}

//dibujamos el frame que contendra los muertos
void Core::displayDeadsFrame(int x, int y)
{
    deadHolder = new QGraphicsRectItem(x,y,300,900);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    deadHolder->setBrush(brush);
    aggregateToScene(deadHolder);
}

//para dibujar el menu
void Core::displayMainMenu()
{

    QGraphicsPixmapItem *title = new QGraphicsPixmapItem();
    title->setPixmap(QPixmap(":/img/img/titleChess.png"));
    title->setPos(460,90);
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

//se ejecuta cuando alguno gane, reseteando el juego
void Core::gameOver(){
    removeAll();
    setTurn("WHITE");
    piecesInGame.clear();

    chess->reset();
//mostrar imagen quien gano
}

//eliminamos absolutamente todo lo que este en la escena
void Core::removeAll(){
    QList<QGraphicsItem*> itemsList = chessScene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          deleteToScene(itemsList[i]);
    }
}
