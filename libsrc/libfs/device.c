#include <device.h>

zDevice devZSPI={
	.major= DRV_ZSPI,
	.minor= 0,
	.devname="zspi",

	// int16_t	(*init)(struct zDevice* dev);
	// int16_t	(*release)(struct zDevice* dev);
	// int16_t	(*open)(struct zDevice* dev);
	// int16_t	(*close)(struct zDevice* dev);
	// int16_t	(*read)(struct zDevice* dev,  void* buf, int16_t size);
	// int16_t	(*write)(struct zDevice* dev, int16_t fd, void* buf, int16_t size);
	// int16_t	(*poll)(struct zDevice* dev);
	// int16_t	(*ioctl)(struct zDevice* dev, int16_t rq, ... );
};

zDevice devNGSSPI={
	.major= DRV_NGSSPI,
	.minor= 0,
	.devname="ngsspi",

	// int16_t	(*init)(struct zDevice* dev);
	// int16_t	(*release)(struct zDevice* dev);
	// int16_t	(*open)(struct zDevice* dev);
	// int16_t	(*close)(struct zDevice* dev);
	// int16_t	(*read)(struct zDevice* dev,  void* buf, int16_t size);
	// int16_t	(*write)(struct zDevice* dev, int16_t fd, void* buf, int16_t size);
	// int16_t	(*poll)(struct zDevice* dev);
	// int16_t	(*ioctl)(struct zDevice* dev, int16_t rq, ... );
};


zDevice devNEMOIDE={
	.major= DRV_NEMOIDE,
	.minor= 0,
	.devname="nemoide",

	// int16_t	(*init)(struct zDevice* dev);
	// int16_t	(*release)(struct zDevice* dev);
	// int16_t	(*open)(struct zDevice* dev);
	// int16_t	(*close)(struct zDevice* dev);
	// int16_t	(*read)(struct zDevice* dev,  void* buf, int16_t size);
	// int16_t	(*write)(struct zDevice* dev, int16_t fd, void* buf, int16_t size);
	// int16_t	(*poll)(struct zDevice* dev);
	// int16_t	(*ioctl)(struct zDevice* dev, int16_t rq, ... );
};

zDevice devSMUCIDE={
	.major= DRV_SMUCIDE,
	.minor= 0,
	.devname="smucide",

	// int16_t	(*init)(struct zDevice* dev);
	// int16_t	(*release)(struct zDevice* dev);
	// int16_t	(*open)(struct zDevice* dev);
	// int16_t	(*close)(struct zDevice* dev);
	// int16_t	(*read)(struct zDevice* dev,  void* buf, int16_t size);
	// int16_t	(*write)(struct zDevice* dev, int16_t fd, void* buf, int16_t size);
	// int16_t	(*poll)(struct zDevice* dev);
	// int16_t	(*ioctl)(struct zDevice* dev, int16_t rq, ... );
};

zDevice devTTYZXMC={
	.major= DRV_TTYZXMC,
	.minor= 0,
	.devname="ttyZXMC",

	// int16_t	(*init)(struct zDevice* dev);
	// int16_t	(*release)(struct zDevice* dev);
	// int16_t	(*open)(struct zDevice* dev);
	// int16_t	(*close)(struct zDevice* dev);
	// int16_t	(*read)(struct zDevice* dev,  void* buf, int16_t size);
	// int16_t	(*write)(struct zDevice* dev, int16_t fd, void* buf, int16_t size);
	// int16_t	(*poll)(struct zDevice* dev);
	// int16_t	(*ioctl)(struct zDevice* dev, int16_t rq, ... );
};

zDevice devTTYZIFI={
	.major= DRV_TTYZIFI,
	.minor= 0,
	.devname="ttyZIFI",

	// int16_t	(*init)(struct zDevice* dev);
	// int16_t	(*release)(struct zDevice* dev);
	// int16_t	(*open)(struct zDevice* dev);
	// int16_t	(*close)(struct zDevice* dev);
	// int16_t	(*read)(struct zDevice* dev,  void* buf, int16_t size);
	// int16_t	(*write)(struct zDevice* dev, int16_t fd, void* buf, int16_t size);
	// int16_t	(*poll)(struct zDevice* dev);
	// int16_t	(*ioctl)(struct zDevice* dev, int16_t rq, ... );
};
