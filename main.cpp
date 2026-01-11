// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Draft Creator");
    app.setOrganizationName("YourCompany");

    MainWindow window;

    window.setWindowTitle("Draft Creator");

    window.show();
    return app.exec();
}

