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

#include <algorithm>
#include <string>
#include <vector>

#ifdef DEBUG
#include <iostream>
#endif

#include "files.hpp"

struct Item {
	std::string name;
	int64_t position;
	bool b_watch;
};

using ITEMS = std::vector<Item>;

class Playlist {
      public:
	Playlist();

	~Playlist();

	void append(const int argc, const char *argv[]);
	void append(Item &item);
	void append(const char *name);
	const char *current() const;
	const char *prev();
	const char *next();
	const unsigned int count() const;
	const unsigned int position() const;
	void position(const unsigned int pos);
	bool is_empty() const;
	void reset();
	bool is_prev() const;
	bool is_next() const;
	const char *title() const;
	void watch(const int64_t pos);
	int64_t watch() const;
	bool is_watch() const;
	void set_watch(bool val);
	bool load(const char *path);
	void save(const char *path);
	void clean();

#ifdef DEBUG
	void print() const
	{
		for (auto &n : items) {
			std::cout << n.name << std::endl;
		}
	}
#endif

      private:
	ITEMS items;
	int ipos;

      public:
	const ITEMS &get_items() const;
};
