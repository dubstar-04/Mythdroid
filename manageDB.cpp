#include "mainwindow.h"

bool MainWindow::setupDb(QString dbname)
{
    Q_ASSERT(dbname.length()>0);
    // using SQLITE driver
    db = QSqlDatabase::addDatabase("QSQLITE", "channels");
    db.setDatabaseName(dbname);

    if(db.open())
    {
        // Try to locate the channels database.
        // If it is not available create it.
        bool found = false;
        foreach (QString table, db.tables())
        {
            if(table == "channels")
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            QSqlQuery query(db);
            query.exec("CREATE TABLE channels (channel VARCHAR(32), chanId VARCHAR(16))");
        }
        // create a new model and use the contacts table
        dbmodel = new QSqlTableModel(this,db);
        dbmodel->setTable("channels");
        // All changes to the model will be applied immediately to the database
        dbmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
        dbmodel->select();
        // creating the model/view association
        //view->setModel(dbmodel);

    }
    else
        return false;

    return true;
}

void MainWindow::AddChanneltoDB(QString channelName, QString chanId)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM channels WHERE chanId =" + chanId );

    // Try to execute the query and position the result on the first and unique record
    if (!query.exec() || !query.first())
    {
        //qDebug("No Table Exists, add the record");
        QSqlRecord rec = dbmodel->record();
        rec.setValue("channel", channelName);
        rec.setValue("chanId", chanId);
        // insert a new record (-1)
        dbmodel->insertRecord(-1,rec);
    }
    // value(0) of first record will contain the "count(*)" value
    else if (query.value(0) == 0)
    {
        // no error, but no corresponding record in the table
        //qDebug("record is new, lets add it");
        QSqlRecord rec = dbmodel->record();
        rec.setValue("channel", channelName);
        rec.setValue("chanId", chanId);
        // insert a new record (-1)
        dbmodel->insertRecord(-1,rec);
    }
    else
    {
       // at least one corresponding record was found
        //qDebug("record Exists");
        }
    }
