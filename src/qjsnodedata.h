#ifndef QJSNODEDATA_H
#define QJSNODEDATA_H

#include <QSharedData>
#include <QJsonValue>

class QJsNodeData : public QSharedData
{
public:
    QJsNodeData();
    QJsNodeData(const QJsonValue &jsonValue);

    // NOTE : we put in and put out QExplicitlySharedDataPointer<QJsNodeData> instances
    //        because we can use those to create instances of the QJsNode wrappers

    // parents can only be QJsObjectData or QJsDocumentData
    // the parent of a QJsDocumentData must be nullptr
    virtual QExplicitlySharedDataPointer<QJsNodeData>        parentNode();
    // necessary for reparenting (not valid for QJsDocumentData)
    virtual void setParentNode(const QExplicitlySharedDataPointer<QJsNodeData> &newParent);

    // children can only be QJsObjectData or QJsArrayData
    QList<QExplicitlySharedDataPointer<QJsNodeData>> childNodes();


    //Appends newChild as the node's last child.
    //If newChild is the child of another node, it is reparented to this node.
    //If newChild is a child of this node, then its position in the list of children is changed.
    //Returns a new reference to newChild on success or a null node on failure.
    //Calling this function on a null node(created, for example, with the default constructor)
    //does nothing and returns a null node.
    QExplicitlySharedDataPointer<QJsNodeData>        appendChild(const QExplicitlySharedDataPointer<QJsNodeData> &newChild);

    // isNull if m_jsonValue is NULL
    bool isNull();



protected:
    QJsonValue m_jsonValue;

    QExplicitlySharedDataPointer<QJsNodeData>          m_parent;
    QList<QExplicitlySharedDataPointer<QJsNodeData>>   m_listChildren;

};

#endif // QJSNODEDATA_H
