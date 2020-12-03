#include "core.h"
#include "button.h"
#include <QPixmap>
#include "king.h"
#include <QDebug>
#include <QColor>
#include <iostream>
#include <QMessageBox>


Core::Core(QWidget *parent ):QGraphicsView(parent)
{
    //construyendo la escena
    chessScene = new QGraphicsScene();
    chessScene->setSceneRect(0,0,1366,700);
    QMessageBox msbx;
    //costruyendo la vista
    setFixedSize(1366,700);
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

    // muestra el check (jaque) como aviso
    check = new QGraphicsTextItem();
    check->setPos(1050,500);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::red);
    check->setFont(QFont("",20));
    check->setPlainText("CHECK, THERE IS A \n POSSIBLE \n CHECKMATE!!");
    check->setVisible(false);
    setTurn("WHITE");

}

//muestra e inicializa el board
void Core::showBoard()
{
    chess = new Board();
    chess->initializeBoard(width()/2-280,90);
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
            //ganaron las piezas negras
            check->setPlainText("Black Won");
            QMessageBox Msgbox;
            Msgbox.setWindowTitle("Chess Winneer!!");
            Msgbox.setText("Black won!!");
            Msgbox.exec();
            gameOver();
        }
        displayDeadWhite();
    }
    else{
        blackDead.append(piece);
        King *g = dynamic_cast <King *>(piece);
        if(g){
            //ganaron las piezas blancas
            check->setPlainText("White Won");
            QMessageBox Msgbox;
            Msgbox.setWindowTitle("Chess Winneer!!");
            Msgbox.setText("White won!!");
            Msgbox.exec();
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
QString Core::getTurn() const
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

void Core::callReset(){
    gameOver();
}


//para empezar el juego, agregamos lo necesario
void Core::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++)
            deleteToScene(listG[i]);

    aggregateToScene(frameTurn);

    //lugar para las piezas blancas muertas
    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(70,10);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::white);
    whitePiece->setFont(QFont("",14));
    whitePiece->setPlainText("WHITE PIECE'S DEAD");
    aggregateToScene(whitePiece);

    //lugar para las piezas blancas muertas
    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();
    blackPiece->setPos(1100,10);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::white);
    blackPiece->setFont(QFont("",14));
    blackPiece->setPlainText("BLACK PIECE'S DEAD");
    aggregateToScene(blackPiece);
    aggregateToScene(check);
    chess->addPieces();

    //lugar para las letras de la izquierda
    QGraphicsTextItem* lettersIZQ = new QGraphicsTextItem();
    lettersIZQ->setPos(350,100);
    lettersIZQ->setZValue(1);
    lettersIZQ->setDefaultTextColor(Qt::white);
    lettersIZQ->setFont(QFont("",44));
    lettersIZQ->setPlainText("8\n7\n6\n5\n4\n3\n2\n1");
    aggregateToScene(lettersIZQ);

    //lugar para las letras de la derecha
    QGraphicsTextItem* lettersDER = new QGraphicsTextItem();
    lettersDER->setPos(990,100);
    lettersDER->setZValue(1);
    lettersDER->setDefaultTextColor(Qt::white);
    lettersDER->setFont(QFont("",44));
    lettersDER->setPlainText("8\n7\n6\n5\n4\n3\n2\n1");
    aggregateToScene(lettersDER);

    //lugar para las letras arriba
    QGraphicsTextItem* lettersARR = new QGraphicsTextItem();
    lettersARR->setPos(420,40);
    lettersARR->setZValue(1);
    lettersARR->setDefaultTextColor(Qt::white);
    lettersARR->setFont(QFont("",30));
    lettersARR->setPlainText("A    B    C    D    E    F    G    H");
    aggregateToScene(lettersARR);

    //lugar para las letras abajo
    QGraphicsTextItem* lettersABA = new QGraphicsTextItem();
    lettersABA->setPos(420,660);
    lettersABA->setZValue(1);
    lettersABA->setDefaultTextColor(Qt::white);
    lettersABA->setFont(QFont("",30));
    lettersABA->setPlainText("A    B    C    D    E    F    G    H");
    aggregateToScene(lettersABA);

    //boton para salir
    Button * salir = new Button("Salir");
    uint16_t sXPos = 70;
    uint16_t sYPos = 600;
    salir->setPos(sXPos,sYPos);
    connect(salir, SIGNAL(clicked()),this,SLOT(start()));
    aggregateToScene(salir);

    //boton para resetear
    Button * reset = new Button("Resetear");
    sXPos = 70;
    sYPos = 520;
    reset->setPos(sXPos,sYPos);
    connect(reset, SIGNAL(clicked()),this,SLOT(callReset()));
    aggregateToScene(reset);
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
    check->setPlainText("CHECK, THERE IS A \n POSSIBLE \n CHECKMATE!!");
    check->setVisible(false);
    //removeAll();

    piecesInGame.clear();
    whiteDead.clear();
    blackDead.clear();
    chess->reset();
    setTurn("WHITE");
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
