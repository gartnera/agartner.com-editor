#ifndef LOCALSTORAGEDIALOG_H
#define LOCALSTORAGEDIALOG_H

#include <QDialog>
#include "QFileDialog"


namespace Ui {
class LocalStorageDialog;
}

class LocalStorageDialog : public QDialog
{
    Q_OBJECT
    
public:
	explicit LocalStorageDialog(QString currentDirectory,QWidget *parent = 0);
    ~LocalStorageDialog();
signals:
	void settingsChanged(QString storageDir);
    

private:
    Ui::LocalStorageDialog *ui;
	QFileDialog storageDirDialog;
};

#endif // LOCALSTORAGEDIALOG_H
