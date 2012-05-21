#ifndef CHANNEL_H
#define CHANNEL_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>

//class Link;

class Channel : public QGraphicsItem
{
    //Q_DECLARE_TR_FUNCTIONS(Node)

public:
    Channel();
    ~Channel();

    void setText(const QString &text);
    QString text() const;
    void setChanId(const QString &channelId);
    QString chanId() const;
    void setPosition(QRect &rect);
    void setNewPosition(int value);
    QRect Position();
    void setTextColor(const QColor &color);
    QColor textColor() const;
    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;
    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    //void addLink(Link *link);
    //void removeLink(Link *link);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
   // void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);

private:
    QRectF outlineRect() const;
    int roundness(double size) const;

    //QSet<Link *> myLinks;
    QString myText;
    QString mychanId;
    QString myChanIcon;
    QColor myTextColor;
    QColor myBackgroundColor;
    QColor myOutlineColor;
    QRect myPosition;


};
#endif // CHANNEL_H
