#ifndef QJSNODE_H
#define QJSNODE_H

#include <QList>
#include <QVariant>
#include <QByteArray>

#include <QExplicitlySharedDataPointer>


class QJsNodeData;

class QJsObject;
class QJsArray;
class QJsDocument;

class QJsNode
{
	friend class QJsArray;
public:
	// constructor
    QJsNode();
	// copy
    QJsNode(const QJsNode &other);
	// assignment
    QJsNode &operator=(const QJsNode &rhs);
	// destructor
    ~QJsNode();
	// comparison ==
	bool operator==(const QJsNode& other);
	// comparison !=
	bool operator!=(const QJsNode& other);

	enum JsFormat
	{
		Indented,
		Compact
	};

	// return this QJsNode to allow chain
	QJsNode        setKeyName(const QString &strKeyName);

	QString        getKeyName() const;

	QJsNode        parentNode() const;

	QJsDocument    ownerDocument() const;

	bool           hasChildByKey(const QString &strKeyName) const;

	QList<QJsNode> childNodes() const;

	QStringList    childrenKeys() const;

	QJsNode        getChildByKey(const QString &strKeyName) const;

	QJsObject      createObject(const QString &strKeyName = "") const;

	QJsArray       createArray(const QString &strKeyName = "") const;

	QJsNode        appendChild (const QJsNode &nodeData);

	void           removeChild (const QString &strKeyName);

	QJsNode        replaceChild(const QString &strKeyName, QJsNode &nodeData);

	bool           isValid() const;

	bool           isEmpty() const;

	bool           isObject() const;

	bool           isArray() const;

	bool           isDocument() const;

	QJsObject      toObject() const;

	QJsArray       toArray() const;

	QJsDocument    toDocument() const;

	QJsNode        clone() const;

	QByteArray     toJson(JsFormat format = Indented) const;

	QByteArray	   toBinaryData() const;

protected:
    QExplicitlySharedDataPointer<QJsNodeData> data;

};

#endif // QJSNODE_H
