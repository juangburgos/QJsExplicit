#include "qjsdocumentdata.h"

QJsDocumentData::QJsDocumentData()
{
	m_jsonValue = QJsonValue(QJsonObject()); // NODE, has to be an object, the QJsonDocument Object
}
