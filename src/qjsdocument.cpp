#include "qjsnode.h"
#include "qjsobject.h"
#include "qjsarray.h"
#include "qjsdocument.h"

#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

QJsDocument::QJsDocument()
{
    data = QExplicitlySharedDataPointer<QJsDocumentData>(new QJsDocumentData());
}

QJsDocument::QJsDocument(const QJsDocument &rhs)
{
    data = rhs.data;
}

QJsDocument &QJsDocument::operator=(const QJsDocument &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QJsDocument::~QJsDocument()
{

}

QJsObject QJsDocument::cloneToObject(const QString &strKeyName /*= ""*/)
{
	auto res = data->toDocument()->cloneToObject(strKeyName);
	QJsObject obj;
	obj.data = res;
	return obj;
}

QString QJsDocument::fromJson(const QByteArray &json)
{
	return data->toDocument()->fromJson(json);
}
