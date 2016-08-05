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
    QJsNode();
    QJsNode(const QJsNode &);
    QJsNode &operator=(const QJsNode &);
    ~QJsNode();

	enum JsFormat
	{
		Indented,
		Compact
	};

	void           setKeyName(const QString &strKeyName);

	QString        getKeyName();

	QJsNode        parentNode();

	QJsDocument    ownerDocument();

	bool           hasChildByKey(const QString &strKeyName);

	QList<QJsNode> childNodes();

	QStringList    childrenKeys();

	QJsNode        getChildByKey(const QString &strKeyName);

	QJsObject      createObject(const QString &strKeyName = "");

	QJsArray       createArray(const QString &strKeyName = "");

	QJsNode        appendChild (const QJsNode &nodeData);

	QJsNode        removeChild (const QString &strKeyName);

	QJsNode        replaceChild(const QString &strKeyName, QJsNode &nodeData);

	bool           isNull();

	bool           isObject();

	bool           isArray();

	bool           isDocument();

	QJsObject      toObject();

	QJsArray       toArray();

	QJsDocument    toDocument();

	QJsNode        clone();

	QByteArray     toJson(JsFormat format = Indented);

	QByteArray	   toBinaryData();

protected:
    QExplicitlySharedDataPointer<QJsNodeData> data;

};

#endif // QJSNODE_H
