#ifndef QJSOBJECTDATA_H
#define QJSOBJECTDATA_H

#include "qjsnodedata.h"

class QJsDocumentData;

class QJsObjectData : public QJsNodeData
{
	friend class QJsNodeData;
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
	void	    setAttribute(const QString &strName, bool       boolValue); // TODO : return reference to this to allow chaining
	void	    setAttribute(const QString &strName, int        intValue );
	void	    setAttribute(const QString &strName, quint32    uint32Value);
	void	    setAttribute(const QString &strName, qint64     int64Value);
	void	    setAttribute(const QString &strName, qulonglong intULLValue);
	void	    setAttribute(const QString &strName, float      floatValue);
	void	    setAttribute(const QString &strName, double     doubleValue);
	void	    setAttribute(const QString &strName, QString    strValue);
	void	    setAttribute(const QString &strName, QVariant   varValue);

	QVariant    removeAttribute(const QString &strName);

#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
protected:
	// call on every edition
	void recalcDebugVars(bool bForce = true) Q_DECL_OVERRIDE;
#endif

private:
	template<typename T>
	void	    setAttributeInternal(const QString &strName, T tValue);
};

template<typename T>
void QJsObjectData::setAttributeInternal(const QString &strName, T tValue)
{
	// implicit shared object upodating
	QJsonObject tmpObject = m_jsonValue.toObject();
	tmpObject[strName]    = tValue;
	m_jsonValue           = tmpObject;
}

#endif // QJSOBJECTDATA_H
