struct String_Hasher {
    size_t operator()(const string &str) const {
        return __gnu_cxx::__stl_hash_string(str.c_str());
    }
};

struct String_Equaler {
    bool operator()(const string &str_a, const string &str_b) const {
        return str_a.compare(str_b) == 0;
    }
};
