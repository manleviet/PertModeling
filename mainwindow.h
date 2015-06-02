#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QToolButton>

#include "diagramscene.h"
#include "pertgraph.h"
#include "script.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Mode {Play, Stop};

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDirPath(QString newPath) {curPath = newPath;}

public slots:
    void openButtonClicked();
    void repeatButtonClicked();
    void previousButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void nextButtonClicked();
    void timerChange(int change);
    void sceneScaleChanged(int scale);
    void modeling();

private:
    void drawPert();
    void drawOutputText();
    void drawStepLabel();
    void creatScript();

    Ui::MainWindow *ui;
    DiagramScene *scene;
    QString curPath;

    PertGraph *pert;
    QTimer *timer;
    Mode nowMode;
    Script *script;
};

#endif // MAINWINDOW_H
