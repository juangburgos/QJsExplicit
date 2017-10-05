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

	QStringList attributeNames() const;

	bool        hasAttribute(const QString &strName) const;

	QVariant    attributeValue(QString strName) const;

	template<typename T>
	T           attributeValue(QString strName) const;

	bool        isBool(QString strName) const;

	bool        isInteger(QString strName) const;

	bool        isDouble(QString strName) const;

	bool        isString(QString strName) const;

	void	    setAttribute(const QString &strName, bool    boolValue);

	void	    setAttribute(const QString &strName, int     intValue);

	void	    setAttribute(const QString &strName, quint32 uint32Value);

	void	    setAttribute(const QString &strName, qint64  int64Value);

	void	    setAttribute(const QString &strName, double  doubleValue);

	void	    setAttribute(const QString &strName, QString strValue);

	void	    setAttribute(const QString &strName, const char *str); // helper

	void	    setAttribute(const QString &strName, QVariant varValue);

	void        removeAttribute(const QString &strName);

	QJsObject   clone() const;

	void        removeAllAttributes(); // helper

	void        mergeAttributesFrom(QJsObject jsObjSource);
};

#endif // QJSOBJECT_H
