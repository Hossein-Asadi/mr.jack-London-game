#ifndef FUNC1_H_INCLUDED
#define FUNC1_H_INCLUDED

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


void step_one(void);
void step_two(void);
void step_three(void);
void random(int a[8]);
void introduction (char *s);
struct node * create_node (char *str);
void add_list (struct node *head , struct node *new_node);
void print_list (struct node * head);
void divide (struct node *head,struct node *head1,struct node *head2);
void delete_front (struct node **head);
void delete_next (struct node **head,int pos);
void find_node(struct node *head,char *s,int chs);
void board(struct node1 place[9][13]);
int check_well_banner(struct node1 place[9][13],int i3,int j3,int i4,int j4);
int check_blocker(struct node1 place[9][13],int i3,int j3,int i4,int j4);
void light_jw_off (struct node1 place[9][13]);
int check_sg(struct node1 place[9][13],int i1,int j1,int i2,int j2,int i3,int j3);
int check_place (struct node1 place[9][13],char *s,int i1,int j1);
void light_off_rnd (struct node1 place[9][13]);
void whistle (struct node1 place[9][13],int i1,int j1);
int check_lamplight(struct node1 place[9][13],int i3,int j3,int i4,int j4);





#endif // FUNC1_H_INCLUDED
