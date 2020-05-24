#include "netwindow.h"
#include "ui_netwindow.h"
#include "ip.h"

NetWindow::NetWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NetWindow)
{
    ui->setupUi(this);

    ui->addrHost->setText(host);
    ui->addrMask->setText(mask);

    ui->addrHost->setFocus();
    ui->addrHost->selectAll();

    connect(ui->addrHost, SIGNAL(textChanged(QString)), this, SLOT(hostUpdated(QString)));
    connect(ui->addrMask, SIGNAL(textChanged(QString)), this, SLOT(maskUpdated(QString)));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitTriggered()));

    ip = iputil::parse_ip(host);
    msk = iputil::parse_ip(mask);
    ui->bitsHost->setText(iputil::binary_string(ip));
    ui->bitsMask->setText(iputil::binary_string(msk));

    updateInfos();
}

NetWindow::~NetWindow()
{
    delete ui;
}

void NetWindow::hostUpdated(QString value) {
    if (value == host || value == "") {
        return ;
    }
    ip = iputil::parse_ip(value);
    ui->bitsHost->setText(iputil::binary_string(ip));
    updateInfos();
}

void NetWindow::maskUpdated(QString value) {
    if (value == mask || value == "") {
        return ;
    }
    msk = iputil::parse_ip(value);
    ui->bitsMask->setText(iputil::binary_string(msk));
    updateInfos();
}

void NetWindow::updateInfos() {
    net = ip & msk;
    ui->infoNetwork->setText(iputil::ip_string(net));

    long size = iputil::mask_size(msk);
    broad = ip | ((1<< (32-size)) - 1);
    ui->infoBroadcast->setText(iputil::ip_string(broad));

    hosts = iputil::count_hosts(msk);
    ui->infoHosts->setText(QString::number(hosts));

    type = iputil::net_type(ip);
    ui->infoType->setText(type);

    klass = iputil::net_class(ip);
    ui->infoClass->setText(klass);
}

void NetWindow::exitTriggered() {
    QApplication::quit();
}

