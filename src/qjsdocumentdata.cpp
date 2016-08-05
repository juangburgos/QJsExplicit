#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

QJsDocumentData::QJsDocumentData()
{
	m_strKeyName = QString();
	m_jsonValue  = QJsonValue(QJsonObject()); // NODE, has to be an object, the QJsonDocument Object
	// null instance
	m_parent = nullptr;
}

bool QJsDocumentData::isDocument()
{
	return true;
}

QExplicitlySharedDataPointer<QJsNodeData> QJsDocumentData::parentNode()
{
	return QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData);
}

bool QJsDocumentData::setParentNode(const QExplicitlySharedDataPointer<QJsNodeData> &newParent)
{
	Q_UNUSED(newParent)
	return false;
}

QString QJsDocumentData::fromJson(const QByteArray &json)
{
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(json, &error);
	if (error.error != QJsonParseError::NoError)
	{
		return error.errorString();
	}
	if (!doc.isObject())
	{
		return "JSON data is not an object";
	}
	// set object and recreate children
	setJsonValue(QJsonValue(doc.object()));
	return "";
}

QString QJsDocumentData::fromBinaryData(const QByteArray &data)
{
	QJsonDocument doc = QJsonDocument::fromJson(data);
	if (doc.isNull())
	{
		return "Invalid binary data";
	}
	if (!doc.isObject())
	{
		return "JSON binary data is not an object";
	}
	// set object and recreate children
	setJsonValue(QJsonValue(doc.object()));
	return "";
}

