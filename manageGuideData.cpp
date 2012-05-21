#include "mainwindow.h"

bool MainWindow::setupGuideDb(QString dbname)
{
    //QTreeView *view = ui->treeView;

    Q_ASSERT(dbname.length()>0);
    //Q_CHECK_PTR(view);

    // using SQLITE driver
    guidedb = QSqlDatabase::addDatabase("QSQLITE", "guideData");
    guidedb.setDatabaseName(dbname);

    if(guidedb.open())
    {
        // Try to locate the contacts database.
        // If it is not available create it.
        bool found = false;
        foreach (QString table, guidedb.tables())
        {
            if(table == "guideData")
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            QSqlQuery query(guidedb);
            query.exec("CREATE TABLE guideData ( chanId VARCHAR(16), title VARCHAR(32),subtitle VARCHAR(50), description VARCHAR(500), category VARCHAR(32), endTime VARCHAR(32), startTime VARCHAR(32) )");
        }
        // create a new model and use the contacts table
        dbguidemodel = new QSqlTableModel(this,guidedb);
        dbguidemodel->setTable("guideData");
        // All changes to the model will be applied immediately to the database
        dbguidemodel->setEditStrategy(QSqlTableModel::OnFieldChange);
        dbguidemodel->select();
        // creating the model/view association
        //view->setModel(dbmodel);

    }
    else
    {
        return false;
    }

    return true;
}

void MainWindow::AddtoGuideDB( QString chanId, QString title, QString subtitle, QString description, QString category, QString endTime, QString startTime )
{
        //qDebug("Add Data");
        QSqlRecord program = dbguidemodel->record();
        program.setValue("chanId", chanId);
        program.setValue("title", title);
        program.setValue("subtitle", subtitle);
        program.setValue("description", description);
        program.setValue("category", category);
        program.setValue("endTime", endTime);
        program.setValue("startTime", startTime);
        // insert a new record (-1)
        dbguidemodel->insertRecord(-1,program);



    }
