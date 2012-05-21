#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QStandardItemModel>
#include <QNetworkAccessManager>
#include <QXmlStreamReader>
#include <QtNetwork>
#include <iostream>

#include <QFile>
//#include <QFileInfo>
#include <QList>
#include <QNetworkReply>
#include <QStringList>
#include <QTimer>

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QtGlobal>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDir>
#include <QDateTime>
#include <QDate>
#include <QGraphicsScene>
#include <QSettings>

#include "timeBar.h"
#include "channel.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //mainwindow
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //QStandardItemModel model;
    //getImage
    void doDownload(const QUrl &url);
    QString saveFileName(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);


    //Mainwindow
    QGraphicsScene *timeline;

signals:
    //mainwindow
    void doneParsing();
    void doneBuildingGuide();


public slots:
    //getImage
    //Mainwindow
    void channelSelected();
    void printSomething();

private slots:
    //mainwindow
    void readData(QNetworkReply *reply);
    void moveTimeBar(int value);
    void moveChannels(int value);
    void buildTimeBar();
    void getChannelIcons();

    //parseData
    bool parseFeed();

    //getImage
    void downloadFinished(QNetworkReply *reply);
    void getChannelList();

    void on_pushButton_clicked();

private:

    //mainwindow
    Ui::MainWindow *ui;
    void buildChannelList();
    void setUpDataBases();
    void getData();
    bool setupGuideDb(QString dbname);
    void buildChannels(QString channelName, QString chanId, int channelCount);
    bool getFile(const QUrl &url);
    void getPrograms(QString chanId, int channelCount);
    void buildGuide(QString channelId, QString title, QString subtitle, QString description, QString endTime, QString startTime, QString category, int channelCount);
    QString formatTime(QString Time);
    //QSettings settings;
    int m_viewHeight;
    int m_viewWidth;
    QNetworkAccessManager manager;
    QNetworkAccessManager *managerPid;
    //timeBar
    QList<TimeBar *> timebars;
    //channel
    QList<Channel *> channels;


    //getImage
    QNetworkAccessManager manager2;
    QList<QNetworkReply *> currentDownloads;

    //parseData
    void getTitle();
    QXmlStreamReader xml;
    //QXmlStreamWriter stream;

    //Database
    QSqlTableModel *dbmodel;
    QSqlDatabase db;
    bool setupDb(QString dbname);
    QSqlTableModel *dbguidemodel;
    QSqlDatabase guidedb;
    //void on_actionDelete_triggered();
    //void on_actionEdit_triggered();
    void AddChanneltoDB(QString channelName, QString chanID);
    void AddtoGuideDB( QString chanId, QString title, QString subtitle, QString description, QString category, QString endTime, QString startTime );
    void AddItem(QString Name, QString Icon);

};


#endif // MAINWINDOW_H




