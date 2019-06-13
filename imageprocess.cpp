#include <assert.h>
#include "imageprocess.h"
#define min(a,b)    ((a<b) ? a : b)
#define max(a,b)    ((a<b) ? b : a)
#define abs(a)      ((a<0) ? -a : a)

ImageProcess::ImageProcess()
{

}

ImageProcess::ImageProcess( int nHeight, int nWidth ) : m_ppImage(NULL)
{
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    Allouer( );
}


// Width of image

int ImageProcess::Width(void )
{
    return Width();
}

// Height of image

int ImageProcess::Height(void )
{
    return Height();
}

// method for allocation memeory
void ImageProcess::Allouer()
{


    if (  m_ppImage != NULL )
        return;

    m_ppImage = new byte* [m_nHeight];
    m_normex = new PIXEL* [m_nHeight];
    m_normey = new PIXEL* [m_nHeight];
    m_norme = new PIXEL* [m_nHeight];
    m_buffer = new byte* [m_nHeight];

    for ( int i=0 ;i< m_nHeight; i++ )
    {
        m_ppImage[i]= new byte[ m_nWidth];
        m_normex[i]= new PIXEL[ m_nWidth];
        m_normey[i]= new PIXEL[ m_nWidth];
        m_norme[i]= new PIXEL[ m_nWidth];
        m_buffer[i]= new byte[ m_nWidth];
    }
    return;
}


// Delete memory allocated
void ImageProcess::Liberer( )
{
    for ( int i=0 ;i< m_nHeight; i++ )
    {

        delete [] m_ppImage[i];
        delete [] m_normex[i];
        delete [] m_normey[i];
        delete [] m_norme[i];
        delete [] m_buffer[i];
    }

    delete [] m_ppImage;
    delete [] m_normex;
    delete [] m_normey;
    delete [] m_norme;
    delete [] m_buffer;
    return;
}


// check if the image isn't null
bool ImageProcess::isNULL()
{
    if(m_ppImage ==NULL || m_nWidth==0 || m_nHeight==0 )
        return true;
    else
        return false;
}

void ImageProcess::normey(int fact)
{
    int i,j,k;
    int moy[8];

    for(i=0;i<8;i++)
    { moy[i]=0;}

    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    m_normey[i][j+k]=min(m_ppImage[i-1][j+k-fact]+2*m_ppImage[i-1][j+k]+m_ppImage[i-1][j+fact+k]-m_ppImage[i+1][j+k-fact]-2*m_ppImage[i+1][j+k]-m_ppImage[i+1][j+fact+k],255);
                }
            }
            else
            {
                m_normey[i][j]=min(m_ppImage[i-1][j-1]+2*m_ppImage[i-1][j]+m_ppImage[i-1][j+1]-m_ppImage[i+1][j-1]-2*m_ppImage[i+1][j]-m_ppImage[i+1][j+1],255);
            }
        }
    }
}

void ImageProcess::normex(int fact)
{
    int i,j,k;
    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    m_normex[i][j+k]=min(m_ppImage[i-1][j+k-fact]+2*m_ppImage[i][j+k-fact]+m_ppImage[i+1][j+k-fact]-m_ppImage[i-1][j+fact+k]-2*m_ppImage[i][j+fact+k]-m_ppImage[i+1][j+fact+k],255);
                }
            }
            else
            {
                m_normex[i][j]=min(m_ppImage[i-1][j-1]+2*m_ppImage[i][j-1]+m_ppImage[i+1][j-1]-m_ppImage[i-1][j+1]-2*m_ppImage[i][j+1]-m_ppImage[i+1][j+1],255);
            }
        }
    }
}

// The norme methode
void ImageProcess::norme(int fact)
{
    int i,j,k;

    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    m_ppImage[i][j+k]=255-min(abs(m_normex[i][j+k])+abs(m_normey[i][j+k]),255);
                }
            }
            else
            {
                m_ppImage[i][j]=255-min(255, abs(m_normex[i][j])+abs(m_normey[i][j]));
            }
        }
    }
}

void ImageProcess::transfertx()
{   int i,j;

    for(i=0;i<m_nHeight;i++)
    {
        for(j=0;j<m_nWidth;j++)
        {
            m_ppImage[i][j]=255-min(255,abs(m_normex[i][j]));
        }
    }
}

void ImageProcess::transferty()
{   int i,j;

    for(i=0;i<m_nHeight;i++)
    {
        for(j=0;j<m_nWidth;j++)
        {
            m_ppImage[i][j]=255-min(255,abs(m_normey[i][j]));
        }
    }
}


void ImageProcess::transfert_to_exim(QImage * pqImg)
{
    float fact;
    int w, h;
    byte * pLine;

    fact=pqImg->depth()/8;
    w=pqImg->width();
    h=pqImg->height() ;

    for ( int i = 0 ; i< h ; i++ )
    {
        pLine = pqImg->scanLine(i);
        memcpy ( m_ppImage[i],  pLine , w*fact*sizeof(byte ));
        assert(m_ppImage[i] != NULL);
    }

}

void ImageProcess::transfert_to_qim(QImage * pqImg)
{
    int w,h;
    float fact;
    byte* pLine;
    w=m_nWidth;
    h=m_nHeight;
    fact=pqImg->depth()/8;

    for ( int i=0 ; i<h ; i++ )
    {
        pLine=pqImg->scanLine(i);
        memcpy ( pLine, m_ppImage[i] , w*sizeof(byte ));
    }
}

void ImageProcess::rgb_to_lum( int fact)
{
    int i,j;

    unsigned char lum;

    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            lum=(min(min(m_ppImage[i][j],m_ppImage[i][j+1]),m_ppImage[i][j+2])+max(max(m_ppImage[i][j],m_ppImage[i][j+1]),m_ppImage[i][j+2]))/2;
            m_ppImage[i][j]=lum;
            m_ppImage[i][j+1]=lum;
            m_ppImage[i][j+2]=lum;
            m_ppImage[i][j+3]=0;
        }
    }
}

// function to implement gaussian filter

void ImageProcess::gaussian(int fact)
{
    int i,j,k;
    for(i=2;i<m_nHeight-2;i++)
    {
        for(j=2*fact;j<m_nWidth-2*fact;j=j+fact)
        {
            if(fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    m_ppImage[i][j+k]=min(255,(2*m_ppImage[i-2][j+k-2*fact]+4*m_ppImage[i-2][j+k-fact]+5*m_ppImage[i-2][j+k]+4*m_ppImage[i-2][j+k+fact]+2*m_ppImage[i-2][j+k+2*fact]+
                                               4*m_ppImage[i-1][j+k-2*fact]+9*m_ppImage[i-1][j+k-fact]+12*m_ppImage[i-1][j+k]+9*m_ppImage[i-1][j+k+fact]+4*m_ppImage[i-1][j+k+2*fact]+
                                               5*m_ppImage[i][j+k-2*fact]+12*m_ppImage[i][j+k-fact]+15*m_ppImage[i][j+k]+12*m_ppImage[i][j+k+fact]+5*m_ppImage[i][j+k+2*fact]+
                                               4*m_ppImage[i+1][j+k-2*fact]+9*m_ppImage[i+1][j+k-fact]+12*m_ppImage[i+1][j+k]+9*m_ppImage[i+1][j+k+fact]+4*m_ppImage[i+1][j+k+2*fact]+
                                               2*m_ppImage[i+2][j+k-2*fact]+4*m_ppImage[i+2][j+k-fact]+5*m_ppImage[i+2][j+k]+4*m_ppImage[i+2][j+k+fact]+2*m_ppImage[i+2][j+k+2*fact])/157);
                }
            }
            else
            {
                m_ppImage[i][j]=min(255,(2*m_ppImage[i-2][j-2*fact]+4*m_ppImage[i-2][j-fact]+5*m_ppImage[i-2][j]+4*m_ppImage[i-2][j+fact]+2*m_ppImage[i-2][j+2*fact]+
                                         4*m_ppImage[i-1][j-2*fact]+9*m_ppImage[i-1][j-fact]+12*m_ppImage[i-1][j]+9*m_ppImage[i-1][j+fact]+4*m_ppImage[i-1][j+2*fact]+
                                         5*m_ppImage[i][j-2*fact]+12*m_ppImage[i][j-fact]+15*m_ppImage[i][j]+12*m_ppImage[i][j+fact]+5*m_ppImage[i][j+2*fact]+
                                         4*m_ppImage[i+1][j-2*fact]+9*m_ppImage[i+1][j-fact]+12*m_ppImage[i+1][j]+9*m_ppImage[i+1][j+fact]+4*m_ppImage[i+1][j+2*fact]+
                                         2*m_ppImage[i+2][j-2*fact]+4*m_ppImage[i+2][j-fact]+5*m_ppImage[i+2][j]+4*m_ppImage[i+2][j+fact]+2*m_ppImage[i+2][j+2*fact])/157);
            }
        }
    }
}
