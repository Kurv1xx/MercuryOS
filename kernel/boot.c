#include <stdint.h>
#include "../libs/shared.h"
#define EFIAPI __attribute__((ms_abi))

typedef uint64_t EFI_STATUS;
typedef uint64_t UINTN;
typedef void* EFI_HANDLE;
typedef uint16_t CHAR16;

/* ================= EFI TABLE HEADER ================= */
typedef struct {
    uint64_t Signature;
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
} EFI_TABLE_HEADER;

/* ================= TEXT OUTPUT ================= */
typedef struct {
    EFI_STATUS (EFIAPI *Reset)(void*, uint8_t);
    EFI_STATUS (EFIAPI *OutputString)(void*, const CHAR16*);
} SIMPLE_TEXT_OUTPUT_PROTOCOL;

/* ================= SYSTEM TABLE ================= */
typedef struct {
    EFI_TABLE_HEADER               Hdr;
    CHAR16*                        FirmwareVendor;
    uint32_t                       FirmwareRevision;

    EFI_HANDLE                     ConsoleInHandle;
    void*                          ConIn;

    EFI_HANDLE                     ConsoleOutHandle;
    SIMPLE_TEXT_OUTPUT_PROTOCOL*   ConOut;

    EFI_HANDLE                     StandardErrorHandle;
    SIMPLE_TEXT_OUTPUT_PROTOCOL*   StdErr;

    void*                          RuntimeServices;
    void*                          BootServices;
} EFI_SYSTEM_TABLE;


/* ================= ENTRY ================= */
extern void kernel_entry(BootInfo*);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
    static CHAR16 msg[] = {
        'M','e','r','c','u','r','y',' ',
        'B','o','o','t',' ','O','K','\r','\n',0
    };

    SystemTable->ConOut->OutputString(SystemTable->ConOut, msg);
    return 0;
}