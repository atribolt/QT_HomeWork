#include <QLayout>
#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Server.h"
#include "CoordinatePacket.h"

MainWindow::MainWindow(Server* server)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(&_timer, &QTimer::timeout, 
          this, &MainWindow::GeneratePoint);
  
  connect(ui->sb_Interval_MLS, QOverload<int>::of(&QSpinBox::valueChanged), 
          &_timer, QOverload<int>::of(&QTimer::setInterval));

  connect(ui->dsb_StepDX,    QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
          this, QOverload<float>::of(&MainWindow::SetDeltaX));

  ui->dsb_StepDX->setValue( 0.5 );
  ui->dsb_ShiftOX->setValue( 0.f );
  ui->dsb_ShiftOY->setValue( 0.f );
  ui->dsb_Amplitude->setValue( 5.f );
  ui->dsb_Frequence->setValue( 0.3 );
  ui->sb_Interval_MLS->setValue( 50  );

  setServer(server);
  
  _timer.start();
}

MainWindow::~MainWindow() noexcept
{}

void MainWindow::setServer(Server* server) {
  _server = server;
}

void MainWindow::setWaveFunction(WaveFunction const& func) {
  _waveFunc = func;
}

void MainWindow::GeneratePoint()  {
  if (!_waveFunc) return;
  
  startX += deltaX;
  double Y = _waveFunc(startX,
                       ui->dsb_Amplitude->value(),
                       ui->dsb_ShiftOX->value(),
                       ui->dsb_ShiftOY->value(),
                       ui->dsb_Frequence->value());

  ui->lbl_X->setText(QString("Значение Х: %1").arg(startX));
  ui->lbl_Value->setText(QString("Значение Y: %1").arg(Y));

  if (_server != nullptr) {
    CoordinatePacket packet;
    packet.x = startX;
    packet.y = Y;
    _server->notifyAllClients(packet.getPacket());
  }
}

void MainWindow::SetDeltaX(float val) noexcept { 
  deltaX = val; 
}
