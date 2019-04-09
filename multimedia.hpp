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
#include <windows.h>
#define hypot hypot
#include <cmath>
#endif

#include <FL/Fl_Preferences.H>
#include <algorithm>
#include <string>
#include <vector>
#include <vlc/vlc.h>

class Multimedia {
      public:
	using VecArgv = std::vector<std::string>;
	using Track = libvlc_track_description_t *;
#ifdef WIN32
	Multimedia(Fl_Preferences *pref_parent, const HWND window_id,
#else
	Multimedia(Fl_Preferences *pref_parent, const int window_id,
#endif
		   const int width, const int height);

	~Multimedia();

      private:
	libvlc_instance_t *vlc_instance = nullptr;
	libvlc_media_player_t *media_player = nullptr;
	libvlc_event_manager_t *event_manager = nullptr;
#ifdef WIN32
	HWND window_id = 0;
#else
	int window_id = 0;
#endif
	int width = 0;
	int height = 0;
	bool b_mute = false;
	int error = 0; // 0 == ok, -1 == errr
	Fl_Preferences *pref_parent;

      private:
	/* VLC lifetime */
	bool initialize();
	void initialize_vlc(const char *argv);
	void release();

	/* events */
	static void event(const libvlc_event_t *event, void *object);
	void register_events();
	void unregister_events() const;

      public:
	/* Actions */
	int play(const char *media_file);
	void set_volume(const int volume) const;
	int get_volume() const;
	bool is_playing() const;
	bool is_seekable() const;
	void stop();
	void pause() const;
	void mute();
	bool is_mute() const;
	void set_position(const int64_t position) const;
	int64_t get_position() const;
	//	bool exist_audio();
	bool is_valid_media() const;

	Multimedia::Track get_video_subtitle_description() const;
	int get_video_subtitle() const;
	void set_video_subtitle(const int id) const;
	void set_video_subtitle(const char *file) const;
	void set_video_subtitle_delay(const int64_t delay) const;
	int64_t get_video_subtitle_delay() const;

	Multimedia::Track get_audio_track_description() const;
	int get_audio_track() const;
	void set_audio_track(const int id) const;
	void set_audio_track_delay(const int64_t delay) const;
	int64_t get_audio_track_delay() const;
	void snapshot(const char *path) const;
};
