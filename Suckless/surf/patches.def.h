/*
 * This file contains patch control flags.
 *
 * In principle you should be able to mix and match any patches
 * you may want. In cases where patches are logically incompatible
 * one patch may take precedence over the other as noted in the
 * relevant descriptions.
 */

/* Replaces aliases with a URI specified in your config file.
 *
 * https://surf.suckless.org/patches/aliases/
 */
#define ALIASES_PATCH 0

/* Use aria2 instead of curl as default download manager.
 *
 * https://surf.suckless.org/patches/aria2/
 */
#define ARIA2_PATCH 0

/* This patch uses xdg-open to open a download once it has finished.
 *
 * This functionality is implemented specifically in relation to the
 * download console (dlconsole) patch. To get this working for normal
 * downloads or the aria2 patch you will need to alter the DOWNLOAD
 * macro to pass the downloaded file to xdg-open when it is done.
 *
 * The strategy of the original patch was:
 *    - deduce the downloaded file path based on the download directory
 *      and the basename of the URL, and store that in a variable
 *    - initiate the download tool (was wget back then) specifying where
 *      to store the downloaded file by referring to the variable
 *    - after the download command is finished run xdg-open passing the
 *      variable containing the file path
 *
 * https://surf.suckless.org/patches/autoopen/
 */
#define AUTO_OPEN_PATCH 0

/* Uses cat to add all strings from ~/.surf/bookmarks to the input dmenu.
 * Ctrl-m is used to add a new bookmark.
 *
 * https://surf.suckless.org/patches/bookmarking/
 */
#define BOOKMARKING_PATCH 0

/* Use the -h command-line tag to determine a custom cache directory.
 * surf -h /path/to/cache/directory/
 *
 * https://surf.suckless.org/patches/cachedir/
 */
#define CACHEDIR_PATCH 0

/* This patch is an extension of the searchengines patch. It parses what you
 * type in the dmenu window when you input new address or a query. If what you
 * wrote is not an internet address or a file uri then it will use a default
 * search engine to query for that phrase: like the chrome bar does.
 *
 * https://surf.suckless.org/patches/chromebar/
 */
#define CHROMEBAR_PATCH 0

/* Use the GTK clipboard instead of primary selection.
 * By default surf's clipboard function access the PRIMARY gtk selection. This
 * patch adds a config option (ClipboardNotPrimary) that allows surf to use the
 * CLIPBOARD selection.
 *
 * https://surf.suckless.org/patches/clipboard-instead-of-primary/
 */
#define CLIPBOARD_INSTEAD_OF_PRIMARY_PATCH 0

/* Built-in downloading with console display
 *
 * This patch removes the original downloading method of calling an external tool
 * and adds built-in support for downloads, along with a simple console display
 * with a list of downloads.
 *
 * To open the downloads list, press Ctrl+d.
 * This list must be manually refreshed: simply press enter to do so.
 * If you enter clean as a command, the list will be cleared. The shell command
 * called to show the downloads is defined by the macro DLSTATUS in the config.
 *
 * This patch takes precedence over the aria2 patch.
 *
 * https://surf.suckless.org/patches/dlconsole/
 */
#define DOWNLOAD_CONSOLE_PATCH 0

/* Pipe the current page's source to an external program.
 * This is particularly helpful for keyboard-based link following and also for
 * viewing the source in an external editor.
 *
 * surf-flexipatch includes the example configuration from the patch page
 * bound to Ctrl+x, Ctrl+shift+x and Ctrl+o.
 *
 * Make sure to download the example scripts if you want to test this out.
 *
 * https://surf.suckless.org/patches/externalpipe/
 * https://surf.suckless.org/patches/externalpipe/surf_linkselect.sh
 * https://surf.suckless.org/patches/externalpipe/edit_screen.sh
 */
#define EXTERNALPIPE_PATCH 0

/* Run an externalpipe command upon receiving the SIGUSR1 signal.
 * This can be helpful for supporting externalpipe scripts that work across
 * multiple surf instances.
 *
 * With the example script you can access a dmenu populated with the contents
 * of all tags contents of all open surf windows for directly pasting.
 *
 * https://surf.suckless.org/patches/externalpipe-signal/
 * https://surf.suckless.org/patches/externalpipe-signal/externalpipe_buffer.sh
 */
#define EXTERNALPIPE_SIGNAL_PATCH 0

/* This patch adds a small command language that allows the browser to be
 * controlled through a FIFO pipe. The format of the language is:
 *
 *    [command] [argument]
 *
 * The fifo pipe of the window is stored in the ~/.surf/fifo/ directory by
 * default, with the name of the file being the window id.
 *
 * Most of the commands are the same as their respective functions, (loaduri,
 * scrollv, scrollh, etc.), though there are a couple that are different.
 * In addition, a new function (injectjs) was added to allow injection of
 * javascript through the pipe, though it can also be bound to a key.
 *
 * https://surf.suckless.org/patches/fifo/
 */
#define FIFO_PATCH 0

/* Adds a black background to the GTK window and make this visible by hiding
 * the background of the WebKit view. This effectively eliminates the momentary
 * white screen that shows after launching surf.
 *
 * Combine this patch with darkmode CSS styles and/or an enabled DarkMode
 * setting in config.h for a completely darkened surfing experience.
 *
 * https://surf.suckless.org/patches/gtkblackbg/
 */
#define GTK_BLACK_BACKGROUND_PATCH 0

/* This patch writes the loaded URI to a file and that is all it does.
 * Refer to the patch page for usage tips. Note that the chromebar patch
 * takes precedence over this patch.
 *
 * https://surf.suckless.org/patches/history/
 */
#define HISTORY_PATCH 0

/* This patch allows for a homepage to be loaded when a URI has not been set.
 *
 * https://surf.suckless.org/patches/homepage/
 */
#define HOMEPAGE_PATCH 0

/* This patch sets the _NET_WM_ICON ewmh property for gtk-created windows.
 * This property is used by some window managers to display an icon for the
 * window on the title bar. It is also used by some programs (like pagers and
 * taskbars) to show a miniature for the window.
 *
 * This patch sets icons of size 16x16, 32x32 and 48x48. The icons are found in
 * the file lib/surf.xpm, which is included directly in the source code. The
 * icons look like surf.png except that they have a white border (to make them
 * distinguishable on dark taskbars/titlebars), and the proportion is slightly
 * modified to make the image fit on small icons.
 *
 * https://surf.suckless.org/patches/icon/
 */
#define ICON_PATCH 0

/* Adds a keybinding Ctrl+Shift+x to add the current page to instapaper.
 *
 * Your instapaper credentials should be saved in ~/.surf/instapaper:
 *
 *    Email first line
 *    Password second line
 *
 * https://surf.suckless.org/patches/instapaper/
 */
#define INSTAPAPER_PATCH 0

/* With this patch, key input handling is done with keycodes instead of keysyms.
 * This way, input is independant from keyboard layout. You can adapt config.h to
 * your keyboard by looking up keycodes, for example, using xev.
 *
 * In order to reduce clutter and having to have two sets of keybindings,
 * surf-flexipatch only applies the code changes from this patch. That means that
 * if you are interested in using keycodes instead of keysyms then you will have
 * to replace all keys in config.h on your own. E.g. GDK_KEY_a --> 38.
 *
 * https://surf.suckless.org/patches/keycodes/
 */
#define KEYCODES_PATCH 0

/* Middle click link or text selection to send it to plumber.
 *
 * https://surf.suckless.org/patches/middle-click-plumb/
 */
#define MIDDLE_CLICK_TO_PLUMB_PATCH 0

/* This patch adds an insert mode to surf.
 * While in the insert mode hotkeys without a MODKEY cannot be used.
 * This allows you to type into a text area without hotkeys interferring.
 *
 * In practice this means that MODKEY will be set to no modifier, thus
 * affecting all keybindings that involves the MODKEY macro.
 *
 * If you manage your keybindings in a different way then you should at
 * least have two hotkeys calling the insert function:
 *
 *    { 0,                     GDK_KEY_i,      insert,     { .i = 1 } },
 *    { 0,                     GDK_KEY_Escape, insert,     { .i = 0 } },
 *
 * Note that if the modifier is 0, GDK_KEY_Escape is the only key that you
 * can use to get out of the insert mode.
 *
 * https://surf.suckless.org/patches/modal/
 */
#define MODAL_PATCH 0

/* This patch replaces scriptfile with an array of scripts. This allows for
 * the inclusion of multiple javascript files rather than a single file.
 *
 * https://surf.suckless.org/patches/multijs/
 */
#define MULTIJS_PATCH 0

/* This patch adds the Ctrl-Shift-h keyboard shortcut to open up dmenu with
 * the recent navigation history of the current surf instance.
 *
 * https://surf.suckless.org/patches/navigation-history/
 */
#define NAVIGATION_HISTORY_PATCH 0

/* Adds support for HTML5 Web Notifications
 *
 * Enable by either passing the -L argument or by pressing Ctrl-Shift-L
 * on the window.
 *
 * https://surf.suckless.org/patches/notifications/
 */
#define NOTIFICATIONS_PATCH 0

/* Run a command each time an URI is loaded. Since the URI may be passed as argument,
 * this patch along with a proper script allows to manage browsing history in many
 * convenient ways.
 *
 * The omnibar script is used to store all URIs, including ones visited by clicking
 * on links, and use them to auto-complete when you type on dmenu. The items are
 * sorted by number of views.
 *
 * For tabbed users, you may also want to add the following to your tabbed config.h:
 *
 *    #define GOTO { \
 *        .v = (char *[]){"/bin/sh", "-c", \
 *            "~/.surf/omnibar goto $0 $1", winid, "_TABBED_SELECT_TAB", NULL \
 *        } \
 *    }
 *
 * Note that to use this patch you need to download the "omnibar" shell script,
 * store it under ~/.surf/omnibar, and remember to chmod -x it. The shell script
 * is not included with surf-flexipatch.
 *
 * Also note that the Atom property format changed from plain strings to
 * unicode support. So in scripts like omnibar the xprop command the format
 * specifier need to change from 8s to 8u.
 *
 * https://surf.suckless.org/patches/omnibar/
 * https://raw.githubusercontent.com/clamiax/.surf/374e101748093215e8ecbf00a24a764932b60ed7/omnibar
 */
#define OMNIBAR_PATCH 0

/* This patch pipes the current page uri to mpv when a hotkey (Ctrl+w) is pressed.
 *
 * https://surf.suckless.org/patches/playexternal/
 */
#define PLAY_EXTERNAL_PATCH 0

/* Enable same-window popup on user gesture.
 * Note that some pages won't work correctly without that, while others
 * redirect to spam pages though.
 *
 * https://surf.suckless.org/patches/popup-on-gesture/
 */
#define POPUP_ON_GESTURE_IN_SAME_WINDOW_PATCH 0

/* Variant of the above that opens the popup in a new window rather than
 * the same window.
 */
#define POPUP_ON_GESTURE_IN_NEW_WINDOW_PATCH 0

/* This patch allows you to specify proxy settings in your config file.
 *
 * Three proxy modes in Webkit is supported:
 *    - CustomProxy: specify a custom proxy URL and list of hosts to ignore
 *    - SystemProxy: use your desktop environment proxy settings or
 *                   http_proxy environment variable
 *    - NoProxy: ensures that a proxy is never used
 *
 * Refer to the patch page for usage examples.
 *
 * https://surf.suckless.org/patches/proxyconfig/
 */
#define PROXY_CONFIG_PATCH 0

/* This patch adds Ctrl+q as a hotkey to quit surf.
 *
 * https://surf.suckless.org/patches/quit-hotkey/
 */
#define QUIT_PATCH 0

/* This patch allows you to make your mouse wheel scroll faster.
 * It simply multiplies the delta_y from GDK event and pass it forward.
 *
 * https://surf.suckless.org/patches/scroll-faster/
 */
#define SCROLL_FASTER_PATCH 0

/* This patch allows the simple use of search engines.
 *
 * You can access each search engine by adding the prefix, defined in the
 * searchengines array in the config, in front of your keywords, e.g.
 *
 *    g foo bar
 *
 * Note that the chromebar patch is an extension of this patch and takes
 * precedence.
 *
 * https://surf.suckless.org/patches/searchengines/
 */
#define SEARCH_ENGINES_PATCH 0

/* This provides a patch to improve readability of the title when using
 * surf with tabbed. This allows the user to hide status information from
 * the title of surf.
 * In particular it removes the Indicators of Operation and Indicators of
 * Web Page from the title. Refer the man page for their definition.
 *
 * Either pass a -E [1|0] as a command line argument to use extended/short
 * extended title respectively or use Ctrl+Shift+e to toggle between the two.
 *
 * https://surf.suckless.org/patches/short-title/
 */
#define SHORT_TITLE_PATCH 0

/* This patch allows scripts to be injected based on the url matching
 * a regular expression, allowing scripts to be site-specfic.
 *
 * It also can serve as a more complex replacement for the multijs patch.
 *
 * https://surf.suckless.org/patches/sitejs/
 */
#define SITE_SPECIFIC_JS_PATCH 0

/* This patch makes surf treat _SURF_URI string with leading whitespace as
 * search query. The search engine to send queries to is defined in the config
 * file and the patch is compatible with the chromebar patch.
 *
 * https://surf.suckless.org/patches/spacesearch/
 */
#define SPACE_SEARCH_PATCH 0

/* This patch adds options to start surf straight into the GO menu.
 * Example usage would be in combinations with patches like bookmarking
 * and search engines.
 *
 * This can be enabled via the -H command line option or alternatively
 * surf can always do this by default.
 *
 * https://surf.suckless.org/patches/startgo/
 */
#define STARTGO_PATCH 0

/* This patch adds URL filtering support to surf.
 *
 * This can be used to remove advertisements, as an example. The filters
 * file, defaulting to ~/.surf/filters, contains POSIX regular expressions
 * (see the re_format(7) manpage). If a HTTP request is about to be made
 * for a URL that matches any of the expressions in the file, then the
 * request will simply be ignored. This may lead to slightly broken display
 * on pages that expect e.g. images to load correctly.
 *
 * An example list of filters may look like this:
 *
 *    /favicon\.ico$
 *    eviladvertismentcompany\.{net,com}/ads
 *
 * The implementation in surf-flexipatch differs from the original patch in
 * that filters are read, parsed and compiled during runtime. In the original
 * patch the filter strings are baked in during compile time, which has the
 * side effect of requiring that surf is recompiled whenever new filters are
 * added. This is not necessary here.
 *
 * https://surf.suckless.org/patches/url-filtering/
 */
#define URL_FILTERING_PATCH 0

/* Also print to standard out whether a URI is filtered or not. */
#define URL_FILTERING_VERBOSE_PATCH 0

/* This patch adds the _SURF_AGENT xproperty which allows updating surf's
 * useragent during runtime. It may be useful to have a file of predefined
 * useragents to pipe through dmenu, or to have a script use xprop and set
 * it for you.
 *
 * https://surf.suckless.org/patches/useragent/
 */
#define USERAGENT_PATCH 0

/* Simple patch that adds a search feature. Use Ctrl+s to search DuckDuckGo.
 *
 * https://surf.suckless.org/patches/web-search/
 */
#define WEB_SEARCH_PATCH 0

/* The XDG patch adds xdg desktop entries for surf and surf-open.sh, and
 * it installs surf.png as the icon "suckless-surf.png".
 *
 * Note that surf-open.sh must be installed to /usr/local/bin/surf-open for
 * the surf-open desktop entry to work.
 *
 * As this patch makes changes to the Makefile only it has been merged in
 * rather than being an an optional toggle.
 *
 * To see what the patch changed run this command:
 *
 *    git diff a9202e0^1 a9202e0
 *
 * To remove the patch run this command:
 *
 *    git revert a9202e0
 *
 * https://surf.suckless.org/patches/xdg/
 */

/* This patch uses xdg-open to open zoommtg links
 *
 * https://surf.suckless.org/patches/zoommtg-handler/
 */
#define ZOOMMTG_HANDLER_PATCH 0
