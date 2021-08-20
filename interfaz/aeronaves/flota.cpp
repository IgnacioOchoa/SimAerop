#include "flota.h"

Flota::Flota(const QString &nombre,
             const QList<Aeronave> &listaAeronaves)
{
    if (!listaAeronaves.isEmpty()){
        nNombre = nombre;
        for (int i = 0;i < listaAeronaves.count();++i ){
            this->agregaAeronave(listaAeronaves[i]);
        }
    }
}

void Flota::setNombre(const QString &nombre)
{
    nNombre = nombre;
}

QString Flota::getNombre() const
{
    return nNombre;
}

void Flota::cargadorFlota(QFile &f)
{
    QString name = QFileInfo(f.fileName()).fileName();
    int pos = name.lastIndexOf(QChar('.'));
    this->setNombre(name.left(pos));

    QDomDocument doc;
    doc.setContent(&f);
    auto root = doc.firstChild().toElement();
    auto ix = root.firstChild().toElement();
    while (!ix.isNull()){
      auto id = ix.attribute("id");
      auto nombre = ix.firstChild().toElement().text();
      auto envergadura = ix.firstChild().nextSibling().toElement().text();
      auto appspd = ix.firstChild().nextSibling().nextSibling().toElement().text();
      auto lda = ix.firstChild().nextSibling().nextSibling().nextSibling().toElement().text();
      auto mtow = ix.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text();
      auto perc = ix.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text();
      agregaAeronave(Aeronave(id, nombre, envergadura, appspd, lda, mtow, perc));
      ix = ix.nextSibling().toElement();
    }
}

void Flota::guardadorFlota(QString &filename)
{
    if (nListaAeronaves.isEmpty()) {
        qDebug() << "No hay nada para guardar...";
        return;
    }
    QDomDocument doc;
    auto root = doc.createElement("aeronave");
    doc.appendChild(root);
    for(int i = 0; i < nListaAeronaves.count(); ++i){
        qDebug() << i;
        auto eAeronave = doc.createElement("aeronave");
        eAeronave.setAttribute("id", nListaAeronaves[i].getId());
        auto eNombre = doc.createElement("name");
        auto eEnvergadura = doc.createElement("wspan");
        auto eApp_spd = doc.createElement("appspd");
        auto eLda = doc.createElement("lda");
        auto eMtow = doc.createElement("mtow");
        auto ePerc = doc.createElement("perc");
        eNombre.appendChild(doc.createTextNode(nListaAeronaves[i].getNombre()));
        eEnvergadura.appendChild(doc.createTextNode(nListaAeronaves[i].getEnvergadura()));
        eApp_spd.appendChild(doc.createTextNode(nListaAeronaves[i].getVel_app()));
        eLda.appendChild(doc.createTextNode(nListaAeronaves[i].getLda()));
        eMtow.appendChild(doc.createTextNode(nListaAeronaves[i].getMtow()));
        ePerc.appendChild(doc.createTextNode(nListaAeronaves[i].getPerc()));
        eAeronave.appendChild(eNombre);
        eAeronave.appendChild(eEnvergadura);
        eAeronave.appendChild(eApp_spd);
        eAeronave.appendChild(eLda);
        eAeronave.appendChild(eMtow);
        eAeronave.appendChild(ePerc);
        root.appendChild(eAeronave);
    }
    qDebug() << "Crea un QDomDocument a partir de si mismo";

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Acá debería correr código para devolver Interfaz el error";
        //QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    QTextStream xout(&file);
    xout << doc.toString();
    file.flush();
    file.close();
}

void Flota::agregaAeronave(const Aeronave &aeronave)
{
      nListaAeronaves.append(aeronave);
}
