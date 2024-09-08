/** @file
  This sample application bases on HelloWorld PCD setting
  to print "UEFI Hello World!" to the UEFI Console.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/ShellCEntryLib.h>              // ShellAppMain()

//
// String token ID of help message text.
// Shell supports to find help message in the resource section of an application image if
// .MAN file is not found. This global variable is added to make build tool recognizes
// that the help string is consumed by user and then build tool will add the string into
// the resource section. Thus the application can use '-?' option to show help message in
// Shell.
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_STRING_ID  mStringHelpTokenId = STRING_TOKEN (STR_HW_HELP_INFORMATION);


/**
  Entry point function of this shell application.
**/
INTN
EFIAPI
ShellAppMain (
  IN UINTN   Argc,
  IN CHAR16  **Argv
  )
{
  // Display my name if no arg is passed
  if (Argc <= 1 ) {
      Print (L"yilie\n");
  } else {
      // echo args
      for (int idx=1 ; idx < Argc ; idx++) {
        Print (L"%s ",Argv[idx]);
      }
      Print (L"\n");
  } 

  return RETURN_SUCCESS;
} //ShellAppMain

