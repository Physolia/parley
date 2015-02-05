/***************************************************************************

    Copyright 2007 Frederik Gladhorn <frederik.gladhorn@kdemail.net>
    Copyright 2014 Inge Wallin       <inge@lysator.liu.se>

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef COLLECTION_H
#define COLLECTION_H

// Qt
#include <QObject>

// keduvocdocument library
#include <keduvocdocument.h>

// Parley
#include "testentry.h"


class QTimer;
class WordCount;


class Collection : public QObject
{
    Q_OBJECT

public:
    Collection(KEduVocDocument *doc, QObject* parent = 0);
    Collection(QUrl *url, QObject* parent = 0);
    ~Collection();


    KEduVocDocument *eduVocDocument();

    void setTitle(const QString& title);

    void numDueWords(WordCount &wc);


    /** Enable/disable the timed auto backup
     */
    void enableAutoBackup(bool enable);

public Q_SLOTS:

    /** close the document*/
    void close();

Q_SIGNALS:
    /** Emitted when the document pointer is changed.
     @todo Stop using documentChanged(0) as a replacement for destoyed in editor classes.**/
    void documentChanged(KEduVocDocument *newDocument);
    void languagesChanged();
    void statesNeedSaving();

private:
    void initializeDefaultGrammar(KEduVocDocument *doc);
    void setDefaultDocumentProperties(KEduVocDocument *doc);

 private:
    // The contents of the document
    KEduVocDocument *m_doc;

    QTimer           *m_backupTimer; // Timer for next autosave
    QList<TestEntry*> m_allTestEntries;

};

#endif
