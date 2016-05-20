/*
*  kernel.c
*/
#include "monitor.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "paging.h"
#include "kheap.h"
#include "task.h"

u32int initial_esp;




void task1() {
    int i=0;
    message msg_send;
    while (1) {
        spauzdinti("Task1");
        for (i = 0; i < 10000000; i++) {
            if (i % 10000000 == 0){
                spauzdinti(".");
            }   
        }
        msg_send = create_message("Task 1 send this message", 2, 3);
        async_send(msg_send);
        message msg_get = async_recv();
        spauzdinti_color("First task got message: ", 0x0A);
        spauzdinti(msg_get.body);
        spauzdinti("\n");
    }
}

void task2(){
    int i = 0;

    while(1){
        message msg_get = async_recv();
        spauzdinti_color("Second task got message: ", 0x0A);
        spauzdinti(msg_get.body);
        spauzdinti("\n");
	spauzdinti("Task2");
        for (i = 0; i < 10000000; i++) {
            if (i % 10000000 == 0){
                spauzdinti(".");
            }
        }

        message msg_send = create_message("Task 2 send this message", 3, 2);
        async_send(msg_send);    
    }
}


int kmain(struct multiboot *mboot_ptr, u32int initial_stack)
{
    initial_esp = initial_stack;
    spauzdinti_color(" OK ", 0x0A);
	
    init_descriptor_tables();
    spauzdinti_color(" OK ", 0x0A);
    
    monitor_clear();
    spauzdinti_color(" OK ", 0x0A);
   
    initialize_paging();
    spauzdinti_color(" OK ", 0x0A);
    
    initialize_tasking();
    spauzdinti_color(" OK ", 0x0A);

    //monitor_clear();
    spauzdinti("Success\n");

    asm volatile("sti");        // enable interrupts
    init_timer(10);
    runFunctionAsync(task1);

    runFunctionAsync(task2);

    //runFunctionAsync(task3);
  
    while(1){

    }
	return 0;
}


