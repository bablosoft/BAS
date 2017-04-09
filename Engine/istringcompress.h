#ifndef ISTRINGCOMPRESS_H
#define ISTRINGCOMPRESS_H

#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT IStringCompress: public QObject
    {
            Q_OBJECT
        public:
            explicit IStringCompress(QObject *parent = 0);


        public slots:
            virtual QString Compress(const QString& data) = 0;
            virtual QString Uncompress(const QString& data) = 0;
    };
}

#endif // ISTRINGCOMPRESS_H
