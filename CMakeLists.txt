cmake_minimum_required(VERSION 3.5)
project(ScribbleExample LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Qt (версии 5 или 6)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Включить автоматические MOC, UIC, RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Добавление исполняемого файла
add_executable(ScribbleExample
    main.cpp
    mainwindow.cpp
    mainwindow.h
    scribblearea.cpp
    scribblearea.h
    mainwindow.ui  # Если есть .ui-файл
)

# Подключение Qt-модулей
target_link_libraries(ScribbleExample PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
