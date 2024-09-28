#ifndef __BASE_RTC_LIB_H__
#define __BASE_RTC_LIB_H__

#include <Uefi.h>
#include <Library/Iolib.h>

#define RTC_BANK0_IDX_IO_PORT  (0x70)
#define RTC_BANK0_TAR_IO_PORT  (0x71)
#define RTC_BANK1_IDX_IO_PORT  (0x72)
#define RTC_BANK1_TAR_IO_PORT  (0x73)

#pragma pack(1)

typedef union {
  struct {
    UINT8 Data[128];
  } Raw;
  struct {
    struct {
        UINT8 Sec;
        UINT8 SecAlarm;
        UINT8 Min;
        UINT8 MinAlarm;
        UINT8 Hour;
        UINT8 HourAlarm;
        UINT8 WeekDay;
        UINT8 DayOfMonth;
        UINT8 Month;
        UINT8 Year;
        UINT8 RegA;
        UINT8 RegB;
        UINT8 RegC;
        UINT8 RegD;
    } Rtc;
    UINT8 UserRam[114];
  } ;

} RTC_CMOS_BANK0;

#pragma pack()

EFI_STATUS
GetCmosRtc (
  OUT RTC_CMOS_BANK0 *RtcBank0
  );
  
VOID
PrintCmosRtc (
  IN RTC_CMOS_BANK0 *RtcBank0
  );


#endif