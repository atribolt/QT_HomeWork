#pragma once

#include <QMenu>
#include <QWidget>
#include <QVector>
#include <QSpinBox>

namespace Registartor::Render {

struct SignalProperties {
    float   thickness { 1 };
    QColor  color     { Qt::GlobalColor::black };
    QPointF offset    { 0.f, 0.f };              // смещение относительно центра области рисования
    QPointF scale     { 1.f, 1.f };
};

class SignalManipulateElement final : public QWidget {
    Q_OBJECT
public:
    explicit SignalManipulateElement(QWidget *parent = nullptr);

    QPointF GetScale() const noexcept { return _propRender.scale; }

    void PushPoint(QPointF point);
    void ClearAllPoint();

    void SetScale        (QPointF val) noexcept;
    void SetColor        (QColor val) noexcept;
    void SetOffset       (QPointF val) noexcept;
    void SetThickness    (float val) noexcept;
    void SetMaxPointCount(int val = 500);     // ограничение хранимых значений для отрисовки

private slots:
    void paintEvent       (QPaintEvent *event) override;
    void wheelEvent       (QWheelEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void DrawGrid  (QPainter*);
    void DrawSignal(QPainter*);

    void InitMenu();
    void ShowSpinBox();
    void ChangeColor();

    QMenu            _toolMenu;
    QDoubleSpinBox   _spinBox;
    SignalProperties _propRender;

    int _begin { 0 };
    QVector<QPointF> buffer;
};

}
