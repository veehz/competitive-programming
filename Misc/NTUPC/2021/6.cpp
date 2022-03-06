#include <bits/stdc++.h>
using namespace std;

template <typename T>
istream &operator>>(istream &is, vector<T> &vec) {
  for (auto &v : vec) is >> v;
  return is;
}
#define _ << ' ' <<
typedef long long ll;
typedef long double ld;

vector<string> split(string s, char n = ';') {
  string cur;
  vector<string> res;
  for (char c : s) {
    if (c == n) {
      res.push_back(cur);
      cur.clear();
    } else
      cur += c;
  }
  res.push_back(cur);
  return res;
}

/* map number to month name */
const string month_name[] = {"January",   "February", "March",    "April",
                             "May",       "June",     "July",     "August",
                             "September", "October",  "November", "December"};

struct person {
  string ic;
  ll day;
  ll month;
  ll year;
  bool male;
  person(string _ic) {
    ic = _ic;
    male = (ic.back() - '0') & 1;
    year = stoll(ic.substr(0, 2));
    if (year >= 30)
      year += 1900;
    else
      year += 2000;
    month = stoll(ic.substr(2, 2));
    day = stoll(ic.substr(4, 2));
  }
  ll birthdate() { return year * 10000 + month * 100 + day; }
  string str() {
    return ic + " " + ic.substr(4, 2) + " " + (month_name[month - 1]) + " " +
           to_string(year) + (male ? " Male" : " Female");
  }
};

/* Birthdate */
bool birthdate(person a, person b) { return a.birthdate() < b.birthdate(); }

/* Birth year */
bool birthyear(person a, person b) { return a.year < b.year; }

/* Birth Month */
bool birthmonth(person a, person b) { return a.month < b.month; }

/* Birth Day */
bool birthday(person a, person b) { return a.day < b.day; }

/* Male */
bool male(person a, person b) { return a.male > b.male; }

/* Female */
bool female(person a, person b) { return a.male < b.male; }

int main() {
  string s;
  cin >> s;
  vector<string> ic = split(s);
  vector<person> pl;
  for (auto k : ic) pl.push_back(person(k));
  // for (auto p : pl) cout << p.str() << endl;
  string c[3];
  getline(cin, c[0]);  // newline
  getline(cin, c[2]);
  getline(cin, c[1]);
  getline(cin, c[0]);
  for (int i = 0; i < 3; i++) {
    if (c[i] == "Birthdate")
      stable_sort(pl.begin(), pl.end(), birthdate);
    else if (c[i] == "Birth Year")
      stable_sort(pl.begin(), pl.end(), birthyear);
    else if (c[i] == "Birth Month")
      stable_sort(pl.begin(), pl.end(), birthmonth);
    else if (c[i] == "Birth Day")
      stable_sort(pl.begin(), pl.end(), birthday);
    else if (c[i] == "Gender with Male first")
      stable_sort(pl.begin(), pl.end(), male);
    else if (c[i] == "Gender with Female first")
      stable_sort(pl.begin(), pl.end(), female);
  }
  for (auto p : pl) cout << p.str() << endl;
}
