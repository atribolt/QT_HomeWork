#pragma once

#include <QMainWindow>

#include "CommonLib/Packet.h"
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
  void hopDataRead(Packet const& packet);

  class Client* _client;
  Registartor::Render::SignalManipulateElement _signalView;
};
