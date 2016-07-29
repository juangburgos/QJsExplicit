#include "qjsobject.h"
#include "qjsobjectdata.h"

QJsObject::QJsObject()
{
    data = QExplicitlySharedDataPointer<QJsObjectData>(new QJsObjectData());
}

QJsObject::QJsObject(const QJsObject &rhs)
{
    data = rhs.data;
}

QJsObject &QJsObject::operator=(const QJsObject &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QJsObject::~QJsObject()
{

}
