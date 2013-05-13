#ifndef CREDENCIALDIALOG_H
#define CREDENCIALDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class CredencialDialog;
}

class CredencialDialog : public QDialog
{
    Q_OBJECT
    
public:
	explicit CredencialDialog(QWidget *parent = 0);
    ~CredencialDialog();
    void execData(QString server, QString username);
signals:
    void credencialsReady(QString server, QString username, QString password, bool save);
    void credencialsConnectionReady(QString server, QString username, QString password, bool save);
    
private:
    Ui::CredencialDialog *ui;
};

#endif // CREDENCIALDIALOG_H
