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
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsObject::setAttribute(const QString &strName, int intValue)
{
	data->toObject()->setAttribute(strName, intValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsObject::setAttribute(const QString &strName, double doubleValue)
{
	data->toObject()->setAttribute(strName, doubleValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsObject::setAttribute(const QString &strName, QString strValue)
{
	data->toObject()->setAttribute(strName, strValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsObject::setAttribute(const QString &strName, const char *str)
{
	data->toObject()->setAttribute(strName, QString::fromUtf8(str));
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsObject::setAttribute(const QString &strName, qint64 int64Value)
{
	data->toObject()->setAttribute(strName, int64Value);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsObject::setAttribute(const QString &strName, quint32 uint32Value)
{
	data->toObject()->setAttribute(strName, uint32Value);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsObject::setAttribute(const QString &strName, QVariant varValue)
{
	data->toObject()->setAttribute(strName, varValue);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

void QJsObject::removeAttribute(const QString &strName)
{
	data->toObject()->removeAttribute(strName);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}

QJsObject QJsObject::clone() const
{
	return QJsNode::clone().toObject();
}

void QJsObject::removeAllAttributes()
{
	foreach(QString strAttribute, attributeNames())
	{
		removeAttribute(strAttribute);
	}
}

void QJsObject::mergeAttributesFrom(QJsObject jsObjSource)
{
	foreach(QString strAttribute, jsObjSource.attributeNames())
	{
		//setAttribute(strAttribute, jsObjSource.attributeValue(strAttribute));
		data->toObject()->setAttribute(strAttribute, jsObjSource.attributeValue(strAttribute));
	}
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	data->recalcDebugVars();
#endif
}
