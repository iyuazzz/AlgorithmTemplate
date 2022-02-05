/*
    index from 1
    return the border of each postion
 */
std::vector<int> kmp(std::string s) {
    s = " " + s;
    std::vector<int> border(s.length(), 0);
    int i = 2, j = 0;
    while (i < (int)s.length()){
        if(s[j + 1] == s[i]) {
            border[i ++] = ++ j;
        } else if (j == 0) {
            border[i ++] = 0;
        } else {
            j = border[j];
        }
    }
    return border;
}

