#ifndef QJSDOCUMENTDATA_H
#define QJSDOCUMENTDATA_H

#include "qjsnodedata.h"

class QJsDocumentData : public QJsNodeData
{
public:
    QJsDocumentData(const QJsonValue &jsonValue);

};

#endif // QJSDOCUMENTDATA_H
