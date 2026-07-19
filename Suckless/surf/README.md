Similar to [dwm-flexipatch](https://github.com/bakkeby/dwm-flexipatch) this surf 2.1
(48517e5, 2025-04-19) project has a different take on surf patching. It uses preprocessor
directives to decide whether or not to include a patch during build time. Essentially this
means that this build, for better or worse, contains both the patched _and_ the original code.
The aim being that you can select which patches to include and the build will contain that code
and nothing more.

For example to include the `aliases` patch then you would only need to flip this setting from
0 to 1 in [patches.h](https://github.com/bakkeby/surf-flexipatch/blob/master/patches.def.h):
```c
#define ALIASES_PATCH 1
```

Once you have found out what works for you and what doesn't then you should be in a better
position to choose patches should you want to start patching from scratch.

Alternatively if you have found the patches you want, but don't want the rest of the flexipatch
entanglement on your plate then you may want to have a look at
[flexipatch-finalizer](https://github.com/bakkeby/flexipatch-finalizer); a custom pre-processor
tool that removes all the unused flexipatch code leaving you with a build that contains the
patches you selected.

Refer to [https://surf.suckless.org/](https://surf.suckless.org/) for details on the surf browser,
how to install it and how it works.

Browsing patches? There is a [map of patches](https://coggle.it/diagram/abR5tfNyq1RiOSoJ) diagram
which tries to organise patches into categories.

---

### Changelog:

2026-03-12 - Added the autoopen, dlconsole and url-filtering patches

2026-03-11 - Added the externalpipe, externalpipe-signal, instapaper, keycodes, play-external,
searchengines, sitejs and web-search patches

2026-03-10 - Added the multijs, navigation-history, omnibar, short-title, space search,
useragent and allow popup on gesture patches

2026-03-09 - Added the modal patch

2026-03-08 - Added the fifo, gtkblackbg, history, homepage, middle-click-plumb, notifications,
proxyconfig, startgo, unicode-in-dmenu, xdg and zoommtg-handler patches

2026-03-07 - Added the following patches: aliases, aria2, bookmarking, cachedir, chromebar,
clipboard-instead-of-primary, icon, quit-hotkey, scroll-faster

### Patches included:

   - [aliases](https://surf.suckless.org/patches/aliases/)
      - replaces aliases with a URI specified in your config file

   - [aria2](https://surf.suckless.org/patches/aria2/)
      - use aria2 instead of curl as default download manager

   - [auto-open](https://surf.suckless.org/patches/autoopen/)
      - uses xdg-open to open a download once it has finished

   - [bookmarking](https://surf.suckless.org/patches/bookmarking/)
      - uses cat to add all strings from ~/.surf/bookmarks to the input dmenu
      - ctrl-m is used to add a new bookmark

   - [cachedir](https://surf.suckless.org/patches/cachedir/)
      - use the -h command-line option to determine a custom cache directory

   - [chromebar](https://surf.suckless.org/patches/chromebar/)
      - parses what you type in the dmenu window when you input new address or a query
      - if what you wrote is not an internet address or a file URI then it will use a
        default search engine to query for that phrase

   - [clipboard-instead-of-primary](https://surf.suckless.org/patches/clipboard-instead-of-primary/)
      - adds a config option that allows surf to use the CLIPBOARD selection instead of PRIMARY

   - [dlconsole](https://surf.suckless.org/patches/dlconsole/)
      - removes the original downloading method of calling an external tool
      - adds built-in support for downloads
      - adds a simple console display with a list of downloads, triggered with Ctrl+d

   - [externalpipe](https://surf.suckless.org/patches/externalpipe/)
      - pipe the current page's source to an external program

   - [externalpipe-signal](https://surf.suckless.org/patches/externalpipe-signal/)
      - the externalpipe command upon receiving the SIGUSR1 signal

   - [fifo](https://surf.suckless.org/patches/fifo/)
      - adds a small command language that allows the browser to be controlled through a FIFO pipe

   - [gtkblackbg](https://surf.suckless.org/patches/gtkblackbg/)
      - adds a black background to the GTK window and make this visible by hiding the background
        of the WebKit view
      - this effectively eliminates the momentary white screen that shows after launching surf

   - [history](https://surf.suckless.org/patches/history/)
      - writes the loaded URI to a file

   - [homepage](https://surf.suckless.org/patches/homepage/)
      - allows for a homepage to be loaded when a URI has not been set

   - [icon](https://surf.suckless.org/patches/icon/)
      - sets the \_NET_WM_ICON ewmh property for gtk-created windows

   - [instapaper](https://surf.suckless.org/patches/instapaper/)
      - add the current page to instapaper

   - [keycodes](https://surf.suckless.org/patches/keycodes/)
      - key input handling is done with keycodes instead of keysyms
      - this way, input is independant from keyboard layout

   - [middle-click-plumb](https://surf.suckless.org/patches/middle-click-plumb/)
      - middle click link or text selection to send it to plumber

   - [modal](https://surf.suckless.org/patches/modal/)
      - adds an insert mode to surf where hotkeys without a MODKEY cannot be used
      - this allows you to type into a text area without hotkeys interferring

   - [multijs](https://surf.suckless.org/patches/multijs/)
      - replaces scriptfile with an array of scripts
      - this allows for the inclusion of multiple javascript files rather than one massive one

   - [navigation-history](https://surf.suckless.org/patches/navigation-history/)
      - adds the MOD-shift-h keyboard shortcut to open up dmenu with the recent navigation
        history of the current surf instance

   - [notifications](https://surf.suckless.org/patches/notifications/)
      - adds support for HTML5 Web Notifications

   - [omnibar](https://surf.suckless.org/patches/omnibar/)
      - run a command each time an URI is loaded

   - [play-external](https://surf.suckless.org/patches/playexternal/)
      - pipes the current page uri to mpv when a hotkey is pressed

   - [popup-on-gesture](https://surf.suckless.org/patches/popup-on-gesture/)
      - enable same-window popup on user gesture
      - some pages won't work correctly without this, while others redirect to spam

   - [proxyconfig](https://surf.suckless.org/patches/proxyconfig/)
      - allows you to specify proxy settings in your config file

   - [quit-hotkey](https://surf.suckless.org/patches/quit-hotkey/)
      - adds 'mod+q' as a hotkey to quit

   - [scroll-faster](https://surf.suckless.org/patches/scroll-faster/)
      - allows you to make the mouse wheel scroll faster
      - it simply multiplies the delta_y from GDK event and pass it forward

   - [searchengines](https://surf.suckless.org/patches/searchengines/)
      - allows for the simple use of search engines
      - chromebar is an extension of this patch and takes precedence

   - [short-title](https://surf.suckless.org/patches/short-title/)
      - improves readability of the title when using surf with tabbed by hiding status information

   - [sitejs](https://surf.suckless.org/patches/sitejs/)
      - allows scripts to be injected based on the url matching a regex, allowing scripts
        to be site-specific
      - can serve as a more complex replacement for the multijs patch

   - [smoothscrolling-via-GTK3](https://surf.suckless.org/patches/smoothscrolling-via-GTK3/)
      - enable smooth scrolling by compiling surf with GTK3 instead of GTK2
      - (merged upstream)

   - [spacesearch](https://surf.suckless.org/patches/spacesearch/)
      - makes surf treat \_SURF_URI string with leading whitespace as search query

   - [startgo](https://surf.suckless.org/patches/startgo/)
      - adds options to start surf straight into the GO menu via a -H command line option

   - [unicode-in-dmenu](https://surf.suckless.org/patches/unicode-in-dmenu/)
      - adds Unicode support to actions with dmenu: opening URL and finding in page
      - (merged upstream)

   - [url-filtering](https://surf.suckless.org/patches/url-filtering/)
      - adds URL filtering support to surf
      - this can be used to remove advertisements, as an example

   - [useragent](https://surf.suckless.org/patches/useragent/)
      - adds the \_SURF_AGENT xproperty which allows updating surf's useragent during runtime

   - [web-search](https://surf.suckless.org/patches/web-search/)
      - simple patch that adds a search feature (e.g. DuckDuckGo search)

   - [xdg](https://surf.suckless.org/patches/xdg/)
      - adds xdg desktop entries for surf and surf-open.sh
      - (merged, can be reverted)

   - [zoommtg-handler](https://surf.suckless.org/patches/zoommtg-handler/)
      - uses xdg-open to open zoommtg links
