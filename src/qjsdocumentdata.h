#ifndef QJSDOCUMENTDATA_H
#define QJSDOCUMENTDATA_H

#include "qjsnodedata.h"

class QJsDocumentData : public QJsNodeData
{
public:
    QJsDocumentData();

	// override necessary base class methods
	bool isDocument() Q_DECL_OVERRIDE;
	QExplicitlySharedDataPointer<QJsNodeData> parentNode() Q_DECL_OVERRIDE;
	bool setParentNode(const QExplicitlySharedDataPointer<QJsNodeData> &newParent) Q_DECL_OVERRIDE;

	QExplicitlySharedDataPointer<QJsObjectData>    cloneToObject(const QString &strKeyName = "");
	// return error message
	QString    	fromJson(const QByteArray &json);
	QString  	fromBinaryData(const QByteArray &data);


};

#endif // QJSDOCUMENTDATA_H
