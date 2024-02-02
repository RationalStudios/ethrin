#ifndef PCI_DEFAULT
#define PCI_DEFAULT
#include <devices/pci_common.h>
#define BAR_0_OFFSET    16
#define BAR_1_OFFSET    20
#define BAR_2_OFFSET    24
#define BAR_3_OFFSET    28
#define BAR_4_OFFSET    32
#define BAR_5_OFFSET    36
uint32_t pci_get_bar_0(uint8_t bus, uint8_t device, uint8_t function);
uint32_t pci_get_bar_1(uint8_t bus, uint8_t device, uint8_t function);
uint32_t pci_get_bar_2(uint8_t bus, uint8_t device, uint8_t function);
uint32_t pci_get_bar_3(uint8_t bus, uint8_t device, uint8_t function);
uint32_t pci_get_bar_4(uint8_t bus, uint8_t device, uint8_t function);
uint32_t pci_get_bar_5(uint8_t bus, uint8_t device, uint8_t function);
#endif