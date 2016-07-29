#include "qjsnode.h"
#include "qjsnodedata.h"

QJsNode::QJsNode() : data(new QJsNodeData()) // force QJsNodeData to receive a QJsonValue
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
