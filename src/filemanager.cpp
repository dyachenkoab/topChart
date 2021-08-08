#include "filemanager.h"

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

    emit sendTop15( variant, m_max );
    emit imDone();
}
