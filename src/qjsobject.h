#ifndef QJSOBJECT_H
#define QJSOBJECT_H

#include "qjsnode.h"

class QJsObject : public QJsNode
{
	friend class QJsDocument;
public:
    QJsObject();
    QJsObject(const QJsObject &);
    QJsObject &operator=(const QJsObject &);
    ~QJsObject();

	// return this QJsObject to allow chain
	QJsObject   setKeyName(const QString &strKeyName);

	QStringList attributeNames() const;

	bool        hasAttribute(const QString &strName) const;

	QVariant    attributeValue(QString strName) const;

	template<typename T>
	T           attributeValue(QString strName) const;

	bool        isBool(QString strName) const;

	bool        isInteger(QString strName) const;

	bool        isDouble(QString strName) const;

	bool        isString(QString strName) const;

	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, bool    boolValue);
	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, int     intValue);
	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, quint32 uint32Value);
	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, qint64  int64Value);
	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, qulonglong intULLValue);
	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, float   floatValue);
	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, double  doubleValue);
	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, QString strValue);
	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, QVariant varValue);
	// return this QJsObject to allow chain
	QJsObject   setAttribute(const QString &strName, const char *str);

	QVariant    removeAttribute(const QString &strName);

	QJsObject   clone() const;

	// return this QJsObject to allow chain
	QJsObject   removeAllAttributes();
	// return this QJsObject to allow chain
	QJsObject   mergeAttributesFrom(QJsObject jsObjSource);
};

#endif // QJSOBJECT_H
