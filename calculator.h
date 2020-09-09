#ifndef __CALCULATOR_H__ 
#define __CALCULATOR_H__

typedef enum {STAT_SUCCESS, STAT_FAIL} status_t;

status_t Calculator(const char *expression, double *res);

#endif