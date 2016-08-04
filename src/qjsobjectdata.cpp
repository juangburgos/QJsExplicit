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

bool QJsObjectData::isObject()
{
	return true;
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

void QJsObjectData::removeAttribute(const QString &strName)
{
	QJsonObject jsonTempObj = m_jsonValue.toObject();
	jsonTempObj.remove(strName);
	updateJsonValue(QJsonValue(jsonTempObj));
}
