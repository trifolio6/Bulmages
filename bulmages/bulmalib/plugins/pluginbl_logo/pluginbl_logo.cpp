/*******************************************f********************************
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

#ifndef WIN32


#include <stdio.h>

#include <QAction>
#include <QMessageBox>
#include <QStringList>
#include <QWidget>
#include <QIcon>
#include <QApplication>
#include <QObject>
#include <QProcess>
#include <QTextStream>

#include "local_BlI18n.h"
#include "pluginbl_logo.h"
#include "bfbulmafact.h"
#include "bcbulmacont.h"
#include "bldockwidget.h"
#include "blworkspace.h"
#include "blform.h"

QMainWindow *g_bges = NULL;
BlMainCompany *g_emp = NULL;




int entryPoint ( BlMainWindow *bges )
{
    blDebug ( "Entrada del plugin Docket", 0 );

    /// Inicializa el sistema de traducciones 'gettext'.
    setlocale ( LC_ALL, "" );
    bindtextdomain ( "pluginbl_logo", g_confpr->valor ( CONF_DIR_TRADUCCION ).toAscii().constData() );

    g_bges = bges;


    blDebug ( "myplugincont::elslot", 0 );

    /// Vamos a probar con un docwindow.
    BlDockWidget *doc1 = new BlDockWidget ( _("Logotipo"), g_main );
    doc1->setWindowIcon ( QIcon ( QString::fromUtf8 ( ":/BulmaCont32x32/images/png/i_lo32-app-bulmages.png" ) ) );

    doc1->setFeatures ( QDockWidget::AllDockWidgetFeatures );

    doc1->setGeometry ( 100, 100, 100, 500 );
    doc1->resize ( 330, 400 );
    g_main->addDockWidget ( Qt::LeftDockWidgetArea, doc1 );

    QLabel *label = new QLabel(g_main);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("first line\nsecond line");
    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    label->setPixmap(QPixmap(g_confpr->valor(CONF_DIR_OPENREPORTS) + "logo.jpg"));
    
     doc1->setWidget ( label );

     doc1->show();
    doc1->cargaconf();
    
    blDebug ( "END myplugincont::elslot", 0 );

    return 0;
}



#endif
