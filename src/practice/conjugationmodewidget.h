/***************************************************************************
    Copyright 2010 Frederik Gladhorn <gladhorn@kde.org>
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef CONJUGATIONMODEWIDGET_H
#define CONJUGATIONMODEWIDGET_H

#include "abstractwidget.h"


namespace Ui
{
class ConjugationPracticeWidget;
}

namespace Practice
{
class PersonConjugationSolutionWidgets;

class ConjugationModeWidget: public AbstractModeWidget
{
    Q_OBJECT

public:
    ConjugationModeWidget(GuiFrontend *frontend, QWidget *parent = 0);
    virtual ~ConjugationModeWidget();
    QVariant userInput() Q_DECL_OVERRIDE;

    void setQuestion(const QVariant& question) Q_DECL_OVERRIDE;
    void setSolution(const QVariant& solution) Q_DECL_OVERRIDE;
    void setHint(const QVariant& hint) Q_DECL_OVERRIDE;
    void setFeedback(const QVariant& feedback) Q_DECL_OVERRIDE;
    void setFeedbackState(AbstractFrontend::ResultState feedbackState) Q_DECL_OVERRIDE {
        Q_UNUSED(feedbackState);
    }
    void setResultState(AbstractFrontend::ResultState resultState) Q_DECL_OVERRIDE {
        Q_UNUSED(resultState);
    }

    void setQuestionFont(const QFont& font) Q_DECL_OVERRIDE;
    void setSolutionFont(const QFont& font) Q_DECL_OVERRIDE;
    void setQuestionSound(const QUrl& soundUrl) Q_DECL_OVERRIDE;
    void setSolutionSound(const QUrl& soundUrl) Q_DECL_OVERRIDE;
    void setSolutionPronunciation(const QString& pronunciationText) Q_DECL_OVERRIDE;
    void setQuestionPronunciation(const QString& pronunciationText) Q_DECL_OVERRIDE;
    void setSynonym(const QString& /*entry*/) Q_DECL_OVERRIDE {}

public Q_SLOTS:
    void showQuestion() Q_DECL_OVERRIDE;
    void showSolution() Q_DECL_OVERRIDE;
    void showSynonym() Q_DECL_OVERRIDE {}

private Q_SLOTS:
    void nextConjugationForm();

private:
    virtual void setNumberOfConjugationWidgets(const int numberOfForms);

    Ui::ConjugationPracticeWidget* m_ui;
    QStringList m_solution;
    QList<PersonConjugationSolutionWidgets*> m_personWidgets;
    QFont m_solutionFont;
};

}

#endif

