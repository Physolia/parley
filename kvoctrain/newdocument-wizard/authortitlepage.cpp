/***************************************************************************

                             kvtnewdocumentwizardlanguagepage

    -----------------------------------------------------------------------

    copyright     : (C) 2007 Frederik Gladhorn <frederik.gladhorn@kdemail.net>

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

#include "authortitlepage.h"

#include <QWizardPage>

#include "kvtnewdocumentwizard.h"

/**
 *
 * @param parent
 */
AuthorTitlePage::AuthorTitlePage(QWizard * parent)
    : QWizardPage(parent)
{
    setTitle(i18n("Title and author"));

    setupUi(this);

    registerField("authorField", authorTextEdit, "plainText", "textChanged()");
    registerField("titleField", titleLineEdit);
    registerField("licenseField", licenseComboBox, "currentText", "editTextChanged(const QString&)");
    registerField("commentField", commentTextEdit, "plainText", "textChanged()");
    registerField("categoryField", categoryComboBox, "currentText", "editTextChanged(const QString&)");

}

AuthorTitlePage::~ AuthorTitlePage()
{
}


#include "authortitlepage.moc"
