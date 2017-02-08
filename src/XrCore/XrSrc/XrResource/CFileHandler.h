#ifndef _CXR_XrFile_HANDER_H
#define _CXR_XrFile_HANDER_H
#include "../Common/XrInternal.h"


class CFileHandler
{
public:
	CFileHandler();
	~CFileHandler(){}

	xr_state readOpen(ConstString fileName);
	xr_state writeOpen(ConstString fileName);
	void read(void* buf, UInt32 elementSize, UInt32 count);
	void write(const void* buf, UInt32 elementSize, UInt32 count);
	void skip(Int32 count);
	void seekFromStart( UInt32 pos );
	void seekFromEnd( UInt32 pos );
	void seekFromCurrent( UInt32 pos );
	UInt32 tell(void);
	Int32 eof(void);
    void close(void);

protected:
	Int32	m_id;
	XrFile*   fp;
};

#endif //_CXR_XrFile_HANDER_H