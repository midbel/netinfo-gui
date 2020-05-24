#ifndef IP_H
#define IP_H

#include <QString>
#include <QStringList>

namespace iputil
{
    long parse_ip(QString str) {
        QStringList list = str.split('.');
        long ip = 0;
        int shift = 24;
        for (int i = 0; i < list.size(); i++) {
            QString str = list[i];
            while(str.startsWith('0')) {
                str.remove(0, 1);
            }
            if (str != "") {
                ip |= str.toLong() << shift;
            }
            shift -= 8;
        }
        return ip;
    }

    long mask_size(long ip) {
        long size = 0;
        for (int i = 31; i >= 0; i--) {
            long bit = (ip >> i) & 0x1;
            if (bit == 1) {
                size++;
            } else {
                long mask = (1 << (32-size)) - 1;
                ip = ip & mask;
                if (ip != 0) {
                    return 0;
                }
                break;
            }
        }
        return size;
    }

    long count_hosts(long ip) {
        long size = mask_size(ip);
        return size == 32 ? 1 : (1 << (32-size)) - 2;
    }

    QString net_class(long ip) {
        if (((ip >> 28) & 0x0F) == 0b1111) {
            return "E";
        } else if (((ip >> 28) & 0x0F) == 0b1110) {
            return "D";
        } else if (((ip >> 29) & 0x07) == 0b110) {
            return "C";
        } else if (((ip >> 31) & 0x01) == 1) {
            return "B";
        } else {
            return "A";
        }
    }

    QString net_type(long ip) {
        unsigned long fst = (ip >> 24) & 0xFF;
        unsigned long snd = (ip >> 16) & 0xFF;
        unsigned long trd = (ip >> 16) & 0xD0;

        switch (fst) {
        case 10:
            break;
        case 127:
            return "local";
        case 172:
            if (trd>>4 == 1) {
                break;
            }
        case 192:
            if (snd == 168) {
                break;
            }
        default:
            return "public";
        }
        return "private";
    }

    QString binary_string(long ip) {
        QString str;
        for (int i = 31; i >= 0; i--) {
            int bit = (ip >> i) & 0x1;
            str.append(QString::number(bit));
            if (i%8 == 0 && i > 0) {
                str.append('.');
            }
        }
        return str;
    }

    QString ip_string(long ip) {
        QStringList qs;
        int shift = 24;
        for (int i = 0; i < 4; i++) {
            int byte = (ip >> shift) & 0xFF;
            if (byte == 0) {
                qs.append("000");
            } else {
                QString str = QString::number(byte);
                qs.append(str.leftJustified(3, '0'));
            }

            shift -= 8;
        }
        return qs.join('.');
    }
}

#endif // IP_H
