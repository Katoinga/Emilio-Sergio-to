#include "board.h"
#include "chesscell.h"
#include "core.h"
#include "queen.h"
#include "tower.h"
#include "pawn.h"
#include "king.h"
#include "horse.h"
#include "bishop.h"
#include <QColor>

extern Core *core;
Board::Board()
{
    initializeBlack();  //inicializar las fichas negras
    initializeWhite();  //inicializar las fichas blancas
}

//dibujando los cuadros
void Board::initializeBoard(int x,int y)
{
    uint16_t sizeCell = 80;
    for(uint16_t i = 0; i < 8; i++) {
        for(uint16_t j = 0; j < 8; j++)
        {
            ChessCell *cell = new ChessCell();
            core->collection[i][j] = cell;
            cell->rowLoc = i;
            cell->colLoc = j;
            cell->setPos(x+sizeCell*j,y+sizeCell*i);
            if((i+j)%2==0)
                cell->setOriginalColor(QColor(255, 206, 158));
            else
                cell->setOriginalColor(QColor(209, 139, 71));
            core->aggregateToScene(cell);
        }
    }

}

//agregando las piezas en las listas
void Board::addPieces() {
    for(uint16_t i = 0; i < 8; i++) {
        for(uint16_t j = 0; j < 8; j++)
        {

            ChessCell *cell =core->collection[i][j];
            if(i < 2) {
                static uint16_t k;
                cell->placePiece(blackPieces[k]);
                core->piecesInGame.append(blackPieces[k]);
                core->aggregateToScene(blackPieces[k++]);
            }
            if(i > 5) {
                static uint16_t h;
                cell->placePiece(whitePieces[h]);
                core->piecesInGame.append(whitePieces[h]);
                core->aggregateToScene(whitePieces[h++]);
            }

        }
    }
}

//inicializar las fichas blancas
void Board::initializeWhite()
{
    ChessPiece *pieceToAdd;
    for(int i = 0; i < 8; i++) {
        pieceToAdd = new Pawn("WHITE");
        whitePieces.append(pieceToAdd);
    }
    pieceToAdd = new Tower("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Horse("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Bishop("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Queen("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new King("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Bishop("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Horse("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Tower("WHITE");
    whitePieces.append(pieceToAdd);

}

//inicializando las piezas negras
void Board::initializeBlack()
{
    ChessPiece *pieceToAdd;
    pieceToAdd = new Tower("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Horse("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Bishop("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Queen("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new King("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Bishop("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Horse("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Tower("BLACK");
    blackPieces.append(pieceToAdd);
    for(int i = 0; i < 8; i++) {
        pieceToAdd = new Pawn("BLACK");
        blackPieces.append(pieceToAdd);
    }
}

//resetea el board una vez haya ganado uno de los jugadores
void Board::reset() {
    int k = 0; int h = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++)
            {

                ChessCell *box =core->collection[i][j];
                box->setHasChessPiece(false);
                box->setChessPieceColor("NONE");
                box->currentPiece = NULL;
                if(i < 2) {

                    box->placePiece(blackPieces[k]);
                    blackPieces[k]->setMoved(true);
                    blackPieces[k]->firstMove = true;
                    core->piecesInGame.append(blackPieces[k++]);

                }
                if(i > 5) {

                    box->placePiece(whitePieces[h]);
                    whitePieces[h]->setMoved(true);
                    whitePieces[h]->firstMove = true;
                    core->piecesInGame.append(whitePieces[h++]);

                }

            }
        }
}
