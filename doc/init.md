Sample init scripts and service configuration for iridiumd
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/iridiumd.service:    systemd service unit configuration
    contrib/init/iridiumd.openrc:     OpenRC compatible SysV style init script
    contrib/init/iridiumd.openrcconf: OpenRC conf.d file
    contrib/init/iridiumd.conf:       Upstart service configuration file
    contrib/init/iridiumd.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "iridium" user
and group.  They must be created before attempting to use these scripts.
The OS X configuration assumes iridiumd will be set up for the current user.

Configuration
---------------------------------

At a bare minimum, iridiumd requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, iridiumd will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that iridiumd and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If iridiumd is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running iridiumd without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/iridium.conf`.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/iridiumd`  
Configuration file:  `/etc/iridium/iridium.conf`  
Data directory:      `/var/lib/iridiumd`  
PID file:            `/var/run/iridiumd/iridiumd.pid` (OpenRC and Upstart) or `/var/lib/iridiumd/iridiumd.pid` (systemd)  
Lock file:           `/var/lock/subsys/iridiumd` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the iridium user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
iridium user and group.  Access to iridium-cli and other iridiumd rpc clients
can then be controlled by group membership.

### Mac OS X

Binary:              `/usr/local/bin/iridiumd`  
Configuration file:  `~/Library/Application Support/Iridium/iridium.conf`  
Data directory:      `~/Library/Application Support/Iridium`  
Lock file:           `~/Library/Application Support/Iridium/.lock`  

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start iridiumd` and to enable for system startup run
`systemctl enable iridiumd`

### OpenRC

Rename iridiumd.openrc to iridiumd and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/iridiumd start` and configure it to run on startup with
`rc-update add iridiumd`

### Upstart (for Debian/Ubuntu based distributions)

Drop iridiumd.conf in /etc/init.  Test by running `service iridiumd start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy iridiumd.init to /etc/init.d/iridiumd. Test by running `service iridiumd start`.

Using this script, you can adjust the path and flags to the iridiumd program by
setting the IRIDIUMD and FLAGS environment variables in the file
/etc/sysconfig/iridiumd. You can also use the DAEMONOPTS environment variable here.

### Mac OS X

Copy org.iridium.iridiumd.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.iridium.iridiumd.plist`.

This Launch Agent will cause iridiumd to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run iridiumd as the current user.
You will need to modify org.iridium.iridiumd.plist if you intend to use it as a
Launch Daemon with a dedicated iridium user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
