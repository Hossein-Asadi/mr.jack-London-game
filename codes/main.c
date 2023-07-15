#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <MMsystem.h>
#include "func1.h"

#define R     "\x1b[31m" //RED
#define G   "\x1b[32m"   //GREEN
#define Y  "\x1b[33m"   //YELLOW
#define B    "\x1b[34m" //BLUE
#define M "\x1b[35m"   //MAGENTA
#define C   "\x1b[36m" //CYAN
#define R1   "\x1b[0m" //RESET

int win_check=0;
int mode=0;


char game_char[8][5]={"IL","MS","JB","JW","WG","SG","JS","SH"};
int b[8]={0};
int show =1;
char mrjack[5];



void move (struct node1 place[9][13],char *s,int *i,int *j);
void move1 (struct node1 place[9][13],char *s,int *i,int *j);
int move_place(struct node1 place[9][13],char *s,int i1,int j1,int sit);
void set_light(struct node1 place[9][13],int i3,int j3,int i4 , int j4);
void light_jw(struct node1 place[9][13],int i1,int j1,int mode );
void move_tunnel (struct node1 place[9][13],char *s,int *i,int *j);
int nearlight(struct node1 place[9][13],int i,int j);
int move_sg(struct node1 place[9][13],int i1,int j1,int i2,int j2);
void show_criminal (struct node1 place[9][13],char *mrjack);
int check_tunnel (struct node1 place[9][13],int i,int j);
void recorrect (struct node1 place[9][13]);
int check_near(struct node1 place[9][13],int i,int j,char *s);
void set_light(struct node1 place[9][13],int i3,int j3,int i4 , int j4);


int main(){
    PlaySound(TEXT("start.wav"),NULL,SND_ASYNC);
    struct node1 place[9][13];
    FILE *fp1,*fp2;
    int i,j,x,sit;
    char c;
    fp1=fopen("object.txt","r");
    fp2=fopen("situation.txt","r");
    if(fp1 == NULL){
	printf(C "Cannot open file\n" R1);
	return -1;
   }
   if(fp2 == NULL){
	printf(C "Cannot open file\n" R1);
	return -1;
   }


     for(i=0;i<9;i++)
     for(j=0;j<13;j++){
      c= fgetc(fp2);
      fscanf(fp1,"%d",&x);
      strcpy(place[i][j].character,"  ");
      place[i][j].situation=c;
      place[i][j].object=x;
      place[i][j].criminal= ' ';
     }
     strcpy(place[0][4].character,"WG");
     strcpy(place[2][6].character,"JS");
     strcpy(place[3][8].character,"JB");
     strcpy(place[3][12].character,"SG");
     strcpy(place[4][0].character,"JW");
     strcpy(place[4][4].character,"IL");
     strcpy(place[5][6].character,"SH");
     strcpy(place[7][8].character,"MS");
     place[0][4].criminal= 'c';
     place[2][6].criminal= 'c';
     place[3][8].criminal= 'c';
     place[3][12].criminal= 'c';
     place[4][0].criminal= 'c';
     place[4][4].criminal= 'c';
     place[5][6].criminal= 'c';
     place[7][8].criminal= 'c';
     random(b);
     step_one();
     step_two();
     step_three();
     strcpy(mrjack,game_char[b[0]-1]);
     printf("your character is" R " %s\n" R1,game_char[b[0]-1]);
     printf(B "\npress any key to continue...\n" R1);
     getchar();
     system("cls");
    fclose(fp1);
    fclose(fp2);
    //board(place);
  int rnd;
  for(rnd =1;rnd<=8;){

    int a[8]={0};
    random(a);
    struct node *head,*new_node,*head1,*head2;
    char str[50];
    strcpy(str,game_char[a[0]-1]);
    head = create_node(str);

    for(i=1;i<8;i++){
        strcpy(str,game_char[a[i]-1]);
        new_node = create_node(str);
        add_list(head,new_node);
    }
    strcpy(str , head -> card_name);
    head1 = create_node(str);
    strcpy(str , head -> next -> card_name);
    head2 = create_node(str);
    divide(head,head1,head2);
     int i1,j1;
     char s[5];
 if(rnd %2 ==1){
        PlaySound(TEXT("soundclock.wav"),NULL,SND_SYNC);
        system("cls");
        board(place);
        printf(G "\nRound %d\n" R1,rnd);
  int chs;
  int tedad=0;
  PlaySound(TEXT("shuffle.wav"),NULL,SND_SYNC);
  PlaySound(TEXT("cards.wav"),NULL,SND_SYNC);
   printf(B "Detective\n" R1 G "choose just one card\n" R1);
        while(1){
        print_list(head1);
         scanf("%d",&chs);
       if(chs>4 || chs<1){
        printf(C "invalid number!try again\n" R1);
        continue;}
        else{
        while(1){
               find_node(head1,s,chs);
               introduction(s);
               board(place);
        printf(G "please enter current place:\n" R1);
        scanf("%d%d",&i1,&j1);
         int chk=check_place(place,s,i1,j1);
         if(chk==1){
         sit = move_place(place,s,i1,j1,1);
         if(sit == 1)
            return 1;
         recorrect(place);
         board(place);
         break;
         }
            else
            {
                printf(C "invalid number!try again\n" R1);
                continue;
            }
        }
        }
       if(chs==1)
        delete_front(&head1);
       else
       delete_next(&head1,chs-1);
       break;}
    if(win_check!=0){
        printf(R "\n*****************MR.JACK WIN*******************\n" R1);
        return 1;
    }
   printf(R "MR.jack\n" R1 G"choose 2 cards\n" R1);
   while(tedad<2){
    print_list(head1);
    if(tedad == 0)
        printf(G "choose first card\n" R1);
    if(tedad == 1)
        printf(G "choose second card\n" R1);
     scanf("%d",&chs);
       if(chs>(3-tedad) || chs<1)
        printf(C "invalid number!try again\n" R1);
        else{
        while(1){
               find_node(head1,s,chs);
               introduction(s);
               board(place);
        printf(G "please enter current place:\n" R1);
        scanf("%d%d",&i1,&j1);
         int chk=check_place(place,s,i1,j1);
         if(chk==1){
         system("cls");
         sit = move_place(place,s,i1,j1,0);
         if(sit == 1)
            return 1;
           recorrect(place);
         board(place);
         break;
         }
            else
            {
                printf(C "invalid number!try again\n" R1);
                continue;
            }
        }
       if(chs==1)
        delete_front(&head1);
       else
       delete_next(&head1,chs-1);
        tedad++;
        }
   }
   if(win_check!=0){
        printf(R "\n*****************MR.JACK WIN*******************\n" R1);
        return 1;
    }
  printf(B "Detective\n" R1 G"choose the last card\n");
    while(1){
    print_list(head1);
     scanf("%d",&chs);
       if(chs>(3-tedad) || chs<1)
        printf(C "invalid number!try again\n" R1);
        else{
        while(1){
               find_node(head1,s,chs);
               introduction(s);
               board(place);
        printf(G "please enter current place:\n"  R1);
        scanf("%d%d",&i1,&j1);
         int chk=check_place(place,s,i1,j1);
         if(chk==1){
        sit = move_place(place,s,i1,j1,1);
        if(sit == 1)
            return 1;
         recorrect(place);
         board(place);
         break;
         }
            else
            {
                printf(C "invalid number!try again\n" R1);
                continue;
            }
        }
        break;
        }
    }
     if(win_check!=0){
        printf(R "\n*****************MR.JACK WIN*******************\n" R1);
        return 1;
    }
    show_criminal(place,mrjack);
   printf(G "\nEnd of Round %d\n" R1,rnd);
   system("cls");
   }

   if(rnd==1 || rnd==3)
    light_off_rnd(place);

   rnd++;
   if(rnd %2 ==0){
    PlaySound(TEXT("soundclock.wav"),NULL,SND_SYNC);
    board(place);
  printf(G "\nRound %d\n" R1,rnd);
  PlaySound(TEXT("cards.wav"),NULL,SND_SYNC);
  int chs;
  int tedad=0;
   printf(R "MR.jack\n" R1 G "choose just one card\n" R1);
        while(1){
        print_list(head2);
         scanf("%d",&chs);
       if(chs>4 || chs<1){
        printf(C "invalid number!try again\n" R1);
        continue;}
        else{
        while(1){
               find_node(head2,s,chs);
               introduction(s);
               board(place);
        printf(G "please enter current place:\n" R1);
        scanf("%d%d",&i1,&j1);
         int chk=check_place(place,s,i1,j1);
         if(chk==1){
         sit = move_place(place,s,i1,j1,0);
         if(sit == 1)
            return 1;
           recorrect(place);
         board(place);
         break;
         }
            else
            {
                printf(C "invalid number!try again\n" R1);
                continue;
            }
        }
        }
       if(chs==1)
        delete_front(&head2);
       else
       delete_next(&head2,chs-1);
       break;}
    if(win_check!=0){
        printf(R "\n*****************MR.JACK WIN*******************\n" R1);
        return 1;
    }
   printf(B "Detective\n" R1 G"choose 2 cards\n" R1);
   while(tedad<2){
    print_list(head2);
    if(tedad == 0)
        printf(G "choose first card\n" R1);
    if(tedad == 1)
        printf(G "choose second card\n"R1);
     scanf("%d",&chs);
       if(chs>(3-tedad) || chs<1)
        printf(C "invalid number!try again\n" R1);
        else{
        while(1){
               find_node(head2,s,chs);
               introduction(s);
               board(place);
        printf(G "please enter current place:\n" R1);
        scanf("%d%d",&i1,&j1);
         int chk=check_place(place,s,i1,j1);
         if(chk==1){
         sit = move_place(place,s,i1,j1,1);
         if(sit == 1)
            return 1;
           recorrect(place);
         board(place);
         break;
         }
            else
            {
                printf(C "invalid number!try again\n" R1);
                continue;
            }
        }
       if(chs==1)
        delete_front(&head2);
       else
       delete_next(&head2,chs-1);
        tedad++;
        }
   }
   if(win_check!=0){
        printf(R "\n*****************MR.JACK WIN*******************\n" R1);
        return 1;
    }
  printf(R "MR.jack\n" R1 G "choose the last card\n"R1);
    while(1){
    print_list(head2);
     scanf("%d",&chs);
       if(chs>(3-tedad) || chs<1)
        printf(C "invalid number!try again\n" R1);
        else{
        while(1){
               find_node(head2,s,chs);
               introduction(s);
               board(place);
        printf(G "please enter current place:\n" R1);
        scanf("%d%d",&i1,&j1);
         int chk=check_place(place,s,i1,j1);
         if(chk==1){
         sit = move_place(place,s,i1,j1,0);
         if(sit == 1)
            return 1;
        recorrect(place);
         board(place);
         break;
         }
            else
            {
                printf(C "invalid number!try again\n" R1);
                continue;
            }
        }
        break;
        }
    }
    if(win_check!=0){
        printf(R "*****************MR.JACK WIN*******************\n" R1);
        return 1;
    }
   show_criminal(place,mrjack);
   printf(G "\nEnd of Round %d\n" R1,rnd);
   system("cls");
   }
   if((rnd==4) || (rnd==2))
    light_off_rnd(place);
   rnd++;

  }
  if(win_check == 0){
        printf(R "*****************MR.JACK WIN*******************\n" R1);
        return 1;
    }
    return 0;
}

int move_place(struct node1 place[9][13],char *s,int i1,int j1,int sit){
    if(strcmp (s,"SH")==0){
         int move_num=0,total_move;
        while(1){
        board(place);
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>3 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     system("cls");
     while(move_num < total_move){
            board(place);
            printf(G "step %d\n" R1,move_num+1);
             if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf(G "do you want to arrest somebody?\n" R1 C "1-yes    " R1 R  "  2-no\n" R1);
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf(G "please enter the name of character that you want to arrest him/her\n" R1);
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                if(n==2)
                    move(place,s,&i1,&j1);
            }
                else
                    move(place,s,&i1,&j1);
             if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            move_num++;
     }
     printf(G "After move\n" R1);
     printf("press any key to pick a card...\n");
     getchar();
     getchar();
     printf("picked card is = " B " %s\n" R1,game_char[b[show]-1]);
     printf(G "press any key to continue...\n" R1);
     getchar();
     show++;
    }
     if(strcmp (s,"JW")==0){
        light_jw_off(place);
          int move_num=0,total_move;
          system("cls");
          board(place);
        while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>3 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     system("cls");
     while(move_num < total_move){
            board(place);
            printf(G "step %d\n" R1,move_num+1);

            if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n*******************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n********************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
             if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                if(n==2)
                    move(place,s,&i1,&j1);
             }
                else
                    move(place,s,&i1,&j1);
             if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                 board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "***********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            move_num++;
     }
     printf(G "After move\n");
     board(place);
     printf("specify the direction of the light\n1 - North      2 - North_East        3 - South_East\n4 - South     5 - South_West      6-North_West\n");
     scanf("%d",&mode);
     light_jw(place,i1,j1,mode);
     system("cls");
     }
     if(strcmp (s,"JS")==0){
            int move_num=0,total_move;
        system("cls");
     printf("do you want to move or use your special action?\n1 - move\n2 - special action\n");
     int n;
     scanf("%d",&n);
     if(n==1){
        printf(G "move part\n" R1);
        board(place);
        while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>3 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     system("cls");
     while(move_num < total_move){
            board(place);
            printf(G "step %d\n" R1,move_num+1);

            if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n**************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n******************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
             if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                if(n==2)
                    move(place,s,&i1,&j1);
             }
                else
                    move(place,s,&i1,&j1);
                     if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                     board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            move_num++;
     }
     system("cls");
     board(place);
     printf(G "After move\n" R1);
     int i3,j3,i4,j4;
     while(1){
            board(place);
     printf(G "please enter the location of light_off and new location to place location of light on(4 values)\n" R1);
     scanf("%d%d%d%d",&i3,&j3,&i4,&j4);
     int z =check_lamplight(place,i3,j3,i4,j4);
     if(z==1){
        place[i3][j3].object = 4;
        place[i4][j4].object = 5;
        set_light(place,i3,j3,i4,j4);
        break;
     }
     else
     {
         printf(C "invalid value!try again\n" R1);
         continue;
     }
     }
     }
     if(n==2){
            system("cls");
         printf(G "special action\n" R1);
     int i3,j3,i4,j4;
     while(1){
         board(place);
     printf(G "please enter the location of light_off and new location to place location of light on(4 values)\n" R1);
     scanf("%d%d%d%d",&i3,&j3,&i4,&j4);
     int z =check_lamplight(place,i3,j3,i4,j4);
     if(z==1){
        place[i3][j3].object = 4;
        place[i4][j4].object = 5;
        set_light(place,i3,j3,i4,j4);
        break;
     }
     else
     {
         printf(C "invalid value!try again\n" R1);
         continue;
     }
     }
     system("cls");
     board(place);
      printf(G "move part\n" R1);
        while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>3 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     system("cls");
     while(move_num < total_move){
           board(place);
            printf(G "step %d\n" R1,move_num+1);

            if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n*******************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n*******************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
             if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                  if(n==2)
                    move(place,s,&i1,&j1);
             }
                else
                    move(place,s,&i1,&j1);
                 if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                 board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            move_num++;
     }
     }
    }
     if(strcmp (s,"IL")==0){
       int move_num=0,total_move;
       system("cls");
       board(place);
        while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>3 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     system("cls");
     while(move_num < total_move){
            board(place);
            printf("step %d\n",move_num+1);

            if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n********************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n**********************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                if(n==2)
                    move(place,s,&i1,&j1);
            }
                else
                    move(place,s,&i1,&j1);
             if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                 board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }

            system("cls");
            move_num++;
     }
     printf(G "After move\n" R1);
     board(place);
     int i3,j3,i4,j4;
     while(1){
     printf(G "please enter the location of blocker and new location to place location of blocker(4 values)\n" R1);
     scanf("%d%d%d%d",&i3,&j3,&i4,&j4);
     int z =check_blocker(place,i3,j3,i4,j4);
     if(z==1){
        place[i3][j3].object = 6;
        place[i4][j4].object = 7;
        system("cls");
        break;
     }
     else
     {
         printf(C "invalid value!try again\n" R1);
         continue;
     }
     }
   }
     if(strcmp (s,"MS")==0){
      int move_num=0,total_move;
      system("cls");
      board(place);
        while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>4 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     system("cls");
     while(move_num < total_move-1){
            board(place);
            printf(G "step %d\n" R1,move_num+1);

            if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n*********************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n********************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                if(n==2)
                    move1(place,s,&i1,&j1);
            }
                else
                    move1(place,s,&i1,&j1);
             if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                 board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            move_num++;
     }
       if(move_num == total_move-1){
             board(place);
          printf(G "step %d\n" R1,move_num+1);
          if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n*********************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n************************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                if(n==2)
                    move(place,s,&i1,&j1);
            }
                else
          move(place,s,&i1,&j1);
           if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                 board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
       }
     }
     if(strcmp(s,"SG")==0){
        int move_num=0,total_move,n=0,k=0;
        system("cls");
        board(place);
        while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>3 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
      while(move_num < total_move){
            board(place);
            if(k==0){
        printf("do you want to whistle?\n1- Yes   2-No\n");
       scanf("%d",&n);}
       if(k==1)
        n=2;
       if(n==2){
            printf("step %d\n",move_num+1);
            if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n**********************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n*********************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R);
                    continue;
                }
                }
            }
            }
             if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                  if(n==2)
                    move(place,s,&i1,&j1);
             }
                else
                    move(place,s,&i1,&j1);
             if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                 board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            move_num++;
       }
       if(n==1 && k==0){
            k++;
        whistle(place,i1,j1);
       }
     }
     if(k==0){
        printf(G "whistle time:\n" R1);
         whistle(place,i1,j1);
     }
     }
     if(strcmp (s,"WG")==0){
            int n;
            system("cls");
            board(place);
     printf("Do you want to have 1 to 3 moves or Change your location with another Character ?\n1- Move 1 to 3 houses \n2- Change your location with another Character\n");
     scanf("%d",&n);
     system("cls");
     if(n==1){
        int move_num=0,total_move;
        board(place);
        while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>3 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     while(move_num < total_move){
            board(place);
            printf(G "step %d\n" R1,move_num+1);

            if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n******************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n****************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
             if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                  if(n==2)
                    move(place,s,&i1,&j1);
             }
                else
                    move(place,s,&i1,&j1);
             if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                 board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            move_num++;
     }
     }
     if(n==2){
            int i2,j2;
            char s[5];
        while(1){
                board(place);
        printf(G "please enter the location details(2 values)\n" R1);
        scanf("%d%d",&i2,&j2);
        printf(G "please enter the name of character(just name with capital words)\n" R1);
        scanf("%s",s);
            int z=check_place(place,s,i2,j2);
        if(z==1 && strcmp(s,"JW")==0){
           light_jw_off(place);
            char s1[5];
              strcpy(s1,place[i2][j2].character);
              strcpy(place[i2][j2].character,place[i1][j1].character);
              strcpy(place[i1][j1].character,s1);
              light_jw(place,i1,j1,mode);
              break;
        }
        else if(z==1){
         char s1[5];
              strcpy(s1,place[i2][j2].character);
              strcpy(place[i2][j2].character,place[i1][j1].character);
              strcpy(place[i1][j1].character,s1);
              system("cls");
              break;
         }
            else
            {
                printf(C "invalid number!try again\n" R1);
                continue;
            }

        }
      }
     }
     if(strcmp (s,"JB")==0){
        int move_num=0,total_move;
       system("cls");
        printf("do you want to move or use your special action?\n1 - move\n2 - special action\n");
        int n;
        scanf("%d",&n);
        if(n==1){
        system("cls");
        board(place);
        while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>3 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     system("cls");
     while(move_num < total_move){
            board(place);
            printf(G "step %d\n" R1,move_num+1);

            if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***********************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n********************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                  if(n==2)
                    move(place,s,&i1,&j1);
            }
                else
                    move(place,s,&i1,&j1);
             if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                 board(place);
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            move_num++;
     }
     system("cls");
     board(place);
     printf("After move\n");
     int i3,j3,i4,j4;
     while(1){
     printf(G "please enter the location of well banner and new location to place location of well banner\n" R1);
     scanf("%d%d%d%d",&i3,&j3,&i4,&j4);
     int z =check_well_banner(place,i3,j3,i4,j4);
     if(z==1){
        place[i3][j3].object = 2;
        place[i4][j4].object = 3;
        system("cls");
        break;
     }
     else
     {
         printf(C "invalid value!try again\n" R1);
         continue;
     }
     }
     }
     if(n==2){
     system("cls");
     board(place);
         printf(G "special action\n" R1);
     int i3,j3,i4,j4;
     while(1){
     printf(G "please enter the location of well banner and new location to place location of well banner\n" R1);
     scanf("%d%d%d%d",&i3,&j3,&i4,&j4);
     int z =check_well_banner(place,i3,j3,i4,j4);
     if(z==1){
        place[i3][j3].object = 2;
        place[i4][j4].object = 3;
        break;
     }
     else
     {
         printf(C "invalid value!try again\n" R1);
         continue;
     }
     }
     system("cls");
     board(place);
     printf(G "After special action\n" R1);
     while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_move);
        if(total_move>3 || total_move<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     while(move_num < total_move){
            board(place);
            printf("step %d\n",move_num+1);

            if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n****************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n****************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
           if(place[i1][j1].object== 2){
                printf("do you want to use tunnel ?\n1- yes\n2 - no\n");
                int n;
                scanf("%d",&n);
                if(n== 1)
                    move_tunnel(place,s,&i1,&j1);
                  if(n==2)
                    move(place,s,&i1,&j1);
           }
                else
                    move(place,s,&i1,&j1);
             if((sit == 1) && (move_num < total_move) && (nearlight(place,i1,j1)==1)){
                printf("do you want to arrest somebody?\n1-yes     2-no\n");
                int n;
                scanf("%d",&n);
                if(n==1){
                        while(1){
                    printf("please enter the name of character that you want to arrest him/her\n");
                    char s[5];
                    scanf("%s",s);
                if(check_near(place,i1,j1,s)==1){
                    if(strcmp(s,mrjack)==0){
                        printf(B "*********Correct choose***********\n\n***************Detective wins******************\n" R1);
                        return 1;
                    }
                    else{
                        printf(R "*********Wrong choose***********\n\n***************MR.jack wins******************\n" R1);
                        return 1;
                    }
                }
                else {
                    printf(C "invalid name!try again\n" R1);
                    continue;
                }
                }
            }
            }
            move_num++;
     }
     }
    }
    return 0;
}
void move (struct node1 place[9][13],char *s,int *i,int *j){
    int i1 =*i;
    int j1 = *j;
    int i2,j2;
        while(1){
        printf(G "please enter the number of row and column of place:\n" R1);
            scanf("%d%d",&i2,&j2);
            if(i1==i2 && j1==j2){
                printf(C "invalid value!try again\n" R1);
                continue;
            }
           else if((i2<0 && i2>8) || (j2<0 && j2>12) ){
                 printf(C "invalid value!try again\n" R1);
                continue;
            }
           else if(place[i2][j2].object==1 || place[i2][j2].object==4 || place[i2][j2].object==5 || place[i2][j2].object==7 || place[i2][j2].object==8 || place[i2][j2].object==9){
                printf(C "invalid value!try again\n" R1);
                continue;
            }
            else if(place[i2][j2].object == 0 || place[i2][j2].object == 3 || place[i2][j2].object == 2){
                if(j1%2==0){
                int x = i2-i1;
                int y = j2-j1;

                if((x==-1 && y==0) || (x==0 && y==1 )|| (x==1  && y==1) || (x==1  && y==0 ) || (x==1  && y==-1) || (x==0 && y==-1)){
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     *i =i2;
                     *j =j2;
                     printf(M "successfully step\n" R1);
                     system("cls");
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     break;
                }
                else{
                    printf(C "invalid move!please try again\n" R1);
                    continue;
                }
                }
               else if(j1%2==1){
                int x = i2-i1;
                int y = j2-j1;

                if((x==-1 && y==0) || (x==-1 && y==1 )|| (x==0  && y==1) || (x==1  && y==0 ) || (x==0  && y==-1) || (x==-1 && y==-1)){
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     *i =i2;
                     *j =j2;
                     printf(M "successfully step\n" R1);
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     system("cls");
                     break;
                }
                else{
                    printf(C "invalid move!please try again\n" R1);
                    continue;
                }
               }
                else
                {
                    printf(C "invalid value!try again\n" R1);
                continue;
                }
            }
          else  if(place[i2][j2].object == 6){
                if(j1%2==0){
                int x = i2-i1;
                int y = j2-j1;

                if((x==-1 && y==0) || (x==0 && y==1 )|| (x==1  && y==1) || (x==1  && y==0 ) || (x==1  && y==-1) || (x==0 && y==-1)){
                    int check;
                 printf("Are you Mr.jack?\t1- yes 2- no\n");
                 scanf("%d",&check);
                if(check == 1 && strcmp(place[i1][j1].character,mrjack)==0){
                  win_check++;
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     *i =i2;
                     *j =j2;
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     break;
                }
                else {
                printf("you are detective or you want to exit wrong character!try again\n");
                continue;
              }
                }
                else {
                printf("you are detective or you want to exit wrong character!try again\n");
                continue;
              }
                }
               else if(j1%2==1){
                int x = i2-i1;
                int y = j2-j1;

                if((x==-1 && y==0) || (x==-1 && y==1 )|| (x==0  && y==1) || (x==1  && y==0 ) || (x==0  && y==-1) || (x==-1 && y==-1)){
                    int check;
              printf("Are you Mr.jack?\t1- yes 2- no\n");
               scanf("%d",&check);
              if(check == 1 && strcmp(place[i1][j1].character,mrjack)==0){
              win_check++;
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     *i =i2;
                     *j =j2;
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     break;
                }
              else {
                printf("you are detective or you want to exit wrong character!try again\n");
                continue;
              }
               }
            else
            {
                printf(C "invalid value!try again\n" R1);
                continue;
            }
               }
                }
                else
                {
                    printf(C "invalid value!try again\n" R1);
                continue;
                }


        }
}
void move1 (struct node1 place[9][13],char *s,int *i,int *j){
    int i1 =*i;
    int j1 = *j;
    int i2,j2;
        while(1){
        printf(G "please enter the number of row and column of place:\n" R1);
            scanf("%d%d",&i2,&j2);
            if(i1==i2 && j1==j2){
                printf(C "invalid value!try again\n" R1);
                continue;
            }
            else if((i2<0 && i2>8) || (j2<0 && j2>12) ){
                 printf(C "invalid value!try again\n" R1);
                continue;
            }
           else if(  place[i2][j2].object==8 || place[i2][j2].object==9){
                printf(C "invalid value!try again\n" R1);
                continue;
            }
           else if(place[i2][j2].object==7 || place[i2][j2].object == 0 ||  place[i2][j2].object == 2 || place[i2][j2].object == 3 || place[i2][j2].object==1  ||  place[i2][j2].object==4 || place[i2][j2].object==5){
               if(j1%2==0){
                int x = i2-i1;
                int y = j2-j1;

            if((x==-1 && y==0) || (x==0 && y==1 )|| (x==1  && y==1) || (x==1  && y==0 ) || (x==1  && y==-1) || (x==0 && y==-1)){
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     *i =i2;
                     *j =j2;
                     system("cls");
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     break;
                }
                else{
                    printf(C "invalid move!please try again\n" R1);
                    continue;
                }
                }
               else if(j1%2==1){
                int x = i2-i1;
                int y = j2-j1;
                if((x==-1 && y==0) || (x==-1 && y==1 )|| (x==0  && y==1) || (x==1  && y==0 ) || (x==0  && y==-1) || (x==-1 && y==-1)){
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     *i =i2;
                     *j =j2;
                     system("cls");
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     break;
                }
                else{
                    printf(C "invalid move!please try again\n" R1);
                    continue;
                }
               }
                else
                {
                    printf(C "invalid value!try again\n" R1);
                continue;
                }
            }
            else if(place[i2][j2].object == 6){
                if(j1%2==0){
                int x = i2-i1;
                int y = j2-j1;

                if((x==-1 && y==0) || (x==0 && y==1 )|| (x==1  && y==1) || (x==1  && y==0 ) || (x==1  && y==-1) || (x==0 && y==-1)){
                    int check;
                 printf("Are you Mr.jack?\t1- yes 2- no\n");
                 scanf("%d",&check);
                if(check == 1  &&  strcmp(place[i1][j1].character,mrjack)==0){
                  win_check++;
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     *i =i2;
                     *j =j2;
                     system("cls");
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     break;
                }
                else {
                printf("you are detective or you want to exit wrong character!try again\n");
                continue;
              }
                }
                else{
                    printf(C "invalid move!please try again\n" R1);
                    continue;
                }
                }
               else if(j1%2==1){
                int x = i2-i1;
                int y = j2-j1;

            if((x==-1 && y==0) || (x==-1 && y==1 )|| (x==0  && y==1) || (x==1  && y==0 ) || (x==0  && y==-1) || (x==-1 && y==-1)){
                    int check;
              printf("Are you Mr.jack?\t1- yes 2- no\n");
               scanf("%d",&check);
              if(check == 1  &&  strcmp(place[i1][j1].character,mrjack)==0){
              win_check++;
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     *i =i2;
                     *j =j2;
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     system("cls");
                     break;
                }
                else {
                printf("you are detective or you want to exit wrong character!try again\n");
                continue;
              }
            }
                else{
                    printf(C "invalid move!please try again\n" R1);
                    continue;
                }
               }
            else
            {
                printf(C "invalid value!try again\n" R1);
                continue;
            }
                }
                else
                {
                    printf(C "invalid value!try again\n" R1);
                continue;
                }


        }
}

void set_light(struct node1 place[9][13],int i3,int j3,int i4 ,int j4){
    int i= i3;
    int j = j3;
    int i1=i4 , j1=j4;
            if(place[i][j].object == 4){
                place[i][j].situation = 'L';
                if(i>0){
                    if(place[i-1][j].situation =='D')
                       place[i-1][j].situation ='L';
                   else if(place[i-1][j].situation =='L' ||  place[i-1][j].situation =='W')
                       place[i-1][j].situation ='S';
                }
                if(i<8){
                    if(place[i+1][j].situation =='D')
                       place[i+1][j].situation ='L';
                   else  if(place[i+1][j].situation =='L' ||  place[i+1][j].situation =='W')
                       place[i+1][j].situation ='S';
                }
                if(j<12){
                    if(place[i][j+1].situation =='D')
                       place[i][j+1].situation ='L';
                   else  if(place[i][j+1].situation =='L' ||  place[i][j+1].situation =='W')
                       place[i][j+1].situation ='S';
                }
                if(j>0){
                    if(place[i][j-1].situation =='D')
                       place[i][j-1].situation ='L';
                    else if(place[i][j-1].situation =='L' ||  place[i][j-1].situation =='W')
                       place[i][j-1].situation ='S';
                }
                if(j%2 == 0 && j<12 && i<12){
                    if(place[i+1][j+1].situation =='D')
                       place[i+1][j+1].situation ='L';
                     else if(place[i+1][j+1].situation =='L' ||  place[i+1][j+1].situation =='W')
                       place[i+1][j+1].situation ='S';
                }
                if(j%2 == 0 && j>0 && i<12){
                    if(place[i+1][j-1].situation =='D')
                       place[i+1][j-1].situation ='L';
                    else if(place[i+1][j-1].situation =='L' ||  place[i+1][j-1].situation =='W')
                       place[i+1][j-1].situation ='S';
                }
                if(j%2 == 1 && j<12 && i>0){
                    if(place[i-1][j+1].situation =='D')
                       place[i-1][j+1].situation ='L';
                   else  if(place[i-1][j+1].situation =='L' ||  place[i-1][j+1].situation =='W')
                       place[i-1][j+1].situation ='S';
                }
                if(j%2 == 1 && j>0 && i>0){
                    if(place[i-1][j-1].situation =='D')
                       place[i-1][j-1].situation ='L';
                     else if(place[i-1][j-1].situation =='L' ||  place[i-1][j-1].situation =='W')
                       place[i-1][j-1].situation ='S';
                }
            }
            if(place[i1][j1].object == 5){
                 place[i1][j1].situation = 'D';
                if(i1>0){
                    if(place[i1-1][j1].situation =='L')
                       place[i1-1][j1].situation ='D';
                   else if(place[i1-1][j1].situation =='S')
                       place[i1-1][j1].situation ='L';
                }
                if(i1<8){
                    if(place[i1+1][j1].situation =='L')
                       place[i1+1][j1].situation ='D';
                   else  if(place[i1+1][j1].situation =='S')
                       place[i1+1][j1].situation ='L';
                }
                if(j1<12){
                    if(place[i1][j1+1].situation =='L')
                       place[i1][j1+1].situation ='D';
                     else if(place[i1][j1+1].situation =='S')
                       place[i1][j1+1].situation ='L';
                }
                if(j1>0){
                    if(place[i1][j1-1].situation =='L')
                       place[i1][j1-1].situation ='D';
                    else if(place[i1][j1-1].situation =='S')
                       place[i1][j1-1].situation ='L';
                }
                if(j1%2 == 0 && j1<12 && i1<12){
                    if(place[i1+1][j1+1].situation =='L')
                       place[i1+1][j1+1].situation ='D';
                   else  if(place[i1+1][j1+1].situation =='S')
                       place[i1+1][j1+1].situation ='L';
                }
                if(j1%2 == 0 && j1>0 && i1<12){
                    if(place[i1+1][j1-1].situation =='L')
                       place[i1+1][j1-1].situation ='D';
                    else if(place[i1+1][j1-1].situation =='S')
                       place[i1+1][j1-1].situation ='L';
                }
                if(j1%2 == 1 && j1<12 && i1>0){
                    if(place[i1-1][j1+1].situation =='L')
                       place[i1-1][j1+1].situation ='D';
                   else  if(place[i1-1][j1+1].situation =='S')
                       place[i1-1][j1+1].situation ='L';
                }
                if(j1%2 == 1 && j1>0 && i1>0){
                    if(place[i1-1][j1-1].situation =='L')
                       place[i1-1][j1-1].situation ='D';
                    else if(place[i1-1][j1-1].situation =='S')
                       place[i1-1][j1-1].situation ='L';
                }
            }

}
void light_jw(struct node1 place[9][13],int i1,int j1,int mode ){
        int i = i1;
        int j = j1;
        if(mode == 0)
            return ;
       if(mode == 1){
        while(i>0){
            if(place[i-1][j].object == 8 || place[i-1][j].object ==4 || place[i-1][j].object== 5 || place[i-1][j].object==1){
            if(place[i-1][j].situation == 'D'){
             place[i-1][j].situation = 'W';}
          else if(place[i-1][j].situation == 'W'  ||  place[i-1][j].situation == 'L'){
             place[i-1][j].situation = 'S';}
            break;}
          if(place[i-1][j].situation == 'D'){
             place[i-1][j].situation = 'W';}
          else if(place[i-1][j].situation == 'W'  ||  place[i-1][j].situation == 'L'){
             place[i-1][j].situation = 'S';}
             i--;
        }
       }
       if(mode == 4){
        while(i<8){
            if(place[i+1][j].object == 8 || place[i+1][j].object ==4 || place[i+1][j].object== 5 || place[i+1][j].object==1){
            if(place[i+1][j].situation == 'D'){
             place[i+1][j].situation = 'W';}
          else if(place[i+1][j].situation == 'W' ||  place[i+1][j].situation == 'L'){
             place[i+1][j].situation = 'S';}
            break;}
          if(place[i+1][j].situation == 'D'){
             place[i+1][j].situation = 'W';}
          else if(place[i+1][j].situation == 'W' ||  place[i+1][j].situation == 'L'){
             place[i+1][j].situation = 'S';}
             i++;
        }
       }
     if(mode == 2){
        if(j%2==1){
            int tedad=0;
        while(i>0  && j<12){
            if(tedad %2 ==0){
            if(place[i-1][j+1].object == 8 || place[i-1][j+1].object ==4 || place[i-1][j+1].object== 5 || place[i-1][j+1].object==1){
            if(place[i-1][j+1].situation == 'D'){
             place[i-1][j+1].situation = 'W';}
         else  if(place[i-1][j+1].situation == 'W' ||   place[i-1][j+1].situation == 'L'){
             place[i-1][j+1].situation = 'S';}
            break;}
             if(place[i-1][j+1].situation == 'D'){
             place[i-1][j+1].situation = 'W';}
         else  if(place[i-1][j+1].situation == 'W' ||   place[i-1][j+1].situation == 'L'){
             place[i-1][j+1].situation = 'S';}
             j++;
             i--;
            }
            else if(tedad %2 ==1){
            if(place[i][j+1].object == 8 || place[i][j+1].object ==4 || place[i][j+1].object== 5 || place[i][j+1].object==1){
             if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
          else if(place[i][j+1].situation == 'W' ||   place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
            break;}
              if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
          else if(place[i][j+1].situation == 'W' ||   place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
             j++;
            }
            tedad++;
        }
     }
      if(j%2==0){
        int tedad=0;
        if(i==0){
             if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
           else if(place[i][j+1].situation == 'W' ||  place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
             j++;
        }
        while(i>0  && j<12){
            if(tedad %2 ==1){
            if(place[i-1][j+1].object == 8 || place[i-1][j+1].object ==4 || place[i-1][j+1].object== 5 || place[i-1][j+1].object==1){
             if(place[i-1][j+1].situation == 'D'){
             place[i-1][j+1].situation = 'W';}
           else if(place[i-1][j+1].situation == 'W' ||  place[i-1][j+1].situation == 'L'){
             place[i-1][j+1].situation = 'S';}
            break;}
             if(place[i-1][j+1].situation == 'D'){
             place[i-1][j+1].situation = 'W';}
           else if(place[i-1][j+1].situation == 'W' ||  place[i-1][j+1].situation == 'L'){
             place[i-1][j+1].situation = 'S';}
             j++;
             i--;
            }
             if(tedad %2 ==0){
            if(place[i][j+1].object == 8 || place[i][j+1].object ==4 || place[i][j+1].object== 5 || place[i][j+1].object==1){
             if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
          else if(place[i][j+1].situation == 'W'  ||  place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
            break;}
              if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
          else if(place[i][j+1].situation == 'W'  ||  place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
             j++;
            }
            tedad++;
        }
     }
     }
     if(mode == 3){
       if(j%2==1){
        if(i==8 && j<12){
         if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
          else if(place[i][j+1].situation == 'W'  ||  place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
        }
        int tedad=0;
        while(i<8  && j<12){
         if(tedad %2 ==1){
            if(place[i+1][j+1].object == 8 || place[i+1][j+1].object ==4 || place[i+1][j+1].object== 5 || place[i+1][j+1].object==1){
            if(place[i+1][j+1].situation == 'D'){
             place[i+1][j+1].situation = 'W';}
         else  if(place[i+1][j+1].situation == 'W'  ||  place[i+1][j+1].situation == 'L'){
             place[i+1][j+1].situation = 'S';}
            break;}
             if(place[i+1][j+1].situation == 'D'){
             place[i+1][j+1].situation = 'W';}
         else  if(place[i+1][j+1].situation == 'W'  ||  place[i+1][j+1].situation == 'L'){
             place[i+1][j+1].situation = 'S';}
             j++;
             i++;
            }
             if(tedad %2 ==0){
            if(place[i][j+1].object == 8 || place[i][j+1].object ==4 || place[i][j+1].object== 5 || place[i][j+1].object==1){
              if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
          else if(place[i][j+1].situation == 'W'  ||  place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
            break;}
              if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
          else if(place[i][j+1].situation == 'W'  ||  place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
             j++;
            }
            tedad++;
        }
     }
      if(j%2==0){
        int tedad=0;
        while(i<8  && j<12){
            if(tedad %2 ==0){
            if(place[i+1][j+1].object == 8 || place[i+1][j+1].object ==4 || place[i+1][j+1].object== 5 || place[i+1][j+1].object==1){
             if(place[i+1][j+1].situation == 'D'){
             place[i+1][j+1].situation = 'W';}
           else if(place[i+1][j+1].situation == 'W'  ||  place[i+1][j+1].situation == 'L'){
             place[i+1][j+1].situation = 'S';}
            break;}
             if(place[i+1][j+1].situation == 'D'){
             place[i+1][j+1].situation = 'W';}
           else if(place[i+1][j+1].situation == 'W'  ||  place[i+1][j+1].situation == 'L'){
             place[i+1][j+1].situation = 'S';}
             j++;
             i++;
            }
             if(tedad %2 ==1){
            if(place[i][j+1].object == 8 || place[i][j+1].object ==4 || place[i][j+1].object== 5 || place[i][j+1].object==1){
             if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
          else if(place[i][j+1].situation == 'W'  ||  place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
            break;}
              if(place[i][j+1].situation == 'D'){
             place[i][j+1].situation = 'W';}
          else if(place[i][j+1].situation == 'W'  ||  place[i][j+1].situation == 'L'){
             place[i][j+1].situation = 'S';}
             j++;
            }
            tedad++;
        }
     }
     }
      if(mode == 5){
       if(j%2==1){
            if(i==8 && j>0){
                if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
           else if(place[i][j-1].situation == 'W' ||  place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
        }
        int tedad=0;
        while(i<8  && j>0){
         if(tedad %2 ==0){
            if(place[i][j-1].object == 8 || place[i][j-1].object ==4 || place[i][j-1].object== 5 || place[i][j-1].object==1){
              if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
           else if(place[i][j-1].situation == 'W' ||  place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
            break;}
             if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
           else if(place[i][j-1].situation == 'W' ||  place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
             j--;
            }
             if(tedad %2 ==1){
            if(place[i+1][j-1].object == 8 || place[i+1][j-1].object ==4 || place[i+1][j-1].object== 5 || place[i+1][j-1].object==1){
             if(place[i+1][j-1].situation == 'D'){
             place[i+1][j-1].situation = 'W';}
           else if(place[i+1][j-1].situation == 'W'  ||  place[i+1][j-1].situation == 'L'){
             place[i+1][j-1].situation = 'S';}
            break;}
              if(place[i+1][j-1].situation == 'D'){
             place[i+1][j-1].situation = 'W';}
           else if(place[i+1][j-1].situation == 'W'  ||  place[i+1][j-1].situation == 'L'){
             place[i+1][j-1].situation = 'S';}
             j--;
             i++;
            }
            tedad++;
        }
     }
      if(j%2==0){
        int tedad=0;
        while(i<8  && j>0){
            if(tedad %2 ==0){
            if(place[i+1][j-1].object == 8 || place[i+1][j-1].object ==4 || place[i+1][j-1].object== 5 || place[i+1][j-1].object==1){
              if(place[i+1][j-1].situation == 'D'){
             place[i+1][j-1].situation = 'W';}
          else if(place[i+1][j-1].situation == 'W'  ||  place[i+1][j-1].situation == 'L'){
             place[i+1][j-1].situation = 'S';}
            break;}
             if(place[i+1][j-1].situation == 'D'){
             place[i+1][j-1].situation = 'W';}
          else if(place[i+1][j-1].situation == 'W'  ||  place[i+1][j-1].situation == 'L'){
             place[i+1][j-1].situation = 'S';}
             j--;
             i++;
            }
             if(tedad %2 ==1){
            if(place[i][j-1].object == 8 || place[i][j-1].object ==4 || place[i][j-1].object== 5 || place[i][j-1].object==1){
              if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
          else if(place[i][j-1].situation == 'W'  ||    place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
            break;}
              if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
          else if(place[i][j-1].situation == 'W'  ||    place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
             j--;
            }
            tedad++;
        }
     }
     }
     if(mode == 6){
       if(j%2==0){
        int tedad=0;
     if(i==0 && j>0){
             if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
           else if(place[i][j-1].situation == 'W' ||  place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
             j--;
        }
        while(i>0  && j>0){
         if(tedad %2 ==0){
            if(place[i][j-1].object == 8 || place[i][j-1].object ==4 || place[i][j-1].object== 5 || place[i][j-1].object==1){
              if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
           else if(place[i][j-1].situation == 'W'  ||    place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
            break;}
             if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
           else if(place[i][j-1].situation == 'W'  ||    place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
             j--;
            }
             if(tedad %2 ==1){
            if(place[i-1][j-1].object == 8 || place[i-1][j-1].object ==4 || place[i-1][j-1].object== 5 || place[i-1][j-1].object==1){
              if(place[i-1][j-1].situation == 'D'){
             place[i-1][j-1].situation = 'W';}
          else  if(place[i-1][j-1].situation == 'W'  ||  place[i-1][j-1].situation == 'L'){
             place[i-1][j-1].situation = 'S';}
            break;}
              if(place[i-1][j-1].situation == 'D'){
             place[i-1][j-1].situation = 'W';}
          else  if(place[i-1][j-1].situation == 'W'  ||  place[i-1][j-1].situation == 'L'){
             place[i-1][j-1].situation = 'S';}
             j--;
             i--;
            }
            tedad++;
        }
     }
      if(j%2==1){
        int tedad=0;
        while(i>0  && j>0){
            if(tedad %2 ==0){
            if(place[i-1][j-1].object == 8 || place[i-1][j-1].object ==4 || place[i-1][j-1].object== 5 || place[i-1][j-1].object==1){
              if(place[i-1][j-1].situation == 'D'){
             place[i-1][j-1].situation = 'W';}
          else if(place[i-1][j-1].situation == 'W'  ||  place[i-1][j-1].situation == 'L'){
             place[i-1][j-1].situation = 'S';}
            break;}
             if(place[i-1][j-1].situation == 'D'){
             place[i-1][j-1].situation = 'W';}
          else if(place[i-1][j-1].situation == 'W'  ||  place[i-1][j-1].situation == 'L'){
             place[i-1][j-1].situation = 'S';}
             j--;
             i--;
            }
             if(tedad %2 ==1){
            if(place[i][j-1].object == 8 || place[i][j-1].object ==4 || place[i][j-1].object== 5 || place[i][j-1].object==1){
            if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
          else if(place[i][j-1].situation == 'W'  ||  place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
            break;}
              if(place[i][j-1].situation == 'D'){
             place[i][j-1].situation = 'W';}
          else if(place[i][j-1].situation == 'W'  ||  place[i][j-1].situation == 'L'){
             place[i][j-1].situation = 'S';}
             j--;
            }
            tedad++;
        }
     }
     }
}

int move_sg(struct node1 place[9][13],int i1,int j1,int i2,int j2){
        while(1){
           if(place[i2][j2].object == 0 || place[i2][j2].object == 3  || place[i2][j2].object == 2){
                if(j1%2==0){
                int x = i2-i1;
                int y = j2-j1;

                if((x==-1 && y==0) || (x==0 && y==1 )|| (x==1  && y==1) || (x==1  && y==0 ) || (x==1  && y==-1) || (x==0 && y==-1)){
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     return 1;
                }
                }
               else if(j1%2==1){
                int x = i2-i1;
                int y = j2-j1;

                if((x==-1 && y==0) || (x==-1 && y==1 )|| (x==0  && y==1) || (x==1  && y==0 ) || (x==0  && y==-1) || (x==-1 && y==-1)){
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     return 1;
                }
               }
                else
                {
                    printf(C "invalid value!try again\n" R1);
                return 0;
                }
            }
            else if(place[i2][j2].object == 6){
                if(j1%2==0){
                int x = i2-i1;
                int y = j2-j1;

                if((x==-1 && y==0) || (x==0 && y==1 )|| (x==1  && y==1) || (x==1  && y==0 ) || (x==1  && y==-1) || (x==0 && y==-1)){
                    int check;
                 printf("Are you Mr.jack?\t1- yes 2- no\n");
                 scanf("%d",&check);
                if(check == 1){
                  win_check++;
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                     char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                     return 1;
                }
                }
                }
               else if(j1%2==1){
                int x = i2-i1;
                int y = j2-j1;

                if((x==-1 && y==0) || (x==-1 && y==1 )|| (x==0  && y==1) || (x==1  && y==0 ) || (x==0  && y==-1) || (x==-1 && y==-1)){
                    int check;
              printf("Are you Mr.jack?\t1- yes 2- no\n");
               scanf("%d",&check);
              if(check == 1){
              win_check++;
                    char s[3];
                    strcpy(s,place[i2][j2].character);
                    strcpy(place[i2][j2].character,place[i1][j1].character);
                    strcpy(place[i1][j1].character,s);
                    char temp;
                    temp =  place[i2][j2].criminal ;
                    place[i2][j2].criminal =  place[i1][j1].criminal;
                     place[i1][j1].criminal = temp;
                     PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
                   return 1;
                }
               }
               }
            }
            else
            {
                printf(C "invalid value!try again\n" R1);
                return 0;
            }
                }
}

void move_tunnel (struct node1 place[9][13],char *s,int *i,int *j){
     int i1,j1,i2,j2;
     i1 = *i;
     j1 = *j;
     while(1){
     printf(G "please enter the location of target tunnel(2 values)\n" R1);
     scanf("%d%d",&i2,&j2);
     if(check_tunnel(place,i2,j2)==1){
         char s[3];
        strcpy(s,place[i2][j2].character);
        strcpy(place[i2][j2].character,place[i1][j1].character);
        strcpy(place[i1][j1].character,s);
        char temp;
        temp =  place[i2][j2].criminal ;
        place[i2][j2].criminal =  place[i1][j1].criminal;
        place[i1][j1].criminal = temp;
         *i =i2;
         *j =j2;
         PlaySound(TEXT("move.wav"),NULL,SND_ASYNC);
         break;
     }
     else{
        printf(C "incorrect values!try again\n" R1);
        continue;
     }
     }
}
int check_tunnel (struct node1 place[9][13],int i,int j){
     if(place[i][j].object == 2)
        return 1;
     else
        return 0;
}
void show_criminal (struct node1 place[9][13],char *mrjack){
    int i,j,i1,j1;
   for(i=0;i<9;i++)
   for(j=0;j<13;j++){
    if(strcmp(place[i][j].character,mrjack)==0)
    {
     i1= i;
     j1= j;
     break;
    }
   }

   if(place[i1][j1].situation == 'D')
   {
       for(i=0;i<9;i++)
       for(j=0;j<13;j++){
if(strcmp(place[i][j].character,"  ")!=0){
            if(place[i][j].criminal == 'c'){
                if(place[i][j].situation == 'L' || place[i][j].situation == 'W' || place[i][j].situation == 'S'  || (nearlight(place,i,j)==1))
                    place[i][j].criminal = 'i';
            }
        }
       }
   }
   else if(place[i1][j1].situation == 'L' || place[i1][j1].situation == 'W' || place[i1][j1].situation == 'S'  || (nearlight(place,i1,j1)==1))
   {
      for(i=0;i<9;i++)
       for(j=0;j<13;j++){
if(strcmp(place[i][j].character,"  ")!=0){
            if(place[i][j].criminal == 'c'){
                if(place[i][j].situation == 'D' )
                    place[i][j].criminal = 'i';
            }
        }
       }
   }
}
int nearlight(struct node1 place[9][13],int i,int j){
   if(j%2==0){
    if(i>0){
        if(strcmp(place[i-1][j].character,"  ")==1)
            return 1;
    }
     if(i<8){
        if(strcmp(place[i+1][j].character,"  ")==1)
            return 1;
    }
    if(j<12){
         if(strcmp(place[i][j+1].character,"  ")==1)
            return 1;
    }
   if(j>0){
         if(strcmp(place[i][j-1].character,"  ")==1)
            return 1;
    }
    if(j<12  && i<8){
         if(strcmp(place[i+1][j+1].character,"  ")==1)
            return 1;
    }
    if(j>0  && i<8){
         if(strcmp(place[i+1][j-1].character,"  ")==1)
            return 1;
    }
   }
   if(j%2==1){
     if(i>0){
        if(strcmp(place[i-1][j].character,"  ")==1)
            return 1;
    }
     if(i<8){
        if(strcmp(place[i+1][j].character,"  ")==1)
            return 1;
    }
    if(j<12){
         if(strcmp(place[i][j+1].character,"  ")==1)
            return 1;
    }
   if(j>0){
         if(strcmp(place[i][j-1].character,"  ")==1)
            return 1;
    }
    if(j<12  && i>0){
         if(strcmp(place[i-1][j+1].character,"  ")==1)
            return 1;
    }
    if(j>0  && i>0){
         if(strcmp(place[i-1][j-1].character,"  ")==1)
            return 1;
    }
   }
   return 0;
}
void recorrect (struct node1 place[9][13]){
  int i,j;
  for(i=0;i<9;i++)
  for(j=0;j<13;j++){
    if((strcmp(place[i][j].character,"  ")==0) && place[i][j].object == 9){
     place[i][j].object = 0;}
     if((strcmp(place[i][j].character,"  ")== 1) && place[i][j].object == 0){
     place[i][j].object = 9;}
  }
}
int check_near(struct node1 place[9][13],int i,int j,char *s){
   if(j%2==0){
    if(i>0){
        if(strcmp(place[i-1][j].character,s)==0)
            return 1;
    }
     if(i<8){
        if(strcmp(place[i+1][j].character,s)==0)
            return 1;
    }
    if(j<12){
         if(strcmp(place[i][j+1].character,s)==0)
            return 1;
    }
   if(j>0){
         if(strcmp(place[i][j-1].character,s)==0)
            return 1;
    }
    if(j<12  && i<8){
         if(strcmp(place[i+1][j+1].character,s)==0)
            return 1;
    }
    if(j>0  && i<8){
         if(strcmp(place[i+1][j-1].character,s)==0)
            return 1;
    }
   }
   if(j%2==1){
     if(i>0){
        if(strcmp(place[i-1][j].character,s)==0)
            return 1;
    }
     if(i<8){
        if(strcmp(place[i+1][j].character,s)==0)
            return 1;
    }
    if(j<12){
         if(strcmp(place[i][j+1].character,s)==0)
            return 1;
    }
   if(j>0){
         if(strcmp(place[i][j-1].character,s)==0)
            return 1;
    }
    if(j<12  && i>0){
         if(strcmp(place[i-1][j+1].character,s)==0)
            return 1;
    }
    if(j>0  && i>0){
         if(strcmp(place[i-1][j-1].character,s)==0)
            return 1;
    }
   }
   return 0;
}


