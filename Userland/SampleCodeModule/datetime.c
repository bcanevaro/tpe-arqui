#include <syscalls.h>
#include <libc.h>

void datetime(unsigned int fd) {
    uint64_t realtime[6];
    system_datetime(realtime);
    // TODO -> tener en cuenta los días y eso.
    if(realtime[2] >= 0 && realtime[2] <= 2){
        realtime[2] += 21;
    }else{
        realtime[2] -= 3;
    }
    int seconds_len = num_length(realtime[0]);
    int minutes_len = num_length(realtime[1]);
    int hours_len = num_length(realtime[2]);
    int day_len = num_length(realtime[3]);
    int month_len = num_length(realtime[4]);
    int year_len = num_length(realtime[5]);
    char str_hours[hours_len];
    char str_minutes[minutes_len];
    char str_seconds[seconds_len];
    char str_day[day_len];
    char str_month[month_len];
    char str_year[year_len];
    num_to_str(realtime[0], str_seconds, seconds_len);
    num_to_str(realtime[1], str_minutes, minutes_len);
    num_to_str(realtime[2], str_hours, hours_len);
    num_to_str(realtime[3], str_day, day_len);
    num_to_str(realtime[4], str_month, month_len);
    num_to_str(realtime[5], str_year, year_len);
    write(fd, str_day, strlen(str_day));
    write(fd, "-", 1);
    write(fd, str_month, strlen(str_month));
    write(fd, "-", 1);
    write(fd, str_year, strlen(str_year));
    write(fd, "\t", 1);
    write(fd, str_hours, strlen(str_hours));
    write(fd, ":", 1);
    write(fd, str_minutes, strlen(str_minutes));
    write(fd, ":", 1);
    write(fd, str_seconds, strlen(str_seconds));
    write(fd, "\n", 1);
    return;
}