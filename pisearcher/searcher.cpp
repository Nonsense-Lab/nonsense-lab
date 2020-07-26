/**
 * A HUUUUUUUUUUGE THANKS TO STACKOVERFLOW!
 * WHAT A SAVIOR (*Tears*)
 * https://stackoverflow.com/questions/5905822/function-to-find-the-nth-digit-of-pi
 */

/**
 * Computation of the n'th decimal digit of \pi with very little memory.
 * Written by Fabrice Bellard on January 8, 1997.
 *
 * We use a slightly modified version of the method described by
 * Simon Plouffe in "On the Computation of the n'th decimal digit of
 * various transcendental numbers" (November 1996). We have modified
 * the algorithm to get a running time of O(n^2) instead of O(n^3log(n)^3).
 *
 * This program uses mostly integer arithmetic. It may be slow
 * on some hardwares where integer multiplications and divisions must
 * be done by software. We have supposed that 'int' has a size of 32 bits.
 * If your compiler supports 'long long' integers of 64 bits, you
 * may use the integer version of 'mul_mod' (see HAS_LONG_LONG).
 */

// [[INCLUDE START
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <cmath>
#include <sstream>
#include <cstring>
using namespace std;
// ]]

/********** STACKOVERFLOW CODEBLOCK START **********/
#define HAS_LONG_LONG

#ifdef HAS_LONG_LONG
#define mul_mod(a,b,m) (( (long long) (a) * (long long) (b) ) % (m))
#endif

/* Returns the inverse of x MOD y */
int inv_mod(int x, int y) {
    int q, u, v, a, c, t;
    u = x;
    v = y;
    c = 1;
    a = 0;
    do {
        q = v / u;
        t = c;
        c = a - q * c;
        a = t;
        t = u;
        u = v - q * u;
        v = t;
    } while (u != 0);
    a = a % y;
    if (a < 0) a = y + a;
    return a;
}

/* Returns (a ^ b) MOD m */
int pow_mod(int a, int b, int m) {
    int r, aa;
    r = 1;
    aa = a;
    while (true) {
        if (b & 1) {
            r = mul_mod(r, aa, m);
        }
        b = b >> 1;
        if (b == 0) {
            break;
        }
        aa = mul_mod(aa, aa, m);
    }
    return r;
}

/* Returns true if n is prime */
bool is_prime(int n) {
    int r, i;
    if ((n % 2) == 0) return false;

    r = (int) (sqrt(n));
    for (i = 3; i <= r; i += 2) {
        if ((n % i) == 0) {
            return 0;
        }
    }
    return 1;
}

/* Returns the prime number immediately after n */
int next_prime(int n) {
    do {
        n++;
    } while (!is_prime(n));
    return n;
}

/********** ORIGINAL STACKOVERFLOW END **********/
/********** MODIFIED STACKOVERFLOW SOLUTION main() START **********/

double summ(int Input_N) {
    int av, a, vmax, N, n, num, den, k, kq, kq2, t, v, s, i;
    double sum;

    n = Input_N;

    N = (int) ((n + 20) * log(10) / log(2));

    sum = 0;

    for (a = 3; a <= (2 * N); a = next_prime(a)) {

    vmax = (int) (log(2 * N) / log(a));
    av = 1;
    for (i = 0; i < vmax; i++)
        av = av * a;

    s = 0;
    num = 1;
    den = 1;
    v = 0;
    kq = 1;
    kq2 = 1;

    for (k = 1; k <= N; k++) {

        t = k;
        if (kq >= a) {
        do {
            t = t / a;
            v--;
        } while ((t % a) == 0);
        kq = 0;
        }
        kq++;
        num = mul_mod(num, t, av);

        t = (2 * k - 1);
        if (kq2 >= a) {
        if (kq2 == a) {
            do {
            t = t / a;
            v++;
            } while ((t % a) == 0);
        }
        kq2 -= a;
        }
        den = mul_mod(den, t, av);
        kq2 += 2;

        if (v > 0) {
        t = inv_mod(den, av);
        t = mul_mod(t, num, av);
        t = mul_mod(t, k, av);
        for (i = v; i < vmax; i++)
            t = mul_mod(t, a, av);
        s += t;
        if (s >= av)
            s -= av;
        }

    }

    t = pow_mod(10, n - 1, av);
    s = mul_mod(s, t, av);
    sum = fmod(sum + (double) s / (double) av, 1.0);
    }
    return sum;
}

bool MainFunction(int Input_N, string str, int& j, int I) {
    double sum = summ(Input_N);
    char* retptr = new char[str.size()+120];
    memset(retptr, 0, sizeof(retptr));
    if (Input_N == 1) sprintf(retptr, "3%09d", (int)(sum * 1e9));
    else
    sprintf(retptr, "%09d%09d", (int)(sum * 1e9), (int)(summ(Input_N + 1 * 9) * 1e9));
    if (str.size() >= strlen(retptr)) {
        for (int i = 1; i < (int)(str.size() / 9 ) + 10; i++) {
            sum = summ(Input_N + i * 9);
            sprintf(retptr+i*9+1,"%09d",(int)(sum * 1e9));
        }
    }
    printf("%s]",retptr);
    string rptr = (string)retptr;
    bool spp = false;
    for (int i = 0; i < rptr.size() - str.size(); i++) {
        string rpt = rptr.substr(i, str.size());
        if (rpt == str) {spp = true; break;}
        j=I+i;
    }

    if (Input_N % 500 == 0) {
            cout << "\rYou have tried " << Input_N << " times. Would you like to continue? [y/n]: ";
            char yn;
            cin >> yn;
            if (yn == 'n') exit(1);
            else cout << "\r";
    }

    return spp;
    /*
    string ptrf = "%";
    stringstream ss;

    if (Input_N == 1) { ss<<str.size()-1; ptrf += string("3")+ss.str()+string("d"); }
    else { ss<<str.size(); ptrf += ss.str()+string("d"); }
    sprintf(retptr, ptrf.c_str(), (int) (sum * 1e9));
    if (string(retptr) == str) return true;
    return false;*/
}

/********** main() Function Start **********/
int main(int argc, char** argv) {
    if (argc < 2) {
        const char* helpstr =
            "===== Help of PI Searcher (C++) =====\n"
            "Enter Nothing \t:\tShow HELP, ABOUT, and VERSION file.\n"
            "Enter a number\t:\tSearch your number in PI.\n"
            "=====  About PI Searcher (C++)  =====\n"
            "(c) 2020 Nonsense Lab <https://github.com/Nonsense-Lab>.\n"
            "PI Searcher is an application written in C++ which \n"
            "could help you search a specific number string in the first \n"
            "200M digits of PI.\n"
            "=====          Version          =====\n"
            "v0.0.1 alpha\n"
            "First commit on July 26, 2020.\n"
            "=====          Appendix         =====\n"
            "You certainly haven\'t noticed there are 10(11) spaces on the left and 11(10) spaces on the right\n"
            "of the title of the sections [Version] and [Appendix]\n"
            "(>wO)";
        printf("%s",helpstr);
        return 0;
    }
    time_t start = time(0);
    string searchstr = string(argv[1]);
    for (int i = 1; i < 20000000; i++) {
        cout << "\r" << i << ": Loading... => [";
        int j = 0;
        if (MainFunction(i, searchstr, j, i)) {
            printf("\nYour string %s is at the #%d digit in PI.", searchstr.c_str(), j);
            cout << "\nElapsed time: " << (time(0) - start) << " Second(s)" << endl;
            return 0;
        }
    }
    cout << "\nThere isn\'t the string you want to find in PI." << endl;
    return 0;
}
