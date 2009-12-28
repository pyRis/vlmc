/*****************************************************************************
 * GreenFilterEffect.cpp: test effect module, just for apply a green filter
 *****************************************************************************
 * Copyright (C) 2008-2009 the VLMC team
 *
 * Authors: Vincent Carrubba <cyberbouba@gmail.com>
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

#include "GreenFilterEffect.h"
#include <QtDebug>
#include <QTime>

char const * 	GreenFilterEffect::m_videoInputsNames[] = {"in"};
char const *	GreenFilterEffect::m_videoOutputsNames[] = {"out"};

GreenFilterEffect::GreenFilterEffect() : GenericEffect(
                       GreenFilterEffect::m_videoInputsNames, GreenFilterEffect::m_nbVideoInputs,
                       GreenFilterEffect::m_videoOutputsNames, GreenFilterEffect::m_nbVideoOutputs
                       ),
                                         m_logo(QImage(QImage(":/images/images/vlmc.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation)).rgbSwapped()),
                     m_enabled( true )
{
};

GreenFilterEffect::~GreenFilterEffect()
{
}

void    GreenFilterEffect::render( void )
{
    quint32		i;
    LightVideoFrame	tmp;

    ( m_videoInputs[0] ) >> tmp;
    if (tmp->frame.octets != NULL)
    {
        if (m_enabled)
      {
        QImage		img(tmp->frame.octets, 640, 480, QImage::Format_RGB888);
        QPainter		painter(&img);

        painter.setRenderHint( QPainter::Antialiasing );
        painter.drawImage(530, 380, m_logo);

        painter.setFont( QFont( "verdana", 15, QFont::Bold ) );
        painter.drawText( 500, 50, QTime::currentTime().toString( "HH:mm:ss" ) );

        //	    pouet.fillRect(30, 30, 100, 100, Qt::blue);
      }
//             for ( i = 0; i < tmp->nbpixels; ++i )
//             {
//                 tmp->frame.pixels[i].Red = 0;
//                 tmp->frame.pixels[i].Blue = 0;
//             }
    }
    (m_videoOutputs[0]) << tmp;
    return ;
}

void	GreenFilterEffect::enable( void )
{
  m_enabled = true;
  return ;
}

void	GreenFilterEffect::disable( void )
{
  m_enabled = false;
  return ;
}
