/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-normal-*-14-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#999999";
static const char normbgcolor[]     = "#999999";
static const char normfgcolor[]     = "#000000";
static const char selbordercolor[]  = "#999999";
static const char selbgcolor[]      = "#666666";
static const char selfgcolor[]      = "#ffffff";
static unsigned int borderpx        = 1;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */
static Bool showbar                 = False;     /* False means no bar */
static Bool topbar                  = True;     /* False means bottom bar */

/* tagging */
static const char tags[][MAXTAGLEN] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static Rule rules[] = {
	/* class      instance    title       tags mask     isfloating */
	{ "Gimp",     NULL,       NULL,       0,            True },
	{ "opera",    NULL,       NULL,       1,            False },
	{ "Firefox",  NULL,       NULL,       1,            False },
	{ "MPlayer",  NULL,       NULL,       1,            True },
	{ "aterm",    NULL,       NULL,       1,            False },
	{ "squeak",   NULL,       NULL,       0,            False },
} ;

/* layout(s) */
static float mfact      = 0.55;
static Bool resizehints = False; /* False means respect size hints in tiled resizals */

static Layout layouts[] = {
	/* symbol     arrange function */
	{ "^_^",      NULL },    /* no layout function means floating behavior */
	{ "o_O",      tile },    /* first entry is default */
	{ "*_*",      monocle },
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
static const char *termcmd[]  = { "aterm", "-bg", "black", "-fg", "#009999", "-cr", "#999900", "-pr", "#999900", "-tr", "-fade", "80", "-tint", "#666666", "-tinttype", "true", "-si", "-vb", "-trsb", "+sb", "-sr", "-geometry", "182x72+0+0", "-sl", "9999", "-tn", "xterm", "-C" , NULL };
static const char *xtrlock[]  = { "xtrlock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = xtrlock } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be a tag number (starting at 0),
 * ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

