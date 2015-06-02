#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QDir>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "diagramscene.h"
#include "graphprovider.h"
#include "pcalculate.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    scene = new DiagramScene();
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));

    ui->setupUi(this);
    ui->pertView->setScene(scene);

    QList<int> list;
    list << this->height() /5 *4 << this->height() /5;
    ui->splitter->setSizes(list);

    ui->stepLabel->setText("Etape 0 dans 0 etapes.");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(modeling()));
    timer->start(2000);
    nowMode = Stop;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openButtonClicked()
{
    if (nowMode == Play) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("Cannot open one file when the modeling is executing."),
                             QMessageBox::Ok);
        return;
    }
    QDir dir(this->curPath);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Graph"),
                                                    dir.currentPath(),
                                                    tr("Graph xml (*.xml)"));
    if (!fileName.isEmpty()){
        pert = new PertGraph();
        GraphProvider *read = new GraphProvider();
        script = new Script();

        if (!read->readGraph(pert, script, fileName)){
            QMessageBox::warning(this, tr("Warning"),
                                 tr("Cannot reading file."),
                                 QMessageBox::Ok);
        }
        else{
            this->drawPert();
            PCalculate cal;
            cal.setDataFile(fileName);
            QString resultpath = dir.currentPath() + "/resultStep.xml";
            QString resultfilepath = dir.currentPath() + "/result.xml";
            cal.setResultFileStep(resultpath);
            cal.setResultFile(resultfilepath);
            if (!cal.calculate()){
                QMessageBox::warning(this, tr("Warning"),
                                     tr("Cannot calculate for this graph."),
                                     QMessageBox::Ok);
            }
            else{
                if (!read->readResultStep(pert, resultpath)){
                    QMessageBox::warning(this, tr("Warning"),
                                         tr("Cannot calculate for this graph."),
                                         QMessageBox::Ok);
                }
                if (!read->readResult(pert, resultfilepath)){
                    QMessageBox::warning(this, tr("Warning"),
                                         tr("Cannot calculate for this graph."),
                                         QMessageBox::Ok);
                }
                this->creatScript();
                script->firstStep();
                ui->stepLabel->setText("Etape " + QObject::tr("%1").arg(script->indexStep()) + " dans " +
                                       QObject::tr("%1").arg(script->totalStep()-1) + " etapes.");
            }
        }
    }
}

void MainWindow::repeatButtonClicked()
{
    script->firstStep();
    pert->setScriptStep(script->currentStep());
    this->drawPert();
    this->drawOutputText();
    this->drawStepLabel();
}

void MainWindow::previousButtonClicked()
{
    if (script->indexStep() == 0) return;
    script->previousStep();
    pert->setScriptStep(script->currentStep());
    this->drawPert();
    this->drawOutputText();
    this->drawStepLabel();
}

void MainWindow::playButtonClicked()
{
    if (nowMode == Stop)
    {
        nowMode = Play;
        script->firstStep();
    }
}

void MainWindow::stopButtonClicked()
{
    nowMode = Stop;
}

void MainWindow::nextButtonClicked()
{
    if (script->indexStep() == (script->totalStep() -1)){
        nowMode = Stop;
        return;
    }
    script->nextStep();
    pert->setScriptStep(script->currentStep());
    this->drawPert();
    this->drawOutputText();
    this->drawStepLabel();
}

void MainWindow::timerChange(int change)
{
    timer->start(change * 1000);
}

void MainWindow::sceneScaleChanged(int scale)
{
    double newScale = scale / 100.0;
    QMatrix oldMatrix = ui->pertView->matrix();
    ui->pertView->resetMatrix();
    ui->pertView->translate(oldMatrix.dx(), oldMatrix.dy());
    ui->pertView->scale(newScale, newScale);
}

void MainWindow::modeling()
{
    if (nowMode == Stop) return;
    if (script->indexStep() <= script->totalStep())
        this->nextButtonClicked();
}

void MainWindow::drawPert()
{
    scene->clear();
    for (int i = 0; i < pert->lengthNodeList(); i++)
        scene->setNode(pert->node(i));
    for (int i = 0; i < pert->lengthTaskList(); i++)
        scene->setTask(pert->task(i));
    scene->update(scene->sceneRect());
}

void MainWindow::drawOutputText()
{
    ui->outputText->setText(script->outputText());
    ui->outputText->moveCursor(QTextCursor::End);
}

void MainWindow::drawStepLabel()
{
    QString temp;
    temp = "Etape " + QObject::tr("%1").arg(script->indexStep()) + " dans " +
           QObject::tr("%1").arg(script->totalStep() - 1) + " etapes.";
    ui->stepLabel->setText(temp);
}

void MainWindow::creatScript()
{
    for (int i = 0; i < pert->totalStep(); i++)
    {
        pert->nextStep();
        ScriptStep *step = new ScriptStep();
        for (int i = 0; i < pert->lengthNodeList(); i++)
            step->setInfoNode(pert->node(i)->state(), pert->node(i)->earlyDate(), pert->node(i)->lateDate());
        for (int i = 0; i < pert->lengthTaskList(); i++)
            step->setInfoTask(pert->task(i)->state());
        step->setOutputText(pert->outputText());
        script->setStep(step);
    }
}
