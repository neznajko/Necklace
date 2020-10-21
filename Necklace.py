#!/usr/bin/env python3
####----\\\\;;;;    ____````,,,,||||====>>>>;;;;....////
def getColours(patron, nofBeads):
  """ patron is an integer with nofBeads number of bits.
      In binary it represents  a colouring pattern, e.g:
      patron = 10, nofBead = 4 is 1010. Now 1 is 'r' and
      0 is 'b', zo ..  **   the function will return the 
      corresponding bytearray, in the above case 'brbr'.
      Note that it's reversed.  oo     --  ..   ^^    """
  getColours.clr = b'br'
  b = bytearray(nofBeads)
  for pos in range(nofBeads):
    bit = ((1 << pos) & patron) >> pos
    b[pos] = getColours.clr[bit]
  return b

####====\\\\::::    ****____^^^^----,,,,>>>>    %%%%____
def findWhiteBeads(s):
  """ Return the positions of white beads. """
  ls = []
  for pos, char in enumerate( s ):
    if char == 'w': ls.append( pos )
  return ls

####....````____====''''----____====    ^^^^----____%%%%
def paint(wPos, t, patron, nofBeads):
  """ wPos is a list of w positions of t, which is a
      bytearray copy of the orininal template necklace
      string.                                        """
  b = getColours(patron, nofBeads)
  for j in range( nofBeads ):
    t[wPos[j]] = b[j]
    
####____    ====````----^^^^____====>>>>    ''''____````
####====oooo>>>><<<<====    ::::    ----^^^^____====>>>>
####----////\\\\....````====____****____====''''....,,,,
####====    ====____%%%%....====____====''''"""";;;;____
####    ****====,,,,____!!!!;;;;    ````____====****
####....    ''''    ____====;;;;""""____    ====----////
####....,,,,____====\\\\////____^^^^____====____^^^^----
####____````****oooo____////----%%%%####~~~~xxxx____****
####    ====****----,,,,%%%%        @@@@====____||||
####----$$$$....''''////----4444    ----____""""''''////
def clcknext(j, n):
  """ solid as a [s]ock """
  j += 1
  if j == n: j = 0
  return j

def clckprev(j, n):
  """ bo[+]m """
  j -= 1
  # w=[ 1, 2, 3 ], w[-3] iz 1, but w[-4] is boom. 
  if j < -n: j = -1
  return j

####====    ____::::""""''''````^^^^||||____====    ////
# s - a string: "bbbrrrb" of blue and red beads.     _=
# j - junction posi ^ tion                         _/
# retour number of same beads on both ends      -//
def cont(s, j):
  """ x [o] g u   n e E """
  # at least we have 2:
  x = 2
  bwd = j - 1 # backward position
  fwd = j     # w h a t i s t h i s ?
  n = len(s)
  while True:
    prev = clckprev(bwd, n)
    if s[prev] != s[bwd]: break
    x += 1
    bwd = prev
  while True:
    next = clcknext(fwd, n)
    if s[next] != s[fwd]: break
    x += 1
    fwd = next  
  return x

####____!!!!    \\\\^^^^////____````!!!!>>>>____'''',,,,
def getJunctions(s):
  """ 6 e 3   g y M u """
  junc = []
  for j in range(len(s)):
    if s[j] != s[j - 1]:
      junc.append(j)
  return junc 

####====>>>>====<<<<====````====,,,,====((((====''''====
def maxCont(s):
  """          """
  mx = 0  # max cont
  mj = -1 # mx junction 
  for j in getJunctions(s):
    x = cont(s, j)
    if mx < x:
      mx, mj = x, j
  if mj < 0: mx = len(s)
  return mx, mj

if __name__ == '__main__':
  s = 'wrwbwr'
  print(s)
  wpos = findWhiteBeads(s)
  nofw = len(wpos)
  mx, mj, mt = 0, None, None
  for j in range( 1 << nofw ):
    t = bytearray(s, encoding='utf-8')
    paint(wpos, t, j, nofw)
    x, j = maxCont(t.decode())
    if mx < x: mx, mj, mt = x, j, t
  print(mx, mj, mt.decode())

####____''''====>>>>"""",,,,    !!!!````~~~~%%%%,,,,log:
