#include <tables/idt.h>
#include <memset/memset.h>
#include <notify/notify.h>
struct idt_entry idt[256];
struct idt_ptr  idtp;

//Sets an entry in the interrupt descriptor table
void idt_set_gate(unsigned char num, unsigned long base, unsigned short seg_sel, unsigned char flags)
{
    //Split the base into 16 bits for low and high
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    //Always 0 is always 0
    idt[num].always0 = 0;
    //Set the kernel select segment
    idt[num].select_segment = seg_sel;
    //And the flags
    idt[num].flags = flags;
}

//Initializes IDT
void init_idt()
{
    notify("Initializing IDT...");
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int) &idt;
    idt_set_gate(0, (unsigned int) isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned int) isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned int) isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned int) isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned int) isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned int) isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned int) isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned int) isr7, 0x08, 0x8E);
    idt_set_gate(8, (unsigned int) isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned int) isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned int) isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned int) isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned int) isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned int) isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned int) isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned int) isr15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned int) isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned int) isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned int) isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned int) isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned int) isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned int) isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned int) isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned int) isr23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned int) isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned int) isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned int) isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned int) isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned int) isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned int) isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned int) isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned int) isr31, 0x08, 0x8E);
    memset(&idt, 0, sizeof(struct idt_entry) * 256);
    idt_load();
    notify("IDT initialized");
}