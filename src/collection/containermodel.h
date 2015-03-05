/***************************************************************************

    Copyright 2007-2008 Frederik Gladhorn <frederik.gladhorn@kdemail.net>

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CONTAINERMODEL_H
#define CONTAINERMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>

#include <QObject>

#include <keduvocdocument.h>
#include <keduvoclesson.h>
#include <keduvocreadonlycontainermodel.h>


/**
  * Model for the tree of containers (lessons, word types).
  */
class ContainerModel : public KEduVocReadonlyContainerModel
{
    Q_OBJECT

public:
    enum ColumnType {
        ContainerNameColumn = 0,
        TotalCountColumn,
        FirstDataColumn
    };

    explicit ContainerModel(KEduVocContainer::EnumContainerType type, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    Qt::DropActions supportedDropActions() const Q_DECL_OVERRIDE;
    QStringList mimeTypes() const Q_DECL_OVERRIDE;
    QMimeData * mimeData(const QModelIndexList &indexes) const Q_DECL_OVERRIDE;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                              int row, int column, const QModelIndex &parent) Q_DECL_OVERRIDE;

    /** Change the name or checkbox of a lesson.
     * @param index which lesson
     * @param value new name
     * @param role
     * @return bool @c true it worked */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;


    QModelIndex appendContainer(const QModelIndex& parent, const QString & containerName = QString());

    void deleteContainer(const QModelIndex& containerIndex);

    /** Indicate supported drag actions
     @return enum of actions supported **/
    Qt::DropActions supportedDragActions() const  Q_DECL_OVERRIDE;

signals:
    /**
     * emitted when the inPractice state or name of a lesson changed.
     */
    void documentModified();
};


#endif
