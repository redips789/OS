#ifndef _TASK_H_
#define _TASK_H_

#include "common.h"
#include "paging.h"

#define MAXITEMS 1000 
#define MAX_MESSAGES 1000
#define MAX_MESSAGE_LENGTH 100
typedef s32int pid_t;

typedef struct message {
  pid_t src; //the source process that sends the message
  pid_t dst; //the destination process that receives
  char* body; //the body of the message (usually holds type and arguments, it's up to you)
} message;

typedef struct circbuff {
  int head;  //index to queue start within buffer
  int tail;  //index to queue end within buffer
  int count; //number of elements in buff
  message buffer[MAXITEMS]; //buffer to hold messages
} buffer_t;

// represents a process
typedef struct task {
  pid_t id; // process id
  u32int esp, ebp; // stack and base ptrs
  u32int eip; // instruction pointer
  page_directory_t *page_directory;
  u32int state; // task state - runnable, sleeping, etc
  u32int quantum; // number of ticks remaining to the process
  enum {RUNNING, SUSPENDED} task_state;
  struct task *next; // next task on the list
  //char buffer[MAX_MESSAGES][MAX_MESSAGE_LENGTH];
  buffer_t messages_buffer;
} task_t;

void async_send(message msg);

message async_recv();

void initialize_tasking();

void switch_task();

pid_t fork();

// copy the current process's stack to a new location and update esp/ebp
void move_stack(void *new_stack_start, u32int size);

pid_t getpid();

task_t* getProcess(pid_t id);

void runFunctionAsync();

message pop_message(pid_t id);

message create_message(char* msg, pid_t src, pid_t dst);

void push_message(message msg);


#endif
