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
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

QJsArray::QJsArray(const QJsArray &rhs)
{
	data.reset();
    data = rhs.data;
}

QJsArray &QJsArray::operator=(const QJsArray &rhs)
{
	if (this != &rhs) {
		data.reset();
		data.operator=(rhs.data);
	}
	return *this;
}

QJsArray::~QJsArray()
{
	data.reset();
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
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsArray::setValueAt(int idx, int intValue)
{
	data->toArray()->setValueAt(idx, intValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsArray::setValueAt(int idx, double doubleValue)
{
	data->toArray()->setValueAt(idx, doubleValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsArray::setValueAt(int idx, QString strValue)
{
	data->toArray()->setValueAt(idx, strValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsArray::setValueAt(int idx, const char *str)
{
	data->toArray()->setValueAt(idx, QString::fromUtf8(str));
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsArray::setNodeAt(int idx, QJsNode nodeValue)
{
	data->toArray()->setNodeAt(idx, nodeValue.data);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	nodeValue.data->recalcDebugVars();
#endif
}

void QJsArray::setObjectAt(int idx, QJsObject objValue)
{
	data->toArray()->setObjectAt(idx, objValue.data->toObject());
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	objValue.data->recalcDebugVars();
#endif
}

void QJsArray::setArrayAt(int idx, QJsArray arrValue)
{
	data->toArray()->setArrayAt(idx, arrValue.data->toArray());
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	arrValue.data->recalcDebugVars();
#endif
}

void QJsArray::appendValue(bool boolValue)
{
	data->toArray()->appendValue(boolValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsArray::appendValue(int intValue)
{
	data->toArray()->appendValue(intValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsArray::appendValue(double doubleValue)
{
	data->toArray()->appendValue(doubleValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsArray::appendValue(QString strValue)
{
	data->toArray()->appendValue(strValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsArray::appendObject(QJsObject objValue)
{
	data->toArray()->appendObject(objValue.data->toObject());
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	objValue.data->recalcDebugVars();
#endif
}

void QJsArray::appendArray(QJsArray arrValue)
{
	data->toArray()->appendArray(arrValue.data->toArray());
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	arrValue.data->recalcDebugVars();
#endif
}

QVariant QJsArray::removeValueAt(int idx)
{
	QVariant & retVal = data->toArray()->removeValueAt(idx);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	return retVal;
}

int QJsArray::removeValue(int intValue)
{
	int retVal = data->toArray()->removeValue(intValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	return retVal;
}

QString QJsArray::removeValue(QString strValue)
{
	QString & retVal = data->toArray()->removeValue(strValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	return retVal;
}

QJsArray QJsArray::clone() const
{
	return QJsNode::clone().toArray();
}
