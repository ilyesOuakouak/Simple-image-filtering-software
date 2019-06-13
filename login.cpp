#include "login.h"
#include "ui_login.h"
#include<QMainWindow>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    myDatabase = QSqlDatabase::addDatabase("QSQLITE");
    myDatabase.setDatabaseName("/home/ily19/Desktop/c++ development /sqlDatabase/mydatabase/database.db");
    QFileInfo checkFile("/home/ily19/Desktop/c++ development /sqlDatabase/mydatabase/database.db");

    if(checkFile.isFile())
    {
        if(myDatabase.open())
        {
            qDebug()<<"login connected";
        }
    }else{
        qDebug()<<"login not connected";
    }



}

login::~login()
{
    delete ui;
}



void login::on_login_btn_clicked()
{
    if(!myDatabase.isOpen())
    {
        QMessageBox::critical(this, tr("login not connected"), tr(" login no connection established"));
        return;
    }

    QString email, password;
    email = ui->login_email->text();
    password = ui->login_password->text();

    myDatabase.open();
    QSqlQuery sql;

    if(!email.isEmpty() && !password.isEmpty())
    {
        sql.prepare("SELECT * FROM users WHERE email = '"+email+"' AND password = '"+password+"'");
        if(sql.exec())
        {
            int count = 0;
            while(sql.next())
            {
                count ++;
            }

            if(count == 1 )
            {
                QMessageBox::critical(this,tr("welcome"), tr("welcome to your account"));
                ui->login_email->setText("");
                ui->login_password->setText("");
                QString connection;
                connection = myDatabase.connectionName();
                myDatabase.close();
                myDatabase = QSqlDatabase();
                myDatabase.removeDatabase(connection);

                this->hide();
                UploadImage a;
                a.setModal(true);
                a.exec();
            }

            if(count != 1)
                QMessageBox::critical(this, tr("no result"), tr("Email or Password is incorrect"));
        }
    }else{
        QMessageBox::critical(this, tr("error"), tr("Fill all the fields"));
    }


}

