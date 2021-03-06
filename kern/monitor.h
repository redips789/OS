// monitor.h -- Defines the interface for monitor.h
//              From JamesM's kernel development tutorials.

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void spausdinti(char *c);
void spausdinti_number(u32int val, u32int base);

void write_message_and_wait(char *c);

void monitor_put_color(char c, u8int foreColour);
void spausdinti_color(char *c, u8int foreColour);

#endif // MONITOR_H
