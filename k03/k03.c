#include <stdio.h>

#define DEBUG

#define ALPHABET_LEN    255

char StrOriginal[] = "On a dark deseart highway, cool wind in my hair.";
char StrKey[] = "wind";

char* ForceSearch(char text[], char key[])
{
    int start, pos;
    int text_len, key_len;

    text_len = strlen(text);
    key_len = strlen(key);

    for(start = 0; start+key_len < text_len; start++)
    {
        for(pos = 0; pos < key_len; pos++)
        {
            if(text[start+pos] == key[pos])
            {
                if(pos+1 == key_len)
                {
                    return &text[start];
                }
            }
            else
            {
                break;
            }
        }
    }
    return NULL;
}

char* BMSearch(char text[], char key[])
{
    char* ch;
    int index, key_index;
    int text_len, key_len;
    int* table[256];

    text_len = strlen(text);
    key_len = strlen(key);
    
    for(int pos = 0; pos < 256; pos++)
    {
        table[pos] = key_len;
    }
    for(int pos = 0; key[pos] != NULL; pos++)
    {
        table[key[pos]] = (key_len-1) - pos;
    }

    key_index = key_len - 1;
    while(text[key_index] != NULL)
    {
        ch = &text[key_index - (key_len-1)];
        for(index = 0; key[index] != 0; index++)
        {
            if(text[key_index - index] != key[(key_len-1) - index])
            {
                if(table[text[key_index - index]] > index)
                {
                    key_index += (int)table[text[key_index - index]] - index;
                }
                else
                {
                    key_index++;
                }
                ch = NULL;
                break;
            }
        }
        if(ch != NULL)
        {
            return ch;
        }
    }
    return NULL;
}

int main(void)
{
    char*   str;
    str = ForceSearch(StrOriginal, StrKey);
    printf("Force Search. Find keyword at:%s\n", str);

    str = BMSearch(StrOriginal, StrKey);
    printf("BM Search. Find keyword at:%s\n", str);

    return 0;
}