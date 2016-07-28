#ifndef QJSNODEDATA_H
#define QJSNODEDATA_H

#include <QSharedData>
#include <QJsonValue>

class QJsNodeData : public QSharedData
{
public:
    QJsNodeData(const QJsonValue &jsonValue);

    // isNull if m_jsonValue is NULL

protected:
    QJsonValue m_jsonValue;
};

#endif // QJSNODEDATA_H
