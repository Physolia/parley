/***************************************************************************

    $Id$

                    viewing options dialog page

    -----------------------------------------------------------------------

    begin                : Fri Sep 10 16:42:01 1999

    copyright            : (C) 1999-2001 Ewald Arnold
                           (C) 2001 The KDE-EDU team
    email                : kvoctrain@ewald-arnold.de

    -----------------------------------------------------------------------

    $Log$
    Revision 1.7  2001/11/10 21:13:42  arnold
    removed icons and compatibilty for kde1

    Revision 1.6  2001/11/09 14:19:33  arnold
    fixed and improved some dialog pages

    Revision 1.5  2001/11/09 10:40:46  arnold
    removed ability to display a different font for each column

    Revision 1.4  2001/10/25 17:34:19  arnold
    replaced qtarch dialog files by qtdesigner

    Revision 1.3  2001/10/17 21:41:15  waba
    Cleanup & port to Qt3, QTableView -> QTable
    TODO:
    * Fix actions that work on selections
    * Fix sorting
    * Fix language-menu

    Revision 1.2  2001/10/13 11:45:29  coolo
    includemocs and other smaller cleanups. I tried to fix it, but as it's still
    qt2 I can't test :(

    Revision 1.1  2001/10/05 15:44:04  arnold
    import of version 0.7.0pre8 to kde-edu


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   * 
 *                                                                         *
 ***************************************************************************/

#include <kapp.h>
#include <kfontdialog.h>
#include <kcolorbutton.h>
#include <klocale.h>

#include <qkeycode.h>
#include <qlabel.h>
#include <qcheckbox.h>

#include "ViewOptPage.h"
#include "LangOptPage.h"

#include <QueryManager.h>
#include <kv_resource.h>

#include <kstddirs.h>
#include  <kconfig.h>

ViewOptPage::ViewOptPage
(
        QFont        &_font,
        GradeCols    &cols,
        QueryManager *manager,
	QWidget      *parent,
	const char   *name
)
	:
	ViewOptPageForm( parent, name ),
        gc(cols),
        font(_font)
{
   connect( b_col0, SIGNAL(changed(const QColor&)), SLOT(slotCol0(const QColor&)) );
   connect( b_col1, SIGNAL(changed(const QColor&)), SLOT(slotCol1(const QColor&)) );
   connect( b_col2, SIGNAL(changed(const QColor&)), SLOT(slotCol2(const QColor&)) );
   connect( b_col3, SIGNAL(changed(const QColor&)), SLOT(slotCol3(const QColor&)) );
   connect( b_col4, SIGNAL(changed(const QColor&)), SLOT(slotCol4(const QColor&)) );
   connect( b_col5, SIGNAL(changed(const QColor&)), SLOT(slotCol5(const QColor&)) );
   connect( b_col6, SIGNAL(changed(const QColor&)), SLOT(slotCol6(const QColor&)) );
   connect( b_col7, SIGNAL(changed(const QColor&)), SLOT(slotCol7(const QColor&)) );
   connect( c_use, SIGNAL(toggled(bool)), SLOT(slotColUsed(bool)) );
   connect( b_choose, SIGNAL(clicked()), SLOT(slotChooseFont()) );

   setCaption( kapp->makeStdCaption(i18n("Document properties" )));

   e_font->setText (QString("%1 %2pt").arg(font.family()).arg(font.pointSize()));

// l_lev0->setText (QueryManager::gradeStr("Not queried:");
   l_lev0->setBuddy(b_col0);

   QString s = QueryManager::gradeStr(KV_LEV1_GRADE);
   int pos = s.findRev(" ");
   if (pos >= 0)
     s.insert(pos+1, "&");
   l_lev1->setText (s+':');
   l_lev1->setBuddy(b_col1);

   s = QueryManager::gradeStr(KV_LEV2_GRADE);
   pos = s.findRev(" ");
   if (pos >= 0)
     s.insert(pos+1, "&");
   l_lev2->setText (s+':');
   l_lev2->setBuddy(b_col2);

   s = QueryManager::gradeStr(KV_LEV3_GRADE);
   pos = s.findRev(" ");
   if (pos >= 0)
     s.insert(pos+1, "&");
   l_lev3->setText (s+':');
   l_lev3->setBuddy(b_col3);

   s = QueryManager::gradeStr(KV_LEV4_GRADE);
   pos = s.findRev(" ");
   if (pos >= 0)
     s.insert(pos+1, "&");
   l_lev4->setText (s+':');
   l_lev4->setBuddy(b_col4);
 
   s = QueryManager::gradeStr(KV_LEV5_GRADE);
   pos = s.findRev(" ");
   if (pos >= 0)
     s.insert(pos+1, "&");
   l_lev5->setText (s+':');
   l_lev5->setBuddy(b_col5);
 
   s = QueryManager::gradeStr(KV_LEV6_GRADE);
   pos = s.findRev(" ");
   if (pos >= 0)
     s.insert(pos+1, "&");
   l_lev6->setText (s+':');
   l_lev6->setBuddy(b_col6);
 
   s = QueryManager::gradeStr(KV_LEV7_GRADE);
   pos = s.findRev(" ");
   if (pos >= 0)
     s.insert(pos+1, "&");
   l_lev7->setText (s+':');
   l_lev7->setBuddy(b_col7);
 
   b_col0->setColor (cols.col0);
   b_col1->setColor (cols.col1);
   b_col2->setColor (cols.col2);
   b_col3->setColor (cols.col3);
   b_col4->setColor (cols.col4);
   b_col5->setColor (cols.col5);
   b_col6->setColor (cols.col6);
   b_col7->setColor (cols.col7);
   c_use->setChecked (gc.use);
   slotColUsed(gc.use);

}


void ViewOptPage::initFocus() const
{
  c_use->setFocus();
}


void ViewOptPage::slotChooseFont()
{
   KFontDialog fdlg (0L, 0L, false, true);
   fdlg.setIcon (QPixmap (locate("data",  "kvoctrain/mini-kvoctrain.xpm" )));
   fdlg.setCaption(i18n("Choose table font"));
   fdlg.setFont(font);
   if (fdlg.exec() == QDialog::Accepted ) {
     font = fdlg.font();
     font.setWeight(QFont::Normal);
     font.setStrikeOut(false);
     font.setUnderline(false);
     e_font->setText (QString("%1 %2pt").arg(font.family()).arg(font.pointSize()));
   }
}


void ViewOptPage::slotCol0(const QColor &col)
{
  gc.col0 = col;
}


void ViewOptPage::slotCol1(const QColor &col)
{
  gc.col1 = col;
}


void ViewOptPage::slotCol2(const QColor &col)
{
  gc.col2 = col;
}


void ViewOptPage::slotCol3(const QColor &col)
{
  gc.col3 = col;
}


void ViewOptPage::slotCol4(const QColor &col)
{
  gc.col4 = col;
}


void ViewOptPage::slotCol5(const QColor &col)
{
  gc.col5 = col;
}


void ViewOptPage::slotCol6(const QColor &col)
{
  gc.col6 = col;
}


void ViewOptPage::slotCol7(const QColor &col)
{
  gc.col7 = col;
}


void ViewOptPage::slotColUsed(bool used)
{
  gc.use = used;

  b_col0->setEnabled(used);
  b_col1->setEnabled(used);
  b_col2->setEnabled(used);
  b_col3->setEnabled(used);
  b_col4->setEnabled(used);
  b_col5->setEnabled(used);
  b_col6->setEnabled(used);
  b_col7->setEnabled(used);

  l_lev0->setEnabled(used);
  l_lev1->setEnabled(used);
  l_lev2->setEnabled(used);
  l_lev3->setEnabled(used);
  l_lev4->setEnabled(used);
  l_lev5->setEnabled(used);
  l_lev6->setEnabled(used);
  l_lev7->setEnabled(used);
}

void ViewOptPage::keyPressEvent( QKeyEvent *e )
{
   if (e->state() & AltButton & ControlButton & ShiftButton == 0) {
     if (  e->key() == Key_Escape )
       emit reject();
     else if (  e->key() == Key_Enter
              ||e->key() == Key_Return)
       emit accept();
     else
       e->ignore();
   }
   else
     e->ignore();
}
#include "ViewOptPage.moc"
