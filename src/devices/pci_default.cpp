#include <devices/pci_default.h>

uint32_t pci_get_bar_0(uint8_t bus, uint8_t device, uint8_t function)
{
    //Read BAR 0
    return (uint32_t)(get_config_first_word(bus, device, function, BAR_0_OFFSET));
}

uint32_t pci_get_bar_1(uint8_t bus, uint8_t device, uint8_t function)
{
    //Read BAR 0
    return (uint32_t)(get_config_first_word(bus, device, function, BAR_1_OFFSET));
}

uint32_t pci_get_bar_2(uint8_t bus, uint8_t device, uint8_t function)
{
    //Read BAR 0
    return (uint32_t)(get_config_first_word(bus, device, function, BAR_2_OFFSET));
}

uint32_t pci_get_bar_3(uint8_t bus, uint8_t device, uint8_t function)
{
    //Read BAR 0
    return (uint32_t)(get_config_first_word(bus, device, function, BAR_3_OFFSET));
}

uint32_t pci_get_bar_4(uint8_t bus, uint8_t device, uint8_t function)
{
    //Read BAR 0
    return (uint32_t)(get_config_first_word(bus, device, function, BAR_4_OFFSET));
}

uint32_t pci_get_bar_5(uint8_t bus, uint8_t device, uint8_t function)
{
    //Read BAR 0
    return (uint32_t)(get_config_first_word(bus, device, function, BAR_5_OFFSET));
}