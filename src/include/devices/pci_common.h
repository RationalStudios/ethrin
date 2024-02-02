#ifndef PCI_COMMON
#define PCI_COMMON
#include <devices/pci.h>
#include <stddef.h>
#include <stdint.h>
uint16_t pci_get_vendor_id(uint8_t bus, uint8_t device, uint8_t function);
uint16_t pci_get_device_id(uint8_t bus, uint8_t device, uint8_t function);
uint16_t pci_get_command(uint8_t bus, uint8_t device, uint8_t function);
uint16_t pci_get_status(uint8_t bus, uint8_t device, uint8_t function);
uint8_t pci_get_revision_id(uint8_t bus, uint8_t device, uint8_t function);
uint8_t pci_get_prog_if(uint8_t bus, uint8_t device, uint8_t function);
uint8_t pci_get_subclass_code(uint8_t bus, uint8_t device, uint8_t function);
uint8_t pci_get_class_code(uint8_t bus, uint8_t device, uint8_t function);
uint8_t pci_get_cache_line_size(uint8_t bus, uint8_t device, uint8_t function);
uint8_t pci_get_latency_timer(uint8_t bus, uint8_t device, uint8_t function);
uint8_t pci_get_header_type(uint8_t bus, uint8_t device, uint8_t function);
uint8_t pci_get_bist(uint8_t bus, uint8_t device, uint8_t function);
#endif