#pragma once

#include <QTime>
#include <QTimer>
#include <QLabel>
#include <QMainWindow>

#include "WaveFunction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
  MainWindow(class Server* server = nullptr);
  ~MainWindow() noexcept;
  
  void setServer(class Server* server);
  void setWaveFunction(WaveFunction const& func);
  
private:
  void GeneratePoint();
  void SetDeltaX(float val) noexcept;

  Ui::MainWindow *ui;

  QTimer _timer;
  WaveFunction _waveFunc;
  class Server* _server;

  float startX { 0.f };
  float deltaX { 0.5 };
};
