
typedef char           int8_t;
typedef unsigned char		u_int8_t;
typedef short			int16_t;
typedef unsigned short		u_int16_t;
typedef int			int32_t;
typedef unsigned int		u_int32_t;
typedef long long		int64_t;
typedef unsigned long long	u_int64_t;

#if __LP64__
typedef int64_t			register_t;
#else
typedef int32_t			register_t;
#endif

typedef long			intptr_t;
typedef unsigned long		uintptr_t;

#if defined(__SIZE_TYPE__)
typedef __SIZE_TYPE__		size_t;        /* sizeof() */
#else
typedef unsigned long		size_t;        /* sizeof() */
#endif
typedef long			ssize_t;
#if defined(__PTRDIFF_TYPE__)
typedef __PTRDIFF_TYPE__	ptrdiff_t;     /* ptr1 - ptr2 */
#else
typedef int			ptrdiff_t;     /* ptr1 - ptr2 */
#endif
typedef int64_t     		off_t;
typedef long	 		time_t;
#define INFINITE_TIME 		0xffffffffUL

///////////////////////////////////////////////
// stdint.h
///////////////////////////////////////////////

/* from ISO/IEC 988:1999 spec */

/* 7.18.1.1 Exact-width integer types */
typedef u_int8_t              uint8_t;
typedef u_int16_t            uint16_t;
typedef u_int32_t            uint32_t;
typedef u_int64_t            uint64_t;

/* 7.18.2.1 Limits of exact-width integer types */
#define INT8_MIN         (-127-1)
#define INT16_MIN        (-32767-1)
#define INT32_MIN        (-2147483647-1)
#define INT64_MIN        (-9223372036854775807LL-1LL)

#define INT8_MAX         +127
#define INT16_MAX        +32767
#define INT32_MAX        +2147483647
#define INT64_MAX        +9223372036854775807LL

#define UINT8_MAX         255
#define UINT16_MAX        65535
#define UINT32_MAX        4294967295U
#define UINT64_MAX        18446744073709551615ULL

/* 7.18.2.4 Limits of integer types capable of holding object pointers */

#if __LP64__
#define INTPTR_MIN        INT64_MIN
#define INTPTR_MAX        INT64_MAX
#else
#define INTPTR_MIN        INT32_MIN
#define INTPTR_MAX        INT32_MAX
#endif

#if __LP64__
#define UINTPTR_MAX       UINT64_MAX
#else
#define UINTPTR_MAX       UINT32_MAX
#endif

/* 7.18.3 "Other" */
#if __LP64__
#define PTRDIFF_MIN       INT64_MIN
#define PTRDIFF_MAX       INT64_MAX
#else
#define PTRDIFF_MIN       INT32_MIN
#define PTRDIFF_MAX       INT32_MAX
#endif

#if __LP64__
#define SIZE_MAX          UINT64_MAX
#else
#define SIZE_MAX          UINT32_MAX
#endif

///////////////////////////////////////////////
// libkern/libkern/OSTypes.h
///////////////////////////////////////////////
typedef unsigned char		UInt8;
typedef unsigned short		UInt16;
typedef unsigned int		UInt32;
typedef unsigned long long	UInt64;

typedef signed char		SInt8;
typedef signed short		SInt16;
typedef signed int		SInt32;
typedef signed long long	SInt64;

typedef enum {
	kMemoryRegion_StorageProcessor,
	kMemoryRegion_ConsistentDebug,
	kMemoryRegion_SleepToken,
	kMemoryRegion_DramConfig,
	kMemoryRegion_Panic,
	kMemoryRegion_Display,
	kMemoryRegion_Heap,
	kMemoryRegion_Stacks,
	kMemoryRegion_PageTables,
	kMemoryRegion_iBoot,
	kMemoryRegion_Kernel,
	kMemoryRegion_Monitor,
	kMemoryRegion_SecureProcessor,
	kMemoryRegion_AOP,
	kMemoryRegion_Reconfig,
	kMemoryRegion_NumberOfRegions,
} memory_region_type_t;
struct usb_device_descriptor
{
    u_int8_t bLength;
    u_int8_t bDescriptorType;
    u_int16_t bcdUSB;
    u_int8_t bDeviceClass;
    u_int8_t bDeviceSubClass;
    u_int8_t bDeviceProtocol;
    u_int8_t bMaxPacketSize0;
    u_int16_t idVendor;
    u_int16_t idProduct;
    u_int16_t bcdDevice;
    u_int8_t iManufacturer;
    u_int8_t iProduct;
    u_int8_t iSerialNumber;
    u_int8_t bNumConfigurations;
} __attribute__((packed));

enum { kUSB_DP = 1, kUSB_DM = 2, kUSB_NONE = 0, kUSB_DCD = 3, kUSB_CP1 = 4, kUSB_CP2 = 5 };

typedef struct _CBUFFER {
  uint8_t   * head;
  uint8_t   * tail;
  size_t   size;
  size_t   readableSize;
  size_t    bufferSize;
  uint8_t   * dataStart;
  uint8_t   * dataEnd;
} CBUFFER;

struct list_node {
	struct list_node *prev;
	struct list_node *next;
};

enum target_property {
	TARGET_PROEPRTY_NONE = 0,
	TARGET_PROPERTY_WIFI_MACADDR,
	TARGET_PROPERTY_WIFI_CALIBRATION_TX,
	TARGET_PROPERTY_WIFI_CALIBRATION_TX_24,
	TARGET_PROPERTY_WIFI_CALIBRATION_TX_50,
	TARGET_PROPERTY_WIFI_CALIBRATION_RX_24,
	TARGET_PROPERTY_WIFI_CALIBRATION_RX_50,
	TARGET_PROPERTY_WIFI_CALIBRATION_RX_TEMP,
	TARGET_PROPERTY_WIFI_CALIBRATION_FREQ_GROUP_2G,
	TARGET_PROPERTY_WIFI_BOARD_SNUM,
	TARGET_PROPERTY_WIFI_WCAL,
	TARGET_PROPERTY_BT_MACADDR,
	TARGET_PROPERTY_ETH_MACADDR,
	TARGET_PROPERTY_BB_REGION_SKU,
	TARGET_PROPERTY_RESTORE_BACKLIGHT_LEVEL,
	TARGET_PROPERTY_PINTO_MACADDR,
	TARGET_PROPERTY_WIFI1_MACADDR,
	TARGET_PROPERTY_BT1_MACADDR,
	TARGET_PROPERTY_ETH1_MACADDR,
	TARGET_PROPERTY_BLUETOOTH_DEV_MACADDR0,
	TARGET_PROPERTY_MAX,
};

enum boot_target {
	BOOT_UNKNOWN = 0,
	BOOT_HALT,
	BOOT_IBOOT,
	BOOT_DARWIN,         // Darwin restore / boot
	BOOT_DARWIN_RESTORE, // resume from RAM
	BOOT_DIAGS,
	BOOT_TSYS,
	BOOT_SECUREROM,
	BOOT_MONITOR,
	BOOT_DALI,
};

/* boot devices */
enum boot_device {
     	BOOT_DEVICE_NOR = 0,
     	BOOT_DEVICE_SPI,
	BOOT_DEVICE_NAND,
	BOOT_DEVICE_NVME,
	BOOT_DEVICE_USBDFU,
	BOOT_DEVICE_TBTDFU,
	BOOT_DEVICE_XMODEM,
};


enum colorspace {
	CS_4BPP,
	CS_8BPP,
	CS_RGB332,
	CS_RGB565,
	CS_ARGB1555,
	CS_ARGB4444,
	CS_RGB888,
	CS_ARGB8888,
	CS_ARGB8101010,
};


struct syscfg_wpcl {
	u_int32_t	version;
	u_int32_t	red;
	u_int32_t	green;
	u_int32_t	blue;
};

union  syscfg_DCLr_RGB {
	u_int32_t	rgb;
	struct {
		u_int8_t	blue;
		u_int8_t	green;
		u_int8_t	red;
		u_int8_t	reserved;
	} component;
};

typedef struct syscfg_DClr {
	u_int8_t		minor_version;
	u_int8_t		major_version;
	u_int8_t		reserved_2;
	u_int8_t		reserved_3;

	union syscfg_DCLr_RGB	device_enclosure;

	union syscfg_DCLr_RGB	cover_glass;

	u_int8_t		reserved_C;
	u_int8_t		reserved_D;
	u_int8_t		reserved_E;
	u_int8_t		reserved_F;
} syscfg_DClr_t;

typedef enum {
        clrcColorUnknown = -1,
        clrcColorBlack   = 0,
        clrcColorWhite   = 1,
        clrcColorRed     = 2,
        clrcColorSilver  = 3,
        clrcColorPink    = 4,
        clrcColorBlue    = 5,
        clrcColorYellow  = 6,
        clrcColorGold    = 7,
        clrcColorSparrow = 8,
        clrcColorCount
} clrcColor;

typedef struct syscfg_ClrC {
	u_int8_t		clrcColor;	// clrcColor
	u_int8_t		reserved[15];
} syscfg_ClrC_t;

// Color remapping policy options a target may select
enum color_map_policy {
	COLOR_MAP_POLICY_NONE,		// Common remapping: No color remapping (legacy devices)
	COLOR_MAP_POLICY_INVERT,	// Common remapping: Invert colors
};

// Function pointer typedefs for color remappers.
typedef uint32_t (* map_color_t)(uint64_t color);    // Target specific color remapping

// Color remapping policy data
typedef struct color_policy {
	enum color_map_policy	policy_type;	// Color remapping policy type
	void		       *color_table;	// Pointer to policy-specific color table (e.g., a color_policy_invert_t)
	uint32_t		color_count;	// Number of entries in the color table
	map_color_t		map_color;	// Pointer to color remapping function
} color_policy_t;

// Color remapping table provided by the target for COLOR_MAP_POLICY_INVERT.
typedef struct color_policy_invert {
	uint32_t	cover_glass;	// Cover glass color
	char		invert;		// Invert bg/fg colors if true
} color_policy_invert_t;

struct plane {
	enum colorspace	cs;
	void		*fb_virt;
	void *		db_virt;     //draw buffer, start: fb_virt + frame size, align to next 4K
	u_int32_t	plane_size;
	u_int32_t	pixel_size;
	u_int32_t	pixel_size_per_channel;
	u_int32_t	line_x;
	u_int32_t	width;
	u_int32_t	height;
	u_int32_t	stride;
	void		(* plot)(struct plane *p, u_int32_t x, u_int32_t y, uint64_t color);
	u_int32_t	(* get_pixel)(struct plane *p, u_int32_t x, u_int32_t y);
	void		(* hline)(struct plane *p, u_int32_t x, u_int32_t y, u_int32_t len, uint64_t color);
	void		(* vline)(struct plane *p, u_int32_t x, u_int32_t y, u_int32_t len, uint64_t color);
};

#define MAX_NUM_PLANES_PER_CANVAS	2

struct canvas {
	enum colorspace	cs;
	struct plane	planes[MAX_NUM_PLANES_PER_CANVAS];
	uint32_t	num_of_active_planes;
	void		*fb_virt;
	uintptr_t	fb_phys;
	u_int32_t	x;
	u_int32_t	y;
	map_color_t	map_color;
};
#define kSysCfgBdevOffset  0x4000

struct syscfgEntry {
	u_int32_t	seTag;
	u_int8_t	seData[16];
};

struct syscfgEntryCNTB {
	u_int32_t       seTag;	/* 'CTNB' */
	u_int32_t	seRealTag;
	u_int32_t	seDataSize;
	u_int32_t	seDataOffset;
	u_int32_t	reserved;
};

struct syscfgMemEntry {
	u_int32_t	seTag;
	u_int8_t	seData[16];
	u_int32_t	seDataSize;	
	u_int32_t	seDataOffset;
};

#define ARP_CACHE_SIZE 32

typedef struct arp_cache_entry {
	uint32_t ip;
	char mac[6];
	struct arp_cache_entry *next;
} arp_cache_entry_t;

typedef struct arp_cache {
	arp_cache_entry_t cache[ARP_CACHE_SIZE];
} arp_cache_t;

struct listentry;

typedef int (*callback_handler)(char *data,int offset,int len,void *prevlayerdata);
typedef struct listentry {
	int cb_id;
	int port; //port/service/etc
	callback_handler callback;
	struct listentry *next;
} listentry_t;

typedef struct callbacks {
	listentry_t *first;
}callbacks_t;

struct mbufentry;

typedef struct mbufentry {
	int flag;
	int len;
	char *data;
	struct mbufentry *next;
} mbufentry_t;

typedef struct mymbuf {
	mbufentry_t *first;	
	int allocated_length;
	int current_length;
	char *primarydata;
	int offset;
}mymbuf_t;
typedef struct udpinfo {
	uint32_t srcip;
	uint16_t srcport;
	uint16_t length;
} udpinfo_t;
//====================================================================
// USB Descriptor Types
//====================================================================
#define USB_DT_DEVICE				1
#define USB_DT_CONFIGURATION                    2
#define USB_DT_STRING                           3
#define USB_DT_INTERFACE                        4
#define USB_DT_ENDPOINT                         5
#define USB_DT_DEVICE_QUALIFIER                 6
#define USB_DT_OTHER_SPEED_CONFIGURATION	7

//====================================================================
// USB Endpoints Types
//====================================================================
#define USB_ENDPOINT_CONTROL            0x00
#define USB_ENDPOINT_ISOCHRONOUS        0x01
#define USB_ENDPOINT_BULK               0x02
#define USB_ENDPOINT_INTERRUPT          0x03

//====================================================================
// USB Standard Request Types
//====================================================================
#define USB_REQ_GET_STATUS              0x00
#define USB_REQ_CLEAR_FEATURE           0x01
#define USB_REQ_SET_FEATURE             0x03
#define USB_REQ_SET_ADDRESS             0x05
#define USB_REQ_GET_DESCRIPTOR          0x06
#define USB_REQ_SET_DESCRIPTOR          0x07
#define USB_REQ_GET_CONFIGURATION       0x08
#define USB_REQ_SET_CONFIGURATION       0x09
#define USB_REQ_GET_INTERFACE           0x0A
#define USB_REQ_SET_INTERFACE           0x0B

//====================================================================
// USB Feature Types
//====================================================================
#define USB_FEATURE_ENDPOINT_HALT		0x00
#define USB_FEATURE_REMOTE_WAKEUP		0x01
#define USB_FEATURE_TEST_MODE			0x02

//====================================================================
// USB Device Request Types
//====================================================================
#define USB_REQ_TYPE_STANDARD           0x00
#define USB_REQ_TYPE_CLASS              0x20
#define USB_REQ_TYPE_VENDOR             0x40

//====================================================================
// USB Class Codes
//====================================================================
#define USB_CLASS_INTERFACE_SPECIFIC         0
#define USB_CLASS_VENDOR_SPECIFIC            0xff

//====================================================================
// 		USB Chap9 specific consts
//====================================================================
#define USB_DT_DEVICE_SIZE		18
#define USB_DT_CONFIGURATION_SIZE      	9
#define USB_DT_INTERFACE_SIZE   	9
#define USB_DT_ENDPOINT_SIZE    	7
#define USB_DT_DEVICE_QUALIFIER_SIZE    10
#define USB_DT_STRING_SIZE		6

#define USB_DIR_OUT                     0
#define USB_DIR_IN                      0x80

#define USB_ENDPOINT_MASK               0x03
#define USB_ENDPOINT_NUMBER_MASK        0x0f
#define USB_ENDPOINT_DIR_MASK           0x80

#define USB_BCD_VERSION			0x0200

#define USB_REQ_DIRECTION_MASK          0x80
#define USB_REQ_TYPE_MASK               0x60
#define USB_REQ_RECIPIENT_MASK          0x1f

#define USB_REQ_DEVICE2HOST             0x80
#define USB_REQ_HOST2DEVICE             0x00

#define USB_REQ_RECIPIENT_DEVICE        0x00
#define USB_REQ_RECIPIENT_INTERFACE     0x01
#define USB_REQ_RECIPIENT_ENDPOINT      0x02
#define USB_REQ_RECIPIENT_OTHER         0x03

#define SETUP_PACKET_LEN	0x8

#define EP0_IN		0x80
#define EP0_OUT		0x0
//====================================================================
// 		Enums, structs and typedefs
//====================================================================
struct usb_device_request
{
    u_int8_t bmRequestType;
    u_int8_t bRequest;
    u_int16_t wValue;
    u_int16_t wIndex;
    u_int16_t wLength;
} __attribute__((packed));

struct usb_device_descriptor
{
    u_int8_t bLength;
    u_int8_t bDescriptorType;
    u_int16_t bcdUSB;
    u_int8_t bDeviceClass;
    u_int8_t bDeviceSubClass;
    u_int8_t bDeviceProtocol;
    u_int8_t bMaxPacketSize0;
    u_int16_t idVendor;
    u_int16_t idProduct;
    u_int16_t bcdDevice;
    u_int8_t iManufacturer;
    u_int8_t iProduct;
    u_int8_t iSerialNumber;
    u_int8_t bNumConfigurations;
} __attribute__((packed));

struct usb_configuration_descriptor
{
    u_int8_t bLength;
    u_int8_t bDescriptorType;
    u_int16_t wTotalLength;
    u_int8_t bNumInterfaces;
    u_int8_t bConfigurationValue;
    u_int8_t iConfiguration;
    u_int8_t bmAttributes;
    u_int8_t bMaxPower;
} __attribute__((packed));

struct usb_interface_descriptor
{
    u_int8_t bLength;
    u_int8_t bDescriptorType;
    u_int8_t bInterfaceNumber;
    u_int8_t bAlternateSetting;
    u_int8_t bNumEndpoints;
    u_int8_t bInterfaceClass;
    u_int8_t bInterfaceSubClass;
    u_int8_t bInterfaceProtocol;
    u_int8_t iInterface;
} __attribute__((packed));

struct usb_endpoint_descriptor
{
    u_int8_t bLength;
    u_int8_t bDescriptorType;
    u_int8_t bEndpointAddress;
    u_int8_t bmAttributes;
    u_int16_t wMaxPacketSize;
    u_int8_t bInterval;
} __attribute__((packed));

struct usb_string_descriptor
{
    u_int8_t bLength;
    u_int8_t bDescriptorType;
    u_int8_t wData[2];
} __attribute__((packed));

struct usb_device_qualifier_descriptor
{
    u_int8_t bLength;
    u_int8_t bDescriptorType;
    u_int16_t bcdUSB;
    u_int8_t bDeviceClass;
    u_int8_t bDeviceSubClass;
    u_int8_t bDeviceProtocol;
    u_int8_t bMaxPacketSize0;
    u_int8_t bNumConfigurations;
    u_int8_t bReserved;
} __attribute__((packed));

enum
{
	DEVICE_ST_UNKNOWN = -1,
	DEVICE_ST_INIT = 0,
    DEVICE_ST_ATTACHED,
    DEVICE_ST_POWERED,
    DEVICE_ST_DEFAULT,
    DEVICE_ST_ADDRESSED,
    DEVICE_ST_CONFIGURED,
    DEVICE_ST_SUSPENDED
};

//====================================================================
// 		USB driver specific consts
//====================================================================
#define EP0_MAX_PACKET_SIZE	0x40
#define HS_BULK_EP_MAX_PACKET_SIZE	0x200
#define HS_INT_EP_MAX_PACKET_SIZE	0x40
#define FS_EP_MAX_PACKET_SIZE		0x40
enum
{
	USB_IO_ERROR = -1,
	USB_IO_SUCCESS = 0,
	USB_IO_ABORTED
};

enum
{
	CABLE_CONNECTED = 0,
	CABLE_DISCONNECTED,
	USB_RESET,
	USB_ENUM_DONE
};

enum {
    CONNECTION_SPEED_FULL = 0,
    CONNECTION_SPEED_HIGH
};

struct usb_device_io_request
{
	u_int32_t endpoint;
	volatile u_int8_t *io_buffer;
	int status;
	int io_length;
	int return_count;
	void (*callback) (struct usb_device_io_request *io_request);
	struct usb_device_io_request *next;
};

struct usb_endpoint_instance
{
	int		endpoint_address;
	int 		max_packet_size;
	int 		attributes;
	int 		bInterval;
	
	int 		transfer_size;
	int 		packet_count;
    
	struct usb_endpoint_instance *next_ep;
    
	struct usb_device_io_request *io_head;
	struct usb_device_io_request *io_tail;
    
	int		tx_fifo_number;
};

struct usb_controller_ops
{
	void (*start) (void);
	void (*stop) (void);
	void (*set_address) (int new_address);
	void (*stall_endpoint) (u_int32_t endpoint, char stall);
	void (*reset_endpoint_data_toggle) (u_int32_t endpoint);
	char (*is_endpoint_stalled) (u_int32_t endpoint);
	void (*do_endpoint_io) (struct usb_device_io_request *req);
	void (*activate_endpoint) (u_int32_t endpoint, int type, int max_packet_size, int interval);
	void (*deactivate_endpoint) (u_int32_t endpoint);
	void (*abort_endpoint) (u_int32_t endpoint);
	void (*do_test_mode)(int test_selector);
	int (*get_connection_speed) (void);
};

struct usb_interface_instance
{
	int (*interface_request_handler) (struct usb_device_request *request, u_int8_t ** out_data);
	void (*non_setup_data_phase_finished_callback) (int data_rcvd);
	void (*activate_interface) (void);
	void (*bus_reset_handler) (void);
	int (*get_interface_handler) (void);
	int (*set_interface_handler) (int alt_setting);
};


typedef enum {
	USB_CONTROLLER_synopsys_otg,
	USB_CONTROLLER_dbgfifo,
} USB_CONTROLLER_T;

struct usb_controller_functions {
	int (*init)(void);
	void (*free_func)(void);
	int (*start)(void);
	void (*stop)(void);
	void (*set_address)(uint32_t new_address);
	int (*get_connection_speed)(void);
	void (*activate_endpoint)(uint32_t endpoint, int type, int max_packet_size, int interval);
	void (*do_endpoint_io)(struct usb_device_io_request *req);
	void (*stall_endpoint)(uint32_t endpoint, char stall);
	void (*reset_endpoint_data_toggle)(uint32_t endpoint);
	char (*is_endpoint_stalled)(uint32_t endpoint);
	void (*do_test_mode)(uint32_t selector);
	void (*abort_endpoint)(uint32_t endpoint);
	void (*deactivate_endpoint)(uint32_t endpoint);
};


enum {
    USB_TRANSFER_TYPE_DFU_GET,
    USB_TRANSFER_TYPE_DFU_PUT,
    USB_TRANSFER_TYPE_BULK_GET,
    USB_TRANSFER_TYPE_BULK_PUT
};
typedef struct nhi_sgl {
	void *buffer;
	uint32_t bytes;
	struct nhi_sgl *next;
} nhi_sgl_t;

