#include <X11/XF86keysym.h>

// Shell
char shell[] = "/bin/sh";

#define Super Mod4Mask
#define TERM "st"

#define TERCMD(str) cmd(TERM " -e " #str)
#define DUSKLAYOUT(int) cmd("duskc run_command setlayoutex " #int)
#define TERCHEAT(str) cmd(TERM " -n cheatsheet -g 120x30 -e " #str)
#define WEBCAM cmd("mpv --no-cache --no-osc --no-input-default-bindings --profile=low-latency --untimed --vf=hflip --no-keepaspect-window --panscan=1 --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)")
#define NOOP cmd("")

enum {
	Applications,
	Layouts,
	Cheatsheets,
	DmenuScripts,
	MusicPlayer,
	Screenshot,

	// Declare modes above this
	MODE_SIZE,
};

// Define mode key bindings here
// NOTE: "20" here is the maximum number of key bindings for each mode
Key modes[MODE_SIZE][20] = {
	// KEY MODES

	// Cheatsheet mode. Toggle once using [Super+`]
	[Cheatsheets] = {
		{ 0,  XK_1,         cmd("duskbindings") }, // dwm window managementbindings
		{ 0,  XK_2,         cmd("shotkey-list") }, // shotkey applications key binds list
		{ 0,  XK_3,         cmd("stbindings") }, // st terminal key bindings
	},

	// Applications shortcuts. Toggle once using [Super+o]
	[Applications] = {
		{ 0,  XK_w,         cmd("$BROWSER") },
		{ 0,  XK_d,         cmd("discord --no-sandbox") },
		{ 0,  XK_e,         TERCMD(neomutt; duskc run_command setstatus 7 "$(sb-mailbox)") },
		{ 0,  XK_l,         cmd(TERM " -d `xcwd` -e lf") }, // lf file manager with image previews
		{ 0,  XK_n,         TERCMD(newsboat) },
		{ 0,  XK_t,         TERCMD(gotop) }, // System usage terminal applications
	},

	// Layouts shortcuts. Toggle using [Super+;]
	[Layouts] = {
		{ 0,  XK_q,         DUSKLAYOUT(0) }, // []=
		{ 0,  XK_a,         DUSKLAYOUT(1) }, // ||=
		{ 0,  XK_w,         DUSKLAYOUT(2) }, // :::
		{ 0,  XK_s,         DUSKLAYOUT(3) }, // ==#
		{ 0,  XK_e,         DUSKLAYOUT(4) }, // TTT
		{ 0,  XK_d,         DUSKLAYOUT(5) }, // ===
		{ 0,  XK_r,         DUSKLAYOUT(6) }, // [M]
		{ 0,  XK_f,         DUSKLAYOUT(7) }, // [D]
		{ 0,  XK_t,         DUSKLAYOUT(8) }, // |M|
		{ 0,  XK_g,         DUSKLAYOUT(9) }, // -M-
		{ 0,  XK_y,         DUSKLAYOUT(10) }, // [T]
		{ 0,  XK_h,         DUSKLAYOUT(11) }, // >M>
		{ 0,  XK_u,         DUSKLAYOUT(12) }, // (@)
		{ 0,  XK_j,         DUSKLAYOUT(13) }, // [\]
		{ 0,  XK_i,         DUSKLAYOUT(14) }, // ><>
	},

	// dmenu scripts mode. Toggle once using [Super+p]
	[DmenuScripts] = {
		{ 0, XK_b,          cmd("bookmarksurf") }, // Dmenu bookmarks manager
		{ 0, XK_e,          cmd("dm-emoji") }, // Emoji keyboard
		{ 0, XK_k,          cmd("dm-kill") }, // Terminate applications
		{ 0, XK_m,          cmd("dm-man") }, // Man pages list
		{ 0, XK_n,          cmd("dm-notes") }, // Markdown notes manager
		{ 0, XK_o,          cmd("dm-mount") }, // Mount drives, including USBs and a Android devices
		{ 0, XK_p,          cmd("passmenu --type -p 'ﳳ :: '") }, // Password manager and autotyper
		{ 0, XK_r,          cmd("dm-record") }, // Record using dmenu
		{ 0, XK_u,          cmd("dm-umount") }, // Unmount any drive
	},

	// Music mode. Toggle using [Super+m] and hold super. Press any other key to go back to normal mode
	[MusicPlayer] = {
		{ Super,            XK_0,             cmd("mpc seek 0%") }, // Restart song
		{ Super,            XK_bracketleft,   cmd("mpc seek -60") }, // Backward 60 secs
		{ Super,            XK_bracketright,  cmd("mpc seek +60") }, // Forward 60 secs
		{ Super,            XK_comma,         cmd("mpc seek -10") }, // Backward 10 secs
		{ Super,            XK_period,        cmd("mpc seek +10") }, // Forward 10 secs
		{ Super,            XK_h,             cmd("mpc prev") }, // Previous song
		{ Super,            XK_j,             cmd("mpc volume -3") }, // Volume down -3
		{ Super,            XK_k,             cmd("mpc volume +3") }, // Volume up +3
		{ Super,            XK_l,             cmd("mpc next") }, // Next song
		{ Super,            XK_m,             cmd(TERM " -e ncmpcpp") }, // Open ncmpcpp
		{ Super,            XK_r,             cmd("mpc repeat") }, // Toggle repeat mode
		{ Super,            XK_s,             cmd("mpc pause ; pauseallmpv") }, // Stop
		{ Super,            XK_space,         cmd("mpc toggle") }, // Pause/play
		{ Super|ShiftMask,  XK_k,             cmd("mpc volume +12") }, // Volume up +12
		{ Super|ShiftMask,  XK_j,             cmd("mpc volume -12") }, // Volume down -12
	},

	// Screenshot mode, using flameshot. Use [PrintScreen] to toggle once.
	[Screenshot] = {
		{ 0, XK_g,          cmd("flameshot gui -p ~/Pics/screenshots") },
		{ 0, XK_f,          cmd("flameshot full -p ~/Pics/screenshots") },
	},
};

Key keys[] = {

	// NORMAL MODE (No modifiers enabled)

	/* Mod                        Key                           Command */
	// Applications
	{ Super,                      XK_Return,                    cmd(TERM) }, // Spawn default terminal (st)
	{ Super|ShiftMask,            XK_Return,                    cmd(TERM " -d `xcwd`") }, // Spawn terminal in current working directory
	{ Super,                      XK_o,                         mode(Applications, False) }, // Application launcher
	{ Super,                      XK_m,                         mode(MusicPlayer, True) }, // Music player
	{ Super|ShiftMask,            XK_m,                         cmd("mic-toggle") },
	{ Super,                      XK_c,                         cmd("clipmenu") }, // dmenu clipboard history manager
	{ Super,                      XK_d,                         cmd("j4-dmenu-desktop --dmenu=\"dmenu -c -l 8 -bw 2\"") }, // Application launcher
	{ Super,                      XK_p,                         mode(DmenuScripts, False) },
	{ Super,                      XK_semicolon,                 mode(Layouts, False) },
	{ Super,                      XK_grave,                     mode(Cheatsheets, False) }, // Display cheatsheets
	{ Super,                      XK_BackSpace,                 cmd("dm-power") }, // Powermenu

	// System
	/* { 0,                          XF86XK_Battery,               cmd("") }, */
	{ 0,                          XF86XK_Calculator,            TERCMD(bc -l) },
	{ 0,                          XF86XK_DOS,                   cmd(TERM) },
	{ 0,                          XF86XK_Launch1,               cmd("xset dpms force off") },
	{ 0,                          XF86XK_Mail,                  TERCMD(neomutt ; duskc run_command setstatus 7 "$(sb-mailbox)") },
	{ 0,                          XF86XK_MonBrightnessDown,     cmd("xbacklight -dec 2 ; duskc run_command setstatus 3 \"$(sb-brightness)\"") },
	{ 0,                          XF86XK_MonBrightnessUp,       cmd("xbacklight -inc 2 ; duskc run_command setstatus 3 \"$(sb-brightness)\"") },
	{ 0,                          XF86XK_MyComputer,            cmd(TERM " -d $(xcwd) -e lf") },
	{ 0,                          XF86XK_PowerOff,              cmd("dm-power") },
	{ 0,                          XF86XK_ScreenSaver,           cmd("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0,                          XF86XK_Sleep,                 cmd("sudo -A zzz") },
	{ 0,                          XF86XK_TaskPane,              TERCMD(gotop) },
	{ 0,                          XF86XK_TouchpadOff,           cmd("synclient TouchpadOff=1") },
	{ 0,                          XF86XK_TouchpadOn,            cmd("synclient TouchpadOff=0") },
	{ 0,                          XF86XK_TouchpadToggle,        cmd("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0,                          XF86XK_WWW,                   cmd("$BROWSER") },

	// Media controls
	{ 0,                          XF86XK_AudioForward,          cmd("mpc seek +10") }, 
	{ 0,                          XF86XK_AudioLowerVolume,      cmd("pamixer --allow-boost -d 3; duskc run_command setstatus 5 \"$(sb-volume)\" ; canberra-gtk-play -i audio-volume-change") },
	{ 0,                          XF86XK_AudioMedia,            TERCMD(ncmpcpp) },
	{ 0,                          XF86XK_AudioMicMute,          cmd("mic-toggle") },
	{ 0,                          XF86XK_AudioMute,             cmd("pamixer -t; duskc run_command setstatus 5 \"$(sb-volume)\"") },
	{ 0,                          XF86XK_AudioNext,             cmd("mpc next") },
	{ 0,                          XF86XK_AudioPause,            cmd("mpc pause") },
	{ 0,                          XF86XK_AudioPlay,             cmd("mpc play") },
	{ 0,                          XF86XK_AudioPrev,             cmd("mpc prev") },
	{ 0,                          XF86XK_AudioRaiseVolume,      cmd("pamixer -u; pamixer --allow-boost -i 3; duskc run_command setstatus 5 \"$(sb-volume)\"; canberra-gtk-play -i audio-volume-change") },
	{ 0,                          XF86XK_AudioRewind,           cmd("mpc seek -10") },
	{ 0,                          XF86XK_AudioStop,             cmd("mpc stop") },

	// Function keys
	{ Super,                      XK_F1,                        cmd("sxiv -r -q -t -o ~/Pics/wallpapers/*") },
	{ Super,                      XK_F2,                        cmd("feh --randomize --bg-fill ~/Pics/wallpapers/*") }, // Set random wallpaper
	{ Super,                      XK_F3,                        cmd("pavucontrol; duskc run_command setstatus 5 \"$(sb-volume)\"") }, // Volume mixer
	{ Super,                      XK_F4,                        cmd("toggle-conky") }, // Toggle conky, a computer specs and statistics display
	{ Super,                      XK_F5,                        cmd("mw -Y && duskc run_command setstatus $BLOCK_STATUS \"$(sb-mailbox)\"") }, // Refresh mutt wizard email
	/* { Super,                      XK_F6,                        cmd("") },  */
	/* { Super,                      XK_F7,                        cmd("") },  */
	/* { Super,                      XK_F8,                        cmd("") }, */
	/* { Super,                      XK_F9,                        cmd("") }, */
	/* { Super,                      XK_F10,                       cmd("") }, */
	{ Super,                      XK_F11,                       cmd("remaps; notify-send \"⌨️ Keyboard remapping...\" \"Re-running keyboard defaults for any newly plugged-in keyboards.\"") },
	{ Super,                      XK_F12,                       WEBCAM }, // Display output of webcam using mpv
	// Screenshot
	{ 0,                          XK_Print,                     mode(Screenshot, False) }, // Toggle flameshot mode
};

ModeProperties mode_properties[MODE_SIZE] = {
	[Applications] = { "Apps" },
	[Layouts] = { "Layouts" },
	[Cheatsheets] = { "Cheatsheet" },
	[DmenuScripts] = { "dmenu" },
	[MusicPlayer] = { "Music Player" },
	[Screenshot] = { "Screenshot" }
};

// Call this script on mode change
char* on_mode_change = "shotkey-mode on-mode-change";
