/******************************************************************************/
/* Mednafen - Multi-system Emulator                                           */
/******************************************************************************/
/* nongl.cpp:
**  Copyright (C) 2005-2016 Mednafen Team
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "main.h"
#include "video.h"
#include "nongl.h"


template<typename T, int alpha_shift>
static void BlitStraight(const MDFN_Surface *src_surface, const MDFN_Rect *src_rect, MDFN_Surface *dest_surface, const MDFN_Rect *dest_rect)
{
	const T* src_pixels = src_surface->pixels;	
	for(int32 y = 0; y < 232; y++)
	{
		memcpy(dest_surface->pixels, src_pixels, 256 * sizeof(T));
		src_pixels += 1024;
		dest_surface->pixels += 256;
	}
}

extern SDL_Surface* screen;


void MDFN_StretchBlitSurface(const MDFN_Surface* src_surface, const MDFN_Rect& src_rect, MDFN_Surface* dest_surface, const MDFN_Rect& dest_rect, bool source_alpha, int scanlines, const MDFN_Rect* original_src_rect, int rotated, int InterlaceField)
{
	MDFN_Rect sr, dr, o_sr;
	sr = src_rect;
	o_sr = *original_src_rect;
	dr = dest_rect;
	//printf("%d:%d, %d:%d, %d:%d\n", sr.x, sr.w, sr.y, sr.h, src_surface->w, src_surface->h);
	BlitStraight<uint32, 31>(src_surface, &sr, dest_surface, &dr);
}
