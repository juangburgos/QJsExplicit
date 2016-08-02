#ifndef QJSOBJECT_H
#define QJSOBJECT_H

#include "qjsnode.h"

class QJsObject : public QJsNode
{
public:
    QJsObject();
    QJsObject(const QJsObject &);
    QJsObject &operator=(const QJsObject &);
    ~QJsObject();

	QStringList attributeNames();

	QVariant    attributeValue(QString strName);

	bool        isBool(QString strName);

	bool        isInteger(QString strName);

	bool        isDouble(QString strName);

	bool        isString(QString strName);

	void	    setAttribute(const QString &strName, bool    boolValue);

	void	    setAttribute(const QString &strName, int     intValue);

	void	    setAttribute(const QString &strName, double  doubleValue);

	void	    setAttribute(const QString &strName, QString strValue);

	void        removeAttribute(const QString &strName);
};

#endif // QJSOBJECT_H
