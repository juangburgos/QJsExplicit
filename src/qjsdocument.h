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

	QString   fromJson(const QByteArray &json);

	//QString  	fromBinaryData(const QByteArray &data);

};

#endif // QJSDOCUMENT_H
