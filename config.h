#include <X11/XF86keysym.h>

// Shell
char shell[] = "/bin/sh";

#define Super Mod4Mask
#define TERM "st"

/* #define SCRIPT(str) cmd("~/scripts/" #str) */
#define TERCMD(str) cmd(TERM " -e " #str)
#define DWMLAYOUT(int) cmd("dwmc setlayout " #int)
#define TERCHEAT(str) cmd(TERM " -n cheatsheet -g 120x30 -e " #str)
#define WEBCAM cmd("mpv --no-cache --no-osc --no-input-default-bindings --profile=low-latency --untimed --vf=hflip --no-keepaspect-window --panscan=1 --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)")
#define NOOP cmd("")

enum {
  Cheatsheets,
  dmenuScripts,
  MusicPlayer,
  Screenshot,

  // Declare modes above this
  MODE_SIZE,
};

// Define mode key bindings here
// NOTE: "10" here is the maximum number of key bindings for each mode
Key modes[MODE_SIZE][20] = {
  [Cheatsheets] = {
    { 0, XK_1,          TERCHEAT("$HOME/.local/lib/cheatsheets/dwmbindings") },
    { 0, XK_2,          TERCHEAT("$HOME/.local/lib/cheatsheets/shotkey-list") },
    { 0, XK_3,          TERCHEAT("$HOME/.local/lib/cheatsheets/stbindings") },
  },
  [dmenuScripts] = {
    { 0, XK_b,          cmd("bookmarksurf") },
    { 0, XK_k,          cmd("dmenukill") },
    { 0, XK_o,          cmd("dmenumount") },
    { 0, XK_u,          cmd("dmenuumount") },
    { 0, XK_n,          cmd("dmenunotes") },
    { 0, XK_r,          cmd("dmenurecord") },
    { 0, XK_p,          cmd("passmenu --type -p 'ﳳ :: '") },
    { 0, XK_space,      cmd("j4-dmenu-desktop --dmenu=\"dmenu -c -l 8 -bw 2\"") },
  },
  [MusicPlayer] = {
    { 0,          XK_comma,         cmd("mpc seek -10") },
    { 0,          XK_period,        cmd("mpc seek +10") },
    { 0,          XK_bracketleft,   cmd("mpc seek -60") },
    { 0,          XK_bracketright,  cmd("mpc seek +60") },
    { 0,          XK_0,             cmd("mpc seek 0%") },
    { 0,          XK_k,             cmd("mpc volume +3") },
    { ShiftMask,  XK_k,             cmd("mpc volume +12") },
    { 0,          XK_j,             cmd("mpc volume -3") },
    { ShiftMask,  XK_j,             cmd("mpc volume -12") },
    { 0,          XK_l,             cmd("mpc next") },
    { 0,          XK_h,             cmd("mpc previous") },
    { 0,          XK_m,             cmd("dwmc togglescratch 2")}, // Toggle ncmpcpp music player scratchpad 
    { 0,          XK_space,         cmd("mpc pause") },
    { 0,          XK_p,             cmd("mpc toggle") },
    { 0,          XK_s,             cmd("mpc pause ; pauseallmpv") },
    { 0,          XK_r,             cmd("mpc repeat") },
  },
  [Screenshot] = {
    { 0, XK_g,          cmd("flameshot gui -p ~/Pics/screenshots") },
    { 0, XK_f,          cmd("flameshot full -p ~/Pics/screenshots") },
  },
};

// Define normal mode key bindings here
Key keys[] = {
  /* Mod                        Key                           Command */
  // Applications
  { Super,                      XK_Return,                    cmd(TERM) }, // Spawn default terminal (st)
  { Super|ShiftMask,            XK_Return,                    cmd(TERM " -d $(xcwd)") }, // Spawn terminal in current working directory

  { Super,                      XK_w,                         cmd("$BROWSER") }, // dmenu bookmark manager
  /* { Super|ShiftMask,            XK_w,                         cmd("") }, // Default web browser (brave) */

  { Super,                      XK_e,                         TERCMD(neomutt ; sb-refresh sb-mailbox) }, // Neomutt email client
  { Super|ShiftMask,            XK_e,                         TERCMD(abook) }, // Addressbook for neomutt

  { Super,                      XK_r,                         cmd(TERM " -d $(xcwd) -e lf-run") }, // lf file manager with image previews
  { Super|ShiftMask,            XK_r,                         TERCMD(gotop) }, // System usage terminal applications

  { Super,                      XK_apostrophe,                cmd("dwmc togglescratch 1")}, // Toggle bc calculator scratchpad
  /* { Super,                      XK_apostrophe,                cmd("")}, */

  { Super,                      XK_n,                         TERCMD(newsboat; sb-refresh sb-news) }, // RSS newsfeed
  /* { Super|ShiftMask,            XK_n,                         cmd("") }, */

  { Super,                      XK_BackSpace,                 cmd("sysact") }, // Powermenu
  /* { Super|ShiftMask,            XK_BackSpace,                 cmd("") }, */

  // Music player
  { Super,                      XK_m,                         mode(MusicPlayer, True) },
  { Super|ShiftMask,            XK_m,                         cmd("mic-toggle") }, // Toggle microphone

  // Menus
  { Super,                      XK_c,                         cmd("clipmenu") }, // dmenu clipboard history manager
  /* { Super|ShiftMask,            XK_c,                         cmd("") }, */
  { Super,                      XK_p,                         mode(dmenuScripts, False) },
  /* { Super|ShiftMask,            XK_p,                         cmd("") }, */
  { Super,                      XK_grave,                     mode(Cheatsheets, False) }, // Display cheatsheets
  /* { Super|ShiftMask,            XK_grave,                     cmd("") }, */

  // System
  /* { 0,                          XF86XK_Battery,               cmd("") }, */
  { 0,                          XF86XK_Calculator,            TERCMD(bc -l) },
  { 0,                          XF86XK_DOS,                   cmd(TERM) },
  { 0,                          XF86XK_Launch1,               cmd("xset dpms force off") },
  { 0,                          XF86XK_Mail,                  TERCMD(neomutt ; sb-refresh sb-mailbox) },
  { 0,                          XF86XK_MonBrightnessDown,     cmd("xbacklight -dec 2 ; sb-refresh sb-brightness") },
  { 0,                          XF86XK_MonBrightnessUp,       cmd("xbacklight -inc 2 ; sb-refresh sb-brightness") },
  { 0,                          XF86XK_MyComputer,            cmd(TERM " -d $(xcwd) -e lf-run") },
  { 0,                          XF86XK_PowerOff,              cmd("sysact") },
  { 0,                          XF86XK_ScreenSaver,           cmd("slock & xset dpms force off; mpc pause; pauseallmpv") },
  { 0,                          XF86XK_Sleep,                 cmd("sudo -A zzz") },
  { 0,                          XF86XK_TaskPane,              TERCMD(gotop) },
  { 0,                          XF86XK_TouchpadOff,           cmd("synclient TouchpadOff=1") },
  { 0,                          XF86XK_TouchpadOn,            cmd("synclient TouchpadOff=0") },
  { 0,                          XF86XK_TouchpadToggle,        cmd("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
  { 0,                          XF86XK_WWW,                   cmd("$BROWSER") },

  // Media controls
  { 0,                          XF86XK_AudioForward,          cmd("mpc seek +10") },
  { 0,                          XF86XK_AudioLowerVolume,      cmd("pamixer --allow-boost -d 3; sb-refresh sb-volume; canberra-gtk-play -i audio-volume-change") },
  { 0,                          XF86XK_AudioMedia,            TERCMD(ncmpcpp) },
  { 0,                          XF86XK_AudioMicMute,          cmd("mic-toggle") },
  { 0,                          XF86XK_AudioMute,             cmd("pamixer -t; sb-refresh sb-volume") },
  { 0,                          XF86XK_AudioNext,             cmd("mpc next") },
  { 0,                          XF86XK_AudioPause,            cmd("mpc pause") },
  { 0,                          XF86XK_AudioPlay,             cmd("mpc play") },
  { 0,                          XF86XK_AudioPrev,             cmd("mpc prev") },
  { 0,                          XF86XK_AudioRaiseVolume,      cmd("pamixer -u; pamixer --allow-boost -i 3; sb-refresh sb-volume; canberra-gtk-play -i audio-volume-change") },
  { 0,                          XF86XK_AudioRewind,           cmd("mpc seek -10") },
  { 0,                          XF86XK_AudioStop,             cmd("mpc stop") },

  // Function keys
  /* { Super,                      XK_F1,                        cmd("") }, */
  { Super,                      XK_F2,                        cmd("dmenuunicode") }, // dmenu emoji keyboard
  { Super,                      XK_F3,                        cmd("feh --bg-fill --random ~/Pics/wallpapers") }, // Set random wallpaper
  { Super,                      XK_F4,                        cmd("pavucontrol; sb-refresh sb-volume") }, // Volume mixer
  { Super,                      XK_F5,                        cmd("toggle-conky") }, // Toggle conky, a computer specs and statistics display
  /* { Super,                      XK_F6,                        cmd("") },  */
  /* { Super,                      XK_F7,                        cmd("") },  */
  { Super,                      XK_F8,                        cmd("mw -Y && sb-refresh sb-mailbox") }, // Refresh mutt wizard email
  { Super,                      XK_F9,                        cmd("dmenumount") }, // Mount devices, including USB drives using dmenu
  { Super,                      XK_F10,                       cmd("dmenuumount") }, // Unmount devices, including USB drives using dmenu
  { Super,                      XK_F11,                       WEBCAM }, // Display output of webcam using mpv
  { Super,                      XK_F12,                       cmd("remaps && notify-send \\\"⌨️ Keyboard remapping...\\\" \\\"Re-running keyboard defaults for any newly plugged-in keyboards.\\\"") },
  // Screenshot
  { 0,                          XK_Print,                     mode(Screenshot, False) }, // Toggle flameshot mode
};

ModeProperties mode_properties[MODE_SIZE] = {
  [Cheatsheets] = { "📋" },
  [dmenuScripts] = { "📚" },
  [MusicPlayer] = { "🎹" },
  [Screenshot] = { "📷" }
};

// Call this script on mode change
char* on_mode_change = "shotkey-mode on-mode-change";

