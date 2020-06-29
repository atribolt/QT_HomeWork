#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _server     = Emulator::SendData::Create(); //(QHostAddress::LocalHost, 8888);
    _simpleWave = new Emulator::Cosinusoida();

    connect(&_timer, &QTimer::timeout, this, &MainWindow::GeneratePoint);
    connect(ui->sb_Interval_MLS, QOverload<int>::of(&QSpinBox::valueChanged), &_timer, QOverload<int>::of(&QTimer::setInterval));

    connect(ui->dsb_StepDX,    QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, QOverload<float>::of(&MainWindow::SetDeltaX));
    connect(ui->dsb_ShiftOX,   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, QOverload<float>::of(&MainWindow::SetShiftOX));
    connect(ui->dsb_ShiftOY,   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, QOverload<float>::of(&MainWindow::SetShiftOY));
    connect(ui->dsb_Amplitude, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, QOverload<float>::of(&MainWindow::SetAmplitude));
    connect(ui->dsb_Frequence, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, QOverload<float>::of(&MainWindow::SetFrequence));

    ui->dsb_StepDX     ->setValue( 0.5 );
    ui->dsb_ShiftOX    ->setValue( 0.f );
    ui->dsb_ShiftOY    ->setValue( 0.f );
    ui->dsb_Amplitude  ->setValue( 5.f );
    ui->dsb_Frequence  ->setValue( 0.3 );
    ui->sb_Interval_MLS->setValue( 50  );

    _timer.start();
}

MainWindow::~MainWindow()
{
    if(_simpleWave)
        delete _simpleWave;

    delete ui;
}

void MainWindow::GeneratePoint()  {
    startX += deltaX;
    auto val = (*_simpleWave)( startX );

    ui->lbl_X    ->setText(QString("Значение Х: %1").arg(startX));
    ui->lbl_Value->setText(QString("Значение Y: %1").arg(val));

    _server->Send(startX, val);
}

void MainWindow::SetDeltaX(float val) noexcept { deltaX = val; }
