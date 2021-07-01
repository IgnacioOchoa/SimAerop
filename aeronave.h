#ifndef AERONAVE_H
#define AERONAVE_H

#include<QString>

class Aeronave
{
public:
    Aeronave(const QString &id = "",
             const QString &nombre = "",
             const QString &envergadura = "",
             const QString &vel_app = "",
             const QString &lda = "",
             const QString &mtow = "",
             const QString &perc = "");
    void setId(const QString &id);
    void setNombre(const QString &nombre);
    void setEnvergadura(const QString &envergadura);
    void setVel_app(const QString &vel_app);
    void setLda(const QString &lda);
    void setMtow(const QString &mtow);
    void setPerc(const QString &perc);
    QString getId() const;
    QString getNombre() const;
    QString getEnvergadura() const;
    QString getVel_app() const;
    QString getLda() const;
    QString getMtow() const;
    QString getPerc() const;
private:
    QString nId;
    QString nNombre;
    QString nEnvergadura;
    QString nVel_app;
    QString nLda;
    QString nMtow;
    QString nPerc;
};

#endif // AERONAVE_H
