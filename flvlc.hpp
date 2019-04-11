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

#ifdef WIN32
#include <pthread.h>
#else
#include <thread>
#endif

#include <sstream>

//#ifdef DEBUG
//#include <iostream>
//#define LOG(x) std::cerr << "#Func: " << __func__ << "() #Line: " << __LINE__
//<< " #Msg: " << (x) << std::endl #else #define LOG(x) #endif

#include <FL/filename.H> // FL_PATH_MAX

#include "main_window.hpp"
#include "multimedia.hpp"
#include "playlist.hpp"
#include "playlist_window.hpp"
#include "preferences_window.hpp"
#include "subtitles_window.hpp"
#include "syslog.hpp"
#include "url_window.hpp"

namespace FLVLC {
static MainWindow window;
static Multimedia *multimedia = nullptr;
static Playlist playlist;
static PlaylistWindow *pl_window = nullptr;
static SubtitlesWindow *sbt_window = nullptr;
static URL_Window *url_window = nullptr;
static Preferences_Window *pref_window = nullptr;
static Fl_Preferences *preferences = nullptr;
static MainWindow::STATE state = MainWindow::STATE::STOP;
static bool b_fullscreen = false;
static constexpr char *time_cero = "00:00:00 / 00:00:00";
static std::string time_length;
static float video_percent_low;
static float video_percent_high;

void cb_end();
void cb_time_changed(float value);
void cb_length_changed(float value);

void initialize_volume();
void initialize_preferences();
void update_title_info();
void update_time_info(const float value);
void toggle_fullscreen();
const std::string parse_time(float value);
void update_gui(void *);
void up_volume();
void down_volume();
void make_multimedia();
void check_if_watch();
void play_seek(const char *media);
void load_playlist();
void save_playlist();
void update_label_playlist();

void action_play_pause();
void action_stop();
void action_prev();
void action_next();
#ifdef WIN32
void *action_stop_next(void *);
#else
void action_stop_next();
#endif
void action_mute();
void action_repeat();
void action_volume();
void action_video();
void action_quit();
void action_open_file();
void action_open_url();
void action_watch();
void action_playlist();
void action_subtitles();
void action_preferences();
void action_snapshot();
}; // namespace FLVLC
