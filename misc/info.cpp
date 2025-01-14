---------------
// bitset
bitset<1000> b;
b.set(i);       //set ith bit
b.flip(i);      //flip ith bit
b.test(i);      //value
b.count();      //count of set bits
b.reset();      //set all bits to 0
b._Find_first();    //position of first set bit
b._Find_next(i)      //position of first set bit after i
b.to_string();      //converts to string

---------------
//THINGS TO WATCH OUT FOR:
// 1. multiset.count(x) is O(logn + occ(x)) !!!!!!
// 2. v.clear() doesn’t free the vector’s memory so if you are doing a small to large trick the memory complexity would 
// still be 𝑂(𝑛log𝑛) which might MLE in some cases. However v.clear(); v.shrink_to_fit(); frees its memory and makes the 
// memory complexity 𝑂(𝑛) in this case.

---------------
//Enumerating bitmasks:

//for updating all supermasks/submasks, just incrementally do it to get amortized N * (1 << N)

//iterate over all submasks of mask s
for (int s=m; s; s=(s-1)&m)
    ... use s ...
//note that mask = 0 will not be processed in the above

//iterating through all masks, with their submasks, O(3^n)
for (int m=0; m<(1<<n); ++m)
    for (int s=m; s; s=(s-1)&m)
        ... use s and m ...

---------------
//2-SAT
// We have some set of boolean variables, and a set of implications (disjunctions).
// The task is to find an assignment of values to all variables, such that the conjunction 
// of the implications is satisfied.
// For every boolean variable x, we create two nodes, representing x and !x 
// In this graph, for every implication a -> b, we will add edge a -> b and !b -> !a
//Finally, condense this graph into its SCC's
//Complete condition for existence of solution is that for every variable x, node x
//and node !x must be in different SCC.
//If condition true, topsort this dag. For every variable x, if scc of x occurs before 
//scc of !x, then x is false, else x is true
//Note: To force x to be true, add implication !x -> x (2 edges)
//Note: To force x to be false, add implication x -> !x (2 edges)

---------------
//SOS DP
// Given an array A[1 << N], find F[1 << N] such that F[i] = sum(A[mask]) such that mask is a submask of i
// Runs in O(N * (1 << N))
for(int i = 0; i<(1<<N); ++i)
	F[i] = A[i];
for(int i = 0; i < N; ++i) 
    for(int mask = 0; mask < (1<<N); ++mask)
	    if(mask & (1<<i))
		    F[mask] += F[mask^(1<<i)];

---------------
// int128 (supports numbers till 1e36)
// comment out all pbds things

typedef __int128 ell;

// For printing
std::ostream&
operator<<( std::ostream& dest, __int128_t value ) {
	std::ostream::sentry s( dest );
	if ( s ) {
		__uint128_t tmp = value < 0 ? -value : value; char buffer[ 128 ];
		char* d = std::end( buffer );
		do {	-- d; *d = "0123456789"[ tmp % 10 ]; tmp /= 10;} while ( tmp != 0 );
		if ( value < 0 ) {-- d; *d = '-';}
		int len = std::end( buffer ) - d;
		if ( dest.rdbuf()->sputn( d, len ) != len ) {dest.setstate( std::ios_base::badbit );}
	}
	return dest;
}

// For reading _int128 to_read = read()
__int128 read() {
	__int128 x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}
---------------
// Bellman ford, single source shortest path with negative weights
vector<int> d(n, INF);
d[v] = 0;
for (int i = 0; i < n - 1; ++i)
    for (Edge e : edges)
        if (d[e.a] < INF)
            d[e.b] = min(d[e.b], d[e.a] + e.cost);
//heuristic: stop the stage loop if at some stage no transitions are made
//negative cycle if we run a phase after the n - 1 th phase and it performs a relaxation

---------------
// Floyd Warshall, all pairs shortest paths with negative weights
for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (d[i][k] < INF && d[k][j] < INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 

---------------
// increasing splitting point for dp[i][l] with increasing l when a <= b <= c <= d
// C(a, c) + C(b, d) is more optimal than C(a, d) + C(b, c)

//summations : atmost O(sqrt(N)) unique elemnents in a set which sums to N
// for nsqrt(n)/32
/*
split all elements into groups of (w_i, occ_i)
for each w_i, its occurences can be split into new groups of the form (w_i, 1), (2w_i, 1), (4w_i, 1), etc and 
last might not be a power of two * w_i but thats okay. (for example (w_i, 12) splits to (w_i, 1) (2w_i, 1)
, (4wi, 1), (5w_i, 1))

now, the number of groups will be O(sqrt(C)) (not sqrt(C) log(C)!!!) where C is the total sum, and each group will have occurences = 1

finally, just do the ((elements) * (sum))/32 bitset dp
*/
---------------
// modint bs
// aarghhhh remember that for fucking exclusion from a group product, you cant
// just use negation by dividing, so you gotta use pre + suf or sqrt

---------------
// primes:
2, 11, 101, 1009, 10007, 100019, 100043, 1000003, 10000019, 100000007, 1000000007, 10000000019,
22371641, 223299231, 223857, 216091791, 427302833, 314533331, 747159897, 406492001

---------------
// Ternary Search
// finding maxima in unimodal function in O(logN)
double ternary_search(double l, double r) {
    //set the error limit here
    // number of iterations and error are directly related,
    // you can also stop the algorithm by bounding the number 
    // of iterations instead of the r - l > eps condition
    // (200 - 300 iterations are generally enough) 
    // iterations are independent of l and r
    double eps = 1e-9;              
    while (r - l > eps) {
        double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        //evaluates the function at m1 and m2
        double f1 = f(m1), f2 = f(m2);
        if (f1 < f2)    l = m1;
        else    r = m2;
    }
    return f(l);                    //return the maximum of f(x) in [l, r]
}
//for ternary searching on an integer number line, you just need to divide 
// [l, r] into three approximately equal parts, and stop when (r - l) < 3
// at this point, just check all the values in [l, r] manually

---
__builtin_clz(x): the number of zeros at the beginning of the number
__builtin_ctz(x): the number of zeros at the end of the number
__builtin_popcount(x): the number of ones in the number
__builtin_parity(x): the parity (even or odd) of the number of ones
fill(start_iterator, end_iterator, val) fills val in [start_iterator, end_iterator);
copy(start_iterator, end_iterator, result) copies [start_iterator, end_iterator) into result....

---
1. Euler path : path that traverses each edge exactly once
2. Euler cycle: an euler path which starts and ends at the same node
Necessary and sufficient conditions:
1. Euler path : connected graph, only two nodes have odd degrees (these end up becoming start, end)
2. Euler cycle: connected graph, all nodes have even degrees
Pseudo code for finding euler path/cycle:
stack St;
put start vertex in St;
until St is empty
  let V be the value at the top of St;
  if degree(V) = 0, then
    add V to the answer;
    remove V from the top of St;
  otherwise
    find any edge coming out of V;
    remove it from the graph;
    put the second end of this edge in St;

---
//Random Results
/*
"Konigs Theorem": In a bipartite graph, size of MVC = size of Max Matching

"Erdős-Ginzburg-Ziv" theorem:
From any set S of (2n - 1) integers, you can always choose a subset P of n integers, such that the sum of all integers in it is divisible by n." 

"Bertrand-Chebyshev Theorem": There is always atleast one prime p lying in (n, 2n] for all n.

"Erdos-Szekeres Theorem":
In any array (assume that we have permutation of n distinct integers for simplicity), we must have atleast one of the following: 
1. An increasing subsequence of length (>= sqrt(n)).
2. A decreasing subsequence of length (>= sqrt(n)).

Expected number of times pref max changes in randomly shuffled array is O(log(n))

"Four square theorem": Any non-negative integer can be expressed as the sum of 4 squares
*/

---
// Dynamic insertions in offline built data structures:
/* Simply maintain one based for every bit in binary representation of total number of elements and merge updwards as number of elements
 changes, note that you finally have to unite O(log(n)) query answers */

---
//Variable Length Bitsets:
template <int len = 1>
void solve(int n) {
    if (n > len) {
        solve<std::min(len*2, MAXLEN)>(n);
        return;
    }
    // solution using bitset<len>
}

---
