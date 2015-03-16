/*
 * Xmusic (Zhwen.org)
 *
 * Copyright (c) 2008-~  Zhwen.org
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: xfuns.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#include "xfuns.h"

char *getlast(char *str)
{
	char *p, *tmp;
	p = str;
	while(strchr(p, '/')){
			tmp = strchr(p, '/');
			p = tmp + 1;
	};
	return p;
}
