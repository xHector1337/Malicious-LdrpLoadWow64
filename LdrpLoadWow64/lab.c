#include "lab.h"

#define LdrpLoadWow64Offset 0x837f4

NTSTATUS LdrpLoadWow64(PWCHAR DllPath) {
	HMODULE hNtdll = NULL;
	NTSTATUS(NTAPI * LdrpLoadWow64)(PUNICODE_STRING DllPath) = NULL;
	UNICODE_STRING unicodeDllPath = { 0 };
	NTSTATUS retVal = STATUS_DLL_INIT_FAILED;
	
	//hNtdll = GetModuleHandleA("ntdll.dll");
	hNtdll = CustomGetModuleHandle();
	if (hNtdll == NULL) {
		DbgPrint("[-][%s] CustomGetModuleHandle couldn't retrieve the handle.\n",__func__);
		goto exit;
	}

	LdrpLoadWow64 = (NTSTATUS(NTAPI*)(PUNICODE_STRING))((CHAR*)hNtdll + LdrpLoadWow64Offset);

	RtlInitUnicodeString(&unicodeDllPath, DllPath);
	
	retVal = LdrpLoadWow64(&unicodeDllPath);

exit:
	return retVal;
	
}

void RtlInitUnicodeString(OUT UNICODE_STRING* DestinationString, IN OPTIONAL PWSTR SourceString) {
	if (DestinationString == NULL) {
		return;
	}

	DestinationString->Length = 0;
	DestinationString->MaximumLength = 0;
	DestinationString->Buffer = SourceString;

	if (SourceString == NULL) {
		return;
	}
	
	size_t i = 0;
	for (; *SourceString != 0x00; i++) {
		SourceString++;
	}
	i = i * 2;
	if (i >= 65534) {
		i = 65532;
	}
	DestinationString->Length = (USHORT)i;
	DestinationString->MaximumLength = (USHORT)i + 2;

}