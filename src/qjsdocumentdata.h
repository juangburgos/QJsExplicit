#ifndef QJSDOCUMENTDATA_H
#define QJSDOCUMENTDATA_H

#include "qjsobjectdata.h"

class QJsDocumentData : public QJsObjectData
{
public:
    QJsDocumentData();

	// override necessary base class methods
	bool isDocument() Q_DECL_OVERRIDE;
	QExplicitlySharedDataPointer<QJsNodeData> parentNode() Q_DECL_OVERRIDE;
	bool setParentNode(const QExplicitlySharedDataPointer<QJsNodeData> &newParent) Q_DECL_OVERRIDE;

	// return error message
	QString    	fromJson(const QByteArray &json);
	QString  	fromBinaryData(const QByteArray &data);

};

#endif // QJSDOCUMENTDATA_H
