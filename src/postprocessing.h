#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H
#include <QThread>
#include <QPointer>
#include "filemanager.h"
typedef QMap<QString, int> QIntMap;

class PostProcessing : public QObject
{
    Q_OBJECT
    QStringList m_keys;
    QList<int> m_values;
    int m_max = 0;

public:
    explicit PostProcessing( QObject *parent = nullptr );
    ~PostProcessing() = default;

public slots:
    void prepareTop15( const QVariant &map, const int &max );
    QStringList returnKeys();
    QList<int> returnValues();
    int returnMax();
    void newComputation( const QString &link );
    void cleanUp();

signals:
    void readyToOperate();
    void fileSize( int sz );
    void currentSize( int sz );
    void done();
};


#endif // POSTPROCESSING_H
