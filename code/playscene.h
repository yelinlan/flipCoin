//
// Created by 夜林蓝 on 2024/4/21.
//

#ifndef FLIPCOIN_PLAYSCENE_H
#define FLIPCOIN_PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"


QT_BEGIN_NAMESPACE
namespace Ui { class PlayScene; }
QT_END_NAMESPACE

class PlayScene : public QMainWindow {
Q_OBJECT

public:
    PlayScene(int i);
    explicit PlayScene(QWidget *parent = nullptr);
    int levelNum;
protected:
    void paintEvent(QPaintEvent *event) override;

    int gameArray[4][4];


    MyCoin *btnCoin[4][4];

    bool  isWin;
private:
    Ui::PlayScene *ui;
signals:
    void playSceneBack();
};


#endif //FLIPCOIN_PLAYSCENE_H
