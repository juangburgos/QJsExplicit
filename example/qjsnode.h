#ifndef QJSNODE_H
#define QJSNODE_H

#include <QList>
#include <QExplicitlySharedDataPointer>

class QJsNodeData;

class QJsNode
{
public:
    QJsNode();
    QJsNode(const QJsNode &);
    QJsNode &operator=(const QJsNode &);
    ~QJsNode();

protected:
    QExplicitlySharedDataPointer<QJsNodeData> data;

};

#endif // QJSNODE_H
