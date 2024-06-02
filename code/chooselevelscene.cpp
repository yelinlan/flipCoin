//
// Created by 夜林蓝 on 2024/4/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChooseLevelScene.h" resolved

#include "chooselevelscene.h"
#include "mypushbutton.h"
#include<QMenuBar>
#include<QPainter>
#include<QDebug>
#include<QTimer>
#include<QLabel>


ChooseLevelScene::ChooseLevelScene(QWidget *parent) :
        QMainWindow(parent) {

    this->resize(320, 588);
    this->setWindowIcon(QPixmap(":/menu/Coin0001.png"));
    setWindowTitle("选择关卡");

    QMenuBar *pBar = menuBar();
    setMenuBar(pBar);
    QMenu *pMenu = pBar->addMenu("开始");
    QAction *pAction = pMenu->addAction("退出");
    connect(pAction, &QAction::triggered, this, &QMainWindow::close);

    auto *pButton = new MyPushButton(":/menu/BackButton.png", ":/menu/BackButtonSelected.png");
    pButton->setParent(this);
    pButton->move(this->width() - pButton->width(), this->height() - pButton->height());
    connect(pButton, &MyPushButton::clicked, this, [=]() {
        qDebug() << "返回";
        QTimer::singleShot(50, [=]() {
            emit this->ChooseSceneBack();
        });
    });

    for (int i = 0; i < 20; ++i) {
        auto *pButton1 = new MyPushButton(":/menu/LevelIcon.png");
        pButton1->setParent(this);
        pButton1->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        const QString &string = QString("您选择的是第%1关！").arg(i + 1);
        qDebug() << string;
        connect(pButton1, &MyPushButton::clicked, this, [=]() {
            playScene = new PlayScene(i + 1);
            QTimer::singleShot(50, this, [=]() {
                playScene->setGeometry(this->geometry());
                this->hide();
                playScene->show();
            });
            connect(playScene, &PlayScene::playSceneBack, this, [=]() {
                this->setGeometry(playScene->geometry());
                this->show();
                delete playScene;
                playScene = nullptr;
            });
        });


        auto *pLabel = new QLabel();
        pLabel->setParent(this);
        pLabel->setText(QString::number(i + 1));
        pLabel->setFixedSize(pButton1->width(), pButton1->height());
        pLabel->move(25 + i % 4 * 70, 130 + i / 4 * 70);
        pLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        pLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    }


}

void ChooseLevelScene::paintEvent(QPaintEvent *event) {
    QPainter qPainter(this);
    QPixmap pix;
    pix.load(":/menu/OtherSceneBg.png");
    qPainter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/menu/Title.png");
    qPainter.drawPixmap(this->width() * 0.5 - pix.width() * 0.5, 30, pix.width(), pix.height(), pix);
}
