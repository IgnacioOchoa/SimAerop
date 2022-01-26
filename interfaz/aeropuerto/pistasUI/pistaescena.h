#ifndef PISTAESCENA_H
#define PISTAESCENA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsRectItem>
#include "../dibujo/cotagrafica.h"
#include "../dibujo/lineaumbral.h"
#include "../../../estructuras-datos/elementosaerop.h"

class PistaEscena : public QGraphicsScene
{
    Q_OBJECT
public:
    PistaEscena(QObject* ob = nullptr);
    enum class Lado {IZQ, DER};
    void graficarPista(Pista p);
    void mostrarCotas(bool);
    void limpiar();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    enum class Umbral {UMBRAL1,UMBRAL2};

signals:
    void sigLineaUmbralMovida(Umbral umbral, int nuevaPos);

public slots:
    void slotUmbralActivado(Umbral um, bool estado);
    void slotUmbralModificado(Umbral umbral, int valor);
    void slotLineaUmbralMovida(int pos);
    void slotSetLimUmbrales(int limUmbral1, int limUmbral2);

private:

    void crearRectanguloPista();
    void crearCotas();
    void crearLineasUmbral();
    void crearZonasExt();
    void actualizarLineasUmbral();

    QList<CotaGrafica*> listaCotas;
    QGraphicsRectItem* grRectItm;
    CotaGrafica* cota1;
    CotaGrafica* cota2;
    CotaGrafica* cota3;
    CotaGrafica* cota4;
    LineaUmbral* lineaUmbral1;
    LineaUmbral* lineaUmbral2;
    bool umbral1Visible;
    bool umbral2Visible;
    bool cotasVisibles;
    Pista pistaGraficada;
    QRect rectPista;

    bool escenaLimpia;
};

#endif // PISTAESCENA_H
