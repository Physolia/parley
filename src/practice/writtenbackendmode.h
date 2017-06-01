/***************************************************************************
    Copyright 2009 Frederik Gladhorn <gladhorn@kde.org>
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef WRITTENBACKENDMODE_H
#define WRITTENBACKENDMODE_H

#include "abstractbackendmode.h"
#include "practice/sessionmanagerbase.h"
#include "practice/writtenpracticevalidator.h"
#include <QScopedPointer>

namespace Practice
{

class WrittenBackendMode : public AbstractBackendMode
{
    Q_OBJECT

public:
    WrittenBackendMode(Practice::AbstractFrontend* frontend, QObject* parent,
                       Practice::SessionManagerBase* sessionManager, KEduVocDocument* doc);

    bool setTestEntry(TestEntry* current) Q_DECL_OVERRIDE;

    void checkAnswer() Q_DECL_OVERRIDE;

public Q_SLOTS:
    void hintAction() Q_DECL_OVERRIDE;

private:
    QString getFeedbackString(TestEntry::ErrorTypes error);

    QString m_lastAnswer;
    QString m_currentHint;
    bool m_firstAttempt;
    SessionManagerBase* m_sessionManager;
    QScopedPointer<WrittenPracticeValidator> m_validator;
    KEduVocDocument* m_doc;
};

}

#endif // WRITTENBACKENDMODE_H
