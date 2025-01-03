// Basic command to restore player health
syncmd_giveHealth(playerid, params[]) {
    SetPlayerHealth(playerid, 100);
    SendClientMessage(playerid, COLOR_GREEN, "Your health has been restored to 100%!");

    return 1;
}
