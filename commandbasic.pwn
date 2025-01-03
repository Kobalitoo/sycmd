// Basic command to restore player health
syncmd_giveHealth(playerid, params[]) {
    // Set the player's health to maximum (100)
    SetPlayerHealth(playerid, 100);

    // Inform the player that their health has been restored
    SendClientMessage(playerid, COLOR_GREEN, "Your health has been restored to 100%!");

    return 1;
}
