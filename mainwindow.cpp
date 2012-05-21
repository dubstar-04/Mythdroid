#include "mainwindow.h"
//#include "GetImage.h"
#include "ui_mainwindow.h"
#include "program.h"
#include "timeBar.h"
#include "channel.h"
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QString dataFolder = "/sdcard/MythDroidData/";
    QDir folder(dataFolder);
    if (!QDir(folder).exists()){
            QDir().mkdir(dataFolder);
    }

    QFont newFont("system/fonts/DroidSans.ttf", -1, QFont::Bold,false);
    //set font of application
    QApplication::setFont(newFont);

    ui->setupUi(this);
    //this->repaint();
    connect(&manager, SIGNAL(finished(QNetworkReply * )), SLOT(readData(QNetworkReply *)));
    connect(&manager2, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
    connect(this, SIGNAL(doneParsing()), SLOT(getChannelList()));
    connect(ui->graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),this, SLOT(moveTimeBar(int)));
    connect(ui->graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(moveChannels(int)));
    connect(this, SIGNAL(doneBuildingGuide()), this, SLOT(buildTimeBar()));
    //connect(ui->listView, SIGNAL(clicked(QModelIndex )), SLOT(channelSelected()));

    timeline = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(timeline);
    ui->graphicsView->setBackgroundBrush(QBrush(QColor::fromRgb(69,69,69)));
    ui->graphicsView->setAlignment(Qt::AlignTop);

    //QCoreApplication::setOrganizationName("OpenSource");
    //QCoreApplication::setOrganizationDomain("mysoft.com");
    //QCoreApplication::setApplicationName("MythDroid");

    QSettings settings("OpenSource", "MythDroid");
    QString IpAddress = settings.value("ipAddress", "NULL").toString();
    //qDebug(qPrintable(IpAddress));

    if (IpAddress == "NULL"){
        ui->stackedWidget->setCurrentIndex(1);
        ui->ipAddress1->setText(IpAddress);
    }else{
        ui->stackedWidget->setCurrentIndex(0);

        QString TodaysDate = QDateTime::currentDateTime().toString();
        TodaysDate.remove(0, 8);
        TodaysDate.chop(14);

        if (TodaysDate == settings.value("data").toString()){

            setUpDataBases();
            getChannelList();


        }else{
            QString guidefilename = "/sdcard/MythDroidData/guideData.db";
            QFile().remove(guidefilename);
            setUpDataBases();
            getData();
        }

        //qDebug("boom");
    }
}

void MainWindow::printSomething()
{
    std::cout << "hello i am in mainwindow" << std::endl;
}

void MainWindow::getData()
{
    //QSettings settings;
    QSettings settings("OpenSource", "MythDroid");
    QString IpAddress = settings.value("ipAddress").toString();
    QString now = QDateTime::currentDateTime().toString();
    QString startTime = formatTime(now);
    QString end = QDateTime::currentDateTime().addDays(1).toString();
    QString endTime = formatTime(end);
    //QString IpAddress = "192.168.1.10";
    QString requestUrl = "http://" + IpAddress + ":6544/Myth/GetProgramGuide?EndTime=" + endTime + "&NumOfChannels=-1&StartTime=" + startTime + "&Details=1";
    std::cout << qPrintable(requestUrl) << std::endl;
    QUrl url(requestUrl);
    getFile(url);
}

void MainWindow::setUpDataBases()
{
    //check if the database exists, if not exit
    QString filename = "/sdcard/MythDroidData/channels.db";
    if(!setupDb(filename))
    {
        QMessageBox::critical(this,
                              tr("Database not found"),
                              tr("Database not found. The application will be closed."),
                              QMessageBox::Ok);
        qApp->exit();
    }
    QString guidefilename = "/sdcard/MythDroidData/guideData.db";
    //TO DO remove this and impliment a check on programs
    //QFile().remove(guidefilename);
    if(!setupGuideDb(guidefilename))
    {
        QMessageBox::critical(this,
                              tr("Database not found"),
                              tr("Database not found. The application will be closed."),
                              QMessageBox::Ok);
        qApp->exit();
    }

}

void MainWindow::moveTimeBar(int value)
{
    foreach (TimeBar *Timebar, timebars) {
       Timebar->setNewPosition(value);
    }
}
void MainWindow::moveChannels(int value)
{
    foreach (Channel *channel, channels) {
       channel->setNewPosition(value);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::channelSelected()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::buildTimeBar()
{
    for (int i = 0; i < 24; i++){
    TimeBar *Timebar = new TimeBar;
    Timebar->setText(QString::number(i) + ":00" );
    QRect rect(((m_viewWidth/3)*i*2)+ 60, 0, (2 * (m_viewWidth/3)), 20);
    Timebar->setPosition(rect);
    timeline->addItem(Timebar);
    timebars.append(Timebar);
    }
}

void MainWindow::buildChannels(QString channelName, QString chanId, int channelCount)
{

    //for (int i = 0; i < 24; i++){
    Channel *channel = new Channel;
    channel->setText(channelName);
    channel->setChanId(chanId);
    channel->setBackgroundColor(Qt::gray);
    channel->setOutlineColor(Qt::darkGray);

    int row = (channelCount * 60) + 20;
    QRect rect(0, row, 60, 60);
    channel->setPosition(rect);
    timeline->addItem(channel);
    channels.append(channel);

}

bool MainWindow::getFile(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);
    return true;
}

void MainWindow::readData(QNetworkReply *reply)
{
        xml.addData(reply->readAll());
        parseFeed();
        //qDebug("Done Parsing");
        QSettings settings("OpenSource", "MythDroid");

        QString TodaysDate = QDateTime::currentDateTime().toString();
        TodaysDate.remove(0, 8);
        TodaysDate.chop(14);

        settings.setValue("data", TodaysDate);
        if (!settings.value("icons").toInt() == 1){
        getChannelIcons();
        }
        emit doneParsing();

}

void MainWindow::buildGuide(QString channelID, QString title, QString subtitle, QString description, QString endTime, QString startTime, QString category, int channelCount)
{
    //start time format 2011-04-15T16:00:00
   QString now = QDateTime::currentDateTime().toString();
   QString Time = now;
   Time.remove(0, 11);
   Time.chop(8);

   QString TodaysDate = now;
   TodaysDate.remove(0, 8);
   TodaysDate.chop(14);

   //Format Date and Start / End Time
   QString programDate = startTime;
   //std::cout << qPrintable(startTime) << std::endl;
   programDate.remove(0, 8);
   programDate.chop(9);

   QString startHour = startTime;
   startHour.remove(0, 11);
   startHour.chop(6);
   //startTime.remove(2, 1);
   QString startMin = startTime;
   startMin.remove(0, 14);
   startMin.chop(3);

   QString endHour = endTime;
   endHour.remove(0, 11);
   endHour.chop(6);
   QString endMin = endTime;
   endMin.remove(0, 14);
   endMin.chop(3);
   //endTime.remove(2,1);

   int startTimeMinutes = (startHour.toInt() * 60) + startMin.toInt();
   int endTimeMinutes = (endHour.toInt() * 60) + endMin.toInt();

   if (programDate.toInt() < TodaysDate.toInt())
   {
       startTimeMinutes = startTimeMinutes - (24 * 60);
   }
   if (programDate.toInt() > TodaysDate.toInt())
   {
       startTimeMinutes = startTimeMinutes + (24 * 60);
       endTimeMinutes = endTimeMinutes + (24 * 60);
   }
   if (endTimeMinutes < startTimeMinutes)
   {
       endTimeMinutes = endTimeMinutes + (24 * 60);
   }

   //std::cout << startTimeMinutes << " : " << endTimeMinutes << std::endl;
   int duration = endTimeMinutes - startTimeMinutes;
   //std::cout << "duration: " << duration << std::endl;

   float startLocation = ((startTimeMinutes * ((m_viewWidth/3)*2))/60);
   float progDuration = ((duration * ((m_viewWidth/3)*2))/60);

   //std::cout << "startLocation: " << startLocation << " progDuration: " << progDuration << std::endl;

   QColor colour;
   if (category == "Drama")
   { colour = Qt::red;}
   else if (category == "Education/Science/Factual")
   { colour = Qt::gray;}
   else if (category == "Entertainment")
   { colour = Qt::darkMagenta;}
   else if (category == "Kids")
   { colour = Qt::darkYellow;}
   else if (category == "Leisure/Hobbies")
   { colour = Qt::green;}
   else if (category == "Movie")
   { colour = Qt::green;}
   else if (category == "Music/Ballet/Dance")
   { colour = Qt::magenta;}
   else if (category == "News")
   { colour = Qt::darkGreen;}
   else if (category == "Social/Policical/Economics")
   { colour = Qt::darkRed;}
   else if (category == "Sports")
   { colour = Qt::green;}
   else
   { colour = Qt::white;}

    Program *item = new Program;
    //item->setBackgroundColor(QColor(Qt::blue));
    //item->setBackgroundColor(QColor::fromRgb(0,51,102));
    int row = (channelCount * 60) + 20;
    QRect rect(startLocation + 60, row, progDuration, 60);
    item->setPosition(rect);
    item->setText(title);
    item->setSubtitle(subtitle);
    item->setDescription(description);
    item->setChanId(channelID);
    item->setCategory(category);
    item->setGenreColor(colour);
    timeline->addItem(item);

}

void MainWindow::getChannelList()
{
    //ui->graphicsView->
    m_viewHeight = 350; //ui->graphicsView->geometry().height();
    m_viewWidth = 350; //ui->graphicsView->geometry().width();

    //std::cout << "width: " << m_viewWidth << std::endl;
    QSqlQuery query(db);
       query.exec("SELECT chanId, channel FROM channels");
int channelCount = 0;
       while (query.next()) {
           QString chanId = query.value(0).toString();
           QString channelName = query.value(1).toString();
           getPrograms(chanId, channelCount);
           buildChannels(channelName,chanId,channelCount);
           channelCount++;

       }
       int sceneheight = (channelCount * 60) + 30;
       timeline->setSceneRect(0, 0, ((m_viewWidth/3)*48)+ 60, sceneheight );

       QString now = QDateTime::currentDateTime().toString();
       QString Time = now;
       Time.remove(0, 11);
       Time.chop(8);

       QString nowHour = Time;
       nowHour.chop(3);
       Time.remove(0,3);
       float guidePosition = ((((nowHour.toInt() * 60) + Time.toInt()) * ((m_viewWidth/3)*2))/60) + (m_viewWidth/3) ;
       ui->graphicsView->centerOn(guidePosition,0);
       emit doneBuildingGuide();
       db.close();
       guidedb.close();
}

void MainWindow::getPrograms(QString chanId, int channelCount)
{
    QSqlQuery query(guidedb);
           query.exec("SELECT chanID, title, subtitle, description, endTime, startTime, category FROM guideData");
           //qDebug("in getPrograms");

           while (query.next()) {
               QString  channelId = query.value(0).toString();
              // std::cout << qPrintable(channelId) << " = " << qPrintable(chanId) << std::endl;
               QString title = query.value(1).toString();
               QString subtitle = query.value(2).toString();
               QString description = query.value(3).toString();
               QString endTime = query.value(4).toString();
               QString startTime = query.value(5).toString();
               QString category = query.value(6).toString();
               //std::cout << qPrintable(description) << std::endl;
               //std::cout << qPrintable(category) << std::endl;
               //std::cout << qPrintable(channelId) << " = " << qPrintable(chanId) << qPrintable(endTime) << std::endl;

               if (channelId == chanId){
                  //std::cout << qPrintable(channelId) << " = " << qPrintable(chanId) << std::endl;
                  buildGuide(channelId, title, subtitle, description, endTime, startTime, category, channelCount);
               }

       }

}


QString MainWindow::formatTime(QString now)
{

    //Required format 2011-04-07T19:00
   // currentDateTime Sun Apr 10 20:22:35 2011
    //QDateTime now = QDateTime::currentDateTime();

    QString Year = now;
    Year.remove(0, 20);

    QString Month = now;
    Month.remove(0, 4);
    Month.chop(16);

    qDebug(qPrintable(Month));

    if (Month == "Jan"){
        Month = "01";
    }else if (Month == "Feb"){
        Month = "02";
    }else if (Month == "Mar"){
        Month = "03";
    }else if (Month == "Apr"){
        Month = "04";
    }else if (Month == "May"){
        Month = "05";
    }else if (Month == "Jun"){
        Month = "06";
    }else if (Month == "Jul"){
        Month = "07";
    }else if (Month == "Aug"){
        Month = "08";
    }else if (Month == "Sep"){
        Month = "09";
    }else if (Month == "Oct"){
        Month = "10";
    }else if (Month == "Nov"){
        Month = "11";
    }else if (Month == "Dec"){
        Month = "12";
    }

    QString Date = now;
    Date.remove(0, 8);
    Date.chop(14);

    QString Time = now;
    Time.remove(0, 11);
    Time.chop(8);
    //std::cout << qPrintable(StartTime) << std::endl;
    QString FormattedDateTime = Year + "-" + Month + "-" + Date + "T" + Time;

    return FormattedDateTime;
}


void MainWindow::on_pushButton_clicked()
{
    QSettings settings("OpenSource", "MythDroid");
    settings.setValue("ipAddress", ui->ipAddress1->text());
    ui->stackedWidget->setCurrentIndex(0);
    setUpDataBases();
    getData();
}

