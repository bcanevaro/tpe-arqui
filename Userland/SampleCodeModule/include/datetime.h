#ifndef DATETIME_H

#define DATETIME_H
void datetime(unsigned int fd);
int previous_is_large_month(uint64_t month);
int previous_is_short_month(uint64_t month);
int is_a_leap_year(uint64_t year);
#endif