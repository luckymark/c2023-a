#ifndef TBOARDD_H
#define TBOARDD_H

#include "./AI/board.h"
#include "./AI/negamax.h"

#include <iostream>

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QApplication>

class TBoard : public QWidget
{
    Q_OBJECT
private:
    Board board;
    bool clickable;
    bool humanFirst;
    static double padX, padY;
    static double perY, perX;
    static int chessSize;
    QBrush whiteBrush, blackBrush;

public:
    explicit TBoard(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
signals:
    void humanPutChess(Place p, bool success);
    void computerPutChess();
    void computerPutChess(Place p);
};

#endif // TBOARDD_H
