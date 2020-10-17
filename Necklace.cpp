#include                                                                <string>
#include                                                              <iostream>
using namespace                                                             std;
////////////////////////////////////////////////////////////////////////////////
////----____oooo````;;;;,,,,....''''----    ....////---->>>>!!!!^^^^    ____%%%%
string::iterator next(string::iterator it, string &s)
{ /**/
  if( ++it == s.end()) it = s.begin();
  return it; }
  
string::iterator prev(string::iterator it, string &s)
{ /* oo */
  if( it == s.begin()) it = s.end(); // neva beginze
  return --it; }

////////////////////////////////////////////////////////////////////////////////
int cont(const string::iterator &cut, string &s)
{ /* Count number of same beads on both ends. */
  const string::iterator put = prev(cut, s); // note: there is std::prev!!
  char f = *cut; /* forward */
  char b = *put; /* bacward */
  int cx = 2; // conter
  for(string::iterator it = cut; 
      *(it = next(it, s)) == f; 
      ++cx) {}
  for(string::iterator it = put;
      *(it = prev(it, s)) == b;
      ++cx) {}
  return cx; }

    ////    ----    ````    ,,,,    ____    ====    ||||    """"    ****    ;;;;
pair<int,int> junction(string &s)
{ /* Apply cont to al {r,b} junctions, return maximum cont and position. */
  int mcont = 0; // maximum count
  int m = -1;    // mcont position
  for (string::iterator it = s.begin(); it != s.end(); ++it) {
    if (*it != *prev(it, s)) { // junction
      int cx = cont(it, s);
      if( cx > mcont) {
        m = it - s.begin();
        mcont = cx; }}}
  if (m == -1) { // there are no junctions
    mcont = s.size(); }
  return {m, mcont}; }

////    ----    <<<<    ****    ||||    ````    ,,,,    ....    ;;;;    >>>>____
#include <vector>
vector<int> extract_wpos( const string &s )
{ /* Get white positions from s. */
  vector<int> wpos;
  int siz = s.size();
  for (int i(0); i < siz; ++i) {
    if (s[i] == 'w') {
      wpos.push_back(i); }}
  return wpos; }

////----____````////====,,,,''''////####....""""////eeee    ||||////&&&&____''''
#include <iterator>
template <typename T>
ostream &operator<<(ostream &out, vector<T> vec)
{ /* Yea! */
  copy(vec.begin(), vec.end(), ostream_iterator<T>(cout," "));
  return out; }

////////////////////////////////////////////////////////////////////////////////
vector<string> paint(const string &s)
{ /* get all strings from template s */
  vector<int> wpos = extract_wpos(s);
  int wsiz = wpos.size();
  int car = 1 << wsiz; // cardinality
  vector<string> stk;
  for (int bits = 0; bits < car; ++bits) {
    string t = s; /* copy */
    /* match 1's with red and 0's with blue: */
    for (int j = 0; j < wsiz; ++j) {
      int p = wpos[j];
      if ( bits & ( 1 << j )) {
        t[p] = 'r'; }
      else {
        t[p] = 'b'; }}
    stk.push_back(t); }
  return stk; }

////    ----****____\\\\----    ****____  * ____ *  ==== *  ````*   ====  * ====
#include <tuple>
tuple<int,int,string> necklace(string &s)
{ /**/
  vector<string> stk = paint(s);
  int stksiz = stk.size();
  int cont =  0;
  int j    = -1;
  int i    = 0;
  for (int k = 0; k < stksiz; ++k) {
    auto [m, mcont] = junction(stk[k]);
    if (cont < mcont) {
      cont = mcont;
      j = m;
      i = k; }}
  return {cont, j, stk[i]}; }

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{ /* yea! */
  string s = "brrwwbwrwrrw";
  puts(s.c_str());
  auto [cont, j, t] = necklace(s);
  cout << cont << ' ' << j << ' ' << t; 
  puts(""); }

/////////////////////////////////////////////////////////////////////////// log:
//
