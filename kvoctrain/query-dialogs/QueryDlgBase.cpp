/***************************************************************************

    $Id$

                    base class for query dialogs

    -----------------------------------------------------------------------

    begin                : Wed Feb 16 20:50:53 MET 2000
                                           
    copyright            : (C) 1999-2001 Ewald Arnold
                           (C) 2001 The KDE-EDU team
                         
    email                : kvoctrain@ewald-arnold.de                                    

    -----------------------------------------------------------------------

    $Log$
    Revision 1.3  2001/10/17 21:41:16  waba
    Cleanup & port to Qt3, QTableView -> QTable
    TODO:
    * Fix actions that work on selections
    * Fix sorting
    * Fix language-menu

    Revision 1.2  2001/10/13 11:45:29  coolo
    includemocs and other smaller cleanups. I tried to fix it, but as it's still
    qt2 I can't test :(

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

#include "QueryDlgBase.h"

#include <qlineedit.h>
#include <qmultilineedit.h>
#include <qradiobutton.h>
#include <qfont.h>

#include <iostream.h>

#include <LineList.h>

QueryDlgBase::QueryDlgBase ()
{
  kv_doc = 0;
  kv_exp = 0;
  type_timeout = kvq_notimeout;
}


void QueryDlgBase::initFocus() const
{
  //
}


bool QueryDlgBase::smartCompare (const QString& s1, const QString &s2,
                                 int level) const
{
  return s1.stripWhiteSpace() == s2.stripWhiteSpace();
}


bool QueryDlgBase::verifyField(QLineEdit *field, const QString &really)
{
  if (!field->isEnabled() )
    return true;

  QColorGroup u_normal = field->colorGroup();
  u_normal.setColor(QColorGroup::Text, QColor(0xff, 0x00, 0x00));
  QColorGroup k_normal = field->colorGroup();
  k_normal.setColor(QColorGroup::Text, QColor(0x00, 0x80, 0x00));

  QPalette known_pal( field->palette());
  QPalette unknown_pal( field->palette());

  QFont ft = field->font();
  if (ft.weight() != QFont::Bold) {
    ft.setWeight(QFont::Bold);
    field->setFont(ft);
  }

  bool ret = false;
  if (smartCompare(really, field->text(), 0) ) {
    ret = true;
    if (   known_pal.normal() != k_normal
        || known_pal.inactive() != k_normal
        || known_pal.active() != k_normal) {
      // replace text colors
      known_pal.setNormal(k_normal);
      known_pal.setActive(k_normal);
      known_pal.setInactive(k_normal);
      field->setPalette( known_pal );
    }
  }
  else
    if (   unknown_pal.normal() != u_normal
        || unknown_pal.inactive() != u_normal
        || unknown_pal.active() != u_normal) {
      // replace text colors
      unknown_pal.setNormal(u_normal);
      unknown_pal.setActive(u_normal);
      unknown_pal.setInactive(u_normal);
      field->setPalette( unknown_pal );
    }
  return ret;
}


void QueryDlgBase::resetField(QLineEdit *field)
{
  if (!field->isEnabled() )
    return;
  QColorGroup normal = field->colorGroup();
  normal.setColor(QColorGroup::Text, QColor(0x00, 0x00, 0x00));

  QPalette pal( field->palette());
  // replace text colors

  if (   pal.normal() != normal
      || pal.inactive() != normal
      || pal.active() != normal) {
    pal.setNormal(normal);
    pal.setActive(normal);
    pal.setInactive(normal);
    field->setPalette( pal );
  }

  QFont ft = field->font();
  if (ft.weight() != QFont::Normal) {
    ft.setWeight(QFont::Normal);
    field->setFont(ft);
  }
}


bool QueryDlgBase::verifyField(QMultiLineEdit *field, const QString &really,
                               bool mixed)
{
  if (!field->isEnabled() )
    return true;
  QColorGroup u_normal = field->colorGroup();
  u_normal.setColor(QColorGroup::Text, QColor(0xff, 0x00, 0x00));
  QColorGroup k_normal = field->colorGroup();
  k_normal.setColor(QColorGroup::Text, QColor(0x00, 0x80, 0x00));

  QPalette known_pal( field->palette());
  QPalette unknown_pal( field->palette());

  QFont ft = field->font();
  if (ft.weight() != QFont::Bold) {
    ft.setWeight(QFont::Bold);
    field->setFont(ft);
  }

  bool ret = false;
  bool equal = false;
  LineList answerlist (really);
  LineList inputlist (field->text());
  if (!mixed) // no tolerance
    equal = smartCompare(answerlist.allLines(), inputlist.allLines(), 0);
  else {
     bool all = true;
     for (int ai = 0; ai < (int) answerlist.count(); ai++) {
       bool found = false;
       for (int ii = 0; ii < (int) inputlist.count(); ii++) {
         if (answerlist.getLine (ai) == inputlist.getLine(ii) ) {
           found = true;
           break;
         }
       }
       if (!found)
         all = false;
     }
     if (all)
       equal = true;
  }

  if (equal) {
    ret = true;
    if (   known_pal.normal() != k_normal
        || known_pal.inactive() != k_normal
        || known_pal.active() != k_normal) {
      // replace text colors
      known_pal.setNormal(k_normal);
      known_pal.setActive(k_normal);
      known_pal.setInactive(k_normal);
      field->setPalette( known_pal );
    }
  }
  else
    if (   unknown_pal.normal() != u_normal
        || unknown_pal.inactive() != u_normal
        || unknown_pal.active() != u_normal) {
      // replace text colors
      unknown_pal.setNormal(u_normal);
      unknown_pal.setActive(u_normal);
      unknown_pal.setInactive(u_normal);
      field->setPalette( unknown_pal );
    }
  return ret;
}


void QueryDlgBase::resetField(QMultiLineEdit *field)
{
  if (!field->isEnabled() )
    return;
  QColorGroup normal = field->colorGroup();
  normal.setColor(QColorGroup::Text, QColor(0x00, 0x00, 0x00));

  QPalette pal( field->palette());
  // replace text colors

  if (   pal.normal() != normal
      || pal.inactive() != normal
      || pal.active() != normal) {
    pal.setNormal(normal);
    pal.setActive(normal);
    pal.setInactive(normal);
    field->setPalette( pal );
  }

  QFont ft = field->font();
  if (ft.weight() != QFont::Normal) {
    ft.setWeight(QFont::Normal);
    field->setFont(ft);                               	
  }
}


void QueryDlgBase::verifyButton(QRadioButton *radio, bool is_ok, QWidget *widget2)
{
  if (!radio->isEnabled() )
    return;

  QColorGroup u_normal = radio->colorGroup();
  u_normal.setColor(QColorGroup::Foreground, QColor(0xff, 0x00, 0x00));
  QColorGroup k_normal = radio->colorGroup();
  k_normal.setColor(QColorGroup::Foreground, QColor(0x00, 0x80, 0x00));

  QPalette known_pal( radio->palette());
  QPalette unknown_pal( radio->palette());

  // replace text colors

  QFont ft = radio->font();
  if (ft.weight() != QFont::Bold) {
    ft.setWeight(QFont::Bold);
    radio->setFont(ft);
  }

  if (widget2 != 0) {
    ft = widget2->font();
    if (ft.weight() != QFont::Bold) {
      ft.setWeight(QFont::Bold);
      widget2->setFont(ft);
    }
  }

  if (is_ok) {
    if (   known_pal.normal() != k_normal
        || known_pal.inactive() != k_normal
        || known_pal.active() != k_normal) {
      known_pal.setNormal(k_normal);
      known_pal.setActive(k_normal);
      known_pal.setInactive(k_normal);
      radio->setPalette( known_pal );
      if (widget2 != 0)
        widget2->setPalette( known_pal );
    }
  }
  else {
    if (   unknown_pal.normal() != u_normal
        || unknown_pal.inactive() != u_normal
        || unknown_pal.active() != u_normal) {
      unknown_pal.setNormal(u_normal);
      unknown_pal.setActive(u_normal);
      unknown_pal.setInactive(u_normal);
      radio->setPalette( unknown_pal );
      if (widget2 != 0)
        widget2->setPalette( unknown_pal );
    }
  }
}



void QueryDlgBase::resetButton(QRadioButton *radio, QWidget *widget2)
{
  if (!radio->isEnabled() )
    return;
  QColorGroup normal = radio->colorGroup();
  normal.setColor(QColorGroup::Foreground, QColor(0x00, 0x00, 0x00));

  QPalette pal(radio->palette());
  // replace text colors, avoid flickering
  if (   pal.normal() != normal
      || pal.inactive() != normal
      || pal.active() != normal) {
    pal.setNormal(normal);
    pal.setActive(normal);
    pal.setInactive(normal);
    radio->setPalette( pal );
    if (widget2 != 0)
      widget2->setPalette( pal );
  }

  QFont ft = radio->font();
  if (ft.weight() != QFont::Normal) {
    ft.setWeight(QFont::Normal);
    radio->setFont(ft);
  }

  if (widget2 != 0) {
    ft = widget2->font();
    if (ft.weight() != QFont::Normal) {
      ft.setWeight(QFont::Normal);
      widget2->setFont(ft);
    }
  }
}
//#include "QueryDlgBase.moc"
