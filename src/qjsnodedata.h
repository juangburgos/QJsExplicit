#ifndef QJSNODEDATA_H
#define QJSNODEDATA_H

#include <QMap>
#include <QVector>

#include <QVariant>
#include <QByteArray>
#include <QSharedData>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

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
	/* [API] */ bool    setKeyName(const QString &strKeyName); 
	/* [API] */ QString getKeyName();

    // parents can only be QJsObjectData or QJsDocumentData
    // the parent of a QJsDocumentData must be nullptr
	/* [API] */ virtual QJsNodeData * parentNode();

    // necessary for reparenting (not valid for QJsDocumentData)
    virtual bool setParentNode(QJsNodeData * newParent);

	// get root
	/* [API] */ QExplicitlySharedDataPointer<QJsDocumentData>    ownerDocument();
	/* [API] */ bool                                             hasChildByKey(const QString &strKeyName);

    // children can only be QJsObjectData or QJsArrayData
	/* [API] */ QList<QExplicitlySharedDataPointer<QJsNodeData>> childNodes();
	/* [API] */ QStringList                                      childrenKeys();
	/* [API] */ QExplicitlySharedDataPointer<QJsNodeData>        getChildByKey(const QString &strKeyName);

	/* [API] */ QExplicitlySharedDataPointer<QJsObjectData>      createObject(const QString &strKeyName = "");
	/* [API] */ QExplicitlySharedDataPointer<QJsArrayData>       createArray (const QString &strKeyName = "");

	// used for cleanup when this deleted (destructor)
	void removeChildren();

    // Appends newChild as the node's last child.
    // If newChild is the child of another node, it is reparented to this node.
    // If newChild is a child of this node, then its position in the list of children is changed.
    // Returns a new reference to newChild on success or a null node on failure.
    // Calling this function on a null node(created, for example, with the default constructor)
    // does nothing and returns a null node.
	// Will fail also if key name is empty and parent is not array
	/* [API] */ QExplicitlySharedDataPointer<QJsNodeData> appendChild(const QExplicitlySharedDataPointer<QJsNodeData> &nodeData);
	/* [API] */ bool                                      removeChild(const QString &strKeyName);
	/* [API] */ QExplicitlySharedDataPointer<QJsNodeData> replaceChild(const QString &strKeyName, const QExplicitlySharedDataPointer<QJsNodeData> &nodeData);

	// isValid if key is non empty and m_jsonValue is not NULL, also
	/* [API] */ bool isValid();
	bool isEmpty();

	// Each class reimplementation must return true accordingly
	/* [API] */ virtual bool isObject();
	/* [API] */ virtual bool isArray();
	/* [API] */ virtual bool isDocument();

	// create new instances of each class if can be casted if not null
	/* [API] */ QExplicitlySharedDataPointer<QJsObjectData>    toObject();
	/* [API] */ QExplicitlySharedDataPointer<QJsArrayData>     toArray();
	/* [API] */ QExplicitlySharedDataPointer<QJsDocumentData>  toDocument();

	/* [API] */ QExplicitlySharedDataPointer<QJsNodeData> clone();
	void cloneDeep(QExplicitlySharedDataPointer<QJsNodeData> parent);

	/* [API] */ QByteArray	toJson(QJsonDocument::JsonFormat format = QJsonDocument::Indented);
	/* [API] */ QByteArray	toBinaryData();

	// Recursive methods
	void toJsonObject(QJsonObject &jsonObject);
	void toJsonArray (QJsonArray  &jsonArray);
	void fromJsonObject(QJsonObject &jsonObject);
	void fromJsonArray(QJsonArray  &jsonArray);

#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	// call on every edition
	virtual void recalcDebugVars();
#endif

protected:
    QString                                                  m_strKeyName;
    QJsonValue                                               m_jsonValue;
	QJsNodeData                                            * m_parent;
	QMap<QString, QExplicitlySharedDataPointer<QJsNodeData>> m_mapChildren;
	QVector<QExplicitlySharedDataPointer<QJsNodeData>>       m_vectorChildren;

	void recursivellyLoadChildArray(QJsonValue &currValue, QString &strCurrKey);
	void recursivellyLoadChildObject(QJsonValue &currValue, QString &strCurrKey);

	// [WARNING] : This approach was causing memory leaks because when a parent obj
	//             was out of scope of use the the top level application, the reference
	//             count was decreased by 1 but its children still had references to it, 
	//             so its instance was kept floating, never released.
	//             This was clearly visible when an application would call the QJsNode::clone()
	//             method multiple times to perform temporary operations.
    //QExplicitlySharedDataPointer<QJsNodeData>                m_parent; 

#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	// debug variables (QJsNodeData)
	std::string d_strKeyName;
	std::string d_strJsonFull;
	std::string d_strParentKeyName;
	// debug variables (QJsObjectData)
	std::string d_strAttributes;
	// debug variables (QJsArrayData)
	std::string d_strCount;
	//// cache variable to improve 'toJson' performance during 'recalcDebugVars' call
	//QJsonObject d_cacheJsonObj;
	//QJsonArray  d_cacheJsonArr;
#endif

};

#endif // QJSNODEDATA_H
