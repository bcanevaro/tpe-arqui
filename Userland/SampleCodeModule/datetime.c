#include <syscalls.h>
#include <libc.h>

void datetime(){
    uint64_t realtime[6];
	uint64_t minutes;
	uint64_t seconds;
    system_datetime(realtime, minutes, seconds);
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
    write(1, str_day, strlen(str_day));
    write(1, "-", 1);
    write(1, str_month, strlen(str_month));
    write(1, "-", 1);
    write(1, str_year, strlen(str_year));
    write(1, "\t", 1);
    write(1, str_hours, strlen(str_hours));
    write(1, ":", 1);
    write(1, str_minutes, strlen(str_minutes));
    write(1, ":", 1);
    write(1, str_seconds, strlen(str_seconds));
    write(1, "\n", 1);
    return;
}