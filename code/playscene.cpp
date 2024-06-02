//
// Created by 夜林蓝 on 2024/4/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PlayScene.h" resolved

#include "playscene.h"
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QPropertyAnimation>


PlayScene::PlayScene(QWidget *parent) :
        QMainWindow(parent) {
}

PlayScene::PlayScene(int i) {
    this->levelNum = i;
    const QString &string = QString("您已进入第%1关！").arg(this->levelNum);
    qDebug() << string;

    this->resize(320, 588);
    this->setWindowIcon(QPixmap(":/menu/Coin0001.png"));
    setWindowTitle(QString("翻金币 第%1关！").arg(this->levelNum));

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
            emit this->playSceneBack();
        });
    });

    auto *pLabel = new QLabel(this);
    QFont qFont;
    qFont.setFamily("华文新魏");
    qFont.setPointSize(20);
    pLabel->setFont(qFont);
    pLabel->setText(QString("LEVEL: %1").arg(this->levelNum));
    pLabel->setGeometry(30, this->height() - 50, 120, 50);

    dataConfig config;
    for (int j = 0; j < 4; ++j) {
        for (int k = 0; k < 4; ++k) {
            this->gameArray[j][k] = config.mData[this->levelNum][j][k];
        }
    }


    auto *pQLabel = new QLabel();
    QPixmap pix;
    pix.load(":/menu/LevelCompletedDialogBg.png");
    pQLabel->setGeometry(0, 0, pix.width(), pix.height());
    pQLabel->setPixmap(pix);
    pQLabel->setParent(this);
    pQLabel->move((this->width()-pix.width())*0.5,-pix.height());

    for (int j = 0; j < 4; ++j) {
        for (int k = 0; k < 4; ++k) {
            auto *pLabel1 = new QLabel(this);
            const QPixmap &pixmap = QPixmap(":/menu/BoardNode.png");
            pLabel1->setGeometry(0, 0, pixmap.width(), pixmap.height());
            pLabel1->setPixmap(pixmap);
            pLabel1->move(57 + 50 * j, 200 + 50 * k);
            QString str = this->gameArray[j][k] == 1 ? ":/menu/Coin0001.png" : ":/menu/Coin0008.png";
            auto *pCoin = new MyCoin(str);
            pCoin->setParent(this);
            pCoin->move(59 + 50 * j, 204 + 50 * k);
            pCoin->posX = j;
            pCoin->posY = k;
            pCoin->flag = this->gameArray[j][k];
            this->btnCoin[j][k] = pCoin;
            connect(pCoin, &MyCoin::clicked, [=]() {
                for (auto &l: this->btnCoin) {
                    for (auto &m: l) {
                        m->isWin = true;
                    }
                }
                pCoin->changeFlag();
                this->gameArray[j][k] = !this->gameArray[j][k];
                qDebug() << j << "   " << k << "  ;";
                QTimer::singleShot(300, this, [=]() {
                    if (j > 0) {
                        btnCoin[j - 1][k]->changeFlag();
                        this->gameArray[j - 1][k] = !this->gameArray[j - 1][k];
                    }
                    if (j < 3) {
                        btnCoin[j + 1][k]->changeFlag();
                        this->gameArray[j + 1][k] = !this->gameArray[j + 1][k];
                    }
                    if (k > 0) {
                        btnCoin[j][k - 1]->changeFlag();
                        this->gameArray[j][k - 1] = !this->gameArray[j][k - 1];
                    }
                    if (k < 3) {
                        btnCoin[j][k + 1]->changeFlag();
                        this->gameArray[j][k + 1] = !this->gameArray[j][k + 1];
                    }
                    for (auto &l: this->btnCoin) {
                        for (auto &m: l) {
                            m->isWin = false;
                        }
                    }
                    this->isWin = true;
                    for (auto &l: this->btnCoin) {
                        for (auto &m: l) {
                            if (!m->flag) {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if (this->isWin) {
                        qDebug() << "胜利了！";
                        for (auto &l: this->btnCoin) {
                            for (auto &m: l) {
                                m->isWin = true;
                            }
                        }

                        auto *pAnimation = new QPropertyAnimation(pQLabel, "geometry");
                        pAnimation->setDuration(1000);
                        pAnimation->setStartValue(QRect(pQLabel->x(), pQLabel->y(), pQLabel->width(), pQLabel->height()));
                        pAnimation->setEndValue(QRect(pQLabel->x(), pQLabel->y()+114, pQLabel->width(), pQLabel->height()));
                        pAnimation->setEasingCurve(QEasingCurve::OutBounce);
                        pAnimation->start();
                    }


                });

            });

        }
    }

}

void PlayScene::paintEvent(QPaintEvent *event) {
    QPainter qPainter(this);
    QPixmap pix;
    pix.load(":/menu/PlayLevelSceneBg.png");
    qPainter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/menu/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    qPainter.drawPixmap(10, 30, pix);
}
