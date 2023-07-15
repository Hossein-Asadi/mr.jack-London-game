#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <MMsystem.h>


#define R     "\x1b[31m" //RED
#define G   "\x1b[32m"   //GREEN
#define Y  "\x1b[33m"   //YELLOW
#define B    "\x1b[34m" //BLUE
#define M "\x1b[35m"   //MAGENTA
#define C   "\x1b[36m" //CYAN
#define R1   "\x1b[0m" //RESET

struct node {
   char card_name[5];
   struct node *next;
};
struct node1 {
   char character[2];
   int object;
   char situation;
    char criminal;
};

void step_one(void){
   printf("2-player inference game\nLondon 1888 White Chapel\nThe night covers the streets with a mask of darkness.");
 printf("Jack moves in the shadowsThe best detectives of the gas lamp age have gathered here to arrest him before he can escape the darkness forever." );
           printf( "The trap slowly spreads and closes the way for himBut Jack is cunning. He actually stole the identity of one of the detectives.\n\n" );
  printf("One player chooses the role of Mr. Jack and the other the role of the detective. The goal of this game is to win one player and the game has a maximum of 8 rounds." );
        printf("In each round, 2 actions are performed by each player." );
    printf("\n\npress any key to continue...\n" );
    getchar();
    system("cls");
}
void step_three (void){
    int n;
      printf(G "player 1\nplease choose your role!\n" R1 R "1- MR.jack       " R1 C  "2- detective\n\n" R1);
      while(1){
      scanf("%d",&n);
      if(n!=1 && n!=2 ){
        printf(C "invalid number! please try again.\n" R1);
        continue;}
        else{
      if(n==1)
        printf(R "player 1 is MR.jack.\n" R1 B "player 2 is detective.\n" R1);
      if(n==2)
        printf(R "player 2 is MR.jack.\n" R1 B "player 1 is detective.\n" R1);
      printf(R "MR.jack \n" R1 G"please press any key to show your character...\n" R1);
      getchar();
      getchar();
      system("cls");
      break;
      }
    }
}
void step_two (void){
    printf("Informations about this game & symbols:\n" R "objects" R1" :\n1 - blank : 0\t2 - house : 1\t3 - open tunnel : 2\t4 - close tunnel : 3\n");
    printf("5 - lights on : 4\t6 - lights off : 5\n7 - open escape route : 6\t8 - close escape route\t9 - extra house :8\t10 - character 's place:9\n");
    printf("\n" G " situation " R1 ":\nlightness : L\tDarkness : D\tWatson Light : W\tvery bright : S\n");
    printf("\n" B "character "R1 ":\n1 - INSPECTEUR LESTRADE(IL)\t2 - MISS STEALTHY(MS)\t3 - JEREMY BERT(JB)\n");
    printf("4 - JOHN H.WATSON(JW)\t5 - SIR WILLIAM GULL(WG)\t6 - SERGENT GOODLEY(SG)\n7 - JOHN SMITH(JS)\t 8 - SHERLOCK HOLMEZ(SH)\n");
    printf("\n" M " Criminal " R1 ":\n1- c : criminal     2- i : innocent\n");
    printf("\n\n in map first and second word are the " B "character's name " R1 " third word is" G " situation" R1 " and the last word is" M " criminal\n" R1);
    printf(G "\npress any key to continue...\n" R1);
    getchar();
    system("cls");
}
void random(int a[8])
{
    int tedad=0,i,random,k;
     srand(time(0));
    while(tedad<=7){
            k=1;
        random = rand()%8+1;
    for(i=0;i<tedad;i++){
        if(a[i]==random)
            k*=0;
    }
    if(k==1){
        a[tedad]=random;
        tedad++;
    }
    }
}
void introduction (char *s){
     if(strcmp (s,"SH")==0){
        printf(B "SHERLOK HOLMES(SH)\n" R1);
        printf("Move 1 to 3 houses then Take a card from the list of suspects.\n");
     }
     if(strcmp (s,"JW")==0){
        printf(B "JOHN H.WATSON(JW)\n" R1);
        printf("Move 1 to 3 houses, then specify the direction of the light\n");
     }
     if(strcmp (s,"JS")==0){
        printf(B "JOHN SMITH(JS)\n" R1);
        printf("Move 1 to 3 houses. Before or after moving, you must select and turn off one light and turn on another light (one light must be on and the other off)\n");
     }
     if(strcmp (s,"IL")==0){
        printf(B "INSPECTEUR LESTRADE(IL)\n" R1);
        printf("Move 1 to 3 houses, then you have to take one of the blocking tokens and place it on the other exit.\n");
     }
     if(strcmp (s,"MS")==0){
        printf(B "MISS STEALTHY(MS)\n" R1);
        printf("Move 1 to 4 houses. You can pass non-empty houses to solve the movement, but the final destination where you stop must be an empty house.\n");
     }
     if(strcmp(s,"SG")==0){
        printf(B "SERGENT GOODLEY(SG)\n" R1);
        printf("Move 1 to 3 houses.whistle before or after the move,and move the game characters closer to you for a total of 3 moves.\n");
     }
     if(strcmp (s,"WG")==0){
        printf(B "SIR WILLIAM GULL(WG)\n" R1);
        printf("Move 1 to 3 houses or Change your location with another Character.\n");
     }
     if(strcmp (s,"JB")==0){
        printf(B "HEREMY BERT(JB)\n" R1);
        printf("Move 1 to 3 houses.before or after moving,remove one of the well caps and place it on the other well.\n");
     }
     printf(G "press any key to continue..." R1);
     getchar();
     getchar();
     system("cls");
}
struct node * create_node (char *str){

   struct node *nn;
   nn = (struct node *)malloc (sizeof(struct node));
   strcpy(nn -> card_name, str);
   nn -> next = NULL;
    return nn;
}
void add_list (struct node *head , struct node *new_node){
  //  printf("*");
      struct node *current ;
      for(current = head ; current -> next != NULL ; current = current -> next);
      current -> next = new_node;
      new_node -> next = NULL;
}

void print_list (struct node * head){
    struct node *current ;
    int i;
    for(current = head,i=1 ; current !=NULL ; current = current -> next,i++)
        printf("%d- %s \n",i,current -> card_name);
}
void divide (struct node *head,struct node *head1,struct node *head2){
    char str[50];
    struct node *current ,*nn;
    current = head -> next -> next;
    while(current!=NULL){
        strcpy(str,current -> card_name);
        nn=create_node(str);
        add_list(head1,nn);
        current = current -> next;
        strcpy(str,current -> card_name);
        nn=create_node(str);
        add_list(head2,nn);
        current = current -> next;
    }
}
void delete_front (struct node **head){
   struct node *current;
   current = *head;
   *head = (*head) -> next;
   free(current);
}
void delete_next (struct node **head,int pos){
   struct node *current;
   current = *head;
   for(int i=0;i<pos -1 && current != NULL;i++)
    current = current -> next;
   struct node *next = current -> next -> next;
   free(current -> next);
   current -> next = next;
}
void find_node(struct node *head,char *s,int chs){
    struct node *current;
    current = head;
    int i=1;
    while(i<chs){
        current = current -> next;
        i++;
    }
    strcpy(s,current -> card_name);
    printf("%s\n",s);
}
void board(struct node1 place[9][13]){
    int i,j,x,y;

    printf("     0     1     2     3     4     5     6     7     8     9    10    11    12\n");
   for(i=0;i<58;i++){
        if(i%6==0 && i!=0 && i!=59)
        printf("%d",i/6-1);
      else
        printf(" ");
    for(j=0;j<80;j++){
        if(i%6==0){
                if(i==0){
            if(j%12==9 || j%12==8 || j%12==10 || j%12==11)
                printf(Y "-" R1);
                else
                    printf(" ");
        }
        else
        {
           if(j%12==9 || j%12==8 || j%12==10 || j%12==11)
                printf(Y "-" R1);
                else if(j%12==2){
                    x=i/6-1;
                    y=j/6;
                printf(B " %s " R1 R "%d" R1 G "%c" R1 M"%c " R1,place[x][y].character,place[x][y].object,place[x][y].situation,place[x][y].criminal);
                }
        }
        }

        if(i%6==1){
            if(j%12==7){
               printf(Y "/" R1);
            }
            else if(j%12==0)
                printf(Y "\\" R1);
            else
                printf(" ");
        }
        if(i%6==2){
            if(j%12==6){
                printf(Y "/" R1);

            }
            else if(j%12==1)
                 printf(Y "\\" R1);
            else
                printf(" ");
        }
        if(i%6==3){
                if(i==57){
                 if(j%12==3 || j%12==2 || j%12==4 || j%12==5)
                printf(Y "-" R1);
                else
                    printf(" ");
                }
                else
                    {
                if(j==0 || j==1)
                printf(" ");
            if(j%12==3 || j%12==2 || j%12==4 || j%12==5)
                printf(Y "-" R1);
                else if(j%12==7 && j<78){
                     x=i/6;
                     y=j/6;
                    printf(B " %s " R1 R "%d" R1 G "%c" R1 M"%c " R1,place[x][y].character,place[x][y].object,place[x][y].situation,place[x][y].criminal);
                }
                }
        }
        if(i%6==4){
            if(j%12==1){
               printf(Y "/" R1);
            }
            else if(j%12==6)
                printf(Y "\\" R1);
            else
                printf(" ");
        }
        if(i%6==5){
            if(j%12==0)
                printf(Y "/" R1);
            else if(j%12==7)
            printf(Y "\\" R1);
            else
                printf(" ");
    }
    }
    printf("\n");
   }
   printf("     0     1     2     3     4     5     6     7     8     9    10    11    12\n");
}


int check_well_banner(struct node1 place[9][13],int i3,int j3,int i4,int j4){
     if(place[i3][j3].object== 3  && place[i4][j4].object== 2)
        return 1;
     else
        return 0;
}
 int check_blocker(struct node1 place[9][13],int i3,int j3,int i4,int j4){
     if(place[i3][j3].object== 7  && place[i4][j4].object== 6)
        return 1;
     else
        return 0;
 }
 void light_jw_off (struct node1 place[9][13]){
   int i,j;
   for(i=0;i<9;i++)
   for(j=0;j<13;j++){
    if(place[i][j].situation == 'W')
        place[i][j].situation = 'D';
    if(place[i][j].situation == 'S')
        place[i][j].situation = 'L';
   }

}
int check_sg(struct node1 place[9][13],int i1,int j1,int i2,int j2,int i3,int j3){
         if(i2==i3 && j3==j2){
                printf(C "invalid value!try again\n" R1);
                return 0;
            }
        else if((i3<0 || i3>8) || (j3<0 || j3>12) ){
                 printf(C "invalid value!try again\n" R1);
                return 0;
            }
 else if(place[i3][j3].object==1 || place[i3][j3].object==4  || place[i3][j3].object==5 || place[i3][j3].object==7 || place[i3][j3].object==8 || place[i3][j3].object==9){
                printf(C "invalid value!try again\n" R1);
                return 0;
            }
            else if(i1>=i2){
                if(j1>=j2){
                    if(j3>=j2 && j3<=j1 && i3>=i2 && i3<=i1)
                        return 1;
                    else
                        return 0;
                }
                if(j1<=j2){
                    if(j3<=j2 && j3>=j1 && i3>=i2 && i3<=i1)
                        return 1;
                    else
                        return 0;
                }
            }
            else if(i1<=i2){
                if(j1>=j2){
                    if(j3>=j2 && j3<=j1 && i3<=i2 && i3>=i1)
                        return 1;
                    else
                        return 0;
                }
                if(j1<=j2){
                    if(j3<=j2 && j3>=j1 && i3<=i2 && i3>=i1)
                        return 1;
                    else
                        return 0;
                }
            }
            return 0;
}
void light_off_rnd (struct node1 place[9][13]){
  int i1,j1;
  for(i1=0;i1<9;i1++)
  for(j1=0;j1<13;j1++){
    if(place[i1][j1].object == 4){
        place[i1][j1].object = 5;
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
                return;
    }
  }
}

int check_place (struct node1 place[9][13],char *s,int i1,int j1){
   if(strcmp(place[i1][j1].character,s)==0)
    return 1;
   else
    return 0;
}
void whistle (struct node1 place[9][13],int i1,int j1){
    int  total_whistle,whistle_num=0;
    int i2,j2,i3,j3;
    PlaySound(TEXT("whistle.wav"),NULL,SND_SYNC);
    board(place);
    char s[5];
     while(1){
        printf(G "please enter the number of moves :\n" R1);
        scanf("%d",&total_whistle);
        if(total_whistle>3 || total_whistle<1){
            printf(C "invalid value!try again\n" R1);
            continue;
        }
        else
            break;
     }
     system("cls");
     while(whistle_num < total_whistle){
        board(place);
        printf(G "step %d\n" R1,whistle_num+1);
        printf(G "please enter the location of the desired character:\n" R1);
        while(1){
        scanf("%d%d",&i2,&j2);
        if(i2>8 || i2<0 || j2<0 || j2>12){
            printf(C "invalid location!try again\n" R1);
           continue;
        }
        printf(G "please enter the name of the desired character:\n" R1);
        scanf("%s",s);
        int n = check_place(place,s,i2,j2);
        if(n==0){
            printf(C "invalid name!try again\n" R1);
            continue;
        }
        if(n==1){
            printf(G "please enter destination\n" R1);
            while(1){
                scanf("%d%d",&i3,&j3);
       if(i3>8 || i3<0 || j3<0 || j3>12){
            printf(C "invalid location!try again\n" R1);
           continue;
        }
        else if(check_sg(place,i1,j1,i2,j2,i3,j3)==0){
            printf(C "incorrect location!try again\n" R1);
            continue;
        }
        else {
          int k = move_sg (place,i2,j2,i3,j3);
          if(k==1)
        break;
          else
            continue;
        }
        }
        break;
        }
      }
        whistle_num++;
     }
     system("cls");
}
int check_lamplight(struct node1 place[9][13],int i3,int j3,int i4,int j4){
     if(place[i3][j3].object== 5  &&  place[i4][j4].object== 4)
        return 1;
     else
        return 0;
 }

