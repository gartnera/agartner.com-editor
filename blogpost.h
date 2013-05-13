#ifndef BLOGPOST_H
#define BLOGPOST_H

#include <QString>
#include <QFile>
#include <qftp/qurlinfo.h>
#include <qftp/qftp.h>
#include <QFileInfo>
#include <QDateTime>
#include <QStringList>
#include <QObject>

class BlogPost : public QObject
{
	Q_OBJECT

public:
	BlogPost(QFileInfo info, int index);
	BlogPost(QUrlInfo info, QFtp &ftp, int index);

	int getIndex();
	QString getDate(){return dateWritten.toString();}
	QString getTitle(){return title;}
	QString getAuthor(){return author;}
	QString getPost(){return rawPost;}

public slots:
	void ftpCommandFinished(int id, bool error);

signals:
	void errorsProcessing();
	void ready(BlogPost*);

private:
	QFile file;
	QFtp *ftp;

	//ftp or file specific
	int ftpOpId;
	QString absoluteFileName;

	//shared by all
	int index;
	QString fileName;
	QStringList splitFileName;
	QDateTime dateWritten;
	QDateTime dateLastModified;
	QString rawPost;
	QString title;
	QString author;
	QStringList tags;

	bool processFileName();
};

#endif // BLOGPOST_H
