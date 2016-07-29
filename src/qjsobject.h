#ifndef QJSOBJECT_H
#define QJSOBJECT_H

#include "qjsnode.h"

class QJsObject : public QJsNode
{
public:
    QJsObject();
    QJsObject(const QJsObject &);
    QJsObject &operator=(const QJsObject &);
    ~QJsObject();


};

#endif // QJSOBJECT_H
