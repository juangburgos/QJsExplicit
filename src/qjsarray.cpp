#include "qjsarray.h"
#include "qjsarraydata.h"

QJsArray::QJsArray()
{
    data = QExplicitlySharedDataPointer<QJsArrayData>(new QJsArrayData(QJsonValue()));
}

QJsArray::QJsArray(const QJsArray &rhs)
{
    data = rhs.data;
}

QJsArray &QJsArray::operator=(const QJsArray &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QJsArray::~QJsArray()
{

}
