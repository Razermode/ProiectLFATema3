#include <bits/stdc++.h>

using namespace std;
ifstream fin ("tema3.in");
ofstream fout ("tema3.out");


unordered_map <string, set<string>> G;
unordered_map <string, set<string>> NonEpsilonG;

set <string> G_epsilon;
set <string> NonEpsilonGsymbol;
string NonEpsilonGS;

unordered_map <string , set<pair<string, char>>> Automat;
string start;
set<string> end_s;

int main()
{
    int M = 0;
    string  a, b;
    while (fin >> a >> b){
        G[a].insert(b);
        if(b != "$") {
            NonEpsilonG[a].insert(b);
            G_epsilon.insert(a);
        }
    }
    for (auto i : G_epsilon) {
        for (auto j : NonEpsilonG)
            for (auto k : j.second)
                if (k.find(i) != string::npos) {
                    string aux = k;
                    aux.erase(k.find(i), i.length());
                    NonEpsilonG[j.first].insert(aux);
                }
    }
    if (G["S"].find("$") != G["S"].end()) {
        NonEpsilonG["S1"].insert("$");
        for (auto x : NonEpsilonG["S"])
            NonEpsilonG["S1"].insert(x);
        NonEpsilonGS = "S1";
    }
    else
        NonEpsilonGS = "S";

    start = NonEpsilonGS;
    end_s.insert("D0");
    if(NonEpsilonG[NonEpsilonGS].find("$") != NonEpsilonG[NonEpsilonGS].end())
        end_s.insert(NonEpsilonGS);

    for (auto i: NonEpsilonG)
        for(auto j : i.second) {
            if (j != "$") {
                if(j.length() == 1)
                    Automat[i.first].insert(make_pair("D0", j[0]));
                else {
                    int pozTerm, pozNeTerm;
                    if(j[0] >= 'a' && j[0] <= 'z') {
                        pozTerm = 0;
                        pozNeTerm = 1;
                    }
                    else {
                        pozNeTerm = 0;
                        pozTerm = 1;
                    }
                    Automat[i.first].insert(make_pair(string(1, j[pozNeTerm]), j[pozTerm]));
                }
            }
        }
    for (auto i: NonEpsilonG) {
        fout << i.first << ' ';
        for (auto x : i.second)
            fout << x << ' ';
        fout << '\n';
    }
    fout << "\n\n";

    for(auto pereche: Automat)
        for (auto p: pereche.second) {
            M++;
            NonEpsilonGsymbol.insert(pereche.first);
            NonEpsilonGsymbol.insert(p.first);
        }

    fout << NonEpsilonGsymbol.size() << '\n' << M << '\n';
    for (auto pereche: Automat)
        for(auto p: pereche.second)
            fout << pereche.first << ' ' << p.first << ' ' << p.second << '\n';

    fout << '\n' << NonEpsilonGS << '\n' << end_s.size() << '\n';
    for(auto i: end_s)
        fout << i << ' ';

    return 0;
}
