#ifndef NETWINDOW_H
#define NETWINDOW_H

#include <QMainWindow>
#include <QHostInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class NetWindow; }
QT_END_NAMESPACE

class NetWindow : public QMainWindow
{
    Q_OBJECT

public:
    NetWindow(QWidget *parent = nullptr);
    ~NetWindow();

public slots:
    void hostUpdated(QString value);
    void maskUpdated(QString value);
    void exitTriggered();
    void resolveDone(QHostInfo host);

protected:
    void closeEvent(QCloseEvent* event);

private:
    Ui::NetWindow *ui;
    QString host = "127.000.000.001";
    QString mask = "255.255.255.0";

    long ip = 0;
    long msk = 0;
    long net = 0;
    long broad = 0;
    long hosts = 0;
    QString type = "";
    QString klass = "";

    void updateInfos(bool resolve = false);
    void saveSettings();
    void loadSettings();
};
#endif // NETWINDOW_H
