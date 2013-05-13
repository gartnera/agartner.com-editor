#include "opendialog.h"
#include "ui_opendialog.h"
#include <algorithm>
#include <QDebug>

OpenDialog::OpenDialog(QStringList *fileList, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OpenDialog)
{
	list = fileList;
	ui->setupUi(this);

	connect(ui->pbOk,&QPushButton::clicked,this,&QDialog::hide);
	connect(ui->pbCancel,&QPushButton::clicked,this,&QDialog::hide);
	connect(ui->pbOk,&QPushButton::clicked,[&](){
		emit fileSelected(ui->listView->selectionModel()->selectedIndexes().at(0).row());
	});



}

OpenDialog::~OpenDialog()
{
	delete ui;
}

void OpenDialog::execAndUpdate(){
	if (ui->listView->model() != NULL){
		delete ui->listView->model();
	}
	ui->listView->setModel(new QStringListModel(*list,this));
	ui->pbOk->setEnabled(ui->listView->selectionModel()->hasSelection());

	connect(ui->listView->selectionModel(), &QItemSelectionModel::selectionChanged,[&]{
		ui->pbOk->setEnabled(ui->listView->selectionModel()->hasSelection());
	});
	this->exec();
}


