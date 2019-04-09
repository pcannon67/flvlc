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

#ifdef DEBUG
#include <string>
#include <syslog.h>
template <typename... Arguments>
static inline void SysLog(const char *const message, Arguments... argv)
{
	std::string fmt("#Func:%s #Line:%d #Message:");
	fmt += message;
	syslog(LOG_ERR, fmt.c_str(), argv...);
}
#else  // DEBUG
template <typename... Arguments>
__attribute__((unused)) static inline void SysLog(const char *const message,
						  Arguments... argv) {}
#endif // DEBUG

#undef Log
#undef Begin
#undef End
#define Log (SysLog(
#define Begin , __func__, __LINE__,
#define End ));
