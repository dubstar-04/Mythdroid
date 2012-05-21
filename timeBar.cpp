#include <QtGui>

//#include "link.h"
#include "timeBar.h"
#include "mainwindow.h"

TimeBar::TimeBar()
{

    myTextColor = Qt::darkGray;
    myOutlineColor = Qt::black;
    myBackgroundColor = Qt::gray;

    //setFlags();
}

TimeBar::~TimeBar()
{
}

void TimeBar::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    update();
}

void TimeBar::setPosition(QRect &rect)
{
    prepareGeometryChange();
    myPosition = rect;
    update();
}

void TimeBar::setNewPosition(int value)
{
    prepareGeometryChange();
    myPosition = QRect(myPosition.left(),value,myPosition.width(), myPosition.height());
    update();
}



QString TimeBar::text() const
{
    return myText;
}

void TimeBar::setTextColor(const QColor &color)
{
    myTextColor = color;
    update();
}

QColor TimeBar::textColor() const
{
    return myTextColor;
}

void TimeBar::setOutlineColor(const QColor &color)
{
    myOutlineColor = color;
    update();
}

QColor TimeBar::outlineColor() const
{
    return myOutlineColor;
}

void TimeBar::setBackgroundColor(const QColor &color)
{
    myBackgroundColor = color;
    update();
}

QColor TimeBar::backgroundColor() const
{
    return myBackgroundColor;
}

QRectF TimeBar::boundingRect() const
{
    const int Margin = 1;
    return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
}

QPainterPath TimeBar::shape() const
{
    QRectF rect = outlineRect();

    QPainterPath path;
    path.addRoundRect(rect, roundness(rect.width()),
                      roundness(rect.height()));
    return path;
}

void TimeBar::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget * /* widget */)
{
    QPen pen(myOutlineColor);
    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }else{
        pen.setWidth(1);
    }

    //painter->Antialiasing;
    painter->setPen(pen);

    //QLinearGradient linearGrad(QPointF(0, 4800), QPointF(30, 4800));
    QLinearGradient linearGrad(myPosition.topLeft(),myPosition.bottomLeft());
    linearGrad.setColorAt(0, Qt::gray);
    linearGrad.setColorAt(0.5, Qt::white);
    linearGrad.setColorAt(1, Qt::gray);
    painter->setBrush(linearGrad);
    //painter->setBrush(myBackgroundColor);
    painter->drawRect(myPosition);
    painter->setPen(myTextColor);
    painter->drawText(myPosition, Qt::AlignCenter, myText);
}
/*
void TimeBar::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

   QString text = QInputDialog::getText(event->widget(),
                           "Edit Text", "Enter new text:",
                           QLineEdit::Normal, myText);
    if (!text.isEmpty())
        setText(text);
}
*/

QVariant TimeBar::itemChange(GraphicsItemChange change,
                          const QVariant &value)
{

    if (change == ItemPositionHasChanged) {
        //foreach (Link *link, myLinks)
          //  link->trackNodes();
    }
    return QGraphicsItem::itemChange(change, value);

}

QRectF TimeBar::outlineRect() const
{
    //const int Padding = 0;
    //QFontMetricsF metrics = qApp->font();
    //QRectF rect = metrics.boundingRect(myText);

    QRectF rect = myPosition;
    //rect.adjust(-Padding, -Padding, +Padding, +Padding);
    //rect.translate(-rect.center());
    return rect;
}

int TimeBar::roundness(double size) const
{
    const int Diameter = 12;
    return 100 * Diameter / int(size);
}



