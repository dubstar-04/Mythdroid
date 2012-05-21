#include <QtGui>

//#include "link.h"
#include "channel.h"
#include "mainwindow.h"

Channel::Channel()
{
    myTextColor = Qt::white;
    myOutlineColor = Qt::black;
    myBackgroundColor = Qt::darkGray;

    //setFlags();
}

Channel::~Channel()
{
}

void Channel::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    update();
}

void Channel::setPosition(QRect &rect)
{
    prepareGeometryChange();
    myPosition = rect;
    update();
}

void Channel::setNewPosition(int value)
{
    prepareGeometryChange();
    myPosition = QRect(value, myPosition.top(), myPosition.width(), myPosition.height());
    update();
}



QString Channel::text() const
{
    return myText;
}

void Channel::setChanId(const QString &channelId)
{
    prepareGeometryChange();
    mychanId = channelId;
    myChanIcon = "/sdcard/MythDroidData/Icons/" + mychanId + ".jpg";
    QFile Icon(myChanIcon);
    if (!Icon.exists()){
        myChanIcon = "NULL";
    }


    update();
}

QString Channel::chanId() const
{
    return mychanId;
}

void Channel::setTextColor(const QColor &color)
{
    myTextColor = color;
    update();
}

QColor Channel::textColor() const
{
    return myTextColor;
}

void Channel::setOutlineColor(const QColor &color)
{
    myOutlineColor = color;
    update();
}

QColor Channel::outlineColor() const
{
    return myOutlineColor;
}

void Channel::setBackgroundColor(const QColor &color)
{
    myBackgroundColor = color;
    update();
}

QColor Channel::backgroundColor() const
{
    return myBackgroundColor;
}

QRectF Channel::boundingRect() const
{
    const int Margin = 1;
    return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
}

QPainterPath Channel::shape() const
{
    QRectF rect = outlineRect();

    QPainterPath path;
    path.addRoundRect(rect, roundness(rect.width()),
                      roundness(rect.height()));
    return path;
}

void Channel::paint(QPainter *painter,
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
    painter->setBrush(myBackgroundColor);
    painter->drawRect(myPosition);
    //painter->setPen(myTextColor);
    //painter->drawText(myPosition,Qt::AlignCenter, myText);
   //QString iconname = QDir::homePath() + "/MythDroidData/Icons/" + mychanId + ".jpg";

   if (myChanIcon != "NULL"){
   QPixmap Icon(myChanIcon);
   //Icon.scaled(58,58,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
   painter->setRenderHint(QPainter::SmoothPixmapTransform);
   painter->drawPixmap(myPosition.left()+2,myPosition.top()+2, 58, 58, Icon);
   }
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

QVariant Channel::itemChange(GraphicsItemChange change,
                          const QVariant &value)
{

    if (change == ItemPositionHasChanged) {
        //foreach (Link *link, myLinks)
          //  link->trackNodes();
    }
    return QGraphicsItem::itemChange(change, value);

}

QRectF Channel::outlineRect() const
{
    //const int Padding = 0;
    //QFontMetricsF metrics = qApp->font();
    //QRectF rect = metrics.boundingRect(myText);

    QRectF rect = myPosition;
    //rect.adjust(-Padding, -Padding, +Padding, +Padding);
    //rect.translate(-rect.center());
    return rect;
}

int Channel::roundness(double size) const
{
    const int Diameter = 12;
    return 100 * Diameter / int(size);
}




