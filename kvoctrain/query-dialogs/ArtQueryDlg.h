/***************************************************************************

    $Id$

                     query dialog for articles

    -----------------------------------------------------------------------

    begin                : Fri Dec 3 18:28:18 1999

    copyright            : (C) 1999-2001 Ewald Arnold
                           (C) 2001 The KDE-EDU team
    email                : kvoctrain@ewald-arnold.de

    -----------------------------------------------------------------------

    $Log$
    Revision 1.2  2001/10/17 21:41:15  waba
    Cleanup & port to Qt3, QTableView -> QTable
    TODO:
    * Fix actions that work on selections
    * Fix sorting
    * Fix language-menu

    Revision 1.1  2001/10/05 15:45:05  arnold
    import of version 0.7.0pre8 to kde-edu


 ***************************************************************************

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef ArtQueryDlg_included
#define ArtQueryDlg_included

#include "ArtQueryDlgForm.h"
#include "QueryDlgBase.h"
#include <GrammerManager.h>

struct SpecFont_t;

class ArtQueryDlg : public ArtQueryDlgForm,
		    public QueryDlgBase
{
    Q_OBJECT

public:

    ArtQueryDlg(
                SpecFont_t *font,
                QString type,
                int entry,
                int col,
                int query_cycle,
                int query_num,
                int query_startnum,
                kvoctrainExpr *exp,
                kvoctrainDoc  *doc,
                const Article &articles,
                int   mqtime,
                bool show,
                kvq_timeout_t type_timeout,
                QWidget *parent=0,
                char    *name=0);

    void setQuery (QString type,
                int entry,
                int col,
                int query_cycle,
                int query_num,
                int query_startnum,
                kvoctrainExpr *exp,
                kvoctrainDoc  *doc,
                const Article &articles,
                int   mqtime,
                bool show,
                kvq_timeout_t type_timeout);

public slots:
    virtual void initFocus() const;

protected:
    void keyPressEvent( QKeyEvent *e );

signals:
    void sigEditEntry(int row, int col);

protected slots:
    void stopItClicked();
    void showMoreClicked();
    void showAllClicked();
    void slotFemClicked();
    void editClicked();
    void knowItClicked();
    void slotNaturalClicked();
    void slotMaleClicked();
    void dontKnowClicked();
    void verifyClicked();
    void returnPressed();
    void timeoutReached();

protected:

    Article   articles;

};
#endif // ArtQueryDlg_included
