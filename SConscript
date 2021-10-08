Import('rtconfig')
from building import *

cwd     = GetCurrentDir()

USB_SRC = []
USB_PORT_SRC = []

INC = []
INC += [cwd + "/tinyusb/src"]

CPPDEFINES = []
CPPDEFINES += ['CFG_TUSB_OS=OPT_OS_RTTHREAD']

USB_DEVICE_SRC = Split('''
tinyusb/src/tusb.c
tinyusb/src/device/usbd.c
tinyusb/src/device/usbd_control.c
tinyusb/src/common/tusb_fifo.c
'''    
)

USB_HOST_SRC = Split('''
tinyusb/src/tusb.c
tinyusb/src/host/hub.c
tinyusb/src/host/usbh_control.c
tinyusb/src/common/tusb_fifo.c
tinyusb/src/host/usbh.c
'''
)

if GetDepend('PKG_USING_TINYUSB2RTT_MCU_NRF5X'):
    CPPDEFINES += ['CFG_TUSB_MCU=OPT_MCU_NRF5X']
    USB_PORT_SRC += Glob("tinyusb/src/portable/nordic/nrf5x/dcd_nrf5x.c")
    USB_PORT_SRC += Glob("ports/hw/bsp/nrf/family.c")

if GetDepend('PKG_USING_TINYUSB2RTT_USBD'):
    USB_SRC += USB_DEVICE_SRC
else:
    USB_SRC += USB_HOST_SRC

if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_CDC'):
    USB_SRC += Glob("tinyusb/src/class/cdc/cdc_device.c")
    USB_PORT_SRC += Glob("ports/examples/device/cdc_dual_ports/src/usb_main.c")
    USB_PORT_SRC += Glob("ports/examples/device/cdc_dual_ports/src/usb_descriptors.c")
    INC += [cwd + "/ports/examples/device/cdc_dual_ports/src"]

if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_AUDIO'):
    USB_SRC += Glob("tinyusb/src/class/audio/audio_device.c")
    USB_PORT_SRC += Glob("tinyusb/examples/device/audio_test/src/usb_descriptors.c")
    INC += [cwd + "/tinyusb/examples/device/audio_test/src"]
    
if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_DFU'):
    USB_SRC += Glob("tinyusb/src/class/dfu/dfu_device.c")
    USB_PORT_SRC += Glob("tinyusb/examples/device/dfu/src/usb_descriptors.c")
    INC += [cwd + "/tinyusb/examples/device/dfu/src"]
    
if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_DFU_RT'):
    USB_SRC += Glob("tinyusb/src/class/dfu/dfu_rt_device.c")
    USB_PORT_SRC += Glob("tinyusb/examples/device/dfu_runtime/src/usb_descriptors.c")
    INC += [cwd + "/tinyusb/examples/device/dfu_runtime/src"]
    
if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_HID'):
    USB_SRC += Glob("tinyusb/src/class/hid/hid_device.c")
    USB_PORT_SRC += Glob("tinyusb/examples/device/hid_boot_interface/src/usb_descriptors.c")
    INC += [cwd + "/tinyusb/examples/device/hid_boot_interface/src"]
    
if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_MIDI'):
    USB_SRC += Glob("tinyusb/src/class/midi/midi_device.c")
    USB_PORT_SRC += Glob("tinyusb/examples/device/midi_test/src/usb_descriptors.c")
    INC += [cwd + "/tinyusb/examples/device/midi_test/src"]
    
if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_MSC'):
    USB_SRC += Glob("tinyusb/src/class/msc/msc_device.c")
    USB_PORT_SRC += Glob("tinyusb/examples/device/msc_dual_lun/src/usb_descriptors.c")
    INC += [cwd + "/tinyusb/examples/device/msc_dual_lun/src"]
    
if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_NET'):
    USB_SRC += Glob("tinyusb/src/class/net/net_device.c")
    USB_PORT_SRC += Glob("tinyusb/examples/device/net_lwip_webserver/src/usb_descriptors.c")
    INC += [cwd + "/tinyusb/examples/device/net_lwip_webserver/src"]
    
if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_USBTMC'):
    USB_SRC += Glob("tinyusb/src/class/usbtmc/usbtmc_device.c")
    USB_PORT_SRC += Glob("tinyusb/examples/device/usbtmc/src/usb_descriptors.c")
    INC += [cwd + "/tinyusb/examples/device/usbtmc/src"]
    
if GetDepend('PKG_USING_TINYUSB2RTT_DEVICE_VENDOR'):
    USB_SRC += Glob("tinyusb/src/class/vendor/vendor_device.c")


group = DefineGroup('tinyusb2rtt/src' , USB_SRC, depend = ['PKG_USING_TINYUSB2RTT'], CPPPATH = INC, CPPDEFINES = CPPDEFINES)
group = DefineGroup('tinyusb2rtt/portable', USB_PORT_SRC  , depend = ['PKG_USING_TINYUSB2RTT'], CPPPATH = INC)

Return('group')
