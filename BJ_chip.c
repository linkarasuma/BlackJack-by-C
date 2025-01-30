

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	char mark[128];
	int number;
	int point;
} Card;

typedef struct {
	char name[64];
	int score;
	Card hand[20];
	int count;
} Player;

void printScore(Player p) {
	printf("■%-8s      ", p.name);
	printf("( %2dP ) ",p.score);
	for (int i = 0; i < p.count; i++) {
		printf("%s < %2d >   ",p.hand[i].mark, p.hand[i].number);
	}
	putchar('\n');
}
void printMask(Player p) {
	printf("■%-8s      ", p.name);
	printf("( --P ) ");
	printf("%s < %2d >   ******* < ** >",p.hand[0].mark, p.hand[0].number);
	putchar('\n');
}

int isJudge(int a, int b) {
	if ( a == 21 && b != 21)
			return 1;
		else if ( a != 21 && b == 21 )
			return 2;
		else if ( a == b )
			return 0;
		else if ( a > 21 && b > 21 )
			return 0;
		else if ( a > 21 && b < 21 )
			return 2;
		else if ( a < 21 && b > 21 )
			return 1;
		else if ( a > b )
			return 1;
		else if ( a < b )
			return 2;
}

void shuffle (Card c[], int n) {
	srand(time(NULL));
	Card temp[n];
	int ram;

	for (int i = 0; i < n; i++) {
		ram = rand() % n;
		temp[i] = c[ram];
		c[ram]  = c[n - 1];
		c[n - 1] = temp[i];
	}
}

void Drew(Player *p, Card *d,int *deck_size,int *top) {
	p->hand[p->count] = d[(*top)];
	p->count++;
	p->score += d[(*top)].point;
	(*top)++;
	(*deck_size)--;
}

void animation() {
	putchar('\n');
	for (int i = 0; i < 10; i++) {
		printf("☆☆"); fflush(0); Sleep(100);
	}
	putchar('\n');
}

int main(void) {

	while(1) {

	Player player1;
	strcpy(player1.name, "Computer");
	player1.score = 0;
	player1.count = 0;

	Player player2;
	strcpy(player2.name, "Human");
	player2.score = 0;
	player2.count = 0;

	Card deck[52];

	int deck_size = 52;
	int retry;
	int top = 0;

	for (int i = 0; i < 13; i++) {

		for (int j = 0; j < 13; j++) {
			strcpy(deck[j].mark, "ク ラ ブ");
			deck[j].number = j + 1;
		}

		for (int j = 13; j < 26; j++) {
			strcpy(deck[j].mark, "ダ イ ヤ");
			deck[j].number = j - 12;
		}

		for (int j = 26; j < 39; j++) {
			strcpy(deck[j].mark, "ハ ー ト");
			deck[j].number = j - 25;
		}

		for (int j = 39; j < 52; j++) {
			strcpy(deck[j].mark, "スペード");
			deck[j].number = j - 38;
		}
	}

	for (int i = 0; i < 10; i++) {
		deck[i].point      = i + 1;
		deck[i + 13].point = i + 1;
		deck[i + 26].point = i + 1;
		deck[i + 39].point = i + 1;
	}
	for (int i = 10; i < 13; i++) {
		deck[i].point = 10;
		deck[i + 13].point = 10;
		deck[i + 26].point = 10;
		deck[i + 39].point = 10;
	}

	shuffle(deck,deck_size);

	putchar('\n');
	puts("■□■□■□■□■□■□ BlackJack START □■□■□■□■□■□■\n");

	//COMのドロー
	for (int i = 0; i < 2; i++) {
		Drew(&player1,deck,&deck_size,&top);
	}
	printMask(player1);

	//PLのドロー

	for (int i = 0; i < 2; i++) {
		Drew(&player2,deck,&deck_size,&top);
	}
	printScore(player2);

	printf("□カードを引きますか？ [Y...1 / N...0]"); fflush(0); scanf("%d", &retry);

	putchar('\n');

	//PLのターン
	while (retry == 1) {

		//PLのドロー
		Drew(&player2,deck,&deck_size,&top);

		printMask(player1);
		printScore(player2);

		if ( player2.score > 21) {
			printf("□%-6s is BURST!!\n",player2.name);
			break;
		} else {
			printf("□さらにカードを引きますか？ [Y...1 / N...0]"); fflush(0); scanf("%d", &retry);
			if ( retry == 1 )
				continue;
			else
				break;
		}

	}

	//COMのターン
	while(1) {
		if (player1.score < 16 && player1.count < 8) {
			//COMのドロー
			Drew(&player1,deck,&deck_size,&top);
		} else {
			break;
		}
	}

	animation();

	printScore(player1);
	printScore(player2);

	if (isJudge(player1.score,player2.score) == 1) {
		printf("□%-8s WIN!!! \n",player1.name);
	} else if (isJudge(player1.score,player2.score) == 2) {
		printf("□%-8s WIN!!! \n",player2.name);
	} else {
		printf("□引き分け\n");
	}

	printf("□ゲーム続行しますか？ [Y...1 / N...0]"); fflush(0); scanf("%d", &retry);
	if (retry == 0)
		break;
	}

	puts("■GAME SET.");

	return 0;
}
