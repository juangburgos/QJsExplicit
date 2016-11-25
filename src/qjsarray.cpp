#include "qjsnode.h"
#include "qjsobject.h"
#include "qjsarray.h"
#include "qjsdocument.h"

#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

QJsArray::QJsArray()
{
    data = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData());
}

QJsArray::QJsArray(const QJsArray &rhs)
{
    data = rhs.data;
}

QJsArray &QJsArray::operator=(const QJsArray &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QJsArray::~QJsArray()
{

}

int QJsArray::count() const
{
	return data->toArray()->count();
}

QVariant QJsArray::getValueAt(int idx) const
{
	return data->toArray()->getValueAt(idx);
}

QJsNode QJsArray::getNodeAt(int idx) const
{
	QJsNode node;
	node.data = data->toArray()->getNodeAt(idx);
	return node;
}

bool QJsArray::isBool(int idx) const
{
	return data->toArray()->isBool(idx);
}

bool QJsArray::isInteger(int idx) const
{
	return data->toArray()->isInteger(idx);
}

bool QJsArray::isDouble(int idx) const
{
	return data->toArray()->isDouble(idx);
}

bool QJsArray::isString(int idx) const
{
	return data->toArray()->isString(idx);
}

bool QJsArray::isObject(int idx) const
{
	return data->toArray()->isObject(idx);
}

bool QJsArray::isArray(int idx) const
{
	return data->toArray()->isArray(idx);
}

void QJsArray::setValueAt(int idx, bool boolValue)
{
	data->toArray()->setValueAt(idx, boolValue);
}

void QJsArray::setValueAt(int idx, int intValue)
{
	data->toArray()->setValueAt(idx, intValue);
}

void QJsArray::setValueAt(int idx, double doubleValue)
{
	data->toArray()->setValueAt(idx, doubleValue);
}

void QJsArray::setValueAt(int idx, QString strValue)
{
	data->toArray()->setValueAt(idx, strValue);
}

void QJsArray::setValueAt(int idx, const char *str)
{
	data->toArray()->setValueAt(idx, QString::fromUtf8(str));
}

void QJsArray::setNodeAt(int idx, QJsNode nodeValue)
{
	data->toArray()->setNodeAt(idx, nodeValue.data);
}

void QJsArray::setObjectAt(int idx, QJsObject objValue)
{
	data->toArray()->setObjectAt(idx, objValue.data->toObject());
}

void QJsArray::setArrayAt(int idx, QJsArray arrValue)
{
	data->toArray()->setArrayAt(idx, arrValue.data->toArray());
}

void QJsArray::appendValue(bool boolValue)
{
	data->toArray()->appendValue(boolValue);
}

void QJsArray::appendValue(int intValue)
{
	data->toArray()->appendValue(intValue);
}

void QJsArray::appendValue(double doubleValue)
{
	data->toArray()->appendValue(doubleValue);
}

void QJsArray::appendValue(QString strValue)
{
	data->toArray()->appendValue(strValue);
}

void QJsArray::appendObject(QJsObject objValue)
{
	data->toArray()->appendObject(objValue.data->toObject());
}

void QJsArray::appendArray(QJsArray arrValue)
{
	data->toArray()->appendArray(arrValue.data->toArray());
}

QVariant QJsArray::removeValueAt(int idx)
{
	return data->toArray()->removeValueAt(idx);
}

int QJsArray::removeValue(int intValue)
{
	return data->toArray()->removeValue(intValue);
}

QString QJsArray::removeValue(QString strValue)
{
	return data->toArray()->removeValue(strValue);
}
