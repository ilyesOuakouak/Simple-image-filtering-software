#include "create.h"
#include "ui_create.h"

create::create(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::create)
{
    ui->setupUi(this);



    myDatabase = QSqlDatabase::addDatabase("QSQLITE");
    myDatabase.setDatabaseName("/home/ily19/Desktop/c++ development /sqlDatabase/mydatabase/database.db");
    QFileInfo checkFile("/home/ily19/Desktop/c++ development /sqlDatabase/mydatabase/database.db");

    if(checkFile.isFile())
    {
        if(myDatabase.open())
        {
            qDebug()<<"connected";
        }
    }else{
        qDebug()<<"not connected";
    }

}

create::~create()
{
    delete ui;
}

void create::on_create_account_btn_clicked()
{

    if(!myDatabase.isOpen())
    {
        QMessageBox::critical(this, tr("not connected"), tr("no connection established"));
        return;
    }

    QString username, email, password, confirm_password;

    username = ui->edit_username->text();
    email = ui->edit_email->text();
    password = ui->edit_password->text();
    confirm_password = ui->edit_confirm_password->text();

    myDatabase.open();
    QSqlQuery query;


    if(!username.isEmpty() && !email.isEmpty() && !password.isEmpty() && !confirm_password.isEmpty())
    {
        if(password.length()>6)
        {
            if(password == confirm_password)
            {
                query.prepare("INSERT INTO users(username, email, password) VALUES('"+username+"', '"+email+"', '"+password+"')");
                if(query.exec())
                {
                    QMessageBox::critical(this, tr("saved"), tr("your account hase been created"));

                    QString connection;
                    connection = myDatabase.connectionName();
                    myDatabase.close();
                    myDatabase = QSqlDatabase();
                    myDatabase.removeDatabase(connection);

                    // open the new wintow to login
                    this->hide();
                    login login_window;
                    login_window.setModal(true);
                    login_window.exec();

                }else
                {
                    QMessageBox::critical(this, tr("error"), query.lastError().text());
                }


            }else{
                QMessageBox::critical(this, tr("error"), tr("Passwords are not identical"));
            }

        }else{
            QMessageBox::critical(this, tr("error"), tr("Password should have at least character"));
        }

    }else{
        QMessageBox::critical(this, tr("error"), tr("you have to fill all the fields"));

            }














    /*
    QString username, email, password, confirm_password;

    username = ui->edit_username->text();
    email = ui->edit_password->text();
    password = ui->edit_password->text();
    confirm_password = ui->edit_confirm_password->text();

    if(!connectionOpen() == false)
    {
        qDebug()<<"no connection to the database";
        return;
    }

    connectionOpen();
    QSqlQuery query;

    query.prepare("INSERT INTO users(username, email, password) VALUES(:username, :email, :password)");
    query.bindValue(":username", username);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    if(query.exec())
    {
        QMessageBox::critical(this, tr("Inserted"), tr("Your Account Has Been Successfully Created"));
        connectionClose();
    }else{
        QMessageBox::critical(this, tr("not Inserted"), query.lastError().text());
    }
*/








}

void create::on_go_to_login_link_clicked()
{
    this->hide();
    login log;
    log.setModal(true);
    log.exec();
}
