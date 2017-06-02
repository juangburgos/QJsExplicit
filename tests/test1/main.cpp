#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QTimer>

#include <qjsdocument.h>
#include <qjsobject.h>
#include <qjsarray.h>

void createLevel1(QJsDocument &jsonDataBase)
{
    // level 1, object a
    QJsObject   m_jsObj1a;
    m_jsObj1a.setKeyName("1a");
    m_jsObj1a.setAttribute("name"   , "puto");
    m_jsObj1a.setAttribute("surname", "el que lo lea");
    m_jsObj1a.setAttribute("age"    , 10);
    jsonDataBase.appendChild(m_jsObj1a);

    // level 1, object b
    QJsObject   m_jsObj1b;
    m_jsObj1b.setKeyName("1b");
    m_jsObj1b.setAttribute("name"   , "fuck");
    m_jsObj1b.setAttribute("surname", "yeah mothafucka");
    m_jsObj1b.setAttribute("age"    , 20);
    jsonDataBase.appendChild(m_jsObj1b);
}

void createLevel2(QJsDocument &jsonDataBase)
{
    // level 2, append to 1a
    QJsObject   jsObj1a = jsonDataBase.getChildByKey("1a").toObject();
    // level 2, object a
    QJsObject   m_jsObj2a;
    m_jsObj2a.setKeyName("2a");
    m_jsObj2a.setAttribute("title"  , "puto");
    m_jsObj2a.setAttribute("pages"   , 100);
    jsObj1a.appendChild(m_jsObj2a);
    // level 2, object b
    QJsObject   m_jsObj2b;
    m_jsObj2b.setKeyName("2b");
    m_jsObj2b.setAttribute("title"  , "pendejo");
    m_jsObj2b.setAttribute("pages"   , 200);
    jsObj1a.appendChild(m_jsObj2b);

    // level 2, append to 1b
    QJsObject   jsObj1b = jsonDataBase.getChildByKey("1b").toObject();
    // level 2, object c
    QJsObject   m_jsObj2c;
    m_jsObj2c.setKeyName("2c");
    m_jsObj2c.setAttribute("title"  , "puto");
    m_jsObj2c.setAttribute("pages"   , 100);
    jsObj1b.appendChild(m_jsObj2c);
    // level 2, object d
    QJsObject   m_jsObj2d;
    m_jsObj2d.setKeyName("2d");
    m_jsObj2d.setAttribute("title"  , "pendejo");
    m_jsObj2d.setAttribute("pages"   , 200);
    jsObj1b.appendChild(m_jsObj2d);
}

void createLevel3(QJsDocument &jsonDataBase)
{
    // level 3
    QJsObject   jsObj1a = jsonDataBase.getChildByKey("1a").toObject();
    QJsObject   jsObj1b = jsonDataBase.getChildByKey("1b").toObject();

    QList<QJsObject> jsObjList;
    jsObjList.append(jsObj1a.getChildByKey("2a").toObject());
    jsObjList.append(jsObj1a.getChildByKey("2b").toObject());
    jsObjList.append(jsObj1b.getChildByKey("2c").toObject());
    jsObjList.append(jsObj1b.getChildByKey("2d").toObject());

    QJsObject jsTemplateObj;
    jsTemplateObj.setKeyName("model");
    jsTemplateObj.setAttribute("value"  , false);
    jsTemplateObj.setAttribute("quality", "good");

    for(int i = 0; i < jsObjList.count(); i++)
    {
        QJsObject jsTemplateObjClone = jsTemplateObj.clone().toObject();
        jsTemplateObjClone.setAttribute("timestamp", i);
        jsObjList[i].appendChild(jsTemplateObjClone);
    }

}

void updateTimestamps(QJsDocument &jsonDataBase)
{
	QJsObject   jsObj1a = jsonDataBase.getChildByKey("1a").toObject();
	QJsObject   jsObj1b = jsonDataBase.getChildByKey("1b").toObject();

	QList<QJsObject> jsObjList;
	jsObjList.append(jsObj1a.getChildByKey("2a").toObject());
	jsObjList.append(jsObj1a.getChildByKey("2b").toObject());
	jsObjList.append(jsObj1b.getChildByKey("2c").toObject());
	jsObjList.append(jsObj1b.getChildByKey("2d").toObject());

	// TODO : use methods in question
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer      fuckingTimer;
    QJsDocument m_jsonDataBase;
    // level 1
    createLevel1(m_jsonDataBase);
    // level 2
    createLevel2(m_jsonDataBase);
    // level 3
    createLevel3(m_jsonDataBase);



    QObject::connect(&fuckingTimer, &QTimer::timeout, [&]() {
        static int i = 0;
        i++;
        QString strDebugBefore = m_jsonDataBase.toJson(QJsNode::Compact);

		updateTimestamps(m_jsonDataBase);

        QString strDebugAfter  = m_jsonDataBase.toJson(QJsNode::Compact);
        qDebug() << i;
    });

    fuckingTimer.start(100);

    return a.exec();
}
