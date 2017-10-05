#include "qjsnodedata.h"
#include "qjsobjectdata.h"
#include "qjsarraydata.h"
#include "qjsdocumentdata.h"

#include <QDebug>

QJsArrayData::QJsArrayData()
{
	m_strKeyName = "";
	m_jsonValue  = QJsonValue(QJsonArray());
	// null instance
	m_parent = nullptr;
}

QJsArrayData::~QJsArrayData()
{
	this->removeChildren();
}

bool QJsArrayData::isArray()
{
	return true;
}

bool QJsArrayData::isDocument()
{
	return false;
}

bool QJsArrayData::isObject()
{
	return false;
}

int QJsArrayData::count()
{
	return m_vectorChildren.count();
}

QVariant QJsArrayData::getValueAt(int idx)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		return QVariant();
	}
	return m_vectorChildren.at(idx)->m_jsonValue.toVariant();
}

QExplicitlySharedDataPointer<QJsNodeData> QJsArrayData::getNodeAt(int idx)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		return QExplicitlySharedDataPointer<QJsNodeData>(nullptr);
	}
	return m_vectorChildren[idx];
}

void QJsArrayData::setValueAt(int idx, bool boolValue)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::setValueAt(int idx, bool boolValue)";
		return;
	}
	m_vectorChildren[idx]->removeChildren();
	m_vectorChildren[idx]->m_jsonValue = QJsonValue(boolValue);
}

void QJsArrayData::setValueAt(int idx, int intValue)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::setValueAt(int idx, int intValue)";
		return;
	}
	m_vectorChildren[idx]->removeChildren();
	m_vectorChildren[idx]->m_jsonValue = QJsonValue(intValue);
}

void QJsArrayData::setValueAt(int idx, double doubleValue)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::setValueAt(int idx, double doubleValue)";
		return;
	}
	m_vectorChildren[idx]->removeChildren();
	m_vectorChildren[idx]->m_jsonValue = QJsonValue(doubleValue);
}

void QJsArrayData::setValueAt(int idx, QString strValue)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::setValueAt(int idx, QString strValue)";
		return;
	}
	m_vectorChildren[idx]->removeChildren();
	m_vectorChildren[idx]->m_jsonValue = QJsonValue(strValue);
}



void QJsArrayData::setValueAt(int idx, QVariant varValue)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::setValueAt(int idx, QVariant varValue)";
		return;
	}
	switch (varValue.type())
	{
	case QVariant::Bool:
		setValueAt(idx, varValue.toBool());
		break;
	case QVariant::Int:
		setValueAt(idx, varValue.toInt());
		break;
	case QVariant::Double:
		setValueAt(idx, varValue.toDouble());
		break;
	case QVariant::String:
		setValueAt(idx, varValue.toString());
		break;
	default:
		qDebug() << "[ERROR] unsupported type in QJsArrayData::setValueAt";
		break;
	}
}

void QJsArrayData::setNodeAt(int idx, QExplicitlySharedDataPointer<QJsNodeData> nodeValue)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::setNodeAt";
		return;
	}
	QString strIdx = QString::number(idx);
	replaceChild(strIdx, nodeValue);
}

void QJsArrayData::setObjectAt(int idx, QExplicitlySharedDataPointer<QJsObjectData> objValue)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::setObjectAt";
		return;
	}
	QString strIdx = QString::number(idx);
	replaceChild(strIdx, objValue);
}

void QJsArrayData::setArrayAt(int idx, QExplicitlySharedDataPointer<QJsArrayData> arrValue)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::setArrayAt";
		return;
	}
	QString strIdx = QString::number(idx);
	replaceChild(strIdx, arrValue);
}

bool QJsArrayData::isBool(int idx)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::isBool";
		return false;
	}
	return m_vectorChildren[idx]->m_jsonValue.isBool();
}

bool QJsArrayData::isInteger(int idx)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::isInteger";
		return false;
	}
	if (!m_vectorChildren[idx]->m_jsonValue.isDouble())
	{
		return false;
	}
	double value = m_vectorChildren[idx]->m_jsonValue.toDouble();
	double intpart;
	if (modf(value, &intpart) == 0.0)
	{
		return true;
	}
	return false;
}

bool QJsArrayData::isDouble(int idx)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::isDouble";
		return false;
	}
	return m_vectorChildren[idx]->m_jsonValue.isDouble();
}

bool QJsArrayData::isString(int idx)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::isString";
		return false;
	}
	return m_vectorChildren[idx]->m_jsonValue.isString();
}

bool QJsArrayData::isObject(int idx)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::isObject";
		return false;
	}
	return m_vectorChildren[idx]->m_jsonValue.isObject();
}

bool QJsArrayData::isArray(int idx)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::isArray";
		return false;
	}
	return m_vectorChildren[idx]->m_jsonValue.isArray();
}

void QJsArrayData::appendValue(bool boolValue)
{
	auto newNode          = QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData);
	newNode->m_jsonValue  = QJsonValue(boolValue);
	newNode->m_parent     = this;
	newNode->m_strKeyName = QString::number(m_vectorChildren.count());
	m_vectorChildren.append(newNode);
}

void QJsArrayData::appendValue(int intValue)
{
	auto newNode          = QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData);
	newNode->m_jsonValue  = QJsonValue(intValue);
	newNode->m_parent     = this;
	newNode->m_strKeyName = QString::number(m_vectorChildren.count());
	m_vectorChildren.append(newNode);
}

void QJsArrayData::appendValue(double doubleValue)
{
	auto newNode          = QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData);
	newNode->m_jsonValue  = QJsonValue(doubleValue);
	newNode->m_parent     = this;
	newNode->m_strKeyName = QString::number(m_vectorChildren.count());
	m_vectorChildren.append(newNode);
}

void QJsArrayData::appendValue(QString strValue)
{
	auto newNode          = QExplicitlySharedDataPointer<QJsNodeData>(new QJsNodeData);
	newNode->m_jsonValue  = QJsonValue(strValue);
	newNode->m_parent     = this;
	newNode->m_strKeyName = QString::number(m_vectorChildren.count());
	m_vectorChildren.append(newNode);
}

void QJsArrayData::appendValue(QVariant varValue)
{
	switch (varValue.type())
	{
	case QVariant::Bool:
		appendValue(varValue.toBool());
		break;
	case QVariant::Int:
		appendValue(varValue.toInt());
		break;
	case QVariant::Double:
		appendValue(varValue.toDouble());
		break;
	case QVariant::String:
		appendValue(varValue.toString());
		break;
	default:
		qDebug() << "[ERROR] unsupported type in QJsArrayData::appendValue";
		break;
	}
}

void QJsArrayData::appendObject(QExplicitlySharedDataPointer<QJsObjectData> objValue)
{
	// first clear any key the objetc might have
	objValue->m_strKeyName.clear();
	// append, performs reparenting as well
	appendChild(objValue);
}

void QJsArrayData::appendArray(QExplicitlySharedDataPointer<QJsArrayData> arrValue)
{
	// append, performs reparenting as well
	appendChild(arrValue);
}

QVariant QJsArrayData::removeValueAt(int idx)
{
	// check if within range
	if (idx >= m_vectorChildren.count())
	{
		qDebug() << "[ERROR] invalid index in QJsArrayData::removeValueAt";
		return false;
	}
	// get return value
	QVariant retVar = m_vectorChildren[idx]->m_jsonValue.toVariant();
	// remove
	QString strIdx = QString::number(idx);
	removeChild(strIdx);
	return retVar;
}

int QJsArrayData::removeValue(int intValue)
{
	for (int i = 0; i < m_vectorChildren.count(); i++)
	{
		if (!m_vectorChildren[i]->m_jsonValue.isDouble())
		{
			continue;
		}
		double value = m_vectorChildren[i]->m_jsonValue.toDouble();
		double dbl_intpart;
		int    int_intpart;
		if (modf(value, &dbl_intpart) == 0.0)
		{
			int_intpart = (int)dbl_intpart;
			if (int_intpart == intValue)
			{
				QString strIdx = QString::number(i);
				removeChild(strIdx);
				return int_intpart;
			}
		}
	}
	return -1;
}

QString QJsArrayData::removeValue(QString strValue)
{
	for (int i = 0; i < m_vectorChildren.count(); i++)
	{
		if (!m_vectorChildren[i]->m_jsonValue.isString())
		{
			continue;
		}
        QString value = m_vectorChildren[i]->m_jsonValue.toString();
		if (value.compare(strValue, Qt::CaseSensitive) == 0)
		{
			QString strIdx = QString::number(i);
			removeChild(strIdx);
			return value;
		}
	}
	return QString();
}

#if defined(QT_DEBUG) && defined(Q_OS_WIN) && defined(JS_DEBUG)
void QJsArrayData::recalcDebugVars()
{
	d_strCount = QString::number(this->count()).toStdString();
	// call base class method
	QJsNodeData::recalcDebugVars();
}
#endif