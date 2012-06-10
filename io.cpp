void p(const char str[]) {
    fputs(str, stdout);
}

int c_to_i(char c) {
    return c - '0';
}

int i_to_c(int x) {
    return x + '0';
}

int get_int(char digits[]) {
    int x=0;
    char *ptr=digits;
    while(isdigit(*ptr)) {
        x *= 10;
        x += c_to_i(*ptr);
        ptr++;
    }
    return x;
}

void put_int(int x) {
    if(x == 0) {
        putchar('0');
        return;
    }
    char *ptr = output_buffer;
    while(x) {
        *ptr = i_to_c(x%10);
        x /= 10;
        ptr++;
    }
    *ptr = STREND;
    char *ptr2 = output_buffer;
    while(*ptr2) {
        putchar(*ptr2);
        ptr2++;
    }
}


int get_month(char s[]) {
    const char month[12][10] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    for(int i=0; i<12; i++)
        if(strcmp(s, month[i]) == 0)
            return i;
    return -1;
}

int get_epoch(char date[]) {
    if(date[0] == '-')
        return -1;
    struct tm t;
    char *ptr=strtok(date, " ");
    t.tm_mday = get_int(ptr);
    ptr = strtok(NULL, " ");
    t.tm_mon = get_month(ptr);
    ptr = strtok(NULL, " ");
    t.tm_year = get_int(ptr) - 1900;
    ptr = strtok(NULL, " ");    //it's "at"
    ptr = strtok(NULL, ":");
    t.tm_hour = get_int(ptr);
    ptr = strtok(NULL, " \n");
    t.tm_min = get_int(ptr);
    t.tm_sec = 0;
    return mktime(&t);
}

