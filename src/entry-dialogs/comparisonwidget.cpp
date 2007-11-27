/***************************************************************************

    Copyright 2007 Frederik Gladhorn <frederik.gladhorn@kdemail.net>

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "comparisonwidget.h"

#include <keduvocwordtype.h>
#include <keduvoctranslation.h>
#include <keduvocexpression.h>
#include <keduvocdocument.h>
#include <KDebug>
#include <KMessageBox>

ComparisonWidget::ComparisonWidget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    m_doc = 0;

    connect(makeAdjectiveButton, SIGNAL(clicked()), SLOT(slotMakeAdjectiveButton()));
    connect(makeAdverbButton, SIGNAL(clicked()), SLOT(slotMakeAdverbButton()));

//     makeAdjectiveButton->setEnabled(false);
//     makeAdverbButton->setEnabled(false);

    connect(comparativeLineEdit, SIGNAL(editingFinished()), SLOT(slotComparativeChanged()));
    connect(superlativeLineEdit, SIGNAL(editingFinished()), SLOT(slotSuperlativeChanged()));
}

void ComparisonWidget::setTranslation(KEduVocExpression * entry, int translation)
{
    comparativeLineEdit->setText(QString());
    superlativeLineEdit->setText(QString());
    comparativeLineEdit->setEnabled(false);
    superlativeLineEdit->setEnabled(false);

    if (entry) {
        m_translation = entry->translation(translation);
    } else {
        m_translation = 0;
    }

    if (m_translation) {
        absoluteEntryLabel->setText(m_translation->text());
        setEnabled(true);

        if(m_translation->wordType()) {
            if(m_translation->wordType()->containerType() == KEduVocLesson::WordTypeAdjectiveContainer
                || m_translation->wordType()->containerType() == KEduVocLesson::WordTypeAdverbContainer) {
                comparativeLineEdit->setEnabled(true);
                superlativeLineEdit->setEnabled(true);

        ///@todo the comparison forms api is ugly
                comparativeLineEdit->setText(m_translation->comparison().l2());
                superlativeLineEdit->setText(m_translation->comparison().l3());
            }
        }
    } else {
        setEnabled(false);
        absoluteEntryLabel->setText(QString());
    }
}

void ComparisonWidget::slotMakeAdjectiveButton()
{
    if(!m_doc) {
        return;
    }

    // find an adjective container
    KEduVocContainer* container = m_doc->wordTypeContainer()->childOfType(KEduVocWordType::WordTypeAdjectiveContainer);
    if (container) {
        m_translation->setWordType(static_cast<KEduVocWordType*>(container));
        comparativeLineEdit->setEnabled(true);
        superlativeLineEdit->setEnabled(true);
        comparativeLineEdit->setFocus();
    } else {
        ///@todo better message
        KMessageBox::information(this, i18n("Could not determine word type of adjectives"));
    }
}

void ComparisonWidget::slotMakeAdverbButton()
{
    if(!m_doc) {
        return;
    }

    // find an adjective container
    KEduVocContainer* container = m_doc->wordTypeContainer()->childOfType(KEduVocWordType::WordTypeAdverbContainer);
    if (container) {
        m_translation->setWordType(static_cast<KEduVocWordType*>(container));
        comparativeLineEdit->setEnabled(true);
        superlativeLineEdit->setEnabled(true);
        comparativeLineEdit->setFocus();
    } else {
        ///@todo better message
        KMessageBox::information(this, i18n("Could not determine word type of adjectives"));
    }
}

void ComparisonWidget::setDocument(KEduVocDocument * doc)
{
    m_doc=doc;
}

void ComparisonWidget::slotComparativeChanged()
{
    m_translation->comparison().setL2(comparativeLineEdit->text());
}

void ComparisonWidget::slotSuperlativeChanged()
{
     m_translation->comparison().setL3(superlativeLineEdit->text());
}


#include "comparisonwidget.moc"
