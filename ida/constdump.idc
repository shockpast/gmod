#include <idc.idc>

static main()
{
    auto pAddress, szFilePath, hFile;
    auto entryAddr, szString;

    SetStatus(IDA_STATUS_WORK);

    pAddress = ScreenEA();
    if (pAddress == BADADDR)
    {
        Message("[ - ] no address selected\n");
        SetStatus(IDA_STATUS_READY);
        return;
    }

    if ((szFilePath = AskFile(1, "*.txt", "select output dump file:")) == 0)
    {
        Message("[ + ] aborted\n");
        SetStatus(IDA_STATUS_READY);
        return;
    }

    if ((hFile = fopen(szFilePath, "wb")) != 0)
    {
        fprintf(hFile, "// 0x%08X\n", pAddress, GetInputFile());
        fprintf(hFile, "// %s\n\n", GetInputFile());
        fprintf(hFile, "// <address> <value>\n\n");

        Message("[ + ] dumping data from 0x%08X ...\n", pAddress);

        auto count = 0;
        while (1)
        {
            entryAddr = Dword(pAddress);
            if (entryAddr == 0 || entryAddr == BADADDR)
                break;

            szString = GetString(entryAddr, -1, ASCSTR_C);
            if (szString == "")
                szString = "<no_string>";

            fprintf(hFile, "0x%08X\t\"%s\"\n", entryAddr, szString);

            pAddress = pAddress + 4;
            count++;
        }

        fclose(hFile);
        Message("[ + ] dumped %d constants\n", count);
    }
    else
    {
        Message("[ ! ] error opening output file!\n");
    }

    SetStatus(IDA_STATUS_READY);
    Message("[ + ] done\n");
}
