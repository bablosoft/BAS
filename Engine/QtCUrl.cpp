/* This file is part of QtCurl
 *
 * Copyright (C) 2013-2014 Pavel Shmoylov <pavlonion@gmail.com>
 *
 * Thanks to Sergey Romanenko for QStringList options support and for
 * trace function.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software Foundation.
 *
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "QtCUrl.h"

#include <iostream>

#include <QUrl>

#include <QStringList>

#include <string>
#include <sstream>
#include <QByteArray>
#include "every_cpp.h"


int writer(char* data, size_t size, size_t nmemb, std::string* buffer) {

    // What we will return
    int result = 0;

    // Is there anything in the buffer?
    if (buffer != NULL) {
        // Append the data to the buffer
        buffer->append(data, size * nmemb);

        // How much did we write?
        result = size * nmemb;
    }

    return result;
}


int writer_file(char* data, size_t size, size_t nmemb, QFile* file){

    // What we will return
    int result = 0;

    // Append the data to the buffer
    file->write(data, size * nmemb);

    // How much did we write?
    result = size * nmemb;


    return result;
}



int writer2(char* data, size_t size, size_t nmemb, BufferAndFilter* buffer_and_filter) {

    int result = 0;

    if(buffer_and_filter->Filter->operator ==("*"))
    {
        buffer_and_filter->Buffer->append(data, size * nmemb);
    }else
    {
        if(QString::fromUtf8(data, size * nmemb).contains(buffer_and_filter->Filter))
        {
            buffer_and_filter->Buffer->append(data, size * nmemb);
        }
    }


    // How much did we write?
    result = size * nmemb;


    return result;


}


int progress_callback(void *clientp,   curl_off_t dltotal,   curl_off_t dlnow,   curl_off_t ultotal,   curl_off_t ulnow)
{
    if(*((bool *)clientp))
        return 1;
    else
        return 0;
}

#ifdef QTCURL_DEBUG
int trace(CURL *handle, curl_infotype type, unsigned char *data, size_t size, void *userp)
{
	std::cerr<< data << std::endl;
	return 1;
}
#endif


QtCUrl::QtCUrl() {
	/*
	 * It's necessarily to call curl_global_init ones before the first use
	 * of curl_easy_init.
	 *
	 * http://curl.haxx.se/libcurl/c/curl_easy_init.html
	 */

	_curl = curl_easy_init();

	_errorBuffer = new char[CURL_ERROR_SIZE];
    _buffer_and_filter.Buffer = &_buffer2;
    _buffer_and_filter.Filter = &Filter;
}

void QtCUrl::SetFilter(const QString& Filter)
{
    this->Filter = Filter;
    _buffer_and_filter.Filter = &Filter;
}


QtCUrl::~QtCUrl() {
    while(_slist.count()) {
		curl_slist_free_all(_slist.first());
		_slist.removeFirst();
	}
    curl_easy_cleanup(_curl);
    delete[] _errorBuffer;
}



void QtCUrl::exec(Options& opt)
{
	setOptions(opt);

    if(!FileName.isEmpty())
        File.open(QIODevice::WriteOnly);

    AutoDelete = false;
	_lastCode = Code(curl_easy_perform(_curl));

    if(!FileName.isEmpty())
        File.close();
}

void QtCUrl::SetFileName(const QString& FileName)
{
    this->FileName = FileName;
}



QByteArray QtCUrl::GetLogByteArray()
{
    return QByteArray(_buffer2.c_str(),_buffer2.length());
}

QByteArray QtCUrl::GetDataByteArray()
{
    return QByteArray(_buffer.c_str(),_buffer.length());
}

QString QtCUrl::GetLog()
{
    if(Filter.isEmpty())
    {
        return "";
    }

    const char *reply = _buffer2.c_str();



    return reply;
}

void QtCUrl::MarkAutoDelete()
{
    AutoDelete = true;
}


void QtCUrl::setOptions(Options& opt) {
	Options defaults;
    //defaults[CURLOPT_FAILONERROR] = true;
	defaults[CURLOPT_ERRORBUFFER].setValue(_errorBuffer);

    if(FileName.isEmpty())
    {
        defaults[CURLOPT_WRITEFUNCTION].setValue(&writer);
        defaults[CURLOPT_WRITEDATA].setValue(&_buffer);
    }else
    {
        File.setFileName(FileName);

        defaults[CURLOPT_WRITEFUNCTION].setValue(&writer_file);
        defaults[CURLOPT_WRITEDATA].setValue(&File);
    }

    defaults[CURLOPT_PROGRESSFUNCTION].setValue(&progress_callback);
    defaults[CURLOPT_PROGRESSDATA].setValue(&AutoDelete);

    defaults[CURLOPT_NOPROGRESS].setValue(0);

    defaults[CURLOPT_SSL_VERIFYPEER].setValue(false);
    defaults[CURLOPT_SSL_VERIFYHOST].setValue(false);

    if(!Filter.isEmpty())
    {
        //defaults[CURLOPT_VERBOSE].setValue(1);
        defaults[CURLOPT_HEADERFUNCTION].setValue(&writer2);
        defaults[CURLOPT_WRITEHEADER].setValue(&_buffer_and_filter);
    }
    //defaults[CURLOPT_VERBOSE].setValue(1);



#ifdef QTCURL_DEBUG
	curl_easy_setopt(_curl, CURLOPT_VERBOSE, 1);
	curl_easy_setopt(_curl, CURLOPT_DEBUGFUNCTION, trace);
#endif

	OptionsIterator i(defaults);

	while (i.hasNext()) {
		i.next();

		if (! opt.contains(i.key())) {
			opt[i.key()] = i.value();
		}
	}

    if(opt.contains(CURLOPT_POSTFIELDSIZE))
    {
        int val = opt[CURLOPT_POSTFIELDSIZE].toInt();
        curl_easy_setopt(_curl, CURLOPT_POSTFIELDSIZE, (long)val);
    }

	i = opt;

	while (i.hasNext()) {
		i.next();
		QVariant value = i.value();


        if(i.key() == CURLOPT_POSTFIELDSIZE)
        {
            continue;
        }

		switch (value.type()) {
			case QVariant::Bool:
			case QVariant::Int: {
				int val = value.toInt();
				curl_easy_setopt(_curl, i.key(), val);
				break;
			}
			case QVariant::ByteArray: {
				QByteArray ba = value.toByteArray();
				curl_easy_setopt(_curl, i.key(), ba.constData());
				break;
			}
			case QVariant::Url: {
				QByteArray ba = value.toUrl().toEncoded();
				curl_easy_setopt(_curl, i.key(), ba.constData());
				break;
			}
			case QVariant::String: {
                curl_easy_setopt(_curl, i.key(), value.toString().toUtf8().data());
				break;
			}
			case QVariant::ULongLong: {
				qulonglong val = value.toULongLong();
				curl_easy_setopt(_curl, i.key(), (void*) val);
				break;
			}
			case QVariant::StringList: {
				struct curl_slist *slist = NULL;
				foreach (const QString &tmp, value.toStringList()) {
					 slist = curl_slist_append(slist, tmp.toUtf8().data());
				}
				_slist.append(slist);
				curl_easy_setopt(_curl, i.key(), slist);
				break;
			}
			default:
				const QString typeName = value.typeName();

				if (typeName == "QtCUrl::WriterPtr") {
					curl_easy_setopt(_curl, i.key(), value.value<WriterPtr>());
                }else if (typeName == "QtCUrl::WriterFilePtr") {
                    curl_easy_setopt(_curl, i.key(), value.value<WriterFilePtr>());
                }else if (typeName == "QtCUrl::HeaderPtr") {
                    curl_easy_setopt(_curl, i.key(), value.value<HeaderPtr>());
                }else if (typeName == "QtCUrl::ProgressPtr") {
                    curl_easy_setopt(_curl, i.key(), value.value<ProgressPtr>());
                }
				else if (typeName == "std::string*") {
					curl_easy_setopt(_curl, i.key(), value.value<std::string*>());
				}
                else if (typeName == "BufferAndFilter*") {
                    curl_easy_setopt(_curl, i.key(), value.value<BufferAndFilter*>());
                }
				else if (typeName == "char*") {
					curl_easy_setopt(_curl, i.key(), value.value<char*>());
				}
                else if (typeName == "bool*") {
                    curl_easy_setopt(_curl, i.key(), value.value<bool*>());
                }
                else if (typeName == "QFile*") {
                    curl_easy_setopt(_curl, i.key(), value.value<QFile*>());
                }
				else {
                    //qDebug() << "[QtCUrl] Unsupported option type: " << typeName;
				}
		}
	}
}



