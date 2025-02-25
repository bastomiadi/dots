/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 33;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad            = 6;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "Ubuntu Regular:size=10","Hack Nerd Font Mono:size=16"};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222"; //black
static const char col_gray2[]       = "#444444"; //lightblack
static const char col_gray3[]       = "#bbbbbb"; //white
static const char col_gray4[]       = "#eeeeee"; // light-grey
static const char col_cyan[]        = "#005577"; //blue

/*onedark colors*/ 

static const char onedark_bg[]     = "#1e2127"; //black
static const char onedark_1[]      = "#282C34"; //black
static const char onedark_2[]      = "#E06C75"; //red
static const char onedark_3[]      = "#98C379"; //green
static const char onedark_4[]      = "#E5C70B"; //yellow
static const char onedark_5[]      = "#61AFEF"; //blue
static const char onedark_6[]      = "#C678DD"; //violet
static const char onedark_7[]      = "#56B6C2"; //cyan
static const char onedark_8[]      = "#ABB2BF"; //white
static const char col_inactive[]   = "#707880";

static const char *colors[][3]      = {

/*               fg         bg         border   */
[SchemeNorm] = { onedark_8, onedark_bg, onedark_1 },
[SchemeSel]  = { onedark_8, onedark_bg, onedark_1  },

/* color bar patch */
/*{text,background,not used but cannot be empty}*/

[SchemeStatus]    = { onedark_8, onedark_bg,  "#000000"  }, // left most bar which shows dwm-6.2
[SchemeTagsSel]   = { onedark_2, onedark_bg,  "#000000"  }, // Currently selected tag
[SchemeTagsNorm]  = { onedark_8, onedark_bg,  "#000000"  }, // Active tags but not in focus & Window mode indicatior ([]= / ><>)
[SchemeInfoSel]   = { col_inactive, onedark_bg, "#000000"  }, // middle bar which shows window info and other stuff when windows are open
[SchemeInfoNorm]  = { onedark_8, onedark_bg,  "#000000"  }, // middle bar when no window is open


};

/* tagging */
static const char *tags[] = {"", "", "", "", "", "", "", "", "漣" };


static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      						instance    title       tags mask    isfloating   monitor */
	{ "Lxappearance",  					NULL,       NULL,       0,       		 1,           -1 },
	{ "Nitrogen",			 			NULL,       NULL,       0,       		 1,           -1 },
	{ "Pavucontrol",	 				NULL,       NULL,       0,       		 1,           -1 },
	{ "Simple-scan",	 				NULL,       NULL,       0,       		 1,           -1 },
	{ "System-config-printer.py",	 			NULL,       NULL,       0,       		 1,           -1 },
	{ "Pavucontrol",	 				NULL,       NULL,       0,       		 1,           -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *filecmd[]  = { "pcmanfm", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = filecmd } },

	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },       /*clean quit dwm*/
	{ MODKEY|ShiftMask, 		XK_r,      quit,           {1} },	/*reload dwm*/  
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },	/*close focused application*/
	
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },

	/*{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },*/
	/*{ MODKEY,                       XK_Return, zoom,           {0} },*/
	
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


	/*PATCHES*/

	/*rotate stack*/
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   rotatestack,    {.i = -1 } },

	/*cycle-layouts*/
	{ MODKEY,           						XK_e, 		 cyclelayout,    {.i = +1 } },

	/*mover-size*/
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

	/*actual-fullscreen*/
	{ MODKEY,            		XK_f,      togglefullscr,  {0} },

	/*fullgaps*/
	{ MODKEY,             		XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,             		XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_BackSpace,  setgaps,    {.i = 0  } },

	/*scratchpad*/

	{ MODKEY|ShiftMask,             XK_equal, 	scratchpad_hide,{0} }, 		/* will also add item to scratchpad if its empty*/
	{ MODKEY|ShiftMask,             XK_minus, 	scratchpad_show,{0} }, 		/* will show scratchpad items*/
	{ MODKEY|ShiftMask,             XK_z, 		  scratchpad_remove,{0} },	/*will remove an item from scratchpad*/

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

