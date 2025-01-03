/***************************************
 *                                     *
 *   ██████╗ ██╗   ██╗██╗     ██████╗ *
 *   ██╔══██╗██║   ██║██║     ██╔══██╗*
 *   ██████╔╝██║   ██║██║     ██████╔╝*
 *   ██╔══██╗██║   ██║██║     ██╔══██╗*
 *   ██████╔╝╚██████╔╝███████╗██████╔╝*
 *                                     *
 *   @Author:      Kobaalito           *
 *   @Version:     1.0.0               *
 *   @Released:    02/01/2025          *
 *   @GitHub:      https://github.com/Kobalitoo*
 *   @Library:     sycmd                *
 *                                     *
 ***************************************/

#define MAX_CMD_NAME (32)
#define MAX_ARGUMENTS (128)
#define IS_ADMIN(playerid) (GetPlayerAdminLevel(playerid) > 0)

// Define the prefix for SYCMD commands
#define SYNCMD:%1(%2)			\
            forward syncmd_%1(%2); \
            public syncmd_%1(%2)

// Macro to add SYCMD commands
#define synCommand(%1,%2,%3) \
            SYNCMD:%1(%2, %3)

// Declare event "hooks"
forward OnPlayerCommandReceived(playerid, cmdtext[]);
forward OnPlayerCommandProcessed(playerid, cmdtext[], success);

// Necessary variables
static bool:syncmd_g_HasCommandReceived = false;
static logBuffer[MAX_PLAYERS][128];

// Gamemode initialization function
public OnGameModeInit()
{
    syncmd_g_HasCommandReceived = funcidx("OnPlayerCommandReceived") != -1;
    if (funcidx("syncmd_OnGameModeInit") != -1)
    {
        return CallLocalFunction("syncmd_OnGameModeInit", "");
    }
    return 1;
}

// Verifies if the player has admin permissions (customize according to your system)
#define IS_ADMIN(playerid) (GetPlayerAdminLevel(playerid) > 0)

// This function handles the commands players send
public OnPlayerCommandText(playerid, cmdtext[])
{
    // If another extension handles OnPlayerCommandReceived, we don’t process the command here
    if (syncmd_g_HasCommandReceived && !CallLocalFunction("OnPlayerCommandReceived", "is", playerid, cmdtext))
    {
        return 1;
    }

    // Process the command
    new pos, funcname[MAX_CMD_NAME], arguments[MAX_ARGUMENTS];
    while (cmdtext[++pos] > ' ') 
    {
        funcname[pos-1] = tolower(cmdtext[pos]); 
    }
    format(funcname, sizeof(funcname), "syncmd_%s", funcname);
    while (cmdtext[pos] == ' ') pos++;
    
    // Save the arguments
    new i = 0;
    while (cmdtext[pos] && cmdtext[pos] != '\n' && cmdtext[pos] != '\r' && i < MAX_ARGUMENTS-1)
    {
        arguments[i++] = cmdtext[pos++];
    }
    arguments[i] = '\0'; // End the arguments string

    // Verify permissions (only admin can execute certain commands)
    if (strcmp(funcname, "syncmd_someAdminCommand", true) == 0 && !IS_ADMIN(playerid))
    {
        SendClientMessage(playerid, COLOR_RED, "You don’t have permission to use this command.");
        return 0;
    }

    // If the command is empty, process it
    if (!cmdtext[pos])
    {
        return CallLocalFunction(funcname, "is", playerid, "\1");
    }

    // Call the command function with arguments
    return CallLocalFunction(funcname, "is", playerid, arguments);
}

// This function handles the case when another extension or gamemode has processed a command
public OnPlayerCommandProcessed(playerid, cmdtext[], success)
{
    // Additional logic if another extension has already processed the command (e.g., logging)
    // Here you can log the executed command and its result in a log file
    logCommand(playerid, cmdtext, success);
    return success;
}

// Example command with autocomplete
public syncmd_help(playerid, arguments[])
{
    SendClientMessage(playerid, COLOR_YELLOW, "Available commands:");
    SendClientMessage(playerid, COLOR_YELLOW, "/command1 - Command 1 description");
    SendClientMessage(playerid, COLOR_YELLOW, "/command2 - Command 2 description");
    return 1;
}

// Command with multiple arguments
public syncmd_testArgsCommand(playerid, arguments[])
{
    SendClientMessage(playerid, COLOR_GREEN, "Command with multiple arguments executed.");
    return 1;
}

// Command for administrators only
public syncmd_someAdminCommand(playerid, arguments[])
{
    if (!IS_ADMIN(playerid))
    {
        SendClientMessage(playerid, COLOR_RED, "You don’t have permission to use this command.");
        return 0;
    }

    SendClientMessage(playerid, COLOR_GREEN, "Admin command executed.");
    return 1;
}

// Example command with log
public syncmd_testCommand(playerid, arguments[])
{
    // Log the command
    logCommand(playerid, arguments, true);
    SendClientMessage(playerid, COLOR_GREEN, "Command executed.");
    return 1;
}

// Function to log executed commands (audit)
public logCommand(playerid, cmdtext[], success)
{
    format(logBuffer[playerid], sizeof(logBuffer[playerid]), "Player %d executed the command: %s. Success: %d", playerid, cmdtext, success);
    // Here you can add the log to a file or database
    // LogToFile(logBuffer[playerid]); // Example of logging function
    printf(logBuffer[playerid]); // Prints in the server console
}
