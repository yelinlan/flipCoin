//
// Created by 夜林蓝 on 2024/4/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CoinMainScene.h" resolved

#include "coinmainscene.h"
#include "ui_CoinMainScene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QTimer>


CoinMainScene::CoinMainScene(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::CoinMainScene) {
    ui->setupUi(this);

    setFixedSize(320, 588);
    setWindowIcon(QIcon(":/menu/Coin0001.png"));
    setWindowTitle("翻金币");
    connect(ui->actionquit, &QAction::triggered, this, &QMainWindow::close);


    auto *pButton = new MyPushButton(":/menu/MenuSceneStartButton.png");
    pButton->setParent(this);
    pButton->move(this->width() * 0.5 - pButton->width() * 0.5, this->height() * 0.7);

    chooseLevelScene = new ChooseLevelScene();

    connect(pButton, &MyPushButton::clicked, [=]() {
        pButton->zoom2();
        QTimer::singleShot(50, this, [=]() {
            chooseLevelScene->setGeometry(this->geometry());
            this->hide();
            chooseLevelScene->show();
        });
    });

    connect(chooseLevelScene, &ChooseLevelScene::ChooseSceneBack, this, [=](){
        this->setGeometry(chooseLevelScene->geometry());
        chooseLevelScene->hide();
        this->show();
    });


}

CoinMainScene::~CoinMainScene() {
    delete ui;
}

void CoinMainScene::paintEvent(QPaintEvent *event) {
    QPainter qPainter(this);
    QPixmap pix;
    pix.load(":/menu/PlayLevelSceneBg.png");
    qPainter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/menu/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    qPainter.drawPixmap(10, 30, pix);
}
