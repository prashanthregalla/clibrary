
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#include "helper_fns_pr.h"

#define MAX_WORDS 500000
#define MAX_LENGTH 40
#define ASK_USER_AFTER 5

char *words[MAX_WORDS];

static void
str_tolower(char *str)
{
    for(int i = 0; str[i]; i++){
      str[i] = tolower(str[i]);
      }
}

static int 
read_words(void) //returns count of all words eligible for the game
{
    FILE* fp;

    if((fp = fopen("/usr/share/dict/linux.words", "r")) == NULL)
    {
        fprintf(stderr, "Unable to open the words list file /usr/share/dict/linux.words ...%s\n",strerror(errno));
        exit(1);  
    }
    int count = 0;
    //able to open and got the handle to file now
    char cur_word[MAX_LENGTH]; //buffer
    while( (fgets(cur_word, MAX_LENGTH, fp))!= NULL)
    {
        
        str_tolower(cur_word);
        int word_len = strlen(cur_word);
        cur_word[word_len-1] = '\0'; //replacing the \n character with \0
        
        //<=4 even when we wanted 4 char words is because the word_len includes \n char too
        if( word_len <=4 ||                  
            (cur_word[0] >='0' && cur_word[0] <='9') || strchr(cur_word, '.') ||
            strchr(cur_word, '/') || strchr(cur_word,'\'') || strchr(cur_word, '-') || strchr(cur_word, ',') )

                continue;
        words[count] = strdup(cur_word);
        count++;   

    }
    return count;

}

//shifting this to helper_fns_pr.h

/*
 * static void
fill_word(char *word, char fill_char, int word_len)
{
    //int word_len = strlen(word);

    for(int i=0; i < word_len; i++)
        word[i] = fill_char;
}
*/

static void
give_hint(char* word, char* hint_buf, int hint_no, int word_len)
{

    int hint_pos;

    while(1)
    {
        hint_pos = rand() % word_len;
        if(hint_buf[hint_pos] == '.')
        {
            hint_buf[hint_pos] = word[hint_pos];
            break;
        }
    }

    hint_buf[word_len] = '\0';
    if( (word_len <=5 && hint_no <= 2) || (word_len >5 && hint_no <= 4))
        printf("\nHint #%d : %s", hint_no, hint_buf);
    else
        printf("\nNo clues now...");

}


/*
static void
shuffle_word(char *word, int word_len)
{
    char shuffle_buf[MAX_LENGTH];
    strcpy(shuffle_buf, word);
    int count = 0; //for the filled positions in the shuffle_buf    
    int shuffle_pos;
    fill_word(shuffle_buf, '.', word_len);
    
    while(count <= word_len)
    {
        shuffle_pos = rand() % word_len;
        if(shuffle_buf[shuffle_pos] == '.')
        {
            shuffle_buf[shuffle_pos] = word[count];
            count++;
            if(count == word_len)
                break;
        }
               
    }
    strcpy(word, shuffle_buf);
    //printf("word is : %s\n", word);
    //printf("Shuffled word is : %s\n", shuffle_buf);
}
*/

void
play_game_anagram()
{
    
       
    srand(time(NULL));
    system("clear");   
    
    printf("\n\n\n************************************ ANAGRAM GAME ********************\n\n");
    printf("***************** You need to guess the correct word by looking at the given anagram... ******************** \n\n");
    
    char proceed = 'y';
    
    int count = read_words(); //read the file and get the word count for the game
    //printf("count is %d\n", count);
    //exit(0);

    int anagram_no = 1; //these many words are displayed without asking and then ask for user confirmation

    while(proceed == 'y' || proceed == 'Y')
    {
        
        system("clear");
        printf("\n\n\n************************************ ANAGRAM GAME ********************\n\n");
        printf("***************** You need to guess the correct word by looking at the given anagram... ******************** \n\n");
        int no_tries = 0, no_hints = 0;
        int max_tries = 0, max_hints = 0;
        int right = 0;
        
        

        int disp_word_num = rand() % count;
        int disp_word_len = strlen(words[disp_word_num]);
        char display_word[MAX_LENGTH];
        char hint_buf[MAX_LENGTH];
        char answer[MAX_LENGTH];

        //strcopy(hint_buf, words[disp_word_num]);
        //fill_word(hint_buf, '.', disp_word_len);
        memset(hint_buf, '.', disp_word_len);

        if(disp_word_len <=5)
            max_tries = 3;
        else
            max_tries = 5;
            
        if(disp_word_len <=5)
            max_hints = 2;
        else
            max_hints = 4;

        strcpy(display_word, words[disp_word_num]);
        shuffle_word(display_word, disp_word_len);
        while(++no_tries <= max_tries)
        {    
            printf("            Anagram #%d: %s, Type in correct word, Attempt #%d :  ", anagram_no, display_word, no_tries);
            fgets(answer, MAX_LENGTH, stdin);
        
        
            //check if it is right answer
            if(strncmp(answer, words[disp_word_num], disp_word_len) == 0)
            {
                printf("\n\nNice...Right Answer...You have succeeded in %d Attemtpts\n\n\n", no_tries);
                right = 1;
                break;
            }
            else
            {
                if(++no_hints <= max_hints)
                    give_hint(words[disp_word_num], hint_buf, no_hints, disp_word_len);   
            }   
        
        }
        
        if(!right)
        {
            printf("\n\nNice try...Answer is : %s\n", words[disp_word_num]);
            //getchar();
        }
        fflush(NULL);
        
        if(anagram_no++ < ASK_USER_AFTER)
        {
            sleep(3);
            continue;
        }

        printf("\nWant to Proceed with another word now...?(y/n): ");
        //proceed = getchar();
        proceed = fgetc(stdin);
        getchar(); //to eat the new_line character left by fgetc
        
                  
    }
    
    printf("\n\nThank you for Playing...Try again when you have some time....\n\n");
    return 0;
}

