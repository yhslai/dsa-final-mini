#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <climits>
#include <string>
#include <set>
#include <map>
#include <backward/hash_set>
#include <backward/hash_map>

#define STREND ('\0')
#define BUFFER_SIZE (1000000)
#define NAME_SIZE (1000)
#define MAIL_BUCKET_SIZE (100000)
#define WORD_BUCKET_SIZE (10000000)

using namespace std;

#include "string_hash.cpp"

typedef __gnu_cxx::hash_set<int> Mail_set;
typedef __gnu_cxx::hash_map<string, Mail_set, String_Hasher, String_Equaler> Name_index;
typedef __gnu_cxx::hash_map<string, Mail_set, String_Hasher, String_Equaler> Keyword_index;
typedef set<int> Ordered_mails;
typedef multimap<int, int> Date_index;

char input_buffer[BUFFER_SIZE];
char output_buffer[BUFFER_SIZE];
Mail_set mail_set(MAIL_BUCKET_SIZE); 
Name_index name_index(MAIL_BUCKET_SIZE);
Date_index date_index;
Keyword_index keyword_index;

#include "io.cpp"
#include "index.cpp"
#include "command.cpp"

void input_cmd(char cmd[]) {
    if(strncmp(cmd, "add", 3) == 0) {
        add_mail(&cmd[4]);
    }
    else if(strncmp(cmd, "remove", 6) == 0) {
        int id=get_int(&cmd[7]);
        remove_mail(id);
    }
    else {
        char *from_ptr=&cmd[12];
        char *to_ptr=strstr(from_ptr, " To ")+4;
        char *before_ptr=strstr(to_ptr, " Before ")+8;
        char *after_ptr=strstr(before_ptr, " After ")+7;
        char *keywords_ptr;
        if(*after_ptr == '-')
            keywords_ptr = after_ptr+2;
        else
            keywords_ptr=strstr(after_ptr, ":")+4;
        *(to_ptr-4) = *(before_ptr-8) = *(after_ptr-7) = *(keywords_ptr-1) = STREND;
        search_mails(from_ptr, to_ptr, before_ptr, after_ptr, keywords_ptr);
    }
}

int main() {
    while(gets(input_buffer)) {
        input_cmd(input_buffer); 
    }; 
}
