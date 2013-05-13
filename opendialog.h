#ifndef OPENDIALOG_H
#define OPENDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class OpenDialog;
}

class OpenDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit OpenDialog(QStringList *fileList, QWidget *parent = 0);
	~OpenDialog();

	void execAndUpdate();
signals:
	void fileSelected(int index);
private:
	Ui::OpenDialog *ui;
	QStringList *list;

};

#endif // OPENDIALOG_H
