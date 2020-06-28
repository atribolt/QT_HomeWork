#ifndef SIMPLEWAVECONTROL_H
#define SIMPLEWAVECONTROL_H

#include <QPushButton>

#include "BaseWave.hpp"
#include "signalmanipulateelement.h"

/*
 * графический элемент для управления графическим состоянием простого волнового сигнала
 *
 *
*/

namespace Emulator::Render {

class SimpleWaveControl final : public QWidget {
    Q_OBJECT

public:
    SimpleWaveControl(QWidget *parent = nullptr);
    SimpleWaveControl(SimpleWave const&, QWidget *parent = nullptr );

private:
    QPushButton btns;

    SimpleWave *wave { nullptr };
    SignalManipulateElement signalElem;
};

}
#endif // SIMPLEWAVECONTROL_H
