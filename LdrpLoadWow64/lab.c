#include "lab.h"

#define LdrpLoadWow64Offset 0x837f4

NTSTATUS LdrpLoadWow64(PWCHAR DllPath) {
	HMODULE hNtdll = NULL;
	NTSTATUS(NTAPI * RtlInitUnicodeString)(OUT PUNICODE_STRING DestinationString, IN OPTIONAL __drv_aliasesMem PWSTR SourceString) = NULL;
	NTSTATUS(NTAPI * LdrpLoadWow64)(PUNICODE_STRING DllPath) = NULL;
	UNICODE_STRING unicodeDllPath = { 0 };
	NTSTATUS retVal = STATUS_DLL_INIT_FAILED;
	
	hNtdll = GetModuleHandleA("ntdll.dll");
	if (hNtdll == NULL) {
		error("GetModuleHandleA");
	}
	RtlInitUnicodeString = (NTSTATUS(NTAPI*)(PUNICODE_STRING, __drv_aliasesMem PWSTR))GetProcAddress(hNtdll, "RtlInitUnicodeString");
	if (RtlInitUnicodeString == NULL) {
		error("GetProcAddress for RtlInitUnicodeString");
	}
	LdrpLoadWow64 = (NTSTATUS(NTAPI*)(PUNICODE_STRING))((CHAR*)hNtdll + LdrpLoadWow64Offset);

	retVal = RtlInitUnicodeString(&unicodeDllPath, DllPath);
	if (retVal) {
		DbgPrint("[-][%s] %s returned 0x%x\n", __func__, "RtlInitUnicodeString", retVal);
		goto exit;
	}
	retVal = LdrpLoadWow64(&unicodeDllPath);

exit:
	return retVal;
	
}