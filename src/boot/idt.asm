
global idt_load:function
extern idtp
idt_load:
    lidt[idtp]
    ret
