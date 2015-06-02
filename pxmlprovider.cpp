#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "pxmlprovider.h"

PXMLProvider::PXMLProvider()
{
}

PXMLProvider::PXMLProvider(QString file)
{
    fileName = file;
}

bool PXMLProvider::saveFile()
{
    const int Indent = 4;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }
    QTextStream out(&file);
    this->docFile.save(out, Indent);
    return true;
}

bool PXMLProvider::parseFile()
{
    if (this->fileName.isEmpty()) return false;
    QFile file(fileName);

    // Load file XML vao QDomDocument
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!docFile.setContent(&file, true, &errorStr, &errorLine, &errorColumn)){
        QMessageBox::warning(0, QObject::tr("Read XML"),
                             QObject::tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr),
                             QMessageBox::Ok);
        return false;
    }
    return true;
}
