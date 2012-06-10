void index_mail(int id) {
    mail_set.insert(id);
}

void index_keywords(int id, char keywords[]) {
    //TODO
}

void index_name(int id, char from[], char to[]) {
    string s1,s2,s3,s4("- -");
    s1 += from; s1 += " "; s1 += to;
    name_index[s1].insert(id);
    s2 += from; s2 += " "; s2 += "-";
    name_index[s2].insert(id);
    s3 += "-"; s3 += " "; s3 += to;
    name_index[s3].insert(id);
    name_index[s4].insert(id);
}

void index_date(int id, int epoch) {
    date_index.insert(pair<int,int>(epoch,id));
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
    Mail_set &matches = name_index[s];
    Intersection(result, matches);
}

void search_index_date(int before, int after, Ordered_mails &result) {
    if(before == -1 && after == -1)
        return;
    if(after == -1)
        after = INT_MIN;
    if(before == -1)
        before = INT_MAX;

    Mail_set matches;
    Date_index::iterator di,end_i;
    di = date_index.lower_bound(after);
    end_i = date_index.upper_bound(before);
    while(di != end_i) {
        matches.insert(di->second);
        di++;
    }
    Intersection(result, matches); 
}
