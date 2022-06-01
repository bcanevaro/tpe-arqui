#include <syscalls.h>
#include <libc.h>

static char prime_no[] = "Prime No ";
static int prime_no_len = 9;
static char equal[] = " = ";
static int equal_len = 3;

int get_next_prime(int last_prime);

void primes(unsigned int fd) {
    int last_prime = 1;
    int counter = 1;
    while (1) {
        last_prime = get_next_prime(last_prime);
        int length = num_length(last_prime);
        char str[length + 1];
        num_to_str(last_prime, str, length);

        int counter_length = num_length(counter);
        char counter_str[counter_length + 1];
        num_to_str(counter, counter_str, counter_length + 1);

        write(fd, prime_no, prime_no_len);
        write(fd, counter_str, counter_length);
        write(fd, equal, equal_len);
        write(fd, str, length + 1);
        write(fd, "\n", 1);

        counter++;
        // sleep(1);
    }
}

int get_next_prime(int last_prime) {
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