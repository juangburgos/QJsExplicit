#ifndef QJSDOCUMENT_H
#define QJSDOCUMENT_H

#include "qjsobject.h"

class QJsDocument : public QJsObject
{
public:
    QJsDocument();
    QJsDocument(const QJsDocument &);
    QJsDocument &operator=(const QJsDocument &);
    ~QJsDocument();

	static QJsDocument fromJson(const QByteArray &json, QString &error);

	static QJsDocument fromBinaryData(const QByteArray &bindata, QString &error);

};

#endif // QJSDOCUMENT_H
