/*****************************************************************************
 * LightVideoFrame.cpp: class used to contains raw video frame, with
 * copy-on-write and references conter mecanism for performance and avoiding
 * memory leak
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

#include "LightVideoFrame.h"

VideoFrame::~VideoFrame()
{
  if ( frame.octets != NULL )
    delete [] frame.octets;
};

VideoFrame::VideoFrame()
{
  frame.octets = NULL;
  nboctets = 0;
  nbpixels = 0;
}

VideoFrame::VideoFrame(VideoFrame const & tocopy) : QSharedData( tocopy )
{
  if ( tocopy.frame.octets != NULL )
    {
      quint32	i;

      nboctets = tocopy.nboctets;
      nbpixels = tocopy.nboctets / Pixel::NbComposantes;
      frame.octets = new quint8[tocopy.nboctets];

      for ( i = 0; i < nboctets; ++i )
	frame.octets[i] = tocopy.frame.octets[i];
    }
  else
    {
      nboctets = 0;
      nbpixels = 0;
      frame.octets = NULL;
    }
}

//
//
//
//
//

LightVideoFrame::LightVideoFrame()
{
  m_videoFrame = new VideoFrame;
};

LightVideoFrame::LightVideoFrame(LightVideoFrame const & tocopy) : m_videoFrame(tocopy.m_videoFrame)
{
};

LightVideoFrame&	LightVideoFrame::operator=(LightVideoFrame const & tocopy)
{
  m_videoFrame = tocopy.m_videoFrame;
  return ( *this );
};

LightVideoFrame::LightVideoFrame(quint32 nboctets)
{
  m_videoFrame = new VideoFrame;
  m_videoFrame->nboctets = nboctets;
  m_videoFrame->nbpixels = nboctets / Pixel::NbComposantes;
  m_videoFrame->frame.octets = new quint8[nboctets];
};

LightVideoFrame::LightVideoFrame(quint8 const * tocopy, quint32 nboctets)
{
  quint32	i;

  m_videoFrame = new VideoFrame;
  m_videoFrame->nboctets = nboctets;
  m_videoFrame->nbpixels = nboctets / Pixel::NbComposantes;
  m_videoFrame->frame.octets = new quint8[nboctets];

  for ( i = 0; i < m_videoFrame->nboctets; ++i )
    m_videoFrame->frame.octets[i] = tocopy[i];
};

LightVideoFrame::~LightVideoFrame()
{
};

VideoFrame const * LightVideoFrame::operator->(void) const
{
  return ( m_videoFrame.data() );
};

VideoFrame const & LightVideoFrame::operator*(void) const
{
  return ( *m_videoFrame );
};

VideoFrame* LightVideoFrame::operator->(void)
{
  return ( m_videoFrame.data() );
};

VideoFrame& LightVideoFrame::operator*(void)
{
  return ( *m_videoFrame );
};