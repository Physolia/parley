/***************************************************************************

                    base class for query dialogs

    -----------------------------------------------------------------------

    begin          : Wed Feb 16 20:50:53 MET 2000

    copyright      : (C) 1999-2001 Ewald Arnold <kvoctrain@ewald-arnold.de>
                     (C) 2005, 2007 Peter Hedlund <peter.hedlund@kdemail.net>

    -----------------------------------------------------------------------

 ***************************************************************************

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "practicedialog.h"
#include "entry-dialogs/EntryDlg.h"
#include <KLocale>
#include <Phonon/MediaObject>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QCloseEvent>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsItem>

PracticeDialog::PracticeDialog(const QString & caption, KEduVocDocument *doc, QWidget *parent) : KDialog(parent)
{
    setCaption(caption);
    setModal(false);
    setButtons(0);
    setDefaultButton(NoDefault);

    QWidget *main = new QWidget(this);
    setMainWidget(main);

    m_doc = doc;
    m_entry = 0;
    m_timer = 0;

    m_player = 0;
}


PracticeDialog::~PracticeDialog()
{
    if ( m_player ) {
        m_player->deleteLater();
    }
}


bool PracticeDialog::smartCompare(const QString& s1, const QString &s2) const
{
    return s1.simplified() == s2.simplified();
}


/**
 * Compare the text of a lineedit with a string, set the lineedits colors to red/green if wrong/right.
 * @param field the lineEdit
 * @param really the solution
 * @return solution is right
 */
bool PracticeDialog::verifyField(QLineEdit *field, const QString &really)
{
    /** @todo the colors should not be hard coded here. */
    if (!field->isEnabled())
        return true;

    if (smartCompare(really, field->text())) {  // answer was right - green text
        setWidgetTextColorAndFontWeight(field, QColor(0x00, 0x80, 0x00), QFont::Bold);
        return true;
    }
    // wrong - red text
    setWidgetTextColorAndFontWeight(field, QColor(0xff, 0x00, 0x00), QFont::Bold);
    return false;  // right/wrong
}


/**
 * Set text to black, font not bold.
 * @param widget
 */
void PracticeDialog::resetQueryWidget(QWidget *w)
{
    if (!w->isEnabled()) {
        return;
    }
    // set black text and normal font
    setWidgetTextColorAndFontWeight(w, QColor(0x00, 0x00, 0x00), QFont::Normal);
}


void PracticeDialog::verifyButton(QRadioButton *radio, bool is_ok, QWidget *widget2)
{
    if (!radio->isEnabled())
        return;

    if (is_ok) {
        setWidgetTextColorAndFontWeight(radio, QColor(0x00, 0x80, 0x00), QFont::Bold);
        if (widget2 != 0) {
            setWidgetTextColorAndFontWeight(widget2, QColor(0x00, 0x80, 0x00), QFont::Bold);
        }
    } else {
        setWidgetTextColorAndFontWeight(radio, QColor(0xff, 0x00, 0x00), QFont::Bold);
        if (widget2 != 0) {
            setWidgetTextColorAndFontWeight(widget2, QColor(0xff, 0x00, 0x00), QFont::Bold);
        }
    }
}


QString  PracticeDialog::getOKComment(int percent_done)
{
    return i18n("Well done, you knew the correct answer. %1% done.", percent_done);
}


QString  PracticeDialog::getTimeoutComment(int percent_done)
{
    return i18n("You waited too long to enter the correct answer. %1% done.", percent_done);
}


QString  PracticeDialog::getNOKComment(int percent_done)
{
    return i18n("Your answer was wrong. %1% done.", percent_done);
}


void PracticeDialog::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);
    emit sigQueryChoice(StopIt);
}


void PracticeDialog::setWidgetTextColorAndFontWeight(QWidget *widget, const QColor &color, QFont::Weight QFontWeight)
{
    QPalette qp = QPalette(widget->palette());
    qp.setColor(QPalette::Active, QPalette::Text, color);
    qp.setColor(QPalette::Inactive, QPalette::Text, color);
    qp.setColor(QPalette::Active, QPalette::WindowText, color);
    qp.setColor(QPalette::Inactive, QPalette::WindowText, color);
    widget->setPalette(qp);

    QFont ft = widget->font();
    ft.setWeight(QFontWeight);
    widget->setFont(ft);
}


void PracticeDialog::timeoutReached()
{
    // update every second, count down m_timerCount
    if (m_timerCount > 0) {
        m_timerCount--;
        timebar()->setValue(m_timerCount);
        m_timer->start(1000);
    }

    if (m_timerCount <= 0) {
        timebar()->setValue(0);
        if (Prefs::queryTimeout() == Prefs::EnumQueryTimeout::Show) {
            showSolution();
        } else if (Prefs::queryTimeout() == Prefs::EnumQueryTimeout::Continue) {
            emit sigQueryChoice(Timeout);
        }
    }
}


void PracticeDialog::startTimer()
{
    if (Prefs::queryTimeout() == Prefs::EnumQueryTimeout::NoTimeout) {
        kDebug() << "Prefs::queryTimeout() == Prefs::EnumQueryTimeout::NoTimeout ->NO TIMEOUT!";
        return;
    }

    int mqtime = Prefs::maxTimePer();
    if (mqtime > 0) {
        if (m_timer == 0) {
            m_timer = new QTimer(this);
            m_timer->setSingleShot(true);
            connect(m_timer, SIGNAL(timeout()), this, SLOT(timeoutReached()));
        }

        if (Prefs::queryTimeout() != Prefs::EnumQueryTimeout::NoTimeout) {
            m_timerCount = mqtime;
            timebar()->setMaximum(m_timerCount);
            timebar()->setValue(m_timerCount);
            m_timer->start(1000);
        } else
            timebar()->setEnabled(false);
    } else {
        timebar()->setEnabled(false);
    }
}

void PracticeDialog::setEntry(TestEntry * entry)
{
    m_entry = entry;
    m_testType = Prefs::testType();
    startTimer();
//     audioPlayFromIdentifier();
}

void PracticeDialog::editEntry()
{
    if (m_timer != 0) {
        m_timer->stop();
    }

    EntryDlg* entryDlg = new EntryDlg(0 , m_doc);

    QList<int> entry;
    entry.append(m_entry->m_index);
    entryDlg->setData(entry, Prefs::toIdentifier());
    entryDlg->exec();

    // punish with a don't know
    kDebug() << "Edit entry. For now count this attempt as wrong!";
    emit sigQueryChoice(Wrong);
}

void PracticeDialog::skipKnown()
{
    emit sigQueryChoice(SkipKnown);
}

void PracticeDialog::skipUnknown()
{
    emit sigQueryChoice(SkipUnknown);
}

void PracticeDialog::resultCorrect()
{
    audioPlayCorrect();
//     emit sigQueryChoice(Correct);
}

void PracticeDialog::resultWrong()
{
    emit sigQueryChoice(Wrong);
}

void PracticeDialog::audioPlayFromIdentifier()
{
    QString file = m_entry->exp->translation(Prefs::fromIdentifier()).soundUrl().url();
    if ( !file.isEmpty() ) {
        audioPlayFile(file);
    }
}

void PracticeDialog::audioPlayToIdentifier()
{
    QString file = m_entry->exp->translation(Prefs::toIdentifier()).soundUrl().url();
    if ( !file.isEmpty() ) {
        audioPlayFile(file);
    }
}

void PracticeDialog::audioPlayFile(const QString & soundFile)
{
    kDebug() << "Attempting to play sound: " << soundFile;
    if (!m_player)
    {
        kDebug() << "Creating Phonon player...";
        m_player = Phonon::createPlayer(Phonon::NotificationCategory, soundFile);
        m_player->setParent(this);
    } else {
        m_player->setCurrentSource(soundFile);
//         m_player->enqueue(soundFile);
    }
    m_player->play();
}


void PracticeDialog::audioPlayCorrect()
{
    KUrl soundFile = m_entry->exp->translation(Prefs::toIdentifier()).soundUrl();
    if ( !soundFile.isEmpty() ) {
        if (!m_player)
        {
            kDebug() << "Creating Phonon player...";
            m_player = Phonon::createPlayer(Phonon::NotificationCategory, soundFile);
            m_player->setParent(this);
        } else {
            m_player->setCurrentSource(soundFile);
        }
        connect(m_player, SIGNAL(finished()), this, SLOT(emitCorrect()));
        m_player->play();
        kDebug() << "Play sound: " << soundFile;
    } else {
//         QTimer::singleShot(2000, this, SLOT(emitCorrect()));
        emitCorrect();
    }
}

void PracticeDialog::emitCorrect()
{
kDebug() << "Correct";
    emit sigQueryChoice(Correct);
}

void PracticeDialog::imageShowFile(QGraphicsView * view, const QString & url)
{
    kDebug() << "show image:" << url;
    if ( !view->scene() ) {
        view->setScene(new QGraphicsScene());
    }

    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(QPixmap(url));

    qreal scale = qMin(view->width()/pixmapItem->boundingRect().width(), view->height()/pixmapItem->boundingRect().height());

    pixmapItem->scale( scale, scale );

    pixmapItem->translate( -pixmapItem->boundingRect().width()/2.0, -pixmapItem->boundingRect().height()/2.0 );

    foreach ( QGraphicsItem* item, view->scene()->items() ) {
        view->scene()->removeItem(item);
        delete item;
    }
    view->scene()->setSceneRect( 0.0, 0.0, 1.0, 1.0 );
    view->scene()->addItem(pixmapItem);
}

void PracticeDialog::imageShowFromEntry(QGraphicsView * view, const TestEntry * entry)
{
    if ( Prefs::practiceImagesEnabled() ) {
        QString url = entry->exp->translation(Prefs::fromIdentifier()).imageUrl().toLocalFile();
        if ( url.isEmpty() ) {
            url = entry->exp->translation(Prefs::toIdentifier()).imageUrl().toLocalFile();
        }
        if ( url.isEmpty() ) {
            view->setVisible(false);
        } else {
            view->setVisible(true);
            imageShowFile( view, url );
        }
    }
}

#include "practicedialog.moc"

