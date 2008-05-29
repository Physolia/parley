//
// C++ Implementation: testentrymanager
//
// Description:
//
//
// Author: David Capel <wot.narg@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include <algorithm>

#include "practiceprefs.h"

#include "../../libkdeedu/keduvocdocument/keduvocexpression.h"
#include "../../libkdeedu/keduvocdocument/keduvoctranslation.h"
#include "../../libkdeedu/keduvocdocument/keduvocdocument.h"


#include <KDebug>

#include "entryfilter.h"
#include "testentrymanager.h"

TestEntryManager::TestEntryManager(QObject * parent)
        : QObject(parent),
        m_iter(QList<KEduVocExpression*>()) // it has no empty constructor. Annoying...
{
    m_entries = QList<KEduVocExpression*>();
    m_fromTranslation = PracticePrefs::questionLanguage();
    m_toTranslation = PracticePrefs::solutionLanguage();
    m_testType = PracticePrefs::testType();

    filterTestEntries();
    shuffle();
}

void TestEntryManager::filterTestEntries()
{
    EntryFilter filter(this, m_doc);
    QList<KEduVocExpression*> m_entries = filter.entries();
}


void TestEntryManager::open(KEduVocDocument* doc)
{
    m_doc = doc;

    if (m_doc && m_doc->lesson())
    {
        m_entries = m_doc->lesson()->entries(KEduVocContainer::Recursive);
        kDebug() << "count " << m_doc->lesson()->entryCount(KEduVocContainer::Recursive);
        m_iter = m_entries;
    }
    else
    {
        kDebug() << "bad" << m_doc << m_doc->lesson();
    }
}

const QString TestEntryManager::currentSolution() const
{
    return m_entry->translation(0)->text(); // TODO use PracticePrefs to find real answer
}

int TestEntryManager::totalEntryCount() const
{
    return m_entries.count();
}

int TestEntryManager::activeEntryCount() const
{
    return totalEntryCount() - m_numberEntriesUsed;
}


void TestEntryManager::shuffle()
{
    // The stl random_shuffle is better than what I would write ;)
    std::random_shuffle(m_entries.begin(), m_entries.end());
}


void TestEntryManager::slotNewEntry()
{
    if (m_iter.hasNext())
    {
        m_entry = m_iter.next();
        KEduVocTranslation * original = m_entry->translation(0);
        kDebug() << original->text();

        // It doesn't matter if these are empty since we would emit empty KUrls/QStrings anyway
        emit signalNewText(original->text());
        emit signalNewImage(original->imageUrl());
        emit signalNewSound(original->soundUrl());
        
        emit signalExpressionChanged(m_entry);

    }
    else
    {
        emit signalQuestionSetFinished();
        kDebug() << "finished";
    }
}
