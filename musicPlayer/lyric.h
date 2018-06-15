#ifndef LYRIC_H
#define LYRIC_H
#include <QObject>

class Lyric : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int time READ time NOTIFY timeChanged)
    Q_PROPERTY(QString text READ text NOTIFY textChanged)

public:
    Lyric(QObject *parent = 0);
    Lyric(const int t, const QString text, QObject *parent  = 0);

    int time() const;
    QString text() const;
    Q_SIGNAL void textChanged();
    Q_SIGNAL void timeChanged();



    Q_INVOKABLE QList<QObject*> getLyric(QString path);

private:
    int m_time;
    QString m_text;
};

#endif // LYRIC_H
