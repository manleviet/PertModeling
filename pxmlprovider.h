#ifndef PXMLPROVIDER_H
#define PXMLPROVIDER_H

#include <QDomDocument>

class PXMLProvider
{
public:
    PXMLProvider();
    PXMLProvider(QString file);
    QString getFileName(){return fileName;}
    void setFileName(const QString &file){fileName = file;}
    QDomDocument getDocument(){return docFile;}
    void setDocument(const QDomDocument &doc){docFile = doc;}

    bool parseFile();
    bool saveFile();

private:
    QString fileName;
    QDomDocument docFile;
};
#endif // PXMLPROVIDER_H
