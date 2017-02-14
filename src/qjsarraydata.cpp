#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

QJsArrayData::QJsArrayData()
{
	m_strKeyName = QString();
	m_jsonValue  = QJsonValue(QJsonArray());
	// null instance
	m_parent = nullptr;
}

QJsArrayData::~QJsArrayData()
{
	this->removeChildren();
}

bool QJsArrayData::isArray()
{
	return true;
}

bool QJsArrayData::isDocument()
{
	return false;
}

bool QJsArrayData::isObject()
{
	return false;
}

int QJsArrayData::count()
{
	return m_jsonValue.toArray().count();
}

QVariant QJsArrayData::getValueAt(int idx)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	return jsonTempArr.at(idx).toVariant();
}

QExplicitlySharedDataPointer<QJsNodeData> QJsArrayData::getNodeAt(int idx)
{
	return m_mapChildren.value(QString::number(idx));
}

void QJsArrayData::setValueAt(int idx, bool boolValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	if (idx < 0 || idx >= jsonTempArr.size())
	{
		return;
	}
	jsonTempArr.replace(idx, QJsonValue(boolValue));
	updateJsonValue(QJsonValue(jsonTempArr));
}

void QJsArrayData::setValueAt(int idx, int intValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	if (idx < 0 || idx >= jsonTempArr.size())
	{
		return;
	}
	jsonTempArr.replace(idx, QJsonValue(intValue));
	updateJsonValue(QJsonValue(jsonTempArr));
}

void QJsArrayData::setValueAt(int idx, double doubleValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	if (idx < 0 || idx >= jsonTempArr.size())
	{
		return;
	}
	jsonTempArr.replace(idx, QJsonValue(doubleValue));
	updateJsonValue(QJsonValue(jsonTempArr));
}

void QJsArrayData::setValueAt(int idx, QString strValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	if (idx < 0 || idx >= jsonTempArr.size())
	{
		return;
	}
	jsonTempArr.replace(idx, QJsonValue(strValue));
	updateJsonValue(QJsonValue(jsonTempArr));
}

void QJsArrayData::setNodeAt(int idx, QExplicitlySharedDataPointer<QJsNodeData> nodeValue)
{
	replaceChild(QString::number(idx), nodeValue);
}

void QJsArrayData::setObjectAt(int idx, QExplicitlySharedDataPointer<QJsObjectData> objValue)
{
	replaceChild(QString::number(idx), objValue);
}

void QJsArrayData::setArrayAt(int idx, QExplicitlySharedDataPointer<QJsArrayData> arrValue)
{
	replaceChild(QString::number(idx), arrValue);
}

bool QJsArrayData::isBool(int idx)
{
	return m_jsonValue.toArray().at(idx).isBool();
}

bool QJsArrayData::isInteger(int idx)
{
	bool isOK = false;
	m_jsonValue.toArray().at(idx).toString().toInt(&isOK);
	return isOK;
}

bool QJsArrayData::isDouble(int idx)
{
	return m_jsonValue.toArray().at(idx).isDouble();
}

bool QJsArrayData::isString(int idx)
{
	return m_jsonValue.toArray().at(idx).isString();
}

bool QJsArrayData::isObject(int idx)
{
	return m_jsonValue.toArray().at(idx).isObject();
}

bool QJsArrayData::isArray(int idx)
{
	return m_jsonValue.toArray().at(idx).isArray();
}

void QJsArrayData::appendValue(bool boolValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	jsonTempArr.append(QJsonValue(boolValue));
	updateJsonValue(QJsonValue(jsonTempArr));
}

void QJsArrayData::appendValue(int intValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	jsonTempArr.append(QJsonValue(intValue));
	updateJsonValue(QJsonValue(jsonTempArr));
}

void QJsArrayData::appendValue(double doubleValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	jsonTempArr.append(QJsonValue(doubleValue));
	updateJsonValue(QJsonValue(jsonTempArr));
}

void QJsArrayData::appendValue(QString strValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	jsonTempArr.append(QJsonValue(strValue));
	updateJsonValue(QJsonValue(jsonTempArr));
}

void QJsArrayData::appendObject(QExplicitlySharedDataPointer<QJsObjectData> objValue)
{
	objValue->m_strKeyName.clear();
	appendChild(objValue);
}

void QJsArrayData::appendArray(QExplicitlySharedDataPointer<QJsArrayData> arrValue)
{
	appendChild(arrValue);
}

QVariant QJsArrayData::removeValueAt(int idx)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	if (idx < 0 || idx >= jsonTempArr.size())
	{
		return QVariant();
	}
	QJsonValue varVal = jsonTempArr.takeAt(idx);
	updateJsonValue(QJsonValue(jsonTempArr));
	return varVal.toVariant();
}

int QJsArrayData::removeValue(int intValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	for (int i = 0; i < jsonTempArr.count(); i++)
	{
		if (jsonTempArr.at(i).isDouble() && ((int)jsonTempArr.at(i).isDouble() == intValue))
		{
			QJsonValue intVal = jsonTempArr.takeAt(i);
			updateJsonValue(QJsonValue(jsonTempArr));
			return (int)intVal.toDouble();
		}
	}
	return 0;
}

QString QJsArrayData::removeValue(QString strValue)
{
	QJsonArray jsonTempArr = m_jsonValue.toArray();
	for (int i = 0; i < jsonTempArr.count(); i++)
	{
		if (jsonTempArr.at(i).isString() && jsonTempArr.at(i).toString().compare(strValue, Qt::CaseInsensitive) == 0)
		{
			QJsonValue strVal = jsonTempArr.takeAt(i);
			updateJsonValue(QJsonValue(jsonTempArr));
			return strVal.toString();
		}
	}
	return QString();
}


