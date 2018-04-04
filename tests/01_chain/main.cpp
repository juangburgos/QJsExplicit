#include <QCoreApplication>
#include <QDebug>
#include <QJsObject>
#include <QJsArray>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	QJsObject jsObjChild;
	QJsArray  jsArrChild;
	QJsObject jsObjParent;

	jsObjChild
		.setKeyName("object_child")
		.setAttribute("uno" , 1.1)
		.setAttribute("dos" , 2.2)
		.setAttribute("tres", 3.3);

	jsArrChild
		.setKeyName("array_child")
		.appendValue(1)
		.appendValue(2)
		.appendValue(3)
		.appendValue(4)
		.appendValue(5)
		.appendObject(jsObjChild); // NOTE : keyName hets changed to index

	jsObjParent
		.setAttribute("one"  , 1  )
		.setAttribute("two"  , 2  )
		.setAttribute("three", 3  )
		.setAttribute("four" , "4")
		.appendChild(jsObjChild)  // NOTE : appendChild return the appended child
		.setKeyName("object_child")
		.appendChild(jsArrChild);

	qDebug() << jsObjParent.toJson(QJsNode::Compact);

    return a.exec();
}
