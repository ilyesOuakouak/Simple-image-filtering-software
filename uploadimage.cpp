#include "uploadimage.h"
#include "ui_uploadimage.h"

#include <QtGui>

UploadImage::UploadImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UploadImage)
{
   QMainWindow *mainwindowCreated = new QMainWindow();







    ui->setupUi(this);
}

UploadImage::~UploadImage()
{
    delete ui;
}


void UploadImage::loadImage()
{
    QSize size(ui->space_label->width(), ui->space_label->height());
    QImage image2 = image1.scaled(size, Qt::KeepAspectRatio);

    ui->space_label->setPixmap(QPixmap::fromImage(image2));

}



// function to upload a file image

void UploadImage::on_uploadImage_clicked()
{
    // cacherParametre();
    fileName = QFileDialog::getOpenFileName(this, "Open a File...", QString());

    if (!fileName.isEmpty()) {
        QImage image(fileName);
        image1=image;
        m_chemin=fileName;
        if (image1.isNull()) {
            QMessageBox::information(this, "MainWindow ",
                                     tr("You have to load an image").arg(fileName));
            return;
        }
        int fact=image1.depth()/8;
        im1=new ImageProcess(image1.height(),fact*image1.width());
        this->loadImage();
    }
}



void UploadImage::on_GrayScale_clicked()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "You have to load an Image!!!,"
                                 "To open a window click on the button open an Image "
                                 " Then select an image");
        return;
    }
    meth=1;
    // cacherParametre();
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new ImageProcess(image1.height(),fact*image1.width());
    }
    this->setWindowTitle(tr("From RGB to GRAY"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    if(fact==4)
    { im1->rgb_to_lum(fact);}
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();;
}

// function to initialize the image after a filter has been applied
void UploadImage::on_initializer_clicked()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "You have to load an Image!!!,"
                                 "To open a window click on the button open an Image "
                                 " Then select an image");
        return;
    }
    //cacherParametre();
    QImage image(fileName);
    image1=image;
    m_chemin=fileName;

    this->loadImage();
}

// function to make a short description about the application

void UploadImage::on_about_clicked()
{
    QMessageBox::about(this, "About the Application",
                       tr("<p>This <b> Application</b> has been developed using C++ and Qt library "
                          "The idea is to filter a given image by using different types of filters. "
                          "All the functions used are a pure c++ function no computer vision library such as opencv is used"));
}



void UploadImage::on_gaussian_clicked()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "You have to load an Image!!!,"
                                 "To open a window click on the button open an Image "
                                 " Then select an image");
        return;
    }
    // cacherParametre();
    meth=0;
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new ImageProcess(image1.height(),fact*image1.width());
    }
    this->setWindowTitle(tr("Filtre Gaussien"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    im1->gaussian(fact);
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}

void UploadImage::on_h_Gradient_clicked()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "You have to load an Image!!!,"
                                 "To open a window click on the button open an Image "
                                 " Then select an image");
        return;
    }
    // cacherParametre();
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new ImageProcess(image1.height(),fact*image1.width());
    }
    this->setWindowTitle(tr("Horizental Gradient Filter"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    im1->normey(fact);
    im1->transferty();
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}

void UploadImage::on_v_gradient_clicked()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "You have to load an Image!!!,"
                                 "To open a window click on the button open an Image "
                                 " Then select an image");
        return;
    }
    //cacherParametre();
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new ImageProcess(image1.height(),fact*image1.width());
    }
    // MainWindow *w = new MainWindow();
    this->setWindowTitle(tr("vertical Gradient Filter"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    im1->normex(fact);
    im1->transfertx();
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}



void UploadImage::on_contoursDetection_clicked()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "You have to load an Image!!!,"
                                 "To open a window click on the button open an Image "
                                 " Then select an image");
        return;
    }
    meth=2;
    // cacherParametre();
    int fact=image1.depth()/8;
    if(im1->isNULL())
    {
        im1=new ImageProcess(image1.height(),fact*image1.width());
    }
    this->setWindowTitle(tr("Contours Detection"));
    this->show();
    this->image1=this->image1.copy();
    im1->transfert_to_exim(&(this->image1));
    im1->normex(fact);
    im1->normey(fact);
    im1->norme(fact);
    im1->transfert_to_qim(&(this->image1));
    this->loadImage();
    this->repaint();
}






//function to save an image -----------
void UploadImage::on_SaveImageResult_clicked()
{
    if (image1.isNull()) {
        QMessageBox::information(this, "MainWindow ",
                                 "You have to load an Image!!!,"
                                 "To open a window click on the button open an Image "
                                 " Then select an image");
        return;
    }

    QString chemin = QFileDialog::getSaveFileName(this, "Enregistrer le fichier", m_chemin,"Image (*.jpeg)");
    QFile file(chemin);
    if(!file.open(QIODevice::WriteOnly))
        return;
    QImage im1=this->image1;
    im1.save(chemin,0);

}








//--------------------------------------------------------------------------------------------------



























