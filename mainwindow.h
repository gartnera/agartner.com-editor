#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "credencialdialog.h"
#include "localstoragedialog.h"
#include "blogpost.h"
#include "opendialog.h"
#include "qftp/qftp.h"
#include <QVector>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
public slots:
    void openCredencialWindow();
	
private:
	Ui::MainWindow *ui;
    CredencialDialog *credencialDialog;
    LocalStorageDialog *lsDialog;
	OpenDialog *localOpenDialog;
	OpenDialog *remoteOpenDialog;
	QFileInfoList localFileList;
	QStringList localFileStringList;
	QVector <QUrlInfo> remoteFileList;
	QStringList remoteFileStringList;

	QVector <BlogPost*> localPosts;
	QVector <BlogPost*> remotePosts;

    QFtp ftpConnection;

	void menuClicked(QAction *action);
	void showContextMenu(const QPoint &p);
	void testFunction();
    void processCredencials(QString, QString, QString, bool);
	void updateLocalCdList();
	void loadAndProcessFile(int index);
	void saveFile();
	void displayPost(BlogPost *post);

    QSettings settings;

    QString server;
    QString username;
    QString password;
};

#endif // MAINWINDOW_H
