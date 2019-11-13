#include "pid.h"

#include "../../lib/uart/uart.h"

#define SCALING_FACTOR 128

#define U_MAX 255
#define U_MIN -255

#define MAX_I_TERM INT32_MAX / 2

static int16_t Kp, Ki, Kd, e0, max_error;
static int32_t sum_error, max_sum_error;


void pid_init( int16_t Kp_, int16_t Ki_, int16_t Kd_ )
{
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;

    sum_error = 0;
    max_error = INT16_MAX / (Kp + 1);
    max_sum_error = MAX_I_TERM / (Ki + 1);

    e0 = 0;
}


int16_t pid_update( int16_t ref, int16_t pos )
{
    int16_t error, p_term, d_term;
    int32_t i_term, temp;

    error = (pos - ref) / SCALING_FACTOR;

    if (error > max_error)
    {
        p_term = INT16_MAX;
    } else if (error < -max_error) 
    {
        p_term = -INT16_MAX;
    } else
    {
        p_term = Kp*error;
    }
    
    temp = sum_error + error;
    if (temp > max_sum_error)
    {
        i_term = MAX_I_TERM;
    } else if (temp < -max_sum_error)
    {
        i_term = -MAX_I_TERM;
    } else
    {
        i_term = Ki * sum_error;
    }
    
    
    
    
    d_term = (error - e0) * Kd;
    int16_t u = (p_term + i_term + d_term);

    e0 = error;

    if ( u < U_MIN ) { u = U_MIN; } 
    else if ( u > U_MAX ) { u = U_MAX; }

    //printf("%d\r\n", u);
    return u;
}