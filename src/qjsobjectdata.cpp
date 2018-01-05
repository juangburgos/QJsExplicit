#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

#include <QDebug>

QJsObjectData::QJsObjectData()
{
	m_strKeyName = "";
	m_jsonValue  = QJsonValue(QJsonObject());
	// null instance
	m_parent = nullptr;
}

QJsObjectData::~QJsObjectData()
{
	this->removeChildren();
}

bool QJsObjectData::isObject()
{
	return true;
}

bool QJsObjectData::isArray()
{
	return false;
}

bool QJsObjectData::isDocument()
{
	return false;
}

QStringList QJsObjectData::attributeNames()
{
	QStringList listAttrNames;
	QJsonObject jsonTempObj  = m_jsonValue.toObject();
	QStringList listKeys     = jsonTempObj.keys();
	for (int i = 0; i < listKeys.count(); i++)
	{
		QJsonValue jsonTempVal = jsonTempObj.value(listKeys.at(i));
		if (jsonTempVal.isBool() || jsonTempVal.isDouble() || jsonTempVal.isString())
		{
			listAttrNames.append(listKeys.at(i));
		}
	}
	return listAttrNames;
}

bool QJsObjectData::hasAttribute(const QString &strName)
{
	return m_jsonValue.toObject().keys().contains(strName);
}

QVariant QJsObjectData::attributeValue(QString strName)
{
	return m_jsonValue.toObject().value(strName).toVariant();
}

bool QJsObjectData::isBool(QString strName)
{
	return m_jsonValue.toObject().value(strName).isBool();
}

bool QJsObjectData::isInteger(QString strName)
{
	bool isOK = false;
	m_jsonValue.toObject().value(strName).toString().toInt(&isOK);
	return isOK;
}

bool QJsObjectData::isDouble(QString strName)
{
	return m_jsonValue.toObject().value(strName).isDouble();
}

bool QJsObjectData::isString(QString strName)
{
	return m_jsonValue.toObject().value(strName).isString();
}

void QJsObjectData::setAttribute(const QString &strName, bool boolValue)
{
	setAttributeInternal(strName, boolValue);
}

void QJsObjectData::setAttribute(const QString &strName, int intValue)
{
	setAttributeInternal(strName, intValue);
}

void QJsObjectData::setAttribute(const QString &strName, qulonglong intULLValue)
{
	setAttributeInternal(strName, (qint64)intULLValue);
}

void QJsObjectData::setAttribute(const QString &strName, float floatValue)
{
	setAttributeInternal(strName, floatValue);
}

void QJsObjectData::setAttribute(const QString &strName, double doubleValue)
{
	setAttributeInternal(strName, doubleValue);
}

void QJsObjectData::setAttribute(const QString &strName, QString strValue)
{
	setAttributeInternal(strName, strValue);
}

void QJsObjectData::setAttribute(const QString &strName, qint64 int64Value)
{
	setAttributeInternal(strName, int64Value);
}

void QJsObjectData::setAttribute(const QString &strName, quint32 uint32Value)
{
	setAttributeInternal(strName, (qint32)uint32Value);
}

void QJsObjectData::setAttribute(const QString &strName, QVariant varValue)
{
	switch (varValue.type())
	{
	case QMetaType::Bool:
		setAttribute(strName, varValue.toBool());
		break;
	case QMetaType::Int:
		setAttribute(strName, varValue.toInt());
		break;
	case QMetaType::UInt:
		setAttribute(strName, varValue.toUInt());
		break;
	case QMetaType::Float:
		setAttribute(strName, varValue.toFloat());
		break;
	case QMetaType::Double:
		setAttribute(strName, varValue.toDouble());
		break;
	case QMetaType::QString:
		setAttribute(strName, varValue.toString());
		break;
	case QMetaType::ULongLong:
		setAttribute(strName, varValue.toULongLong());
		break;
	case QMetaType::LongLong:
		setAttribute(strName, varValue.toLongLong());
		break;
	default:
		Q_ASSERT_X(false, "QJsObjectData::setAttribute", "Unknown variant type for QJsObject");
		qDebug() << "[ERROR] QJsObjectData::setAttribute, Unknown variant type : " << varValue.type();
		break;
	}
}

void QJsObjectData::removeAttribute(const QString &strName)
{
	// implicit shared object upodating
	QJsonObject tmpObject = m_jsonValue.toObject();
	tmpObject.remove(strName);
	m_jsonValue = tmpObject;
}

#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)

void QJsObjectData::recalcDebugVars(bool bForce/* = true*/)
{
	// NOTE : creating attributes moved to QJsNodeData::jsObjToJson for efficiency
	// call base class method
	QJsNodeData::recalcDebugVars(bForce);
}

#endif