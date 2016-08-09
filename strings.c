
#include <stdlib.h>
#include <string.h>
#include <strings_pr.h>
#include <time.h>


void
string_shuffle(char *str, int str_len)
{
    
    srand(time(NULL));
    char *shuffle_buf = malloc(str_len);
    strcpy(shuffle_buf, str);
    int count = 0; //for the filled positions in the shuffle_buf    
    int shuffle_pos;
    //fill_word(shuffle_buf, '.', word_len); //defined in game_anagram.c
    memset(shuffle_buf, '.', str_len);

    while(count <= str_len)
    {
        shuffle_pos = rand() % str_len;
        if(shuffle_buf[shuffle_pos] == '.')
        {
            shuffle_buf[shuffle_pos] = str[count];
            count++;
            if(count == str_len)
                break;
        }

    }
    strcpy(str, shuffle_buf);
    free(shuffle_buf);
    shuffle_buf = NULL;
    //printf("word is : %s\n", word);
    //printf("Shuffled word is : %s\n", shuffle_buf);
}
