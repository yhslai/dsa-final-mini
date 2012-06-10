void index_mail(int id) {
    mail_set.insert(id);
}

void index_keyword(int id, char *keyword) {
    string word(keyword);
    keyword_index[word].insert(id); 
#ifdef DEBUG
    cerr << "Index ID " << id << " with keyword '" << keyword << "'" << endl;
#endif
}

void index_keywords(int id, char keywords[]) {
    char *p,*q;
    p = keywords;
    while(*p) {
        while(!isalnum(*p) && *p)
            p++;
        if(*p) {
            q = p;
            while(isalnum(*q))
                q++;
            bool ending = (*q == STREND);
            *q = STREND;
            index_keyword(id, p);
            if(ending)
                break;
            p = q + 1;
        }
    }
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
#ifdef DEBUG
    cerr << "Index ID " << id << " with name '" << s1 << "'" << endl;
    cerr << "Index ID " << id << " with name '" << s2 << "'" << endl;
    cerr << "Index ID " << id << " with name '" << s3 << "'" << endl;
    cerr << "Index ID " << id << " with name '" << s4 << "'" << endl;
#endif
}

void index_date(int id, int epoch) {
    date_index.insert(pair<int,int>(epoch,id));
}

bool id_exist(int id) {
    return mail_set.find(id) != mail_set.end();
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
#ifdef DEBUG
    cerr << "Search by name '" << s << "'" << endl;
#endif
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

void search_index_keywords(char keywords[], Ordered_mails &result) {
    char *ptr;
    ptr = strtok(keywords, " ");
    Mail_set &matches = keyword_index[string(ptr)];
    result = Ordered_mails(matches.begin(), matches.end());
    ptr = strtok(NULL, " ");
    while(ptr) {
        Mail_set &matches = keyword_index[string(ptr)];
        Intersection(result, matches);
        ptr = strtok(NULL, " ");
    }
}
