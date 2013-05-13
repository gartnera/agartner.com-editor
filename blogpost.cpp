#include "blogpost.h"
#include <QDebug>

BlogPost::BlogPost(QFileInfo info, int index):
	file(),
	dateWritten()
{
	this->index = index;
	fileName = info.completeBaseName();
	absoluteFileName = info.absoluteFilePath();
	dateLastModified = info.lastModified();
	if (processFileName()){
		file.setFileName(absoluteFileName);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				 emit errorsProcessing();
		else{
			rawPost = QString(file.readAll());
			emit ready(this);
			file.close();
		}
	}
}

BlogPost::BlogPost(QUrlInfo info, QFtp &ftp, int index){
	this->index = index;
	this->ftp = &ftp;
	fileName = info.name();
	dateLastModified = info.lastModified();
	if (processFileName()){
		connect(this->ftp,&QFtp::commandFinished, this,&BlogPost::ftpCommandFinished);
		ftpOpId = ftp.get(fileName);
	}
}

bool BlogPost::processFileName(){
	splitFileName = fileName.split("~");
	if (splitFileName.count()>=3){
		QStringList dateparts = splitFileName.at(0).split("-");
		dateWritten.setDate(QDate(dateparts.at(2).toInt(),dateparts.at(0).toInt(),dateparts.at(1).toInt()));
		title = splitFileName.at(1);
		author= splitFileName.at(2);
		if (splitFileName.count()==4){
			tags = splitFileName.at(3).split("|");
		}
		return true;
	}
	else{
		emit errorsProcessing();
		return false;
	}
}

void BlogPost::ftpCommandFinished(int id, bool error){
	if (!error){
		if (id==ftpOpId){
			rawPost = QString(ftp->readAll());
			emit ready(this);
		}
	}
	else
		emit errorsProcessing();
}

int BlogPost::getIndex(){
	return index;
}
