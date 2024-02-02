#include <devices/pci_common.h>

uint16_t pci_get_vendor_id(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get the vendor id
    return get_config_first_word(bus, device, function, VENDOR_ID_OFFSET);
}

uint16_t pci_get_device_id(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get the device id
    return get_config_first_word(bus, device, function, DEVICE_ID_OFFSET);
}

uint16_t pci_get_command(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get command
    return get_config_first_word(bus, device, function, COMMAND_OFFSET);
}

uint16_t pci_get_status(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get status
    return get_config_first_word(bus, device, function, STATUS_OFFSET);
}

uint8_t pci_get_revision_id(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get associated revision id
    return get_config_first_word(bus, device, function, REVISION_OFFSET);
}

uint8_t pci_get_prog_if(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get PROG IF
    return get_config_first_word(bus, device, function, PROG_IF_OFFSET);
}

uint8_t pci_get_subclass_code(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get subclass code
    return get_config_first_word(bus, device, function, SUBCLASS_OFFSET);
}

uint8_t pci_get_class_code(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get the class code
    return get_config_first_word(bus, device, function, CLASS_CODE_OFFSET);
}

uint8_t pci_get_cache_line_size(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get cache line size
    return get_config_first_word(bus, device, function, CACHE_LINE_OFFSET);
}

uint8_t pci_get_latency_timer(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get latency timer
    return get_config_first_word(bus, device, function, LATENCY_OFFSET);
}

uint8_t pci_get_header_type(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get the header type
    return get_config_first_word(bus, device, function, HEADER_TYPE_OFFSET);
}

uint8_t pci_get_bist(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get BIST
    return get_config_first_word(bus, device, function, BIST_OFFSET);
}
