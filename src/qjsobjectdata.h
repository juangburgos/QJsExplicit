#ifndef QJSOBJECTDATA_H
#define QJSOBJECTDATA_H

#include "qjsnodedata.h"

class QJsDocumentData;

class QJsObjectData : public QJsNodeData
{
	friend class QJsDocumentData;
public:
    QJsObjectData();
	~QJsObjectData();

	// override necessary base class methods
	bool isObject()   Q_DECL_OVERRIDE;
	bool isArray()    Q_DECL_OVERRIDE;
	bool isDocument() Q_DECL_OVERRIDE;

	// implement attributes API
	QStringList attributeNames();
	bool        hasAttribute(const QString &strName);
	QVariant    attributeValue(QString strName);

	bool        isBool(QString strName);
	bool        isInteger(QString strName);
	bool        isDouble(QString strName);
	bool        isString(QString strName);

	// set or insert or append is the same
	void	    setAttribute(const QString &strName, bool     boolValue); // TODO : return reference to this to allow chaining
	void	    setAttribute(const QString &strName, int      intValue );
	void	    setAttribute(const QString &strName, qint64   int64Value);
	void	    setAttribute(const QString &strName, double   doubleValue);
	void	    setAttribute(const QString &strName, QString  strValue);
	void	    setAttribute(const QString &strName, QVariant varValue);

	void        removeAttribute(const QString &strName);
};


#endif // QJSOBJECTDATA_H
