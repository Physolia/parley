/***************************************************************************
    Copyright 2008 Daniel Laidig <d.laidig@gmx.de>
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QStyledItemDelegate>

#include <QPoint>

class WelcomeScreen;
class QToolButton;

class ButtonDelegate
    : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ButtonDelegate(QAbstractItemView *itemView, WelcomeScreen *parent);

    virtual ~ButtonDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QModelIndex hoveredIndex() const;

public slots:
    void slotEdit();
    void slotPractice();

private:
    int m_rightMargin;
    int m_buttonHeight;
    WelcomeScreen *m_welcomeScreen;
    QAbstractItemView *m_itemView;
    QToolButton *m_editButton;
};

#endif //BUTTONDELEGATE_H
