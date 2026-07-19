/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

static const struct arg args[] = {
	/* function       format                    argument */

	/* Disk */
	{ disk_free,      " 󰋊 %s ",               "/"      },

	/* Network - change enp0s25 to your interface (ip a) */
	{ netspeed_rx,    " 󰇚 %s ",               "enp0s25" },
	{ netspeed_tx,    " 󰕒 %s ",               "enp0s25" },

	/* CPU */
	{ cpu_perc,       " 󰻠 %s%% ",             NULL     },

	/* RAM */
	{ ram_used,       " 󰍛 %s ",               NULL     },

	/* Volume */
	{ run_command, " 󰕾 %s%% ", "wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{printf \"%d\", $2 * 100}'" },

	/* Date / Time */
	{ datetime,       " 󰸘 %s  ",             "%a %d %b" },
	{ datetime,       " 󱑎 %s  ",             "%H:%M"    },
};
