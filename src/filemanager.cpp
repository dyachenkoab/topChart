#include "filemanager.h"
#include <chrono>
#include <QLocale>

FileManager::FileManager( const QString &link_, QObject *parent )
    : QObject( parent )
{
    m_link = QUrl( link_ );
}

void FileManager::openFile()
{
    m_file.setFileName( m_link.toLocalFile() );

    if ( !m_file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        emit imDone();
        return;
    }
    emit maxSize( m_file.size() );
    computation();
}

void FileManager::computation()
{
    auto t1 = std::chrono::high_resolution_clock::now();
    QList<Note> note;
    int size = 0;

    while ( !m_file.atEnd() ) {
        QStringList lst = QString( m_file.readLine() ).simplified().split( " " );
        emit actualSizeReaded( m_file.pos() );

        QStringList::iterator i = lst.begin();

        while ( i != lst.end() ) {
            auto a = std::find( note.begin(), note.end(), *i );
            if ( a != note.end() ) {
                ( *a ).count += 1;
            } else {
                note.append( Note( ( *i ), 1 ) );
                size++;
            }
            ++i;
        }
    }

    std::sort( note.begin(), note.end() );
    m_file.close();

    if ( size ){
        m_max = note.at( 0 ).count;
    } else {
        emit imDone();
        return;
    }

    int howMany = ( size > 15 ? 15 : size );

    for ( int i = 0; i < howMany; i++ ) {
        m_map.insert( note.at( i ).word, note.at( i ).count );
    }

    QVariant variant;
    variant.setValue(m_map);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto sec = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);
    qDebug() << sec.count() << "- Sec," << (m_file.size() / 1024) / 1024 << "- file size in Mb";


    emit sendTop15( variant, m_max );
    emit imDone();
}
