#include "qjsdocument.h"
#include "qjsdocumentdata.h"

QJsDocument::QJsDocument()
{
    data = QExplicitlySharedDataPointer<QJsDocumentData>(new QJsDocumentData(QJsonValue()));
}

QJsDocument::QJsDocument(const QJsDocument &rhs)
{
    data = rhs.data;
}

QJsDocument &QJsDocument::operator=(const QJsDocument &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QJsDocument::~QJsDocument()
{

}
