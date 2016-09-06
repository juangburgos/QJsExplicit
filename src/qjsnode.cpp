#include "qjsnode.h"
#include "qjsobject.h"
#include "qjsarray.h"
#include "qjsdocument.h"

#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

#include <QJsonDocument>

QJsNode::QJsNode() : data(new QJsNodeData())
{

}

QJsNode::QJsNode(const QJsNode &rhs) : data(rhs.data)
{

}

QJsNode &QJsNode::operator=(const QJsNode &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QJsNode::~QJsNode()
{

}

void QJsNode::setKeyName(const QString &strKeyName)
{
	data->setKeyName(strKeyName);
}

QString QJsNode::getKeyName()
{
	return data->getKeyName();
}

QJsNode QJsNode::parentNode()
{
	QJsNode node;
	node.data = data->parentNode();
	return node;
}

QJsDocument QJsNode::ownerDocument()
{
	QJsDocument doc;
	doc.data = data->ownerDocument();
	return doc;
}

bool QJsNode::hasChildByKey(const QString &strKeyName)
{
	return data->hasChildByKey(strKeyName);
}

QList<QJsNode> QJsNode::childNodes()
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

QStringList QJsNode::childrenKeys()
{
	return data->childrenKeys();
}

QJsNode QJsNode::getChildByKey(const QString &strKeyName)
{
	QJsNode node;
	node.data = data->getChildByKey(strKeyName);
	return node;
}

QJsObject QJsNode::createObject(const QString &strKeyName /*= ""*/)
{
	QJsObject obj;
	obj.data = data->createObject(strKeyName);
	return obj;
}

QJsArray QJsNode::createArray(const QString &strKeyName /*= ""*/)
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

QJsNode QJsNode::removeChild(const QString &strKeyName)
{
	auto res = data->removeChild(strKeyName);
	if (!res)
	{
		return QJsNode();
	}
	QJsNode node;
	node.data = res;
	return node;
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

bool QJsNode::isNull()
{
	if (!data || data->isNull())
	{
		return true;
	}
	return false;
}

bool QJsNode::isValid()
{
	if (data->isValid())
	{
		return true;
	}
	return false;
}

bool QJsNode::isObject()
{
	return data->isObject();
}

bool QJsNode::isArray()
{
	return data->isArray();
}

bool QJsNode::isDocument()
{
	return data->isDocument();
}

QJsObject QJsNode::toObject()
{
	QJsObject obj;
	obj.data = data->toObject();
	return obj;
}

QJsArray QJsNode::toArray()
{
	QJsArray arr;
	arr.data = data->toArray();
	return arr;
}

QJsDocument QJsNode::toDocument()
{
	QJsDocument doc;
	doc.data = data->toDocument();
	return doc;
}

QJsNode QJsNode::clone()
{
	auto res = data->clone();
	QJsNode obj;
	obj.data = res;
	return obj;
}

QByteArray QJsNode::toJson(JsFormat format /*= Indented*/)
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

QByteArray QJsNode::toBinaryData()
{
	return data->toBinaryData();
}
