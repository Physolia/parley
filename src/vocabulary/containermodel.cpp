/***************************************************************************

    Copyright 2007 Frederik Gladhorn <frederik.gladhorn@kdemail.net>

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "containermodel.h"

#include "containermimedata.h"
#include "vocabularymimedata.h"

#include <keduvocdocument.h>
#include <keduvoclesson.h>
#include <keduvocwordtype.h>
#include <keduvocexpression.h>

#include <KRandom>
#include <KIcon>
#include <kdebug.h>
#include <klocale.h>
#include <QItemSelection>

/** @file
  * Implementation of ContainerModel.
  * Functions to create the model from the lessons of the vocabulary document.
  */

ContainerModel::ContainerModel(KEduVocLesson::EnumContainerType type, QObject * parent) : QAbstractItemModel(parent)
{
    m_type = type;
    m_container = 0;

    switch(m_type){
    case KEduVocLesson::Lesson:
kDebug() << "Creating new root lesson container";
        m_container = new KEduVocLesson("model root lesson", 0);
        break;
    case KEduVocLesson::WordType:
kDebug() << "Creating new root word type container";
        m_container = new KEduVocWordType("model root word type", 0);
        break;
//     case KEduVocLesson::Leitner:
//         m_container = new KEduVocLeitnerBox(0);
//         break;
    }

    setSupportedDragActions(Qt::CopyAction | Qt::MoveAction);
}


ContainerModel::~ ContainerModel()
{
    delete m_container;
}


void ContainerModel::setDocument(KEduVocDocument * doc)
{

//     appendLesson(QModelIndex(), "first");
//     appendLesson(QModelIndex(), "second");
// 
//     appendLesson(index(1, 0, QModelIndex()), "child of second");
//     appendLesson(index(0, 0, QModelIndex()), "child of first");
//     appendLesson(index(1, 0, QModelIndex()), "child 2 of second");

/*
kDebug() <<
    "appended: " << 
        static_cast<KEduVocContainer*>(appended.internalPointer())->name()
    << "\nchild of appended: " <<
        static_cast<KEduVocContainer*>(app2.internalPointer())->name();*/

//     removeRows(0, 1, appended);

    if (rowCount(QModelIndex()) > 0) {
        beginRemoveRows(QModelIndex(), 0, 0);
        m_container->removeChildContainer(0);
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), 0, 0);
    switch(m_type){
    case KEduVocLesson::Lesson:
kDebug() << "setting root lesson";
        m_container->appendChildContainer(doc->lesson());
        break;
    case KEduVocLesson::WordType:
        m_container->appendChildContainer(doc->wordTypeContainer());
        break;
//     case KEduVocLesson::Leitner:
//         m_container
//         break;
    default:
        break;
    }
    endInsertRows();
}


QModelIndex ContainerModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    KEduVocContainer *parentLesson;

    if (!parent.isValid()) {
        parentLesson = m_container;
    } else {
        parentLesson = static_cast<KEduVocContainer*>(parent.internalPointer());
    }

    KEduVocContainer *childLesson = parentLesson->childContainer(row);

    if (childLesson) {
        return createIndex(row, column, childLesson);
    } else {
        return QModelIndex();
    }
}


QModelIndex ContainerModel::index(KEduVocContainer * container) const
{
    if(!container) {
        return QModelIndex();
    }

    if(container == m_container) {
        return QModelIndex();
    }

    QModelIndex currentIndex = index(container->row(), 0, index(container->parent()));
    Q_ASSERT(container == currentIndex.internalPointer());

    return currentIndex;
}


QModelIndex ContainerModel::parent(const QModelIndex &index) const
{

    if (!index.isValid()) {
        return QModelIndex();
    }

    KEduVocContainer *childItem = static_cast<KEduVocContainer*>(index.internalPointer());
    KEduVocContainer *parentItem = childItem->parent();

    if (parentItem == m_container) {
        return QModelIndex();
    }

    QModelIndex parentIndex = createIndex(parentItem->row(), 0, parentItem);
    return parentIndex;
}


int ContainerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0;
    }

    KEduVocContainer *parentItem;
    if (!parent.isValid()) {
        parentItem = m_container;
    } else {
        parentItem =  static_cast<KEduVocContainer*>(parent.internalPointer());
    }
    return parentItem->childContainerCount();
}


QModelIndex ContainerModel::appendLesson(const QModelIndex& parent, const QString & lessonName)
{
    if (m_container->containerType() == KEduVocContainer::Lesson) {
        KEduVocLesson* parentLesson;
        if (parent.isValid()) {
            parentLesson = static_cast<KEduVocLesson*>(parent.internalPointer());
        } else {
            parentLesson = static_cast<KEduVocLesson*>(m_container);
        }

kDebug() << "Append child lesson to: " << parentLesson->name() << " new lesson name: " << lessonName;

        beginInsertRows(parent, parentLesson->childContainerCount(), 
            parentLesson->childContainerCount() );

        parentLesson->appendChildContainer(new KEduVocLesson(lessonName, parentLesson));
        endInsertRows();

        return index(parentLesson->childContainerCount() - 1, 0, parent);
    }

    return QModelIndex();
}

// 
// void ContainerModel::setAllLessonsInPractice()
// {
//     for (int lesson = 0; lesson < m_doc->lessonCount(); lesson++) {
//         m_doc->lesson(lesson).setInPractice(true);
//     }
// 
//     // this is not too great - say all data has changed
//     emit dataChanged(index(0, 0, QModelIndex()), index(rowCount(), 0, QModelIndex()));
//     //emit signalLessonsInPracticeChanged(intLessons);
// }


// void ContainerModel::setNoLessonsInPractice()
// {
//     for (int lesson = 0; lesson < m_doc->lessonCount(); lesson++) {
//         m_doc->lesson(lesson).setInPractice(false);
//     }
// 
//     // this is not too great - say all data has changed
//     emit dataChanged(index(0, 0, QModelIndex()), index(rowCount(), 0, QModelIndex()));
//     //emit signalLessonsInPracticeChanged(intLessons);
// }


// bool ContainerModel::removeRows(int row, int count, const QModelIndex &parent)
// {
//     Q_UNUSED(parent);
//     /// @todo either really use this or remove it
//     beginRemoveRows(QModelIndex(), row, row);
//     endRemoveRows();
// 
//     // to support drag and drop
//     kDebug() << "removeRows(int row, int count, const QModelIndex &parent)" << row << ", " << count;
//     return true;
// }


void ContainerModel::splitLesson(const QModelIndex& containerIndex, int entriesPerLesson, SplitLessonOrder order)
{
    if (!containerIndex.isValid()) {
        return;
    }

    if (!static_cast<KEduVocContainer*>(containerIndex.internalPointer())->containerType() == KEduVocContainer::Lesson) {
        return;
    }

    KEduVocLesson* parentLesson = static_cast<KEduVocLesson*>(containerIndex.internalPointer());

    int numNewLessons = parentLesson->entryCount() / entriesPerLesson;
    // modulo - fraction lesson if not 0 we need one more
    if (parentLesson->entryCount()%entriesPerLesson) { 
        numNewLessons++;
    }

    while (parentLesson->entryCount() > 0) {
        beginInsertRows(containerIndex, parentLesson->entryCount(), parentLesson->entryCount() );
        KEduVocLesson* child = new KEduVocLesson(parentLesson->name()
            + QString(" %1").arg(parentLesson->childContainerCount() + 1), parentLesson);
        parentLesson->appendChildContainer(child);
        endInsertRows();

        // number entries in the lesson that is being filled
        int entries = 0;
        while (parentLesson->entryCount() > 0 && child->entryCount() < entriesPerLesson) {
            // next entry to be assigned to one of the new lessons
            int nextEntry=0;
            if (order == Random) {
                nextEntry = KRandom::random() % parentLesson->entryCount();
                child->addEntry(parentLesson->entry(nextEntry));
                parentLesson->removeEntry(parentLesson->entry(nextEntry));
            }
        }
    }
}


QVariant ContainerModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid()) {
         return QVariant();
    }

    KEduVocContainer *container = static_cast<KEduVocContainer*>(index.internalPointer());

    switch (index.column()){
    case 0:
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return container->name();
        }
        // checkboxes
        if (role == Qt::CheckStateRole) {
            if (container->inPractice())
                return Qt::Checked;
            else
                return Qt::Unchecked;
        }
//         if (role == Qt::DecorationRole) {
//             return KIcon("favorites");
//         }
        if (role == Qt::TextAlignmentRole) {
            return Qt::AlignLeft;
        }
    case 1:
        if (role == Qt::DisplayRole) {
            return container->entriesRecursive().count();
        }
        if (role == Qt::TextAlignmentRole) {
            return Qt::AlignRight;
        }
    }

    return QVariant();
}


bool ContainerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if ( index.column() == 0 ) {
        KEduVocContainer *container = static_cast<KEduVocContainer*>(index.internalPointer());
        // rename a lesson
        if (role == Qt::EditRole) {
            container->setName(value.toString());
            emit documentModified();
            return true;
        }

        // checkboxes
        if (role == Qt::CheckStateRole) {
            if (!container->inPractice()) {
                container->setInPractice(true);
            } else {
                container->setInPractice(false);
            }
            emit documentModified();
            return true;
        }
    }
    return false;
}


Qt::ItemFlags ContainerModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        // the root element, not editable for now
        if ( index.column() == 0 && index.parent() == QModelIndex()) {
            return (Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsUserCheckable);
        }
        // every other element
        if ( index.column() == 0 ) {
            return (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
                    | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled );
        }
    }
    return  Qt::ItemIsDropEnabled;
}


QVariant ContainerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // statically two columns for now
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            if(role == Qt::DisplayRole) {
                return i18n("Lesson");
            }

        case 1:
            if(role == Qt::DisplayRole) {
                return QVariant();
            }
            if(role == Qt::ToolTipRole) {
                return i18n("Number of entries in this lesson.");
            }
        }
    }
    return QVariant();
}


int ContainerModel::columnCount(const QModelIndex & parent) const
{
    if(!m_container) {
        return 0;
    }

    return 2;
}


void ContainerModel::deleteLesson(const QModelIndex & lessonIndex)
{
    KEduVocContainer* lesson = static_cast<KEduVocContainer*>(lessonIndex.internalPointer());
    KEduVocContainer* parent = lesson->parent();

///@todo delete children???

    beginRemoveRows(lessonIndex.parent(), lessonIndex.row(), lessonIndex.row());
    parent->deleteChildContainer(lesson->row());
    endRemoveRows();
}


KEduVocContainer::EnumContainerType ContainerModel::containerType()
{
    if (m_container) {
        return m_container->containerType();
    }
    return KEduVocContainer::Container;
}

Qt::DropActions ContainerModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

QStringList ContainerModel::mimeTypes() const
{
    return QStringList() << "text/plain";
}


QMimeData * ContainerModel::mimeData(const QModelIndexList &indexes) const
{
     ContainerMimeData *mimeData = new ContainerMimeData();
//      QByteArray encodedData;

    foreach (QModelIndex index, indexes) {
        mimeData->addContainer(static_cast<KEduVocContainer*>(index.internalPointer()));
    }
    mimeData->setText("Parley lesson");

//      QDataStream stream(&encodedData, QIODevice::WriteOnly);
// stream << "Parley lesson";
//      foreach (QModelIndex index, indexes) {
//          if (index.isValid()) {
//              QString text = data(index, Qt::DisplayRole).toString();
//              stream << text;
//          }
//      }
// // kDebug() << "mimeData:" << encodedData;
//      mimeData->setData("text/plain", encodedData);
    return mimeData;
}


bool ContainerModel::dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent)
{
    if (action == Qt::IgnoreAction) {
         return true;
    }

    // if it's internal, get the pointers
    const ContainerMimeData * lessonData =
             qobject_cast<const ContainerMimeData *>(data);


    if (lessonData) {
        foreach (KEduVocContainer* container, lessonData->containerList()) {
            // no way to move a word type to a lesson for now
            if (container->containerType() != m_container->containerType()) {
                return false;
            }

            if (action == Qt::MoveAction || action == Qt::CopyAction) {
//                 container->parent();
                kDebug() << "Move container: " << container->name();
                KEduVocContainer* parentContainer;

                if (parent.isValid()) {
                    parentContainer = static_cast<KEduVocContainer*>(parent.internalPointer());
                } else {
                    parentContainer = m_container;
                }

                QModelIndex oldParent = index(container->parent());

// removeRows(row, 1, oldParent);

                beginRemoveRows(oldParent, container->row(), container->row());
                container->parent()->removeChildContainer(container->row());
                endRemoveRows();

                // if we get to choose, append seems sane.
                if (row < 0) {
                    row = parentContainer->childContainerCount();
                }

                beginInsertRows(parent, row, row);
                parentContainer->insertChildContainer(row, container);
                endInsertRows();

                return true;
            }
        }
    }


    // if it's a translation, get the pointers
    const VocabularyMimeData * translationData =
             qobject_cast<const VocabularyMimeData *>(data);

    if (translationData) {
        if(!parent.isValid()) {
            return false;
        }
        if (containerType() == KEduVocContainer::Lesson) {
            foreach (KEduVocTranslation* translation, translationData->translationList()) {
                static_cast<KEduVocLesson*>(parent.internalPointer())->addEntry(translation->entry());
            }
        }

        if (containerType() == KEduVocContainer::WordType) {
            foreach (KEduVocTranslation* translation, translationData->translationList()) {
                translation->setWordType(
                    static_cast<KEduVocWordType*>(parent.internalPointer()));
            }
        }
        return false;
    }


    kDebug() << data->formats();
/*
    if (data->hasText()) {
        if (action == Qt::CopyAction | action == Qt::MoveAction) {
            QString name;
            name = data->text();
            kDebug() << "Copy lesson " << name;

            appendLesson(parent, name);
            
            return true;
        }
    }*/

    return false;
}


bool ContainerModel::removeRows(int row, int count, const QModelIndex & parent)
{
    KEduVocContainer* parentContainer;
    if (!parent.internalPointer()) {
        parentContainer = m_container;
    } else {
        parentContainer = static_cast<KEduVocContainer*>(parent.internalPointer());
    }
kDebug() << "removeRows from " << parentContainer->name() << " row " << row << "count" << count;

    beginRemoveRows ( parent, row, row+count );
    for (int i = 0; i<count; i++) {
        parentContainer->removeChildContainer(row);
    }
    endRemoveRows();

    return true;
}

bool ContainerModel::insertRows(int row, int count, const QModelIndex & parent)
{
    Q_ASSERT(parent.internalPointer());
    kDebug() << "" << static_cast<KEduVocContainer*>(parent.internalPointer())->name();
    return false;
}



#include "containermodel.moc"


