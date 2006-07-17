/***************************************************************************
 *   Copyright (C) 2006 by Dominic Rath                                    *
 *   Dominic.Rath@gmx.de                                                   *
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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "time_support.h"

#include <sys/time.h>
#include <time.h>

int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y);
int timeval_add(struct timeval *result, struct timeval *x, struct timeval *y);
int timeval_add_time(struct timeval *result, int sec, int usec);

/* calculate difference between two struct timeval values */
int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y)
{
	if (x->tv_usec < y->tv_usec)
	{
		int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
		y->tv_usec -= 1000000 * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_usec - y->tv_usec > 1000000) {
		int nsec = (x->tv_usec - y->tv_usec) / 1000000;
		y->tv_usec += 1000000 * nsec;
		y->tv_sec -= nsec;
	}

	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_usec = x->tv_usec - y->tv_usec;

	/* Return 1 if result is negative. */
	return x->tv_sec < y->tv_sec;
}

/* add two struct timeval values */
int timeval_add(struct timeval *result, struct timeval *x, struct timeval *y)
{
	result->tv_sec = x->tv_sec + y->tv_sec;
	
	result->tv_usec = x->tv_usec + y->tv_usec;
	
	while (result->tv_usec > 1000000)
	{
		result->tv_usec -= 1000000;
		result->tv_sec++;
	}
	
	return 0;
}

int timeval_add_time(struct timeval *result, int sec, int usec)
{
	result->tv_sec += sec;
	result->tv_usec += usec;
	
	while (result->tv_usec > 1000000)
	{
		result->tv_usec -= 1000000;
		result->tv_sec++;
	}
	
	return 0;
}

