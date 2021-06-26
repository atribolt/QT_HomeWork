#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QLayout>
#include <QPainter>
#include <QHostAddress>

#include "Client.h"
#include "CoordinatePacket.h"

MainWindow::MainWindow(Client* client)
    : QWidget(nullptr)
    , _client(client)
{
  //######## Init _signalView
  _signalView.setParent(this);
  _signalView.move(0, 0);
  _signalView.SetMaxPointCount();
  //#########################
  
  setClient(client);
}

void MainWindow::setClient(Client* client) {
  QObject::disconnect(_client, nullptr, nullptr, nullptr);
  _client = client;
  QObject::connect(_client, &Client::newPacket, this, &MainWindow::hopDataRead);
}

void MainWindow::hopDataRead(Packet const& pack) {
  CoordinatePacket coordinate;
  coordinate.setPacket(pack);

  _signalView.PushPoint( { coordinate.x, coordinate.y } );
  update();
}

void MainWindow::paintEvent(QPaintEvent*) {
  _signalView.resize( geometry().size() );
  _signalView.update();
}
