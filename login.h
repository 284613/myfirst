#pragma once

#include <QDialog>
#include "ui_login.h"
#include <QtWidgets/QApplication>

class login : public QDialog
{
	Q_OBJECT

public:
	login(QWidget *parent = nullptr);
	~login();
private slots:
	void on_loginclose_clicked();
private slots:
	void on_loginbtn_clicked();
private:
	Ui::loginClass ui;
};
