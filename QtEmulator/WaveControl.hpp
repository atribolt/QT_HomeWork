#ifndef WAVECONTROL_HPP
#define WAVECONTROL_HPP

#include <QMenu>
#include <QTimer>
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

#include <memory>

#include "signal.h"
#include "BaseWave.hpp"
#include "signalmanipulateelement.h"

/*
 * Элемент управления для сигналов.
 *
 * Отображение сигнала
 * Масштабирование
 * Смещение
 * Изменение толщины
 * Изменение скорости генерации
*/

namespace Emulator::Render {

template<class TSignal>
    class WaveControl : public QWidget {
        Q_OBJECT

        using signal_type = TSignal;
        using signal_ptr  = std::unique_ptr<signal_type>;

    public:
        WaveControl(QWidget *parent = nullptr)
            : WaveControl(parent, nullptr) {}

        WaveControl(QWidget *parent = nullptr, signal_ptr ptr = nullptr)
            : QWidget(parent)
        {
            _signal = ptr;

           // connect(&_timer, &QTimer::timeout, this, &WaveControl::GenerateSignal);
         //   connect(&_timeInterval, &QSpinBox::valueChanged, &_timer, &QTimer::setInterval);
        }

    private slots:
        void paintEvent       (QPaintEvent  *event) override;
        void resizeEvent      (QResizeEvent *event) override;
        void mouseReleaseEvent(QMouseEvent  *event) override;

    protected:
        void GenerateSignal();

        QMenu                    _menuTool;
        QSpinBox                 _timeInterval;
        QTimer                   _timer;
        signal_ptr               _signal;
        SignalManipulateElement  _signalRender;
    };

}
#endif // WAVECONTROL_HPP
