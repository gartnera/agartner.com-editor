#include "localstoragedialog.h"
#include "ui_localstoragedialog.h"
#include "QDir"

LocalStorageDialog::LocalStorageDialog(QString currentDirectory,QWidget *parent) :
    QDialog(parent),
	ui(new Ui::LocalStorageDialog),
	storageDirDialog(this)
{
    ui->setupUi(this);
	ui->leDirectory->setText(currentDirectory);
	storageDirDialog.setFileMode(QFileDialog::DirectoryOnly);
	connect(ui->pbDirectory, &QPushButton::clicked, [&]{
		QString path = ui->leDirectory->text();
		if (path == ""){
			path = QDir::homePath();
		}
		storageDirDialog.setDirectory(path);
		storageDirDialog.exec();
	});

	connect(&storageDirDialog, &QFileDialog::fileSelected, ui->leDirectory, &QLineEdit::setText);
	connect(ui->pbSave, &QPushButton::clicked, [&]{
		emit settingsChanged(ui->leDirectory->text());
	});

	connect(ui->pbSave, &QPushButton::clicked, this, &QDialog::hide);
	connect(ui->pbCancel, &QPushButton::clicked, this, &QDialog::hide);

}

LocalStorageDialog::~LocalStorageDialog()
{
    delete ui;
}
