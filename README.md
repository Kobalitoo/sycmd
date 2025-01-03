# sycmd - Command System for SA:MP

sycmd is a lightweight and powerful command library for SA:MP (San Andreas Multiplayer). It allows you to create, manage, and customize server commands efficiently, offering advanced features like permission handling and seamless integration with your gamemode.

This repository is an easy-to-use solution for managing SA:MP commands, with support for multiple arguments, admin permissions, and simple command structures.

# 🚀 Features
- **Simple and Fast Command Creation**: Add commands to your server using a straightforward macro.
- **Multiple Arguments Support**: Define commands with multiple parameters and handle them flexibly.
- **Permission System**: Easily manage who can execute certain commands with admin-level checks.
- **Lightweight & Optimized**: Minimal impact on server performance.
- **Seamless Integration**: Works with any SA:MP gamemode or extension.

# 🔧 Installation

To get started with sycmd, follow the steps below:

# Using sampctl (Recommended)
Simply install the package using sampctl for easy management and updates:

```
sampctl package install Kobalitoo/sycmd
Once installed, include the library in your project:
```

# include <sycmd>
Manual Installation
Alternatively, you can manually download the sycmd.inc file and place it in your project directory. Then, include it like this:

```
#include "sycmd.inc"
```
# ⚡ Usage
Basic Command Example
After including the library, you can start defining commands like this:

```
syncmd_help(playerid, params[]) {
    SendClientMessage(playerid, 0xFFFF00FF, "This is the help command!");
    return 1;
}
Command with Admin Permissions
To restrict a command to admins only:
```
```
syncmd_adminOnlyCommand(playerid, params[]) {
    if (!IS_ADMIN(playerid)) {
        SendClientMessage(playerid, COLOR_RED, "You don't have permission to use this command.");
        return 0;
    }
    
    SendClientMessage(playerid, COLOR_GREEN, "Admin command executed successfully.");
    return 1;
}
Command with Multiple Arguments
Commands can also accept multiple arguments:
```
```
syncmd_testArgsCommand(playerid, params[]) {
    SendClientMessage(playerid, COLOR_GREEN, "Command with multiple arguments executed!");
    return 1;
}
Advanced Logging (Optional)
You can implement logging of executed commands:
```
```
public logCommand(playerid, cmdtext[], success)
{
    format(logBuffer[playerid], sizeof(logBuffer[playerid]), "Player %d executed the command: %s. Success: %d", playerid, cmdtext, success);
    printf(logBuffer[playerid]); // Print log to server console
}

```
# 📝 Documentation
For more advanced usage and detailed documentation, please refer to the original documentation or explore the source code in this repository.

# 📜 License
This repository is licensed under the MIT License. Feel free to contribute, modify, and use it in your projects.

# 📌 Notes
This document is being updated consecutively, which is in its beta phase, make sure you have the most recent update.

