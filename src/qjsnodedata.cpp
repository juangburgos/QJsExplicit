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

void QJsNodeData::setKeyName(const QString &strKeyName)
{
	if (strKeyName.isEmpty())
	{
		return;
	}
	// if old keyname is not empty and parent is not nullptr
	// replace old key entry from parent with new key entry
	// this has ot be done BEFORE the key is changed
	if (m_parent && !m_parent->isNull())
	{
		if (m_strKeyName.compare(strKeyName) != 0)
		{
			// recursively remove old json from parent if key exists in parent
			QJsonValue jsonValParent = m_parent->getJsonValue();
			if (m_parent->isObject() || m_parent->isDocument())
			{
				QJsonObject jsonObjParent = jsonValParent.toObject();
				if (jsonObjParent.contains(m_strKeyName))
				{
					jsonObjParent.remove(m_strKeyName);
					m_parent->updateJsonValue(QJsonValue(jsonObjParent));
				}
			}
			else if (m_parent->isArray())
			{
				QJsonArray jsonArrParent = jsonValParent.toArray();
				int intKey = m_strKeyName.toInt();
				if (intKey >= 0 && intKey < jsonArrParent.size())
				{
					jsonArrParent.removeAt(intKey); // NOTE IMPORTANT, in case of parent being array, the key of an array child id the index in string mode
					m_parent->updateJsonValue(QJsonValue(jsonArrParent));
				}
			}
			else
			{
				// TODO : error
			}
			// remove old child list entry (manual tree-rearrange)
			m_parent->m_mapChildren.remove(m_strKeyName);

			// recursively append new json to parent and add new child list entry
			m_strKeyName = strKeyName;
			setParentNode(m_parent);
		}
	}
	// update regardless
	m_strKeyName = strKeyName;
}

QString QJsNodeData::getKeyName()
{
	return m_strKeyName;
}

// Appended for the first time or reparented, tree re-arrange
void QJsNodeData::setJsonValue(const QJsonValue &jsonValue)
{
	// early exit
	if (!this->isDocument() && m_strKeyName.isEmpty())
	{
		return;
	}
	// copy json value
	m_jsonValue = jsonValue;
	// recreateChildren -> setParentNode -> updateJsonValue <-> updateJsonValue
	recreateChildren();
}

QJsonValue QJsNodeData::getJsonValue()
{
	return m_jsonValue;
}

// Only update value upwards, no tree re-arrange
void QJsNodeData::updateJsonValue(const QJsonValue &jsonValue)
{
	// update: just copy the value
	m_jsonValue = jsonValue;
	// if old keyname is not empty and parent is not nullptr
	// replace old json entry from parent with new json entry
	// NOTE : upwards recursive chain is broken when m_parent is null (i.e. QJsDocumentData)
	if (m_parent && !m_parent->isNull())
	{
		// Use original QJson API
		QJsonValue jsonValParent = m_parent->getJsonValue();
		if (m_parent->isObject() || m_parent->isDocument())
		{
			QJsonObject jsonObjParent = jsonValParent.toObject();
			jsonObjParent.insert(m_strKeyName, m_jsonValue);
			m_parent->updateJsonValue(QJsonValue(jsonObjParent));
		}
		else if (m_parent->isArray())
		{
			QJsonArray jsonArrParent = jsonValParent.toArray();
			// NOTE : this replace, setParentNode append
			jsonArrParent.replace(m_strKeyName.toInt(), m_jsonValue); // NOTE IMPORTANT, in case of parent being array, the key of an array child id the index in string mode
			m_parent->updateJsonValue(QJsonValue(jsonArrParent));
		}
		else
		{
			// TODO : error
		}
	}
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::parentNode()
{
    return m_parent;
}

// 
bool QJsNodeData::setParentNode(const QExplicitlySharedDataPointer<QJsNodeData> &newParent)
{
	// Use null parent to float free and remove form old only
	//// append to json AND to children list (different if array or obj)

	// recursively remove from old parent children list if key and parent not empty
	if (m_parent && !m_parent->isNull() && m_parent != newParent)
	{
		QJsonValue jsonValParent = m_parent->getJsonValue();
		if (m_parent->isObject() || m_parent->isDocument())
		{
			QJsonObject jsonObjParent = jsonValParent.toObject();
			if (jsonObjParent.contains(m_strKeyName))
			{
				jsonObjParent.remove(m_strKeyName);
				m_parent->updateJsonValue(QJsonValue(jsonObjParent));
			}
		}
		else if (m_parent->isArray())
		{
			QJsonArray jsonArrParent = jsonValParent.toArray();
			int intKey = m_strKeyName.toInt();
			if (intKey >= 0 && intKey < jsonArrParent.size())
			{
				jsonArrParent.removeAt(intKey); // NOTE IMPORTANT, in case of parent being array, the key of an array child id the index in string mode
				m_parent->updateJsonValue(QJsonValue(jsonArrParent));
			}
		}
		else
		{
			return false; // error
		}
		// remove from parent children list
		m_parent->m_mapChildren.remove(m_strKeyName);

	}

	// copy new parent
	m_parent = newParent;
	if (!m_parent)
	{
		return false;
	}

	// recursively add to new parent
	if (!m_parent->isNull())
	{
		// if parent is array get avilable key
		if (m_parent->isArray())
		{
			bool bOK = false;
			m_strKeyName.toInt(&bOK);
			if (m_strKeyName.isEmpty() || !bOK)
			{
				m_strKeyName = QString::number(m_parent->getJsonValue().toArray().count());
			}
			else
			{
				// TODO : error
			}
		}
		// Use original QJson API
		QJsonValue jsonValParent = m_parent->getJsonValue();
		if (m_parent->isObject() || m_parent->isDocument())
		{
			QJsonObject jsonObjParent = jsonValParent.toObject();
			jsonObjParent.insert(m_strKeyName, m_jsonValue);
			m_parent->updateJsonValue(QJsonValue(jsonObjParent));
		}
		else if (m_parent->isArray())
		{
			QJsonArray jsonArrParent = jsonValParent.toArray(); 
			int intKey = m_strKeyName.toInt();
			if (intKey >= 0 && intKey <= jsonArrParent.size())
			{
				jsonArrParent.insert(m_strKeyName.toInt(), m_jsonValue); // NOTE IMPORTANT, here we insert to parent
				m_parent->updateJsonValue(QJsonValue(jsonArrParent));
			}
			else
			{
				return false; // error
			}
		}
		else
		{
			return false; // error
		}
		// add also to parent list of children
		m_parent->m_mapChildren.insert(m_strKeyName, QExplicitlySharedDataPointer<QJsNodeData>(this));
	}

	// NOTE: QJsDocumentData must return false.

	return true;
}

QExplicitlySharedDataPointer<QJsDocumentData> QJsNodeData::ownerDocument()
{
	if (m_parent->isNull())
	{
		// TODO : error
		return QExplicitlySharedDataPointer<QJsDocumentData>(new QJsDocumentData);
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
	return m_mapChildren.value(strKeyName, QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData));
}

QExplicitlySharedDataPointer<QJsObjectData> QJsNodeData::createObject(const QString &strKeyName /*= ""*/)
{
	if ((this->isObject() || this->isDocument()))
	{
		if (strKeyName.isEmpty())
		{
			return QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData);
		}
		auto newObjChild          = QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData());
		newObjChild->m_strKeyName = strKeyName;
		//newObjChild->m_jsonValue  = QJsonValue(QJsonObject());
		if (newObjChild->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this)))
		{
			return newObjChild;
		}
		return QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData);
	} 
	else if (this->isArray())
	{
		if (!strKeyName.isEmpty())
		{
			//return QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData);
			// ignore 
			// TODO : error
		}
		auto newObjChild          = QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData());
		//newObjChild->m_strKeyName = "";
		//newObjChild->m_jsonValue  = QJsonValue(QJsonObject());
		QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this))->appendObject(newObjChild);
		return newObjChild;
	}

	return QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData);
}

QExplicitlySharedDataPointer<QJsArrayData> QJsNodeData::createArray(const QString &strKeyName /*= ""*/)
{
	if ((this->isObject() || this->isDocument()))
	{
		if (strKeyName.isEmpty())
		{
			return QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData);
		}
		auto newArrChild = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData());
		newArrChild->m_strKeyName = strKeyName;
		//newArrChild->m_jsonValue  = QJsonValue(QJsonArray());
		if (newArrChild->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this)))
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
		//newArrChild->m_strKeyName = "";
		//newArrChild->m_jsonValue  = QJsonValue(QJsonArray());
		QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this))->appendArray(newArrChild);
		return newArrChild;
	}

	return QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData);
}

void QJsNodeData::recreateChildren()
{
	// recreate children map
	m_mapChildren.clear();
	// convert to object or array
	// loop through json children values that are objects or arrays
	if (m_jsonValue.isObject())
	{
		QJsonObject jsonTempObj = m_jsonValue.toObject();
		QStringList listKeys = jsonTempObj.keys();
		for (int i = 0; i < listKeys.count(); i++)
		{
			QJsonValue jsonNewChild = jsonTempObj.value(listKeys.at(i));
			if (jsonNewChild.isObject())
			{
				auto newObjChild = QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData());
				newObjChild->m_strKeyName = listKeys.at(i);
				newObjChild->m_jsonValue  = jsonNewChild;
				newObjChild->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this)); // NOTE : setParentNode appends to parent's children list 
			}
			else if (jsonNewChild.isArray())
			{
				auto newArrChild = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData());
				newArrChild->m_strKeyName = listKeys.at(i);
				newArrChild->m_jsonValue = jsonNewChild;
				newArrChild->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this));
			}
			else
			{
				// ignore
			}
		}
	}
	else if (m_jsonValue.isArray())
	{
		QJsonArray jsonTempArr = m_jsonValue.toArray();
		for (int i = 0; i < jsonTempArr.count(); i++)
		{
			QJsonValue jsonNewChild = jsonTempArr.at(i);
			if (jsonNewChild.isObject())
			{
				auto newObjChild = QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData());
				newObjChild->m_strKeyName = QString::number(i);
				newObjChild->m_jsonValue  = jsonNewChild;
				newObjChild->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this));
			}
			else if (jsonNewChild.isArray())
			{
				auto newArrChild = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData());
				newArrChild->m_strKeyName = QString::number(i);
				newArrChild->m_jsonValue  = jsonNewChild;
				newArrChild->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this));
			}
			else
			{
				// ignore
			}
		}
	}
	else
	{
		// TODO : error
	}
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::appendChild(const QExplicitlySharedDataPointer<QJsNodeData> &nodeData)
{
	// cannot be null nor document, or if not child of array must have a key
	if (nodeData->isNull() || (!this->isArray() && nodeData->getKeyName().isEmpty()) || nodeData->isDocument())
	{
		return QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData); // null
	}
	// append (setParentNode actually does the linking)
	if (nodeData->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this)))
	{
		return nodeData;
	}
	return QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData);
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::removeChild(const QString &strKeyName)
{
	if (strKeyName.isEmpty())
	{
		return QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData);; // null
	}
	// call set null parent to child
	auto childToRemove = m_mapChildren.value(strKeyName);
	if (!childToRemove->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData)))
	{
		return childToRemove;
	}
	return QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData);
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::replaceChild(const QString &strKeyName, const QExplicitlySharedDataPointer<QJsNodeData> &nodeData)
{
	// copy key name
	//nodeData->m_strKeyName = strKeyName;
	//// copy backend data
	//auto originalNode = getChildByKey(strKeyName);
	//if (!originalNode)
	//{
	//	return QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData);
	//}
	//originalNode           = nodeData;
	//originalNode->m_parent = this;
	//// recreateChildren -> setParentNode -> updateJsonValue <-> updateJsonValue
	//originalNode->recreateChildren();
	//return originalNode;
	removeChild(strKeyName);
	nodeData->m_strKeyName = strKeyName;
	appendChild(nodeData);
	return nodeData;
}

bool QJsNodeData::isNull()
{
    if(m_jsonValue.type() == QJsonValue::Null)
    {
        return true;
    }
    return false;
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
	// if castable then return
	if ( (this->isObject() || this->isDocument()) && static_cast<QJsObjectData*>(this))
	{
		return QExplicitlySharedDataPointer<QJsObjectData>(static_cast<QJsObjectData*>(this));
	}
	// else return null
	return QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData);
}

QExplicitlySharedDataPointer<QJsArrayData> QJsNodeData::toArray()
{
	// if castable then return
	if (this->isArray() && static_cast<QJsArrayData*>(this))
	{
		return QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this));
	}
	// else return null
	return QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData);
}

QExplicitlySharedDataPointer<QJsDocumentData> QJsNodeData::toDocument()
{
	// if castable then return
	if (this->isDocument() && static_cast<QJsDocumentData*>(this))
	{
		return QExplicitlySharedDataPointer<QJsDocumentData>(static_cast<QJsDocumentData*>(this));
	}
	// else return null
	return QExplicitlySharedDataPointer<QJsDocumentData>(new QJsDocumentData);
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
	newNode->m_jsonValue = m_jsonValue;
	newNode->recreateChildren();
	return newNode;
}

QByteArray QJsNodeData::toJson(QJsonDocument::JsonFormat format/* = QJsonDocument::Indented*/)
{

	if (this->isArray())
	{
		QJsonArray    jsonTempArr = m_jsonValue.toArray();
		QJsonDocument jsonTempDoc;
		jsonTempDoc.setArray(jsonTempArr);
		return jsonTempDoc.toJson(format); 
	}
	else if (!this->isNull())
	{
		QJsonObject   jsonTempObj = m_jsonValue.toObject();
		QJsonDocument jsonTempDoc;
		jsonTempDoc.setObject(jsonTempObj);
		return jsonTempDoc.toJson(format); 
	} 
	return QByteArray();
}

QByteArray QJsNodeData::toBinaryData()
{
	QJsonObject   jsonTempObj = m_jsonValue.toObject();
	QJsonDocument jsonTempDoc;
	jsonTempDoc.setObject(jsonTempObj);
	return jsonTempDoc.toBinaryData();
}