#include "qjsnode.h"
#include "qjsobject.h"
#include "qjsarray.h"
#include "qjsdocument.h"

#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

#include <QJsonDocument>

QJsNode::QJsNode() : data(nullptr)
{
	data = QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData());
}

QJsNode::QJsNode(const QJsNode &rhs) : data(rhs.data)
{
	data.reset();
	data = rhs.data;
}

QJsNode &QJsNode::operator=(const QJsNode &rhs)
{
	if (this != &rhs) {
		data.reset();
		data.operator=(rhs.data);
	}
    return *this;
}

QJsNode::~QJsNode()
{
	data.reset();
}

void QJsNode::setKeyName(const QString &strKeyName)
{
	data->setKeyName(strKeyName);
}

QString QJsNode::getKeyName() const
{
	return data->getKeyName();
}

QJsNode QJsNode::parentNode() const
{
	QJsNode node;
	node.data = data->parentNode();
	return node;
}

QJsDocument QJsNode::ownerDocument() const
{
	QJsDocument doc;
	doc.data = data->ownerDocument();
	return doc;
}

bool QJsNode::hasChildByKey(const QString &strKeyName) const
{
	return data->hasChildByKey(strKeyName);
}

QList<QJsNode> QJsNode::childNodes() const
{
	QList<QJsNode> listChildNodes;
	for (int i = 0; i < data->childNodes().count(); i++)
	{
		QJsNode node;
		node.data = data->childNodes().at(i);
		listChildNodes.append(node);
	}
	return listChildNodes;
}

QStringList QJsNode::childrenKeys() const
{
	return data->childrenKeys();
}

QJsNode QJsNode::getChildByKey(const QString &strKeyName) const
{
	QJsNode node;
	node.data = data->getChildByKey(strKeyName);
	return node;
}

QJsObject QJsNode::createObject(const QString &strKeyName /*= ""*/) const
{
	QJsObject obj;
	obj.data = data->createObject(strKeyName);
	return obj;
}

QJsArray QJsNode::createArray(const QString &strKeyName /*= ""*/) const
{
	QJsArray arr;
	arr.data = data->createArray(strKeyName);
	return arr;
}

QJsNode QJsNode::appendChild(const QJsNode &nodeData)
{
	auto res = data->appendChild(nodeData.data);
	if (!res)
	{
		return QJsNode();
	}
	QJsNode node;
	node.data = res;
	return node;
}

void QJsNode::removeChild(const QString &strKeyName)
{
	if (data->hasChildByKey(strKeyName))
	{
		data->removeChild(strKeyName);
	}
}

QJsNode QJsNode::replaceChild(const QString &strKeyName, QJsNode &nodeData)
{
	auto res = data->replaceChild(strKeyName, nodeData.data);
	if (!res)
	{
		return QJsNode();
	}
	QJsNode node;
	node.data = res;
	return node;
}

bool QJsNode::isValid() const
{
	if (data->isValid())
	{
		return true;
	}
	return false;
}

bool QJsNode::isEmpty() const
{
	if (data->isEmpty())
	{
		return true;
	}
	return false;
}

bool QJsNode::isObject() const
{
	return data->isObject();
}

bool QJsNode::isArray() const
{
	return data->isArray();
}

bool QJsNode::isDocument() const
{
	return data->isDocument();
}

QJsObject QJsNode::toObject() const
{
	QJsObject obj;
	obj.data = data->toObject();
	return obj;
}

QJsArray QJsNode::toArray() const
{
	QJsArray arr;
	arr.data = data->toArray();
	return arr;
}

QJsDocument QJsNode::toDocument() const
{
	QJsDocument doc;
	doc.data = data->toDocument();
	return doc;
}

QJsNode QJsNode::clone() const
{
	auto res = data->clone();
	QJsNode obj;
	obj.data = res;
	return obj;
}

QByteArray QJsNode::toJson(JsFormat format /*= Indented*/) const
{
	switch (format)
	{
	case QJsNode::Indented:
		return data->toJson(QJsonDocument::Indented);
		break;
	case QJsNode::Compact:
		return data->toJson(QJsonDocument::Compact);
		break;
	default:
		return QByteArray();
		break;
	}
	return QByteArray();
}

QByteArray QJsNode::toBinaryData() const
{
	return data->toBinaryData();
}