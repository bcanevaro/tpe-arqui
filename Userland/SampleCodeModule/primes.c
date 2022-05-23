#include <syscalls.h>
#include <libc.h>

int stop_primes = 0;
int last_prime = 1;

int get_next_prime();

void primes() {
    while (!stop_primes) {
        int p = get_next_prime();
        int length = num_length(p);
        char str[length + 1];
        num_to_str(p, str, length);
        write(1, str, length + 1);
        write(1, " ", 1);
        sleep(1);
    }
}

int get_next_prime() {
    int found = 0;
    for (int i = last_prime + 1; !found; i++) {
        int divisible = 0;
        for (int j = 1; j <= i; j++) {
            if (i % j == 0) {
                divisible++;
            }
        }
        if (divisible == 2) {
            found = 1;
            last_prime = i;
        }
    }
    return last_prime;
}