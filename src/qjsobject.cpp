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
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
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

QJsObject QJsObject::setKeyName(const QString &strKeyName)
{
	// call original base class method
	QJsNode::setKeyName(strKeyName);
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
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

QJsObject QJsObject::setAttribute(const QString &strName, bool boolValue)
{
	data->toObject()->setAttribute(strName, boolValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::setAttribute(const QString &strName, int intValue)
{
	data->toObject()->setAttribute(strName, intValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::setAttribute(const QString &strName, float floatValue)
{
	data->toObject()->setAttribute(strName, floatValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::setAttribute(const QString &strName, double doubleValue)
{
	data->toObject()->setAttribute(strName, doubleValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::setAttribute(const QString &strName, QString strValue)
{
	data->toObject()->setAttribute(strName, strValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::setAttribute(const QString &strName, const char *str)
{
	data->toObject()->setAttribute(strName, QString::fromUtf8(str));
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::setAttribute(const QString &strName, quint32 uint32Value)
{
	data->toObject()->setAttribute(strName, uint32Value);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::setAttribute(const QString &strName, qint64 int64Value)
{
	data->toObject()->setAttribute(strName, int64Value);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::setAttribute(const QString &strName, qulonglong intULLValue)
{
	data->toObject()->setAttribute(strName, intULLValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::setAttribute(const QString &strName, QVariant varValue)
{
	data->toObject()->setAttribute(strName, varValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QVariant QJsObject::removeAttribute(const QString &strName)
{
	QVariant varOldVal = data->toObject()->removeAttribute(strName);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	return varOldVal;
}

QJsObject QJsObject::clone() const
{
	return QJsNode::clone().toObject();
}

QJsObject QJsObject::removeAllAttributes()
{
	foreach(QString strAttribute, attributeNames())
	{
		removeAttribute(strAttribute);
	}
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}

QJsObject QJsObject::mergeAttributesFrom(QJsObject jsObjSource)
{
	foreach(QString strAttribute, jsObjSource.attributeNames())
	{
		data->toObject()->setAttribute(strAttribute, jsObjSource.attributeValue(strAttribute));
	}
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
	// return this to allow chain
	QJsObject objThis;
	objThis.data = data;
	return objThis;
}
