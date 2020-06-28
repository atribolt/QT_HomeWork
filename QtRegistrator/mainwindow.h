#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "RecieveData.h"
#include "signalmanipulateelement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void paintEvent(QPaintEvent *event) override;

private:
    void HopDataRead(float x, float val);

    RecieveData rd;
    Registartor::Render::SignalManipulateElement _signalView;
};
#endif // MAINWINDOW_H
