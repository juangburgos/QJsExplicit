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
public:
    QJsNodeData();
    QJsNodeData(const QJsNodeData &other);

    // NOTE : we put in and put out QExplicitlySharedDataPointer<QJsNodeData> instances
    //        because we can use those to create instances of the QJsNode wrappers

	// In case of parent is array, key is index in array
	void    setKeyName(const QString &strKeyName);
	QString getKeyName();

	void       setJsonValue(const QJsonValue &jsonValue);
	QJsonValue getJsonValue();
	void       updateJsonValue(const QJsonValue &jsonValue);

    // parents can only be QJsObjectData or QJsDocumentData
    // the parent of a QJsDocumentData must be nullptr
    virtual QExplicitlySharedDataPointer<QJsNodeData>        parentNode();
    // necessary for reparenting (not valid for QJsDocumentData)
    virtual bool setParentNode(const QExplicitlySharedDataPointer<QJsNodeData> &newParent);

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

    // Appends newChild as the node's last child.
    // If newChild is the child of another node, it is reparented to this node.
    // If newChild is a child of this node, then its position in the list of children is changed.
    // Returns a new reference to newChild on success or a null node on failure.
    // Calling this function on a null node(created, for example, with the default constructor)
    // does nothing and returns a null node.
	// Will fail also if key name is empty and parent is not array
    QExplicitlySharedDataPointer<QJsNodeData> appendChild(const QExplicitlySharedDataPointer<QJsNodeData> &nodeData);
	QExplicitlySharedDataPointer<QJsNodeData> removeChild(const QString &strKeyName);
	QExplicitlySharedDataPointer<QJsNodeData> replaceChild(const QString &strKeyName, const QExplicitlySharedDataPointer<QJsNodeData> &nodeData);

    // isNull if m_jsonValue is NULL
    bool isNull();

	// Each class reimplementation must return true accordingly
	virtual bool isObject();
	virtual bool isArray();
	virtual bool isDocument();

	// create new instances of each class if can be casted if not null
	QExplicitlySharedDataPointer<QJsObjectData>    toObject();
	QExplicitlySharedDataPointer<QJsArrayData>     toArray();
	QExplicitlySharedDataPointer<QJsDocumentData>  toDocument();

	QByteArray	toJson(QJsonDocument::JsonFormat format = QJsonDocument::Indented);
	QByteArray	toBinaryData();



protected:
    QString                                                  m_strKeyName;
    QJsonValue                                               m_jsonValue;
    QExplicitlySharedDataPointer<QJsNodeData>                m_parent;
	QMap<QString, QExplicitlySharedDataPointer<QJsNodeData>> m_mapChildren;


};

#endif // QJSNODEDATA_H
