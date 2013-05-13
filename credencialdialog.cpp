#include "credencialdialog.h"
#include "ui_credencialdialog.h"
#include "QDebug"

CredencialDialog::CredencialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CredencialDialog)
{
    ui->setupUi(this);

    connect(ui->pbSave,&QPushButton::clicked,[&]{
        emit credencialsReady(ui->leServer->text(),ui->leUsername->text(),ui->lePassword->text(),ui->checkBox->isChecked());
    });
    connect(ui->pbSaveConnect,&QPushButton::clicked,[&]{
        emit credencialsConnectionReady(ui->leServer->text(),ui->leUsername->text(),ui->lePassword->text(),ui->checkBox->isChecked());
    });
	connect(ui->pbCancel,&QPushButton::clicked,this, &QDialog::hide);
	connect(ui->pbSaveConnect,&QPushButton::clicked,this, &QDialog::hide);
	connect(ui->pbSave,&QPushButton::clicked,this, &QDialog::hide);


}

CredencialDialog::~CredencialDialog()
{
    delete ui;
}

void CredencialDialog::execData(QString server, QString username){
    ui->leServer->setText(server);
    ui->leUsername->setText(username);
    this->exec();
}

