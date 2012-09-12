/*
   Pure Media Server - A Media Server Sotfware for stage and performing
   Copyright (C) 2012  Santiago Noreña
   belfegor <AT> gmail <DOT> com

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "PureMediaServer.h"
#include "CITPDefines.h"
#include "MSEXDefines.h"
#include "citp-lib.h"
#include "MediaServer.h"

#include <QtDebug>
#include <QtNetwork>
#include <QFileInfo>
#include <QFileDialog>

#define PDPORT 9195

struct conf
{
bool window;
quint16 winpositionx;
quint16 winpositiony;
quint16 winsizex;
quint16 winsizey;
quint16 layer1Add;
bool layer1Check;
quint16 layer2Add;
bool layer2Check;
quint16 layer3Add;
bool layer3Check;
quint16 layer4Add;
bool layer4Check;
quint16 layer5Add;
bool layer5Check;
quint16 layer6Add;
bool layer6Check;
quint16 layer7Add;
bool layer7Check;
quint16 layer8Add;
bool layer8Check;
bool dmx;
quint8 universe;
quint8 ipadd1;
quint8 ipadd2;
quint8 ipadd3;
quint8 ipadd4;
QString path;
};

PureMediaServer::PureMediaServer(QWidget *parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  // Creamos el socket para la conexión a Pure Data
  m_pd_socket = new QTcpSocket(this);
  Q_CHECK_PTR(m_pd_socket);
  // Conectamos a Pure Data
  on_connectPDButton_clicked();

  // Creamos el objeto CITP y el peer information socket
  m_citp = new CITPLib(this);
  Q_CHECK_PTR(m_citp);
  quint32 ipadd = ui.ipAddress1->value();
  ipadd << 8;
  ipadd = ipadd + ui.ipAddress2->value();
  ipadd << 8;
  ipadd = ipadd + ui.ipAddress3->value();
  ipadd << 8;
  ipadd = ipadd + ui.ipAddress4->value();
  if (!m_citp->createPeerInformationSocket(NAME, STATE, ipadd))
      {
      qDebug("CreatePeerInformationSocket failed");
  }

  // Creamos el mediaserver
  m_mediaserver = new MediaServer(this);
  Q_CHECK_PTR(m_mediaserver);
  // Conectamos los menus
  connect(ui.actionOpen_conf, SIGNAL(triggered()), this, SLOT(open()));
  connect(ui.actionSave_conf, SIGNAL(triggered()), this, SLOT(save()));
  // Cargamos la configuración
}

PureMediaServer::~PureMediaServer()
{
    qDebug() << "Exit";
    m_pd_socket->disconnectFromHost();
}

void PureMediaServer::close()
{
qDebug() << "Close";
}

void PureMediaServer::on_updateButton_clicked()
{
    // Chequeamos si existe el path a los medias
    QDir dir(m_mediaserver->getpath());
     if (!dir.exists())
     {
         qWarning("Cannot find the media directory");
         return;
     }
     ui.textEdit->appendPlainText("Actualizando biblioteca de medias. Esto puede llevar un rato");
     if (!m_mediaserver->updatemedia())
     {
         qWarning("Cannot explore the media");
         return;
     }
}

void PureMediaServer::on_connectPDButton_clicked(){
    if (m_pd_socket->isOpen()){
            //qDebug()<<"PD Socket already open";
            //ui.textEdit->appendPlainText("PD Socket already open");
            m_pd_socket->disconnectFromHost();
    }
    QString desc = tr("Conectando con Pure Data on port %1").arg(PDPORT);
    ui.textEdit->appendPlainText(desc);
    qDebug()<<"Conectando a pure data on "<<PDPORT;
    m_pd_socket->connectToHost(QHostAddress::LocalHost, PDPORT);
    disconnect(m_pd_socket, SIGNAL(connected()),this, SLOT(newconexion()));
    disconnect(m_pd_socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(m_pd_socket, SIGNAL(connected()),this, SLOT(newconexion()));
    connect(m_pd_socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(m_pd_socket, SIGNAL(disconnected()), this, SLOT(pdDisconnected()));
}

void PureMediaServer::pdDisconnected()
{
    qDebug() << "Pure Data Disconnected";
                ui.textEdit->appendPlainText("Pure Data Disconected!");
    m_pd_socket->disconnectFromHost();
}

void PureMediaServer::handleReadyRead()
{
    qDebug() << "Info arrives...";
}

bool PureMediaServer::sendPacket(const char *buffer, int bufferLen)
{
 if (!m_pd_socket) {
    return false;
 }
 if (QAbstractSocket::ConnectedState != m_pd_socket->state())
 {
    qDebug() << "pdInterface::sendPacket() - Socket not connected";
    return false;
 }
 if (bufferLen != m_pd_socket->write((const char*)buffer, bufferLen))
 {
    qDebug() << "pdInterface::sendPacket() write failed:" << m_pd_socket->error();
    return false;
 }
 return true;
}

void PureMediaServer::newconexion()
    {
    ui.textEdit->appendPlainText("Conectado a Pure Data");
    qDebug() << "Connected to PD";
    sendconf();
    }

void PureMediaServer::sendconf()
{
    qDebug() << "Sending configuration to PD";
    int bufferLen = sizeof(struct conf) + pathmedia.size();
    char *buffer = new char[bufferLen];
    memset(buffer, 0, bufferLen);
    conf *packet = (conf *)buffer;
    packet->window = ui.window->checkState();
    packet->winpositionx = ui.winpositionx->value();
    packet->winpositiony = ui.winpositiony->value();
    packet->winsizex = ui.winsizex->value();
    packet->winsizey = ui.winsizey->value();
    packet->layer1Add = ui.layer1Add->value();
    packet->layer1Check = ui.layer1Check->checkState();
    packet->layer2Add = ui.layer2Add->value();
    packet->layer2Check = ui.layer2Check->checkState();
    packet->layer3Add = ui.layer3Add->value();
    packet->layer3Check = ui.layer3Check->checkState();
    packet->layer4Add = ui.layer4Add->value();
    packet->layer4Check = ui.layer4Check->checkState();
    packet->layer5Add = ui.layer5Add->value();
    packet->layer5Check = ui.layer5Check->checkState();
    packet->layer6Add = ui.layer6Add->value();
    packet->layer6Check = ui.layer6Check->checkState();
    packet->layer7Add = ui.layer7Add->value();
    packet->layer7Check = ui.layer7Check->checkState();
    packet->layer8Add = ui.layer8Add->value();
    packet->layer8Check = ui.layer8Check->checkState();
    packet->dmx = ui.readDMX->checkState();
    packet->universe = ui.universe->value();
    packet->ipadd1 = ui.ipAddress1->value();
    packet->ipadd2 = ui.ipAddress2->value();
    packet->ipadd3 = ui.ipAddress3->value();
    packet->ipadd4 = ui.ipAddress4->value();
    int offset = sizeof (struct conf) - 4;
    memcpy(buffer+offset, pathmedia.toAscii().constData(), pathmedia.size());
    if (!sendPacket (buffer, bufferLen))
    {
        qDebug() << "Can not send configuration to PD";
        ui.textEdit->appendPlainText(" Can not send configuration to PD");
    }
}

void PureMediaServer::on_window_stateChanged(int state)
{
    if ((state == 2)) {
       ui.textEdit->appendPlainText("Creando Ventana");
       QString desc("0001 0001;");
       if (!sendPacket(desc.toAscii().constData(),desc.size()))
       {
        ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
       }
    }
    if ((state == 0)) {
          ui.textEdit->appendPlainText("Destruyendo Ventana");
          QString desc("0001 0000;");
          if (!sendPacket(desc.toAscii().constData(),desc.size()))
          {
           ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
          }
   }
}

void PureMediaServer::on_winpositionx_valueChanged()
{
    int x = ui.winpositionx->value();
    QString desc = tr("0002 %1;").arg(x);
    if (!sendPacket(desc.toAscii().constData(),desc.size()))
            {
             ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
            }

}

void PureMediaServer::on_winpositiony_valueChanged()
{
    int x = ui.winpositiony->value();
    QString desc = tr("3 %1;").arg(x);
    if (!sendPacket(desc.toAscii().constData(),desc.size()))
            {
             ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
            }

}

void PureMediaServer::on_winsizex_valueChanged()
{
    int x = ui.winsizex->value();
    QString desc = tr("4 %1;").arg(x);
    if (!sendPacket(desc.toAscii().constData(),desc.size()))
            {
             ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
            }

}

void PureMediaServer::on_winsizey_valueChanged()
{
    int x = ui.winsizey->value();
    QString desc = tr("5 %1;").arg(x);
    if (!sendPacket(desc.toAscii().constData(),desc.size()))
            {
             ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
            }
}

void PureMediaServer::on_layer1Check_stateChanged (int state)
{
    if ((state == 0))
    {
        QString desc("0011 0000;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        return;
    }
    if ((state == 2))
    {
        on_layer1Add_valueChanged();
    }
}

void PureMediaServer::on_layer1Add_valueChanged()
{
   if (ui.layer1Check->isChecked()){
        int x = ui.layer1Add->value();
        QString desc = tr("0011 %1;").arg(x);
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
           {
            ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
           }
    }
}

void PureMediaServer::on_layer2Check_stateChanged (int state)
{
    if ((state == 0))
    {
        QString desc("0012 0000;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        return;
    }
    if ((state == 2))
    {
        on_layer2Add_valueChanged();
    }
}

void PureMediaServer::on_layer2Add_valueChanged()
{
   if (ui.layer2Check->isChecked()){
   int x = ui.layer2Add->value();
   QString desc = tr("0012 %1;").arg(x);
   if (!sendPacket(desc.toAscii().constData(),desc.size()))
           {
            ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
           }
   }
}

void PureMediaServer::on_layer3Check_stateChanged (int state)
{
    if ((state == 0))
    {
        QString desc("0013 0000;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        return;
    }
    if ((state == 2))
    {
        on_layer3Add_valueChanged();
    }
}

void PureMediaServer::on_layer3Add_valueChanged()
{
   if (ui.layer3Check->isChecked()){
   int x = ui.layer3Add->value();
   QString desc = tr("0013 %1;").arg(x);
   if (!sendPacket(desc.toAscii().constData(),desc.size()))
           {
            ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
           }
  }
}

void PureMediaServer::on_layer4Check_stateChanged (int state)
{
    if ((state == 0))
    {
        QString desc("0014 0000;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        return;
    }
    if ((state == 2))
    {
        on_layer4Add_valueChanged();
    }
}

void PureMediaServer::on_layer4Add_valueChanged()
{
   if (ui.layer4Check->isChecked()){
   int x = ui.layer4Add->value();
   QString desc = tr("0014 %1;").arg(x);
   if (!sendPacket(desc.toAscii().constData(),desc.size()))
           {
            ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
           }
   }
}

void PureMediaServer::on_layer5Check_stateChanged (int state)
{
    if ((state == 0))
    {
        QString desc("0015 0000;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        return;
    }
    if ((state == 2))
    {
        on_layer5Add_valueChanged();
    }
}

void PureMediaServer::on_layer5Add_valueChanged()
{
   if (ui.layer5Check->isChecked()){
   int x = ui.layer5Add->value();
   QString desc = tr("0015 %1;").arg(x);
   if (!sendPacket(desc.toAscii().constData(),desc.size()))
           {
            ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
           }
    }
}

void PureMediaServer::on_layer6Check_stateChanged (int state)
{
    if ((state == 0))
    {
        QString desc("0016 0000;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        return;
    }
    if ((state == 2))
    {
        on_layer6Add_valueChanged();
    }
}

void PureMediaServer::on_layer6Add_valueChanged()
{
   if (ui.layer6Check->isChecked()){
   int x = ui.layer6Add->value();
   QString desc = tr("0016 %1;").arg(x);
   if (!sendPacket(desc.toAscii().constData(),desc.size()))
           {
            ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
           }
   }
}

void PureMediaServer::on_layer7Check_stateChanged (int state)
{
    if ((state == 0))
    {
        QString desc("0017 0000;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        return;
    }
    if ((state == 2))
    {
        on_layer7Add_valueChanged();
    }
}

void PureMediaServer::on_layer7Add_valueChanged()
{
   if (ui.layer7Check->isChecked()){
   int x = ui.layer7Add->value();
   QString desc = tr("0017 %1;").arg(x);
   if (!sendPacket(desc.toAscii().constData(),desc.size()))
           {
            ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
           }
   }
}

void PureMediaServer::on_layer8Check_stateChanged (int state)
{
    if ((state == 0))
    {
        QString desc("0018 0000;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        return;
    }
    if ((state == 2))
    {
        on_layer8Add_valueChanged();
    }
}

void PureMediaServer::on_layer8Add_valueChanged()
{
   if (ui.layer8Check->isChecked()){
   int x = ui.layer8Add->value();
   QString desc = tr("0018 %1;").arg(x);
   if (!sendPacket(desc.toAscii().constData(),desc.size()))
           {
            ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
           }
  }
}

void PureMediaServer::on_readDMX_stateChanged(int state)
{
    if ((state == 0)) {
        QString desc("0020 0000;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        return;
    }
    if ((state == 2))
    {
        int x = ui.universe->value();
        QString desc = tr("0021 %1;").arg(x);
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
        desc = tr("0020 0001;");
        if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                }
       return;
    }
 }

void PureMediaServer::on_ChangePath_clicked()
{

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
    QString file = fileNames.at(0);
    QString desc = tr("0000 0000 %1;").arg(file);
    if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                return;
                }
    pathmedia = file;
    desc = tr("Media Path Changed to: %1").arg(pathmedia);
    ui.textEdit->appendPlainText(desc);
}

void PureMediaServer::open()
{
    qDebug()<<"Opening...";
    QFile file("pms.conf");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
        ui.textEdit->appendPlainText("Can not find the conf file");
        return;
     }
    unsigned char * fileconf = new unsigned char[file.size()];
    memset(fileconf, 0, file.size());
    fileconf = file.map(0x00, file.size());
    if (fileconf == 0){
        qDebug() << "Cannot map the file";
        return;
    }
    conf *packet = (conf *)fileconf;
    ui.window->setChecked(packet->window);
    ui.winpositionx->setValue(packet->winpositionx);
    ui.winpositiony->setValue(packet->winpositiony);
    ui.winsizex->setValue(packet->winsizex);
    ui.winsizey->setValue(packet->winsizey);
    ui.layer1Add->setValue(packet->layer1Add);
    ui.layer1Check->setChecked(packet->layer1Check);
    ui.layer2Add->setValue(packet->layer2Add);
    ui.layer2Check->setChecked(packet->layer2Check);
    ui.layer3Add->setValue(packet->layer3Add);
    ui.layer3Check->setChecked(packet->layer3Check);
    ui.layer4Add->setValue(packet->layer4Add);
    ui.layer4Check->setChecked(packet->layer4Check);
    ui.layer5Add->setValue(packet->layer5Add);
    ui.layer5Check->setChecked(packet->layer5Check);
    ui.layer6Add->setValue(packet->layer6Add);
    ui.layer6Check->setChecked(packet->layer6Check);
    ui.layer7Add->setValue(packet->layer7Add);
    ui.layer7Check->setChecked(packet->layer7Check);
    ui.layer8Add->setValue(packet->layer8Add);
    ui.layer8Check->setChecked(packet->layer8Check);
    ui.readDMX->setChecked(packet->dmx);
    ui.universe->setValue(packet->universe);
    ui.ipAddress1->setValue(packet->ipadd1);
    ui.ipAddress2->setValue(packet->ipadd2);
    ui.ipAddress3->setValue(packet->ipadd3);
    ui.ipAddress4->setValue(packet->ipadd4);
    int offset = sizeof(struct conf) - 4;
    int size = file.size() - offset;

    char * buffer = new char[size];
    memset(buffer, 0, size);
    memcpy(buffer, fileconf+offset, size);

//    m_mediaserver->setpathu(buffer);
    pathmedia = buffer;

    QString desc = tr("0000 0000 %1;").arg(pathmedia);
    if (!sendPacket(desc.toAscii().constData(),desc.size()))
                {
                 ui.textEdit->appendPlainText("No puedo mandar mensaje a Pure Data");
                return;
                }
    desc = tr("Media Path Changed to: %1").arg(pathmedia);
    ui.textEdit->appendPlainText(desc);
    file.close();
}

void PureMediaServer::save()
{
    qDebug()<<"Saving...";
    int bufferLen = sizeof(struct conf) + pathmedia.size();
    unsigned char *buffer = new unsigned char[bufferLen];
    memset(buffer, 0, bufferLen);
    conf *packet = (conf *)buffer;
    packet->window = ui.window->checkState();
    packet->winpositionx = ui.winpositionx->value();
    packet->winpositiony = ui.winpositiony->value();
    packet->winsizex = ui.winsizex->value();
    packet->winsizey = ui.winsizey->value();
    packet->layer1Add = ui.layer1Add->value();
    packet->layer1Check = ui.layer1Check->checkState();
    packet->layer2Add = ui.layer2Add->value();
    packet->layer2Check = ui.layer2Check->checkState();
    packet->layer3Add = ui.layer3Add->value();
    packet->layer3Check = ui.layer3Check->checkState();
    packet->layer4Add = ui.layer4Add->value();
    packet->layer4Check = ui.layer4Check->checkState();
    packet->layer5Add = ui.layer5Add->value();
    packet->layer5Check = ui.layer5Check->checkState();
    packet->layer6Add = ui.layer6Add->value();
    packet->layer6Check = ui.layer6Check->checkState();
    packet->layer7Add = ui.layer7Add->value();
    packet->layer7Check = ui.layer7Check->checkState();
    packet->layer8Add = ui.layer8Add->value();
    packet->layer8Check = ui.layer8Check->checkState();
    packet->dmx = ui.readDMX->checkState();
    packet->universe = ui.universe->value();
    packet->ipadd1 = ui.ipAddress1->value();
    packet->ipadd2 = ui.ipAddress2->value();
    packet->ipadd3 = ui.ipAddress3->value();
    packet->ipadd4 = ui.ipAddress4->value();
    int offset = sizeof (struct conf) - 4;
    memcpy(buffer+offset, pathmedia.toAscii().constData(), pathmedia.size());
    QFile file("pms.conf");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug("Can not open file pms.conf");
        return;
    }
    int error =  file.write((const char *)buffer, bufferLen);
    qDebug() << "Bytes Write to file "<< error;
    QString errorstring = tr("Bytes Write to file %1").arg(error);
    ui.textEdit->appendPlainText(errorstring);
    file.close();
}
