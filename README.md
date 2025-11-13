# Introduction

This project and accompanying PoC are part of *LoadLibrary - LdrLoadDll research* I made between 20 October 2025 and 2 November 2025. I found the **LdrpLoadWow64** function while checking for cross references of **LdrpLoadDll**. Moreover, I noticed that this function can lead to DLL injection as an alternative to **LdrLoadDll** function.
I used [Binary Ninja Free](https://binary.ninja/), [x64dbg](https://x64dbg.com/) and [Microsoft Visual Studio 2022](https://visualstudio.microsoft.com) for this project.

## Thanks

Before going deeper, there are some people that I want to thank:

- Thanks to my grandma for raising me as an amazing child,
- Thanks to Mrs Kübra Çakır Erdoğdu and Mr Diego Ledda for always mentoring me,
- Thanks to my sister and our cat Pamuk for supporting me endlessly.

# Description
<img width="1822" height="816" alt="binja_pseuode-c" src="https://github.com/user-attachments/assets/4251dcb1-0b98-4c23-819b-b9606b489345" />

The Pseudo C code provided by Binary Ninja is shown in the attached photo. At first glance, I thought it was taking a **PWSTR**. The point I was missing was `RtlAppendUnicodeStringToString(&dllName, arg1);` line. Because `RtlAppendUnicodeStringToString` function takes two arguments and both are **PCUNICODE_STRING**. So, that led me to think arg1 is a pointer to **UNICODE_STRING** structure. Then, the function calls `RtlAppendUnicodeToString(&dllName, u"wow64.dll")`. By doing so, it adds `L"wow64.dll"` to the end of the string arg1 stores. My idea was if I have a dll named **wow64.dll** and pass the pointer of the `UNICODE_STRING` structure that holds its path as an argument for **LdrpLoadWow64**, it would end in DLL injection. It did as well.

## Bonus Ideas and Contributing

I have some ideas, and contributors are welcome to work on these:

- First of all, testing this on newer and older x64 systems is required to have a clear picture of the method's reliability. I have only tested this on **Microsoft Windows 10 Pro x64 Build 19045**.

- ~~Achieving DLL Injection with this method without including any suspicious functions like **GetModuleHandle** and **GetProcAddress**.
In my opinion, this can be achieved by writing a custom GetModuleHandle function and either a custom GetProcAddress or a copycat function of RtlInitUnicodeString in order to use in my LdrpLoadWow64 wrapper. (Writing a custom GetProcAddress function is another option, but I prefer having a custom RtlInitUnicodeString function.) **[I'm working on this.]**~~ :white_check_mark:

- Since **LdrpLoadWow64** doesn't return the attached DLL's handle and it is just a wrapper of **LdrpLoadDll**, a new function that returns the DLL's handle can be written by observing how it uses **LdrpLoadDll**.

- New ideas are welcome!

# Author

Muzaffer Umut ŞAHİN mailatmayinlutfen@gmail.com

