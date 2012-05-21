#include <QtGui>

//#include "link.h"
#include "program.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "programinfo.h"


Program::Program()
{

    myTextColor = Qt::white;
    myOutlineColor = Qt::black;
    myBackgroundColor = QColor::fromRgb(69,69,69);

    //setFlags(ItemIsSelectable);
    //QObject::connect(this, SIGNAL(thisorthat()), MainWindow, SLOT(printSomething()));
}

Program::~Program()
{
}

void Program::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    myTitle = text;

    QFontMetricsF metrics = qApp->font();
    int textWidth = metrics.width(myText);
    int programWidth = myPosition.width();


        if (programWidth < 50){
         myText = "i";
         }

        textWidth = metrics.width(myText);
         if (textWidth > programWidth){
         while(textWidth > programWidth){
         myText.chop(1);
         textWidth = metrics.width(myText);
         }
         myText = myText + "...";
         }


    update();
}

void Program::setSubtitle(const QString &subtitle)
{
    mySubtitle = subtitle;
}

void Program::setDescription(const QString &description)
{
    myDescription = description;
}

void Program::setChanId(const QString &chanId)
{
    prepareGeometryChange();
    myChanId = chanId;
    update();
}

void Program::setCategory(const QString &category)
{
    prepareGeometryChange();
    myCategory = category;
    update();
}

QString Program::getCategory() const
{
 return myCategory;
}

void Program::setPosition(QRect &rect)
{
    prepareGeometryChange();
    myPosition = rect;
    update();
}

QString Program::text() const
{
    return myText;
}

void Program::setTextColor(const QColor &color)
{
    myTextColor = color;
    update();
}

QColor Program::textColor() const
{
    return myTextColor;
}

void Program::setGenreColor(const QColor &color)
{
    myGenreColor = color;
    update();
}

QColor Program::genreColor() const
{
    return myGenreColor;
}

void Program::setOutlineColor(const QColor &color)
{
    myOutlineColor = color;
    update();
}

QColor Program::outlineColor() const
{
    return myOutlineColor;
}

void Program::setBackgroundColor(const QColor &color)
{
    myBackgroundColor = color;
    update();
}

QColor Program::backgroundColor() const
{
    return myBackgroundColor;
}

QRectF Program::boundingRect() const
{
    //const int Margin = 1;
    return outlineRect();//.adjusted(-Margin, -Margin, +Margin, +Margin);
}


void Program::paint(QPainter *painter,
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
    painter->setBrush(myBackgroundColor);
    painter->drawRect(myPosition);
    pen.setColor(myGenreColor);
    painter->setBrush(myGenreColor);
    painter->drawRect(myPosition.left(),myPosition.bottom() - 4, myPosition.width(), 4);
    painter->setPen(myTextColor);
    painter->drawText(myPosition, Qt::AlignCenter, myText);
}

void Program::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    programInfo *info = new programInfo();
    info->setTitle(myTitle);
    info->setSubtitle(mySubtitle);
    info->setDescription(myDescription);


    QString iconname = "/sdcard/MythDroidData/Icons/" + myChanId + ".jpg";
    if (QFile(iconname).exists())
    {
    QPixmap Icon(iconname);
    info->setIcon(Icon);
    }

    info->showFullScreen();

    //QWidget *ProgramWindow = new QWidget();
    //ProgramWindow->setBackgroundRole(myBackgroundColor);
    //ProgramWindow->show();




}

QVariant Program::itemChange(GraphicsItemChange change,
                          const QVariant &value)
{

    if (change == ItemPositionHasChanged) {
        //foreach (Link *link, myLinks)
          //  link->trackNodes();
    }
    return QGraphicsItem::itemChange(change, value);

}

QRectF Program::outlineRect() const
{
    //const int Padding = 0;
    //QFontMetricsF metrics = qApp->font();
    //QRectF rect = metrics.boundingRect(myText);

    QRectF rect = myPosition;
    //rect.adjust(-Padding, -Padding, +Padding, +Padding);
    //rect.translate(-rect.center());
    return rect;
}



