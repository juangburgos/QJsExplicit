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

	static QJsDocument fromJson(const QByteArray &json);

	static QJsDocument fromBinaryData(const QByteArray &bindata);

};

#endif // QJSDOCUMENT_H
