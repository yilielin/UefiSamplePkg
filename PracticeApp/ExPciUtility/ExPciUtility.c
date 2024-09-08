/** @file
  This sample application bases on HelloWorld PCD setting
  to print "UEFI Hello World!" to the UEFI Console.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>
#include <IndustryStandard/Pci.h>

#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/ShellCEntryLib.h>              // ShellAppMain()
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciIo.h>

VOID
EFIAPI
PrintAllPciDevices (
  VOID
);

EFI_STATUS
PciReadType00 (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridgeIo,
  OUT PCI_TYPE00                          *PciType00,
  IN  UINT8                               Bus,
  IN  UINT8                               Dev,
  IN  UINT8                               Fun
  );

//
// String token ID of help message text.
// Shell supports to find help message in the resource section of an application image if
// .MAN file is not found. This global variable is added to make build tool recognizes
// that the help string is consumed by user and then build tool will add the string into
// the resource section. Thus the application can use '-?' option to show help message in
// Shell.
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_STRING_ID  mStringHelpTokenId = STRING_TOKEN (STR_HW_HELP_INFORMATION);


  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *mPciRootBridgeIo = NULL;
  EFI_HANDLE  *mPciRBHandleBuffer = NULL;
  UINTN       mPciRBHandleCount = 0;

/**
  Entry point function from ShellCEntryLib.
**/
INTN
EFIAPI
ShellAppMain (
  IN UINTN   Argc,
  IN CHAR16  **Argv
  )
{
  DEBUG ((DEBUG_INFO, "ExPciUtility start\n"));
  EFI_STATUS  Status = EFI_NOT_STARTED;
  INTN        RetVal = RETURN_NOT_STARTED;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol, 
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  &mPciRBHandleCount,
                  &mPciRBHandleBuffer
                  );

  if (EFI_ERROR (Status)) {
    Print (L"PCI root bridge is not found\n");
    Status = EFI_NOT_FOUND;
    return RETURN_ABORTED;
  }
  

  // Display PCI devices if no args passed
  if (Argc <= 1) {
      PrintAllPciDevices ();
      RetVal = RETURN_SUCCESS;
  } // if

  // Print PCI configure space
  if (Argc <= 4) {
    // TODO
  }

  DEBUG ((DEBUG_INFO, "ExPciUtility end\n"));
  return RetVal;
} //ShellAppMain


VOID
EFIAPI
PrintAllPciDevices (
  VOID
  )
{
  EFI_STATUS  Status = EFI_NOT_STARTED;
  PCI_TYPE00  PciType00;

  // Locate all EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL
  for( UINTN Idx = 0; Idx < mPciRBHandleCount; Idx++) {
    DEBUG ((DEBUG_INFO, "mPciRBHandleBuffer[%d]\n", Idx));
    Status = gBS->HandleProtocol (
                    mPciRBHandleBuffer[Idx],
                    &gEfiPciRootBridgeIoProtocolGuid,
                    (VOID**)&mPciRootBridgeIo
                    );

    if (!EFI_ERROR (Status)) {
      for(UINT8 Bus=0; Bus < PCI_MAX_BUS; Bus++) {
        for(UINT8 Dev=0; Dev <= PCI_MAX_DEVICE; Dev++) {
          for(UINT8 Fun=0; Fun <= PCI_MAX_FUNC; Fun++) {
            if (PciReadType00 (mPciRootBridgeIo, &PciType00, Bus, Dev, Fun) == EFI_SUCCESS) {
              Print (L"B:%3x  D:%2x  F:%1x  |  VID:%4x  DID:%4x\n", Bus, Dev, Fun, PciType00.Hdr.VendorId, PciType00.Hdr.DeviceId);
            }
          } // Fun
        } // Dev
      } // Bus
    } // if
  } // for
} // PrintAllPciDevices


EFI_STATUS
PciReadType00 (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridgeIo,
  OUT PCI_TYPE00                          *PciType00,
  IN  UINT8                               Bus,
  IN  UINT8                               Dev,
  IN  UINT8                               Fun
  )
{
  PciRootBridgeIo->Pci.Read (
                     PciRootBridgeIo,
                     EfiPciWidthUint32,
                     EFI_PCI_ADDRESS (Bus, Dev, Fun, 0),
                     1,
                     PciType00
                     );
  // 0xFFFF is invalid to VID
  if (PciType00->Hdr.VendorId != 0xFFFF) {
    return EFI_SUCCESS;
  } else {
    return EFI_ABORTED;
  }
}


