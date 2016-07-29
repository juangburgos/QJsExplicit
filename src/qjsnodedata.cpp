#include "qjsnodedata.h"

QJsNodeData::QJsNodeData()
{
    QJsNodeData(QJsonValue());
}

QJsNodeData::QJsNodeData(const QJsonValue &jsonValue)
{
    m_jsonValue = jsonValue;
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::parentNode()
{
    return m_parent;
}

void QJsNodeData::setParentNode(const QExplicitlySharedDataPointer<QJsNodeData> &newParent)
{
    m_parent = newParent;

    // TODO : recreate m_listChildren
}

QList<QExplicitlySharedDataPointer<QJsNodeData> > QJsNodeData::childNodes()
{
    return m_listChildren;
}

QExplicitlySharedDataPointer<QJsNodeData> QJsNodeData::appendChild(const QExplicitlySharedDataPointer<QJsNodeData> &newChild)
{
    // TODO : implement

    return QExplicitlySharedDataPointer<QJsNodeData>(nullptr);
}

bool QJsNodeData::isNull()
{
    if(m_jsonValue.type() == QJsonValue::Null)
    {
        return true;
    }
    return false;
}
