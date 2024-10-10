#ifndef __TIME_H__
#define __TIME_H__	1

#ifdef __cplusplus
extern "C" {
#endif

struct timespec {
    unsigned long tv_sec; // seconds
    long tv_nsec; // nanoseconds
};

int nanosleep(const struct timespec *requested_time, struct timespec *remaining);

#ifdef __cplusplus
}
#endif

#endif
