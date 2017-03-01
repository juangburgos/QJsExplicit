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

QJsDocumentData::~QJsDocumentData()
{
	this->removeChildren();
}

bool QJsDocumentData::isDocument()
{
	return true;
}

bool QJsDocumentData::isObject()
{
	return false;
}

bool QJsDocumentData::isArray()
{
	return false;
}

QJsNodeData * QJsDocumentData::parentNode()
{
	return nullptr;
}

bool QJsDocumentData::setParentNode(QJsNodeData * newParent)
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
		return "[ERROR] JSON data is not an object";
	}

	// create internal tree recursivelly
	if (doc.isArray()) // TODO : not supported because QJsDocumentData inherits from QJsObjectData
	{
        auto tmpLinux = doc.array();
        fromJsonArray(tmpLinux);
	}
	else if (doc.isObject())
	{
        auto tmpLinux = doc.object();
        fromJsonObject(tmpLinux);
	}

	return "";
}

QString QJsDocumentData::fromBinaryData(const QByteArray &data)
{
	QJsonDocument doc = QJsonDocument::fromBinaryData(data);
	if (doc.isNull())
	{
		return "[ERROR] Invalid binary data";
	}
	if (!doc.isObject())
	{
		return "[ERROR] JSON binary data is not an object";
	}

	// create internal tree recursivelly
	if (doc.isArray()) // TODO : not supported because QJsDocumentData inherits from QJsObjectData
	{
        auto tmpLinux = doc.array();
        fromJsonArray(tmpLinux);
	}
	else if (doc.isObject())
	{
        auto tmpLinux = doc.object();
        fromJsonObject(tmpLinux);
	}

	return "";
}

