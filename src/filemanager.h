#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QUrl>
#include <algorithm>
#include <QDataStream>

typedef QMap<QString, int> QIntMap;

struct Note;

class FileManager : public QObject
{
    Q_OBJECT

    QFile m_file;
    QUrl m_link;
    QIntMap m_map;
    int m_max = 0;

    void computation();

public:
    explicit FileManager( const QString &link_, QObject *parent = nullptr );
    ~FileManager() = default;

public slots:
    void openFile();

signals:
    void sendTop15( const QVariant &map, const int &max );
    void maxSize( int sz );
    void actualSizeReaded( int sz );
    void imDone();
};

struct Note {
    QString word;
    int count = 0;

    Note( const QString &str, const int &t )
    {
        word = str;
        count = t;
    }
    ~Note() = default;

    bool operator<( const Note &n ) const
    {
        return count > n.count;
    }

    bool operator==( const QString &n ) const
    {
        return word == n;
    }
};

#endif // FILEMANAGER_H
