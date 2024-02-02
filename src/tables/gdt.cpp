#include <tables/gdt.h>
#include <memset/memset.h>
#include <notify/notify.h>

struct gdt_entry gdt[3];
struct gdt_ptr gdtp;
//Setup a descriptor in the GDT
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity)
{
    //Set the address
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFFFF;
    gdt[num].base_high = (base >> 24) & 0xFFFF;
    //Setup descriptor limits
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;
    //Setup granularity
    gdt[num].granularity |= (granularity & 0xF0);
    //Setup access
    gdt[num].access = access;
}

//Setup the GDT
void init_gdt()
{
    //We are intializing GDT
    notify("Initializing GDT...");
    //Setup GDT pointer and limit
    gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdtp.base = (unsigned int) &gdt;
    //Set the null descriptor
    gdt_set_gate(0, 0, 0, 0, 0);
    //Set the code segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    //Set the data segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    //Flush the old gdt
    gdt_flush();
    //GDT was initialized
    notify("GDT initialized successfully");
}