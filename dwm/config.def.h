/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx		= 12;			/* gaps betwees windows */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad				= 12;
static const int sidepad				= 12;
static const char *fonts[]          = { "JetBrains Mono Nerd Font:size=10:antialias=true:bold" };
static const char col_dark[]			= "#1c1b1f";
static const char col_gray[]			= "#a9a9b9";
static const char col_light[]       = "#e7e7fc";
static const char col_accent[]		= "#d85895"; // 5a24ff  2b2c32
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray, col_dark, col_dark },
	[SchemeSel]  = { col_light, col_accent, col_accent },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title		tags mask		isfloating		isterminal		noswallow	  monitor */
	{ "Mindustry", NULL,		  NULL,		0,					0,					0,					0,				  -1 },
	{ "Nvidia-settings", "nvidia-settings", "NVIDIA Settings", 0, 1,	0,					0,				  -1 },
	{ "Pulseaudio-equalizer-gtk", "pulseaudio-equalizer-gtk", "PulseAudio Equalizer", 0, 1, 0, 0,  -1 },
	{ "Alacritty", NULL,		  NULL,		0,					0,					1,					0,				  -1 },
	{ NULL,			NULL,		  "Event Tester", 0,			1,					0,					1,				  -1 },
};

static const MonitorRule monrules[] = {
	/* monitor layout  mfact  nmaster  showbar  topbar */
	{  1,      4,      -1,    -1,      -1,      -1     }, // use a different layout for the second monitor
	{  -1,     0,      -1,    -1,      -1,      -1     }, // default
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "[]—",    tile },
	{ "—|—",		gaplessgrid },
	{ "[F]",		NULL },
	{ "|⊤|",		bstack },
	{ "|—|",		bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_Down,	ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_Up,		ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave,	ACTION##stack, {.i = PREVSEL } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-y", "56", "-x", "12", "-z", "390", "-l", "18", NULL };

static const Key keys[] = {
	/* modifier							key			function        argument */
	{ MODKEY|ShiftMask,				XK_Return,	spawn,          {.v = dmenucmd } },
	{ MODKEY,		               XK_Return,	spawn,          {.v = (const char*[]) { "alacritty", NULL } } },
	{ MODKEY,							XK_h,			togglebar,      {0} },
	STACKKEYS(MODKEY,									focus)
	STACKKEYS(MODKEY|ShiftMask,					push)
	{ MODKEY,                     XK_minus,	setmfact,       {.f = -0.05} },
	{ MODKEY,                     XK_equal,	setmfact,       {.f = +0.05} },
	{ MODKEY,                     XK_Tab,		view,           {0} },
	{ MODKEY,							XK_q,			killclient,     {0} },
	{ MODKEY,                     XK_t,			setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,				XK_f,			setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                     XK_g,			setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,				XK_b,			setlayout,		 {.v = &layouts[3]} },
	{ MODKEY,							XK_b,			setlayout,		 {.v = &layouts[4]} },
	{ 0|ControlMask|ShiftMask,		XK_f,			fullscreen,		 {0} },
	{ MODKEY,                     XK_0,			view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,           XK_0,			tag,            {.ui = ~0 } },
	{ MODKEY,                     XK_Left,		focusmon,       {.i = -1 } },
	{ MODKEY,                     XK_Right,	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,           XK_Left,		tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,           XK_Right,	tagmon,         {.i = +1 } },
	TAGKEYS(                      XK_1,                       0)
	TAGKEYS(                      XK_2,                       1)
	TAGKEYS(                      XK_3,                       2)
	TAGKEYS(                      XK_4,                       3)
	TAGKEYS(                      XK_5,                       4)
	TAGKEYS(                      XK_6,                       5)
	TAGKEYS(                      XK_7,                       6)
	TAGKEYS(                      XK_8,                       7)
	TAGKEYS(                      XK_9,                       8)
	{ MODKEY|ShiftMask,           XK_Escape,	quit,				 {0} },
	{ 0,						XF86XK_AudioMute,		spawn,			 SHCMD("pulsemixer --toggle-mute") },
	{ 0,				XF86XK_AudioLowerVolume,	spawn,			 SHCMD("pulsemixer --change-volume -2") },
	{ 0,				XF86XK_AudioRaiseVolume,	spawn,			 SHCMD("pulsemixer --change-volume +2") },
	{ MODKEY,							XK_l,			spawn,			 SHCMD("slock") },
	{ MODKEY,							XK_f,			spawn,			 {.v = (const char*[]) { "firefox" } } },
	{ MODKEY,							XK_v,			spawn,			 {.v = (const char*[]) { "alacritty", "-e", "nvim", NULL } } },
	{ 0|ControlMask|ShiftMask,		XK_Escape,	spawn,			 {.v = (const char*[]) { "alacritty", "-e", "gotop", "-s", "-r", "600ms", "--nvidia", NULL } } },
	{ MODKEY,							XK_p,			spawn,			 SHCMD("/home/finn/.config/dmenu/scripts/powermenu") },
	{ MODKEY|ShiftMask,				XK_s,			spawn,			 SHCMD("/home/finn/.config/dmenu/scripts/screenshot") },
	{ MODKEY,							XK_m,			spawn,			 SHCMD("/home/finn/.config/dmenu/scripts/manuals") },
	{ MODKEY,							XK_comma,	spawn,			 SHCMD("/home/finn/.config/dmenu/scripts/charmap") },
	{ MODKEY,				XF86XK_AudioMute,		spawn,			 {.v = (const char*[]) { "alacritty", "-e", "pulsemixer", NULL } } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[0]} },
	{ ClkStatusText,        0,              Button3,        spawn,          SHCMD("/home/finn/.config/dmenu/scripts/powermenu") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,	       Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,			MODKEY|ShiftMask, Button2,		  killclient,		{0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
