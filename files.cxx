/*
	Copyright (C) 2015 Daniel T. Borelli

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

#include "files.hpp"

/* No debe ser un directorio.
 * Debe ser un archivo regular o 
 *  un enlace.
 * */
bool FILES::is_file(const char *name)
{
#ifdef WIN32 
	const DWORD attr = GetFileAttributes(name);

	if ( (attr != INVALID_FILE_ATTRIBUTES and attr != FILE_ATTRIBUTE_DIRECTORY and
		attr != FILE_ATTRIBUTE_REPARSE_POINT) // <- FIXME: no detecta los enlaces
	   )
	{
	  //TODO: get size
		return true;
	}	

#else // LINUX
  struct stat st;
  
  const int status = lstat(name, &st);

  if (status == 0 &&
  	  not S_ISDIR(st.st_mode) &&
  	  ( S_ISREG(st.st_mode) ||
		S_ISLNK(st.st_mode) ) &&
  	  st.st_size != 0 
  	  )
  {
  	return true;
  }
#endif 

	return false;
}



bool FILES::is_uri(const char *name)
{
  const char* match = "{http|https|ftp}://*";
  return  0 != fl_filename_match(name, match); 
}



bool FILES::make_name_file(std::string& name, const char *file)
{
  if ( is_file(file) )
  {
	char abs_path[FL_PATH_MAX];
	fl_filename_absolute(abs_path, sizeof(abs_path), file);

#ifdef WIN32
	name = "file:///"; name += abs_path;
#else
	name = "file://";  name += abs_path;
#endif
  }
  else if ( is_uri(file) )
  {
	name = file;
  }
  else
  {
  	return false;
  }

  return true;
}

