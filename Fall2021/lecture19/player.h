#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdint.h>

struct player_t {
    char *name;
    char password[20]; 
    int32_t age;
    int32_t num_games;
    int32_t score_dist[16];
    struct player_t* next;
};

// add new player_t to the head of the linked list
struct player_t* player_init(const char* n, const char* pswd, int32_t p_age);

// remove player_t from the list
int32_t player_delete (struct player_t** player_list, struct player_t* p);

// print player_t linked list
void player_print(struct player_t* player_list);

#endif
