flvlc
=====

<a href="https://postimages.org/" target="_blank"><img src="https://i.postimg.cc/C1rn0KtL/flvlc-00.png" alt="flvlc-00"/></a>


<a href="https://postimg.cc/cKvHCQj1" target="_blank"><img src="https://i.postimg.cc/cKvHCQj1/flvlc-01.png" alt="flvlc-01"/></a><br/><br/>

<a href="https://postimg.cc/Yvn0tXdy" target="_blank"><img src="https://i.postimg.cc/Yvn0tXdy/flvlc-02.png" alt="flvlc-02"/></a><br/><br/>

<a href="https://postimg.cc/p93dFmbf" target="_blank"><img src="https://i.postimg.cc/p93dFmbf/flvlc-03.png" alt="flvlc-03"/></a><br/><br/>



Download:
---------
From [SourceForge](http://sourceforge.net/projects/flvlc)
or from [Git](https://github.com/spycapitan/flvlc)


Compile
-------
- Linux

	- Requirements:
		  - FLTK >=1.3
		  - libvlc >=2.1 ( or vlc 2.1 )
		  - cmake >=2.8
		  - GCC support c++11

- Windows (mingw) (testing,obsolete)
	
	- Requirements:
		  - FLTK >=1.3-snapshot
		  - vlc >=2.1 sdk
		  - cmake >=2.8
		  - GCC support gnu++11

- Build

	```bash
	mkdir build && cd build
	cmake -DCMAKE_BUILD_TYPE=Release .. && make
			-- or --
	cmake -DCMAKE_BUILD_TYPE=Debug .. && make
	```

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


