/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-misc-*-medium-r-normal-*-14-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#999999";
static const char normbgcolor[]     = "#000066";
static const char normfgcolor[]     = "#ffffff";
static const char selbordercolor[]  = "#333333";
static const char selbgcolor[]      = "#ccccff";
static const char selfgcolor[]      = "#000066";
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = False;    /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "ichi", "ni", "san", "yon", "go", "roku", "nana", "hachi", "kyuu" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1,            False,       -1 },
 	{ "opera",    NULL,       NULL,       1,            True,        -1 },
 	{ "zathura",  NULL,       NULL,       1,            True,        -1 },
 	{ "MPlayer",  NULL,       NULL,       1,            True,        -1 },
 	{ "aterm",    NULL,       NULL,       1,            False,       -1 },
 	{ "squeak",   NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* False means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "^_^",      NULL },    /* no layout function means floating behavior */
	{ "o_O",      tile },    /* first entry is default */
	{ "-.-",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *browsercmd[]  = { "opera", NULL };
static const char *utermtmuxcmd[]  = { "uxterm", "-si", "-vb", "+sb", "-fullscreen", "-C", "-e", "tmux new-session -d -s hajime \"tmux source ~/.tmux.conf.$HOST\"; exec tmux attach", NULL };
static const char *utermtmuxattachcmd[]  = { "uxterm", "-si", "-vb", "+sb", "-fullscreen", "-C", "-e", "exec tmux -2u attach", NULL };
static const char *xtrlockcmd[]  = { "xtrlock", NULL };
static const char *viewercmd[]  = { "evince", NULL };
static const char *screenshotcmd[]  = { "shot", NULL };
#ifdef __linux__
static const char *shutdowncmd[]  = { "sudo", "poweroff", NULL };
static const char *rebootcmd[]  = { "sudo", "reboot", NULL };
#else
static const char *shutdowncmd[]  = { "sudo", "shutdown", "-p", "now", NULL };
static const char *rebootcmd[]  = { "sudo", "shutdown", "-r", "now", NULL };
#endif

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_e,      spawn,          {.v = viewercmd } },
	{ MODKEY,                       XK_o,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = screenshotcmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = xtrlockcmd } },
	{ MODKEY,                       XK_u,      spawn,          {.v = utermtmuxcmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = utermtmuxattachcmd } },
	{ MODKEY|ControlMask,           XK_f,      spawn,          {.v = shutdowncmd } },
	{ MODKEY|ControlMask,           XK_r,      spawn,          {.v = rebootcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be a tag number (starting at 0),
 * ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

