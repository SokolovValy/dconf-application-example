cmake_minimum_required(VERSION 3.16)

project(CounterExample VERSION 0.1 LANGUAGES CXX)

# Настройки для автоматической обработки Qt файлов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Поиск dconf и glib-2.0 с помощью pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(DCONF REQUIRED dconf)
pkg_check_modules(GLIB REQUIRED glib-2.0)

# Указание include-директорий
include_directories(
    ${DCONF_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
)

# Указание директорий для поиска библиотек
link_directories(
    ${DCONF_LIBRARY_DIRS}
    ${GLIB_LIBRARY_DIRS}
)

# Источники проекта
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# Создание исполняемого файла
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CounterExample
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(CounterExample ${PROJECT_SOURCES})
endif()

# Линковка с библиотеками
target_link_libraries(CounterExample PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${DCONF_LIBRARIES}
    ${GLIB_LIBRARIES}
)

# Настройки для macOS и Windows
set_target_properties(CounterExample PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Установка
include(GNUInstallDirs)
install(TARGETS CounterExample
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Финализация для Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CounterExample)
endif()
