#include "interfazprincipal.h"

#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont fnt= QApplication::font();
    fnt.setPointSize(10);
    a.setFont(fnt);

    QFile file(":/stylesheets/stylesheetGeneral.qss");
        if(file.open(QFile::ReadOnly)) {
           QString StyleSheet = QLatin1String(file.readAll());
           a.setStyleSheet(StyleSheet);
        }

    InterfazPrincipal w;
    w.show();
    return a.exec();
}
