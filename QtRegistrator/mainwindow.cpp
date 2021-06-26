#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QLayout>
#include <QPainter>
#include <QHostAddress>

#include "Client.h"

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
  _client = client;
}

void MainWindow::hopDataRead(float x, float val) {
    _signalView.PushPoint( { x, val } );
    update();
}

void MainWindow::paintEvent(QPaintEvent*) {
    _signalView.resize( geometry().size() );
    _signalView.update();
}
