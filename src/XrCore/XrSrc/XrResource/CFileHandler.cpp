#include "CFileHandler.h"


CFileHandler::CFileHandler()
{
	fp = 0;
}

xr_state CFileHandler::readOpen(ConstString fileName)
{
	fp = XrFOpen((String)fileName, (String)"rb");
	if (!fp) return XR_FAILED;
	else return XR_OK;
}

xr_state CFileHandler::writeOpen(ConstString fileName)
{
	fp = XrFOpen((String)fileName, (String)"wb");
	if (!fp) return XR_FAILED;
	else return XR_OK;
}

void CFileHandler::read(void* buf, UInt32 elementSize, UInt32 count)
{
	XrFRead(buf, elementSize, count, fp);
}

void CFileHandler::write(const void* buf, UInt32 elementSize, UInt32 count)
{
	//XrFWrite((Void*)buf, elementSize, count, fp);
}

void CFileHandler::skip(Int32 count)
{

}
void CFileHandler::seekFromStart( UInt32 pos )
{
	XrFSeek(fp, pos, SEEK_SET);
}
void CFileHandler::seekFromEnd( UInt32 pos )
{
	XrFSeek(fp, pos, SEEK_END);
}
void CFileHandler::seekFromCurrent( UInt32 pos )
{
	XrFSeek(fp, pos, SEEK_CUR);
}

UInt32 CFileHandler::tell(void)
{
	return XrFTell(fp);
}

Int32 CFileHandler::eof(void)
{
	return XrFEOF(fp);
}

void CFileHandler::close(void)
{
	XrFClose(fp);
}
