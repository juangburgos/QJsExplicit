#ifndef QJSARRAYDATA_H
#define QJSARRAYDATA_H

#include "qjsnodedata.h"

class QJsArrayData : public QJsNodeData
{
public:
    QJsArrayData();

	// override necessary base class methods
	bool isArray() Q_DECL_OVERRIDE;

	// implement attributes API
	int count();

	QVariant                                  getValueAt(int idx);
	QExplicitlySharedDataPointer<QJsNodeData> getNodeAt(int idx);

	bool        isBool   (int idx);
	bool        isInteger(int idx);
	bool        isDouble (int idx);
	bool        isString (int idx);

	bool        isObject (int idx);
	bool        isArray  (int idx);

	// set or replace is the same
	void	    setValueAt(int idx, bool    boolValue);
	void	    setValueAt(int idx, int     intValue);
	void	    setValueAt(int idx, double  doubleValue);
	void	    setValueAt(int idx, QString strValue);

	void        setNodeAt  (int idx, QExplicitlySharedDataPointer<QJsNodeData>   nodeValue);
	void	    setObjectAt(int idx, QExplicitlySharedDataPointer<QJsObjectData> objValue);
	void	    setArrayAt (int idx, QExplicitlySharedDataPointer<QJsArrayData>  arrValue);

	// append adds a new at the end
	void	    appendValue(bool    boolValue);
	void	    appendValue(int     intValue);
	void	    appendValue(double  doubleValue);
	void	    appendValue(QString strValue);

	void	    appendObject(QExplicitlySharedDataPointer<QJsObjectData> objValue);
	void	    appendArray (QExplicitlySharedDataPointer<QJsArrayData>  arrValue);

	// TODO : insert (shift others) require recreateChildren


};

#endif // QJSARRAYDATA_H
