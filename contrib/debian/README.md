
Debian
====================
This directory contains files used to package iridiumd/iridium-qt
for Debian-based Linux systems. If you compile iridiumd/iridium-qt yourself, there are some useful files here.

## iridium: URI support ##


iridium-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install iridium-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your iridium-qt binary to `/usr/bin`
and the `../../share/pixmaps/iridium128.png` to `/usr/share/pixmaps`

iridium-qt.protocol (KDE)

