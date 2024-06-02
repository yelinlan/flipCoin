//
// Created by 夜林蓝 on 2024/4/21.
//

#ifndef FLIPCOIN_MYCOIN_H
#define FLIPCOIN_MYCOIN_H

#include <QPushButton>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MyCoin; }
QT_END_NAMESPACE

class MyCoin : public QPushButton {
Q_OBJECT

public:
    explicit MyCoin(QString btnImg);

    QString btnImg;

    int posX;
    int posY;
    bool flag;
    bool  isWin = false;

    void changeFlag();

    QTimer *timer1;
    QTimer *timer2;

    int min = 1;
    int max = 8;

    bool animation = false;



protected:
    void mousePressEvent(QMouseEvent *e) override;


};


#endif //FLIPCOIN_MYCOIN_H
