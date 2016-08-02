#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

QJsArrayData::QJsArrayData()
{
	m_jsonValue = QJsonValue(QJsonArray());
	// null instance
	m_parent = nullptr;
}

bool QJsArrayData::isArray()
{
	return true;
}

void QJsArrayData::appendObject(QExplicitlySharedDataPointer<QJsObjectData> objValue)
{

}
