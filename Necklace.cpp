/*-*-C++-*-*////////////////////////////////////////////////////////////////////
#include /*                                                        ***/ <cstdio>
#include /*                                                        ***/ <string>
#include /*                                                        */ <iostream>
#include /*                                                        ***/ <vector>
#include /*                                                        */ <iterator>
#include /*                                                        ****/ <tuple>
using namespace                                                             std;
////////////////////////////////////////////////////////////////////////////////
////----____oooo````;;;;,,,,....''''----    ....////---->>>>!!!!^^^^    ____%%%%
string::iterator next(string::iterator it, string &s)
{ /* Implement circular iteration by overloading std::next */
  return ( ++it == s.end() )? s.begin(): it; }
  
string::iterator prev(string::iterator it, string &s)
{ /* oo */
  return ( it-- == s.begin() )? (s.end() - 1): it; /* neva beginze */ }

////    ----    <<<<    ****    ||||    ````    ,,,,    ....    ;;;;    >>>>
vector<int> extract_wpos(const string &s)
{ /* Extract white positions from s. */
  vector<int> wpos;
  int siz = s.size();
  for (int i(0); i < siz; ++i) {
    if( s[i] == 'w' ){ wpos.push_back(i); }}
  return wpos; }

////----____````////====,,,,''''////####....""""////eeee    ||||////&&&&____''''
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &vec)
{ /* Yea! */
  copy(vec.begin(), vec.end(), ostream_iterator<T>(out, " "));
  return out; }

////////////////////////////////////////////////////////////////////////////////
vector<string> paint(const string &s)
{ /* Use w's in s to generate all possible coloured necklaces. */
  vector<int> wpos = extract_wpos(s);
  int wsiz = wpos.size(); // number of w's
  int car  = 1 << wsiz;   // cardinality of the set of all wsiz subsets
  vector<string> stk;     // buffer 
  /* [Ok] let's have a string s = wrbw, than wpos should be [0,3] and
   * car = 4, now we have to match the 1-bits in 0 <= bits < car to red
   * and 0-bits to b in the corresponding w's:
   * wpos: 0 '   '   ' 3 
   * s   : w ' r ' b ' w
   * bits: 0 '   '   ' 0 : 0(brbb)
   *       1 '   '   ' 0 : 1(rrbb)
   *       0 '   '   ' 1 : 2(brbr)
   *       1 '   '   ' 1 : 3(rrbr)
   */
  for (int bits = 0; bits < car; ++bits) {
    string t = s; /* copy */
    for (int j = 0; j < wsiz; ++j) {
      int p = wpos[j];
      if( bits & (1 << j) ){
        t[p] = 'r'; 
      } else {
        t[p] = 'b'; 
      }}
    stk.push_back(t); }
  return stk; }

////////////////////////////////////////////////////////////////////////////////
int cont(const string::iterator &fwd, string &s)
{ /* Count number of same beads on both, fwd and bwd ends. */
  int x = 2; // conter
  const string::iterator &bwd = ::prev(fwd, s); 
  for(string::iterator it = fwd; *(it = ::next(it, s)) == *fwd; ++x)
    ;
  for(string::iterator it = bwd; *(it = ::prev(it, s)) == *bwd; ++x)
    ;
  return x; }

    ////    ----    ````    ,,,,    ____    ====    ||||    """"    ****    ;;;;
pair<int, int> junction(string &s)
{ /* Apply cont to all rb or br junctions, return maximum cont, and position. */
  int mx = 0; // maximum count
  int m = -1; // mx position
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (*it != *::prev(it, s)) { // junction
      int x = cont(it, s);
      if( x > mx ){
        m = it - s.begin();
        mx = x; }}}
  if( m == -1 ){ // there are no junctions
    mx = s.size(); }
  return {mx, m}; }

////    ----****____\\\\----    ****____  * ____ *  ==== *  ````*   ====  * ====
tuple<int, int, string> Necklace(string &s)
{ /* Return beads counter, cut position and necklace string. */
  vector<string> stk = paint(s);
  int cont(0);
  int j;
  vector<string>::iterator p;
  for (auto it = stk.begin(); it != stk.end(); ++it) {
    auto [mx, m] = junction(*it);
    if( cont < mx ){
      cont = mx;
      j = m;
      p = it; }}
  return {cont, j, *p}; }

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{ /* yea! */
  string s = "rwbwwbbbrrwwbrr";
  puts(s.c_str());
  auto [cont, j, Nec] = Necklace(s);
  cout << cont << ' ' << j << ' ' << Nec; 
  puts(""); }

/////////////////////////////////////////////////////////////////////////// log:
// xògu neE
