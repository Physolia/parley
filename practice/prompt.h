//
// C++ Interface: prompt
//
// Description: The prompt displays the question portion or original translation of an entry
///\file prompt.h
//
// Author: David Capel <wot.narg@gmail.com>, (C) 2008
//

/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/


#ifndef PROMPT_H
#define PROMPT_H

#include <QString>
#include <QLabel>
#include <QPicture>

#include <KUrl>
#include <KSvgRenderer>
#include <QGraphicsTextItem>

class TextualPrompt : public QGraphicsTextItem
{
        Q_OBJECT

    public:
        TextualPrompt(KSvgRenderer * renderer);

    public slots:
        void slotSetText(const QString& text);
    private:
        KSvgRenderer * m_renderer;
        QRectF m_backgroundRect;
};

class SoundPrompt : public QLabel
{
        Q_OBJECT


    public:
        SoundPrompt(KSvgRenderer * renderer, QWidget * parent = 0);

    public slots:
        void slotSetSound(const KUrl& sound) { m_sound = sound; };
    private:
        KUrl m_sound;
        KSvgRenderer * m_renderer;
        QRectF m_backgroundRect;
};

class ImagePrompt : public QLabel
{
        Q_OBJECT


    public:
        ImagePrompt(KSvgRenderer * renderer, QWidget * parent = 0);

    public slots:

        void slotSetImage(const KUrl& image);

    private:
        QPicture m_pic;
        KSvgRenderer * m_renderer;
        QRectF m_backgroundRect;
};


#endif

