
#if CHROMEBAR_PATCH
#include "chromebar.h"
#elif SEARCH_ENGINES_PATCH
#include "searchengines.h"
#endif
#if DOWNLOAD_CONSOLE_PATCH
#include "dlconsole.h"
#endif
#if EXTERNALPIPE_PATCH || EXTERNALPIPE_SIGNAL_PATCH
#include "externalpipe.h"
#endif
#if FIFO_PATCH
#include "fifo.h"
#endif
#if HISTORY_PATCH && !CHROMEBAR_PATCH
#include "history.h"
#endif
#if ICON_PATCH
#include "icon.h"
#include "surf.xpm"
#endif
#if MIDDLE_CLICK_TO_PLUMB_PATCH
#include "click_to_plumb.h"
#endif
#if MODAL_PATCH
#include "insert.h"
#endif
#if NAVIGATION_HISTORY_PATCH
#include "navigation_history.h"
#endif
#if PLAY_EXTERNAL_PATCH
#include "playexternal.h"
#endif
#if QUIT_PATCH
#include "quit.h"
#endif
#if SCROLL_FASTER_PATCH
#include "scroll_faster.h"
#endif
#if SHORT_TITLE_PATCH
#include "short_title.h"
#endif
#if SITE_SPECIFIC_JS_PATCH
#include "sitejs.h"
#endif
#if URL_FILTERING_PATCH
#include "url_filtering.h"
#endif
#if USERAGENT_PATCH
#include "useragent.h"
#endif
#if WEB_SEARCH_PATCH
#include "web_search.h"
#endif
#if ZOOMMTG_HANDLER_PATCH
#include "zoommtg_handler.h"
#endif
