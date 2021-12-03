#include <ZCVisionTool/ZCVisionTool.h>

int HexToChar(uint8_t c)
{
	return ((c >= '0') && (c <= '9')) ? int(c - '0') :
		((c >= 'A') && (c <= 'F')) ? int(c - 'A' + 10) :
		((c >= 'a') && (c <= 'f')) ? int(c - 'a' + 10) :
		-1;
}

unsigned int ssstrlen(const char* str)
{
	const char* cp = str;
	while (*cp++);
	return (cp - str - 1);
}

DLLAPI int STDCALL HexCharValue(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	assert(0);
	return 0;
}

DLLAPI int STDCALL HexToDecimalInt(const char* szHex, int len)
{
	int result = 0;
	for (int i = 0; i < len; i++)
	{
		result += (int)pow((float)16, (int)len - i - 1) * HexCharValue(szHex[i]);
	}
	return result;
}

DLLAPI int STDCALL HexToAscii(char* Hex, char* ASCii)
{
	int hexLen = ssstrlen(Hex);
	int asciiLen = 0;

	for (int i = 0, cnt = 0; i < hexLen; i++)
	{
		char c = HexToChar(Hex[i]);

		if (-1 == c)
			continue;
		if (cnt)
		{
			cnt = 0;
			ASCii[asciiLen++] += c;
		}
		else
		{
			cnt = 1;
			ASCii[asciiLen] = c << 4;
		}
	}
	ASCii[asciiLen++] = 0;
	return asciiLen;
}

DLLAPI std::string STDCALL AsciiToHex(char* ASCii)
{
	int asciiLen = ssstrlen(ASCii);

	std::string result = "";

	if (asciiLen <= 0)
		return result;

	char buf[4];
	

	for (int i = 0; i < asciiLen; i++)
	{
		sprintf_s(buf, "%02x", ASCii[i]);
		result += buf;
	}

	return result;
}