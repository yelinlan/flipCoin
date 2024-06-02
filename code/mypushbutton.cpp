//
// Created by 夜林蓝 on 2024/4/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MyPushButton.h" resolved

#include "mypushbutton.h"

#include<QPixmap>
#include<QDebug>
#include<QPropertyAnimation>

MyPushButton::MyPushButton(QWidget *parent) :
        QPushButton(parent) {
}

MyPushButton::MyPushButton(QString normalImgPath, QString pressImgPath) {

    this->normalImgPath = normalImgPath;
    this->pressImgPath = pressImgPath;

    QPixmap pixmap;
    bool b = pixmap.load(normalImgPath);
    if (!b) {
        qDebug() << "图片加载失败！";
        return;
    }

    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));
}

void MyPushButton::zoom2() {
    auto *pAnimation = new QPropertyAnimation(this, "geometry");
    pAnimation->setDuration(200);
    pAnimation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    pAnimation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    pAnimation->setEasingCurve(QEasingCurve::OutBounce);
    pAnimation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e) {
    if (!pressImgPath.isEmpty()) {
        qDebug() << "mousePressEvent！";
        QPixmap pixmap;
        bool b = pixmap.load(pressImgPath);
        if (!b) {
            qDebug() << "图片加载失败！";
            return;
        }

        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e) {
    if (!pressImgPath.isEmpty()) {
        qDebug() << "mouseReleaseEvent！";
        QPixmap pixmap;
        bool b = pixmap.load(normalImgPath);
        if (!b) {
            qDebug() << "图片加载失败！";
            return;
        }

        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    QPushButton::mouseReleaseEvent(e);
}
