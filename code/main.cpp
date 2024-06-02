#include <QApplication>
#include "coinmainscene.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    CoinMainScene coinMainScene(nullptr);
    coinMainScene.show();
    return QApplication::exec();
}
