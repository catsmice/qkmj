
Here's a fork version for QKMJ systme,
which is made by sysu(吳先祐).

The version forked from 0.94 beta by TonyQ, 
and plan to implement some special feature.

Remaster with WebSocket proxy and dockerize by gjchen.tw@gmail.com.

Usage
=====

* run a ws://qkmj.site service:

```
   docker run -d -p 80:80 gjchen/qkmj
```

* run a telnet://qkmj.site service:

```
   docker run -d -p 23:23 gjchen/qkmj
```

Building and running locally (macOS / Apple Silicon)
====================================================

The server and client build natively on macOS (Apple Silicon, arm64) — no
Docker or emulation required. You need the Xcode command-line tools
(`xcode-select --install`); the client links the system `ncurses`.

```
# 1. Build the server (mjgps) and the admin record tool (mjrec)
cd qkmjserver && make && cd ..

# 2. Build the terminal client (qkmj)
cd qkmjclient && make && cd ..
```

Run it (each in its own terminal tab):

```
qkmjserver/mjgps 7001            # the game server, listening on port 7001
qkmjclient/qkmj 127.0.0.1 7001   # the client; run one per player
```

A full game needs four clients connected to one table (there are no bots):
open four tabs, log in under four different names, have one type `/serv` to
open a table and the other three `/join <that-name>`. Type `/help` in-game
for the command list.

Data directory
--------------

The server stores accounts and logs in a data directory, resolved at startup:

* `$QKMJ_DATA_DIR` if that environment variable is set, otherwise
* `$HOME/.qkmj`

It is created automatically on first run — no `sudo` and no manual setup. The
admin tool reads the same file, e.g. `qkmjserver/mjrec ~/.qkmj/qkmj.rec`.

Terminal encoding
-----------------

The UI (including the table borders) is **Big5**-encoded. Set your terminal's
character encoding to Traditional Chinese (Big5) or the Chinese text and
box-drawing will show as garbage. iTerm2 (Profiles → Terminal → Character
Encoding → Big5) works well; `luit -encoding Big5 qkmjclient/qkmj ...` is an
alternative that keeps a UTF-8 terminal.

macOS / Apple Silicon changes in this fork
------------------------------------------

This fork adds macOS support on top of TonyQ's QKMJ (originally by 吳先祐 /
Shian-Yow Wu, remastered/dockerized by gjchen). Changes:

* Fixed `init_socket()` in the client to return success explicitly — it
  previously fell off the end and returned an undefined value, which on arm64
  is typically negative and made the client wrongly report "cannot connect".
* Moved the server data files out of a hardcoded `/var/qkrecord` (which needed
  `sudo`) to `$QKMJ_DATA_DIR` / `$HOME/.qkmj`, auto-created at startup.
* Build fixes for modern clang/gcc (`<termios.h>`, `<stdlib.h>`, forward
  declarations, `-std=gnu89`), and cross-platform Makefiles.

The Docker/WebSocket path above is unchanged.

