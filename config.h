/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int gappx              = 0;        /* gap size between windows */
static const int rmaster            = 1;        /* 1 means master is initially on the right */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Font Awesome:size=10" };
//static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#3b4252";
static const char col_gray3[]       = "#434c5e";
static const char col_gray4[]       = "#4c566a";
static const char col_cyan[]        = "#5e81ac";
static const char col_white[]       = "#e6e6e6";
static const char col1[]            = "#ffffff";
static const char col2[]            = "#ffffff";
static const char col3[]            = "#ffffff";
static const char col4[]            = "#ffffff";
static const char col5[]            = "#ffffff";
static const char col6[]            = "#ffffff";
static const char col7[]            = "#ffffff";
static const char col8[]            = "#ffffff";
static const char col9[]            = "#ffffff";
static const char col10[]           = "#ffffff";
static const char col11[]           = "#ffffff";
static const char col12[]           = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_gray1, col_gray2 },
	[SchemeSel]  = { col_white, col_cyan,  col_cyan  },
	[SchemeCol1]  = { col_cyan,      col_gray1, col_gray2 },
	[SchemeCol2]  = { col2,      col_gray1, col_gray2 },
	[SchemeCol3]  = { col3,      col_gray1, col_gray2 },
	[SchemeCol4]  = { col4,      col_gray1, col_gray2 },
	[SchemeCol5]  = { col5,      col_gray1, col_gray2 },
	[SchemeCol6]  = { col6,      col_gray1, col_gray2 },
	[SchemeCol7]  = { col7,      col_gray1, col_gray2 },
	[SchemeCol8]  = { col8,      col_gray1, col_gray2 },
	[SchemeCol9]  = { col8,      col_gray1, col_gray2 },
	[SchemeCol10] = { col10,     col_gray1, col_gray2 },
	[SchemeCol11] = { col11,     col_gray1, col_gray2 },
	[SchemeCol12] = { col12,     col_gray1, col_gray2 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.45; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
    { "[D]",      deck },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[]=",      tile },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "_M_",      centeredmonocle },
    { "[G]",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray4, "-nf", col_white, "-sb", col_cyan, "-sf", col_white, NULL };
static const char *termcmd[]  = { "st", "-f", "SauceCodePro NF:size=12:antialias=true:autohint=true", "-e", "tmux", NULL };
static const char *stcmd[]  = { "st", "-f", "SauceCodePro NF:size=12:antialias=true:autohint=true", NULL };
static const char *ranger_cmd[] = { "st", "-f", "SauceCodePro NF:size=12:antialias=true:autohint=true", "-e", "ranger", NULL };
static const char *chromium_cmd[] = { "chromium", NULL };
/* brightness */
static const char *brightness_inc_cmd[] = { "xbacklight", "-inc", "3", NULL};
static const char *brightness_dec_cmd[] = { "xbacklight", "-dec", "3", NULL };
static const char *brightness_pkill[] = { "pkill", "-RTMIN+2", "dwmblocks", NULL };
/* volume */
static const char *volume_inc_cmd[] =   { "pactl", "set-sink-volume", "0", "+3%", NULL };
static const char *volume_dec_cmd[] =   { "pactl", "set-sink-volume", "0", "-3%", NULL };
static const char *volume_mute_cmd[] =  { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *volume_pkill[] = { "pkill", "-RTMIN+1", "dwmblocks", NULL };
/* lock */
static const char *lock_cmd[] =         { "slock", NULL };
static const char *lock_suspend_cmd[] = { "slock", "systemctl", "suspend", NULL };
/* screenshots */
static const char *screenshot_cmd[] = { "scrot", "-z", "-o", "/tmp/screenshot_%Y%m%d_%H%M%S.png", NULL };
static const char *screenshot_focus_cmd[] = { "scrot", "-z", "-o", "-u", "/tmp/screenshot_%Y%m%d_%H%M%S.png", NULL };
/*keyboard backlight brightnessctl --device='tpacpi::kbd_backlight' set 0 */
static const char *keyboard_backlight_off_cmd[] = { "brightnessctl","-q", "--device=tpacpi::kbd_backlight", "set", "1-", NULL };
static const char *keyboard_backlight_on_cmd[] = { "brightnessctl", "-q", "--device=tpacpi::kbd_backlight", "set", "+1", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ Mod4Mask,                     XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = stcmd} },
	{ MODKEY,                       XK_r,      spawn,          {.v = ranger_cmd } },
	{ MODKEY,                       XK_g,      spawn,          {.v = chromium_cmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ Mod4Mask,                     XK_j,      pushdown,       {0} },
	{ Mod4Mask,                     XK_k,      pushup,         {0} },
	{ Mod4Mask,                     XK_i,      incnmaster,     {.i = +1 } },
	{ Mod4Mask,                     XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_n,      focusmaster,    {0}},
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ Mod4Mask|ShiftMask,           XK_f,      togglefakefullscreen, {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_x,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[5]} },
    { MODKEY,                       XK_e,      setlayout,      {.v = &layouts[6]} },
    { Mod4Mask,                     XK_g,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ Mod4Mask,                     XK_r,      togglermaster,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ Mod4Mask,                     XK_comma,  tagmon,         {.i = -1 } },
	{ Mod4Mask,                     XK_period, tagmon,         {.i = +1 } },
	{ Mod4Mask,                     XK_h,      tagmon,         {.i = -1 } },
	{ Mod4Mask,                     XK_l,      tagmon,         {.i = +1 } },
	{ Mod4Mask|ShiftMask,           XK_x,      spawn,          {.v = brightness_inc_cmd}  },
	{ Mod4Mask|ShiftMask,           XK_x,      spawn,          {.v = brightness_pkill}  },
	{ Mod4Mask,                     XK_x,      spawn,          {.v = brightness_dec_cmd} },
	{ Mod4Mask,                     XK_x,      spawn,          {.v = brightness_pkill} },
	{ Mod4Mask|ShiftMask,           XK_z,      spawn,          {.v = volume_inc_cmd } },
	{ Mod4Mask|ShiftMask,           XK_z,      spawn,          {.v = volume_pkill } },
	{ Mod4Mask,                     XK_z,      spawn,          {.v = volume_dec_cmd } },
	{ Mod4Mask,                     XK_z,      spawn,          {.v = volume_pkill } },
	{ Mod4Mask,                     XK_m,      spawn,          {.v = volume_mute_cmd } },
	{ Mod4Mask,                     XK_m,      spawn,          {.v = volume_pkill } },
	{ Mod4Mask,                     XK_o,      spawn,          {.v = lock_cmd } },
	{ Mod4Mask,                     XK_p,      spawn,          {.v = lock_suspend_cmd } },
	{ Mod4Mask,                     XK_s,      spawn,          {.v = screenshot_cmd} },
	{ Mod4Mask,                     XK_f,      spawn,          {.v = screenshot_focus_cmd } },
	{ Mod4Mask|ShiftMask,           XK_k,      spawn,          {.v = keyboard_backlight_off_cmd } },
	{ MODKEY|ShiftMask,             XK_k,      spawn,          {.v = keyboard_backlight_on_cmd } },
	{ Mod4Mask|ShiftMask,           XK_s,      spawn,          SHCMD("sleep 1s;scrot -s -o -z /tmp/screenshot_%Y%m%d_%H%M%S.png") },
	{ Mod4Mask,                     XK_c,      spawn,          SHCMD("sleep 1s;scrot -s -o -z -e 'sxiv -b $f' /tmp/screenshot_%Y%m%d_%H%M%S.png") },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdsblocks,    {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdsblocks,    {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdsblocks,    {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button3,      dragcfact,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

