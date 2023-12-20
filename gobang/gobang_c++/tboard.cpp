#include "tboard.h"

double TBoard::padX = 0.05, TBoard::padY = 0.05;
double TBoard::perY = 0.9, TBoard::perX = 0.9;
int TBoard::chessSize = 20;


TBoard::TBoard(QWidget *parent) : QWidget{parent}, board(), clickable{true}, humanFirst{true},
                                  whiteBrush(QColor(255, 255, 255)), blackBrush(QColor(0, 0, 0)) {
//    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    QApplication::setOverrideCursor(Qt::ArrowCursor);//设置鼠标样式为默认

    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Board"));
    this->resize(550, 550);
//    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setCursor(Qt::PointingHandCursor);
    QMetaObject::connectSlotsByName(this);

    this->whiteBrush.setStyle(Qt::SolidPattern);
    this->blackBrush.setStyle(Qt::SolidPattern);
}

void TBoard::mousePressEvent(QMouseEvent *event) {
    QRect rect(0, 0, this->width(), this->height());
    if (!this->clickable) {
        goto mousePressEventReturn;
    }
    if (this->clickable && event->button() == Qt::LeftButton)   //鼠标左键
    {
        this->clickable = false;
        QPointF pos = event->position();        //相对坐标,x,y均为double
        double spanX = this->width() * 0.9 / 14, spanY = this->height() * 0.9 / 14;
        Place pc{(int) ((pos.x() - this->width() * TBoard::padX) / spanX + 0.5), // NOLINT(*-incorrect-roundings)
                 (int) ((pos.y() - this->height() * TBoard::padY) / spanY + 0.5)}; // NOLINT(*-incorrect-roundings)
        bool result = this->board.put(pc, Role::HUMAN, true);
        emit humanPutChess(pc, result);
        if (result) {
            //落子成功
            /*update(QRect((int) (this->width() * (TBoard::padX + TBoard::perX * pc.x / 14) - TBoard::chessSize/2.0),
                         (int) (this->height() * (TBoard::padY + TBoard::perY * pc.y / 14) - TBoard::chessSize/2.0),
                         TBoard::chessSize, TBoard::chessSize));*/
            update();

            if (this->board.isWin() != Role::NONE) {
                this->clickable = false;
                QApplication::setOverrideCursor(Qt::ForbiddenCursor);
                goto mousePressEventReturn;
            }

            QApplication::setOverrideCursor(Qt::ForbiddenCursor);
            emit computerPutChess();
            auto p = deepenAll(this->board, Role::COMPUTER);
            this->board.put(p, Role::COMPUTER, true);
            rect = QRect((int) (this->width() * (TBoard::padX + TBoard::perX * p.x / 14) - TBoard::chessSize / 2.0),
                         (int) (this->height() * (TBoard::padY + TBoard::perY * p.y / 14 - TBoard::chessSize / 2.0)),
                         TBoard::chessSize, TBoard::chessSize);
            emit computerPutChess(p);
//            update(rect);
            update();
            if (this->board.isWin() != Role::NONE) {
                update(rect);
                goto mousePressEventReturn;
            }

            this->clickable = true;
            QApplication::setOverrideCursor(Qt::ArrowCursor);
        }
    }

    mousePressEventReturn:
    if (this->clickable)update(rect);
    event->accept();
}


void TBoard::paintEvent(QPaintEvent *event) {
    Role r;
    QPainter painter(this);
    QPen pen;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    //绘制棋盘
    int W = this->width(), H = this->height();
    QRect rect((int) (W * TBoard::padX), (int) (H * TBoard::padY), (int) (W * TBoard::perX),
               (int) (H * TBoard::perY));
    pen.setWidth(2);
    pen.setColor(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    QBrush brush;
    brush.setColor(QColor(249, 211, 103, 128));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(rect);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    double spanX = this->width() * TBoard::perX / 14, spanY = this->height() * TBoard::perY / 14;
    for (int i = 1; i < 14; i++) {
        painter.drawLine((int) (W * TBoard::padX + spanX * i), (int) (H * TBoard::padY),
                         (int) (W * TBoard::padX + spanX * i), (int) (H * (TBoard::padY + TBoard::perY)));
        painter.drawLine((int) (W * TBoard::padX), (int) (H * padY + spanY * i),
                         (int) (W * (TBoard::padX + TBoard::perX)), (int) (H * padY + spanY * i));
    }

    //绘制棋子
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(0);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);

    for (int x = 0; x < Board::X; x++) {
        for (int y = 0; y < Board::Y; y++) {
            r = this->board.map[x][y];
            if (this->board.map[x][y] != Role::NONE && event->rect().contains(
                    (int) (this->width() * (TBoard::padX + TBoard::perX * x / 14) - TBoard::chessSize / 2.0),
                    (int) (this->height() * (TBoard::padY + TBoard::perY * y / 14) - TBoard::chessSize / 2.0))) {
                std::cout << "x=" << x << ",y=" << y << std::endl;
                painter.setBrush((this->humanFirst && r == Role::HUMAN || !this->humanFirst && r == Role::COMPUTER)
                                 ? this->blackBrush : this->whiteBrush);
                painter.setPen(QPen(Qt::black));
                QRect rect2(
                        (int) (this->width() * (TBoard::padX + TBoard::perX * x / 14) - TBoard::chessSize / 2.0),
                        (int) (this->height() * (TBoard::padY + TBoard::perY * y / 14) - TBoard::chessSize / 2.0),
                        TBoard::chessSize, TBoard::chessSize);
                painter.drawEllipse(rect2);
            }
        }
    }

}

void TBoard::enterEvent(QEnterEvent *event) {
    QApplication::setOverrideCursor(this->clickable?Qt::ArrowCursor:Qt::ForbiddenCursor);
    QWidget::enterEvent(event);
}

void TBoard::leaveEvent(QEvent *event) {
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    QWidget::leaveEvent(event);
}
