/* modifier 0 means no modifier */
static int surfuseragent    = 1;  /* Append Surf version to default WebKit user agent */
static char *fulluseragent  = ""; /* Or override the whole user agent string */
#if MULTIJS_PATCH
static char *scriptfiles[]  = {
	"~/.surf/script.js",
};
#else
static char *scriptfile     = "~/.surf/script.js";
#endif // MULTIJS_PATCH
static char *styledir       = "~/.surf/styles/";
static char *certdir        = "~/.surf/certificates/";
static char *cachedir       = "~/.surf/cache/";
static char *cookiefile     = "~/.surf/cookies.txt";
#if ARIA2_PATCH || DOWNLOAD_CONSOLE_PATCH
static char *downloaddir    = "~/Downloads/";
#endif // ARIA2_PATCH | DOWNLOAD_CONSOLE_PATCH
#if DOWNLOAD_CONSOLE_PATCH
static char *dlstatusdir    = "~/.surf/dlstatus/";
#endif // DOWNLOAD_CONSOLE_PATCH
#if FIFO_PATCH
static char *fifodir        = "~/.surf/fifo/";
#endif // FIFO_PATCH
#if URL_FILTERING_PATCH
static char *filterfile     = "~/.surf/filters"
#endif // URL_FILTERING_PATCH
#if HISTORY_PATCH || CHROMEBAR_PATCH
static char *historyfile    = "~/.surf/history.txt";
#endif // CHROMEBAR_PATCH
#if SITE_SPECIFIC_JS_PATCH
static char *scriptdir      = "~/.surf/scripts/";
#endif // SITE_SPECIFIC_JS_PATCH

#if HOMEPAGE_PATCH
static const char *homepage_uri = "about:blank";  /* Used when no URI is specified */
#endif // HOMEPAGE_PATCH

#if SCROLL_FASTER_PATCH
static float scroll_multiplier = 7.0;  /* Increases the scroll speed */
#endif // SCROLL_FASTER_PATCH

#if SHORT_TITLE_PATCH
static int extendedtitle    = 0;  /* 0 to not append surf's toggle and page status to title */
#endif // SHORT_TITLE_PATCH

#if STARTGO_PATCH
static int startgo = 0;  /* Whether to always open GO prompt on startup */
#endif // STARTGO_PATCH

#if EXTERNALPIPE_PATCH || EXTERNALPIPE_SIGNAL_PATCH
static char *linkselect_curwin [] = { "/bin/sh", "-c",
	"surf_linkselect.sh $0 'Link' | xargs -r xprop -id $0 -f _SURF_GO 8u -set _SURF_GO",
	winid, NULL
};
static char *linkselect_newwin [] = { "/bin/sh", "-c",
	"surf_linkselect.sh $0 'Link (new window)' | xargs -r surf",
	winid, NULL
};
static char *editscreen[] = { "/bin/sh", "-c", "edit_screen.sh", NULL };

#if EXTERNALPIPE_SIGNAL_PATCH
static char *externalpipe_sigusr1[] = {"/bin/sh", "-c", "externalpipe_buffer.sh surf_strings_read"};
#endif // EXTERNALPIPE_SIGNAL_PATCH
#endif // EXTERNALPIPE_PATCH

/* Webkit default features */
/* Highest priority value will be used.
 * Default parameters are priority 0
 * Per-uri parameters are priority 1
 * Command parameters are priority 2
 */
static Parameter defconfig[ParameterLast] = {
	/* parameter                    Arg value       priority */
	[AccessMicrophone]    =       { { .i = 0 },     },
	[AccessWebcam]        =       { { .i = 0 },     },
	[Certificate]         =       { { .i = 0 },     },
	[CaretBrowsing]       =       { { .i = 0 },     },
	[CookiePolicies]      =       { { .v = "@Aa" }, },
	[DarkMode]            =       { { .i = 0 },     },
	[DefaultCharset]      =       { { .v = "UTF-8" }, },
	[DiskCache]           =       { { .i = 1 },     },
	[Ephemeral]           =       { { .i = 0 },     },
	[FileURLsCrossAccess] =       { { .i = 0 },     },
	[FontSize]            =       { { .i = 12 },    },
	[Geolocation]         =       { { .i = 0 },     },
	#if GTK_BLACK_BACKGROUND_PATCH
	[HideBackground]      =       { { .i = 1 },     },
	#else
	[HideBackground]      =       { { .i = 0 },     },
	#endif // GTK_BLACK_BACKGROUND_PATCH
	[Inspector]           =       { { .i = 0 },     },
	[JavaScript]          =       { { .i = 1 },     },
	[KioskMode]           =       { { .i = 0 },     },
	[LoadImages]          =       { { .i = 1 },     },
	[MediaManualPlay]     =       { { .i = 1 },     },
	#if NOTIFICATIONS_PATCH
	[Notifications]       =       { { .i = 0 }      },
	#endif // NOTIFICATIONS_PATCH
	[PDFJSviewer]         =       { { .i = 1 },     },
	[PreferredLanguages]  =       { { .v = (char *[]){ NULL } }, },
	#if PROXY_CONFIG_PATCH
	[ProxyIgnoreHosts]    =       { { .v = (char *[]){ NULL } }, },
	[ProxyMode]           =       { { .i = SystemProxy }, },
	[ProxyUrl]            =       { { .v = (char *) NULL }, },
	#endif // PROXY_CONFIG_PATCH
	[RunInFullscreen]     =       { { .i = 0 },     },
	[ScrollBars]          =       { { .i = 1 },     },
	[ShowIndicators]      =       { { .i = 1 },     },
	[SiteQuirks]          =       { { .i = 1 },     },
	[SmoothScrolling]     =       { { .i = 0 },     },
	[SpellChecking]       =       { { .i = 0 },     },
	[SpellLanguages]      =       { { .v = ((char *[]){ "en_US", NULL }) }, },
	[StrictTLS]           =       { { .i = 1 },     },
	[Style]               =       { { .i = 1 },     },
	[WebGL]               =       { { .i = 0 },     },
	[ZoomLevel]           =       { { .f = 1.0 },   },
	#if CLIPBOARD_INSTEAD_OF_PRIMARY_PATCH
	[ClipboardNotPrimary] =       { { .i = 1 },     },
	#endif // CLIPBOARD_INSTEAD_OF_PRIMARY_PATCH
};

static UriParameters uriparams[] = {
	{ "(://|\\.)suckless\\.org(/|$)", {
		[JavaScript] = { { .i = 0 }, 1 },
	}, },
};

/* default window size: width, height */
static int winsize[] = { 800, 600 };

static WebKitFindOptions findopts = WEBKIT_FIND_OPTIONS_CASE_INSENSITIVE |
                                    WEBKIT_FIND_OPTIONS_WRAP_AROUND;

#define PROMPT_GO   "Go:"
#define PROMPT_FIND "Find:"
#if USERAGENT_PATCH
#define PROMPT_AGENT "Agent:"
#endif // USERAGENT_PATCH

/* SETPROP(readprop, setprop, prompt)*/
#if BOOKMARKING_PATCH
#define SETPROP(r, s, p) { \
	.v = (const char *[]){ "/bin/sh", "-c", \
		"prop=\"$(printf '%b' \"$(xprop -id $1 $2 " \
		"| sed \"s/^$2(STRING) = //;s/^\\\"\\(.*\\)\\\"$/\\1/\" && cat ~/.surf/bookmarks)\" " \
		"| dmenu -l 10 -p \"$4\" -w $1)\" " \
		"&& xprop -id $1 -f $3 8u -set $3 \"$prop\"", \
		"surf-setprop", winid, r, s, p, NULL \
	} \
}

/* BM_ADD(readprop) */
#define BM_ADD(r) {\
	.v = (const char *[]){ "/bin/sh", "-c", \
		"(echo $(xprop -id $0 $1) | cut -d '\"' -f2 " \
		"| sed 's/.*https*:\\/\\/\\(www\\.\\)\\?//' && cat ~/.surf/bookmarks) " \
		"| awk '!seen[$0]++' > ~/.surf/bookmarks.tmp && " \
		"mv ~/.surf/bookmarks.tmp ~/.surf/bookmarks", \
		winid, r, NULL \
	} \
}
#else // !BOOKMARKING_PATCH
#define SETPROP(r, s, p) { \
	.v = (const char *[]){ "/bin/sh", "-c", \
		"prop=\"$(printf '%b' \"$(xprop -id $1 "r" " \
		"| sed -e 's/^"r"(UTF8_STRING) = \"\\(.*\\)\"/\\1/' " \
		"      -e 's/\\\\\\(.\\)/\\1/g')\" " \
		"| dmenu -p '"p"' -w $1)\" " \
		"&& xprop -id $1 -f "s" 8u -set "s" \"$prop\"", \
		"surf-setprop", winid, NULL \
	} \
}
#endif // BOOKMARKING_PATCH

/* DOWNLOAD(URI, referer) */
#if DOWNLOAD_CONSOLE_PATCH
#define DLSTATUS { \
	.v = (const char *[]){ "st", "-e", "/bin/sh", "-c", \
		"while true; do cat $1/* 2>/dev/null || echo \"no downloads\";" \
		"A=; read A; " \
		"if [ $A = \"clean\" ]; then rm $1/*; fi; clear; done", \
		"surf-dlstatus", dlstatus, NULL \
	} \
}

#if AUTO_OPEN_PATCH
#define AUTOOPEN(dest) { \
	.v = (const char *[]){ "/bin/sh", "-c", "xdg-open \"$0\"", dest, NULL } \
}
#endif // AUTO_OPEN_PATCH
#elif ARIA2_PATCH
#define DOWNLOAD(d, r) { \
	.v = (const char *[]){ "/bin/sh", "-c", \
		"cd $4;"\
		"st -e /bin/sh -c \"aria2c -U '$1' " \
		"--referer '$2' --load-cookies $3 --save-cookies $3 '$0';" \
		"sleep 3;\"", \
		d, useragent, r, cookiefile, downloaddir, NULL \
	} \
}
#else
#define DOWNLOAD(u, r) { \
	.v = (const char *[]){ "st", "-e", "/bin/sh", "-c",\
		"curl -g -L -J -O -A \"$1\" -b \"$2\" -c \"$2\"" \
		" -e \"$3\" \"$4\"; read", \
		"surf-download", useragent, cookiefile, r, u, NULL \
	} \
}
#endif // ARIA2_PATCH

/* PLUMB(URI) */
/* This called when some URI which does not begin with "about:",
 * "http://" or "https://" should be opened.
 */
#define PLUMB(u) {\
	.v = (const char *[]){ "/bin/sh", "-c", \
		"xdg-open \"$0\"", u, NULL \
	} \
}

/* VIDEOPLAY(URI) */
#define VIDEOPLAY(u) {\
	.v = (const char *[]){ "/bin/sh", "-c", \
		"mpv --really-quiet \"$0\"", u, NULL \
	} \
}

#if NAVIGATION_HISTORY_PATCH
#define SELNAV { \
	.v = (char *[]){ "/bin/sh", "-c", \
		"prop=\"`xprop -id $0 _SURF_HIST" \
		" | sed -e 's/^.[^\"]*\"//' -e 's/\"$//' -e 's/\\\\\\n/\\n/g'" \
		" | dmenu -i -l 10`\"" \
		" && xprop -id $0 -f _SURF_NAV 8u -set _SURF_NAV \"$prop\"", \
		winid, NULL \
	} \
}
#endif // NAVIGATION_HISTORY_PATCH

#if OMNIBAR_PATCH
#define ONLOAD(u) { \
	.v = (char *[]){"/bin/sh", "-c", \
		"~/.surf/omnibar addhist \"$0\"", u, NULL \
	} \
}

#define GOTO { \
	.v = (char *[]){"/bin/sh", "-c", \
		"~/.surf/omnibar goto \"$0\" \"$1\"", winid, "_SURF_GO", NULL \
	} \
}
#endif // OMNIBAR_PATCH

#if WEB_SEARCH_PATCH
#define SEARCH { \
	.v = (const char *[]){ "/bin/sh", "-c", \
		"xprop -id $1 -f $2 8u -set $2 \"" \
		"$(dmenu -p Search: -w $1 < /dev/null)\"", \
		"surf-search", winid, "_SURF_SEARCH", NULL \
	} \
}
#endif // WEB_SEARCH_PATCH

#if INSTAPAPER_PATCH
#define INSTAPAPER { \
	.v = (char *[]){ "/bin/sh", "-c", \
		"curl -s " \
		" -d username=\"$(cat ~/.surf/instapaper | sed -n '1p')\"" \
		" -d password=\"$(cat ~/.surf/instapaper | sed -n '2p')\"" \
		" -d url=\"$(xprop -id $0 _SURF_URI | cut -d '\"' -f 2)\"" \
		" https://www.instapaper.com/api/add > /dev/null", winid, NULL \
	} \
}
#endif // INSTAPAPER_PATCH

/* styles */
/*
 * The iteration will stop at the first match, beginning at the beginning of
 * the list.
 */
static SiteSpecific styles[] = {
	/* regexp               file in $styledir */
	{ ".*",                 "default.css" },
};

/* certificates */
/*
 * Provide custom certificate for urls
 */
static SiteSpecific certs[] = {
	/* regexp               file in $certdir */
	{ "://suckless\\.org/", "suckless.org.crt" },
};

#if SITE_SPECIFIC_JS_PATCH
/* scripts */
/*
 * Run scripts on certain URLs, will inject more than one script
 */
static SiteSpecific scripts[] = {
	/* regexp                script in $scriptdir */
	{ "://duckduckgo\\.com", "example.js" },
};
#endif // SITE_SPECIFIC_JS_PATCH

#if MODAL_PATCH
#define MODKEY 0
#define Shift GDK_CONTROL_MASK
#else
#define MODKEY GDK_CONTROL_MASK
#define Shift GDK_SHIFT_MASK
#endif // MODAL_PATCH

/* hotkeys */
/*
 * If you use anything else but MODKEY and Shift, then don't forget to
 * edit the CLEANMASK() macro.
 */
static Key keys[] = {
	/* modifier              keyval          function    arg */
	#if USERAGENT_PATCH
	{ MODKEY,                GDK_KEY_a,      spawn,      SETPROP("_SURF_AGENT", "_SURF_AGENT", PROMPT_AGENT) },
	#endif // USERAGENT_PATCH
	#if OMNIBAR_PATCH
	{ MODKEY,                GDK_KEY_g,      spawn,      GOTO },
	#else
	{ MODKEY,                GDK_KEY_g,      spawn,      SETPROP("_SURF_URI", "_SURF_GO", PROMPT_GO) },
	#endif // OMNIBAR_PATCH
	{ MODKEY,                GDK_KEY_f,      spawn,      SETPROP("_SURF_FIND", "_SURF_FIND", PROMPT_FIND) },
	{ MODKEY,                GDK_KEY_slash,  spawn,      SETPROP("_SURF_FIND", "_SURF_FIND", PROMPT_FIND) },
	#if BOOKMARKING_PATCH
	{ MODKEY,                GDK_KEY_m,      spawn,      BM_ADD("_SURF_URI") },
	#endif // BOOKMARKING_PATCH
	#if DOWNLOAD_CONSOLE_PATCH
	/* download-console */
	{ MODKEY,                GDK_KEY_d,      spawndls,   { 0 } },
	#endif // DOWNLOAD_CONSOLE_PATCH
	#if WEB_SEARCH_PATCH
	{ MODKEY,                GDK_KEY_s,      spawn,      SEARCH },
	#endif // WEB_SEARCH_PATCH
	#if INSTAPAPER_PATCH
	{ MODKEY|Shift,          GDK_KEY_x,      spawn,      INSTAPAPER },
	#endif // INSTAPAPER_PATCH

	#if EXTERNALPIPE_PATCH || EXTERNALPIPE_SIGNAL_PATCH
	{ MODKEY,                GDK_KEY_x,      externalpipe, { .v = linkselect_curwin } },
	{ MODKEY|Shift,          GDK_KEY_x,      externalpipe, { .v = linkselect_newwin } },
	{ MODKEY,                GDK_KEY_o,      externalpipe, { .v = editscreen        } },
	#endif // EXTERNALPIPE_PATCH

	#if MODAL_PATCH
	{ 0,                     GDK_KEY_Escape, insert,     { .i = 0 } },
	{ 0,                     GDK_KEY_i,      insert,     { .i = 1 } },
	#else
	{ 0,                     GDK_KEY_Escape, stop,       { 0 } },
	#endif // MODAL_PATCH
	{ MODKEY,                GDK_KEY_c,      stop,       { 0 } },

	#if PLAY_EXTERNAL_PATCH
	{ MODKEY,                GDK_KEY_w,      playexternal, { 0 } },
	#endif // PLAY_EXTERNAL_PATCH

	#if QUIT_PATCH
	{ 0,                     GDK_KEY_q,      quit,       { 0 } },
	#endif // QUIT_PATCH

	{ MODKEY|Shift,          GDK_KEY_r,      reload,     { .i = 1 } },
	{ MODKEY,                GDK_KEY_r,      reload,     { .i = 0 } },

	{ MODKEY,                GDK_KEY_l,      navigate,   { .i = +1 } },
	{ MODKEY,                GDK_KEY_h,      navigate,   { .i = -1 } },
	#if NAVIGATION_HISTORY_PATCH
	{ MODKEY|Shift,          GDK_KEY_h,      selhist,    SELNAV },
	#endif // NAVIGATION_HISTORY_PATCH

	/* vertical and horizontal scrolling, in viewport percentage */
	{ MODKEY,                GDK_KEY_j,      scrollv,    { .i = +10 } },
	{ MODKEY,                GDK_KEY_k,      scrollv,    { .i = -10 } },
	{ MODKEY,                GDK_KEY_space,  scrollv,    { .i = +50 } },
	{ MODKEY,                GDK_KEY_b,      scrollv,    { .i = -50 } },
	{ MODKEY,                GDK_KEY_i,      scrollh,    { .i = +10 } },
	{ MODKEY,                GDK_KEY_u,      scrollh,    { .i = -10 } },

	{ MODKEY|Shift,          GDK_KEY_j,      zoom,       { .i = -1 } },
	{ MODKEY|Shift,          GDK_KEY_k,      zoom,       { .i = +1 } },
	{ MODKEY|Shift,          GDK_KEY_q,      zoom,       { .i = 0  } },
	{ MODKEY,                GDK_KEY_minus,  zoom,       { .i = -1 } },
	{ MODKEY,                GDK_KEY_plus,   zoom,       { .i = +1 } },

	{ MODKEY,                GDK_KEY_p,      clipboard,  { .i = 1 } },
	{ MODKEY,                GDK_KEY_y,      clipboard,  { .i = 0 } },

	{ MODKEY,                GDK_KEY_n,      find,       { .i = +1 } },
	{ MODKEY|Shift,          GDK_KEY_n,      find,       { .i = -1 } },

	{ MODKEY|Shift,          GDK_KEY_p,      print,      { 0 } },
	{ MODKEY,                GDK_KEY_t,      showcert,   { 0 } },

	{ MODKEY|Shift,          GDK_KEY_a,      togglecookiepolicy, { 0 } },
	{ 0,                     GDK_KEY_F11,    togglefullscreen, { 0 } },
	{ MODKEY|Shift,          GDK_KEY_o,      toggleinspector, { 0 } },
	#if SHORT_TITLE_PATCH
	{ MODKEY|Shift,          GDK_KEY_e,      toggletitle, { 0 } },
	#endif // SHORT_TITLE_PATCH

	{ MODKEY|Shift,          GDK_KEY_c,      toggle,     { .i = CaretBrowsing } },
	{ MODKEY|Shift,          GDK_KEY_g,      toggle,     { .i = Geolocation } },
	{ MODKEY|Shift,          GDK_KEY_s,      toggle,     { .i = JavaScript } },
	{ MODKEY|Shift,          GDK_KEY_i,      toggle,     { .i = LoadImages } },
	{ MODKEY|Shift,          GDK_KEY_b,      toggle,     { .i = ScrollBars } },
	#if NOTIFICATIONS_PATCH
	{ MODKEY|Shift,          GDK_KEY_l,      toggle,     { .i = Notifications } },
	#endif // NOTIFICATIONS_PATCH
	{ MODKEY|Shift,          GDK_KEY_t,      toggle,     { .i = StrictTLS } },
	{ MODKEY|Shift,          GDK_KEY_m,      toggle,     { .i = Style } },
	{ MODKEY|Shift,          GDK_KEY_d,      toggle,     { .i = DarkMode } },
};

/* button definitions */
/* target can be OnDoc, OnLink, OnImg, OnMedia, OnEdit, OnBar, OnSel, OnAny */
static Button buttons[] = {
	/* target       event mask      button  function        argument        stop event */
	#if MIDDLE_CLICK_TO_PLUMB_PATCH
	{ OnAny,        0,              2,      clickplumb,     { .i = 0 },     1 },
	#else
	{ OnLink,       0,              2,      clicknewwindow, { .i = 0 },     1 },
	#endif // MIDDLE_CLICK_TO_PLUMB_PATCH
	{ OnLink,       MODKEY,         2,      clicknewwindow, { .i = 1 },     1 },
	{ OnLink,       MODKEY,         1,      clicknewwindow, { .i = 1 },     1 },
	{ OnAny,        0,              8,      clicknavigate,  { .i = -1 },    1 },
	{ OnAny,        0,              9,      clicknavigate,  { .i = +1 },    1 },
	{ OnMedia,      MODKEY,         1,      clickexternplayer, { 0 },       1 },
};

#if ALIASES_PATCH
/* Add your aliases here */
static Alias aliases[] = {
	/* Alias        URI */
	{ "ddg",       "https://duckduckgo.com" },
	{ "wikipedia", "https://www.wikipedia.org" }
};
#endif // ALIASES_PATCH

#if CHROMEBAR_PATCH || SPACE_SEARCH_PATCH || WEB_SEARCH_PATCH
/* Default search engine */
static const char *searchengine = "https://duckduckgo.com/?q=%s";
#endif

#if CHROMEBAR_PATCH || SEARCH_ENGINES_PATCH
static SearchEngine searchengines[] = {
	{ "g",   "http://www.google.de/search?q=%s"   },
	{ "leo", "http://dict.leo.org/ende?search=%s" },
};
#endif // CHROMEBAR_PATCH | SEARCH_ENGINES_PATCH
