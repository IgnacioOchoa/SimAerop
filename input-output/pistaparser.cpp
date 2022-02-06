#include "pistaparser.h"

/* Formato archivo Json
 * "pistas" : [
 *                 { "largo" : xxx,
 *                   "ancho: : xxx,
 *                   "orientacion" : xxx,
 *                   "cabecera1" : "xx",
 *                   "cabecera2" : "xx" },
 *                  ...
 *                 ],
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
 *                      { nombre: "xx",
 *                        coordPerimetro : [[xx.x,xx.x] , [xx.x,xx.x] , ... ]},
 *                      ...
 *                 ]
 */

void PistaParser::escribirPista(const QList<Pista> &listaPistas)
{
    QVariantList varListPistas;
    foreach(const Pista& pista, listaPistas)
    {
        QVariantMap vm;
        vm[variablesPista.at(0)] = pista.largo;
        vm[variablesPista.at(1)] = pista.ancho;
        vm[variablesPista.at(2)] = pista.cabecera1;
        vm[variablesPista.at(3)] = pista.cabecera2;
        vm[variablesPista.at(4)] = pista.orientacion;
        varListPistas.append(vm);
    }
    pista["pistas"] = varListPistas;
}

void PistaParser::escribirRodaje(const QList<Rodaje> &listaRodajes)
{
    QVariantList varListRodajes;
    foreach(const Rodaje& rod, listaRodajes)
    {
        QVariantMap vm;
        vm[variablesRodaje.at(0)] = rod.cabecera;
        vm[variablesRodaje.at(1)] = rod.posicion;
        vm[variablesRodaje.at(2)] = rod.angulo;
        vm[variablesRodaje.at(3)] = rod.ancho;
        vm[variablesRodaje.at(4)] = rod.largo;
        vm[variablesRodaje.at(5)] = rod.radio;
        varListRodajes.append(vm);
    }
    rodaje["calles rodaje"] = varListRodajes;
}

void PistaParser::escribirPlataforma(const QList<Plataforma> &listaPlataformas)
{
    QVariantList varListaPlataformas;
    foreach(const Plataforma& plat, listaPlataformas)
    {
        QVariantMap vm;
        vm[variablesPlataforma.at(0)] = plat.nombre;

        QVariantList vListaPerimetro;
        foreach(QPointF pto, plat.coordPerimetro)
        {
            vListaPerimetro.append(pto);
        }

        vm[variablesPlataforma.at(1)] = vListaPerimetro;
        varListaPlataformas.append(vm);
    }
    plataforma["plataformas"] = varListaPlataformas;
}

void PistaParser::guardarPista(const QString& file, const QList<Pista> &p)
{
    escribirPista(p);
    documento.setObject(QJsonObject::fromVariantMap(pista));
    guardarArchivo(file);
}

void PistaParser::guardarRodaje(const QString& file, const QList<Rodaje> &rod)
{
    escribirRodaje(rod);
    documento.setObject(QJsonObject::fromVariantMap(rodaje));
    guardarArchivo(file);
}

void PistaParser::guardarPlataforma(const QString& file, const QList<Plataforma> &plat)
{
    escribirPlataforma(plat);
    documento.setObject(QJsonObject::fromVariantMap(plataforma));
    guardarArchivo(file);
}

void PistaParser::guardarEscenario(const QString& file,const QList<Pista>& p, const QList<Rodaje>& rod,
                                   const QList<Plataforma>& plat)
{
    escribirPista(p);
    escribirRodaje(rod);
    escribirPlataforma(plat);

    QJsonObject contenedor;
    contenedor.insert("Pista", QJsonObject::fromVariantMap(pista));
    contenedor.insert("Rodaje", QJsonObject::fromVariantMap(rodaje));
    contenedor.insert("Plataformas", QJsonObject::fromVariantMap(plataforma));
    documento.setObject(contenedor);
    guardarArchivo(file);
}

QList<Pista> PistaParser::cargarPista(const QString &file)
{
    if(!cargarArchivo(file)) return {pistaError};
\
    QJsonObject ob = documento.object();
    if (ob.contains("pistas"))
    {
        QList<Pista> listaPistas;
        QJsonArray arrPista = ob["pistas"].toArray();

        foreach(QJsonValue val, arrPista)
        {
            QJsonObject objetoPista = val.toObject();
            foreach(QString st, variablesPista)
            {
                if (!objetoPista.contains(st))
                {
                    qInfo() << "El formato JSON del archivo de pista no es correcto";
                    return {pistaError};
                }
            }
            QVariantMap vm = objetoPista.toVariantMap();
            Pista p = {vm["largo"].toInt(), vm["ancho"].toInt(), vm["orientacion"].toInt(),
                       vm["cabecera1"].toString(), vm["cabecera2"].toString()};
            listaPistas.append(p);
        }
        qInfo() << "Pista cargada correctamente";
        return listaPistas;
    }
    else
    {
        qInfo() << "El archivo cargado no es un archivo de pista";
        return {pistaError};
    }
}

QList<Rodaje> PistaParser::cargarRodaje(const QString &file)
{
    if(!cargarArchivo(file)) return {rodajeError};
    QJsonObject ob = documento.object();
    if (ob.contains("calles rodaje"))
    {
        QList<Rodaje> listaRodaje;
        QJsonValue valArrRodaje = ob["calles rodaje"];
        if(!valArrRodaje.isArray()) {
            qInfo() << "El formato JSON de las calles de rodaje no es correcto";
            return {rodajeError};
        }
        QJsonArray arrRodaje = valArrRodaje.toArray();

        foreach(QJsonValue valRod, arrRodaje)
        {
            QJsonObject objetoRodaje = valRod.toObject();
            foreach(QString st, variablesRodaje)
            {
                if(!objetoRodaje.contains(st))
                {
                    qInfo() << "El formato JSON del archivo de rodaje no es correcto";
                    return {rodajeError};
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
        return {rodajeError};
    }
}

QList<Plataforma> PistaParser::cargarPlataforma(const QString &file)
{
    if(!cargarArchivo(file)) return {plataformaError};
    QJsonObject ob = documento.object();
    if (ob.contains("plataformas"))
    {
        QList<Plataforma> listaPlataformas;
        QJsonArray arrPlataformas = ob["plataformas"].toArray();
        foreach(QJsonValue val, arrPlataformas)
        {
            Plataforma plat;
            QJsonObject objetoPlataforma = val.toObject();
            foreach(QString st, variablesPlataforma)
            {
                if(!objetoPlataforma.contains(st))
                {
                    qInfo() << "El formato JSON del archivo de plataforma no es correcto";
                    return {plataformaError};
                }
            }

            plat.nombre = objetoPlataforma["nombre"].toString();
            QJsonValue valPerimetro = objetoPlataforma["coordPerimetro"];
            if(!valPerimetro.isArray()) {
                qInfo() << "No se pueden cargar las coordenadas del perimetro";
                return {plataformaError};
            }
            QJsonArray arrPtos = objetoPlataforma["coordPerimetro"].toArray();
            QPolygonF listaPer;

            foreach(QJsonValue valPto, arrPtos)
            {
                    QVariant varPto = valPto.toVariant();
                    if(!varPto.canConvert(QMetaType::QVariantList)) {
                        qInfo() << "No se pueden convertir los puntos de perimetro de plataforma";
                        return {plataformaError};
                    }
                    QVariantList variantPto = valPto.toVariant().toList();
                    if(variantPto.size() != 2) {
                        qInfo() << "Error en las coordenadas x-y de los puntos de plataforma";
                        return {plataformaError};
                    }
                    QPointF punto  = {variantPto[0].toFloat(), variantPto[1].toFloat()};
                    listaPer.append(punto);
            }
            plat.coordPerimetro = listaPer;
            listaPlataformas.append(plat);
        }
        qInfo() << "Plataformas cargadas correctamente";
        return listaPlataformas;
    }
    else
    {
        qInfo() << "El archivo cargado no es un archivo de plataforma";
        return {plataformaError};
    }
}

void PistaParser::cargarEscenario(const QString& file, QList<Pista>& p,
                                  QList<Rodaje>& rod, QList<Plataforma>& plat)
{
    p = cargarPista(file);
    rod = cargarRodaje(file);
    plat = cargarPlataforma(file);
}

void PistaParser::guardarArchivo(const QString& file)
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

bool PistaParser::cargarArchivo(const QString &file)
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
        qInfo() << "El documento se cargó pero es nulo";
        return false;
    }
    else return true;
}


