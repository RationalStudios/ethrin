#include <devices/pci_common.h>
#include <devices/pci_default.h>
#include <notify/notify.h>
//A list of all discovered pci devices
struct pci_device *pci_devices;

struct pci_device *get_device(uint8_t vendor_id, uint8_t device_id)
{
    struct pci_device *mock_list = pci_devices;
    while(mock_list->next)
    {
        mock_list = mock_list->next;
        if(mock_list->vendor_id == vendor_id && mock_list->device_id == device_id)
            return mock_list;
    }
    return NULL;
}

uint16_t get_config_first_word(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset)
{
    uint32_t lbus = (uint32_t) bus;
    uint32_t ldevice = (uint32_t) device;
    uint32_t lfunction = (uint32_t) function;
    uint32_t address = (uint32_t) ((lbus << 16) | (ldevice << 11) |
        (lfunction << 8) | (offset & 0xfc) | ((uint32_t) 0x80000000));
    outl(0xCF8, address);
    return (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
}

uint8_t pci_get_secondary_bus(uint8_t bus, uint8_t device, uint8_t function)
{
    //Get secondary bus
    return get_config_first_word(bus, device, function, SECONDARY_BUS_OFFSET);
}

struct pci_device *build_device(uint8_t bus, uint8_t device, uint8_t function)
{
    struct pci_device *pci = (struct pci_device *) malloc(sizeof(struct pci_device));
    pci->bus = bus;
    pci->device = device;
    pci->function = function;
    pci->device_id = pci_get_device_id(bus, device, function);
    pci->vendor_id = pci_get_vendor_id(bus, device, function);
    pci->class_code = pci_get_class_code(bus, device, function);
    pci->subclass_code = pci_get_subclass_code(bus, device, function);
    pci->cache_line_size = pci_get_cache_line_size(bus, device, function);
    pci->latency_timer = pci_get_latency_timer(bus, device, function);
    pci->header_type = pci_get_header_type(bus, device, function);
    pci->bist = pci_get_header_type(bus, device, function);
    return pci;
}

void scan_function(uint8_t bus, uint8_t device, uint8_t function)
{
    uint8_t class_code = pci_get_class_code(bus, device, function);
    uint8_t subclass = pci_get_subclass_code(bus, device, function);
    uint8_t header_type = pci_get_header_type(bus, device, function);
    
    if(HEADER_TYPE_DEFAULT(header_type))
    {
        //Build a PCI structure
        struct pci_device *pci = build_device(bus, device, function);
        pci->bar_0 = pci_get_bar_0(bus, device, function);
        pci->bar_1 = pci_get_bar_1(bus, device, function);
        pci->bar_2 = pci_get_bar_2(bus, device, function);
        pci->bar_3 = pci_get_bar_3(bus, device, function);
        pci->bar_4 = pci_get_bar_4(bus, device, function);
        pci->bar_5 = pci_get_bar_5(bus, device, function);
        pci_devices->next = pci;
        pci->prev = pci_devices;
        pci_devices = pci;
        notify("Found regular PCI device");
    }
    if(IS_PCI_TO_PCI_BRIDGE(class_code, subclass))
    {
        //Get the secondary bus
        uint8_t secondary_bus = pci_get_secondary_bus(bus, device, function);
        //Scan the secondary bus
        scan_bus(secondary_bus);
    }

}

void scan_device(uint8_t bus, uint8_t device)
{
    uint8_t function = 0;
    uint16_t vendor_id = pci_get_device_id(bus, device, function);
    if(vendor_id == FLOATING_BUS_STATE)
        return;
    
    //Get header type
    uint8_t header_type = pci_get_header_type(bus, device, function);
    //Check if device is multi function
    if((header_type & 0x80) != 0)
    {
        notify("Discovered multifunction device, iterating...");
        //Loop through functions
        for(function = 1; function < 8; function++)
        {
            //Check if vendor id is not nothing
            if(pci_get_vendor_id(bus, device, function) != FLOATING_BUS_STATE)
            {
                //Scan the current function
                scan_function(bus, device, function);
            }
        }
    }
    else
    {
        //Scan this function
        scan_function(bus, device, function);
    }
    
}

void scan_bus(uint8_t bus)
{
    //Get all devices
    for(uint8_t device = 0; device < 32; device++)
    {
        //Scan the device
        scan_device(bus, device);
    }
}

void initialize_pci_devices() 
{
    notify("Initializing PCI driver...");
    //Scan first bus
    scan_bus(0);
	return;
}