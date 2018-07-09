#include "lyric.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QString>
#include <QTextCodec>
#include <iostream>
#include <QGuiApplication>

Lyric::Lyric(QObject *parent):QObject(parent)
{

}

Lyric::Lyric(const int t, const QString text, QObject *parent):QObject(parent),m_time(t),m_text(text)
{

}

int Lyric::time() const
{
    return m_time;
}

QString Lyric::text() const
{
    return m_text;
}

QList<QObject *> Lyric::getLyric(QString path)
{
    //    QString path = "/root/tmp/一路向北.mp3";

    QList<QObject*> lyric;

    QFileInfo fi(path);
    path ="./"+ fi.completeBaseName() + ".lrc";
    fi.setFile(path);
    if (fi.exists() && fi.isReadable()) {
        QFile flyric(path);
        if (! flyric.open(QIODevice::ReadOnly|QIODevice::Text)) {
            QObject *error = new Lyric(0,"false open file");
            lyric.append(error);
            return lyric;
        }
        bool isNum;
        QString lyricLine;
        QTextStream input(&flyric);
        int i = 0;
        while (true){
            const QString text = input.read(1);

            QByteArray str = text.toUtf8();
            int m = str.size();
            if (m == 1)
                continue;
            if(m == 2){
                input.setCodec("gbk");
                break;
            }
            if(m == 3)
                break;
            i++;
        }
        int times;

        lyric.clear();
        while (!input.atEnd())
        {
            lyricLine =  input.readLine();

            lyricLine.mid(1,1).toInt(&isNum,10);

            if (!isNum){
                continue;
            }

            times = (lyricLine.mid(1,2).toInt(&isNum) * 60 +
                     lyricLine.mid(4,2).toInt(&isNum)) * 1000 +
                    lyricLine.mid(7,2).toInt(&isNum) * 10;

            lyricLine = lyricLine.mid(10);
            QObject *lyric_line = new Lyric(times, lyricLine);
            lyric.append(lyric_line);
            times = 0;
            lyricLine.clear();
        }
        return lyric;
    }else{
        lyric.clear();
        QObject *lyric_line;
        if (path != ""){
            lyric_line = new Lyric(0, path);
       // lyric_line = new Lyric(0, "Can't find lyric!");
        }
        else{
            lyric_line = new Lyric(0,"");
        }
        lyric.append(lyric_line);
        return lyric;
    }
}

