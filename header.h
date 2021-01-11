#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define red "\033[0;31m"
#define cyan "\033[1;36m"  /* 1 -> bold ;  36 -> cyan */
#define green "\033[0;32m" /* 4 -> underline ;  32 -> green */
#define yellow "\033[0;33m"
#define magenta "\033[0;35m"
#define none "\033[0m"

// border player 1
#define min_x 13
#define max_x 69
#define min_y 7
#define max_y 27

// border player 2
#define min_x_p2 74
#define max_x_p2 132
#define min_y_p2 7
#define max_y_p2 27

// control player 1
#define kiri 68
#define kanan 67

// control player 2
#define kiri_p1 'a'
#define kanan_p1 'd'

// BARANG
typedef struct
{
	// koordinat
	int x;
	int y;
	char karakter; // menampung karakter * atau !
	int damage;
	/*
	damage == 0 artinya *
	damage == -1 artinya !
	*/
} Barang;

#define jumlah_barang 4
Barang arrBarang[jumlah_barang];
Barang arrBarang_p2[jumlah_barang];

// EMBER
typedef struct
{
	int posisi_sebelumnya;
	int posisi;
	int score;
	int alive; // alive == 0 menandakan ember menerima !, berarti game berhenti
} Ember;

Ember ember;
Ember ember_p2;

int stop;		// stop == 1 menandakan user memasukan X atau x, yg artinya stop, maka semua berhenti
int timerCheck; // timerCheck == 1 menandakan waktu sudah habis

static struct termios old, new;
pthread_mutex_t lock;

void initTermios(int echo);
void resetTermios(void);
char getch_(int echo);
char getch(void);
char getche(void);

void SetCursorPos();

void border();
void border_2p(char color_p1[], char color_p2[]);

void play();
void play_2p();

struct timeval begin, now; // begin = waktu mulai, now   = waktu sekarang

void wait(double seconds);

void *InWait(void *vargp);
void *InWait_2p(void *vargp);

void gerakEmber(int input);
void gerakEmber_p1(int input);
void gerakEmber_p2(int input);

void *drop(void *vargp);
void *drop_2p(void *vargp);

void display();
void display_p2();

void gameOverT();
void gameOverT_2p();

void barangInit();

void emberInit();
void emberInit_p2();

void srand(unsigned int seed);

void *inputUser(void *vargp);
void *inputUser_2p(void *vargp);

int randomizer();

void home();