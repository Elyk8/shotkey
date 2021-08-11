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
// NOTE: "20" here is the maximum number of key bindings for each mode
Key modes[MODE_SIZE][20] = {
  // KEY MODES

  // Cheatsheet mode. Toggle once using [Super+`]
  [Cheatsheets] = {
    { 0, XK_1,          TERCHEAT("$HOME/.local/bin/cheatsheets/dwmbindings") }, // dwm window managementbindings
    { 0, XK_2,          TERCHEAT("$HOME/.local/bin/cheatsheets/shotkey-list") }, // shotkey applications key binds list
    { 0, XK_3,          TERCHEAT("$HOME/.local/bin/cheatsheets/stbindings") }, // st terminal key bindings
  },

  // dmenu scripts mode. Toggle once using [Super+p]
  [dmenuScripts] = {
    { 0, XK_b,          cmd("bookmarksurf") }, // Open dmenu bookmarks manager
    { 0, XK_e,          cmd("dmenuunicode") }, // Open emoji keymode
    { 0, XK_k,          cmd("dmenukill") }, // List applications to terminate
    { 0, XK_o,          cmd("dmenumount") }, // Asks to mount drives, including USBs and a Android devices
    { 0, XK_u,          cmd("dmenuumount") }, // Unmount any drive
    { 0, XK_n,          cmd("dmenunotes") }, // Open markdown notes manager
    { 0, XK_r,          cmd("dmenurecord") }, // Record using dmenu
    { 0, XK_p,          cmd("passmenu --type -p 'ﳳ :: '") }, // Open password manager and autotyper
    { 0, XK_space,      cmd("j4-dmenu-desktop --dmenu=\"dmenu -c -l 8 -bw 2\"") }, // Application launcher
  },

  // Music mode. Toggle using [Super+m] and hold super. Press any other key to go back to normal mode
  [MusicPlayer] = {
    { Super,            XK_comma,         cmd("mpc seek -10") }, // Backward 10 secs
    { Super,            XK_period,        cmd("mpc seek +10") }, // Forward 10 secs
    { Super,            XK_bracketleft,   cmd("mpc seek -60") }, // Backward 60 secs
    { Super,            XK_bracketright,  cmd("mpc seek +60") }, // Forward 60 secs
    { Super,            XK_0,             cmd("mpc seek 0%") }, // Restart song
    { Super,            XK_k,             cmd("mpc volume +3") }, // Volume up +3
    { Super|ShiftMask,  XK_k,             cmd("mpc volume +12") }, // Volume up +12
    { Super,            XK_j,             cmd("mpc volume -3") }, // Volume down -3
    { Super|ShiftMask,  XK_j,             cmd("mpc volume -12") }, // Volume down -12
    { Super,            XK_l,             cmd("mpc next") }, // Next song
    { Super,            XK_h,             cmd("mpc prev") }, // Previous song
    { Super,            XK_m,             cmd("dwmc togglescratch 2") }, // Open ncmpcpp
    { Super,            XK_space,         cmd("mpc toggle") }, // Pause/play
    { Super,            XK_s,             cmd("mpc pause ; pauseallmpv") }, // Stop
    { Super,            XK_r,             cmd("mpc repeat") }, // Toggle repeat mode
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
  { Super|ShiftMask,            XK_Return,                    cmd(TERM " -d $(xcwd)") }, // Spawn terminal in current working directory

  { Super,                      XK_w,                         cmd("$BROWSER") }, // Default web browser (brave)
  /* { Super|ShiftMask,            XK_w,                         cmd("") },  */

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
  /* { Super,                      XK_F2,                        cmd("") }, */
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
  [Cheatsheets] = { "Cheatsheet" },
  [dmenuScripts] = { "Dmenu" },
  [MusicPlayer] = { "Music Player" },
  [Screenshot] = { "Screenshot" }
};

// Call this script on mode change
char* on_mode_change = "shotkey-mode on-mode-change";

