#include "copymanager.h"

#include <QByteArray>

void CopyManager::showMessage(QString message)
{
    QMessageBox messageBox;
    messageBox.setText(message);
    messageBox.exec();
    a->exit();
}

CopyManager::CopyManager(QApplication *a)
{
    this->a = a;
}

void CopyManager::copy(QString inputFileName, QString outputFileName)
{
    QFile inputFile(inputFileName);
    if(!inputFile.open(QFile::ReadOnly))
        return showMessage("Failed to open input file \"" + inputFileName + "\"");
    QFile outputFile(outputFileName);
    if(!outputFile.open(QFile::ReadOnly))
        return showMessage("Failed to open output file \"" + outputFileName + "\"");
    outputFile.close();
    if(!outputFile.open(QFile::WriteOnly))
        return showMessage("Failed to open output file \"" + outputFileName + "\"");
    QByteArray buffer = inputFile.readAll();
    outputFile.write(buffer);
    inputFile.close();
    outputFile.close();
    showMessage("Content from \"" + inputFileName + "\" copied to \"" + outputFileName + "\"");
}
