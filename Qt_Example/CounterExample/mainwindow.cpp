#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dconf_client = dconf_client_new();
    if (!dconf_client) {
        qCritical("Failed to initialize DConfClient.");
        return;
    }

    loadNumFromDConf(this->num);
    loadVersionFromDConf(this->version);
    ui->label->setText(version);
    ui->lcdNumber->display(num);
}

MainWindow::~MainWindow()
{
    saveNumToDConf();
    if (dconf_client) {
        g_object_unref(dconf_client); // Освобождение DConfClient
    }
    delete ui;
}

void MainWindow::on_Reset_Button_clicked()
{
    this->num = 0;
    ui->lcdNumber->display(num);
}

void MainWindow::on_Increase_Button_clicked()
{
    this->num++;
    ui->lcdNumber->display(num);
}

void MainWindow::saveNumToDConf()
{
    if (!dconf_client) {
        qCritical() << "DConfClient is not initialized.";
        return;
    }

    GVariant *value = g_variant_new_int32(num);

    // Передаем nullptr для GCancellable и nullptr для GError, чтобы игнорировать ошибки
    gboolean success = dconf_client_write_sync(dconf_client, key_count, value, nullptr, nullptr, nullptr);
}

void MainWindow::loadNumFromDConf(int &num)
{
    if (!dconf_client) {
        qCritical() << "DConfClient is not initialized.";
        num = 0;
        return;
    }

    GVariant *value = dconf_client_read(dconf_client, key_count);

    if (!value) {
        qCritical() << "Failed to read value from DConf.";
        num = 0;
        return;
    }

    if (g_variant_is_of_type(value, G_VARIANT_TYPE_INT32)) {
        num = g_variant_get_int32(value);
    } else {
        num = 0;
    }

    g_variant_unref(value);
}

void MainWindow::loadVersionFromDConf(QString &version)
{
    if (!dconf_client) {
        qCritical() << "DConfClient is not initialized.";
        version = "0.1";
        return;
    }

    GVariant *value = dconf_client_read(dconf_client, key_version);

    if (!value) {
        qCritical() << "Failed to read value from DConf.";
        version = "version 0.1";
        return;
    }

    if (g_variant_is_of_type(value, G_VARIANT_TYPE_STRING)) {
        //const gchar *version_str = g_variant_get_string(value, nullptr);
        //version = QString::fromUtf8(version_str);
        version = g_variant_get_string(value, nullptr);
    } else {
        version = "version 0.1";
    }

    g_variant_unref(value);
}
