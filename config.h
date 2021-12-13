#include <X11/XF86keysym.h>

// Shell
char shell[] = "/bin/sh";

#define Super Mod4Mask
#define Shift ShiftMask
#define Ctrl ControlMask
#define Alt Mod1Mask
#define TERM "st"
#define EMACS "emacsclient -c -a 'emacs'"

#define WEBCAM cmd("mpv --no-cache --no-osc --no-input-default-bindings --profile=low-latency --untimed --vf=hflip --no-keepaspect-window --panscan=1 --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)")
#define NOOP cmd("")

enum {
	Applications,
	Cheatsheets,
	Prompts,
	Screenshot,
	System,
	Music,

	// Declare modes above this
	MODE_SIZE,
};

// Define mode key bindings here
// NOTE: "20" here is the maximum number of key bindings for each mode
Key modes[MODE_SIZE][30] = {
	// KEY MODES

	// Cheatsheet mode. Toggle once using [Super+/].
	[Cheatsheets] = {
		{ 0,  XK_d,         cmd("dwm-keybindings") }, // dwm window managementbindings
		{ 0,  XK_h,         cmd("shotkey-keybindings") }, // shotkey applications key binds list
		{ 0,  XK_t,         cmd("st-keybindings") }, // st terminal key bindings
	},

	// Applications shortcuts. Toggle once using [Super+o].
	[Applications] = {
		{ 0,  XK_w,         cmd("$BROWSER") },
		{ 0,  XK_c,         cmd(TERM " -e calcurse") },
		{ 0,  XK_d,         cmd("/usr/bin/discord --no-sandbox") },
		{ 0,  XK_e,         cmd(TERM " -e neomutt") },
		{ 0,  XK_l,         cmd(TERM " -e lf-run") }, // lf file manager with image previews
		{ 0,  XK_m,         cmd(TERM " -n floating -e ncmpcpp") },
		{ 0,  XK_n,         cmd(TERM " -e newsboat") },
		{ 0,  XK_o,         cmd("/usr/bin/obsidian --no-sandbox") },
		{ 0,  XK_t,         cmd("effitask") },
		{ 0,  XK_v,         cmd("/usr/bin/vscodium") },
	},

	// dmenu scripts mode. Toggle once using [Super+p].
	[Prompts] = {
		{ 0, XK_b,          cmd("dm-beats") }, // Radio FM
		{ 0, XK_c,          cmd("dm-clip") },
		{ 0, XK_d,          cmd("dm-directories") }, // dmenu directories manager
		{ 0, XK_e,          cmd("dm-emoji") }, // Emoji keyboard
		{ 0, XK_k,          cmd("dm-kill") }, // Terminate applications
		{ 0, XK_l,          cmd("rofi-bluetooth") }, // Rofi bluetooth manager
		{ 0, XK_m,          cmd("dm-man") }, // Man pages list
		{ 0, XK_o,          cmd("dm-mount") }, // Mount drives, including USBs and a Android devices
		{ 0, XK_p,          cmd("rofi-pass") }, // Password manager and autotyper
		{ 0, XK_r,          cmd("dm-record") }, // Record using dmenu
		{ 0, XK_s,          cmd("dm-scripts") }, // Find and edit scripts
		{ 0, XK_t,          cmd("todofi") },
		{ 0, XK_u,          cmd("dm-umount") }, // Unmount any drive
		{ 0, XK_w,          cmd("weatherforecast") }, // Display the weather forecast
	},

	// Screenshot mode, using flameshot. Use [PrintScreen] to toggle once.
	[Screenshot] = {
		{ 0, XK_g,          cmd("flameshot gui -p $XDG_PICTURES_DIR/screenshots") },
		{ 0, XK_f,          cmd("flameshot full -p $XDG_PICTURES_DIR/screenshots") },
	},

	// System shortcuts mode. Use [;] to toggle.
	[System] = {
		{ 0,                XK_a,             cmd("sxiv -r -q -t -o $XDG_PICTURES_DIR/wallpapers/*") },
		{ 0,                XK_m,             cmd("multi-monitor") },
		{ 0,                XK_w,             cmd("setwallpaper") },
		{ 0,                XK_v,             cmd("pavucontrol") },
	},

	[Music] = {
		{ 0,                XK_0,             cmd("mpc seek 0%") }, // Restart song
		{ 0,                XK_comma,         cmd("mpc seek -60") }, // Backward 60 secs
		{ 0,                XK_period,        cmd("mpc seek +60") }, // Forward 60 secs
		{ 0,                XK_h,             cmd("mpc seek -10") }, // Backward 10 secs
		{ 0,                XK_l,             cmd("mpc seek +10") }, // Forward 10 secs
		{ 0,                XK_bracketleft,   cmd("mpc prev") }, // Previous song
		{ 0,                XK_bracketright,  cmd("mpc next") }, // Next song
		{ 0,                XK_j,             cmd("mpc volume -3") }, // Volume down -3
		{ 0,                XK_k,             cmd("mpc volume +3") }, // Volume up +3
		{ Shift,            XK_j,             cmd("mpc volume -12") }, // Volume down -12
		{ Shift,            XK_k,             cmd("mpc volume +12") }, // Volume up +12
		{ 0,                XK_p,             cmd("mpc toggle") }, // Pause/play
		{ 0,                XK_r,             cmd("mpc repeat") }, // Toggle repeat mode
		{ 0,                XK_s,             cmd("mpc pause ; pauseallmpv") }, // Stop
		{ 0,                XK_u,             cmd("mpc shuffle") }, // Shuffle the playlist
	},
};

Key keys[] = {
	// NORMAL MODE (No modifiers enabled)

	/* Mod                        Key                           Command */
	// Applications
	{ Super,                      XK_Return,                    cmd(TERM " -d ~") }, // Spawn default terminal (st)
	{ Super,                      XK_o,                         mode(Applications, False) }, // Application launcher
	{ Super,                      XK_semicolon,                 mode(System, False) }, // Application launcher
	{ Super,                      XK_m,                         mode(Music, True) }, // Application launcher
	{ Super|Shift,                XK_m,                         cmd("mic-toggle") },
	{ Super,                      XK_d,                         cmd("rofi-launcher") }, // Application launcher
	{ Super,                      XK_p,                         mode(Prompts, False) },
	{ Super,                      XK_slash,                     mode(Cheatsheets, False) }, // Display cheatsheets
	{ Super,                      XK_BackSpace,                 cmd("arcolinux-logout") },

	// System
	/* { 0,                          XF86XK_Battery,               cmd("") }, */
	{ 0,                          XF86XK_Calculator,            cmd(TERM " -e bc -l") },
	{ 0,                          XF86XK_DOS,                   cmd(TERM) },
	{ 0,                          XF86XK_Launch1,               cmd("xset dpms force off") },
	{ 0,                          XF86XK_Mail,                  cmd(TERM " -e neomutt") },
	{ 0,                          XF86XK_MonBrightnessDown,     cmd("brightness down") },
	{ 0,                          XF86XK_MonBrightnessUp,       cmd("brightness up") },
	{ 0,                          XF86XK_MyComputer,            cmd(TERM " -e lf-run") },
	{ 0,                          XF86XK_PowerOff,              cmd("dm-power") },
	{ 0,                          XF86XK_ScreenSaver,           cmd("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0,                          XF86XK_Sleep,                 cmd("sudo -A zzz") },
	{ 0,                          XF86XK_TaskPane,              cmd(TERM " -e btop") },
	{ 0,                          XF86XK_TouchpadOff,           cmd("synclient TouchpadOff=1") },
	{ 0,                          XF86XK_TouchpadOn,            cmd("synclient TouchpadOff=0") },
	{ 0,                          XF86XK_TouchpadToggle,        cmd("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0,                          XF86XK_WWW,                   cmd("$BROWSER") },

	// Media controls
	{ 0,                          XF86XK_AudioForward,          cmd("mpc seek +10") },
	{ 0,                          XF86XK_AudioLowerVolume,      cmd("volume down") },
	{ 0,                          XF86XK_AudioMedia,            cmd(TERM " -e ncmpcpp") },
	{ 0,                          XF86XK_AudioMicMute,          cmd("mic-toggle") },
	{ 0,                          XF86XK_AudioMute,             cmd("volume mute") },
	{ 0,                          XF86XK_AudioNext,             cmd("mpc next") },
	{ 0,                          XF86XK_AudioPause,            cmd("mpc pause") },
	{ 0,                          XF86XK_AudioPlay,             cmd("mpc play") },
	{ 0,                          XF86XK_AudioPrev,             cmd("mpc prev") },
	{ 0,                          XF86XK_AudioRaiseVolume,      cmd("volume up") },
	{ 0,                          XF86XK_AudioRewind,           cmd("mpc seek -10") },
	{ 0,                          XF86XK_AudioStop,             cmd("mpc stop") },

	// Screenshot
	{ 0,                          XK_Print,                     mode(Screenshot, False) }, // Toggle flameshot mode
};

ModeProperties mode_properties[MODE_SIZE] = {
	[Applications] = { "🎮" },
	[Cheatsheets] = { "🚁" },
	[Prompts] = { "📓" },
	[Screenshot] = { "📸" },
	[System] = { "⚙️" },
	[Music] = { "🎼" },
};

// Call this script on mode change
char* on_mode_change = "$HOME/.local/bin/scripts/shotkey-mode on-mode-change";
