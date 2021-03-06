/***************************************************************************
 *   Copyright (C) 2010 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "pluginbt_teclado.h"

#include "bltoolbutton.h"

#include "btcompany.h"
#include "blplugins.h"
#include "btticket.h"
#include "bldockwidget.h"
#include "blapplication.h"
#include "blfunctions.h"
#include "blmainwindow.h"
#include "blplugins.h"

#include <QHBoxLayout>
#include <QToolButton>
#include <QProcess>
#include <QDockWidget>
#ifndef Q_OS_WIN32
#include <QX11EmbedContainer>
#endif


QDockWidget *g_docteclado = NULL;
QProcess *g_proc = NULL;

///
/**
\return
**/
int entryPoint ( BtBulmaTPV *tpv )
{
    BL_FUNC_DEBUG

    /// Inicializa el sistema de traducciones 'gettext'.
    setlocale ( LC_ALL, "" );
    blBindTextDomain ( "pluginbt_teclado", g_confpr->value( CONF_DIR_TRADUCCION ).toAscii().constData() );

    
    return 0;
}



int BtCompany_createMainWindows_Post ( BtCompany *etpv )
{
  
      /// Creamos un docwindow.
    g_docteclado = new QDockWidget ( "Teclado", g_main );
    g_docteclado->setFeatures ( QDockWidget::AllDockWidgetFeatures );
    g_main->addDockWidget ( Qt::TopDockWidgetArea, g_docteclado );
    g_docteclado->hide();

    g_proc = new QProcess();
    

    /// Hay varios teclados embebidos que se pueden utilizar. Pero el que mejor funciona
    /// Es el matchbox-keyboard
/*
        g_proc->start("kvkbd");
        if (!g_proc->waitForStarted())
            return;
        QString winId = "";
        while (winId == "") winId = blWindowId("kvkbd");
*/


    /*
            g_proc->start("klavier");
            if (!g_proc->waitForStarted())
                return;
            QString winId = "";
            while (winId == "") winId = blWindowId("klavier");
    */


    g_proc->start ( "matchbox-keyboard -xid es" );
    if ( !g_proc->waitForStarted() ) {
        return 0;
    } // end if
    g_proc->waitForReadyRead();
    QString winId = "";
    winId = g_proc->readAllStandardOutput();


#ifndef Q_OS_WIN32

    QX11EmbedContainer *container = new QX11EmbedContainer ( g_docteclado );
    container->embedClient ( winId.toInt() );
    g_docteclado->setWidget ( container );

#endif

  


    BlToolButton *boton_teclado = new BlToolButton(etpv, etpv);

        boton_teclado->setObjectName(QString::fromUtf8("mui_teclado"));
        boton_teclado->setMinimumSize(QSize(72, 72));
        boton_teclado->setMaximumSize(QSize(200, 72));
        boton_teclado->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/company.png"), QSize(), QIcon::Normal, QIcon::Off);
        boton_teclado->setIcon(icon);
        boton_teclado->setIconSize(QSize(32, 32));
        boton_teclado->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        boton_teclado->setText(N_("Teclado", 0));

    QFrame *fr = g_main->findChild<QFrame *> ( "mui_frameabrevs" );
    if ( fr ) {
        QHBoxLayout *m_hboxLayout1 = fr->findChild<QHBoxLayout *> ( "hboxLayout1" );
        if ( !m_hboxLayout1 ) {
            m_hboxLayout1 = new QHBoxLayout ( fr );
            m_hboxLayout1->setSpacing ( 5 );
            m_hboxLayout1->setMargin ( 5 );
            m_hboxLayout1->setObjectName ( QString::fromUtf8 ( "hboxLayout1" ) );
        } // end if
	m_hboxLayout1->addWidget (boton_teclado);
    } // end if



    return 0;
}


///
/**
\return
**/
int exitPoint ( BtBulmaTPV *tpv )
{
    BL_FUNC_DEBUG

    /// Vamos a probar con un docwindow.
    g_proc->kill();
    delete g_proc;
    delete g_docteclado;
    
    return 0;
}

int BlToolButton_released(BlToolButton *bot) {
  if (bot->objectName() == "mui_teclado") {
    if ( g_docteclado->isVisible() ) {
        g_docteclado->hide();
    } else {
        g_docteclado->show();
    }// end if
  } //end if
  return 0;
}
