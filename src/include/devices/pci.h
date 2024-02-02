#ifndef PCI_H
#define PCI_H
#include <stdint.h>
#include <stddef.h>
#include <malloc/malloc.h>
#include <sys/portio.hpp>
#define FLOATING_BUS_STATE  0xFFFF

/*Offsets*/
//General device information
#define VENDOR_ID_OFFSET    0
#define DEVICE_ID_OFFSET    2

//Command and status information
#define COMMAND_OFFSET      4
#define STATUS_OFFSET       6

//Revisions, class codes, etc
#define REVISION_OFFSET     8
#define PROG_IF_OFFSET      9
#define SUBCLASS_OFFSET     10
#define CLASS_CODE_OFFSET   11

//Cache size, latency, and more
#define CACHE_LINE_OFFSET   12
#define LATENCY_OFFSET      13
#define HEADER_TYPE_OFFSET  14
#define BIST_OFFSET         15


//PCI-to-PCI bridge
#define PRIMARY_BUS_OFFSET      18
#define SECONDARY_BUS_OFFSET    19
/*For scanning*/
#define HEADER_TYPE_DEFAULT(HEADER_TYPE) (HEADER_TYPE == 0x00)
#define HEADER_TYPE_PCI_BUS(HEADER_TYPE) (HEADER_TYPE == 0x01)
#define HEADER_TYPE_PCI_CARDBUS(HEADER_TYPE) (HEADER_TYPE == 0x02)
#define IS_PCI_TO_PCI_BRIDGE(CLASS_CODE,SUBCLASS) ((CLASS_CODE == 0x06) && (SUBCLASS == 0x04))
struct pci_device
{
    //Bus, device, and function
    uint8_t bus, device = 0, function = 0;

    //Device and vendor id
    uint8_t device_id = FLOATING_BUS_STATE, vendor_id = FLOATING_BUS_STATE;

    //Class and subclass code
    uint8_t class_code = FLOATING_BUS_STATE, subclass_code = FLOATING_BUS_STATE;

    //Cache line size, latency, header, and bist
    uint8_t cache_line_size = FLOATING_BUS_STATE, latency_timer = FLOATING_BUS_STATE, header_type = FLOATING_BUS_STATE, bist = FLOATING_BUS_STATE;
    
    //BAR0 to BAR5
    uint32_t bar_0 = FLOATING_BUS_STATE, bar_1 = FLOATING_BUS_STATE,  bar_2 = FLOATING_BUS_STATE,  bar_3 = FLOATING_BUS_STATE,  bar_4 = FLOATING_BUS_STATE,  bar_5 = FLOATING_BUS_STATE;
    struct pci_device *next = NULL;
    struct pci_device *prev = NULL;
};
struct pci_device *get_device(uint8_t vendor_id, uint8_t device_id);
uint16_t get_config_first_word(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset);
uint8_t pci_get_secondary_bus(uint8_t bus, uint8_t device, uint8_t function);
struct pci_device *build_device(uint8_t bus, uint8_t device, uint8_t function);
void scan_function(uint8_t bus, uint8_t device, uint8_t function);
void scan_device(uint8_t bus, uint8_t device);
void scan_bus(uint8_t bus);
void initialize_pci_devices();
#endif
