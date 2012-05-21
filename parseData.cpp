#include "mainwindow.h"

bool MainWindow::parseFeed()
{
    db.transaction();
    guidedb.transaction();

    while (!xml.atEnd()) {

            if (xml.isStartElement() & xml.name() == "Channel")
                {

                 getTitle();
                xml.readNext();
               }else{
                xml.readNext();
                }
            }
    db.commit();
    guidedb.commit();

        return true;
    }

void MainWindow::getTitle()
{
    QString channelName, chanId, title, description, subtitle, category, endTime, startTime;

    while (!xml.atEnd()) {
       if (xml.isStartElement() & xml.name() == "Channel")
        {
    channelName = xml.attributes().value("channelName").toString(); //xml.readElementText(); //xml.name().toString(); //readElementText()
    chanId = xml.attributes().value("chanId").toString();
     //std::cout << qPrintable(channel) << std::endl;
     //std::cout << qPrintable(chanId) << std::endl;
     AddChanneltoDB(channelName, chanId);
     //return title, chanId;
       } if (xml.isStartElement() & xml.name() == "Program")
       {
           title = xml.attributes().value("title").toString();
           subtitle = xml.attributes().value("subTitle").toString();
           category = xml.attributes().value("category").toString();
           endTime = xml.attributes().value("endTime").toString();
           startTime = xml.attributes().value("startTime").toString();
           description = xml.readElementText(QXmlStreamReader::SkipChildElements);//.toString();
           //description.replace(QString("/"), QString("//"));
           //std::cout << qPrintable(description) << std::endl;
           //std::cout << qPrintable(subtitle) << std::endl;
          AddtoGuideDB( chanId, title, subtitle, description, category, endTime, startTime );
          // xml.readNext();
        }else if (xml.isStartElement() & xml.name() == "Recording"){
        std::cout << "recording" << std::endl;

    }else{

        xml.readNext();
        }
    }
   // return NULL;
}
