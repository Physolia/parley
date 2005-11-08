/***************************************************************************

                      query options for kvoctrain

    -----------------------------------------------------------------------

    begin                : Tue Apr 5 2005

    copyright            :(C) 2005 Peter Hedlund

    email                : peter.hedlund@kdemail.net

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

#include <Q3GroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <Q3ButtonGroup>

#include <knuminput.h>

#include "queryoptions.h"
#include "prefs.h"

QueryOptions::QueryOptions(QWidget* parent, const char* name, Qt::WFlags fl)
: QueryOptionsBase(parent,name,fl)
{
  connect(kcfg_Split, SIGNAL(toggled(bool)), kcfg_Periods, SLOT(setEnabled(bool)));
  connect(kcfg_Split, SIGNAL(toggled(bool)), kcfg_Colons, SLOT(setEnabled(bool)));
  connect(kcfg_Split, SIGNAL(toggled(bool)), kcfg_Semicolons, SLOT(setEnabled(bool)));
  connect(kcfg_Split, SIGNAL(toggled(bool)), kcfg_Commas, SLOT(setEnabled(bool)));
  connect(kcfg_Split, SIGNAL(toggled(bool)), kcfg_Fields, SLOT(setEnabled(bool)));
  connect(r_no_limit, SIGNAL(toggled(bool)), kcfg_MaxTimePer, SLOT(setDisabled(bool)));
  connect(r_no_limit, SIGNAL(toggled(bool)), kcfg_ShowCounter, SLOT(setDisabled(bool)));
  connect(kcfg_Split, SIGNAL(toggled(bool)), label_at, SLOT(setEnabled(bool)));
  connect(kcfg_Split, SIGNAL(toggled(bool)), label_split_max_fields, SLOT(setEnabled(bool)));
  connect(r_no_limit, SIGNAL(toggled(bool)), label_mqtime, SLOT(setDisabled(bool)));

  kcfg_MaxTimePer->setDisabled(r_no_limit->isChecked());
  kcfg_ShowCounter->setDisabled(r_no_limit->isChecked());
  label_mqtime->setDisabled(r_no_limit->isChecked());
  kcfg_Periods->setEnabled(kcfg_Split->isChecked());
  kcfg_Colons->setEnabled(kcfg_Split->isChecked());
  kcfg_Semicolons->setEnabled(kcfg_Split->isChecked());
  kcfg_Commas->setEnabled(kcfg_Split->isChecked());
  kcfg_Fields->setEnabled(kcfg_Split->isChecked());
  label_at->setEnabled(kcfg_Split->isChecked());
  label_split_max_fields->setEnabled(kcfg_Split->isChecked());
}

void QueryOptions::updateWidgets()
{
  //This is required for loading profiles properly
  kcfg_QueryTimeout->setButton((int) Prefs::queryTimeout());
  kcfg_MaxTimePer->setValue(Prefs::maxTimePer());
  kcfg_ShowCounter->setChecked(Prefs::showCounter());
  kcfg_SwapDirection->setChecked(Prefs::swapDirection());
  kcfg_AltLearn->setChecked(Prefs::altLearn());
  kcfg_Suggestions->setChecked(Prefs::suggestions());
  kcfg_Split->setChecked(Prefs::split());
  kcfg_Periods->setChecked(Prefs::periods());
  kcfg_Colons->setChecked(Prefs::colons());
  kcfg_Semicolons->setChecked(Prefs::semicolons());
  kcfg_Commas->setChecked(Prefs::commas());
  kcfg_Fields->setValue(Prefs::fields());
  kcfg_ShowMore->setChecked(Prefs::showMore());
  kcfg_IKnow->setChecked(Prefs::iKnow());
}

#include "queryoptions.moc"

