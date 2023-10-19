#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "player.h"

struct player_t* player_init(const char* n, const char* pswd, int32_t p_age) 
{
    struct player_t* p = NULL;

    p = (struct player_t*) malloc(sizeof(struct player_t));
    if (NULL == p) { return NULL; }

    p->name = (char *)malloc(strlen(n) + 1);
    if (NULL == p->name) { 
        free(p);
        return 0; 
    }

    strcpy(p->name, n);
    strncpy(p->password, pswd, 19);
    p->age = p_age;
    p->num_games = 0;

    for (int32_t i = 0; 16 > i; i++) {
        p->score_dist[i] = 0;
    }

    p->next = NULL;

    return p;
}

int32_t player_delete(struct player_t** player_list, struct player_t* p)
{
    struct player_t** find;
    
    for (find = player_list; p != *find; find = &(*find)->next) {
        if (NULL == *find) {
            return 0;
        }
    }

    *find = p->next;
    free(p->name);
    free(p);

    return 1;
}

void player_print(struct player_t* player_list)
{
    for (struct player_t *p = player_list; p != NULL; p = p->next) {
        printf("%p ", p);
        printf("%s %s %d %d ", p->name, p->password, p->age, p->num_games);
        printf("%p\n", p->next);
    }

    printf("\n");
}
