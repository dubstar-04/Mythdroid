#ifndef PROGRAMINFO_H
#define PROGRAMINFO_H

#include <QWidget>

namespace Ui {
    class programInfo;
}

class programInfo : public QWidget
{
    Q_OBJECT

public:
    explicit programInfo(QWidget *parent = 0);
    ~programInfo();

    void setTitle(QString Title);
    void setSubtitle(QString subtitle);
    void setDescription(QString description);
    void setIcon(QPixmap Icon);

private:
    Ui::programInfo *ui;
};

#endif // PROGRAMINFO_H
