// -*- C++ -*-
/***************************************************************************

    $Id$

                         view to kvoctrain parts

    -----------------------------------------------------------------------

    begin                : Thu Mar 11 20:50:53 MET 1999
                                           
    copyright            : (C) 1999-2001 Ewald Arnold
                           (C) 2001 The KDE-EDU team
                         
    email                : kvoctrain@ewald-arnold.de                                    

    -----------------------------------------------------------------------

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   * 
 *                                                                         *
 ***************************************************************************/


#ifndef KVOCTRAINVIEW_H 
#define KVOCTRAINVIEW_H 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 

class QGridLayout;
class QFrame;
class KApplication;
class kvoctrainExpr;
class kvoctrainTable;
class kvoctrainApp;
class kvoctrainDoc;
class GradeCols;

#include "rowtable.h"
#include "kvoctraindoc.h"

/**
  * This class provides an incomplete base for your application view. 
  */

class kvoctrainView : public QWidget
{
  Q_OBJECT

 public:

   enum Resizer { Automatic,  // guess something meaningful for resizing
                  Fixed,      // keep users sizes
                  Percent};   // keep percentage of size

  void setResizer (Resizer res) { header_resizer = res; }

  /** Constructor for the main view */
  kvoctrainView(kvoctrainDoc* doc,
                const LangSet &ls, const GradeCols &gradecols,
                kvoctrainApp *parent = 0);

  /** Destructor for the main view */
  ~kvoctrainView();

  /** sets view to another vocabulary */
  void setView (kvoctrainDoc *doc, const LangSet &ls, const GradeCols &gc);

  kvoctrainTable* getTable() { return lb_list; }
  void setHeaderProp (int id, const QString &name, const QString &pixfile=QString::null);

  void setInlineEnabled(bool state);
  void adjustContent();

 private:

 protected:

  QFrame          *f_list;
  kvoctrainTable  *lb_list;
  bool             autoResize;
  kvoctrainDoc    *the_doc;
  QGridLayout     *list_layout;
  Resizer          header_resizer;
  kvoctrainApp    *parent;

  /** resizes table when frame is resized */
  virtual void resizeEvent ( QResizeEvent * );
  void showEvent (  QShowEvent * s_ev);
};

/**
  * This class provides a view to your vocabulary
  */

class kvoctrainTable : public RowTable
{
  Q_OBJECT

 public:
  kvoctrainTable( kvoctrainDoc *_doc,
                  const LangSet *ls, const GradeCols *gc = 0,
                  QWidget *parent = NULL, const char *name = NULL );

  int  currentItem() { return currentRow(); }
  void setCurrentItem(int row);
  int  count() { return numRows(); }

  void setModified (bool _dirty = true) { m_rows->setModified(_dirty); }
  QString getIdent (int i) const { return m_rows->getIdent(i); }
  QString getOriginalIdent () const { return m_rows->getOriginalIdent(); }
  int findIdent (QString id) const { return m_rows->findIdent(id); }

signals:

public slots:
  void sortByColumn_alpha (int index);
  void sortByColumn_index (int index);
  void slotSelectionChanged();

protected:
  int             current;

 private:
  void sortByColumn(int, bool);

};

#endif // KVOCTRAINVIEW_H
