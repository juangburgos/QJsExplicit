#ifndef QJSDOCUMENT_H
#define QJSDOCUMENT_H

#include "qjsnode.h"

class QJsDocument : public QJsNode
{
public:
    QJsDocument();
    QJsDocument(const QJsDocument &);
    QJsDocument &operator=(const QJsDocument &);
    ~QJsDocument();

};

#endif // QJSDOCUMENT_H
