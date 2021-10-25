#include <stdio.h>
#include "player.h"

int main()
{
    struct player_t *player_list = NULL;
    struct player_t *new_player = NULL;

    struct player_t *h, *m, *t;

    printf("Adding to the list...\n\n");

    // add first player
    player_list = player_init("Player 1", "Passwd 1", 1);
    player_print(player_list);
    t = player_list; // store pointer to this player_t

    // add second player to the head
    new_player = player_init("Player 2", "Passwd 2", 2);
    new_player->next = player_list;
	player_list = new_player;
    player_print(player_list);
    m = player_list; // store pointer to this player_t

    // add third player to the head
    new_player = player_init("Player 3", "Passwd 3", 3);
    new_player->next = player_list;
	player_list = new_player;
    player_print(player_list);

    // add next player to the head
    new_player = player_init("Player 4", "Passwd 4", 4);
    new_player->next = player_list;
	player_list = new_player;
    player_print(player_list);
    h = player_list; // store pointer to this player_t

    printf("Deleting from the list...\n\n");

    // delete player at the list head
    player_delete(&player_list, h);
    player_print(player_list);

    // delete player in the middle of the list
    player_delete(&player_list, m);
    player_print(player_list);

    // delete player at the end of the list
    player_delete(&player_list, t);
    player_print(player_list);

    // delete last player
    player_delete(&player_list, player_list);
    player_print(player_list);


    return 0;
}
