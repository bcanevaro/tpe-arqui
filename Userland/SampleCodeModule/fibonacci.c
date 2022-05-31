#include <syscalls.h>
#include <libc.h>

unsigned long long get_next_fibo(unsigned long long * ans, unsigned long long * ans_ans, unsigned long long * counter);

static char str1[] = "Fibonacci(";
static int str1_length = 10;
static char str2[] = ") = ";
static int str2_length = 4;
static char str3[] = "\n";
static int str3_length = 1;

void fibonacci(unsigned int fd) {
    unsigned long long ans_ans = 0;
    unsigned long long ans = 1;
    unsigned long long counter = 1;

    char fibo0[] = "Fibonacci(0) = 0\n";
    char fibo1[] = "Fibonacci(1) = 1\n";
    write(fd, fibo0, strlen(fibo0));
    // sleep(1);
    write(fd, fibo1, strlen(fibo1));
    // sleep(1);
    while (1) {
        unsigned long long f = get_next_fibo(&ans, &ans_ans, &counter);
        int length = num_length(f);
        char str[length + 1];
        num_to_str(f, str, length);

        int counter_length = num_length(counter);
        char counter_str[counter_length + 1];
        num_to_str(counter, counter_str, counter_length + 1);

        write(fd, str1, str1_length);
        write(fd, counter_str, counter_length);
        write(fd, str2, str2_length);
        write(fd, str, length + 1);
        write(fd, str3, str3_length);
        // sleep(1);
    }
}

unsigned long long get_next_fibo(unsigned long long * ans, unsigned long long * ans_ans, unsigned long long * counter) {
    unsigned long long to_return = *ans_ans + *ans;
    *ans_ans = *ans;
    *ans = to_return;
    *counter += 1;
    return to_return;
}