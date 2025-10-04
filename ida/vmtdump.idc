// @note: found it somewhere on unknowncheats, idk who is author

#include <idc.idc>

static main()
{
	auto pAddress, iIndex;
	auto szFilePath, hFile;
	auto skipAmt;

	SetStatus(IDA_STATUS_WORK);

	pAddress = ScreenEA();
	
	if (pAddress == BADADDR)
	{	
		Message("[ - ] no vtable selected");
		SetStatus(IDA_STATUS_READY);
		return;
	}

	skipAmt = AskLong(0, "number of vtable entries to ignore for indexing:");

	SetStatus(IDA_STATUS_WAITING);
	if ((szFilePath = AskFile(1, "*.txt", "select output dump file:")) == 0)
	{
		Message("[ + ] aborted");
		SetStatus(IDA_STATUS_READY);
		return;
	}
	
	if ((hFile = fopen(szFilePath, "wb")) != 0)
	{
		auto szFuncName, szFullName, BadHits;
		
		BadHits = 0;

		fprintf(hFile, "// 0x%08X\n// %s\n", pAddress, GetInputFile());
		
		if (Dword(pAddress) == 0)
			pAddress = pAddress + 8;
		
		pAddress = pAddress + (skipAmt * 4);

		while (pAddress != BADADDR)
		{
			auto real_addr;
			real_addr = Dword(pAddress);
				
			szFuncName = Name(real_addr);
			if (strlen(szFuncName) == 0)
			{
				break;
			}
			szFullName = Demangle(szFuncName, INF_LONG_DN);
			if (szFullName == "")
			{
				szFullName = szFuncName;
			}
			if (strstr(szFullName, "_ZN") != -1)
			{
				fclose(hFile);
				Warning("[ ! ] you must toggle GCC v3.x demangled names!\n");
				break;
			}
			fprintf(hFile, "%d\t%s\n", iIndex, szFullName);
						
			pAddress = pAddress + 4;
			iIndex++;
		};

		fclose(hFile);
		Message("[ + ] successfully wrote %d vtable entries.\n", iIndex);
	}
	else
	{		
		Message("[ ! ] error opening \"%s\"!\n", szFilePath);
	}

	Message("\n[ + ] done\n\n");
	SetStatus(IDA_STATUS_READY);
}