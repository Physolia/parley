/***************************************************************************

    Copyright 2008 Avgoustinos Kadis <avgoustinos.kadis@kdemail.net>

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "script.h"

#include "../parley.h"

#include <QStringList>

/**
This class finds the scripts installed in the application folder and manages loading and unloading of plugin scripts

    @author Avgoustinos Kadis <avgoustinos.kadis@kdemail.net>
*/
class ScriptManager : public QObject
{
    public:
        ScriptManager ( ParleyApp * parleyApp );

        ~ScriptManager();
        /**
         * Finds all the available desktop files in {PARLEY_DATA_FOLDER}/plugins
         *
         * @return The list of desktop filenames available for parley
         */
        static QStringList getDesktopFiles();
        /**
         * Returns a QMap (from from categories codenames to categories display label)
         * to be used in KPluginSelector (ScriptDialog) for displaying the various
         * categories
         *
         * @return the QMap described above
         */
        static QMap<QString, QString> categories();
        /**
         * Parses the desktop @p desktopFile given and returns the value of "Script" entry.
         *
         * @param desktopFile The .desktop file that will get the value from
         * @return The value of "Script" entry. Empty string of no "Script" entry is found
         */
        static QString getScriptEntry ( QString desktopFile );
        /**
         * Returns the full path to the script name given in the @p desktopFile.
         *
         * @param desktopFile The desktop file for the parley plugin
         * @return The full-path to the script
         */

        QString getScriptFileName ( QString desktopFile );
        /**
         * Returns a list of filenames (full path) of enabled scripts
         */
        QStringList enabledScripts();
        /**
         * Modify the parleyrc configuration so it disables the @p dektopFile plugin.
         * This function is to be used when the plugin is invalid (wrong script name,
         * incorrect desktop file etc)
         *
         * @param desktopFile
         */
        void disablePlugin ( QString desktopFile );
        QStringList availableScripts();
        /**
         * Load all the available scripts so they can be activated afterwards
         */
        void loadScripts();
        /**
         * Adds a QObject as a module for the script
         * @param obj The QObject to be added to the script
         * @param name The name of the object as it will appear in the script
         */
        void addObject ( QObject * obj, const QString & name );
        /**
         * Reload all the scripts
         */
        void reloadScripts();
        /**
         * Add a KAction to the Scripts menu
         * @param name The action name
         * @param action KAction to be added
         */
        void addScriptAction ( const QString & name, KAction * action );

    private:
        ParleyApp * m_parleyApp;
        QList<Script*> m_scripts;
        QMap<QString, QObject*> m_scriptObjects;
        QList<QAction*> m_scriptActions;

//         friend class Scripting::Parley;
};

#endif
