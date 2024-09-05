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
// #include <Library/PciLib.h>
// #include <Library/PciCf8Lib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciIo.h>
#include <IndustryStandard/Pci.h>

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
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *mPciRootBridgeIo = NULL;
  PCI_TYPE00                       Pci;
  EFI_STATUS                       Status = EFI_NOT_STARTED;
  INTN                             RetVal = RETURN_NOT_STARTED;

  Status = gBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid, NULL, (VOID **)&mPciRootBridgeIo);
  if (EFI_ERROR (Status)) {
    Print (L"PCI root bridge not found\n");
    Status = EFI_NOT_FOUND;
  }

  if (Status != EFI_SUCCESS) {
    RetVal = RETURN_ABORTED;
  } else {
    RetVal = RETURN_SUCCESS;
    // Display PCI devices if no args passed
    if (Argc <= 1 ) {
        // TODO
    }
    // Print PCI configure space
    if (Argc <= 4 ) {
      mPciRootBridgeIo->Pci.Read(
                        mPciRootBridgeIo,
                        EfiPciIoWidthUint32,
                        PCI_BAR_IDX0,
                        sizeof (Pci) / sizeof (UINT32),
                        &Pci
                        );
      Print (L"VID: %X DID: %X\n",Pci.Hdr.VendorId, Pci.Hdr.DeviceId);
    }
  }

  return RetVal;
} //ShellAppMain

