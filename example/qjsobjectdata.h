#ifndef QJSOBJECTDATA_H
#define QJSOBJECTDATA_H

#include "qjsnodedata.h"

class QJsObjectData : public QJsNodeData
{
public:
    QJsObjectData(const QJsonValue &jsonValue);

};


#endif // QJSOBJECTDATA_H
