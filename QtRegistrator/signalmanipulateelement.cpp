#include "signalmanipulateelement.h"

#include <QPaintEvent>
#include <QPainter>
#include <QLayout>
#include <QColorDialog>

#include <cmath>

//#include <utility>

Registartor::Render
        ::SignalManipulateElement
        ::SignalManipulateElement(QWidget *parent)
    : QWidget(parent)
{
    SetMaxPointCount();
    InitMenu();

    _spinBox.hide();

    connect(&_spinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, QOverload<float>::of(&SignalManipulateElement::SetThickness));
}

void Registartor::Render
             ::SignalManipulateElement
             ::SetMaxPointCount(int val)
{
    buffer.resize(val);
}

void Registartor::Render
             ::SignalManipulateElement
             ::PushPoint(QPointF val)
{
    buffer[_begin++] = val;
    _begin %= buffer.size();
}

void Registartor::Render
             ::SignalManipulateElement
             ::ClearAllPoint()
{
    buffer.resize(0);
}

void Registartor::Render
             ::SignalManipulateElement
             ::SetOffset(QPointF val)  noexcept
{
    _propRender.offset = val;
}

void Registartor::Render
             ::SignalManipulateElement
             ::SetColor(QColor val) noexcept
{
    _propRender.color = val;
}

void Registartor::Render
             ::SignalManipulateElement
             ::SetScale(QPointF val) noexcept
{
    _propRender.scale = val;
}

void Registartor::Render
             ::SignalManipulateElement
             ::SetThickness(float val) noexcept
{
    _propRender.thickness = val;
}

void Registartor::Render
             ::SignalManipulateElement
             ::DrawSignal(QPainter *paint)
{
    QPen pen(_propRender.color);
    pen.setWidthF(_propRender.thickness);
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);


    paint->setPen( pen );

    auto increment = [](int n, int x, int max){ return (n + x) % max; };
    auto decrement = [](int n, int x, int max){ return ((n - x) + max) % max; };

    QPointF back = buffer[decrement(_begin, 1, buffer.size())];
    back.setY(0);

    for (int i = 0; (i) < buffer.size() -1; ++i) {
        int prew_idx = decrement(i + _begin, 1, buffer.size());
        int curr_idx = increment(i + _begin, 0, buffer.size());

        if ( buffer[prew_idx].x() < buffer[curr_idx].x() ) {
            QLineF line( buffer[prew_idx], buffer[curr_idx] );

            line.translate( _propRender.offset  - back);
            paint->drawLine(line);
        }
    }
}

void Registartor::Render
             ::SignalManipulateElement
             ::DrawGrid(QPainter *p)
{
    QPen pen(Qt::GlobalColor::black);

    // толщина координатных осей не должна меняться при масштабе графика
    pen.setWidthF( 1.f / _propRender.scale.x() );
    p->setPen(pen);

    QPointF hor1(-p->viewport().width(), 0)
          , hor2(+p->window().width(), 0);

    QPointF ver1(0, -p->viewport().height())
          , ver2(0,  p->viewport().height());

    p->drawLines( { QLineF(hor1, hor2), QLineF(ver1, ver2) } );
}

void Registartor::Render
             ::SignalManipulateElement
             ::ShowSpinBox()
{
    _spinBox.show();
}

void Registartor::Render
             ::SignalManipulateElement
             ::ChangeColor()
{
    auto color = QColorDialog::getColor();
    SetColor(color);
}


void Registartor::Render
             ::SignalManipulateElement
             ::InitMenu()
{
    auto action = _toolMenu.addAction("Изменить толщину");
    connect(action, &QAction::triggered, this, &SignalManipulateElement::ShowSpinBox);

    action = _toolMenu.addAction("Выбрать цвет");
    connect(action, &QAction::triggered, this, &SignalManipulateElement::ChangeColor);


}

//###################################################################################
//######### SLOTS init
//###################################################################################
void Registartor::Render
             ::SignalManipulateElement
             ::paintEvent(QPaintEvent*)
{

    QPainter paint(this);

    paint.translate( geometry().width() / 2, geometry().height() / 2 );
    paint.setTransform( { 1, 0, 0, 0, -1, 0, 0, 0, 1 }, true );

    paint.scale( _propRender.scale.x(), _propRender.scale.y() );

    paint.setPen(Qt::GlobalColor::black);

    DrawGrid(&paint);   // рисуем сетку
    DrawSignal(&paint);

    paint.end();
}

void Registartor::Render
             ::SignalManipulateElement
             ::wheelEvent(QWheelEvent *we)
{
    auto scale = GetScale();

    float delta = (we->delta() < 0) ? -0.1 : 0.1;

    scale.setX( scale.x() + delta );
    scale.setY( scale.y() + delta );

    if (scale.x() > 0 && scale.y() > 0) SetScale(scale);
}

void Registartor::Render
             ::SignalManipulateElement
             ::mouseReleaseEvent(QMouseEvent *ev)
{
    switch(ev->button()) {
        case Qt::MouseButton::RightButton: {
            _spinBox.move(ev->globalPos());
            _toolMenu.popup(ev->globalPos());
            break;
        }

        default:
            break;
    }
}
