/***************************************************************************

    $Id$

                    types options dialog page

    -----------------------------------------------------------------------

    begin                : Sun Sep 12 15:38:31 1999
                                           
    copyright            : (C) 1999-2001 Ewald Arnold
                           (C) 2001 The KDE-EDU team
                         
    email                : kvoctrain@ewald-arnold.de                                    

    -----------------------------------------------------------------------

    $Log$
    Revision 1.3  2001/10/17 21:41:15  waba
    Cleanup & port to Qt3, QTableView -> QTable
    TODO:
    * Fix actions that work on selections
    * Fix sorting
    * Fix language-menu

    Revision 1.2  2001/10/13 11:45:29  coolo
    includemocs and other smaller cleanups. I tried to fix it, but as it's still
    qt2 I can't test :(

    Revision 1.1  2001/10/05 15:38:38  arnold
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

#include "TypeOptPage.h"

#include <kapp.h>

#include <kmessagebox.h>

#include <qkeycode.h>
#include <qlistbox.h>
#include <qpushbutton.h>

#include <kvoctraindoc.h>
#include <QueryManager.h>

#include "../common-dialogs/LessonInputDlg.h"

#define TYPE_TAG ". "

TypeOptPage::TypeOptPage
(
        const vector<QString> &types,
        kvoctrainDoc    *_doc,
	QWidget         *parent,
	const char      *name,
        bool             modal
)
	:
	TypeOptPageForm( parent, name ),
        doc(_doc)
{
	connect( typeList, SIGNAL(highlighted(int)), SLOT(slotTypeChosen(int)) );
	connect( b_cleanup, SIGNAL(clicked()), SLOT(slotCleanup()) );
	connect( b_delete, SIGNAL(clicked()), SLOT(slotDeleteType()) );
	connect( b_modify, SIGNAL(clicked()), SLOT(slotModifyType()) );
	connect( b_new, SIGNAL(clicked()), SLOT(slotNewType()) );

	setCaption(i18n("Options" ));

        QString str;
        for (int i = 0; i < (int) types.size(); i++) {
          str.setNum (i+1);
          if (i <= 9)
            str.insert (0, " ");
          typeList->insertItem (str+TYPE_TAG+types[i]);
          typeIndex.push_back(i);
        }

        act_type = 0;
        if (types.size() != 0)
          typeList->setCurrentItem (act_type);

        b_modify->setEnabled(typeList->count() != 0);
        b_delete->setEnabled(typeList->count() != 0);

        typeList->setFocus();
}


void TypeOptPage::initFocus() const
{
  typeList->setFocus();
}


void TypeOptPage::slotTypeChosen(int index)
{
   act_type = index;
}


void TypeOptPage::slotNewType()
{
     LessonInputDlg lid ("", i18n("Input type description"), i18n("Type description"));
     if (lid.exec() == QDialog::Accepted) {
       QString str;
       int i = typeList->count()+1;
       str.setNum (i);
       if (i <= 9)
         str.insert (0, " ");
       typeList->insertItem (str+TYPE_TAG+lid.getInput().stripWhiteSpace());
       typeIndex.push_back(-(i-1));
       act_type = typeList->count();
       typeList->setCurrentItem (i-1);
       b_modify->setEnabled(true);
       b_delete->setEnabled(true);
     }
}


void TypeOptPage::slotModifyType()
{
   if (typeList->count() != 0
       && (int) typeList->count() > act_type) {
     QString str = typeList->text (act_type);
     int pos = str.find (TYPE_TAG);
     str.remove (0, pos+strlen (TYPE_TAG));
     LessonInputDlg lid (str, i18n("Input type description"), i18n("Type description"));
     if (lid.exec() == QDialog::Accepted) {
       QString str2;
       str2.setNum (act_type+1);
       if (act_type <= 9)
         str2.insert (0, " ");
       typeList->changeItem (str2+TYPE_TAG+lid.getInput().stripWhiteSpace(), act_type);
     }
   }
}


void TypeOptPage::updateListBox(int start)
{
  QString str, str2;
  for (int i = start; i < (int) typeList->count(); i++) {
     str = typeList->text (i);
     int pos = str.find (TYPE_TAG);
     str.remove (0, pos+strlen (TYPE_TAG));
     str2.setNum (i+1);
     if (i <= 9)
       str2.insert (0, " ");
     typeList->changeItem (str2+TYPE_TAG+str, i);
  }
}


void TypeOptPage::slotDeleteType()
{
   int act = act_type;
   if (typeList->count() != 0
       && (int) typeList->count() > act) {

     QString t;
     t.setNum(typeIndex[act_type]+1);
     t.insert (0, QM_USER_TYPE);
     for (int ent = 0; ent < doc->numEntries(); ent++) {
       // FIXME: ProgressDlg here?
       kvoctrainExpr *exp = doc->getEntry(ent);
       for (int lang = 0; lang < (int) doc->numLangs(); lang++) {
         if (exp->getType(lang) == t) {
           KMessageBox::information(this,
                     i18n("Can't delete this user defined type\nbecause it is in use."),
                     kapp->makeStdCaption(i18n("Deleting a type description")));
           return;
         }
       }
     }

     typeList->removeItem (act);
     typeIndex.erase (&typeIndex[act], &typeIndex[act+1]);

     if ((int) typeList->count() <= act)
        act = typeList->count()-1;
     else
        updateListBox(act); // update items after current
  
     if (act >= 0)
       typeList->setCurrentItem (act);
   }
   b_modify->setEnabled(typeList->count() != 0);
   b_delete->setEnabled(typeList->count() != 0);
}


void TypeOptPage::getTypeNames (vector<QString> &ret_type,
                                vector<int> &ret_Index)
{
   QString str;    ret_type.clear();
   for (int i = 0; i < (int) typeList->count(); i++) {
     str = typeList->text(i);
     int pos = str.find (TYPE_TAG);
     str.remove (0, pos+strlen (TYPE_TAG));
     ret_type.push_back (str);
   }
   ret_Index = typeIndex;
}


void TypeOptPage::slotCleanup()
{
   vector<bool> used_type;
   for (int i = 0; i <= (int) typeList->count(); i++)
     used_type.push_back(false);

   for (int col = 0; col < doc->numLangs(); col++)
     for (int i = 0; i < (int) doc->numEntries(); i++) {
       QString t = doc->getEntry(i)->getType(col);
       if (t.left(strlen(QM_USER_TYPE)) == QM_USER_TYPE) {
         t.remove (0, 1);
         int idx = t.toInt();
         if ((int) used_type.size() < idx)
           used_type.resize(idx);
         if (idx != 0)
           used_type[idx-1] = true ;
       }
     }

   for (int i = used_type.size()-1; i >= 0; i--)
     if (!used_type[i]) {
       for (int u = 0; u < (int) typeIndex.size() ; u++) {
         if (typeIndex[u] == i || typeIndex[u] < 0) {
           act_type = i;
           slotDeleteType();
           break;
         }
       }
     }

   act_type = 0;
   typeList->setCurrentItem (act_type);
}


void TypeOptPage::cleanUnused(kvoctrainDoc *doc,
                              const vector<int> &typeIndex,
                              int old_types)
{
   vector<int> translate_index;
   vector<QString> new_typeStr;

   /////////////////////////////////////////////////////
   // translate_index contains new index number for each
   // old index
   for (int i = 0; i <= QMAX (old_types, (int) typeIndex.size()); i++)
     translate_index.push_back(0);

   // now adjust lesson descriptions to new index

   for (int i = 0; i < (int) typeIndex.size(); i++) {
     if (typeIndex[i] >= 0)
       translate_index[typeIndex[i]+1] = i+1;
   }

   // only keep remaining type indices

   // set type index to 0 when not needed any more
   // and translate to new index

   for (int col = 0; col < doc->numLangs(); col++) {
     for (int i = 0; i < doc->numEntries(); i++) {
       QString old = doc->getEntry(i)->getType (col);
       if (!old.isEmpty() && old.left(strlen(QM_USER_TYPE)) == QM_USER_TYPE) {
         old.remove (0, 1);
         int o = old.toInt();

         QString newtype;
         if (translate_index[o] != 0) {
           newtype.setNum (translate_index[o]);
           newtype.insert (0, QM_USER_TYPE);
           doc->getEntry(i)->setType (col, newtype);
         }
         else
           doc->getEntry(i)->setType (col, "");
       }
     }
   }

}


void TypeOptPage::keyPressEvent( QKeyEvent *e )
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
#include "TypeOptPage.moc"
