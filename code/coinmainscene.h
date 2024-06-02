//
// Created by 夜林蓝 on 2024/4/21.
//

#ifndef FLIPCOIN_COINMAINSCENE_H
#define FLIPCOIN_COINMAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class CoinMainScene; }
QT_END_NAMESPACE

class CoinMainScene : public QMainWindow {
Q_OBJECT

public:
    explicit CoinMainScene(QWidget *parent = nullptr);

    ~CoinMainScene() override;

    ChooseLevelScene * chooseLevelScene= nullptr;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::CoinMainScene *ui;
};


#endif //FLIPCOIN_COINMAINSCENE_H
