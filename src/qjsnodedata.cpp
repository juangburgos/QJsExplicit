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

void QJsNodeData::setKeyName(const QString &strKeyName)
{
	if (strKeyName.isEmpty())
	{
		return;
	}
	// if old keyname is not empty and parent is not nullptr
	// replace old key entry from parent with new key entry
	if (!m_parent->isNull())
	{
		if (m_strKeyName.compare(strKeyName) != 0)
		{
			// remove old json from parent
			QJsonValue jsonValParent = m_parent->getJsonValue();
			if (m_parent->isObject())
			{
				QJsonObject jsonObjParent = jsonValParent.toObject();
				jsonObjParent.remove(m_strKeyName);
				m_parent->setJsonValue(QJsonValue(jsonObjParent));
			}
			else if (m_parent->isArray())
			{
				QJsonArray jsonArrParent = jsonValParent.toArray();
				jsonArrParent.removeAt(m_strKeyName.toInt()); // NOTE IMPORTANT, in case of parent being array, the key of an array child id the index in string mode
				m_parent->setJsonValue(QJsonValue(jsonArrParent));
			}
			else if (m_parent->isDocument())
			{
				QJsonObject jsonObjParent = jsonValParent.toObject();
				jsonObjParent.remove(m_strKeyName);
				m_parent->setJsonValue(QJsonValue(jsonObjParent));
			}
			else
			{
				// TODO : error
			}
			// add new json to parent
			m_strKeyName = strKeyName;
			setJsonValue(m_jsonValue);
		}
	}
	// update regardless
	m_strKeyName = strKeyName;
}

QString QJsNodeData::getKeyName()
{
	return m_strKeyName;
}

void QJsNodeData::setJsonValue(const QJsonValue &jsonValue) // NOTE : recursive
{
	// just copy the value
	m_jsonValue = jsonValue;
	// early exit
	if (m_strKeyName.isEmpty())
	{
		return;
	}
	// if old keyname is not empty and parent is not nullptr
	// replace old json entry from parent with new json entry
	// NOTE : need to recreate children list
	// NOTE : upwards recursive chain is broken when m_parent is null (i.e. QJsDocumentData)
	if (!m_parent->isNull())
	{
		// Use original QJson API
		QJsonValue jsonValParent = m_parent->getJsonValue();
		if (m_parent->isObject())
		{
			QJsonObject jsonObjParent = jsonValParent.toObject();
			jsonObjParent.insert(m_strKeyName, m_jsonValue);
			m_parent->setJsonValue(QJsonValue(jsonObjParent));
		} 
		else if (m_parent->isArray())
		{
			QJsonArray jsonArrParent = jsonValParent.toArray();
			jsonArrParent.replace(m_strKeyName.toInt(), m_jsonValue); // NOTE IMPORTANT, in case of parent being array, the key of an array child id the index in string mode
			m_parent->setJsonValue(QJsonValue(jsonArrParent));
		}
		else if (m_parent->isDocument())
		{
			QJsonObject jsonObjParent = jsonValParent.toObject();
			jsonObjParent.insert(m_strKeyName, m_jsonValue);
			m_parent->setJsonValue(QJsonValue(jsonObjParent));
		}
		else
		{
			// TODO : error
		}
	}

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
				newObjChild->setConfigure(listKeys.at(i), jsonNewChild);
				newObjChild->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this)); // NOTE : setParentNode appends to parent's children list 
			} 
			else if (jsonNewChild.isArray())
			{
				auto newArrChild = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData());
				newArrChild->setConfigure(listKeys.at(i), jsonNewChild);
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
				newObjChild->setConfigure(QString::number(i), jsonNewChild);
				newObjChild->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this));
			}
			else if (jsonNewChild.isArray())
			{
				auto newArrChild = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData());
				newArrChild->setConfigure(QString::number(i), jsonNewChild);
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

QJsonValue QJsNodeData::getJsonValue()
{
	return m_jsonValue;
}

void QJsNodeData::setConfigure(const QString &strKeyName, const QJsonValue &jsonValue)
{
	// update json value
	setJsonValue(jsonValue);
	// update key name (m_strKeyName)
	setKeyName(strKeyName);
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::parentNode()
{
    return m_parent;
}

bool QJsNodeData::setParentNode(const QExplicitlySharedDataPointer<QJsNodeData> &newParent)
{
	// Use null parent to float free and remove form old only
	//// append to json AND to children list (different if array or obj)
	//if (newParent->isNull()) 
	//{
	//	return;
	//}

	// remove from old parent children list if key and parent not empty
	if (!m_parent->isNull())
	{
		QJsonValue jsonValParent = m_parent->getJsonValue();
		if (m_parent->isObject())
		{
			QJsonObject jsonObjParent = jsonValParent.toObject();
			jsonObjParent.remove(m_strKeyName);
			m_parent->setJsonValue(QJsonValue(jsonObjParent));
		}
		else if (m_parent->isArray())
		{
			QJsonArray jsonArrParent = jsonValParent.toArray();
			jsonArrParent.removeAt(m_strKeyName.toInt()); // NOTE IMPORTANT, in case of parent being array, the key of an array child id the index in string mode
			m_parent->setJsonValue(QJsonValue(jsonArrParent));
		}
		else if (m_parent->isDocument())
		{
			QJsonObject jsonObjParent = jsonValParent.toObject();
			jsonObjParent.remove(m_strKeyName);
			m_parent->setJsonValue(QJsonValue(jsonObjParent));
		}
		else
		{
			// TODO : error
		}
		// remove from parent children list
		m_parent->m_mapChildren.remove(m_strKeyName);

	}


	// copy new parent
    m_parent = newParent;

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
		}
		// Use original QJson API
		QJsonValue jsonValParent = m_parent->getJsonValue();
		if (m_parent->isObject())
		{
			QJsonObject jsonObjParent = jsonValParent.toObject();
			jsonObjParent.insert(m_strKeyName, m_jsonValue);
			m_parent->setJsonValue(QJsonValue(jsonObjParent));
		}
		else if (m_parent->isArray())
		{
			QJsonArray jsonArrParent = jsonValParent.toArray();
			jsonArrParent.replace(m_strKeyName.toInt(), m_jsonValue); // NOTE IMPORTANT, in case of parent being array, the key of an array child id the index in string mode
			m_parent->setJsonValue(QJsonValue(jsonArrParent));
		}
		else if (m_parent->isDocument())
		{
			QJsonObject jsonObjParent = jsonValParent.toObject();
			jsonObjParent.insert(m_strKeyName, m_jsonValue);
			m_parent->setJsonValue(QJsonValue(jsonObjParent));
		}
		else
		{
			// TODO : error
		}
		// add also to parent list of children
		m_parent->m_mapChildren.insert(m_strKeyName, QExplicitlySharedDataPointer<QJsNodeData>(this));
	}

	// NOTE: QJsDocumentData must return false.

	return true;
}

QList<QExplicitlySharedDataPointer<QJsNodeData> > QJsNodeData::childNodes()
{
    return m_mapChildren.values();
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::getChildByKey(const QString &strKeyName)
{
	return m_mapChildren.value(strKeyName);
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::appendChild(const QExplicitlySharedDataPointer<QJsNodeData> &nodeData)
{
	// cannot be null nor document, or if not child of array must have a key
	if (nodeData->isNull() || (!this->isArray() && nodeData->getKeyName().isEmpty()) || nodeData->isDocument())
	{
		return QExplicitlySharedDataPointer<QJsNodeData>(); // null
	}
	// append (setParentNode actually does the linking)
	nodeData->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>(this));
	return nodeData;
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::removeChild(const QString &strKeyName)
{
	if (strKeyName.isEmpty())
	{
		return QExplicitlySharedDataPointer<QJsNodeData>();; // null
	}
	// call set null parent to child
	auto childToRemove = m_mapChildren.value(strKeyName);
	childToRemove->setParentNode(QExplicitlySharedDataPointer<QJsNodeData>()); // null
	return childToRemove;
}

bool QJsNodeData::isNull()
{
	if (!m_parent)
	{
		return true;
	}
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
	if (this->isObject() && static_cast<QJsObjectData*>(this))
	{
		return QExplicitlySharedDataPointer<QJsObjectData>(static_cast<QJsObjectData*>(this));
	}
	// else return null
	return QExplicitlySharedDataPointer<QJsObjectData>();
}

QExplicitlySharedDataPointer<QJsArrayData> QJsNodeData::toArray()
{
	// if castable then return
	if (this->isObject() && static_cast<QJsArrayData*>(this))
	{
		return QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this));
	}
	// else return null
	return QExplicitlySharedDataPointer<QJsArrayData>();
}

QExplicitlySharedDataPointer<QJsDocumentData> QJsNodeData::toDocument()
{
	// if castable then return
	if (this->isObject() && static_cast<QJsDocumentData*>(this))
	{
		return QExplicitlySharedDataPointer<QJsDocumentData>(static_cast<QJsDocumentData*>(this));
	}
	// else return null
	return QExplicitlySharedDataPointer<QJsDocumentData>();
}
