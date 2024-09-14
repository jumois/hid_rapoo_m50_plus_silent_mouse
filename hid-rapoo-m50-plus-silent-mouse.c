// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * HID driver for Rapoo M50 Plus Silent Mouse
 *
 * Cloned from HID driver for Xiaomi Silent Mouse
 *
 *  Copyright (c) 2021 Dr. Galambos Máté
 */

/*
 */

#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>

#define RAPOO_FAULT_OFFSET	17

static const __u8 rapoo_m50_faulty_rdesc[] = {
   0x05, 0x01,                    // Usage Page (Generic Desktop)        0
   0x09, 0x02,                    // Usage (Mouse)                       2
   0xa1, 0x01,                    // Collection (Application)            4
   0x85, 0x01,                    //  Report ID (1)                      6
   0x09, 0x01,                    //  Usage (Pointer)                    8
   0xa1, 0x00,                    //  Collection (Physical)              10
   0x05, 0x09,                    //   Usage Page (Button)               12
   0x19, 0x01,                    //   Usage Minimum (1)                 14
   0x29, 0x03,                    //   Usage Maximum (3)                 16  FAULTY
// 0x15, 0x00,                    //   Logical Minimum (0)               18
// 0x25, 0x01,                    //   Logical Maximum (1)               20
// 0x75, 0x01,                    //   Report Size (1)                   22
// 0x95, 0x05,                    //   Report Count (5)                  24
// 0x81, 0x02,                    //   Input (Data,Var,Abs)              26
// 0x75, 0x03,                    //   Report Size (3)                   28
// 0x95, 0x01,                    //   Report Count (1)                  30
// 0x81, 0x01,                    //   Input (Cnst,Arr,Abs)              32
// 0x05, 0x01,                    //   Usage Page (Generic Desktop)      34
// 0x09, 0x30,                    //   Usage (X)                         36
// 0x09, 0x31,                    //   Usage (Y)                         38
// 0x16, 0x01, 0x80,              //   Logical Minimum (-32767)          40
// 0x26, 0xff, 0x7f,              //   Logical Maximum (32767)           43
// 0x75, 0x10,                    //   Report Size (16)                  46
// 0x95, 0x02,                    //   Report Count (2)                  48
// 0x81, 0x06,                    //   Input (Data,Var,Rel)              50
// 0x09, 0x38,                    //   Usage (Wheel)                     52
// 0x15, 0x81,                    //   Logical Minimum (-127)            54
// 0x25, 0x7f,                    //   Logical Maximum (127)             56
// 0x75, 0x08,                    //   Report Size (8)                   58
// 0x95, 0x01,                    //   Report Count (1)                  60
// 0x81, 0x06,                    //   Input (Data,Var,Rel)              62
// 0xc0,                          //  End Collection                     64
// 0xc0,                          // End Collection                      65
// 0x05, 0x0c,                    // Usage Page (Consumer Devices)       66
// 0x09, 0x01,                    // Usage (Consumer Control)            68
// 0xa1, 0x01,                    // Collection (Application)            70
// 0x85, 0x02,                    //  Report ID (2)                      72
// 0x75, 0x10,                    //  Report Size (16)                   74
// 0x95, 0x01,                    //  Report Count (1)                   76
// 0x15, 0x01,                    //  Logical Minimum (1)                78
// 0x26, 0x8c, 0x02,              //  Logical Maximum (652)              80
// 0x19, 0x01,                    //  Usage Minimum (1)                  83
// 0x2a, 0x8c, 0x02,              //  Usage Maximum (652)                85
// 0x81, 0x00,                    //  Input (Data,Arr,Abs)               88
// 0xc0,                          // End Collection                      90
// 0x05, 0x01,                    // Usage Page (Generic Desktop)        91
// 0x09, 0x80,                    // Usage (System Control)              93
// 0xa1, 0x01,                    // Collection (Application)            95
// 0x85, 0x03,                    //  Report ID (3)                      97
// 0x09, 0x82,                    //  Usage (System Sleep)               99
// 0x09, 0x81,                    //  Usage (System Power Down)          101
// 0x09, 0x83,                    //  Usage (System Wake Up)             103
// 0x15, 0x00,                    //  Logical Minimum (0)                105
// 0x25, 0x01,                    //  Logical Maximum (1)                107
// 0x19, 0x01,                    //  Usage Minimum (1)                  109
// 0x29, 0x03,                    //  Usage Maximum (3)                  111
// 0x75, 0x01,                    //  Report Size (1)                    113
// 0x95, 0x03,                    //  Report Count (3)                   115
// 0x81, 0x02,                    //  Input (Data,Var,Abs)               117
// 0x95, 0x05,                    //  Report Count (5)                   119
// 0x81, 0x01,                    //  Input (Cnst,Arr,Abs)               121
// 0xc0,                          // End Collection                      123
// 0x05, 0x01,                    // Usage Page (Generic Desktop)        124
// 0x09, 0x00,                    // Usage (Undefined)                   126
// 0xa1, 0x01,                    // Collection (Application)            128
// 0x85, 0x05,                    //  Report ID (5)                      130
// 0x06, 0x00, 0xff,              //  Usage Page (Vendor Defined Page 1) 132
// 0x09, 0x01,                    //  Usage (Vendor Usage 1)             135
// 0x15, 0x81,                    //  Logical Minimum (-127)             137
// 0x25, 0x7f,                    //  Logical Maximum (127)              139
// 0x75, 0x08,                    //  Report Size (8)                    141
// 0x95, 0x07,                    //  Report Count (7)                   143
// 0xb1, 0x02,                    //  Feature (Data,Var,Abs)             145
// 0xc0,                          // End Collection                      147
// 0x06, 0x00, 0xff,              // Usage Page (Vendor Defined Page 1)  148
// 0x09, 0x0e,                    // Usage (Vendor Usage 0x0e)           151
// 0xa1, 0x01,                    // Collection (Application)            153
// 0x85, 0xba,                    //  Report ID (186)                    155
// 0x95, 0x1f,                    //  Report Count (31)                  157
// 0x75, 0x08,                    //  Report Size (8)                    159
// 0x26, 0xff, 0x00,              //  Logical Maximum (255)              161
// 0x15, 0x00,                    //  Logical Minimum (0)                164
// 0x09, 0x01,                    //  Usage (Vendor Usage 1)             166
// 0x91, 0x02,                    //  Output (Data,Var,Abs)              168
// 0x85, 0xba,                    //  Report ID (186)                    170
// 0x95, 0x1f,                    //  Report Count (31)                  172
// 0x75, 0x08,                    //  Report Size (8)                    174
// 0x26, 0xff, 0x00,              //  Logical Maximum (255)              176
// 0x15, 0x00,                    //  Logical Minimum (0)                179
// 0x09, 0x01,                    //  Usage (Vendor Usage 1)             181
// 0x81, 0x02,                    //  Input (Data,Var,Abs)               183
// 0xc0,                          // End Collection                      185
};

/*
 * we fix the report descriptor by setting byte 17 (Usage Maximum (3)) to 5
 */

static __u8 *rapoo_m50_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
//  Check if the start of the report maches our expectations
    if(memcmp(rdesc, rapoo_m50_faulty_rdesc, RAPOO_FAULT_OFFSET) != 0) return rdesc;
    rdesc[RAPOO_FAULT_OFFSET] = 0x05;
	return rdesc;
}

static const struct hid_device_id rapoo_m50_mouse_devices[] = {
	{ HID_USB_DEVICE(0x24ae, 0x2015) },
	{ }
};
MODULE_DEVICE_TABLE(hid, rapoo_m50_mouse_devices);

static struct hid_driver rapoo_m50_mouse_driver = {
	.name = "rapoo-m50-plus-silent-mouse",
	.id_table = rapoo_m50_mouse_devices,
	.report_fixup = rapoo_m50_report_fixup,
};
module_hid_driver(rapoo_m50_mouse_driver);

MODULE_DESCRIPTION("HID Rapoo M50 Plus Silent Mouse driver");
MODULE_LICENSE("GPL");
