#ifndef CHESSCELL_H
#define CHESSCELL_H

#include <QGraphicsRectItem>
#include <QBrush>
#include "chesspiece.h"
#include <QGraphicsSceneMouseEvent>

class ChessPiece;
class ChessCell:public QGraphicsRectItem
{
public:

    //Constructor
    ChessCell(QGraphicsItem *parent=0);
    //destructor
    ~ChessCell();

    //se presione esa celda
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //cambiar de color
    void setColor(QColor color);
    //obtener el lugar de una pieza
    void placePiece(ChessPiece *piece);

    //resetear al color original
    void resetOriginalColor();
    //cambia el color original
    void setOriginalColor(QColor value);

    //verificar si una celda tiene una pieza
    bool getHasChessPiece() const;
    //cambia la pieza que tiene
    void setHasChessPiece(bool value,ChessPiece *piece = 0);

    void checkForCheck();

    //oobtiene el color de la pieza que contiene
    QString getChessPieceColor() const ;
    void setChessPieceColor(QString value);

    int rowLoc;
    int colLoc;

    ChessPiece * currentPiece;

private:
    QColor originalColor;
    bool hasChessPiece;
    QBrush brush;
    QString chessPieceColor;


};

#endif // CHESSCELL_H
