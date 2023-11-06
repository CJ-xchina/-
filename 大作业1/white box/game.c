#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#define BOX_MAX 4
#define PLAYER_HP_MAX 100
#define REGION_INIT 0
#define REGION_GOAL 12
#define REGION_NEXT_END -1

int16_t REGION_NEXT[12][13] = {
    {1, 2, REGION_NEXT_END},
    {3, 4, 5, REGION_NEXT_END},
    {6, REGION_NEXT_END},
    {7, REGION_NEXT_END},
    {7, REGION_NEXT_END},
    {6, 7, REGION_NEXT_END},
    {9, REGION_NEXT_END},
    {8, REGION_NEXT_END},
    {10, REGION_NEXT_END},
    {10},
    {11, REGION_NEXT_END},
    {12, REGION_NEXT_END},
};

typedef struct Entity {
    char name[32];
    int16_t hp;
    int16_t hpMax;
    int16_t atk;
    int16_t def;
} Entity;

typedef struct Player {
    char name[8];
    int16_t box[BOX_MAX];
    int16_t hp;
    int16_t atk;
    int16_t def;
    int16_t region;
} Player;

#define ITEM_EMPTY 0
#define ITEM_MAX 128
#define ITEM_NAME_MAX 32

#define ITEM_GOD_MIN 65
#define ITEM_GOD_MAX 122

#define ITEM_HP_ADD_10 1
#define ITEM_HP_ADD_50 2
#define ITEM_HP_ADD_100 3
#define ITEM_ATK_ADD_10 4
#define ITEM_ATK_DOUBLE 5
#define ITEM_ATK_HALF_DEF_ADD_1 6
#define ITEM_DEF_ADD_2 7
#define ITEM_DEF_HALF_ATK_ADD_10 8

char ITEM_NAMES[ITEM_MAX][ITEM_NAME_MAX] = {
    "EMPTY",
    "HP+10",
    "HP+50",
    "HP+100",
    "ATK+10",
    "ATK*2",
    "ATK/2, but DEF+1",
    "DEF+2",
    "DEF/2, but ATK+10",
};

Player player;
bool endFlag = false;
#define INPUT_BUF_MAX 4096
char inputBuf[INPUT_BUF_MAX];

void endWithEOF() {
    printf(" * ERROR: Unexpected EOF!\n");
    exit(1);
}

void input() {
    char ch;
    uint32_t i = 0;
    while ((ch = getchar()) != EOF && ch != '\n') {
        inputBuf[i++] = ch;
    }
    if (ch == EOF) {
        endWithEOF();
    }
    inputBuf[i] = '\0';
}

int16_t inputInt() {
    input();
    if (strlen(inputBuf) < 1) return -1;
    for (uint16_t i = 0; i < strlen(inputBuf); i++) {
        if (!isdigit(inputBuf[i])) return -1;
    }
    return (int16_t) atoi(inputBuf);
}

void initPlayer() {
    player.hp = PLAYER_HP_MAX;
    player.atk = 10;
    player.def = 1;
    player.region = REGION_INIT;
    for (uint32_t i = 0; i < BOX_MAX; i++) {
        player.box[i] = ITEM_EMPTY;
    }
}

int16_t countPlayerItems() {
    int16_t cnt = 0;
    for (uint16_t i = 0; i < BOX_MAX; i++) {
        if (player.box[i] != ITEM_EMPTY) {
            cnt++;
        }
    }
    return cnt;
}

void printPlayerStatus() {
    printf("\n");
    printf("------------------------------------\n");
    printf("            Player Status           \n");
    printf(" Name: %s\n", player.name);
    printf(" HP: %d/%d    ATK: %d    DEF: %d\n", player.hp, PLAYER_HP_MAX, player.atk, player.def);
    printf(" Items: %d    Region: %d\n", countPlayerItems(), player.region);
    printf("------------------------------------\n");
}

void printEnemyStatus(Entity *enemy) {
    printf("            Enemy Status            \n");
    printf(" Name: %s\n", enemy->name);
    printf(" HP: %d/%d    ATK: %d    DEF: %d\n", enemy->hp, enemy->hpMax, enemy->atk, enemy->def);
    printf("------------------------------------\n");
}

bool handleItemDirectly(int16_t itemId) {
    printf(" -> You used the item [%s]!\n", ITEM_NAMES[itemId]);
    switch (itemId) {
    case ITEM_HP_ADD_10:
        player.hp += 10;
        if (player.hp > PLAYER_HP_MAX) {
            player.hp = PLAYER_HP_MAX;
        }
        break;
    case ITEM_HP_ADD_50:
        player.hp += 50;
        if (player.hp > PLAYER_HP_MAX) {
            player.hp = PLAYER_HP_MAX;
        }
        break;
    case ITEM_HP_ADD_100:
        player.hp += 100;
        if (player.hp > PLAYER_HP_MAX) {
            player.hp = PLAYER_HP_MAX;
        }
        break;
    case ITEM_ATK_ADD_10:
        player.atk += 10;
        break;
    case ITEM_ATK_DOUBLE:
        player.atk *= 2;
        break;
    case ITEM_ATK_HALF_DEF_ADD_1:
        player.atk /= 2;
        player.def += 1;
        break;
    case ITEM_DEF_ADD_2:
        player.def += 2;
        break;
    case ITEM_DEF_HALF_ATK_ADD_10:
        player.def /= 2;
        player.atk += 10;
        break;
    default:
        printf(" * The item [%s] cannot be used.", ITEM_NAMES[itemId]);
        return false;
    }
    return true;
}

bool handleItem(uint16_t slotId) {
    int16_t itemId = player.box[slotId];
    bool res = handleItemDirectly(itemId);
    if (res) {
        player.box[slotId] = ITEM_EMPTY;
    }
    printPlayerStatus();
    return res;
}

void checkPlayerStatus() {
    if (player.hp <= 0) {
        printf(" * You died! GAME OVER!\n");
        printPlayerStatus();
        exit(0);
    }
    if (countPlayerItems() < 1) return;
    for (uint16_t i = 0; i < BOX_MAX; i++) {
        if (player.box[i] >= ITEM_GOD_MIN && player.box[i] <= ITEM_GOD_MAX) {
            printf(" -> You HAVE the item [OhMyGod], you CLEAR the game!!!\n");
            endFlag = true;
            break;
        }
    }
}

void welcome() {
    printf("====================================\n");
    printf("===== Welcome to RPG Game V1.0 =====\n");
    printf("====================================\n");
}

void inputPlayerName() {
    printf(" * Please input player name: ");
    input();
    strcpy(player.name, inputBuf);
    printf(" * Your name is: %s\n", player.name);
}

int16_t playerUseItem() {
    bool finish = false;
    int16_t slotId = -1;
    do {
        printf("\n************************************\n");
        printf(" * Your item(s) are listed below:\n");
        printf(" - 0. Cancel\n");
        for (uint16_t i = 0; i < BOX_MAX; i++) {
            if (player.box[i] != ITEM_EMPTY) {
                printf(" - %d. [%s]\n", i + 1, ITEM_NAMES[player.box[i]]);
            }
        }
        printf(" * Please choose one to **USE**: ");

        int16_t choice = inputInt();
        switch (choice) {
        case 0:
            printf(" -> You cancelled using item.\n");
            finish = true;
            break;
        default:
            slotId = choice;
            if (slotId < 1 || slotId > BOX_MAX || player.box[slotId] == ITEM_EMPTY) {
                printf(" * Invalid choice!\n");
                break;
            }
            if (!handleItem(slotId)) {
                slotId = -1;
            }
            finish = true;
            break;
        }
    } while (!finish);
    return slotId;
}

int16_t playerDestroyItem() {
    printf("\n************************************\n");
    printf(" * Your item(s) are listed below:\n");
    printf(" - 0. Cancel\n");
    for (uint16_t i = 0; i < BOX_MAX; i++) {
        if (player.box[i] != ITEM_EMPTY) {
            printf(" - %d. [%s]\n", i + 1, ITEM_NAMES[player.box[i]]);
        }
    }
    bool finish = false;
    int16_t slotId = -1;
    do {
        printf(" * Please choose an item to **DESTROY**: ");
        int16_t choice = inputInt();
        switch (choice) {
        case 0:
            printf(" -> You cancelled destroying item.\n");
            finish = true;
            break;
        default:
            slotId = choice - 1;
            if (slotId < 0 || slotId >= BOX_MAX) {
                printf(" * Invalid choice!\n");
                break;
            }
            printf(" -> You destroyed item [%s]!\n", ITEM_NAMES[player.box[slotId]]);
            player.box[slotId] = ITEM_EMPTY;
            finish = true;
            break;
        }
    } while (!finish);
    return slotId;
}

void playerGiveUp() {
    printf(" -> You gave up the game!\n");
    exit(0);
}

bool playerChooseNextRegion(uint16_t currRegion) {
    bool flag = true;
    do {
        printf("\n************************************\n");
        printf(" * Choose a region:\n");
        printf(" - 0. Cancel\n");

        int16_t availableRegions[REGION_GOAL];
        uint16_t cnt = 0;
        for (uint16_t i = 0; i < REGION_GOAL; i++) {
            if (REGION_NEXT[currRegion][i] == -1) {
                break;
            }
            cnt++;
            printf(" - %d. Region #%d\n", cnt, REGION_NEXT[currRegion][i]);
            availableRegions[cnt - 1] = REGION_NEXT[currRegion][i];
        }

        printf(" * Please choose next region: ");
        int16_t choice = inputInt();
        if (choice == 0) {
            printf(" -> You cancelled choosing region.\n");
            break;
        }
        if (choice < 1 || choice > cnt) {
            printf(" * Invalid input!\n");
            flag = false;
            continue;
        }

        int16_t region = availableRegions[choice - 1];
        player.region = region;
        printf(" -> You moved to region #%d.\n", region);
        return true;
    } while (!flag);
    return false;
}

void givePlayerItem(int16_t itemId) {
    if (itemId <= ITEM_EMPTY || itemId >= ITEM_MAX) {
        printf(" * ERROR: Invalid Item ID: %d\n", itemId);
        return;
    }
    int16_t slot = -1;
    for (uint16_t i = 0; i < BOX_MAX; i++) {
        if (player.box[i] == ITEM_EMPTY) {
            slot = i;
            break;
        }
    }
    while (slot == -1) {
        printf(" -> You got the item [%s]", ITEM_NAMES[itemId]);
        printf(", but your item box is full!\n");
        printf(" * Please choose an operation:\n");
        printf(" - 1. Use the item [%s] now\n", ITEM_NAMES[itemId]);
        printf(" - 2. Abandon the item [%s]\n", ITEM_NAMES[itemId]);
        printf(" - 3. Use another item first\n");
        printf(" - 4. Destroy another item first\n");
        printf(" * Please choose: ");

        int16_t choice = inputInt();
        switch (choice) {
        case 1:
            handleItemDirectly(itemId);
            slot = -2;
            break;
        case 2:
            break;
        case 3:
            slot = playerUseItem();
            break;
        case 4:
            slot = playerDestroyItem();
            break;
        default:
            printf(" * Invalid choice!\n");
            break;
        }
    }
    if (slot >= 0) {
        player.box[slot] = itemId;
    }
    printf(" -> You got the item [%s]\n", ITEM_NAMES[itemId]);
}

void fightDoPlayerAttack(Entity *enemy) {
    int16_t damage = player.atk / enemy->def;
    enemy->hp -= damage;
    printf(" -> You hit the enemy [%s], caused damage: %d\n", enemy->name, damage);
}

void fightDoEnemyAttack(Entity *enemy) {
    int16_t damage = enemy->atk / player.def;
    player.hp -= damage;
    if (player.hp < 0) {
        player.hp = 0;
    }
    printf(" -> Enemy [%s] hit you, caused damage: %d\n", enemy->name, damage);
}

void fight(Entity *enemy) {
    printf("\n************************************\n");
    printf(" ! Ooooops ! Entered battle!");

    do {
        printPlayerStatus();
        printEnemyStatus(enemy);
        bool playerTurnFinished = true;
        do {
            printf(" * Next steps:\n");
            printf(" - 0. Do nothing\n");
            printf(" - 1. Attack\n");
            printf(" - 2. Use Item\n");
            printf(" - 3. Check Status\n");
            printf(" - 4. Surrender\n");
            printf(" * Please choose next step: ");

            int16_t choice = inputInt();
            switch (choice) {
            case 0:
                playerTurnFinished = true;
                break;
            case 1:
                playerTurnFinished = true;
                fightDoPlayerAttack(enemy);
                break;
            case 2:
                playerUseItem();
                break;
            case 3:
                printPlayerStatus();
                printEnemyStatus(enemy);
                playerTurnFinished = false;
                break;
            case 4:
                playerGiveUp();
                break;
            default:
                printf(" * Invalid choice!\n");
                break;
            }
        } while (!playerTurnFinished);

        if (enemy->hp > 0) {
            fightDoEnemyAttack(enemy);
        }

        checkPlayerStatus();
    } while (enemy->hp >= 0);

    printf(" -> Enemy [%s] died! You win!\n", enemy->name);
}

void enterRegion(uint16_t region) {
    Entity enemy;
    switch (region) {
    case 0:
        givePlayerItem(ITEM_HP_ADD_100);
        break;
    case 1:
    case 6:
        printf(" -> You've met a Hilichurls!\n");
        strcpy(enemy.name, "Hilichurls");
        enemy.hp = 15;
        enemy.hpMax = 15;
        enemy.atk = 5;
        enemy.def = 1;
        fight(&enemy);
        
        givePlayerItem(ITEM_HP_ADD_10);
        printPlayerStatus();
        break;
    case 7:
        printf(" -> You've met a stronger Hilichurls!\n");
        strcpy(enemy.name, "Strong Hilichurls");
        enemy.hp = 20;
        enemy.hpMax = 20;
        enemy.atk = 50;
        enemy.def = 1;
        fight(&enemy);
        
        givePlayerItem(ITEM_HP_ADD_50);
        printPlayerStatus();
        break;
    case 2:
    case 3:
        printf(" -> You found a mysterious box!\n");
        givePlayerItem(ITEM_DEF_HALF_ATK_ADD_10);
        givePlayerItem(ITEM_DEF_HALF_ATK_ADD_10);
        break;
    case 5:
    case 8:
    case 9:
        printf(" -> You found a treasure box!\n");
        givePlayerItem(ITEM_DEF_ADD_2);
        break;
    case 10:
        printf(" -> You've met a powerful Sentinels!\n");
        strcpy(enemy.name, "Ruin Sentinels");
        enemy.hp = 30;
        enemy.hpMax = 30;
        enemy.atk = 20;
        enemy.def = 1;
        
        fight(&enemy);
        givePlayerItem(ITEM_ATK_ADD_10);
        givePlayerItem(ITEM_ATK_DOUBLE);
        printPlayerStatus();
        break;
    case 11:
        printf(" -> You've met the BOSS!\n");
        strcpy(enemy.name, "Lawachurls");
        enemy.hp = 50;
        enemy.hpMax = 50;
        enemy.atk = 30;
        enemy.def = 2;
        
        fight(&enemy);
        givePlayerItem(ITEM_HP_ADD_50);
        printPlayerStatus();
        break;
        break;
    case 12:
        printf(" * Congratulations! You arrived the GOAL!\n");
        exit(0);
    case 4:

        printf(" * ERROR: Region #4 not implemented!\n");
        exit(2);
    default:

        printf(" * ERROR: Region #%d not implemented!\n", player.region);
        exit(3);
    }
}

void playerNextStep() {
    bool flag = true;
    do {
        printf("\n************************************\n");
        printf(" * Determine next step:\n");
        printf(" - 1. Go to next region\n");
        printf(" - 2. Use item\n");
        printf(" - 3. Destroy item\n");
        printf(" - 4. Check status\n");
        printf(" - 5. Give UP\n");
        printf(" * Please choose next step: ");

        int16_t choice = inputInt();
        switch (choice) {
        case 1:
            if (playerChooseNextRegion(player.region)) {
                enterRegion(player.region);
            } else {
                flag = false;
            }
            break;
        case 2:
            if (playerUseItem() == -1) {
                flag = false;
            }
            break;
        case 3:
            if (playerDestroyItem() == -1) {
                flag = false;
            }
            break;
        case 4:
            printPlayerStatus();
            break;
        case 5:
            playerGiveUp();
            break;
        default:
            printf(" * Invalid input!\n");
            flag = false;
            break;
        }
    } while (!flag);
}

void startGame() {
    if (strlen(player.name) < 1) {
        inputPlayerName();
    }
    printPlayerStatus();
    checkPlayerStatus();
    if (!endFlag) {
        enterRegion(player.region);
    }
    while (!endFlag) {
        playerNextStep();
        checkPlayerStatus();
    }
}

int main(int argc, const char *argv[]) {
    welcome();
    initPlayer();
    startGame();
    return 0;
}
