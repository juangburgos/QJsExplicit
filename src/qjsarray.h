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

	int      count();

	QVariant getValueAt(int idx);

	QJsNode  getNodeAt(int idx);

	bool     isBool(int idx);

	bool     isInteger(int idx);

	bool     isDouble(int idx);

	bool     isString(int idx);

	bool     isObject(int idx);

	bool     isArray(int idx);

	void	 setValueAt(int idx, bool    boolValue);

	void	 setValueAt(int idx, int     intValue);

	void	 setValueAt(int idx, double  doubleValue);

	void	 setValueAt(int idx, QString strValue);

	void	 setValueAt(int idx, const char *str);

	void     setNodeAt(int idx, QJsNode  nodeValue);

	void	 setObjectAt(int idx, QJsObject objValue);

	void	 setArrayAt(int idx, QJsArray arrValue);

	void	 appendValue(bool    boolValue);

	void	 appendValue(int     intValue);

	void	 appendValue(double  doubleValue);

	void	 appendValue(QString strValue);

	void	 appendObject(QJsObject objValue);

	void	 appendArray(QJsArray arrValue);

	QVariant removeValueAt(int   idx);

	int      removeValue(int     intValue);

	QString  removeValue(QString strValue);

	// TODO : insert (shift others) require recreateChildren

};

#endif // QJSARRAY_H
