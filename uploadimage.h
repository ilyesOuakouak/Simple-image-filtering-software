#ifndef UPLOADIMAGE_H
#define UPLOADIMAGE_H

#include <QDialog>
#include<QMainWindow>
#include<QFileDialog>
#include<QBitmap>
#include<QImage>
#include<QPixmap>
#include<QMessageBox>


#include "imageprocess.h" // including the class ImageProcess

namespace Ui {
class UploadImage;
}

class UploadImage : public QDialog
{
    Q_OBJECT

public:
    explicit UploadImage(QWidget *parent = 0);
    ~UploadImage();


    void loadImage(); // method to load the image
    void about(); // about the application


protected:
    int meth; // To design the methode
    void afficherParametre();
    void cacherParametre();

private slots:

    void on_uploadImage_clicked();
    void on_GrayScale_clicked();

    void on_initializer_clicked();

    void on_about_clicked();

    void on_gaussian_clicked();

    void on_h_Gradient_clicked();

    void on_v_gradient_clicked();

    void on_contoursDetection_clicked();


    void on_SaveImageResult_clicked();


private:
    Ui::UploadImage *ui;
    int aa ;
    int bb;

    ImageProcess *im1; //creating an object instance to the class ImageProcess

    QImage image1;
    QImage image2;

    QString m_chemin;
    QString fileName;
};

#endif // UPLOADIMAGE_H
