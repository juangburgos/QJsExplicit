#include "qjsnode.h"
#include "qjsobject.h"
#include "qjsarray.h"
#include "qjsdocument.h"

#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

QJsObject::QJsObject()
{
    data = QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData());
}

QJsObject::QJsObject(const QJsObject &rhs)
{
    data = rhs.data;
}

QJsObject &QJsObject::operator=(const QJsObject &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QJsObject::~QJsObject()
{

}

QStringList QJsObject::attributeNames()
{
	return data->toObject()->attributeNames();
}

bool QJsObject::hasAttribute(const QString &strName)
{
	return data->toObject()->hasAttribute(strName);
}

QVariant QJsObject::attributeValue(QString strName)
{
	return data->toObject()->attributeValue(strName);
}

bool QJsObject::isBool(QString strName)
{
	return data->toObject()->isBool(strName);
}

bool QJsObject::isInteger(QString strName)
{
	return data->toObject()->isInteger(strName);
}

bool QJsObject::isDouble(QString strName)
{
	return data->toObject()->isDouble(strName);
}

bool QJsObject::isString(QString strName)
{
	return data->toObject()->isString(strName);
}

void QJsObject::setAttribute(const QString &strName, bool boolValue)
{
	data->toObject()->setAttribute(strName, boolValue);
}

void QJsObject::setAttribute(const QString &strName, int intValue)
{
	data->toObject()->setAttribute(strName, intValue);
}

void QJsObject::setAttribute(const QString &strName, double doubleValue)
{
	data->toObject()->setAttribute(strName, doubleValue);
}

void QJsObject::setAttribute(const QString &strName, QString strValue)
{
	data->toObject()->setAttribute(strName, strValue);
}

void QJsObject::setAttribute(const QString &strName, const char *str)
{
	data->toObject()->setAttribute(strName, QString::fromUtf8(str));
}

void QJsObject::setAttribute(const QString &strName, qint64 int64Value)
{
	data->toObject()->setAttribute(strName, int64Value);
}

void QJsObject::removeAttribute(const QString &strName)
{
	data->toObject()->removeAttribute(strName);
}
