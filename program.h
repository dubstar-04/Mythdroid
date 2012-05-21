#ifndef PROGRAM_H
#define PROGRAM_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>

class Program : public QGraphicsItem
{
    //Q_DECLARE_TR_FUNCTIONS(Node)
    //Q_OBJECT

public:
    Program();
    ~Program();

    void setText(const QString &text);
    QString text() const;
    void setSubtitle(const QString &subtitle);
    void setDescription(const QString &description);
    void setChanId(const QString &chanId);
    QString ChanId() const;
    void setCategory(const QString &category);
    QString getCategory() const;
    void setPosition(QRect &rect);
    QRect Position();
    void setTextColor(const QColor &color);
    QColor textColor() const;
    void setGenreColor(const QColor &color);
    QColor genreColor() const;
    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;
    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    //void thisorthat();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);

private:
    QRectF outlineRect() const;
    //int roundness(double size) const;

    //QSet<Link *> myLinks;
    QString myText;
    QString myTitle;
    QString mySubtitle;
    QString myDescription;
    QString myChanId;
    QString myCategory;
    QColor myTextColor;
    QColor myGenreColor;
    QColor myBackgroundColor;
    QColor myOutlineColor;
    QRect myPosition;


};


#endif // PROGRAM_H
