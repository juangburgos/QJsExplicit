#ifndef QJSARRAYDATA_H
#define QJSARRAYDATA_H

#include "qjsnodedata.h"

class QJsArrayData : public QJsNodeData
{
public:
    QJsArrayData(const QJsonValue &jsonValue);
};

#endif // QJSARRAYDATA_H
