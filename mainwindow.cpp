#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QDir"
#include "QTextCursor"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	ftpConnection(this),
	settings("agartner.com","agartner.com editor", this)
{
	//qDebug()<<settings.fileName(); //cool stuff
	QCoreApplication::setOrganizationDomain("agartner.com");
	QCoreApplication::setApplicationName("agartner.com editor");

	ui->setupUi(this);
	ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->textEdit, &QTextEdit::customContextMenuRequested, this, &MainWindow::showContextMenu);


	credencialDialog = new CredencialDialog(this);
	connect(ui->actionCredentials,&QAction::triggered,this,&MainWindow::openCredencialWindow);
	connect(credencialDialog, &CredencialDialog::credencialsReady,this, &MainWindow::processCredencials);
	connect(credencialDialog, &CredencialDialog::credencialsConnectionReady,this, &MainWindow::processCredencials);
	connect(credencialDialog, &CredencialDialog::credencialsConnectionReady,[&](){
		ftpConnection.connectToHost(server);
		ftpConnection.login(username,password);
		ftpConnection.cd("/public_html/blog/posts");
		ftpConnection.list();
	});

	remoteFileList.clear();
	connect(&ftpConnection, &QFtp::listInfo,[&](QUrlInfo info){
		remoteFileList.append(info);
	});

	lsDialog = new LocalStorageDialog(settings.value("localstoragedir").toString(),this);
	connect(ui->actionLocal_Storage, &QAction::triggered, lsDialog, &LocalStorageDialog::exec);
	connect(lsDialog, &LocalStorageDialog::settingsChanged,[&](QString localDir){
		settings.setValue("localstoragedir",localDir);
		updateLocalCdList();
	});
	updateLocalCdList();

	localOpenDialog = new OpenDialog(&localFileStringList,this);
	remoteOpenDialog = new OpenDialog(&remoteFileStringList,this);
	connect(remoteOpenDialog, &OpenDialog::fileSelected,[&](int index){
		ftpConnection.get(remoteFileStringList.at(index));
	});
	connect(ui->actionOpen, &QAction::triggered, [&]{
		localFileStringList.clear();
		for (int i=0; i<localFileList.size();i++){
			localFileStringList.append(localFileList.at(i).baseName());
		}
		localOpenDialog->execAndUpdate();

	});
	connect(localOpenDialog, &OpenDialog::fileSelected,[&](int index){
		qDebug()<<index;
	});
	connect(ui->actionOpen_Remote,&QAction::triggered,[&]{
		remoteFileStringList.clear();
		for (int i=0; i<remoteFileList.size();i++){
			remoteFileStringList.append(remoteFileList.at(i).name());
		}
		remoteOpenDialog->execAndUpdate();
	});

	connect(localOpenDialog,&OpenDialog::fileSelected,[&](int index){
		bool postFound = false;
		for (int i = 0; i<localPosts.count();i++){
			if (index == localPosts[i]->getIndex()){
				postFound=true;
				displayPost(localPosts[i]);
				break;
			}
		}
		if (!postFound){
			localPosts.append(new BlogPost(localFileList.at(index),index));
			displayPost(localPosts.last());

		}
	});
	connect(remoteOpenDialog,&OpenDialog::fileSelected,[&](int index){
		bool postFound = false;
		for (int i = 0; i<remotePosts.count();i++){
			if (index == remotePosts[i]->getIndex()){
				postFound=true;
				displayPost(remotePosts[i]);
				break;
			}
		}
		if (!postFound){
			remotePosts.append(new BlogPost(remoteFileList.at(index),ftpConnection,index));
			//this code is bad, as it relys on the ftp connection to be slower than the signal connection. It works though.
			connect(remotePosts.last(),&BlogPost::ready, this, &MainWindow::displayPost);
		}
	});

}

MainWindow::~MainWindow()
{
	delete ui;
	delete credencialDialog;
	delete localOpenDialog;
	delete remoteOpenDialog;
	delete lsDialog;
}

void MainWindow::openCredencialWindow(){
	if (!settings.value("server").toString().isEmpty() || !settings.value("username").toString().isEmpty()){
		credencialDialog->execData(settings.value("server").toString(),settings.value("username").toString());
	}
	else{
		credencialDialog->exec();
	}
}


void MainWindow::showContextMenu(const QPoint &pt)
{
	QMenu *menu = ui->textEdit->createStandardContextMenu();
	QAction *action = new QAction("<p>...</p>",menu);
	connect(action,&QAction::triggered,this, &MainWindow::testFunction);
	if (ui->textEdit->textCursor().hasSelection()){
		menu->addAction(action);
	}
	menu->exec(ui->textEdit->mapToGlobal(pt));
	delete menu;
}

void MainWindow::testFunction(){
	QString selectedText=ui->textEdit->textCursor().selectedText();
	selectedText.prepend("<p>");
	selectedText.append("</p>");
	ui->textEdit->textCursor().insertText(selectedText);
}

void MainWindow::processCredencials(QString server, QString username, QString password, bool store){
	this->server = server;
	this->username = username;
	this->password = password;
	if (store){
		settings.setValue("server",server);
		settings.setValue("username",username);
	}
}

void MainWindow::updateLocalCdList(){
	QDir dir(settings.value("localstoragedir").toString());
	localFileList = dir.entryInfoList(QDir::Files);
}

void MainWindow::displayPost(BlogPost *post){
	ui->leDate->setText(post->getDate());
	ui->leTitle->setText(post->getTitle());
	ui->leAuthor->setText(post->getAuthor());
	ui->textEdit->clear();
	ui->textEdit->insertPlainText(post->getPost());
}
