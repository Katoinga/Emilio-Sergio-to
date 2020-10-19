#include "board.h"
#include "chesscell.h"
#include "core.h"
#include "queen.h"
#include "tower.h"
#include "pawn.h"
#include "king.h"
#include "horse.h"
#include "bishop.h"
extern Core *core;   //to implemeeent
Board::Board()
{
    setUpBlack();  //inicializar las fichas
    setUpWhite();
}

//dibujando los cuadros
void Board::drawBoxes(int x,int y)
{
    int SHIFT = 100;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            ChessCell *box = new ChessCell();
            core->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::lightGray);
            else
                box->setOriginalColor(Qt::darkGray);
            core->addToScene(box);



        }
    }

}

//agregando las piezas en las listas
void Board::addChessPiece() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            ChessCell *box =core->collection[i][j];
            if(i < 2) {
                static int k;
                box->placePiece(blackPieces[k]);
                core->alivePiece.append(blackPieces[k]);
                core->addToScene(blackPieces[k++]);
            }
            if(i > 5) {
                static int h;
                box->placePiece(whitePieces[h]);
                core->alivePiece.append(whitePieces[h]);
                core->addToScene(whitePieces[h++]);
            }

        }
    }
}

//inicializar las fichas blancas
void Board::setUpWhite()
{
    ChessPiece *piece;
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("WHITE");
        whitePieces.append(piece);
    }
    piece = new Horse("WHITE");
    whitePieces.append(piece);
    piece = new Tower("WHITE");
    whitePieces.append(piece);
    piece = new Bishop("WHITE");
    whitePieces.append(piece);
    piece = new Queen("WHITE");
    whitePieces.append(piece);
    piece = new King("WHITE");
    whitePieces.append(piece);
    piece = new Bishop("WHITE");
    whitePieces.append(piece);
    piece = new Horse("WHITE");
    whitePieces.append(piece);
    piece = new Tower("WHITE");
    whitePieces.append(piece);

}

//inicializando las piezas negras
void Board::setUpBlack()
{
    ChessPiece *piece;
    piece = new Horse("BLACK");
    blackPieces.append(piece);
    piece = new Tower("BLACK");
    blackPieces.append(piece);
    piece = new Bishop("BLACK");
    blackPieces.append(piece);
    piece = new Queen("BLACK");
    blackPieces.append(piece);
    piece = new King("BLACK");
    blackPieces.append(piece);
    piece = new Bishop("BLACK");
    blackPieces.append(piece);
    piece = new Horse("BLACK");
    blackPieces.append(piece);
    piece = new Tower("BLACK");
    blackPieces.append(piece);
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("BLACK");
        blackPieces.append(piece);
    }
}


void Board::reset() {

}
