#include "flota.h"

Flota::Flota()
{

}

void Flota::slotCargarFlota()
{
    qDebug() << "Cargar flota en flota.cpp";

//    if (ui->tablaFlota->rowCount() != 0){
//        QMessageBox::StandardButton reply;
//          reply = QMessageBox::warning(this, "Advertencia", "Se han encontrado datos en el espacio de trabajo."
//                                                " Si carga una nueva flota los datos se sobreescribirán."
//                                                "¿Desea continuar?",
//                                        QMessageBox::Yes|QMessageBox::No);
//          if (reply == QMessageBox::No) {
//            return;
//          }
//    }
//    ui->tablaFlota->clearContents();
//    ui->tablaFlota->setRowCount(0);
//    auto filename = QFileDialog::getOpenFileName(this, "Abrir datos", QDir::rootPath(), "XML file (*.xml)");
//    if (filename.isEmpty()){
//      return;
//    }
//    QFile file(filename);
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
//      QMessageBox::critical(this, "Error", file.errorString());
//      return;
//    }
//    QDomDocument doc;
//    doc.setContent(&file);
//    file.close();
//    auto root = doc.firstChild().toElement();
//    auto ix = root.firstChild().toElement();
//    while (!ix.isNull()){
//      auto id = ix.attribute("id");
//      auto nombre = ix.firstChild().toElement().text();
//      auto envergadura = ix.firstChild().nextSibling().toElement().text();
//      auto appspd = ix.firstChild().nextSibling().nextSibling().toElement().text();
//      auto lda = ix.firstChild().nextSibling().nextSibling().nextSibling().toElement().text();
//      auto mtow = ix.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text();
//      auto perc = ix.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text();
//      agregaAeronave(Aeronave(id, nombre, envergadura, appspd, lda, mtow, perc));
//      ix = ix.nextSibling().toElement();

//    }
}

void Flota::slotGuardarFlota()
{
    qDebug() << "Guardar flota en flota.cpp";

//    auto filename = QFileDialog::getSaveFileName(this, "Guardar",
//                                                 QDir::rootPath(),
//                                                 "XML file (*.xml)");
//    if (filename.isEmpty()){
//        return;
//    }
//    QDomDocument doc;
//    auto root = doc.createElement("aeronave");
//    doc.appendChild(root);
//    const int rowCount = ui->tablaFlota->rowCount();
//    for (int ix = 0; ix<rowCount; ++ix){
//        Aeronave aeronave(ui->tablaFlota->item(ix, ID)->text(),
//                          ui->tablaFlota->item(ix, NOMBRE)->text(),
//                          ui->tablaFlota->item(ix, ENVERGADURA)->text(),
//                          ui->tablaFlota->item(ix, APPSPD)->text(),
//                          ui->tablaFlota->item(ix, LDA)->text(),
//                          ui->tablaFlota->item(ix, MTOW)->text(),
//                          ui->tablaFlota->item(ix, PORCENTAJE)->text());
//        auto eAeronave = doc.createElement("aeronave");
//        eAeronave.setAttribute("id", aeronave.getId());
//        auto eNombre = doc.createElement("name");
//        auto eEnvergadura = doc.createElement("wspan");
//        auto eApp_spd = doc.createElement("appspd");
//        auto eLda = doc.createElement("lda");
//        auto eMtow = doc.createElement("mtow");
//        auto ePerc = doc.createElement("perc");
//        eNombre.appendChild(doc.createTextNode(aeronave.getNombre()));
//        eEnvergadura.appendChild(doc.createTextNode(aeronave.getEnvergadura()));
//        eApp_spd.appendChild(doc.createTextNode(aeronave.getVel_app()));
//        eLda.appendChild(doc.createTextNode(aeronave.getLda()));
//        eMtow.appendChild(doc.createTextNode(aeronave.getMtow()));
//        ePerc.appendChild(doc.createTextNode(aeronave.getPerc()));
//        eAeronave.appendChild(eNombre);
//        eAeronave.appendChild(eEnvergadura);
//        eAeronave.appendChild(eApp_spd);
//        eAeronave.appendChild(eLda);
//        eAeronave.appendChild(eMtow);
//        eAeronave.appendChild(ePerc);
//        root.appendChild(eAeronave);
//    }
//    QFile file(filename);
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
//        QMessageBox::critical(this, "Error", file.errorString());
//        return;
//    }
//    QTextStream xout(&file);
//    xout << doc.toString();
//    file.flush();
    //    file.close();
}

void Flota::agregaAeronave(const Aeronave &aeronave)
{
//    const int row = ui->tablaFlota->rowCount();
//    ui->tablaFlota->insertRow(row);
//    ui->tablaFlota->setItem(row, ID, new QTableWidgetItem(aeronave.getId()));
//    ui->tablaFlota->setItem(row, NOMBRE, new QTableWidgetItem(aeronave.getNombre()));
//    ui->tablaFlota->setItem(row, ENVERGADURA, new QTableWidgetItem(aeronave.getEnvergadura()));
//    ui->tablaFlota->setItem(row, APPSPD, new QTableWidgetItem(aeronave.getVel_app()));
//    ui->tablaFlota->setItem(row, LDA, new QTableWidgetItem(aeronave.getLda()));
//    ui->tablaFlota->setItem(row, MTOW, new QTableWidgetItem(aeronave.getMtow()));
//    ui->tablaFlota->setItem(row, PORCENTAJE, new QTableWidgetItem(aeronave.getPerc()));
//    for (int i = 0; i < ui->tablaFlota->columnCount() - 1; i++) {
//        QTableWidgetItem* pItem = ui->tablaFlota->item(row, i);
//        pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
//    }
}
