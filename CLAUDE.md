# dwm fork

Personal fork of suckless dwm with many patches applied (see `patches/`).
Remotes: `upstream` = git://git.suckless.org/dwm, `origin` = the fork.
Upstream releases are merged in as tags (e.g. `Merge tag '6.8'`), then the
config is adjusted.

## Primary goal: stay mergeable with upstream

Every change must keep future `git merge <upstream tag>` as conflict-free as
possible:

- Don't rewrite, reformat or reorder upstream code. Touch as few upstream
  lines as possible; prefer one-line hook calls into new functions over
  inline blocks inside existing functions.
- Put new code in new functions, placed alphabetically like upstream does,
  with prototypes in the alphabetical prototype list.
- Follow upstream style: tabs, K&R braces, return type on its own line, no
  reformatting of surrounding code (`.clang-format` is not applied to dwm.c).
- Keep settings in `config.def.h`/`config.h` instead of hardcoding them.

## Patches

- Save every applied suckless patch unmodified in `patches/`.
- If it doesn't apply cleanly to this fork, port it by hand and also save
  the resulting fork diff in `patches/` (e.g.
  `dwm-preserveonrestart-session-6.8.diff` next to the original
  `dwm-preserveonrestart-6.3.diff`).
- When porting, look for fork-specific code paths the original patch can't
  know about (e.g. tagswapmon, tagallmon, placemouse also change
  `c->tags`/`c->mon`).

## Build & test

- `make` builds `./dwm`. `config.h` is the real config (tracked).
- The session runs dwm in a restart loop (`startdwm`), so `quit` (Mod+Shift+q)
  restarts it. State that must survive a restart is stored in X properties
  (`_NET_CLIENT_INFO` per client, `_DWM_MON_STATE_<n>` on the root window).
- Test headless with two monitors: `Xvfb :58` with `Xephyr :57 -screen 800x600
  -screen 800x600 +xinerama` running inside it, then run `./dwm` on `:57` and
  drive it with `xdotool`. Plain Xvfb multi-screen Xinerama places all heads at
  0,0, so dwm sees only one monitor.
