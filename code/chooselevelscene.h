//
// Created by 夜林蓝 on 2024/4/21.
//

#ifndef FLIPCOIN_CHOOSELEVELSCENE_H
#define FLIPCOIN_CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChooseLevelScene; }
QT_END_NAMESPACE

class ChooseLevelScene : public QMainWindow {
Q_OBJECT

public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    PlayScene *playScene;

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void ChooseSceneBack();

private:
    Ui::ChooseLevelScene *ui{};

};


#endif //FLIPCOIN_CHOOSELEVELSCENE_H
