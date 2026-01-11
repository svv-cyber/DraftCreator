// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mainwindow.h"
#include "scribblearea.h"
#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QImageWriter>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFrame>
#include <QPushButton>
#include <QMenu>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scribbleArea(new ScribbleArea(this))
{
    // Устанавливаем заголовок главного окна
    setWindowTitle(tr("Draft Creator"));

    // Центральный виджет
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *outerLayout = new QVBoxLayout(centralWidget);

    QFrame *mainFrame = new QFrame();
    mainFrame->setFrameShape(QFrame::Box);
    mainFrame->setFrameShadow(QFrame::Plain);
    mainFrame->setStyleSheet(
        "QFrame { "
        "    border: 2px solid #999; "
        "    border-radius: 0px; "
        "    background-color: #f5f5f5; "
        "}"
    );

    QHBoxLayout *mainLayout = new QHBoxLayout(mainFrame);

    // Область рисования (белая)
    scribbleArea->setStyleSheet(
        "ScribbleArea { "
        "    border: 1px solid #bbb; "
        "    border-radius: 0px; "
        "    background-color: white; "
        "}"
    );
    mainLayout->addWidget(scribbleArea, 5);

    QFrame *rightFrame = new QFrame();
    rightFrame->setFrameShape(QFrame::Box);
    rightFrame->setFrameShadow(QFrame::Plain);
    rightFrame->setStyleSheet(
        "QFrame { "
        "    border: 1px solid #bbb; "
        "    border-radius: 0px; "
        "    background-color: #f0f0f0; "
        "}"
    );

    QVBoxLayout *rightPanelLayout = new QVBoxLayout(rightFrame);

    rightPanelLayout->addSpacing(10);

    QLabel *colorLabel = new QLabel(tr("Цвет"));
    colorLabel->setStyleSheet(
        "QLabel { "
        "    font-weight: bold; "
        "    font-size: 14px; "
        "    padding: 5px; "
        "    padding-left: 10px; "
        "}"
    );
    rightPanelLayout->addWidget(colorLabel);

    QWidget *colorWidget = new QWidget();
    colorWidget->setStyleSheet(
        "QWidget { "
        "    background-color: white; "
        "    border: 1px solid #ccc; "
        "    border-radius: 3px; "
        "    margin: 0px 10px 10px 10px; "
        "}"
    );

    QHBoxLayout *colorInnerLayout = new QHBoxLayout(colorWidget);
    colorInnerLayout->setContentsMargins(10, 5, 10, 5);

    // Кнопка выбора цвета
    QPushButton *colorButton = new QPushButton(tr("Выбрать цвет"));
    colorButton->setStyleSheet(
        "QPushButton { "
        "    border: 1px solid #aaa; "
        "    background-color: #f0f0f0; "
        "    padding: 5px 10px; "
        "    font-size: 13px; "
        "}"
        "QPushButton:hover { "
        "    background-color: #e0e0e0; "
        "}"
    );

    QLabel *colorPreview = new QLabel();
    colorPreview->setFixedSize(30, 20);
    colorPreview->setStyleSheet(
        QString("QLabel { "
                "    background-color: %1; "
                "    border: 1px solid #888; "
                "    border-radius: 2px; "
                "}").arg(scribbleArea->penColor().name())
    );

    colorInnerLayout->addWidget(colorButton);
    colorInnerLayout->addSpacing(10);
    colorInnerLayout->addWidget(colorPreview);
    colorInnerLayout->addStretch();

    rightPanelLayout->addWidget(colorWidget);
    rightPanelLayout->addSpacing(20);

    QLabel *thicknessLabel = new QLabel(tr("Толщина"));
    thicknessLabel->setStyleSheet(
        "QLabel { "
        "    font-weight: bold; "
        "    font-size: 14px; "
        "    padding: 5px; "
        "    padding-left: 10px; "
        "}"
    );
    rightPanelLayout->addWidget(thicknessLabel);

    QWidget *thicknessWidget = new QWidget();
    thicknessWidget->setStyleSheet(
        "QWidget { "
        "    background-color: white; "
        "    border: 1px solid #ccc; "
        "    border-radius: 3px; "
        "    margin: 0px 10px 10px 10px; "
        "}"
    );

    QHBoxLayout *thicknessInnerLayout = new QHBoxLayout(thicknessWidget);
    thicknessInnerLayout->setContentsMargins(10, 5, 10, 5);

    penWidthSpinBox = new QSpinBox();
    penWidthSpinBox->setRange(1, 20);
    penWidthSpinBox->setValue(1);
    penWidthSpinBox->setSuffix(" px");
    penWidthSpinBox->setButtonSymbols(QSpinBox::PlusMinus);
    penWidthSpinBox->setStyleSheet(
        "QSpinBox { "
        "    border: none; "
        "    background-color: transparent; "
        "    font-size: 13px; "
        "    min-width: 60px; "
        "}"
        "QSpinBox::up-button, QSpinBox::down-button { "
        "    width: 15px; "
        "    border: 1px solid #aaa; "
        "    background-color: #f0f0f0; "
        "}"
    );
    thicknessInnerLayout->addWidget(penWidthSpinBox);
    thicknessInnerLayout->addStretch();

    rightPanelLayout->addWidget(thicknessWidget);

    rightPanelLayout->addSpacing(20);

    QLabel *lineTypeLabel = new QLabel(tr("Тип линии"));
    lineTypeLabel->setStyleSheet(
        "QLabel { "
        "    font-weight: bold; "
        "    font-size: 14px; "
        "    padding: 5px; "
        "    padding-left: 10px; "
        "}"
    );
    rightPanelLayout->addWidget(lineTypeLabel);

    QWidget *lineTypeWidget = new QWidget();
    lineTypeWidget->setStyleSheet(
        "QWidget { "
        "    background-color: white; "
        "    border: 1px solid #ccc; "
        "    border-radius: 3px; "
        "    margin: 0px 10px 10px 10px; "
        "}"
    );

    QHBoxLayout *lineTypeInnerLayout = new QHBoxLayout(lineTypeWidget);
    lineTypeInnerLayout->setContentsMargins(10, 5, 10, 5);

    penStyleComboBox = new QComboBox();
    penStyleComboBox->addItem(tr("Сплошная"), static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("Пунктир"), static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("Точечная"), static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("Штрихпунктир"), static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->setStyleSheet(
        "QComboBox { "
        "    border: none; "
        "    background-color: transparent; "
        "    font-size: 13px; "
        "    min-width: 120px; "
        "}"
        "QComboBox::drop-down { "
        "    border: 1px solid #aaa; "
        "    background-color: #f0f0f0; "
        "    width: 20px; "
        "}"
    );
    lineTypeInnerLayout->addWidget(penStyleComboBox);
    lineTypeInnerLayout->addStretch();

    rightPanelLayout->addWidget(lineTypeWidget);

    rightPanelLayout->addSpacing(25);

    QPushButton *openButton = new QPushButton(tr("Открыть"));
    QPushButton *saveButton = new QPushButton(tr("Сохранить"));
    QPushButton *clearButton = new QPushButton(tr("Очистить"));
    QPushButton *exitButton = new QPushButton(tr("Выход"));

    QString mainButtonStyle =
        "QPushButton { "
        "    padding: 10px 25px; "
        "    border: 1px solid #888; "
        "    background-color: #e0e0e0; "
        "    border-radius: 0px; "
        "    font-weight: bold; "
        "    font-size: 14px; "
        "}"
        "QPushButton:hover { "
        "    background-color: #d0d0d0; "
        "}";

    openButton->setStyleSheet(mainButtonStyle);
    saveButton->setStyleSheet(mainButtonStyle);
    clearButton->setStyleSheet(mainButtonStyle);
    exitButton->setStyleSheet(mainButtonStyle);

    QHBoxLayout *topButtonsLayout = new QHBoxLayout;
    topButtonsLayout->addStretch();
    topButtonsLayout->addWidget(openButton);
    topButtonsLayout->addWidget(saveButton);
    topButtonsLayout->addStretch();

    QHBoxLayout *bottomButtonsLayout = new QHBoxLayout;
    bottomButtonsLayout->addStretch();
    bottomButtonsLayout->addWidget(clearButton);
    bottomButtonsLayout->addWidget(exitButton);
    bottomButtonsLayout->addStretch();

    rightPanelLayout->addLayout(topButtonsLayout);
    rightPanelLayout->addSpacing(10);
    rightPanelLayout->addLayout(bottomButtonsLayout);
    rightPanelLayout->addStretch();

    mainLayout->addWidget(rightFrame, 2);

    outerLayout->addWidget(mainFrame);

    setCentralWidget(centralWidget);

    createActions();
    createMenus();
    menuBar()->setVisible(false);

    connect(penStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index) {
                Qt::PenStyle style = static_cast<Qt::PenStyle>(
                    penStyleComboBox->itemData(index).toInt()
                );
                scribbleArea->setPenStyle(style);
            });

    connect(penWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            scribbleArea, &ScribbleArea::setPenWidth);

    connect(colorButton, &QPushButton::clicked, this, [this, colorPreview]() {
        QColor newColor = QColorDialog::getColor(scribbleArea->penColor(), this, "Выберите цвет линии");
        if (newColor.isValid()) {
            scribbleArea->setPenColor(newColor);
            // Обновляем превью цвета
            colorPreview->setStyleSheet(
                QString("QLabel { "
                        "    background-color: %1; "
                        "    border: 1px solid #888; "
                        "    border-radius: 2px; "
                        "}").arg(newColor.name())
            );
        }
    });

    connect(openButton, &QPushButton::clicked, openAct, &QAction::trigger);
    connect(saveButton, &QPushButton::clicked, this, [this]() {
        if (!saveAsActs.isEmpty()) {
            saveAsActs.first()->trigger();
        }
    });
    connect(clearButton, &QPushButton::clicked,
            scribbleArea, &ScribbleArea::clearImage);
    connect(exitButton, &QPushButton::clicked, exitAct, &QAction::trigger);

    // Настройка размера окна
    resize(900, 600);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
        event->accept();
    else
        event->ignore();
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            scribbleArea->openImage(fileName);
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Draft Creator"),
                                        tr("Select pen width:"),
                                        scribbleArea->penWidth(),
                                        1, 50, 1, &ok);
    if (ok) {
        scribbleArea->setPenWidth(newWidth);
        penWidthSpinBox->setValue(newWidth);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Draft Creator"),

                       tr("<p>The <b>Draft Creator</b> application shows how to use QMainWindow as the "
                          "base widget for an application, and how to reimplement some of "
                          "QWidget's event handlers to receive the events generated for "
                          "the application's widgets:</p><p> We reimplement the mouse event "
                          "handlers to facilitate drawing, the paint event handler to "
                          "update the application and the resize event handler to optimize "
                          "the application's appearance. In addition we reimplement the "
                          "close event handler to intercept the close events before "
                          "terminating the application.</p><p> The example also demonstrates "
                          "how to use QPainter to draw an image in real time, as well as "
                          "to repaint widgets.</p>"));
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
    for (const QByteArray &format : imageFormats) {
        QString text = tr("%1...").arg(QString::fromLatin1(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, &QAction::triggered, this, &MainWindow::save);
        saveAsActs.append(action);
    }

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, &QAction::triggered, this, &MainWindow::penColor);

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, &QAction::triggered, this, &MainWindow::penWidth);

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, &QAction::triggered,
            scribbleArea, &ScribbleArea::clearImage);

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    for (QAction *action : std::as_const(saveAsActs))
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

bool MainWindow::maybeSave()
{
    if (scribbleArea->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Draft Creator"),
                                   tr("The image has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return saveFile("png");
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty())
        return false;
    return scribbleArea->saveImage(fileName, fileFormat.constData());
}
