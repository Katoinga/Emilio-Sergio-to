#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include "chesscell.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class ChessCell;
class ChessPiece:public QGraphicsPixmapItem
{
public:
    ChessPiece(QString team = "",QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentCell(ChessCell *Cell);
    ChessCell *getCurrentCell() const;
    QString getSide() const ;
    void setSide( QString value);
    virtual void setImage() = 0;
    bool getMoved() const ;
    void setMoved(bool value);
    QList <ChessCell *> moveLocation();
    virtual void move() = 0;
    void recolor();
    bool firstMove;
    bool CellSetup(ChessCell *Cell);

protected:
    ChessCell *currentCell;
    QString side;
    bool Moved;
    QList <ChessCell *> location;

};

#endif // CHESSPIECE_H
