/***************************************************************************

                        show document statistics

    -----------------------------------------------------------------------

    begin         : Sun Sep 19 20:50:53 MET 1999

    copyright     : (C) 1999-2001 Ewald Arnold <kvoctrain@ewald-arnold.de>
                    (C) 2005-2007 Peter Hedlund <peter.hedlund@kdemail.net>
    Copyright 2008 Frederik Gladhorn <frederik.gladhorn@kdemail.net>
    -----------------------------------------------------------------------

 ***************************************************************************

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <KDialog>

class LessonStatisticsView;
class StatisticsModel;
class KEduVocDocument;

class StatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    StatisticsWidget(KEduVocDocument* doc, QWidget *parent);
    ~StatisticsWidget();
    
    void setDocument(KEduVocDocument* doc);

private slots:
    void configurePractice();

private:
    KEduVocDocument* m_doc;
    StatisticsModel* m_statisticsModel;
    LessonStatisticsView* m_lessonStatistics;
};

#endif
