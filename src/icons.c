/*
	Copyright (c) 2019, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.
	Please read that file and understand the license terms
	before using or altering the project.
*/

// The checking is NOT case sensitive

#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "core.h"
#include "icons.h"

// Default file icon is text file or normal link file
#define DEFAULT_FILE_ICON "\uf713"      // 
#define DEFAULT_LINK_FILE_ICON "\uf71c" // 
// Default directory icon is normal directory or normal link directory
#define DEFAULT_DIR_ICON  "\uf74a"      // 
#define DEFAULT_LINK_DIR_ICON "\uf751"  // 


static const char * get_file_icon_by_ext( const char * ext, const bool is_link );
static const char * get_file_icon_by_name( const char * name, const bool is_link );

static bool find_in( const char * of, const char * values, bool is_exact_match );

#define IS( of, values ) find_in( of, values, true )
#define BEGINS( of, values ) find_in( of, values, false )

#define LOSSLESS_AUDIO "8svx, iff, aiff, aif, aifc, au, snd, bwf, wav, wave, cdda, raw, pcm, sam, ra, ram, flac, la, pac, ape, ofr, ofs, off, rka, shn, tak, tta, wv, brstm, dts, dtshd, dtsma, ast, aw, psf, alac, m4a"
#define LOSSY_AUDIO "amr, 3ga, mp1, mp2, mp3, spx, gsm, wma, aac, mpc, vqf, ots, swa, vox, voc, dwd, smp, ogg, oga, opus"
#define PLAYLIST "cue, aimppl, asx, xpl, xspf, zpl, m3u, m3u8, pls"

#define VIDEO "avi, flv, mkv, mov, mp4, ogv, webm"

static const bool is_default_icon( const char * icon )
{
	return strcmp( icon, DEFAULT_FILE_ICON ) == 0 || strcmp( icon, DEFAULT_LINK_FILE_ICON ) == 0;
}

const char * get_file_icon( const char * name, const char * ext, const bool is_link )
{
	const char * file_icon = get_file_icon_by_name( name, is_link );
	if( strcmp( ext, "\0" ) != 0 && is_default_icon( file_icon ) ) {
		const char * ext_icon = get_file_icon_by_ext( ext, is_link );
		return ext_icon;
	}
	return file_icon;
}

const char * get_dir_icon( const char * dir, const bool is_link )
{
		 if( BEGINS( dir, ".git, git"           ) ) return "\ue5fb"; // 
	else if( BEGINS( dir, ".trash, trash"       ) ) return "\uf6bf"; // 
	else if( BEGINS( dir, ".bash"               ) ) return "\ue795"; // 
	else if( BEGINS( dir, ".bundle, .gem"       ) ) return "\ue791"; // 
	else if( BEGINS( dir, ".cargo, .rustup"     ) ) return "\ue7a8"; // 
	else if( BEGINS( dir, ".config"             ) ) return "\ue5fc"; // 
	else if( BEGINS( dir, ".docker"             ) ) return "\uf308"; // 
	else if( BEGINS( dir, ".go"                 ) ) return "\ufcd1"; // ﳑ
	else if( IS    ( dir, ".idea"               ) ) return "\ue7b5"; // 
	else if( BEGINS( dir, ".mix"                ) ) return "\ue62d"; // 
	else if( BEGINS( dir, ".npm, node_modules"  ) ) return "\ue5fa"; // 
	else if( BEGINS( dir, ".vs, .vscode"        ) ) return "\ufb0f"; // ﬏
	else if( BEGINS( dir, ".weechat"            ) ) return "\uf78b"; // 
	else if( BEGINS( dir, "application"         ) ) return "\ufb13"; // ﬓ
	else if( BEGINS( dir, "bin"                 ) ) return "\ufb13"; // ﬓ
	else if( BEGINS( dir, "config"              ) ) return "\ue5fc"; // 
	else if( BEGINS( dir, "desktop"             ) ) return "\uf878"; // 
	else if( BEGINS( dir, "download"            ) ) return "\uf74c"; // 
	else if( BEGINS( dir, "library"             ) ) return "\uf830"; // 
	else if( BEGINS( dir, "movie"               ) ) return "\uf880"; // 
	else if( BEGINS( dir, "music, songs, audio" ) ) return "\uf886"; // 
	else if( BEGINS( dir, "photo, picture"      ) ) return "\uf74e"; // 
	else if( IS    ( dir, "__pycache__"         ) ) return "\uf81f"; // 
	else if( BEGINS( dir, "video"               ) ) return "\uf880"; // 

	if( is_link ) return DEFAULT_LINK_DIR_ICON;
	return DEFAULT_DIR_ICON;
}

static const char * get_file_icon_by_ext( const char * ext, const bool is_link )
{
	// Apple
	     if( IS    ( ext, "DS_Store"                  ) ) return "\uf534"; // 
	// Configuration
	else if( IS    ( ext, "json"                      ) ) return "\ufb25"; // ﬥ
	else if( IS    ( ext, "lock"                      ) ) return "\uf83d"; // 
	else if( IS    ( ext, "ini, yaml, yml, env, toml" ) ) return "\uf423"; // 
	// Data handling / manipulation
	else if( IS    ( ext, "html"                      ) ) return "\uf13b"; // 
	else if( IS    ( ext, "md"                        ) ) return "\ue609"; // 
	else if( IS    ( ext, "xml, ui"                   ) ) return "\uf44f"; // 
	// Git
	else if( BEGINS( ext, "git"                       ) ) return "\uf7a3"; // 
	// Terminal stuff
	else if( IS    ( ext, "zsh, bash, sh"             ) ) return "\ue795"; // 
	else if( BEGINS( ext, "zsh, bash"                 ) ) return "\uf423"; // 
	else if( BEGINS( ext, "vim"                       ) ) return "\ue62b"; // 
	// Databases
	else if( IS    ( ext, "sql, sqlite"               ) ) return "\uf1c0"; // 
	// Audio
	else if( IS    ( ext, LOSSLESS_AUDIO              ) ) return "\uf886"; // 
	else if( IS    ( ext, LOSSY_AUDIO                 ) ) return "\uf886"; // 
	else if( IS    ( ext, PLAYLIST                    ) ) return "\ue602"; // 
	// Video
	else if( IS    ( ext, VIDEO                       ) ) return "\uf880"; // 
	// Programming Languages
	else if( IS    ( ext, "h, hh,hpp,hxx, h++"        ) ) return "\ufb70"; // ﭰ
	else if( IS    ( ext, "c"                         ) ) return "\ufb70"; // ﭰ
	else if( IS    ( ext, "cc, cpp, cxx, c++"         ) ) return "\ufb71"; // ﭱ
	else if( IS    ( ext, "cs"                        ) ) return "\uf81a"; // 
	else if( IS    ( ext, "clj, cljs, cljc, edn"      ) ) return "\ue76a"; // 
	else if( IS    ( ext, "coffee, litcoffee"         ) ) return "\uf0f4"; // 
	else if( IS    ( ext, "ex, exs, eex"              ) ) return "\ue62d"; // 
	else if( IS    ( ext, "elm"                       ) ) return "\ue62c"; // 
	else if( IS    ( ext, "erl, hrl"                  ) ) return "\ue7b1"; // 
	else if( IS    ( ext, "fs, fsi, fsscript"         ) ) return "\ue7a7"; // 
	else if( IS    ( ext, "go"                        ) ) return "\ufcd1"; // ﳑ
	else if( IS    ( ext, "hs, lhs"                   ) ) return "\ue61f"; // 
	else if( IS    ( ext, "java, class, jar"          ) ) return "\ue256"; // 
	else if( IS    ( ext, "js"                        ) ) return "\uf81d"; // 
	else if( IS    ( ext, "jl"                        ) ) return "\ue624"; // 
	else if( IS    ( ext, "lua"                       ) ) return "\ue620"; // 
	else if( IS    ( ext, "pl, pm, t, pod"            ) ) return "\ue769"; // 
	else if( IS    ( ext, "pro, P"                    ) ) return "\ue7a1"; // 
	else if( IS    ( ext, "py, pyc, pyd, pyx"         ) ) return "\uf81f"; // 
	else if( IS    ( ext, "rb"                        ) ) return "\ue791"; // 
	else if( IS    ( ext, "rs, rlib"                  ) ) return "\ue7a8"; // 
	else if( IS    ( ext, "scala, sc"                 ) ) return "\ue737"; // 
	else if( IS    ( ext, "swift"                     ) ) return "\ufbe3"; // ﯣ
	else if( IS    ( ext, "ts, tsx"                   ) ) return "\ufbe4"; // ﯤ

	if( is_link ) return DEFAULT_LINK_FILE_ICON;
	return DEFAULT_FILE_ICON;
}

static const char * get_file_icon_by_name( const char * name, const bool is_link )
{
	// Development
	if( BEGINS( name, "Makefile" ) ) return "\ue779"; // 
	else if( BEGINS( name, "Dockerfile, docker-compose" ) ) return "\uf308"; // 

	// Other
	if( BEGINS( name, "LICENSE, license, copying, COPYING" ) ) return "\uf69a"; // 
	// TODO:
	if( is_link ) return DEFAULT_LINK_FILE_ICON;
	return DEFAULT_FILE_ICON;
}

static inline bool is_whitespc( const char c ) { return c == ',' || c == ' ' || c == '\0'; }

static bool find_in( const char * of, const char * values, bool is_exact_match )
{
	int len_val = strlen( values );
	char tmp_str[ 100 ];
	int tmp_ctr = 0;
	for( int i = 0; i <= len_val; ++i ) {
		if( is_whitespc( values[ i ] ) ) {
			if( tmp_ctr == 0 ) continue;
			tmp_str[ tmp_ctr ] = '\0';
			if( is_exact_match ) {
				if( strcasecmp( of, tmp_str ) == 0 ) return true;
			}
			else {
				if( strncasecmp( of, tmp_str, strlen( tmp_str ) ) == 0 ) return true;
			}
			strcpy( tmp_str, "\0" );
			tmp_ctr = 0;
			continue;
		}
		tmp_str[ tmp_ctr++ ] = values[ i ];
	}
	return false;
}
