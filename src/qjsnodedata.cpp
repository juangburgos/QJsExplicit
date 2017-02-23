#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

QJsNodeData::QJsNodeData()
{
	m_strKeyName = QString();
	m_jsonValue  = QJsonValue();
	// null instance
    m_parent     = nullptr;
}

QJsNodeData::QJsNodeData(const QJsNodeData &other) : QSharedData(other),
m_strKeyName(other.m_strKeyName),
m_jsonValue(other.m_jsonValue),
m_parent(other.m_parent),
m_mapChildren(other.m_mapChildren)
{

}

QJsNodeData::~QJsNodeData()
{
	this->removeChildren();
}

void QJsNodeData::setKeyName(const QString &strKeyName)
{
	if (strKeyName.isEmpty())
	{
		return;
	}
	// TODO
}

QString QJsNodeData::getKeyName()
{
	return m_strKeyName;
}

QJsNodeData * QJsNodeData::parentNode()
{
    return m_parent;
}

// NECESSARY?
bool QJsNodeData::setParentNode(QJsNodeData * newParent)
{
	// TODO

	return true;
}

QExplicitlySharedDataPointer<QJsDocumentData> QJsNodeData::ownerDocument()
{
	// Find up recursivelly
	if (this->isDocument())
	{
		return this->toDocument();
	}
	else if (!m_parent || m_parent->isNull())
	{
		return QExplicitlySharedDataPointer<QJsDocumentData>(nullptr); // TODO : error
	}
	else if (m_parent->isDocument())
	{
		return m_parent->toDocument();
	}
	return m_parent->ownerDocument();
}

bool QJsNodeData::hasChildByKey(const QString &strKeyName)
{
	return !getChildByKey(strKeyName)->isNull();
}

QList<QExplicitlySharedDataPointer<QJsNodeData> > QJsNodeData::childNodes()
{
    return m_mapChildren.values();
}

QStringList QJsNodeData::childrenKeys()
{
	return m_mapChildren.keys();
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::getChildByKey(const QString &strKeyName)
{
	return m_mapChildren.value(strKeyName, QExplicitlySharedDataPointer<QJsNodeData>(nullptr));
}

QExplicitlySharedDataPointer<QJsObjectData> QJsNodeData::createObject(const QString &strKeyName /*= ""*/)
{
	// Create an Object child of this
	// Varies if this is Object or Array
	// TODO : use a QVector instead of QMap if this is Array
	if ((this->isObject() || this->isDocument()))
	{
		if (strKeyName.isEmpty())
		{
			return QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData);
		}
		auto newObjChild          = QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData());
		newObjChild->m_strKeyName = strKeyName;
		if (newObjChild->setParentNode(this))
		{
			return newObjChild;
		}
		return QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData);
	} 
	else if (this->isArray())
	{
		auto newObjChild = QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData());
		QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this))->appendObject(newObjChild);
		return newObjChild;
	}

	return QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData);
}

QExplicitlySharedDataPointer<QJsArrayData> QJsNodeData::createArray(const QString &strKeyName /*= ""*/)
{
	// Create an Array child of this
	// Varies if this is Object or Array
	// TODO : use QVector instead of QMap if this is Array
	if ((this->isObject() || this->isDocument()))
	{
		if (strKeyName.isEmpty())
		{
			return QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData);
		}
		auto newArrChild = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData());
		newArrChild->m_strKeyName = strKeyName;
		if (newArrChild->setParentNode(this))
		{
			return newArrChild;
		}
		return QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData);
	}
	else if (this->isArray())
	{
		if (!strKeyName.isEmpty())
		{
			return QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData);
		}
		auto newArrChild = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData());
		QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this))->appendArray(newArrChild);
		return newArrChild;
	}

	return QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData);
}

void QJsNodeData::removeChildren()
{
	// TODO : use QVector instead of QMap if this is Array
	if (!this)
	{
		return;
	}
	QMap<QString, QExplicitlySharedDataPointer<QJsNodeData>>::const_iterator i = m_mapChildren.constBegin();
	while (i != m_mapChildren.constEnd()) {
		this->removeChild(i.key()); // calls QJsNodeData::removeChild on this
		i = m_mapChildren.constBegin();
	}
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::appendChild(const QExplicitlySharedDataPointer<QJsNodeData> &nodeData)
{
	// cannot be null nor document, or if not child of array must have a key
	if (nodeData->isNull() || (!this->isArray() && nodeData->getKeyName().isEmpty()) || nodeData->isDocument())
	{
		return QExplicitlySharedDataPointer<QJsNodeData>(nullptr); // null
	}
	// append 
	if (this->hasChildByKey(nodeData->getKeyName()))
	{
		return replaceChild(nodeData->getKeyName(), nodeData); // NOTE: setParentNode actually does the linking
	}
	else if (nodeData->setParentNode(this))
	{
		return nodeData;
	}
	return QExplicitlySharedDataPointer<QJsNodeData>(nullptr);
}

void QJsNodeData::removeChild(const QString &strKeyName)
{
	if (strKeyName.isEmpty())
	{
		return;
	}
	// call set null parent to child
	auto childToRemove = m_mapChildren.take(strKeyName);
	if (!childToRemove) // when child with strKeyName does not exist
	{
		return;
	}
	childToRemove->removeChildren();
	childToRemove->setParentNode(nullptr);
	childToRemove.reset();
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::replaceChild(const QString &strKeyName, const QExplicitlySharedDataPointer<QJsNodeData> &nodeData)
{
	removeChild(strKeyName);
	nodeData->m_strKeyName = strKeyName;
	appendChild(nodeData);
	return nodeData;
}

bool QJsNodeData::isNull()
{
	if (!this)
	{
		return true;
	}
    if(m_jsonValue.type() == QJsonValue::Null)
    {
        return true;
    }
    return false;
}

bool QJsNodeData::isValid()
{
	if (this->isNull())
	{
		return false;
	}
	// FIX to match QJsObject() or QJsArray()
	if (m_strKeyName.isEmpty() && m_jsonValue.type() == QJsonValue::Object && m_jsonValue.toObject().isEmpty())
	{
		return false;
	}
	if (m_strKeyName.isEmpty() && m_jsonValue.type() == QJsonValue::Array && m_jsonValue.toArray().isEmpty())
	{
		return false;
	}

	return true;
}

bool QJsNodeData::isObject()
{
	return false;
}

bool QJsNodeData::isArray()
{
	return false;
}

bool QJsNodeData::isDocument()
{
	return false;
}

QExplicitlySharedDataPointer<QJsObjectData> QJsNodeData::toObject()
{
	if (this->isNull())
	{
		return QExplicitlySharedDataPointer<QJsObjectData>(nullptr); // null
	}
	// if castable then return
	if ( (this->isObject() || this->isDocument()) && static_cast<QJsObjectData*>(this))
	{
		return QExplicitlySharedDataPointer<QJsObjectData>(static_cast<QJsObjectData*>(this));
	}
	// else return null
	return QExplicitlySharedDataPointer<QJsObjectData>(nullptr); // null
}

QExplicitlySharedDataPointer<QJsArrayData> QJsNodeData::toArray()
{
	if (this->isNull())
	{
		return QExplicitlySharedDataPointer<QJsArrayData>(nullptr); // null
	}
	// if castable then return
	if (this->isArray() && static_cast<QJsArrayData*>(this))
	{
		return QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this));
	}
	// else return null
	return QExplicitlySharedDataPointer<QJsArrayData>(nullptr); // null
}

QExplicitlySharedDataPointer<QJsDocumentData> QJsNodeData::toDocument()
{
	if (this->isNull())
	{
		return QExplicitlySharedDataPointer<QJsDocumentData>(nullptr); // null
	}
	// if castable then return
	if (this->isDocument() && static_cast<QJsDocumentData*>(this))
	{
		return QExplicitlySharedDataPointer<QJsDocumentData>(static_cast<QJsDocumentData*>(this));
	}
	// else return null
	return QExplicitlySharedDataPointer<QJsDocumentData>(nullptr); // null
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::clone()
{
	QExplicitlySharedDataPointer<QJsNodeData> newNode;
	if (this->isObject())
	{
		newNode = QExplicitlySharedDataPointer<QJsNodeData>(new QJsObjectData());
	}
	else if (this->isArray())
	{
		newNode = QExplicitlySharedDataPointer<QJsNodeData>(new QJsArrayData());
	}
	else if (this->isDocument())
	{
		newNode = QExplicitlySharedDataPointer<QJsNodeData>(new QJsDocumentData());
	}
	else
	{
		newNode = QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData());
	}
	newNode->m_strKeyName = m_strKeyName;
	newNode->m_jsonValue  = m_jsonValue;

	// TODO : Now waht to do here instead?
	//newNode->recreateChildren();

	return newNode;
}

QByteArray QJsNodeData::toJson(QJsonDocument::JsonFormat format/* = QJsonDocument::Indented*/)
{
	// TODO : Update to build tree recursivelly to ultimatelly by able to use QJsonDocument::toJson
	//if (this->isArray())
	//{
	//	QJsonArray    jsonTempArr = m_jsonValue.toArray();
	//	QJsonDocument jsonTempDoc;
	//	jsonTempDoc.setArray(jsonTempArr);
	//	return jsonTempDoc.toJson(format); 
	//}
	//else if (!this->isNull())
	//{
	//	QJsonObject   jsonTempObj = m_jsonValue.toObject();
	//	QJsonDocument jsonTempDoc;
	//	jsonTempDoc.setObject(jsonTempObj);
	//	return jsonTempDoc.toJson(format); 
	//} 

	return QByteArray();
}

QByteArray QJsNodeData::toBinaryData()
{
	// TODO : Update to build tree recursivelly to ultimatelly by able to use QJsonDocument::toBinaryData
	//QJsonObject   jsonTempObj = m_jsonValue.toObject();
	//QJsonDocument jsonTempDoc;
	//jsonTempDoc.setObject(jsonTempObj);
	//return jsonTempDoc.toBinaryData();

	return QByteArray();
}