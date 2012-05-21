#include <QDir>
#include "mainwindow.h"

void MainWindow::doDownload(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager2.get(request);

    currentDownloads.append(reply);
    return;
    //std::cout << "in do download" << std::endl;
}

QString MainWindow::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }
    std::cout << qPrintable(basename) << std::endl;
    return basename;

}

bool MainWindow::saveToDisk(const QString &filename, QIODevice *data)
{
    QString IconFolder = "/sdcard/MythDroidData/Icons/";
    QDir folder(IconFolder);
    if (!QDir(folder).exists()){
            QDir().mkdir(IconFolder);
    }
    QFile file(IconFolder + filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename),
                qPrintable(file.errorString()));
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

void MainWindow::getChannelIcons()
{
    QSqlQuery query(db);
       query.exec("SELECT chanId FROM channels");

       while (query.next()) {
           QString name = query.value(0).toString();

           QString Icon = "/sdcard/MythDroidData/Icons/" + name + ".jpg";
           if (!QFile().exists(Icon)){
           QUrl url("http://192.168.1.10:6544/Myth/GetChannelIcon?ChanId=" + name);
           doDownload(url);
           }
           QSettings settings("OpenSource", "MythDroid");
           settings.setValue("icons", 1);
       }
       return;
}

void MainWindow::downloadFinished(QNetworkReply *reply)
{
    //std::cout << "download finished" << std::endl;
    QUrl url = reply->url();
    if (reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
    } else {
        QString urlString = url.toEncoded().constData();
        urlString.remove(0, 52);
        QString filename = urlString + ".jpg";
        if (saveToDisk(filename, reply))
            printf("Download of %s succeeded\n", qPrintable(filename));
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();

   if (currentDownloads.isEmpty())
       return;
            //buildChannelList();

        // all downloads finished
       // QCoreApplication::instance()->quit();
}


