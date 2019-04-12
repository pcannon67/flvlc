/*
	Copyright (C) 2015, 2019 Daniel T. Borelli

	This file is part of flvlc.

	flvlc is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	flvlc is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with flvlc.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once

#include <stdarg.h>
#include <syslog.h>
#include <stdio.h>
#include <assert.h>

static void va_log(const int option, char const *const format, ...)
{
	assert(format);
	va_list vl;
	va_start(vl, format);
	vsyslog(option, format, vl);
	va_end(vl);
}

static void va_fprintf(FILE *file, char const *const format, ...)
{
	assert(format);
	va_list vl;
	va_start(vl, format);
	vfprintf(file, format, vl);
	va_end(vl);
}

#define macro_string(x) #x
#define macrostr(x) macro_string(x)

#ifdef DEBUG
#define preformat __FILE__ ":" macrostr(__LINE__) ":"
#else
#define preformat
#endif

#define log_warning(...)	\
	va_log(LOG_WARNING, "Warning: " preformat __VA_ARGS__)

#define log_error(...)		\
	va_log(LOG_ERR, "Error: " preformat __VA_ARGS__)

#define log_notice(...)		\
	va_log(LOG_NOTICE,"Notice: " preformat __VA_ARGS__)

#define print_warning(...)	\
	va_fprintf(stdout, "Warning: " preformat __VA_ARGS__)

#define print_error(...)	\
	va_fprintf(stderr, "Error: " preformat __VA_ARGS__)

#define print_notice(...)	\
	va_fprintf(stdout, "Notice: " preformat __VA_ARGS__)
