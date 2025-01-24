#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef DCONF_KEY_COUNT
#define DCONF_KEY_COUNT "/org/altlinux/example/qt_application/count"
#endif

#ifndef DCONF_KEY_VER
#define DCONF_KEY_VER "/org/altlinux/example/qt_application/version"
#endif

#include <dconf/client/dconf-client.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Increase_Button_clicked(); // Обработка нажатия клавиши "Increase by 1"
    void on_Reset_Button_clicked(); // Обработка нажатия клавиши "Reset"

private:
    const gchar *key_count = DCONF_KEY_COUNT; // Ключ Dconf для значения счётчика
    const gchar *key_version = DCONF_KEY_VER; // Ключ Dconf для значения версии
    QString version; // Хранение значения версии
    int num; // Хранение значения счётчика
    void saveNumToDConf();   // Сохранение значения
    void loadNumFromDConf(int &num);  // Загрузка значения
    void loadVersionFromDConf(QString &version);  // Загрузка версии


    Ui::MainWindow *ui;
    DConfClient *dconf_client; // Клиент для DConf
};

#endif // MAINWINDOW_H
