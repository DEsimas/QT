#include <QDataStream>
#include <QDebug>
#include <QFile>

int main()
{
    QFile input("input.dat");
    if(input.open(QIODevice::ReadOnly))
    {
        QTextStream inputStream(&input);
        QString string = inputStream.readAll();
        QFile output("output.dat");
        output.open(QIODevice::WriteOnly);
        QTextStream outputStream(&output);
        outputStream << "---->" + string.toUpper() + "<----";
        input.close();
        output.close();
    }
    return 0;
}
