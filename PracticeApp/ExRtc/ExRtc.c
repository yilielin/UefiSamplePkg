/** @file
  This sample application to print CMOS data to the UEFI Console.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/Iolib.h>

#define RTC_BANK0_IO_IDX_PORT  (0x70)
#define RTC_BANK0_IO_TARG_PORT (0x71)
#define RTC_BANK1_IO_IDX_PORT  (0x72)
#define RTC_BANK1_IO_TARG_PORT (0x73)

typedef union {
  struct {
    UINT8 Data[128];
  } Raw;
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
    UINT8 UserRam[114];
  } Rtc;
} RTC_CMOS_BANK0;


VOID
PrintCmosRtc (
  IN RTC_CMOS_BANK0 *RtcBank0
  );


/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // Read RTC CMOS
  RTC_CMOS_BANK0 RtcBank0;
  for (UINTN offset = 0; offset < sizeof(RTC_CMOS_BANK0); offset++) {
    IoWrite8 (RTC_BANK0_IO_IDX_PORT, (UINT8)offset);
    RtcBank0.Raw.Data[offset] = IoRead8 (RTC_BANK0_IO_TARG_PORT);
  }
  // Print data to screen
  PrintCmosRtc(&RtcBank0);
  return EFI_SUCCESS;
}

VOID
PrintCmosRtc (
  IN RTC_CMOS_BANK0 *RtcBank0
  )
{
  Print(L"RTC (Standard) RAM Bank : \n");
  Print(L"Sec:%02x Min:%02x Hour:%02x \nWD:%02x DoM:%02x Mon:%02x Year:%02x \n",\
        RtcBank0->Rtc.Sec,\
        RtcBank0->Rtc.Min,\
        RtcBank0->Rtc.Hour,\
        RtcBank0->Rtc.WeekDay,\
        RtcBank0->Rtc.DayOfMonth,\
        RtcBank0->Rtc.Month,\
        RtcBank0->Rtc.Year\
        );
  Print(L"\n");
  Print(L"RegA:%02x \nRegB:%02x \nRegC:%02x \nRegD:%02x\n",\
        RtcBank0->Rtc.RegA,\
        RtcBank0->Rtc.RegB,\
        RtcBank0->Rtc.RegC,\
        RtcBank0->Rtc.RegD\
        );
  Print(L"\n"); 
}
