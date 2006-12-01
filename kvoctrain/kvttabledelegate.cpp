//
// C++ Implementation: kvttabledelegate
//
// Description: 
//
//
// Author:  (C) 2006 Peter Hedlund <peter.hedlund@kdemail.net>
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <QtGui>

#include "kdebug.h"
#include <kglobalsettings.h>
#include <klocale.h>

#include "kvttabledelegate.h"
#include "kvttablemodel.h"

KVTTableDelegate::KVTTableDelegate(QObject *parent) : QItemDelegate(parent)
{
}

QWidget * KVTTableDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  if (!index.isValid())
    return 0;

  switch (index.column()) {
    case 0:
    {
      QComboBox *lessonbox = new QComboBox(parent);
      lessonbox->setFrame(false);
      lessonbox->setFont(KGlobalSettings::generalFont());
      connect(lessonbox, SIGNAL(returnPressed()), this, SLOT(commitAndCloseEditor()));
      return lessonbox;
    }
    break;

    case 1:
    {
      QComboBox *statebox = new QComboBox(parent);
      statebox->setFrame(false);
      statebox->setFont(KGlobalSettings::generalFont());
      connect(statebox, SIGNAL(returnPressed()), this, SLOT(commitAndCloseEditor()));
      return statebox;
    }
    break;

    default:
    {
      QLineEdit *editor = new QLineEdit(parent);
      editor->setFrame(false);
      editor->setFont(index.model()->data(index, Qt::FontRole).value<QFont>());
      connect(editor, SIGNAL(returnPressed()), this, SLOT(commitAndCloseEditor()));
      return editor;
    }
  }
}


void KVTTableDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
  if (!index.isValid())
    return;

  switch (index.column()) {
    case 0:
    {
      QStringList sl = index.model()->data(index, LessonsRole).toStringList();
      QComboBox *lessonbox = static_cast<QComboBox*>(editor);
      lessonbox->addItem(i18n("<no lesson>"));
      for (unsigned i = 0; i < (unsigned) sl.count(); ++i)
        lessonbox->addItem (sl[i]);
      lessonbox->setCurrentIndex(index.model()->data(index, LessonRole).toInt());
    }
    break;

    case 1:
    {
      QComboBox *statebox = static_cast<QComboBox*>(editor);
      statebox->addItem (i18nc("state of a row", "Active, Not in Query"));
      statebox->addItem (i18nc("state of a row", "In Query"));
      statebox->addItem (i18nc("state of a row", "Inactive"));
      statebox->setCurrentIndex(index.model()->data(index, StateRole).toInt());
    }
    break;

    default:
    {
      QString value = index.model()->data(index, Qt::DisplayRole).toString();

      if (value == "@empty@")
        value = "";

      QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
      lineEdit->setText(value);
    }
  }
}

void KVTTableDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
  if (!index.isValid())
    return;

  switch (index.column()) {
    case 0:
    {
      QComboBox *lessonbox = static_cast<QComboBox*>(editor);
      int value = lessonbox->currentIndex();
      model->setData(index, value);
    }
    break;

    case 1:
    {
      QComboBox *statebox = static_cast<QComboBox*>(editor);
      int value = statebox->currentIndex();
      model->setData(index, value);
    }
    break;

    default:
    {
      QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
      QString value = lineEdit->text();
      model->setData(index, value);
    }
  }
}

void KVTTableDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  if (index.column() == 1)
  {
    /// @todo a better way to calculate the width of this combobox?
    //QSize sz = editor->sizeHint();
    QRect r = option.rect;
    //sz.setHeight(option.rect.height());
    r.setWidth(150);
    editor->setGeometry(r);
  }
  else
    editor->setGeometry(option.rect);
}

void KVTTableDelegate::commitAndCloseEditor()
{
  QWidget *editor = qobject_cast<QWidget *>(sender());
  kDebug() << "Committing and closing\n";
  emit commitData(editor);
  emit closeEditor(editor, QAbstractItemDelegate::NoHint);
}

void KVTTableDelegate::drawDisplay(QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect, const QString & text) const
{
  QPen pen = painter->pen();
  QPalette::ColorGroup cg = option.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;
  if (option.state & QStyle::State_Selected) {
      painter->fillRect(rect, option.palette.brush(cg, option.state & QStyle::State_HasFocus ?
        QPalette::Base : QPalette::Highlight));
      painter->setPen(option.palette.color(cg, option.state & QStyle::State_HasFocus ?
        QPalette::Text : QPalette::HighlightedText));
  } else {
      painter->setPen(option.palette.color(cg, QPalette::Text));
  }

  if (option.state & QStyle::State_Editing) {
      painter->save();
      painter->setPen(option.palette.color(cg, QPalette::Text));
      painter->drawRect(rect.adjusted(0, 0, -1, -1));
      painter->restore();
  }

  QFont font = painter->font();
  painter->setFont(option.font);
  QRect textRect = rect.adjusted(3, 0, -3, 0); // remove width padding
  QString str = text;
  if (str == "@empty@")
    str = "";

  if (painter->fontMetrics().width(text) > textRect.width() && !text.contains(QLatin1Char('\n')))
      str = elidedText(option.fontMetrics, textRect.width(), option.textElideMode, text);

  painter->drawText(textRect, option.displayAlignment, str);
  painter->setFont(font);
  painter->setPen(pen);
}

void KVTTableDelegate::drawFocus(QPainter * painter, const QStyleOptionViewItem & option, const QRect & rect) const
{
  if (option.state & QStyle::State_HasFocus) {
    painter->save();
    QPen pen = painter->pen();
    pen.setColor(Qt::black);
    pen.setWidth(0);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect.adjusted(0,0,-1,-1));
    painter->drawRect(rect.adjusted(1,1,-2,-2));
    painter->restore();
  }
}

QSize KVTTableDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  return QSize(300, 25);
}

void KVTTableDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  QItemDelegate::paint(painter, option, index);
}

#include "kvttabledelegate.moc"
