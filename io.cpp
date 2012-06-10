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
    ptr--;
    while(ptr >= output_buffer) {
        putchar(*ptr);
        ptr--;
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

int get_time(char date[]) {
    if(date[0] == '-')
        return -1;
    int year,mon,mday,hour,min;
    char *ptr=strtok(date, " ");
    mday = get_int(ptr);
    ptr = strtok(NULL, " ");
    mon = get_month(ptr);
    ptr = strtok(NULL, " ");
    year = get_int(ptr) - 1900;
    ptr = strtok(NULL, " ");    //it's "at"
    ptr = strtok(NULL, ":");
    hour = get_int(ptr);
    ptr = strtok(NULL, " \n");
    min = get_int(ptr);
    return year*535680 + mon*44640 + mday*1440 + hour*60 + min; 
}

