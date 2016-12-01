#ifndef QJSNODEDATA_H
#define QJSNODEDATA_H

#include <QMap>

#include <QVariant>
#include <QByteArray>
#include <QSharedData>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

//#include "qjsobjectdata.h"
//#include "qjsarraydata.h"
//#include "qjsdocumentdata.h"

class QJsObjectData;
class QJsArrayData;
class QJsDocumentData;

class QJsNodeData : public QSharedData
{
	friend class QJsArrayData;
public:
    QJsNodeData();
    QJsNodeData(const QJsNodeData &other);
	~QJsNodeData();

    // NOTE : we put in and put out QExplicitlySharedDataPointer<QJsNodeData> instances
    //        because we can use those to create instances of the QJsNode wrappers

	// In case of parent is array, key is index in array
	void    setKeyName(const QString &strKeyName); // TODO : return reference to this to allow chaining
	QString getKeyName();

	void       setJsonValue(const QJsonValue &jsonValue);
	QJsonValue getJsonValue();
	void       updateJsonValue(const QJsonValue &jsonValue);

    // parents can only be QJsObjectData or QJsDocumentData
    // the parent of a QJsDocumentData must be nullptr
    virtual QJsNodeData * parentNode();
    // necessary for reparenting (not valid for QJsDocumentData)
    virtual bool setParentNode(QJsNodeData * newParent);

	// get root
	QExplicitlySharedDataPointer<QJsDocumentData>    ownerDocument();
	bool                                             hasChildByKey(const QString &strKeyName);

    // children can only be QJsObjectData or QJsArrayData
    QList<QExplicitlySharedDataPointer<QJsNodeData>> childNodes();
	QStringList                                      childrenKeys();
	QExplicitlySharedDataPointer<QJsNodeData>        getChildByKey(const QString &strKeyName);

	QExplicitlySharedDataPointer<QJsObjectData>      createObject(const QString &strKeyName = "");
	QExplicitlySharedDataPointer<QJsArrayData>       createArray (const QString &strKeyName = "");
	void                                             recreateChildren();
	void                                             removeChildren();

    // Appends newChild as the node's last child.
    // If newChild is the child of another node, it is reparented to this node.
    // If newChild is a child of this node, then its position in the list of children is changed.
    // Returns a new reference to newChild on success or a null node on failure.
    // Calling this function on a null node(created, for example, with the default constructor)
    // does nothing and returns a null node.
	// Will fail also if key name is empty and parent is not array
    QExplicitlySharedDataPointer<QJsNodeData> appendChild(const QExplicitlySharedDataPointer<QJsNodeData> &nodeData);
	void                                      removeChild(const QString &strKeyName);
	QExplicitlySharedDataPointer<QJsNodeData> replaceChild(const QString &strKeyName, const QExplicitlySharedDataPointer<QJsNodeData> &nodeData);

    // isNull if m_jsonValue is NULL
    bool isNull();
	// isValid if key is non empty and m_jsonValue is not NULL
	bool isValid();

	// Each class reimplementation must return true accordingly
	virtual bool isObject();
	virtual bool isArray();
	virtual bool isDocument();

	// create new instances of each class if can be casted if not null
	QExplicitlySharedDataPointer<QJsObjectData>    toObject();
	QExplicitlySharedDataPointer<QJsArrayData>     toArray();
	QExplicitlySharedDataPointer<QJsDocumentData>  toDocument();

	QExplicitlySharedDataPointer<QJsNodeData> clone();

	QByteArray	toJson(QJsonDocument::JsonFormat format = QJsonDocument::Indented);
	QByteArray	toBinaryData();



protected:
    QString                                                  m_strKeyName;
    QJsonValue                                               m_jsonValue;
	QJsNodeData                                            * m_parent;
	QMap<QString, QExplicitlySharedDataPointer<QJsNodeData>> m_mapChildren;

	// [WARNING] : This approach was causing memory leaks because when a parent obj
	//             was out of scope of use the the top level application, the reference
	//             count was decreased by 1 but its children still had references to it, 
	//             so its instance was kept floating, never released.
	//             This was clearly visible when an application would call the QJsNode::clone()
	//             method multiple times to perform temporary operations.
    //QExplicitlySharedDataPointer<QJsNodeData>                m_parent; 

};

#endif // QJSNODEDATA_H
