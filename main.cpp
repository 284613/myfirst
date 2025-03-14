#include "myfirst.h"
#include <QtWidgets/QApplication>
#include "login.h"
#include <Qmessagebox.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myfirst w;
	login log;
    if (log.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
	else
	{
		return 0;
	}
}
