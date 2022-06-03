#include <syscalls.h>
#include <libc.h>

void datetime(unsigned int fd) {
    uint64_t realtime[6];
    system_datetime(realtime);
    if(realtime[2] >= 0 && realtime[2] <= 2){
        realtime[2] += 21;
        if(realtime[3] > 1 && realtime[3] <= 31){
            realtime[3] -= 1;
        }
        if(realtime[3] == 1){
            if(realtime[4] == 1){
                realtime[3] = 31;
                realtime[4] = 12;
                realtime[5] -= 1;
            }else if(previous_is_large_month(realtime[4])){
                realtime[3] = 31;
                realtime[4]--;
            }else if(previous_is_short_month(realtime[4])){
                realtime[3] = 30;
                realtime[4]--;
            }else{
                if(is_a_leap_year(realtime[5])){
                    realtime[3] = 29;
                }else{
                    realtime[3] = 28;
                }
                realtime[4]--;
            }
        }
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

int previous_is_large_month(uint64_t month){
    if(month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11){
        return 1;
    }
    return 0;
}

int previous_is_short_month(uint64_t month){
    if(month == 5 || month == 7 || month == 10 || month == 12){
        return 1;
    }
    return 0;
}

int is_a_leap_year(uint64_t year){
    if (year % 400 == 0)
        return 1;
 
    if (year % 100 == 0)
        return 0;
 
    if (year % 4 == 0)
        return 1;
    return 0;
}