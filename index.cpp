void index_mail(int id) {
    mail_set.insert(id);
}

void index_keywords(int id, char keywords[]) {
    //TODO
}

void index_name(int id, char from[], char to[]) {
    string s1,s2,s3,s4("- -");
    s1 += from; s1 += " "; s1 += to;
    name_map[s1].insert(id);
    s2 += from; s2 += " "; s2 += "-";
    name_map[s2].insert(id);
    s3 += "-"; s3 += " "; s3 += to;
    name_map[s3].insert(id);
    name_map[s4].insert(id);
}

void index_date(int id, int epoch) {
    //TODO
}

bool remove_index(int id) {
    //TODO
    return mail_set.erase(id);
}

void Intersection(Ordered_mails &result, Mail_set &matches) {
    Ordered_mails::iterator mi=result.begin();
    while(mi != result.end()) {
        if(matches.find(*mi) == matches.end())
            result.erase(mi++);
        else
            mi++;
    } 
}

void search_index_name(char from[], char to[], Ordered_mails &result) {
    string s;
    s += from; s += " "; s += to;
    Mail_set &matches=name_map[s];
    Intersection(result, matches);
}
