#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QLayout>
#include <QPainter>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , rd(QHostAddress::LocalHost, 8888)
{
    //######## Init _signalView
    _signalView.setParent(this);
    _signalView.move(0, 0);
    _signalView.SetMaxPointCount(300);
    //#########################

    connect(&rd, &RecieveData::NewData, this, &MainWindow::HopDataRead);
}

void MainWindow::HopDataRead(float x, float val) {
    _signalView.PushPoint( { x, val } );
    update();
}

void MainWindow::paintEvent(QPaintEvent *ev) {
    _signalView.resize( geometry().size() );
    _signalView.update();
}
