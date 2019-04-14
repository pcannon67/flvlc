flvlc
=====


<a href='https://postimages.org/' target='_blank'><img src='https://i.postimg.cc/9MRnH6v9/flvlc.png' border='0' alt='flvlc'/></a>



Platform:
----------

- GNU/Linux.

- Windows (flvlc <=2.12, end support).


Compile
-------
- Linux

	- Requirements:

		  - FLTK >=1.3 (dev)

		  - libvlc >=2.1 ( or vlc 2.1 ) (dev)

			  Note: some "distros" need extra plugins.

		  - make

		  - pkg-config

		  - GCC support c++11

- Build

	```bash
	make release
			-- or --
	make debug
	```



Testing
---------

For testing enable debug build.
See logs from a terminal.



Help commands
-------------------
 - Key __'h'__ : toggle maximize
 - Key __'l'__ : show playlist window
 - Key __'p'__ : show preferences window
 - Key __'u'__ : open URL
 - Key __'y'__ : take one snapshot
 - Key __'o'__ : open file
 - key __'t'__ : show subtitles window
 - Key __'w'__ : watch toggle
 - Key __'r'__ : toggle repeat
 - Key __'f'__ : toggle fullscreen
 - Key __'m'__ : toggle mute audio
 - Key __'s'__ : stop media
 - Key __'Esc'__ or __'q'__ : quit
 - Key __'n'__ : next media
 - Key __'b'__ : previous media
 - Key __'Space'__ : toggle play/pause
 - Key __'.'__ : volume up
 - Key __','__ : volume down
 - Key __'arrow right'__ : video foward low
 - Key __'arrow left'__ :  video backward low
 - Key __'arrow up'__ : video foward high
 - Key __'arrow down'__ : video backward high 
 - __Mouse wheel__: volume up/down


Notes
-----

- Repeat modes:
	  - none
	  - repeat current media file.
	  - repeat playlist

- Popup Menu:
	  - Press right button.

- Watch button: 
	  - Save the current position video while running.

- Snapshot:
	  - Save to temp directory.

- Open URL:( alpha, testing )


- Automatically save and load playlist.


