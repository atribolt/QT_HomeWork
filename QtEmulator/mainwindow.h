#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTime>
#include <QTimer>
#include <QLabel>
#include <QMainWindow>

#include "senddata.h"
#include "BaseWave.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void GeneratePoint();
    void SetDeltaX(float val) noexcept;

    inline void SetAmplitude(float val) noexcept { _simpleWave->SetAmplitude(val); }
    inline void SetFrequence(float val) noexcept { _simpleWave->SetFrequence(val); }
    inline void SetShiftOX  (float val) noexcept { _simpleWave->SetShiftOx  (val); }
    inline void SetShiftOY  (float val) noexcept { _simpleWave->SetShiftOy  (val); }

    Ui::MainWindow *ui;

    QTimer _timer;

    Emulator::SimpleWave            *_simpleWave;
    Emulator::SendData::SendDataPtr  _server;

    float startX { 0.f };
    float deltaX { 0.5 };
};

#endif // MAINWINDOW_H
