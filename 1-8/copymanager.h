#ifndef COPYMANAGER_H
#define COPYMANAGER_H

#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QByteArray>

class CopyManager
{
private:
    QApplication *a;
    void showMessage(QString);
public:
    CopyManager(QApplication*);
    void copy(QString, QString);
};

#endif // COPYMANAGER_H
