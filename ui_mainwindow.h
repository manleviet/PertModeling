/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Dec 28 00:13:29 2009
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *pertView;
    QHBoxLayout *horizontalLayout;
    QToolButton *openButton;
    QFrame *line;
    QToolButton *repeatButton;
    QToolButton *previousButton;
    QToolButton *playButton;
    QToolButton *stopButton;
    QToolButton *nextButton;
    QFrame *line_2;
    QLabel *label;
    QSpinBox *timerSpinBox;
    QFrame *line_3;
    QLabel *stepLabel;
    QSpacerItem *horizontalSpacer;
    QSlider *scaleSlider;
    QTextEdit *outputText;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 650);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/icon/MoPert.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(10);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pertView = new QGraphicsView(layoutWidget);
        pertView->setObjectName(QString::fromUtf8("pertView"));
        pertView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);

        verticalLayout->addWidget(pertView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        openButton = new QToolButton(layoutWidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/icon/open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        openButton->setIcon(icon1);
        openButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(openButton);

        line = new QFrame(layoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        repeatButton = new QToolButton(layoutWidget);
        repeatButton->setObjectName(QString::fromUtf8("repeatButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/icon/repeat.ico"), QSize(), QIcon::Normal, QIcon::Off);
        repeatButton->setIcon(icon2);
        repeatButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(repeatButton);

        previousButton = new QToolButton(layoutWidget);
        previousButton->setObjectName(QString::fromUtf8("previousButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/icon/rewind.ico"), QSize(), QIcon::Normal, QIcon::Off);
        previousButton->setIcon(icon3);
        previousButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(previousButton);

        playButton = new QToolButton(layoutWidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/icon/play.ico"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon4);
        playButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(playButton);

        stopButton = new QToolButton(layoutWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/icon/stop.ico"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon5);
        stopButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(stopButton);

        nextButton = new QToolButton(layoutWidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix1/icon/forward.ico"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon6);
        nextButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(nextButton);

        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        timerSpinBox = new QSpinBox(layoutWidget);
        timerSpinBox->setObjectName(QString::fromUtf8("timerSpinBox"));
        timerSpinBox->setMaximum(10);
        timerSpinBox->setValue(2);

        horizontalLayout->addWidget(timerSpinBox);

        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        stepLabel = new QLabel(layoutWidget);
        stepLabel->setObjectName(QString::fromUtf8("stepLabel"));

        horizontalLayout->addWidget(stepLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        scaleSlider = new QSlider(layoutWidget);
        scaleSlider->setObjectName(QString::fromUtf8("scaleSlider"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scaleSlider->sizePolicy().hasHeightForWidth());
        scaleSlider->setSizePolicy(sizePolicy);
        scaleSlider->setMinimumSize(QSize(150, 0));
        scaleSlider->setMaximum(200);
        scaleSlider->setSingleStep(10);
        scaleSlider->setValue(110);
        scaleSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(scaleSlider);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(layoutWidget);
        outputText = new QTextEdit(splitter);
        outputText->setObjectName(QString::fromUtf8("outputText"));
        outputText->setEnabled(true);
        outputText->setAcceptDrops(false);
        outputText->setUndoRedoEnabled(false);
        outputText->setReadOnly(true);
        outputText->setTextInteractionFlags(Qt::NoTextInteraction);
        splitter->addWidget(outputText);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(openButton, SIGNAL(clicked()), MainWindow, SLOT(openButtonClicked()));
        QObject::connect(scaleSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(sceneScaleChanged(int)));
        QObject::connect(playButton, SIGNAL(clicked()), MainWindow, SLOT(playButtonClicked()));
        QObject::connect(stopButton, SIGNAL(clicked()), MainWindow, SLOT(stopButtonClicked()));
        QObject::connect(repeatButton, SIGNAL(clicked()), MainWindow, SLOT(repeatButtonClicked()));
        QObject::connect(previousButton, SIGNAL(clicked()), MainWindow, SLOT(previousButtonClicked()));
        QObject::connect(nextButton, SIGNAL(clicked()), MainWindow, SLOT(nextButtonClicked()));
        QObject::connect(timerSpinBox, SIGNAL(valueChanged(int)), MainWindow, SLOT(timerChange(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Pert Algorithme Modeling", 0, QApplication::UnicodeUTF8));
        openButton->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        repeatButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        previousButton->setText(QApplication::translate("MainWindow", "previous", 0, QApplication::UnicodeUTF8));
        playButton->setText(QApplication::translate("MainWindow", "play", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
        nextButton->setText(QApplication::translate("MainWindow", "next", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Timer :", 0, QApplication::UnicodeUTF8));
        stepLabel->setText(QApplication::translate("MainWindow", "Step 1", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
