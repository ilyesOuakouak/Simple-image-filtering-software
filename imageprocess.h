#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include<iostream>
#include<fstream>
#include<QImage>
typedef unsigned char byte;
typedef double PIXEL;

class ImageProcess
{

protected:
    int m_nWidth ;  // image width
    int m_nHeight ;  // image height

    byte **m_ppImage;    // Image Matrix
    PIXEL **m_normex;    // Matrix of horizontal mask
    PIXEL **m_normey;    // Matrix of vertical mask
    PIXEL **m_norme;     // Matrix of gradient norme

    byte **m_buffer;     // Image Buffer

    // methode  for memory allocation
    void Allouer();
    void Liberer();

public:
    ImageProcess(); //default constructor
    ImageProcess(int , int); // constructor with arguments

    ~ImageProcess(); // deconstructor to destroy the object created dynamically
    int Width() ;  // Method to get the Width of the image
    int Height( );  // Method to get the Height of the image

    bool isNULL();
    // Transfer Methods between QImage and ImageProcess

    void transfert_to_qim(QImage*);
    void transfert_to_exim(QImage*);

    // Gradients norms

    void normex(int);
    void normey(int);
    void norme(int);

    // Transfer buffer methods

    void transfertx(void);
    void transferty(void);
    void transfert_n(void);

    // Transforme an image from RGB to GRAY LEVEL

    void rgb_to_lum(int);

    void gaussian(int);
    void fenetrage(int,int, int, int, double);
    void seuillage(int,int,  double);
    void binarisation(int,int, int);
    void binarisation_par_intervalle(int,int, int, int);
    void seuillage_par_intervalle(int,int, int , int, double);

    void inversion(int);
    void moyenneur(int);
    void mediane(int,int);
    byte tri(byte* , int);

    // recuperer le Buffer

    byte* get_buffer(void) ;

};



















#endif // IMAGEPROCESS_H
