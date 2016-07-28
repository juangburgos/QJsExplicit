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

    // TODO : in QJsNode only implement child-parent hierarchy
    // parents can only be QJsObject or QJsDocument
    // children can only be QJsObject or QJsArray

    QJsNode          parentNode();
    QList<QJsNode>   childNodes();

/*
Appends newChild as the node's last child.
If newChild is the child of another node, it is reparented to this node.
If newChild is a child of this node, then its position in the list of children is changed.
Returns a new reference to newChild on success or a null node on failure.

Calling this function on a null node(created, for example, with the default constructor) does nothing and returns a null node.
*/
    //QJsNode          appendChild(const QJsNode &newChild);

protected:
    QExplicitlySharedDataPointer<QJsNodeData> data;

    QJsNode        * m_parent;
    QList<QJsNode>   m_listChildren;
};

#endif // QJSNODE_H
