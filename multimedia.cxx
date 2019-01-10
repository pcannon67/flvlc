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
#include "multimedia.hpp"
#include "flvlc.hpp"

#ifdef WIN32
Multimedia::Multimedia(Fl_Preferences* pref_parent, const HWND window_id,
#else
Multimedia::Multimedia(Fl_Preferences* pref_parent, const int window_id,
#endif
		   	const int width,
			const int height
			) : 
			pref_parent(pref_parent),
			window_id(window_id),
			width(width),
			height(height)
{
  //TODO: catch
  initialize();
}


Multimedia::~Multimedia()
{
  //XXX: si el archivo de medios es un 
  // audio, se produce un retraso,
  // cerca de ~2 seg. pero al final termina.
  stop();
  release();
}



void Multimedia::pause() const
{
  if ( nullptr != media_player )
  {
  	/* toggle pause auto */
  	libvlc_media_player_pause(media_player);
  }
}


void Multimedia::stop()
{
  if ( is_valid_media() )
  {
  	unregister_events();
  	libvlc_media_player_stop(media_player); 
  	libvlc_media_player_release(media_player);
  	media_player = nullptr;
  }
}


void Multimedia::set_volume(int volume) const
{ 
  if ( is_valid_media() )
  {
	libvlc_audio_set_volume(media_player, volume);
  }
}


int Multimedia::get_volume() const
{
  if ( is_valid_media() )
  {
  	return libvlc_audio_get_volume(media_player);
  }
  return 0;
}

void Multimedia::mute()
{
  if ( is_valid_media() )
  {
	b_mute = !b_mute;
  	libvlc_audio_toggle_mute(media_player);
  }
  else
  {
  	b_mute = false;
  }
}

bool Multimedia::is_valid_media() const
{
  return ( media_player != nullptr);
}


bool Multimedia::is_mute() const
{
  return b_mute;
}

/* Si esta en pause o stop devuelve false*/
bool Multimedia::is_playing() const
{
  return is_valid_media() && libvlc_media_player_is_playing(media_player);
}


void Multimedia::event(const libvlc_event_t* event, void* data)
{
  switch( event->type )
  {
  	case libvlc_MediaPlayerEndReached:
  	  {
		FLVLC::cb_end();
		break;
	  }
	case libvlc_MediaPlayerTimeChanged: // not if pause
	  {
	  	const int64_t time = event->u.media_player_time_changed.new_time;
		FLVLC::cb_time_changed( time );
	  	break;
	  }
	case libvlc_MediaPlayerEncounteredError:
	  {
		if ( nullptr != data  )
		{
		  Log "Error = %s" Begin "libvlc_MediaPlayerEncounteredError" End;
		   ((Multimedia*)(data))->error = -1;
		}
		break;
	  }
	case libvlc_MediaPlayerLengthChanged:
	  {
	  	const int64_t length = event->u.media_player_length_changed.new_length; 
		FLVLC::cb_length_changed( length );
	  	break;
	  }
  }
}


void Multimedia::register_events()
{
  event_manager = libvlc_media_player_event_manager(media_player);

  libvlc_event_attach(event_manager, libvlc_MediaPlayerEndReached, event, NULL);
  libvlc_event_attach(event_manager, libvlc_MediaPlayerEncounteredError, event, this);
  libvlc_event_attach(event_manager, libvlc_MediaPlayerTimeChanged, event, NULL);
  libvlc_event_attach(event_manager, libvlc_MediaPlayerLengthChanged, event, NULL);
}


void Multimedia::unregister_events() const
{
  libvlc_event_detach(event_manager, libvlc_MediaPlayerEndReached, event, NULL);
  libvlc_event_detach(event_manager, libvlc_MediaPlayerEncounteredError, event, NULL);
  libvlc_event_detach(event_manager, libvlc_MediaPlayerTimeChanged, event, NULL);
  libvlc_event_detach(event_manager, libvlc_MediaPlayerLengthChanged, event, NULL);
}

void Multimedia::set_position(const int64_t position) const
{
  if ( is_valid_media() )
  {
	libvlc_media_player_set_time(media_player, position);
  }
}

int64_t Multimedia::get_position() const
{
  if ( is_valid_media() )
  {
  	return libvlc_media_player_get_time(media_player);
  }
  return 0;
}



bool Multimedia::initialize()
{
  const char* default_argv = "--mouse-hide-timeout=5 --swscale-mode=1 --no-video-title-show --no-osd";
  char* pref_value;

  if ( 0 != pref_parent->get("vlc", pref_value, default_argv ) )
  {
  	Log "Init %s" Begin "Register" End;
    initialize_vlc(pref_value);
    free(pref_value);
  }
  else
  {
  	Log "Init %s" Begin "Default" End;
    initialize_vlc(default_argv);
	pref_parent->set("vlc", default_argv);
	pref_parent->flush();
  }

  if ( vlc_instance == nullptr )
  {
  	Log "Error create new %s" Begin "vlc_instance" End;
  	return false;
  }
  Log "VERSION: %s" Begin libvlc_get_version() End;
  Log "COMPILER: %s" Begin libvlc_get_compiler() End;

  return true;
}

  	

/*
 * Make VLC param, char* []
 * Trim by space
 * */
void Multimedia::initialize_vlc(const char* argv)
{
  std::vector<std::string> vvargv{argv};
  std::string::size_type e = 0; 
  std::string::size_type b = 0;

  do {
      e = vvargv[0].find(' ',b); 
      vvargv.push_back( vvargv[0].substr(b, (e-b) ) );
      b = e + 1;
  } while( e < std::string::npos ); 

  vlc_instance = libvlc_new(vvargv.size()-1, (const char* const*) &vvargv[1] );
}

  	

/* 
 * - Si no se detuvo la reproducción,
 *   desde aqui se llama a stop().
 * */
int Multimedia::play(const char* media_file)
{
  error = -1;

  if ( vlc_instance == nullptr )  
  { 
  	Log "vlc_instance == NULL, media file %s" Begin media_file End;
  	return error; 
  }

  libvlc_media_t* media = libvlc_media_new_location(vlc_instance, media_file);

  if ( media == NULL )
  {
  	Log "media  == NULL, media file %s" Begin media_file End;
  	return error;
  }

  if ( is_valid_media() )
  {
  	stop();
  }

  ///////////////////////////////////
  // Detectar si archivo es válido.
  //libvlc_media_parse(media);

  //error = libvlc_media_get_duration(media);
  //Log(error);
  //
  //if (not is_valid_media() and  (0 == error or -1 == error or libvlc_Error == libvlc_media_get_state(media) ) )
  //{
  //  libvlc_media_release(media);
  //  Log("Error file");
  //	return error;
  //}
  ///////////////////////////////////

  media_player = libvlc_media_player_new_from_media(media);

  if ( media_player == nullptr )
  {
  	Log "media_player == %s" Begin "nullptr" End;
  	return false ;
  }

#ifdef WIN32
  libvlc_media_player_set_hwnd(media_player, window_id );
#else
  libvlc_media_player_set_xwindow(media_player, window_id );
#endif


  libvlc_video_set_key_input(media_player, 0);
  libvlc_video_set_mouse_input(media_player, 0);

  register_events();

  libvlc_media_player_play(media_player);

  libvlc_media_release(media);
  return error;
}



void Multimedia::release()
{
  if ( vlc_instance != nullptr )
  {
  	libvlc_release(vlc_instance);
  	vlc_instance = nullptr;
  }
}


void Multimedia::snapshot(const char* path) const
{
  if ( is_valid_media() )
  {
  	libvlc_video_take_snapshot(media_player, 0, path, 0, 0);
  }
}


bool Multimedia::is_seekable() const
{
  return 1 == libvlc_media_player_is_seekable(media_player);
}

/*
bool Multimedia::exist_audio()
{
  if ( is_valid_media() )
  {
	int n = libvlc_audio_get_track_count(media_player);
	Log(n);
  }
  return false;
}*/


/* video */

Multimedia::Track Multimedia::get_video_subtitle_description() const
{
  if ( is_valid_media() )
  {
  	return libvlc_video_get_spu_description(media_player);
  }
  return nullptr;
}


int Multimedia::get_video_subtitle() const
{
  if ( is_valid_media() )
  {
  	return libvlc_video_get_spu(media_player);
  }
  return -1;
}

void Multimedia::set_video_subtitle(const int id) const
{
  if ( is_valid_media() )
  {
  	libvlc_video_set_spu(media_player, id);
  }
}


void Multimedia::set_video_subtitle(const char* file) const
{
  if ( is_valid_media() )
  {
  	libvlc_video_set_subtitle_file(media_player, file);
  }
}


void Multimedia::set_video_subtitle_delay(const int64_t delay) const
{
  if ( is_valid_media() )
  {
  	libvlc_video_set_spu_delay(media_player, delay * 1000000);
  }
}


int64_t Multimedia::get_video_subtitle_delay() const
{
  if ( is_valid_media() )
  {
  	return libvlc_video_get_spu_delay(media_player) / 1000000;
  }

  return -1;
}





/* audio */

Multimedia::Track Multimedia::get_audio_track_description() const
{
  if ( is_valid_media() )
  {
  	return libvlc_audio_get_track_description(media_player);
  }
  return nullptr;
}


int Multimedia::get_audio_track() const
{
  if ( is_valid_media() )
  {
  	return libvlc_audio_get_track(media_player);
  }
  return -1;
}


void Multimedia::set_audio_track(const int id) const
{
  if ( is_valid_media() )
  {
  	libvlc_audio_set_track(media_player, id);
  }
}


void Multimedia::set_audio_track_delay(const int64_t delay) const
{
  if ( is_valid_media() )
  {
  	libvlc_audio_set_delay(media_player, delay * 1000000);
  }
}


int64_t Multimedia::get_audio_track_delay() const
{
  if ( is_valid_media() )
  {
  	return libvlc_audio_get_delay(media_player) / 1000000;
  }
  return -1;
}


/* vim: set ts=4 sw=2 tw=0 noet :*/