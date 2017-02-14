#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

QJsObjectData::QJsObjectData()
{
	m_strKeyName = QString();
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
	QJsonObject jsonTempObj = m_jsonValue.toObject();
	jsonTempObj.insert(strName, QJsonValue(boolValue));
	updateJsonValue(QJsonValue(jsonTempObj));
}

void QJsObjectData::setAttribute(const QString &strName, int intValue)
{
	QJsonObject jsonTempObj = m_jsonValue.toObject();
	jsonTempObj.insert(strName, QJsonValue(intValue));
	updateJsonValue(QJsonValue(jsonTempObj));
}

void QJsObjectData::setAttribute(const QString &strName, double doubleValue)
{
	QJsonObject jsonTempObj = m_jsonValue.toObject();
	jsonTempObj.insert(strName, QJsonValue(doubleValue));
	updateJsonValue(QJsonValue(jsonTempObj));
}

void QJsObjectData::setAttribute(const QString &strName, QString strValue)
{
	QJsonObject jsonTempObj = m_jsonValue.toObject();
	jsonTempObj.insert(strName, QJsonValue(strValue));
	updateJsonValue(QJsonValue(jsonTempObj));
}

void QJsObjectData::setAttribute(const QString &strName, qint64 int64Value)
{
	QJsonObject jsonTempObj = m_jsonValue.toObject();
	jsonTempObj.insert(strName, QJsonValue(int64Value));
	updateJsonValue(QJsonValue(jsonTempObj));
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
	case QMetaType::Double:
		setAttribute(strName, varValue.toDouble());
		break;
	case QMetaType::QString:
		setAttribute(strName, varValue.toString());
		break;
	case QMetaType::ULongLong:
		setAttribute(strName, varValue.toLongLong());
		break;
	default:
		//qDebug() << "[ERROR] QJsObjectData::setAttribute, Unknown variant type.";
		break;
	}
}

void QJsObjectData::removeAttribute(const QString &strName)
{
	QJsonObject jsonTempObj = m_jsonValue.toObject();
	jsonTempObj.remove(strName);
	updateJsonValue(QJsonValue(jsonTempObj));
}
