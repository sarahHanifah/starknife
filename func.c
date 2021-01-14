#include "header.h"

void emberInit()
{
    ember.posisi_sebelumnya = ember.posisi;
    ember.posisi = 38;
    display();
}

void emberInit_p2()
{
    ember_p2.posisi_sebelumnya = ember_p2.posisi;
    ember_p2.posisi = 101;
    display_p2();
}

// nampilin ember
void display()
{
    // hapus ember di koordinat sebelumnya
    SetCursorPos(ember.posisi_sebelumnya, 27);
    printf("     ");

    // print ember
    SetCursorPos(ember.posisi, 27);
    printf("%s\\___/%s", red, none);
}

// nampilin ember player 2
void display_p2()
{
    // hapus ember di koordinat sebelumnya
    SetCursorPos(ember_p2.posisi_sebelumnya, 27);
    printf("     ");

    // print ember
    SetCursorPos(ember_p2.posisi, 27);
    printf("%s\\___/%s", red, none);
}

// gerak ember
void gerakEmber(int input)
{
    pthread_mutex_lock(&lock);

    if (input == kiri)
    {
        if (ember.posisi > (min_x))
        {
            ember.posisi_sebelumnya = ember.posisi;
            ember.posisi -= 3;
        }
    }
    else if (input == kanan)
    {
        if (ember.posisi < (max_x)-5)
        {
            ember.posisi_sebelumnya = ember.posisi;
            ember.posisi += 3;
        }
    }

    display();
    pthread_mutex_unlock(&lock);
}

// gerak ember
void gerakEmber_p1(int input)
{
    pthread_mutex_lock(&lock);

    if (input == kiri_p1)
    {
        if (ember.posisi > (min_x))
        {
            ember.posisi_sebelumnya = ember.posisi;
            ember.posisi -= 3;
        }
    }
    else if (input == kanan_p1)
    {
        if (ember.posisi < (max_x)-5)
        {
            ember.posisi_sebelumnya = ember.posisi;
            ember.posisi += 3;
        }
    }

    display();
    pthread_mutex_unlock(&lock);
}

// gerak ember_p2
void gerakEmber_p2(int input)
{
    pthread_mutex_lock(&lock);

    if (input == kiri)
    {
        if (ember_p2.posisi > (min_x_p2))
        {
            ember_p2.posisi_sebelumnya = ember_p2.posisi;
            ember_p2.posisi -= 3;
        }
    }
    else if (input == kanan)
    {
        if (ember_p2.posisi < (max_x_p2)-5)
        {
            ember_p2.posisi_sebelumnya = ember_p2.posisi;
            ember_p2.posisi += 3;
        }
    }

    display_p2();
    pthread_mutex_unlock(&lock);
}

void *inputUser(void *vargp)
{
    while (stop == 0)
    {
        int ch = getch();
        if (ch == kiri && ember.alive == 1 && timerCheck == 0) //ember gerak ketika masih punya hidup
        {
            gerakEmber(kiri);
        }
        else if (ch == kanan && ember.alive == 1 && timerCheck == 0) //ember gerak ketika masih punya hidup
        {
            gerakEmber(kanan);
        }
        else if (ch == 'x' || ch == 'X')
        {
            stop = 1;
            system("clear");
        }
        else if (ch == 'h' || ch == 'H')
        {
            home();
        }
        else if (ch == 'y' || ch == 'Y')
        {
            play();
        }
    }

    return NULL;
}

void *inputUser_2p(void *vargp)
{
    while (stop == 0)
    {
        int ch = getch();
        if (ch == kiri_p1 && timerCheck == 0 && ember.alive == 1 && ember_p2.alive == 1) //ember gerak ketika masih punya hidup
        {
            gerakEmber_p1(kiri_p1); // a
        }
        else if (ch == kanan_p1 && timerCheck == 0 && ember.alive == 1 && ember_p2.alive == 1) //ember gerak ketika masih punya hidup
        {
            gerakEmber_p1(kanan_p1); // d
        }
        else if (ch == kiri && timerCheck == 0 && ember.alive == 1 && ember_p2.alive == 1) //ember gerak ketika masih punya hidup
        {
            gerakEmber_p2(kiri); // <-
        }
        else if (ch == kanan && timerCheck == 0 && ember.alive == 1 && ember_p2.alive == 1) //ember gerak ketika masih punya hidup
        {
            gerakEmber_p2(kanan); // ->
        }
        else if (ch == 'x' || ch == 'X')
        {
            stop = 1;
            system("clear");
        }
        else if (ch == 'h' || ch == 'H')
        {
            home();
        }
        else if (ch == 'y' || ch == 'Y')
        {
            play_2p();
        }
    }

    return NULL;
}

void *InWait(void *vargp)
{
    int posisi_timer = 60;
    timerCheck = 0;
    gettimeofday(&begin, NULL);
    int end = begin.tv_sec + 60;
    int temp = 0;
    while (timerCheck == 0 && ember.alive == 1 && stop == 0)
    {
        pthread_mutex_lock(&lock);
        SetCursorPos(posisi_timer, 3);
        gettimeofday(&now, NULL);
        if (temp != end - now.tv_sec)
        {
            if (end - now.tv_sec < 10)
            {
                printf("   ");
                printf("00:0");
            }
            else
            {
                printf("   ");
                printf("00:");
            }
            printf("%ld", end - now.tv_sec);
        }
        temp = end - now.tv_sec;
        if (end - now.tv_sec == 0)
        {
            timerCheck = 1;
        }
        pthread_mutex_unlock(&lock);
    }
    SetCursorPos(posisi_timer, 3);
    printf("   ");

    timerCheck = 1;
    gameOverT();
}

void *InWait_2p(void *vargp)
{
    int posisi_timer = 60;
    int posisi_timer_p2 = 123;
    timerCheck = 0;

    gettimeofday(&begin, NULL);
    int end = begin.tv_sec + 60;
    int temp = 0;

    while (timerCheck == 0 && ember.alive == 1 && ember_p2.alive == 1 && stop == 0)
    {
        pthread_mutex_lock(&lock);
        gettimeofday(&now, NULL);
        //if (temp != end - now.tv_sec)
        //{
        if (end - now.tv_sec < 10)
        {
            SetCursorPos(posisi_timer, 3);
            printf("   ");
            printf("00:0");
            printf("%ld", end - now.tv_sec);
            SetCursorPos(posisi_timer_p2, 3);
            printf("   ");
            printf("00:0");
            printf("%ld", end - now.tv_sec);
        }
        else
        {
            SetCursorPos(posisi_timer, 3);
            printf("   ");
            printf("00:");
            printf("%ld", end - now.tv_sec);
            SetCursorPos(posisi_timer_p2, 3);
            printf("   ");
            printf("00:");
            printf("%ld", end - now.tv_sec);
        }
        // temp = end - now.tv_sec;
        //}
        if (end - now.tv_sec == 0)
        {
            timerCheck = 1;
        }
        pthread_mutex_unlock(&lock);
    }

    //hapus timer
    SetCursorPos(posisi_timer, 3);
    printf("   ");

    SetCursorPos(posisi_timer_p2, 3);
    printf("   ");

    timerCheck = 1;
    gameOverT_2p();
}

void gameOverT()
{
    system("clear");
    border();
    int place = 8;
    timerCheck = 1;
    SetCursorPos(33, place++);

    if (ember.alive == 0)
    {
        printf("Game Over!\n\n");
    }
    else
    {
        printf("Time's Up!\n\n");
    }

    place = 12; //biar ada jarak sama judul
    SetCursorPos(15, place++);
    printf("> Your Score : %d\n", ember.score);

    place = 20; //biar ada jarak juga :)
    SetCursorPos(15, place++);
    printf("Press Y to Play Again\n");
    SetCursorPos(15, place++);
    printf("Press H to Return to Main Menu\n");
    SetCursorPos(15, place++);
    printf("Press X to Exit\n");
    SetCursorPos(0, 30);
}

void gameOverT_2p()
{
    int place = 8;
    timerCheck = 1;
    system("clear");

    // score sama dan dua duanya mati
    // score sama dan dua duanya hidup
    if ((ember.score == ember_p2.score) && (ember.alive == 1 && ember_p2.alive == 1) || (ember.alive == 0 && ember_p2.alive == 0))
    {
        border_2p(magenta, magenta);
        SetCursorPos(38, place);
        printf("DRAW!\n\n");
        SetCursorPos(102, place++);
        printf("DRAW!\n\n");
    }
    // score p2 sama atau lebih besar dari p1 dan p2 tidak boleh mati
    else if (ember_p2.score >= ember.score && !(ember.alive == 1 && ember_p2.alive == 0))
    {
        border_2p(red, green);
        SetCursorPos(36, place);
        printf("YOU LOSE!\n\n");
        SetCursorPos(100, place++);
        printf("YOU WIN!\n\n");
    }
    // score p1 sama atau lebih besar dari p2 dan p1 tidak boleh mati
    else if (ember_p2.score <= ember.score && !(ember.alive == 0 && ember_p2.alive == 1))
    {
        border_2p(green, red);
        SetCursorPos(36, place);
        printf("YOU WIN!\n\n");
        SetCursorPos(100, place++);
        printf("YOU LOSE!\n\n");
    }
    // p2 hidup
    else if (ember.alive == 0 && ember_p2.alive == 1)
    {
        border_2p(red, green);
        SetCursorPos(36, place);
        printf("YOU LOSE!\n\n");
        SetCursorPos(100, place++);
        printf("YOU WIN!\n\n");
    }
    // p1 masih hidup
    else if ((ember.alive == 1 && ember_p2.alive == 0))
    {
        border_2p(green, red);
        SetCursorPos(36, place);
        printf("YOU WIN!\n\n");
        SetCursorPos(100, place++);
        printf("YOU LOSE!\n\n");
    }

    place = 12; //biar ada jarak sama judul
    SetCursorPos(15, place);
    printf("> Your Score : %d\n", ember.score);
    SetCursorPos(79, place++);
    printf("> Your Score : %d\n", ember_p2.score);

    place = 20; //biar ada jarak juga :)
    SetCursorPos(15, place);
    printf("Press Y to Play Again\n");
    SetCursorPos(79, place++);
    printf("Press Y to Play Again\n");
    SetCursorPos(15, place);
    printf("Press H to Return to Main Menu\n");
    SetCursorPos(79, place++);
    printf("Press H to Return to Main Menu\n");
    SetCursorPos(15, place);
    printf("Press X to Exit\n");
    SetCursorPos(79, place++);
    printf("Press X to Exit\n");
    SetCursorPos(0, 30);
}

void border()
{
    system("clear");

    int i, j;

    //Top border line...
    SetCursorPos(10, 6);
    for (j = 0; j <= 60; j++)
        printf("%s\u2550%s", cyan, none);

    //Bottom border line...
    SetCursorPos(10, 29);
    for (j = 0; j <= 60; j++)
        printf("%s\u2550%s", cyan, none);

    SetCursorPos(10, 6);
    printf("%s\u2554%s", cyan, none);
    SetCursorPos(70, 6);
    printf("%s\u2557%s", cyan, none);

    //Left and Right border line...
    for (j = 1; j < 23; j++)
    {
        SetCursorPos(10, 6 + j);
        printf("%s\u2551%s", cyan, none);

        SetCursorPos(70, 6 + j);
        printf("%s\u2551%s", cyan, none);
    }
    SetCursorPos(10, 29);
    printf("%s\u255A%s", cyan, none);
    SetCursorPos(70, 29);
    printf("%s\u255D%s", cyan, none);

    printf("\n");
}

void border_2p(char color_p1[], char color_p2[])
{
    system("clear");

    int i, j;

    //Top border line...
    SetCursorPos(11, 6);
    for (j = 11; j <= 69; j++) //58
        printf("%s\u2550%s", color_p1, none);

    SetCursorPos(74, 6);
    for (j = 74; j <= 132; j++)
        printf("%s\u2550%s", color_p2, none);

    //Bottom border line...
    SetCursorPos(11, 29);
    for (j = 11; j <= 69; j++)
        printf("%s\u2550%s", color_p1, none);

    SetCursorPos(74, 29);
    for (j = 74; j <= 132; j++)
        printf("%s\u2550%s", color_p2, none);

    SetCursorPos(10, 6);
    printf("%s\u2554%s", color_p1, none);
    SetCursorPos(70, 6);
    printf("%s\u2557%s", color_p1, none);
    SetCursorPos(71 + 2, 6);
    printf("%s\u2554%s", color_p2, none);
    SetCursorPos(131 + 2, 6);
    printf("%s\u2557%s", color_p2, none);

    //Left and Right border line...
    for (j = 1; j < 23; j++)
    {
        SetCursorPos(10, 6 + j);
        printf("%s\u2551%s", color_p1, none);

        SetCursorPos(70, 6 + j);
        printf("%s\u2551%s", color_p1, none);

        SetCursorPos(71 + 2, 6 + j);
        printf("%s\u2551%s", color_p2, none);

        SetCursorPos(131 + 2, 6 + j);
        printf("%s\u2551%s", color_p2, none);
    }
    SetCursorPos(10, 29);
    printf("%s\u255A%s", color_p1, none);
    SetCursorPos(70, 29);
    printf("%s\u255D%s", color_p1, none);
    SetCursorPos(71 + 2, 29);
    printf("%s\u255A%s", color_p2, none);
    SetCursorPos(131 + 2, 29);
    printf("%s\u255D%s\n", color_p2, none);

    printf("\n");
}

void play()
{
    ember.posisi = 32; //posisi awal ember
    ember.alive = 1;
    emberInit();
    for (int i = 0; i < jumlah_barang; i++)
    {
        barangInit(i);
    }
    border();
    ember.score = 0;

    printf("          ");
    SetCursorPos(11, 3);
    printf("Score : %d", ember.score);

    SetCursorPos(11, 31);
    printf(">>> Tekan <- atau -> untuk kontrol ember");

    timerCheck = 0;
    stop = 0;
    pthread_t timer;
    pthread_t controlEmber;
    pthread_t drop_barang[jumlah_barang];

    pthread_create(&timer, NULL, InWait, NULL);
    pthread_create(&controlEmber, NULL, inputUser, NULL);

    for (int i = 0; i < jumlah_barang; i++)
    {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&drop_barang[i], NULL, drop, arg);
        wait(3);
    }

    pthread_join(timer, NULL);
    pthread_join(controlEmber, NULL);

    for (int i = 0; i < jumlah_barang; i++)
    {
        pthread_join(drop_barang[i], NULL);
    }

    pthread_exit(NULL);
}

void play_2p()
{
    ember.posisi = 32;     //posisi awal ember
    ember_p2.posisi = 102; //posisi awal ember
    ember.alive = 1;
    ember_p2.alive = 1;

    emberInit();
    emberInit_p2();
    for (int i = 0; i < jumlah_barang; i++)
    {
        barangInit(i);
    }
    border_2p(cyan, cyan);

    ember.score = 0;
    ember_p2.score = 0;

    printf("          ");
    SetCursorPos(11, 3);
    printf("Score : %d", ember.score);

    printf("          ");
    SetCursorPos(74, 3);
    printf("Score : %d", ember_p2.score);

    SetCursorPos(11, 31);
    printf(">>> Tekan a atau d untuk kontrol ember");

    SetCursorPos(74, 31);
    printf(">>> Tekan <- atau -> untuk kontrol ember");

    timerCheck = 0;
    stop = 0;
    pthread_t timer;
    pthread_t controlEmber;
    pthread_t drop_barang[jumlah_barang];

    pthread_create(&timer, NULL, InWait_2p, NULL);
    pthread_create(&controlEmber, NULL, inputUser_2p, NULL);

    for (int i = 0; i < jumlah_barang; i++)
    {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&drop_barang[i], NULL, drop_2p, arg);
        wait(3);
    }

    pthread_join(timer, NULL);
    pthread_join(controlEmber, NULL);

    for (int i = 0; i < jumlah_barang; i++)
    {
        pthread_join(drop_barang[i], NULL);
    }

    pthread_exit(NULL);
}

//barang yg akan berjatuhan
void barangInit(int i)
{
    arrBarang[i].x = randomizer();
    arrBarang[i].y = min_y;

    if (arrBarang[i].x % 2 == 1)
    {
        arrBarang[i].karakter = '*';
        arrBarang[i].damage = 0;
    }
    else
    {
        arrBarang[i].karakter = '!';
        arrBarang[i].damage = -1;
    }
}

void *drop(void *i)
{
    //ambil item yg terkait di array
    int idxBarang = *((int *)i);
    free(i);

    Barang barang;
    barang = arrBarang[idxBarang];
    while (timerCheck == 0 && ember.alive == 1 && stop == 0)
    {
        pthread_mutex_lock(&lock);

        // hapus bintang di koordinat sebelumnya
        SetCursorPos(barang.x, barang.y);
        printf(" ");

        if (barang.y == max_y)
        {
            // jika barang sudah ada dibawah maka inisialisasi kembali agar posisi x di random
            barangInit(idxBarang);
            barang = arrBarang[idxBarang];
        }

        barang.y++;

        // print barang
        SetCursorPos(barang.x, barang.y);
        printf("%s%c%s", yellow, barang.karakter, none);

        //cek barang yg masuk ember
        if ((barang.x >= ember.posisi + 1 && barang.x <= ember.posisi + 3) && (barang.y == (max_y)))
        {
            if (barang.damage == 0)
            {
                ember.score++;
                // update score
                SetCursorPos(11, 3);
                printf("          ");
                SetCursorPos(11, 3);
                printf("Score : %d", ember.score);
            }
            else
            {
                system("clear");
                ember.alive = 0;
                gameOverT();
            }
        }
        pthread_mutex_unlock(&lock);
        wait(0.5);
    }
    // hapus bintang
    SetCursorPos(barang.x, barang.y);
    printf(" ");
}

void *drop_2p(void *i)
{
    //ambil item yg terkait di array
    int idxBarang = *((int *)i);
    free(i);

    Barang barang;

    barang = arrBarang[idxBarang];

    while (timerCheck == 0 && ember.alive == 1 && ember_p2.alive == 1 && stop == 0)
    {
        pthread_mutex_lock(&lock);

        // hapus bintang di koordinat sebelumnya
        SetCursorPos(barang.x, barang.y);
        printf(" ");
        SetCursorPos(barang.x + 63, barang.y); //untuk player 2
        printf(" ");

        if (barang.y == max_y)
        {
            // jika barang sudah ada dibawah maka inisialisasi kembali agar posisi x di random
            barangInit(idxBarang);
            barang = arrBarang[idxBarang];
        }

        barang.y++;

        // print barang
        SetCursorPos(barang.x, barang.y);
        printf("%s%c%s", yellow, barang.karakter, none);
        // print barang
        SetCursorPos(barang.x + 63, barang.y); //untuk player 2
        printf("%s%c%s", yellow, barang.karakter, none);

        //cek barang yg masuk ember player 1
        if ((barang.x >= ember.posisi + 1 && barang.x <= ember.posisi + 3) && (barang.y == (max_y)))
        {
            if (barang.damage == 0)
            {
                ember.score++;
                // update score
                SetCursorPos(11, 3);
                printf("           ");
                SetCursorPos(11, 3);
                printf("Score : %d", ember.score);
            }
            else
            {
                system("clear");
                ember.alive = 0;
                gameOverT_2p();
            }
        }

        //cek barang yg masuk ember player 2
        if (((barang.x + 63) >= ember_p2.posisi + 1 && (barang.x + 63) <= ember_p2.posisi + 3) && (barang.y == (max_y_p2)))
        {
            if (barang.damage == 0)
            {
                ember_p2.score++;
                // update score
                SetCursorPos(72, 3);
                printf("           ");
                SetCursorPos(72, 3);
                printf("Score : %d", ember_p2.score);
            }
            else
            {
                system("clear");
                ember_p2.alive = 0;
                gameOverT_2p();
            }
        }
        pthread_mutex_unlock(&lock);
        wait(0.5);
    }
    // hapus bintang
    SetCursorPos(barang.x, barang.y);
    printf(" ");
    SetCursorPos(barang.x + 63, barang.y); //untuk player 2
    printf(" ");
}

int randomizer()
{
    int r = (rand() % 55) + min_x;
    return r;
}

void home()
{
    border();

    int place = 7;
    SetCursorPos(32, place++);
    printf("Drop and Catch\n\n");

    place = 12; //biar ada jarak sama judul
    SetCursorPos(15, place++);
    printf("> Play\n");
    SetCursorPos(15, place++);
    printf("> Exit\n");

    place = 20; //biar ada jarak juga :)
    SetCursorPos(15, place++);
    printf("Press P for Play\n");
    SetCursorPos(15, place++);
    printf("Press X to Exit\n");
    SetCursorPos(15, place++);

    int ch;

    int cek = 0;
    while (cek == 0)
    {
        if (place > 28)
        {
            border();
            place = 7;
        }

        ch = getch();

        if ((ch == 'p') || (ch == 'P'))
        {
            system("clear");
            border();
            int place = 12;
            SetCursorPos(15, place++);
            printf("> 1 Player\n");
            SetCursorPos(15, place++);
            printf("> 2 Player\n");

            place = 20;
            SetCursorPos(15, place++);
            printf("Press 1 for 1 Player\n");
            SetCursorPos(15, place++);
            printf("Press 2 for 2 Player\n");
            SetCursorPos(0, 30);

            int ch = getch();
            if (ch == '1')
            {
                play();
            }
            else if (ch == '2')
            {
                play_2p();
            }
        }
        else if ((ch == 'x') || (ch == 'X'))
        {
            system("clear");
            exit(0);
        }
    }
}

void initTermios(int echo)
{
    tcgetattr(0, &old);                 //grab old terminal i/o settings
    new = old;                          //make new settings same as old settings
    new.c_lflag &= ~ICANON;             //disable buffered i/o
    new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
    tcsetattr(0, TCSANOW, &new);        //apply terminal io settings
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

char getch(void)
{
    return getch_(0);
}

/* 
Read 1 character with echo 
getche() function definition.
*/
char getche(void)
{
    return getch_(1);
}

void wait(double seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait)
    {
    }
}

void SetCursorPos(int XPos, int YPos)
{
    printf("\033[%d;%dH", YPos + 1, XPos + 1);
    printf("\e[?25l");
}
