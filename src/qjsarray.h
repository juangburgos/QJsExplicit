#ifndef QJSARRAY_H
#define QJSARRAY_H

#include "qjsnode.h"

class QJsArray : public QJsNode
{
public:
    QJsArray();
    QJsArray(const QJsArray &);
    QJsArray &operator=(const QJsArray &);
    ~QJsArray();

};

#endif // QJSARRAY_H
