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
	data.reset();
    data = rhs.data;
}

QJsObject &QJsObject::operator=(const QJsObject &rhs)
{
	if (this != &rhs) {
		data.reset();
		data.operator=(rhs.data);
	}
	return *this;
}

QJsObject::~QJsObject()
{
	data.reset();
}

QStringList QJsObject::attributeNames() const
{
	return data->toObject()->attributeNames();
}

bool QJsObject::hasAttribute(const QString &strName) const
{
	return data->toObject()->hasAttribute(strName);
}

QVariant QJsObject::attributeValue(QString strName) const
{
	return data->toObject()->attributeValue(strName);
}

template<typename T>
T QJsObject::attributeValue(QString strName) const
{
	return attributeValue(strName);
}
// bool specialization
template<>
bool QJsObject::attributeValue(QString strName) const
{
	return attributeValue(strName).toBool();
}
// int specialization
template<>
int QJsObject::attributeValue(QString strName) const
{
	return attributeValue(strName).toInt();
}
// qlonglong specialization
template<>
qlonglong QJsObject::attributeValue(QString strName) const
{
	return attributeValue(strName).toLongLong();
}
// double specialization
template<>
double QJsObject::attributeValue(QString strName) const
{
	return attributeValue(strName).toDouble();
}
// QString specialization
template<>
QString QJsObject::attributeValue(QString strName) const
{
	return attributeValue(strName).toString();
}

bool QJsObject::isBool(QString strName) const
{
	return data->toObject()->isBool(strName);
}

bool QJsObject::isInteger(QString strName) const
{
	return data->toObject()->isInteger(strName);
}

bool QJsObject::isDouble(QString strName) const
{
	return data->toObject()->isDouble(strName);
}

bool QJsObject::isString(QString strName) const
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

void QJsObject::setAttribute(const QString &strName, QVariant varValue)
{
	data->toObject()->setAttribute(strName, varValue);
}

void QJsObject::removeAttribute(const QString &strName)
{
	data->toObject()->removeAttribute(strName);
}

QJsObject QJsObject::clone() const
{
	return QJsNode::clone().toObject();
}
