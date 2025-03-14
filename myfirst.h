#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_myfirst.h"
#include <QCloseEvent>
class myfirst : public QMainWindow
{
    Q_OBJECT

public:
    myfirst(QWidget *parent = nullptr);

    ~myfirst();
public :
    void newFile();   // 新建操作
    bool maybeSave(); // 判断是否需要保存
    bool save();      // 保存操作
    bool saveAs();    // 另存为操作
	bool saveFile(const QString& fileName); // 保存文件
    bool loadFile(const QString& fileName); // 加载文件
private slots:
	void on_closebtn_clicked();
private slots:
	void on_action_new_triggered();
	void on_actionsave_triggered();
	void on_actionsave_as_triggered();
	void on_action_open_triggered();
	void on_actionclose_triggered();
	void on_actionquit_triggered();
	void on_actionrevoke_triggered();
	void on_actioncopy_triggered();
	void on_actionpaste_triggered();
	void on_actioncu_triggered();

private:
    bool isUntitled;
    QString curFile;
private:
    Ui::myfirstClass ui;
protected:
	void closeEvent(QCloseEvent* event); // 关闭事件
};
