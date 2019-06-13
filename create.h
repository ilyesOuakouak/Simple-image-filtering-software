#ifndef CREATE_H
#define CREATE_H




#include <QMainWindow>
#include<QtSql>
#include<QMessageBox>
#include<QDebug>
#include<QFileInfo>
#include<login.h>

namespace Ui {
class create;
}

class create : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase myDatabase;


    /*
    // function to close the connection to the database
    void connectionClose(){
        myDatabase.close();
    }

    // function to check the connection to the database
    bool connectionOpen(){
    myDatabase = QSqlDatabase::addDatabase("QSQLITE");
    myDatabase.setDatabaseName("/home/ily19/Desktop/c++ development /sqlDatabase/merde.db");
    QFileInfo checkFile("/home/ily19/Desktop/c++ development /sqlDatabase/merde/merde.db");
    if(checkFile.isFile())
    {
        if(myDatabase.open())
        {
            qDebug()<<"Connetion to the database established";
        }
    }
    else{
            qDebug()<<"No database file found";
        }


    }
    */




public:
    explicit create(QWidget *parent = 0);
    ~create();

private slots:
    void on_create_account_btn_clicked();

    void on_go_to_login_link_clicked();

private:
    Ui::create *ui;
};

#endif // CREATE_H
