#pragma once

#include <QMainWindow>

#include "signalmanipulateelement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
  Q_OBJECT
public:
  MainWindow(class Client* clientSocket);
  void setClient(class Client* client);
    
private slots:
  void paintEvent(QPaintEvent *event) override;

private:
  void hopDataRead(float x, float val);

  class Client* _client;
  Registartor::Render::SignalManipulateElement _signalView;
};
