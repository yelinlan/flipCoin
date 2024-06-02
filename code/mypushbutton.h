//
// Created by 夜林蓝 on 2024/4/21.
//

#ifndef FLIPCOIN_MYPUSHBUTTON_H
#define FLIPCOIN_MYPUSHBUTTON_H

#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class MyPushButton; }
QT_END_NAMESPACE

class MyPushButton : public QPushButton {
Q_OBJECT

public:
    explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton( QString normalImgPath, QString pressImgPath="");

    QString normalImgPath;
    QString pressImgPath;

protected:
    void mousePressEvent(QMouseEvent *e) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

public:

    void zoom2();

};


#endif //FLIPCOIN_MYPUSHBUTTON_H
