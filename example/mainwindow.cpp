#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../src/qjsdocument.h"
#include "../src/qjsobject.h"
#include "../src/qjsarray.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	QJsDocument doc;

	// create test object
	QJsObject testobj = doc.createObject("testobj");
	testobj.setAttribute("attr1", "hola mundo");
	testobj.setAttribute("attr2", 3.1416);
	testobj.setAttribute("attr3", false);

	// create test array
	QJsArray testarr = doc.createArray("testarr");
	testarr.appendValue(2);
	testarr.appendValue(4);
	testarr.appendValue(6);
	testarr.appendValue(8);

	// create test array child object
	QJsObject arrchildobj = testarr.createObject("whatever");
	arrchildobj.setAttribute("xxx", true);
	arrchildobj.setAttribute("yyy", 8);
	arrchildobj.setAttribute("zzz", 7.8);

	// orphan object append to test
	QJsObject orphanobj;
	orphanobj.setKeyName("orphanobj"); // not working if no keyname, but that is desired
	orphanobj.setAttribute("A", 1);
	orphanobj.setAttribute("B", 2);
	orphanobj.setAttribute("C", 3);
	testobj.appendChild(orphanobj);

	// edit through copy of the document
	QJsDocument doc2 = orphanobj.ownerDocument();
	if (doc2.getChildByKey("testarr").isArray())
	{
		QJsArray testarr2 = doc2.getChildByKey("testarr").toArray(); //testarr.referended=3
		testarr2.setValueAt(3, "ocho");                              //testarr.referended=4
	}                                                                //testarr.referended=3

	// orphan array
	QJsArray orphanarr;
	//orphanarr.setKeyName("orphanarr"); works fine without keyname
	for (int i = 0; i < 3; i++)
	{
		QJsObject tempObj;
		tempObj.setAttribute("id", i);
		orphanarr.appendObject(tempObj);
	}
	testarr.appendArray(orphanarr);

	QString strJSON = doc.toJson(QJsNode::Indented);
	// print original
	ui->plainTextEdit->setPlainText(strJSON);
	// print copy
	QString strError;
	QJsDocument doccopy = QJsDocument::fromJson(strJSON.toUtf8(), strError);
	ui->plainTextEdit->appendPlainText("\n\n" + doccopy.toJson(QJsNode::Compact));
	// print copy in binary
	ui->plainTextEdit->appendPlainText("\n\n" + QString::fromStdString(doccopy.toBinaryData().toStdString()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
