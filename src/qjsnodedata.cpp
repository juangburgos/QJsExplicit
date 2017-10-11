#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

#include <QDebug>

QJsNodeData::QJsNodeData()
{
	m_strKeyName = "";
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

bool QJsNodeData::setKeyName(const QString &strKeyName)
{
	if (strKeyName.isEmpty())
	{
		qDebug() << "[ERROR] new node key name is empty in QJsNodeData::setKeyName";
		return false;
	}
	// [DIFF] Different if parent object or array
	if (m_parent && m_parent->isArray())
	{
		// try to convert new key name to int
		bool isInt = false;
		int  newIdx = strKeyName.toInt(&isInt);
		if (!isInt)
		{
			qDebug() << "[ERROR] new node key name belonging to array is not number in QJsNodeData::setKeyName";
			return false;
		}
		// try to convert current key name to int
		isInt = false;
		int  currIdx = m_strKeyName.toInt(&isInt);
		if (!isInt)
		{
			qDebug() << "[ERROR] node key name belonging to array is not number in QJsNodeData::setKeyName";
			return false;
		}
		// if int check if within parent's vector range
		if (currIdx >= m_parent->m_vectorChildren.count())
		{
			qDebug() << "[ERROR] node key name belonging to array out of range in QJsNodeData::setKeyName";
			return false;
		}
		// if in range, remove from parent vector of children
		m_parent->m_vectorChildren.remove(currIdx);
		// check if new idx in range
		if (newIdx > m_parent->m_vectorChildren.count())
		{
			// put back were it was
			m_parent->m_vectorChildren.insert(currIdx, QExplicitlySharedDataPointer<QJsNodeData>(this));
			qDebug() << "[ERROR] new node key name belonging to array out of range in QJsNodeData::setKeyName";
			return false;
		}
		// else insert were it was asked to
		m_parent->m_vectorChildren.insert(newIdx, QExplicitlySharedDataPointer<QJsNodeData>(this));
		// change this keyname
		m_strKeyName = QString::number(newIdx);
	}
	else if(m_parent && (m_parent->isObject() || m_parent->isDocument()))
	{
		// check if this is contained within parent
		if (!m_parent->m_mapChildren.contains(m_strKeyName))
		{
			qDebug() << "[ERROR] node key name not child of parent in QJsNodeData::setKeyName";
			return false;
		}
		// change key name in parent's map
		if (m_parent->m_mapChildren.remove(m_strKeyName) > 1)
		{
			qDebug() << "[WARN] remove count from parent not matching QJsNodeData::setKeyName";
		}
		m_parent->m_mapChildren.insert(strKeyName, QExplicitlySharedDataPointer<QJsNodeData>(this));
		// if not array, just set the string key
		m_strKeyName = strKeyName;
	}
	else
	{
		// if null or invalid parent then just copy keyname
		m_strKeyName = strKeyName;
	}
	return true;
}

QString QJsNodeData::getKeyName()
{
	return m_strKeyName;
}

QJsNodeData * QJsNodeData::parentNode()
{
    return m_parent;
}

bool QJsNodeData::setParentNode(QJsNodeData * newParent)
{
	// check if not null and if valid
	if (!newParent || !newParent->isValid())
	{
		//qDebug() << "[ERROR] new parent cannot be invalid in QJsNodeData::setParentNode";
		//m_parent = newParent;
		return false;
	}
	// remove this from old parent children list if it had one
	// but do not delete (i.e. do not use parent's  QJsNodeData::removeChild method)
	if (m_parent && m_parent->isValid())
	{
		// [DIFF] Different if parent object or array
		if (m_parent->isArray())
		{
			// try to convert this key to int
			bool isInt = false;
			int  idx = m_strKeyName.toInt(&isInt);
			if (!isInt)
			{
				qDebug() << "[ERROR] node key name belonging to array is not number in QJsNodeData::setParentNode";
				return false;
			}
			// check if within parent's vector range
			if (idx >= m_parent->m_vectorChildren.count())
			{
				qDebug() << "[ERROR] node key name belonging to array out of range in QJsNodeData::setParentNode";
				return false;
			}
			// remove
			m_parent->m_vectorChildren.remove(idx);
			// [VECTOR] update keys in old parent array
			for (int i = 0; i < m_parent->m_vectorChildren.count(); i++)
			{
				m_parent->m_vectorChildren.at(i)->m_strKeyName = QString::number(i);
			}
		}
		else
		{
			// check if this is contained within parent
			if (!m_parent->m_mapChildren.contains(m_strKeyName))
			{
				qDebug() << "[ERROR] node key name not child of parent in QJsNodeData::setParentNode";
				return false;
			}
			// change key name in parent's map
			if (m_parent->m_mapChildren.remove(m_strKeyName) > 1)
			{
				qDebug() << "[ERROR] remove count from parent not matching QJsNodeData::setParentNode";
			}
		}
	}
	// [DIFF] Different if new parent object or array
	m_parent = newParent;
	// append to new parent vector or map of children
	if (newParent->isArray())
	{
		// append to vector
		newParent->m_vectorChildren.append(QExplicitlySharedDataPointer<QJsNodeData>(this));
		int newIdx = newParent->m_vectorChildren.count() - 1;
		// change this keyname but give warning in case it does not match
		QString strNewKey = QString::number(newIdx);
		if (!m_strKeyName.isEmpty() && m_strKeyName.compare(strNewKey) != 0)
		{
			qDebug() << "[ERROR] key name (index) mismatch while setting array as parent in QJsNodeData::setParentNode";
		}
		m_strKeyName = strNewKey;
	}
	else
	{
		// if new parent contains a child with same key, remove it first
		// this time, do use QJsNodeData::removeChild
		if (newParent->m_mapChildren.contains(m_strKeyName))
		{
			newParent->removeChild(m_strKeyName);
		}
		// insert to map
		newParent->m_mapChildren.insert(m_strKeyName, QExplicitlySharedDataPointer<QJsNodeData>(this));
	}
	return true;
}

QExplicitlySharedDataPointer<QJsDocumentData> QJsNodeData::ownerDocument()
{
	// Find up recursivelly
	if (this->isDocument())
	{
		return this->toDocument();
	}
	else if (!m_parent || !m_parent->isValid())
	{
		qDebug() << "[ERROR] Invalid parent in QJsNodeData::ownerDocument";
		return QExplicitlySharedDataPointer<QJsDocumentData>(nullptr);
	}
	else if (m_parent->isDocument())
	{
		return m_parent->toDocument();
	}
	return m_parent->ownerDocument();
}

bool QJsNodeData::hasChildByKey(const QString &strKeyName)
{
	return getChildByKey(strKeyName)->isValid();
}

QList<QExplicitlySharedDataPointer<QJsNodeData> > QJsNodeData::childNodes()
{
	// [DIFF] Different if parent object or array
	if (this->isArray())
	{
		return m_vectorChildren.toList();
	}
	return m_mapChildren.values();
}

QStringList QJsNodeData::childrenKeys()
{
	QStringList retList;
	// [DIFF] Different if parent object or array
	if (this->isArray())
	{
		for (int i = 0; i < m_vectorChildren.count(); i++)
		{
			// TODO : remove check if all good
			if (m_vectorChildren.at(i)->getKeyName().compare(QString::number(i), Qt::CaseInsensitive) != 0)
			{
				qDebug() << "[ERROR] non matching key names for array in QJsNodeData::childrenKeys";
				m_vectorChildren.at(i)->m_strKeyName = QString::number(i);
			}
			retList << m_vectorChildren.at(i)->getKeyName();
		}
	}
	else
	{
		retList = m_mapChildren.keys();
	}
	return retList;
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::getChildByKey(const QString &strKeyName)
{
	if (strKeyName.isEmpty())
	{
		return QExplicitlySharedDataPointer<QJsNodeData>(nullptr);
	}
	// [DIFF] Different if parent object or array
	if (this->isArray())
	{
		// check if requested key name is number
		bool isInt = false;
		int  newIdx = strKeyName.toInt(&isInt);
		if (!isInt)
		{
			// comented out because it is used often as a condition for QJsNodeData::hasChildByKey
			//qDebug() << "[ERROR] node key name belonging to array is not number in QJsNodeData::getChildByKey";
			return QExplicitlySharedDataPointer<QJsNodeData>(nullptr);
		}
		// check if requested key name is within range
		if (newIdx >= this->m_vectorChildren.count())
		{
			// comented out because it is used often as a condition for QJsNodeData::hasChildByKey
			//qDebug() << "[ERROR] node key name belonging to array out of range in QJsNodeData::getChildByKey";
			return QExplicitlySharedDataPointer<QJsNodeData>(nullptr);
		}
		// return requested
		return this->m_vectorChildren[newIdx];
	}
	return m_mapChildren.value(strKeyName, QExplicitlySharedDataPointer<QJsNodeData>(nullptr));
}

QExplicitlySharedDataPointer<QJsObjectData> QJsNodeData::createObject(const QString &strKeyName)
{
	// [DIFF] Different if parent object or array
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
		// QJsArrayData::appendObject ends up calling QJsNodeData::appendChild
		QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this))->appendObject(newObjChild);
		return newObjChild;
	}
	return QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData);
}

QExplicitlySharedDataPointer<QJsArrayData> QJsNodeData::createArray(const QString &strKeyName)
{
	// [DIFF] Different if parent object or array
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
		// QJsArrayData::appendArray ends up calling QJsNodeData::appendChild
		QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this))->appendArray(newArrChild);
		return newArrChild;
	}
	return QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData);
}

void QJsNodeData::removeChildren()
{
	// [DIFF] Different if new parent object or array
	if (!this)
	{
		qDebug() << "[ERROR] Invalid instance in QJsNodeData::removeChildren";
		return;
	}
	if (this->isArray())
	{
		while (this->m_vectorChildren.count() > 0)
		{
			QString strKeyToRem = this->m_vectorChildren.at(0)->getKeyName();
			this->removeChild(strKeyToRem);
		}
	}
	else
	{
		// use STL-style iterator
		QMap<QString, QExplicitlySharedDataPointer<QJsNodeData>>::const_iterator i = this->m_mapChildren.constBegin();
		while (i != this->m_mapChildren.constEnd()) {
			this->removeChild(i.key()); // calls QJsNodeData::removeChild on this
			i = this->m_mapChildren.constBegin();
		}
	}
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::appendChild(const QExplicitlySharedDataPointer<QJsNodeData> &nodeData)
{
	// cannot be null nor document, or if not child of array must have a key
	if (!nodeData->isValid() || (!this->isArray() && nodeData->getKeyName().isEmpty()) || nodeData->isDocument())
	{
		qDebug() << "[ERROR] no valid conditions to append child in QJsNodeData::appendChild";
		return QExplicitlySharedDataPointer<QJsNodeData>(nullptr); // null
	}
	// append 
	if (this->hasChildByKey(nodeData->getKeyName()))
	{
		return replaceChild(nodeData->getKeyName(), nodeData); 
	}
	else if (nodeData->setParentNode(this))
	{
		// NOTE: setParentNode actually does the linking
		return nodeData;
	}
	return QExplicitlySharedDataPointer<QJsNodeData>(nullptr);
}

bool QJsNodeData::removeChild(const QString &strKeyName)
{
	if (strKeyName.isEmpty())
	{
		qDebug() << "[ERROR] empty key name in QJsNodeData::removeChild";
		return false;
	}
	// [DIFF] Different if parent object or array
	QExplicitlySharedDataPointer<QJsNodeData> childToRemove;
	if (this->isArray())
	{
		// try to convert current key name to int
		bool isInt = false;
		int  childIdx = strKeyName.toInt(&isInt);
		if (!isInt)
		{
			qDebug() << "[ERROR] child key name belonging to array is not number in QJsNodeData::removeChild";
			return false;
		}
		// if int check if within parent's vector range
		if (childIdx >= this->m_vectorChildren.count())
		{
			qDebug() << "[ERROR] child key name belonging to array out of range in QJsNodeData::removeChild";
			return false;
		}
		// remove
		childToRemove = this->m_vectorChildren.takeAt(childIdx);
		//this->m_vectorChildren.remove(childIdx);
		// [VECTOR] update vector's key names
		for (int i = 0; i < this->m_vectorChildren.count(); i++)
		{
			this->m_vectorChildren.at(i)->m_strKeyName = QString::number(i);
		}
	}
	else
	{
		// call set null parent to child
		childToRemove = m_mapChildren.take(strKeyName);
		if (!childToRemove->isValid()) // when child with strKeyName does not exist
		{
			return false;
		}
	}
	// recursivelly remove down the tree
	childToRemove->removeChildren();
	childToRemove->setParentNode(nullptr);
	childToRemove.reset();
	return true;
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::replaceChild(const QString &strKeyName, const QExplicitlySharedDataPointer<QJsNodeData> &nodeData)
{
	removeChild(strKeyName);
	nodeData->m_strKeyName = strKeyName;
	appendChild(nodeData);
	return nodeData;
}

bool QJsNodeData::isValid()
{
	if (!this || m_jsonValue.type() == QJsonValue::Null)
	{
		return false;
	}

	return true;
}

bool QJsNodeData::isEmpty()
{
	// first test if child nodes
	if (!this || !this->isValid())
	{
		return true;
	}
	if (m_jsonValue.type() == QJsonValue::Object && m_strKeyName.isEmpty() && m_jsonValue.toObject().isEmpty())
	{
		return true;
	}
	if (m_jsonValue.type() == QJsonValue::Array && m_strKeyName.isEmpty() && m_jsonValue.toArray().isEmpty())
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
	if (!this->isValid())
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
	if (!this->isValid())
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
	if (!this->isValid())
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
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	newNode->d_strKeyName       = d_strKeyName;
	newNode->d_strJsonFull      = d_strJsonFull;
	newNode->d_strParentKeyName = d_strParentKeyName;
	newNode->d_strAttributes    = d_strAttributes;
	newNode->d_strCount         = d_strCount;
#endif
	// Actually clone
	cloneDeep(newNode);
	// finished
	return newNode;
}

void QJsNodeData::cloneDeep(QExplicitlySharedDataPointer<QJsNodeData> parent)
{
	if (this->isArray())
	{
		for (int i = 0; i < this->m_vectorChildren.count(); i++)
		{
			parent->appendChild(this->m_vectorChildren.at(i)->clone());
		}
	}
	else if (this->isObject() || this->isDocument())
	{
		QMapIterator<QString, QExplicitlySharedDataPointer<QJsNodeData>> i(this->m_mapChildren);
		while (i.hasNext()) {
			i.next();
			auto currNode = i.value();
			parent->appendChild(currNode->clone());
		}
	}
	else
	{
		if (this->m_vectorChildren.count() > 0 || this->m_mapChildren.count() > 0)
		{
			qDebug() << "[ERROR] pure QJsNode instance is not supposed to has children";
		}
	}
}

QByteArray QJsNodeData::toJson(QJsonDocument::JsonFormat format/* = QJsonDocument::Indented*/)
{
	// TODO : improve performance, own implementation?
	if (this->isArray())
	{
		QJsonArray    jsonTempArr = m_jsonValue.toArray();
		// recursivelly build qt json tree
		this->toJsonArray(jsonTempArr);
		// convert to json string
		QJsonDocument jsonTempDoc;
		jsonTempDoc.setArray(jsonTempArr);
		return jsonTempDoc.toJson(format);
	}
	else if (this->isValid())
	{
		QJsonObject   jsonTempObj = m_jsonValue.toObject();
		// recursivelly build qt json tree
		this->toJsonObject(jsonTempObj); // 25% this, 75% other lines
		// convert to json string
		QJsonDocument jsonTempDoc;
		jsonTempDoc.setObject(jsonTempObj);
		return jsonTempDoc.toJson(format);
	}

	return QByteArray();
}

QByteArray QJsNodeData::toBinaryData()
{
	// TODO : improve performance, own implementation?
	if (this->isArray())
	{
		QJsonArray    jsonTempArr = m_jsonValue.toArray();
		// recursivelly build json tree
		this->toJsonArray(jsonTempArr);
		// convert to json string
		QJsonDocument jsonTempDoc;
		jsonTempDoc.setArray(jsonTempArr);
		return jsonTempDoc.toBinaryData();
	}
	else if (this->isValid())
	{
		QJsonObject   jsonTempObj = m_jsonValue.toObject();
		// recursivelly build json tree
		this->toJsonObject(jsonTempObj);
		// convert to json string
		QJsonDocument jsonTempDoc;
		jsonTempDoc.setObject(jsonTempObj);
		return jsonTempDoc.toBinaryData();
	}

	return QByteArray();
}

void QJsNodeData::toJsonObject(QJsonObject &jsonObject)
{
	QMapIterator<QString, QExplicitlySharedDataPointer<QJsNodeData>> i(this->m_mapChildren);
	while (i.hasNext()) {
		i.next();
		auto currNodeKey = i.key();
		auto currNode    = i.value();
		// append child
		if (currNode->isArray())
		{
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
			// use cache in debug mode to improve performance
			if (!currNode->d_cacheJsonArr.isEmpty())
			{
				jsonObject[currNodeKey] = currNode->d_cacheJsonArr;
			}
			else
			{
#endif
				QJsonArray tmpArray;
				currNode->toJsonArray(tmpArray);
				jsonObject[currNodeKey] = tmpArray;
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
			}
#endif
		}
		else if (currNode->isObject() || currNode->isDocument())
		{
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
			// use cache in debug mode to improve performance
			if (!currNode->d_cacheJsonObj.isEmpty())
			{
				jsonObject[currNodeKey] = currNode->d_cacheJsonObj;
			}
			else
			{
#endif
				QJsonObject tmpObject = currNode->m_jsonValue.toObject();
				currNode->toJsonObject(tmpObject);
				jsonObject[currNodeKey] = tmpObject;
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
			}
#endif
		}
		else
		{
			// copy raw value
			jsonObject[currNodeKey] = currNode->m_jsonValue;
		}
	}
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	d_cacheJsonObj = jsonObject;
#endif
}

void QJsNodeData::toJsonArray(QJsonArray &jsonArray)
{
	for (int i = 0; i < m_vectorChildren.count(); i++)
	{

		auto currNodeKey = m_vectorChildren.at(i)->m_strKeyName;
		// check if all good
		if (m_vectorChildren.at(i)->getKeyName().compare(QString::number(i), Qt::CaseInsensitive) != 0)
		{
			Q_ASSERT_X(false, "QJsNodeData::toJsonArray", "Non matching key names for array in QJsNodeData::toJsonArray");
			qWarning() << "[WARN] non matching key names for array in QJsNodeData::toJsonArray";
			m_vectorChildren.at(i)->m_strKeyName = QString::number(i);
		}
		// append child
		auto currNode    = m_vectorChildren.at(i);
		if (currNode->isArray())
		{
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
			// use cache in debug mode to improve performance
			if (!currNode->d_cacheJsonArr.isEmpty())
			{
				jsonArray.append(currNode->d_cacheJsonArr);
			}
			else
			{
#endif
				QJsonArray tmpArray;
				currNode->toJsonArray(tmpArray);
				jsonArray.append(tmpArray);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
			}
#endif
		}
		else if (currNode->isObject() || currNode->isDocument())
		{
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
			// use cache in debug mode to improve performance
			if (!currNode->d_cacheJsonObj.isEmpty())
			{
				jsonArray.append(currNode->d_cacheJsonObj);
			}
			else
			{
#endif
				QJsonObject tmpObject = currNode->m_jsonValue.toObject();
				currNode->toJsonObject(tmpObject);
				jsonArray.append(tmpObject);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
			}
#endif
		}
		else
		{
			// copy raw value
			jsonArray.append(currNode->m_jsonValue);
		}
	}
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	d_cacheJsonArr = jsonArray;
#endif
}

void QJsNodeData::fromJsonObject(QJsonObject &jsonObject)
{
	// check this is object or document
	if (!this->isObject() && !this->isDocument())
	{
		qDebug() << "[ERROR] cannot load an QJsonObject on a non QJsObject instance in QJsNodeData::fromJsonObject";
		return;
	}
	// loop through keys
	QStringList strListKeys = jsonObject.keys();
	for (int i = 0; i < strListKeys.count(); i++)
	{
		QString strCurrKey   = strListKeys.at(i);
		QJsonValue currValue = jsonObject.value(strCurrKey);
		// switch cases
		if (currValue.isNull() || currValue.isUndefined())
		{
			continue;
		}
		else if (currValue.isArray())
		{
			// recursivelly load child array
			this->recursivellyLoadChildArray(currValue, strCurrKey);
		}
		else if (currValue.isObject())
		{
			// recursivelly load child object
			this->recursivellyLoadChildObject(currValue, strCurrKey);
		}
		else
		{
			// consider the case when attribute is text representing another json object/array
			if (currValue.isString())
			{
				QJsonParseError error;
				QJsonDocument doc = QJsonDocument::fromJson(currValue.toString().toUtf8(), &error);
				if (error.error == QJsonParseError::NoError)
				{
					if (doc.isObject())
					{
						// recursivelly load child object
						this->recursivellyLoadChildObject(QJsonValue(doc.object()), strCurrKey);
					}
					else if (doc.isArray())
					{
						// recursivelly load child array
						this->recursivellyLoadChildArray(QJsonValue(doc.array()), strCurrKey);
					}
					else
					{
						// copy atributte
						QExplicitlySharedDataPointer<QJsObjectData>(static_cast<QJsObjectData*>(this))->setAttribute(strCurrKey, currValue.toVariant());
					}
				}
				else
				{
					// copy atributte
					QExplicitlySharedDataPointer<QJsObjectData>(static_cast<QJsObjectData*>(this))->setAttribute(strCurrKey, currValue.toVariant());
				}
			}
			else
			{
				// copy atributte
				QExplicitlySharedDataPointer<QJsObjectData>(static_cast<QJsObjectData*>(this))->setAttribute(strCurrKey, currValue.toVariant());
			}
		}
	}
}

void QJsNodeData::fromJsonArray(QJsonArray &jsonArray)
{
	// check this is object or document
	if (!this->isArray())
	{
		qDebug() << "[ERROR] cannot load an QJsonArray on a non QJsArray instance in QJsNodeData::fromJsonArray";
		return;
	}
	// loop though array values


	for (int i = 0; i < jsonArray.count(); i++)
	{
		QString strCurrKey   = QString::number(i);
		QJsonValue currValue = jsonArray.at(i);
		// switch cases
		if (currValue.isNull() || currValue.isUndefined())
		{
			continue;
		}
		else if (currValue.isArray())
		{
			// recursivelly load child array
			this->recursivellyLoadChildArray(currValue, strCurrKey);
		}
		else if (currValue.isObject())
		{
			// recursivelly load child object
			this->recursivellyLoadChildObject(currValue, strCurrKey);
		}
		else
		{
			// consider the case when attribute is text representing another json object/array
			if (currValue.isString())
			{
				QJsonParseError error;
				QJsonDocument doc = QJsonDocument::fromJson(currValue.toString().toUtf8(), &error);
				if (error.error == QJsonParseError::NoError)
				{
					if (doc.isObject())
					{
						// recursivelly load child object
						this->recursivellyLoadChildObject(QJsonValue(doc.object()), strCurrKey);
					} 
					else if (doc.isArray())
					{
						// recursivelly load child array
						this->recursivellyLoadChildArray(QJsonValue(doc.array()), strCurrKey);
					}
					else
					{
						// copy value
						QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this))->appendValue(currValue.toVariant());
					}
				}
				else
				{
					// copy value
					QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this))->appendValue(currValue.toVariant());
				}
			}
			else
			{
				// copy value
				QExplicitlySharedDataPointer<QJsArrayData>(static_cast<QJsArrayData*>(this))->appendValue(currValue.toVariant());
			}
		}
	}
}

void QJsNodeData::recursivellyLoadChildArray(QJsonValue &currValue, QString &strCurrKey)
{
	auto newArrChild          = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData());
	newArrChild->m_strKeyName = strCurrKey;
	QJsonArray newJsonArr     = currValue.toArray();
	newArrChild->fromJsonArray(newJsonArr);
	if (!newArrChild->setParentNode(this))
	{
		qDebug() << "[ERROR] loading child array failed in QJsNodeData::fromJsonArray";
	}
}

void QJsNodeData::recursivellyLoadChildObject(QJsonValue &currValue, QString &strCurrKey)
{
	auto newObjChild          = QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData());
	newObjChild->m_strKeyName = strCurrKey;
	QJsonObject newJsonObj    = currValue.toObject();
	newObjChild->fromJsonObject(newJsonObj);
	if (!newObjChild->setParentNode(this))
	{
		qDebug() << "[ERROR] loading child object failed in QJsNodeData::fromJsonArray";
	}
}

#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)

void QJsNodeData::recalcDebugVars()
{
	// key name
	d_strKeyName  = m_strKeyName.toStdString();
	// full json data
	d_strJsonFull = this->toJson(QJsonDocument::Compact).toStdString();
	// parent key name and recursive call
	auto parent = parentNode();
	if (parent)
	{
		d_strParentKeyName = parent->m_strKeyName.toStdString();
		parent->recalcDebugVars();
	}
	else
	{
		d_strParentKeyName = "";
	}
}

#endif