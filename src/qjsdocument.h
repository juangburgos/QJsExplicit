#ifndef QJSDOCUMENT_H
#define QJSDOCUMENT_H

#include "qjsnode.h"

class QJsDocument : public QJsNode
{
public:
    QJsDocument();
    QJsDocument(const QJsDocument &);
    QJsDocument &operator=(const QJsDocument &);
    ~QJsDocument();

	QJsObject cloneToObject(const QString &strKeyName = "");

	// TODO : Move document to inherit from object

	// TODO : QString &error

	static QJsDocument fromJson(const QByteArray &json, QString &error);

	static QJsDocument fromBinaryData(const QByteArray &bindata, QString &error);

};

#endif // QJSDOCUMENT_H
