#include "postprocessing.h"
#include <QScopedPointer>

PostProcessing::PostProcessing( QObject *parent ) : QObject( parent ) {}

void PostProcessing::prepareTop15( const QVariant &map, const int &max )
{
    m_max = max;

    m_keys << map.value<QIntMap>().keys();
    m_values << map.value<QIntMap>().values();

    emit readyToOperate();
}

void PostProcessing::newComputation( const QString &link )
{
    QThread *thread = new QThread();
    FileManager *fm = new FileManager( link );

    fm->moveToThread( thread );
    connect( thread, &QThread::started, fm, &FileManager::openFile );

    connect( fm, &FileManager::maxSize, this, &PostProcessing::fileSize );
    connect( fm, &FileManager::actualSizeReaded, this, &PostProcessing::currentSize );

    connect( thread, &QThread::finished, [fm] { delete fm; } );

    connect( fm, &FileManager::imDone, thread, &QThread::quit );
    connect( fm, &FileManager::imDone, this, &PostProcessing::done );
    connect( thread, &QThread::finished, thread, &QThread::deleteLater );

    connect( fm, &FileManager::sendTop15, this, &PostProcessing::prepareTop15 );

    thread->start();
}

void PostProcessing::cleanUp()
{
    m_keys.clear();
    m_values.clear();
    m_max = 0;
}

QStringList PostProcessing::returnKeys()
{
    return m_keys;
}

QList<int> PostProcessing::returnValues()
{
    return m_values;
}

int PostProcessing::returnMax()
{
    return m_max;
}
