#ifndef QJSARRAY_H
#define QJSARRAY_H

#include "qjsnode.h"

class QJsArray : public QJsNode
{
public:
    QJsArray();
    QJsArray(const QJsArray &);
    QJsArray &operator=(const QJsArray &);
    ~QJsArray();

	// return this QJsArray to allow chain
	QJsArray setKeyName(const QString &strKeyName);

	int      count() const;

	QVariant getValueAt(int idx) const;

	QJsNode  getNodeAt(int idx) const;

	bool     isBool(int idx) const;

	bool     isInteger(int idx) const;

	bool     isDouble(int idx) const;

	bool     isString(int idx) const;

	bool     isObject(int idx) const;

	bool     isArray(int idx) const;

	QJsArray  setValueAt(int idx, bool    boolValue);

	QJsArray  setValueAt(int idx, int     intValue);

	QJsArray  setValueAt(int idx, double  doubleValue);

	QJsArray  setValueAt(int idx, QString strValue);

	QJsArray  setValueAt(int idx, const char *str);

	QJsArray  setNodeAt(int idx, QJsNode  nodeValue);

	QJsArray  setObjectAt(int idx, QJsObject objValue);

	QJsArray  setArrayAt(int idx, QJsArray arrValue);

	QJsArray  appendValue(bool    boolValue);

	QJsArray  appendValue(int     intValue);

	QJsArray  appendValue(double  doubleValue);

	QJsArray  appendValue(QString strValue);

	QJsArray  appendObject(QJsObject objValue);

	QJsArray  appendArray(QJsArray arrValue);

	QVariant removeValueAt(int   idx);

	int      removeValue(int     intValue);

	QString  removeValue(QString strValue);

	QJsArray clone() const;

	// TODO : insert (shift others) require recreateChildren

};

#endif // QJSARRAY_H
