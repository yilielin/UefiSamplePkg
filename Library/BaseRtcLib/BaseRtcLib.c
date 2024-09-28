/** @file
  This application to get CMOS data and print CMOS data to the UEFI Console.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseRtcLib.h>


/**
  Get CMOS RTC data

  @param[out] RtcBank0      Struct of RTC CMOS will be wrote.

  @retval EFI_SUCCESS       The function is executed successfully.
  @retval other             Some error occurs when executing this function.

**/

EFI_STATUS
EFIAPI
GetCmosRtc (
  OUT RTC_CMOS_BANK0 *RtcBank0
  )
{
  if (RtcBank0 == NULL) {
    return EFI_ABORTED;
  }
  // Read RTC CMOS via IO port
  for (UINTN offset = 0; offset < sizeof(RTC_CMOS_BANK0); offset++) {
    IoWrite8 (RTC_BANK0_IDX_IO_PORT, (UINT8)offset);
    RtcBank0->Raw.Data[offset] = IoRead8 (RTC_BANK0_TAR_IO_PORT);
  }
  return EFI_SUCCESS;
}


/**
  Print CMOS RTC data

  @param[in] RtcBank0       Struct of RTC CMOS will be printed.

  @retval VOID

**/

VOID
PrintCmosRtc (
  IN RTC_CMOS_BANK0 *RtcBank0
  )
{
  Print (L"RTC (Standard) RAM Bank : \n");
  Print (L"Sec:%02x Min:%02x Hour:%02x \nWD:%02x DoM:%02x Mon:%02x Year:%02x \n",\
        RtcBank0->Rtc.Sec,\
        RtcBank0->Rtc.Min,\
        RtcBank0->Rtc.Hour,\
        RtcBank0->Rtc.WeekDay,\
        RtcBank0->Rtc.DayOfMonth,\
        RtcBank0->Rtc.Month,\
        RtcBank0->Rtc.Year\
        );
  Print (L"\n");
  Print (L"RegA:%02x \nRegB:%02x \nRegC:%02x \nRegD:%02x\n",\
        RtcBank0->Rtc.RegA,\
        RtcBank0->Rtc.RegB,\
        RtcBank0->Rtc.RegC,\
        RtcBank0->Rtc.RegD\
        );
  Print (L"\n");
}
