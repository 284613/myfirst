#include "myfirst.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QCloseEvent>
myfirst::myfirst(QWidget *parent)
    : QMainWindow(parent)
{
    
    ui.setupUi(this);
    isUntitled = true;
    curFile = tr("未命名.txt");
    setWindowTitle(curFile);
}

myfirst::~myfirst()
{}
void myfirst::on_closebtn_clicked()
{
	this->close();
}
void myfirst::newFile()
{
	if (maybeSave())
	{
		isUntitled = true;
		curFile = "未命名.txt";
		setWindowTitle(curFile);
		ui.textEdit->clear();
		ui.textEdit->setVisible(true);
	}
}
bool myfirst::maybeSave()
{
	if (ui.textEdit->document()->isModified())
	{
		QMessageBox box;
		box.setWindowTitle(tr("警告"));
		box.setIcon(QMessageBox::Warning);
		box.setText(curFile + "尚未保存，是否保存?");
		QPushButton* yesBtn = box.addButton("是(&Y)", QMessageBox::YesRole);
		box.addButton("否(&N)", QMessageBox::NoRole);
		QPushButton* cancelBut = box.addButton("取消", QMessageBox::RejectRole);
		box.exec();
		if (box.clickedButton() == yesBtn)
		{
			return save();
		}
		else if (box.clickedButton() == cancelBut)
		{
			return false;
		}
	}
	return true;
}
bool myfirst::save()
{
	if (isUntitled)
	{
		return saveAs();
	}
	else
	{
		return saveFile(curFile);
	}
}
bool myfirst::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, "另存为", curFile);
	if (fileName.isEmpty())
	{
		return false;
	}
	return saveFile(fileName);
}
bool myfirst::saveFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		// 使用 QString 格式化字符串
		QString errorMsg = QString("无法写入文件 %1:\n%2")
			.arg(file.fileName())    // 文件名
			.arg(file.errorString()); // 错误信息
		QMessageBox::warning(this, "多文档编辑器", errorMsg); // 正确传递参数
		return false;
	}
	QTextStream out(&file);
	out << ui.textEdit->toPlainText();
	isUntitled = false;
	curFile = QFileInfo(fileName).canonicalFilePath();
	setWindowTitle(curFile);
	return true;
}
void myfirst::on_action_new_triggered()
{
	newFile();
}
void myfirst::on_actionsave_triggered()
{
	save();
}
void myfirst::on_actionsave_as_triggered()
{
	saveAs();
}
bool myfirst:: loadFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))//只读方式打开文件
	{
		QMessageBox::warning(this, tr("多文档编辑器"),
			tr("无法读取文件 %1:\n%2.")
			.arg(fileName).arg(file.errorString()));
		return false; // 只读方式打开文件，出错则提示，并返回false
		
	}
	QTextStream in(&file);
	ui.textEdit->setPlainText(in.readAll());//读取文件内容，并显示到文本编辑器中
	QApplication::restoreOverrideCursor();//恢复鼠标指针状态
	curFile = QFileInfo(fileName).canonicalFilePath();//获取文件的标准路径
	setWindowTitle(curFile);//设置窗口标题，以文件名显示
	return true;
	
}
void myfirst::on_action_open_triggered()
{
	if (maybeSave())
	{
		QString fileName = QFileDialog::getOpenFileName(this);//获取文件名
		if (!fileName.isEmpty())//如果文件名不为空
		{
			loadFile(fileName);//加载文件
			ui.textEdit->setVisible(true);//显示文本编辑器	
		}
	}
}
void myfirst :: on_actionclose_triggered()
{
	if (maybeSave())
	{
		ui.textEdit->setVisible(false);//隐藏文本编辑器
	}
}
void myfirst ::on_actionquit_triggered()
{
	on_actionclose_triggered();
	qApp->quit();
}
void myfirst::on_actionrevoke_triggered()
{
	ui.textEdit->undo();
}
void myfirst::on_actioncopy_triggered()
{
	ui.textEdit->copy();
}
void myfirst::on_actionpaste_triggered()
{
	ui.textEdit->paste();
}

void myfirst::on_actioncu_triggered()
{
	ui.textEdit->cut();
}
void myfirst::closeEvent(QCloseEvent* event)
{
	if (maybeSave())
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}