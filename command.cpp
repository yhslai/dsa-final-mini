void add_mail(char file_name[]) {
    FILE *fptr = fopen(file_name, "r");
    int date=0,id=0;
    static char from[NAME_SIZE],to[NAME_SIZE];
    if(fptr != NULL) {
        if(fgets(input_buffer, BUFFER_SIZE, fptr)) {
            //From:
            strcpy(from, &input_buffer[6]);
        }
        if(fgets(input_buffer, BUFFER_SIZE, fptr)) {
            //Date:
            date = get_epoch(&input_buffer[6]);
        }
        if(fgets(input_buffer, BUFFER_SIZE, fptr)) {
            //Message-ID:
            id = get_int(&input_buffer[12]);
        }
        if(fgets(input_buffer, BUFFER_SIZE, fptr)) {
            //Subject:
            index_keywords(id, &input_buffer[9]);        
        }
        if(fgets(input_buffer, BUFFER_SIZE, fptr)) {
            //To:
            strcpy(to, &input_buffer[4]);
        }
        index_name(id, from, to);
        index_date(id, date);
        if(fgets(input_buffer, BUFFER_SIZE, fptr)) {
            //Content:
            while(fgets(input_buffer, BUFFER_SIZE, fptr)) {
                index_keywords(id, input_buffer);
            }
        } 
    }
    else {
        p("No file: "); p(file_name); p("!!!!\n");
        return;
    }
    mail_counter++;
    p("Mail "); put_int(id); p(" added, you have "); put_int(mail_counter); p(" mails"); puts("");
}

void remove_mail(int id) {
    //TODO!
    mail_counter--;
    p("Mail ");
    put_int(id);
    p(" removed, you have ");
    put_int(mail_counter);
    p(" mails\n");
}

void search_mails(char from[], char to[], char before[], char after[], char keywords[]) {
    //TODO!
    printf("Searching from '%s' to '%s' before '%s' after '%s' keywords '%s'\n", from,to,before,after,keywords);
}

