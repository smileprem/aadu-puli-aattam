/* 
 * File:   Graph.c
 * Author: Premkumar Masilamani
 *
 * Created on 4 July, 2011, 11:12 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include <termios.h>
#include <unistd.h>

#define MAXNODES 23

#define NOANIMAL 0
#define GOAT 1
#define TIGER 2

#define TRUE 1
#define FALSE 0

struct node {
    int animal;
};

struct arc {
    int adj;
};

struct graph {
    struct node nodes[MAXNODES];
    struct arc arcs[MAXNODES][MAXNODES];
};

struct graph g;

void init_graph();
void print_graph();
void initialize_tigers();
int place_goat(int node1);
int move(int animal, int node1, int node2);
int goats_left();

// Below methods need to be implemented.
// returns the animal which won the game TIGER,GOAT or NOANIMAL
int game_over();
int tiger_has_moves();
int predict_next_move(int animal);

int tempChar = 0;
int current_player = 0;
int goat_count = 0;

int main(int argc, char** argv) {
    init_graph();
    print_graph();
    /*
        scanf("Tiger or Goat? Enter 1 for Goat and 2 for tiger : %d", current_player);
        //Just to make sure that the move is from GOAT, if the first chosen one is tiger
        if(current_player == TIGER){
            current_player = GOAT;
        }
     */
    int node1 = 0;
    int node2 = 0;
    int result = FALSE;
    current_player = GOAT;

    while (1 == 1) {
        if (current_player == TIGER) {
            printf("Enter the move for tiger : \n node1: ");
            scanf("%d", &node1);
            printf("node2: ");
            scanf("%d", &node2);
            printf("The nodes entered are node1 = %d and node2 = %d\n", node1, node2);
            result = move(TIGER, node1, node2);
            if (result != TRUE) {
                printf("This move is not allowed for TIGER. Try Again !!!");
                goto loop_end;
            }
        } else {
            if (goat_count < 15) {
                printf("Place the goats:\nEnter the node to place the goat: ");
                scanf("%d", &node1);
                printf("The node entered is %d", node1);
                result = place_goat(node1);
                if (result != TRUE) {
                    printf("You cannot place GOAT here. Try again !!!");
                    goto loop_end;
                }
            } else {
                printf("Enter the move for goat : \n node1: ");
                scanf("%d", &node1);
                printf("node2: ");
                scanf("%d", &node2);
                result = move(GOAT, node1, node2);
                if (result != TRUE) {
                    printf("This move is not allowed for GOAT");
                    goto loop_end;
                }
            }
        }

        current_player = (current_player == TIGER) ? GOAT : TIGER;
loop_end:
        myclrscr();
        print_graph();
    }
    mygetch();
    return (EXIT_SUCCESS);
}

int move(int animal, int node1, int node2) {
    if (animal == TIGER) {
        printf("animal is TIGER");
        if (g.nodes[node1].animal == TIGER && g.nodes[node2].animal == NOANIMAL && g.arcs[node1][node2].adj > 1 && g.nodes[g.arcs[node1][node2].adj].animal == GOAT) {
            // Remove the goat in middle
            g.nodes[g.arcs[node1][node2].adj].animal = NOANIMAL;
            // Remove the tiger from node1
            g.nodes[node1].animal = NOANIMAL;
            // Move the tiger to node2
            g.nodes[node2].animal = TIGER;
            return TRUE;
        } else {
            if (g.nodes[node1].animal == TIGER && g.nodes[node2].animal == NOANIMAL && g.arcs[node1][node2].adj == TRUE) {
                // Remove the tiger from node1
                g.nodes[node1].animal = NOANIMAL;
                // Move the tiger to node2
                g.nodes[node2].animal = TIGER;
                return TRUE;
            }
        }
    } else {
        // If the animal is goat.
        if (g.nodes[node1].animal == GOAT && g.nodes[node2].animal == NOANIMAL && g.arcs[node1][node2].adj == TRUE) {
            // Remove the goat from node1
            g.nodes[node1].animal = NOANIMAL;
            // Move the goat to node2
            g.nodes[node2].animal = GOAT;
            return TRUE;
        }
    }

    return FALSE;
}

int place_goat(int node1) {
    printf("The node is %d and the animal is %d\n", node1, g.nodes[node1].animal);
    if (node1 >= 0 && node1 < MAXNODES && g.nodes[node1].animal == NOANIMAL) {
        g.nodes[node1].animal = GOAT;
        goat_count++;
        return TRUE;
    }
    return FALSE;
}

void initialize_tigers() {
    int i;
    for (i = 0; i < MAXNODES; i++) {
        g.nodes[i].animal = NOANIMAL;
    }
    g.nodes[0].animal = g.nodes[3].animal = g.nodes[4].animal = TIGER;
}

void print_graph() {

    printf("\t\t\t\t\t\t        %d\t\t\t\t\t\n\n\n", g.nodes[0].animal);
    printf("\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n\n", g.nodes[1].animal, g.nodes[2].animal, g.nodes[3].animal, g.nodes[4].animal, g.nodes[5].animal, g.nodes[6].animal);
    printf("\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n\n", g.nodes[7].animal, g.nodes[8].animal, g.nodes[9].animal, g.nodes[10].animal, g.nodes[11].animal, g.nodes[12].animal);
    printf("\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n\n", g.nodes[13].animal, g.nodes[14].animal, g.nodes[15].animal, g.nodes[16].animal, g.nodes[17].animal, g.nodes[18].animal);
    printf("\t\t\t\t%d\t\t%d\t\t%d\t\t%d\t\t\n", g.nodes[19].animal, g.nodes[20].animal, g.nodes[21].animal, g.nodes[22].animal);

}

void init_graph() {

    initialize_tigers();

    //Initializing the arcs with GOAT moves.
    g.arcs[0][2].adj = g.arcs[0][3].adj = g.arcs[0][4].adj = g.arcs[0][5].adj = TRUE;
    g.arcs[1][2].adj = g.arcs[1][7].adj = TRUE;
    g.arcs[2][1].adj = g.arcs[2][0].adj = g.arcs[2][3].adj = g.arcs[2][8].adj = TRUE;
    g.arcs[3][2].adj = g.arcs[3][0].adj = g.arcs[3][4].adj = g.arcs[3][9].adj = TRUE;
    g.arcs[4][3].adj = g.arcs[4][0].adj = g.arcs[4][5].adj = g.arcs[4][10].adj = TRUE;
    g.arcs[5][4].adj = g.arcs[5][0].adj = g.arcs[5][6].adj = g.arcs[5][11].adj = TRUE;
    g.arcs[6][5].adj = g.arcs[6][12].adj = TRUE;
    g.arcs[7][1].adj = g.arcs[7][8].adj = g.arcs[7][13].adj = TRUE;
    g.arcs[8][7].adj = g.arcs[8][2].adj = g.arcs[8][9].adj = g.arcs[8][14].adj = TRUE;
    g.arcs[9][8].adj = g.arcs[9][3].adj = g.arcs[9][10].adj = g.arcs[9][15].adj = TRUE;
    g.arcs[10][9].adj = g.arcs[10][4].adj = g.arcs[10][11].adj = g.arcs[10][16].adj = TRUE;
    g.arcs[11][10].adj = g.arcs[11][5].adj = g.arcs[11][12].adj = g.arcs[11][17].adj = TRUE;
    g.arcs[12][11].adj = g.arcs[12][6].adj = g.arcs[12][18].adj = TRUE;
    g.arcs[13][7].adj = g.arcs[13][14].adj = TRUE;
    g.arcs[14][13].adj = g.arcs[14][8].adj = g.arcs[14][15].adj = g.arcs[14][19].adj = TRUE;
    g.arcs[15][14].adj = g.arcs[15][9].adj = g.arcs[15][16].adj = g.arcs[15][20].adj = TRUE;
    g.arcs[16][15].adj = g.arcs[16][10].adj = g.arcs[16][17].adj = g.arcs[16][21].adj = TRUE;
    g.arcs[17][16].adj = g.arcs[17][11].adj = g.arcs[17][18].adj = g.arcs[17][22].adj = TRUE;
    g.arcs[18][17].adj = g.arcs[18][12].adj = TRUE;
    g.arcs[19][14].adj = g.arcs[19][20].adj = TRUE;
    g.arcs[20][19].adj = g.arcs[20][15].adj = g.arcs[20][21].adj = TRUE;
    g.arcs[21][20].adj = g.arcs[21][16].adj = g.arcs[21][22].adj = TRUE;
    g.arcs[22][21].adj = g.arcs[22][17].adj = TRUE;

    //Initializing the arcs with TIGER moves.
    g.arcs[0][8].adj = 2;
    g.arcs[0][9].adj = 3;
    g.arcs[0][10].adj = 4;
    g.arcs[0][11].adj = 5;
    g.arcs[1][3].adj = 2;
    g.arcs[1][13].adj = 7;
    g.arcs[2][4].adj = 3;
    g.arcs[2][14].adj = 8;
    g.arcs[3][1].adj = 2;
    g.arcs[3][5].adj = 4;
    g.arcs[3][15].adj = 9;
    g.arcs[4][2].adj = 3;
    g.arcs[4][6].adj = 5;
    g.arcs[4][16].adj = 10;
    g.arcs[5][3].adj = 4;
    g.arcs[5][17].adj = 11;
    g.arcs[6][4].adj = 5;
    g.arcs[6][18].adj = 12;
    g.arcs[7][9].adj = 8;
    g.arcs[8][0].adj = 2;
    g.arcs[8][10].adj = 9;
    g.arcs[8][19].adj = 14;
    g.arcs[9][7].adj = 8;
    g.arcs[9][0].adj = 3;
    g.arcs[9][20].adj = 15;
    g.arcs[9][11].adj = 10;
    g.arcs[10][8].adj = 9;
    g.arcs[10][0].adj = 4;
    g.arcs[10][12].adj = 11;
    g.arcs[10][21].adj = 16;
    g.arcs[11][9].adj = 10;
    g.arcs[11][0].adj = 5;
    g.arcs[11][22].adj = 17;
    g.arcs[12][10].adj = 11;
    g.arcs[13][1].adj = 7;
    g.arcs[13][15].adj = 14;
    g.arcs[14][2].adj = 8;
    g.arcs[14][16].adj = 15;
    g.arcs[15][13].adj = 14;
    g.arcs[15][3].adj = 9;
    g.arcs[15][17].adj = 16;
    g.arcs[16][14].adj = 15;
    g.arcs[16][4].adj = 10;
    g.arcs[16][18].adj = 17;
    g.arcs[17][15].adj = 16;
    g.arcs[17][5].adj = 11;
    g.arcs[18][16].adj = 17;
    g.arcs[18][6].adj = 12;
    g.arcs[19][8].adj = 14;
    g.arcs[19][21].adj = 20;
    g.arcs[20][9].adj = 15;
    g.arcs[20][22].adj = 21;
    g.arcs[21][19].adj = 20;
    g.arcs[21][10].adj = 16;
    g.arcs[22][20].adj = 21;
    g.arcs[22][11].adj = 17;

}

int mygetch(void) {
    struct termios oldt,
            newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void myclrscr() {
    fprintf(stdout, "\033[2J\033[0;0f");
    fflush(stdout);
}

int goats_left() {
    int i = 0;
    int count = 0;
    for (i = 0; i < MAXNODES; i++) {
        count += g.nodes[i].animal;
    }
    return count - 6;
}