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
	// TODO : use QVector
}

void QJsArrayData::setValueAt(int idx, int intValue)
{
	// TODO : use QVector
}

void QJsArrayData::setValueAt(int idx, double doubleValue)
{
	// TODO : use QVector
}

void QJsArrayData::setValueAt(int idx, QString strValue)
{
	// TODO : use QVector
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
	// TODO : use QVector
}

void QJsArrayData::appendValue(int intValue)
{
	// TODO : use QVector
}

void QJsArrayData::appendValue(double doubleValue)
{
	// TODO : use QVector
}

void QJsArrayData::appendValue(QString strValue)
{
	// TODO : use QVector
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
	// TODO : remove from QVector by index, return removed value
	return QVariant();
}

int QJsArrayData::removeValue(int intValue)
{
	// TODO : remove from QVector by value, where the value matched the integer argument, return removed integer value
	return 0;
}

QString QJsArrayData::removeValue(QString strValue)
{
	// TODO : remove from QVector by value, where the value matched the string argument, return removed string value
	return QString();
}


