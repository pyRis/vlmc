/*****************************************************************************
 * Preferences.cpp: Preferences window
 *****************************************************************************
 * Copyright (C) 2008-2009 the VLMC team
 *
 * Authors: Christophe Courtaut <christophe.courtaut@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include "LanguagePreferences.h"
#include "ui_LanguagePreferences.h"

QTranslator* Preferences::m_currentLang = NULL;
Preferences* Preferences::m_instance = NULL;

Preferences::Preferences( QWidget *parent ) : QDialog( parent )
{
    m_ui.setupUi( this );
    m_ui.comboBoxLanguage->addItem( tr( "English" ), "" );
    m_ui.comboBoxLanguage->addItem( tr( "French" ), "fr" );
    m_ui.comboBoxLanguage->addItem( tr( "Spanish" ), "es" );
    m_ui.comboBoxLanguage->addItem( tr( "Swedish" ), "sv" );
    connect( qApp, SIGNAL( aboutToQuit() ), this, SLOT( deleteLater() ) );
}

void Preferences::changeEvent( QEvent *e )
{
    QWidget::changeEvent( e );
    switch ( e->type() )
    {
    case QEvent::LanguageChange:
        m_ui.retranslateUi( this );
        break;
    default:
        break;
    }
}

Preferences* Preferences::instance()
{
    if ( m_instance )
        return m_instance;
    m_instance = new Preferences();
    return m_instance;
}

void Preferences::on_pushButtonCancel_clicked()
{
    close();
}

void Preferences::on_pushButtonApply_clicked()
{
    Preferences::changeLang( m_ui.comboBoxLanguage->itemData( m_ui.comboBoxLanguage->currentIndex() ).toString() );
    close();
}

void Preferences::changeLang( QString langValue )
{
    QSettings settings;
    QString lang = settings.value( "Lang" ).toString();
    settings.setValue( "Lang", langValue);
    if ( m_currentLang != NULL )
    {
        qApp->removeTranslator( m_currentLang );
        delete m_currentLang;
        m_currentLang = NULL;
    }
    if ( !langValue.isEmpty() )
    {
        m_currentLang = new QTranslator();
        m_currentLang->load( langValue, ":/Lang/" );
        qApp->installTranslator( m_currentLang );
    }
}