
#if CHROMEBAR_PATCH
#include "chromebar.c"
#elif SEARCH_ENGINES_PATCH
#include "searchengines.c"
#endif
#if DOWNLOAD_CONSOLE_PATCH
#include "dlconsole.c"
#endif
#if EXTERNALPIPE_PATCH || EXTERNALPIPE_SIGNAL_PATCH
#include "externalpipe.c"
#endif
#if FIFO_PATCH
#include "fifo.c"
#endif
#if HISTORY_PATCH && !CHROMEBAR_PATCH
#include "history.c"
#endif
#if ICON_PATCH
#include "icon.c"
#endif
#if MIDDLE_CLICK_TO_PLUMB_PATCH
#include "click_to_plumb.c"
#endif
#if MODAL_PATCH
#include "insert.c"
#endif
#if NAVIGATION_HISTORY_PATCH
#include "navigation_history.c"
#endif
#if PLAY_EXTERNAL_PATCH
#include "playexternal.c"
#endif
#if QUIT_PATCH
#include "quit.c"
#endif
#if SCROLL_FASTER_PATCH
#include "scroll_faster.c"
#endif
#if SHORT_TITLE_PATCH
#include "short_title.c"
#endif
#if SITE_SPECIFIC_JS_PATCH
#include "sitejs.c"
#endif
#if URL_FILTERING_PATCH
#include "url_filtering.c"
#endif
#if USERAGENT_PATCH
#include "useragent.c"
#endif
#if WEB_SEARCH_PATCH
#include "web_search.c"
#endif
#if ZOOMMTG_HANDLER_PATCH
#include "zoommtg_handler.c"
#endif
