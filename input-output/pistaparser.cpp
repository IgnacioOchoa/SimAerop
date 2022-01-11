#include "pistaparser.h"

/* Formato archivo Json
 * "pista" : {
 *                   "largo" : xxx,
 *                   "ancho: : xxx,
 *                   "orientacion" : xxx,
 *                   "cabecera1" : "xx",
 *                   "cabecera2" : "xx"
 *                 },
 * "calles rodaje" : [
 *                      { cabecera : "xx",
 *                        posicion : xxx.x,
 *                        angulo   : xx.x,
 *                        ancho    : xxx.x,
 *                        largo    : xxx.x,
 *                        radio    : xxx.x },
 *                      ...
 *                   ],
 * "plataformas" : [
 *                      { coordPerimetro : [[xx.x,xx.x] , [xx.x,xx.x] , ... ]},
 *                      ...
 *                 ]
 */

PistaParser::PistaParser()
{
    pista = QVariantMap();
    rodaje = QVariantMap();
    plataforma = QVariantMap();
    documento = QJsonDocument();
}

void PistaParser::parsearPista(const Pista &p)
{
    QVariantMap vm;
    vm[variablesPista.at(0)] = p.largo;
    vm[variablesPista.at(1)] = p.ancho;
    vm[variablesPista.at(2)] = p.cabecera1;
    vm[variablesPista.at(3)] = p.cabecera2;
    vm[variablesPista.at(4)] = p.orientacion;
    pista["pista"] = vm;
}

void PistaParser::parsearRodaje(const QList<Rodaje> &rod)
{
    QVariantList listaCallesRodaje;
    for(int i = 0; i < rod.size(); i++)
    {
        QVariantMap vm;
        Rodaje r = rod[i];
        vm[variablesRodaje.at(0)] = r.cabecera;
        vm[variablesRodaje.at(1)] = r.posicion;
        vm[variablesRodaje.at(2)] = r.angulo;
        vm[variablesRodaje.at(3)] = r.ancho;
        vm[variablesRodaje.at(4)] = r.largo;
        vm[variablesRodaje.at(5)] = r.radio;
        listaCallesRodaje.append(vm);
    }
    rodaje["calles rodaje"] = listaCallesRodaje;
}

void PistaParser::parsearPlataforma(const QList<Plataforma> &plat)
{
    QVariantList listaPlataformas;
    for(int i=0; i<plat.size(); i++)
    {
        QVariantMap vm;
        Plataforma p = plat[i];

        QVariantList vListaPerimetro;
        for(int j=0; j<p.coordPerimetro.size(); j++)
        {
            vListaPerimetro.append(p.coordPerimetro[j]);
        }

        vm[variablesPlataforma.at(0)] = vListaPerimetro;

        listaPlataformas.append(vm);
    }

    plataforma["plataformas"] = listaPlataformas;
}

void PistaParser::guardarPista(const QString& file, const Pista &p)
{
    parsearPista(p);
    documento.setObject(QJsonObject::fromVariantMap(pista));
    guardar(file);
}

void PistaParser::guardarRodaje(const QString& file, const QList<Rodaje> &rod)
{
    parsearRodaje(rod);
    documento.setObject(QJsonObject::fromVariantMap(rodaje));
    guardar(file);
}

void PistaParser::guardarPlataforma(const QString& file, const QList<Plataforma> &plat)
{
    parsearPlataforma(plat);
    documento.setObject(QJsonObject::fromVariantMap(plataforma));
    guardar(file);
}

void PistaParser::guardarEscenario(const QString& file,const Pista& p, const QList<Rodaje>& rod,
                                   const QList<Plataforma>& plat)
{
    parsearPista(p);
    parsearRodaje(rod);
    parsearPlataforma(plat);

    QJsonObject contenedor;
    contenedor.insert("Pista", QJsonObject::fromVariantMap(pista));
    contenedor.insert("Rodaje", QJsonObject::fromVariantMap(rodaje));
    contenedor.insert("Plataformas", QJsonObject::fromVariantMap(plataforma));
    guardar(file);
}

Pista PistaParser::cargarPista(const QString &file)
{
    if(!cargar(file)) return {0,0,0,"",""};
\
    QJsonObject ob = documento.object();
    if (ob.contains("pista"))
    {
        QJsonObject objetoPista = ob["pista"].toObject();
        foreach(QString st, variablesPista)
        {
            if (!objetoPista.contains(st))
            {
                qInfo() << "El formato del archivo de pista no es correcto";
                return {0,0,0,"",""};
            }
        }

        QVariantMap vm = objetoPista.toVariantMap();
        Pista p = {vm["largo"].toInt(), vm["ancho"].toInt(), vm["orientacion"].toInt(),
                   vm["cabecera1"].toString(), vm["cabecera2"].toString()};

        qInfo() << "Pista cargada correctamente";

        return p;
    }
    else
    {
        qInfo() << "El archivo cargado no es un archivo de pista";
        return {0,0,0,"",""};
    }
}

QList<Rodaje> PistaParser::cargarRodaje(const QString &file)
{
    if(!cargar(file)) return {};
    QJsonObject ob = documento.object();
    if (ob.contains("calles rodaje"))
    {
        QList<Rodaje> listaRodaje;
        QJsonArray arr = ob["calles rodaje"].toArray();
        for(int i=0; i<arr.size(); i++)
        {
            QJsonObject objetoRodaje = arr.at(i).toObject();
            foreach(QString st, variablesRodaje)
            {
                if(!objetoRodaje.contains(st))
                {
                    qInfo() << "El formato del archivo de rodaje no es correcto";
                    return {};
                }
            }

            QVariantMap vm = objetoRodaje.toVariantMap();
            Rodaje rod = {vm["cabecera"].toString(),vm["posicion"].toFloat(),vm["angulo"].toFloat(),
                          vm["ancho"].toInt(),vm["largo"].toInt(),vm["radio"].toInt()};
            listaRodaje.append(rod);
        }

        qInfo() << "Rodaje cargado correctamente";

        return listaRodaje;
    }
    else
    {
        qInfo() << "El archivo cargado no es un archivo de rodaje";
        return {{"",0.0,0.0,0,0,0}};
    }

}

QList<Plataforma> PistaParser::cargarPlataforma(const QString &file)
{
    if(!cargar(file)) return {};
    QJsonObject ob = documento.object();
    if (ob.contains("plataformas"))
    {
        QList<Plataforma> listaPlataformas;
        QJsonArray arr = ob["plataformas"].toArray();
        for(int i=0; i<arr.size(); i++)
        {
            QJsonObject objetoPlataforma = arr.at(i).toObject();
            foreach(QString st, variablesPlataforma)
            {
                if(!objetoPlataforma.contains(st))
                {
                    qInfo() << "El formato del archivo de plataforma no es correcto";
                    return {};
                }
            }

            QVariantMap vm = objetoPlataforma.toVariantMap();
            QList<QPointF> listaPer;
            QList<QPointF> listaPark;

            if (vm["coordPerimetro"].canConvert<QVariantList>())
            {
                QVariantList cper = vm["coordPerimetro"].value<QVariantList>();
                foreach(QVariant varPto, cper)
                {
                    QVariantList coordPto = qvariant_cast<QVariantList>(varPto);
                    QPointF punto = {coordPto[0].toFloat(), coordPto[1].toFloat()};
                    listaPer.append(punto);
                }
            }
            else
            {
                qInfo() << "No se pueden cargar las coordenadas del perimetro";
                listaPer = {};
            }

            Plataforma plat = {listaPer};

            listaPlataformas.append(plat);
        }

        qInfo() << "Plataformas cargadas correctamente";

        return listaPlataformas;
    }
    else
    {
        qInfo() << "El archivo cargado no es un archivo de plataforma";
        return {};
    }
}

void PistaParser::cargarEscenario(const QString& file, Pista& p,
                                  QList<Rodaje>& rod, QList<Plataforma>& plat)
{
    cargar(file);
    p = cargarPista(file);
    rod = cargarRodaje(file);
    plat = cargarPlataforma(file);
}

void PistaParser::guardar(const QString& file)
{
    QFile archivo(file);
    if (!archivo.open(QIODevice::WriteOnly))
    {
        qInfo() << "No se pudo guardar el archivo";
        return;
    }
    archivo.write(documento.toJson());
    archivo.close();
}

bool PistaParser::cargar(const QString &file)
{
    QFile archivo(file);
    if (!archivo.open(QIODevice::ReadOnly))
    {
        qInfo() << "No se pudo cargar el archivo";
        return false;
    }
    QByteArray data = archivo.readAll();
    archivo.close();

    documento = QJsonDocument::fromJson(data);

    if(documento.isNull())
    {
        qInfo() << "El documento se cargo pero es nulo";
        return false;
    }
    else return true;
}


