#include "login.h"
#include <Qmessagebox.h>
login::login(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

login::~login()
{}
void login::on_loginclose_clicked()
{
	this->close();
}
void login::on_loginbtn_clicked()
{
	if (ui.inusrn->text().trimmed() == "admin" && ui.inpsw->text().trimmed() == "123")
	{
		this->accept();
	}
	else 
	{
		QMessageBox::warning(this, "Login", "Username or Password is incorrect",QMessageBox::Yes);
		// 清空内容并定位光标
		ui.inusrn->clear();
		ui.inpsw->clear();
		ui.usrn->setFocus();
	}
}