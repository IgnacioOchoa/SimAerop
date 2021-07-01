#include "interfazprincipal.h"
#include "kernel.h"

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

    Kernel* k = new Kernel();
    InterfazPrincipal w(k);
    w.setMinimumSize(1280,720);
    w.show();
    return a.exec();
}
