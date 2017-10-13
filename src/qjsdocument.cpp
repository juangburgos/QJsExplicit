#include "qjsnode.h"
#include "qjsobject.h"
#include "qjsarray.h"
#include "qjsdocument.h"

#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

QJsDocument::QJsDocument()
{
    data = QExplicitlySharedDataPointer<QJsDocumentData>(new QJsDocumentData());
}

QJsDocument::QJsDocument(const QJsDocument &rhs)
{
	data.reset();
    data = rhs.data;
}

QJsDocument &QJsDocument::operator=(const QJsDocument &rhs)
{
	if (this != &rhs) {
		data.reset();
		data.operator=(rhs.data);
	}
	return *this;
}

QJsDocument::~QJsDocument()
{
	data.reset();
}

QJsDocument QJsDocument::fromJson(const QByteArray &json, QString &error)
{
	QJsDocument doc;
	error = doc.data->toDocument()->fromJson(json);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	doc.data->recalcDebugVars();
#endif
	return doc;
}

QJsDocument QJsDocument::fromBinaryData(const QByteArray &bindata, QString &error)
{
	QJsDocument doc;
	error = doc.data->toDocument()->fromBinaryData(bindata);
#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
	doc.data->recalcDebugVars();
#endif
	return doc;
}

QJsDocument QJsDocument::clone() const
{
	return QJsNode::clone().toDocument();
}
