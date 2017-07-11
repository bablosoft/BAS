#include "moduledll.h"
#include <QDir>
#include <QJsonObject>
#include <QMap>
#include <QDir>
#include <QJsonDocument>
#include <QByteArray>
#include <QVariant>
#include <QImage>
#include <QBuffer>
#include <QPainter>
#include <QImageReader>
#include <QDebug>
#include <opencv2/imgproc/imgproc.hpp>

extern "C" {

using namespace cv;

cv::Mat QImageToCvMat( QImage *inImage )
{
    QImage temp = inImage->convertToFormat( QImage::Format_RGB888 );

    cv::Mat mat(temp.height(), temp.width(),
                  CV_8UC3,
                  const_cast<uchar*>(temp.bits()),
                  static_cast<size_t>(temp.bytesPerLine())
                  );

    return mat.clone();

}


    struct Image
    {
        QImage * Data;
        QString Format;
    };
    using ImageData = QHash<int, Image>;

    void* StartDll()
    {
        return 0;
    }

    void EndDll(void * DllData)
    {

    }

    void* StartThread()
    {
        ImageData *data = new ImageData();

        return data;
    }

    void EndThread(void * DllData)
    {
        ImageData * data = (ImageData *)DllData;
        QHashIterator<int, Image> i(*data);
        while (i.hasNext())
        {
            i.next();
            delete i.value().Data;
        }
        delete data;
    }


    void ImageProcessingLoad(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;

        int Id =  qrand() % 1000000;
        QByteArray IdString = QString::number(Id).toUtf8();
        QByteArray Array = QByteArray::fromBase64(InputJson);
        QBuffer buffer(&Array);
        buffer.open( QIODevice::ReadOnly );
        QImageReader reader(&buffer);
        Image i;
        i.Format = QString::fromUtf8(reader.format());

        QImage *image = new QImage(reader.read());

        buffer.close();

        i.Data = image;

        data->insert(Id,i);

        char * ResMemory = AllocateSpace(IdString.size(),AllocateData);
        memcpy(ResMemory, IdString.data(), IdString.size() );
    }

    void ImageProcessingDelete(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString IdString = InputJson;
        int Id = IdString.toInt();
        if(!data->contains(Id))
            return;
        delete data->operator[](Id).Data;
        data->remove(Id);
    }

    void ImageProcessingGetSize(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString IdString = InputJson;
        int Id = IdString.toInt();
        QString res;
        if(data->contains(Id))
        {
            res.append(QString::number(data->operator[](Id).Data->width()));
            res.append(",");
            res.append(QString::number(data->operator[](Id).Data->height()));
        }
        else
        {
            res = "0,0";
        }

        QByteArray Res = res.toUtf8();

        char * ResMemory = AllocateSpace(Res.size(),AllocateData);
        memcpy(ResMemory, Res.data(), Res.size() );

    }

    void ImageProcessingGetData(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString IdString = InputJson;
        int Id = IdString.toInt();
        QByteArray Res;
        if(data->contains(Id))
        {
            QBuffer buffer(&Res);
            buffer.open(QIODevice::WriteOnly);
            Image i = data->operator[](Id);

            i.Data->save(&buffer,i.Format.toUtf8());
            buffer.close();

            Res = Res.toBase64();
        }

        char * ResMemory = AllocateSpace(Res.size(),AllocateData);
        memcpy(ResMemory, Res.data(), Res.size() );

    }

    void ImageProcessingInsert(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;
        QStringList ParamsList = InputsString.split(",");
        if(ParamsList.length()!=4)
            return;
        int Id1 = ParamsList[0].toInt();
        int Id2 = ParamsList[1].toInt();
        int X = ParamsList[2].toInt();
        int Y = ParamsList[3].toInt();

        if(data->contains(Id1) && data->contains(Id2))
        {
            QImage *Image1 = data->operator[](Id1).Data;
            QImage *Image2 = data->operator[](Id2).Data;
            QPainter painter;
            painter.begin(Image1);
            painter.drawImage(X,Y,*Image2);
        }


    }

    void ImageProcessingCreate(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;
        QStringList ParamsList = InputsString.split(",");
        if(ParamsList.length()!=6)
            return;
        int W = ParamsList[0].toInt();
        int H = ParamsList[1].toInt();
        int ColorR = ParamsList[2].toInt();
        int ColorG = ParamsList[3].toInt();
        int ColorB = ParamsList[4].toInt();
        int ColorA = ParamsList[5].toInt();
        QColor Color(ColorR,ColorG,ColorB,ColorA);

        int Id =  qrand() % 1000000;
        QByteArray IdString = QString::number(Id).toUtf8();

        QImage *image = new QImage(W,H,QImage::Format_ARGB32);
        image->fill(Color);

        Image i;

        i.Data = image;
        i.Format = "png";

        data->insert(Id,i);

        char * ResMemory = AllocateSpace(IdString.size(),AllocateData);
        memcpy(ResMemory, IdString.data(), IdString.size() );


    }
    void ImageProcessingConvert(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {

        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;

        int index = InputsString.indexOf(',');
        if(index < 0)
            return;
        QString IdString = InputsString.mid(0,index);
        int Id = IdString.toInt();
        QString Format = InputsString.remove(0,index + 1);
        if(data->contains(Id))
        {
            data->operator[](Id).Format = Format;
        }
    }
    void ImageProcessingGetPixel(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;
        QStringList ParamsList = InputsString.split(",");
        if(ParamsList.length()!=3)
            return;
        int Id = ParamsList[0].toInt();
        int X = ParamsList[1].toInt();
        int Y = ParamsList[2].toInt();

        QString res;
        if(data->contains(Id))
        {
            QImage * image = data->operator[](Id).Data;
            QColor c = image->pixelColor(X,Y);
            res += QString::number(c.red());
            res += ",";
            res += QString::number(c.green());
            res += ",";
            res += QString::number(c.blue());
            res += ",";
            res += QString::number(c.alpha());

        }
        else
        {
            res = "0,0,0,0";
        }

        QByteArray Res = res.toUtf8();

        char * ResMemory = AllocateSpace(Res.size(),AllocateData);
        memcpy(ResMemory, Res.data(), Res.size() );
    }
    void ImageProcessingSetPixel(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;
        QStringList ParamsList = InputsString.split(",");
        if(ParamsList.length()!=7)
            return;
        int Id = ParamsList[0].toInt();
        int X = ParamsList[1].toInt();
        int Y = ParamsList[2].toInt();
        int ColorR = ParamsList[3].toInt();
        int ColorG = ParamsList[4].toInt();
        int ColorB = ParamsList[5].toInt();
        int ColorA = ParamsList[6].toInt();
        QColor Color(ColorR,ColorG,ColorB,ColorA);

        if(data->contains(Id))
        {
            QImage * image = data->operator[](Id).Data;
            image->setPixelColor(X,Y,Color);
        }
    }
    void ImageProcessingResize(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;
        QStringList ParamsList = InputsString.split(",");
        if(ParamsList.length()!=3)
            return;
        int Id = ParamsList[0].toInt();
        int W = ParamsList[1].toInt();
        int H = ParamsList[2].toInt();
        if(data->contains(Id))
        {
            QImage * image = data->operator[](Id).Data;
            image->swap(image->scaled(W,H));
        }
    }
    void ImageProcessingFill(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;
        QStringList ParamsList = InputsString.split(",");
        if(ParamsList.length()!=9)
            return;
        int Id = ParamsList[0].toInt();
        int X = ParamsList[1].toInt();
        int Y = ParamsList[2].toInt();
        int W = ParamsList[3].toInt();
        int H = ParamsList[4].toInt();
        int ColorR = ParamsList[5].toInt();
        int ColorG = ParamsList[6].toInt();
        int ColorB = ParamsList[7].toInt();
        int ColorA = ParamsList[8].toInt();
        QColor Color(ColorR,ColorG,ColorB,ColorA);

        if(data->contains(Id))
        {
            QImage * image = data->operator[](Id).Data;
            QPainter painter(image);
            painter.fillRect(X,Y,W,H,Color);
        }
    }
    void ImageProcessingSub(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;
        QStringList ParamsList = InputsString.split(",");
        if(ParamsList.length()!=5)
            return;
        int Id = ParamsList[0].toInt();
        int X = ParamsList[1].toInt();
        int Y = ParamsList[2].toInt();
        int W = ParamsList[3].toInt();
        int H = ParamsList[4].toInt();
        QString IdString;
        if(data->contains(Id))
        {
            QImage * image = data->operator[](Id).Data;
            QImage *imageres = new QImage();
            imageres->swap(image->copy(X,Y,W,H));
            Image i;
            i.Format = data->operator[](Id).Format;
            i.Data = imageres;
            int Id =  qrand() % 1000000;
            IdString = QString::number(Id);
            data->insert(Id,i);
        }
        QByteArray IdStringData = IdString.toUtf8();
        char * ResMemory = AllocateSpace(IdStringData.size(),AllocateData);
        memcpy(ResMemory, IdStringData.data(), IdStringData.size() );

    }
    void ImageProcessingText(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;
        QStringList ParamsList = InputsString.split(",");
        if(ParamsList.length()<12)
            return;
        int Id = ParamsList[0].toInt();
        int X = ParamsList[1].toInt();
        int Y = ParamsList[2].toInt();
        int W = ParamsList[3].toInt();
        int H = ParamsList[4].toInt();
        QString Font = ParamsList[5].toInt();
        int ColorR = ParamsList[6].toInt();
        int ColorG = ParamsList[7].toInt();
        int ColorB = ParamsList[8].toInt();
        int ColorA = ParamsList[9].toInt();
        QColor Color(ColorR,ColorG,ColorB,ColorA);
        int Size = ParamsList[10].toInt();
        ParamsList.erase(ParamsList.begin(),ParamsList.begin() + 11);
        QString Text = ParamsList.join(',');
        if(data->contains(Id))
        {
            QImage * image = data->operator[](Id).Data;
            QPainter painter(image);
            QFont font = QFont(Font);
            QPen pen = painter.pen();
            pen.setColor(Color);
            painter.setPen(pen);
            font.setPixelSize(Size);
            painter.setFont(font);
            painter.drawText(X,Y,W,H,Qt::AlignHCenter |   Qt::TextWordWrap,Text);
        }
    }
    void ImageProcessingFind(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        ImageData * data = (ImageData *)ThreadData;
        QString InputsString = InputJson;
        QStringList ParamsList = InputsString.split(",");
        if(ParamsList.length()!=2)
            return;
        int Id1 = ParamsList[0].toInt();
        int Id2 = ParamsList[1].toInt();
        QString res;
        if(data->contains(Id1) && data->contains(Id2))
        {

            QImage * image1 = data->operator[](Id1).Data;
            QImage * image2 = data->operator[](Id2).Data;

            Mat i1 = QImageToCvMat(image1);
            Mat i2 = QImageToCvMat(image2);

            Mat result;

            int result_cols =  i1.cols - i2.cols + 1;
            int result_rows = i1.rows - i2.rows + 1;

            result.create( result_rows, result_cols, CV_32FC1 );


            matchTemplate( i1, i2, result, CV_TM_CCOEFF_NORMED );


            //normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

            double minVal; double maxVal; Point minLoc; Point maxLoc;
            Point matchLoc;

            minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

            matchLoc = maxLoc;

            i1.release();
            i2.release();
            result.release();


            res += QString::number(matchLoc.x);
            res += ",";
            res += QString::number(matchLoc.y);
            res += ",";
            res += QString::number((int)(maxVal * 100.0));
        }
        else
        {
            res = "0,0,0";
        }

        QByteArray Res = res.toUtf8();

        char * ResMemory = AllocateSpace(Res.size(),AllocateData);
        memcpy(ResMemory, Res.data(), Res.size() );
    }



}
