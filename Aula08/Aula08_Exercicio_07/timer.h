/**
*	@file timer.h
*
*	@author Rafael B. Januzi
*	@date 14/03/2018
*
*	@brief This module contains some utility timer functions
*/

#ifndef _TIMER_H
#define _TIMER_H

#include <stdlib.h>
#include <sys/time.h>

void timer_start();
unsigned long long timer_mStop();
unsigned long long timer_uStop();

#endif /* _TIMER_H */


