//
// Created by 夜林蓝 on 2024/4/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MyCoin.h" resolved

#include "mycoin.h"


MyCoin::MyCoin(QString btnImg) {
    this->btnImg = btnImg;

    QPixmap pixmap;
    bool b = pixmap.load(btnImg);
    if (!b) {
        qDebug() << "图片加载失败！" << btnImg;
        return;
    }
    qDebug() << "图片" << btnImg;

    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1, &QTimer::timeout, [=]() {
        QPixmap pix;
        qDebug() << this->posX << "  " << this->posY << ";正面" << "timer1！" << this->flag << "  "
                 << QString(":/menu/Coin000%1.png").arg(this->min);
        bool b = pix.load(QString(":/menu/Coin000%1.png").arg(this->min++));
        if (!b) {
            qDebug() << "图片加载失败！" << pix;
            return;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        if (this->min > this->max) {
            this->min = 1;
            this->animation = false;
            timer1->stop();
        }
    });
    connect(timer2, &QTimer::timeout, [=]() {
        QPixmap pix;
        qDebug() << this->posX << "  " << this->posY << ";反面" << "timer2！" << this->flag << "  "
                 << QString(":/menu/Coin000%1.png").arg(this->max);
        bool b = pix.load(QString(":/menu/Coin000%1.png").arg(this->max--));
        if (!b) {
            qDebug() << "图片加载失败！" << pix;
            return;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        if (this->max < this->min) {
            this->max = 8;
            this->animation = false;
            timer2->stop();
        }
    });

}

void MyCoin::changeFlag() {
    this->animation = true;
    if (this->flag) {
        timer1->start(30);
    } else {
        timer2->start(30);
    }
    this->flag = !this->flag;

}

void MyCoin::mousePressEvent(QMouseEvent *e) {
    if (!animation&&!isWin) {
        QAbstractButton::mousePressEvent(e);
    }
}
