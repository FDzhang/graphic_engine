#include "CDataStream.h"
#include "../External/xrUtility.h"

static CXRString AccessModeToString(UInt16 accessmode)
{
	CXRString str;
	if( accessmode & CDataStream::READ &&
		accessmode & CDataStream::WRITE ) 
	{
		str = "wb";
	}
	else if( accessmode & CDataStream::READ )
	{
		str = "rb+";
	}
	else if( accessmode & CDataStream::WRITE )
		str = "wb";
	
	return str;
}
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    template <typename T> CDataStream& CDataStream::operator >>(T& val)
    {
        read(static_cast<void*>(&val), sizeof(T));
        return *this;
    }
    //-----------------------------------------------------------------------
    CXRString CDataStream::getLine(Boolean trimAfter)
    {
        CHAR tmpBuf[XR_STREAM_TEMP_SIZE];
        CXRString retString;
        UInt32 readCount;
        // Keep looping while not hitting delimiter
        while ((readCount = read(tmpBuf, XR_STREAM_TEMP_SIZE-1)) != 0)
        {
            // Terminate string
            tmpBuf[readCount] = '\0';

            CHAR* p = strchr(tmpBuf, '\n');
            if (p != 0)
            {
                // Reposition backwards
                skip((Long)(p + 1 - tmpBuf - readCount));
                *p = '\0';
            }

            retString += tmpBuf;

            if (p != 0)
            {
                // Trim off trailing CR if this was a CR/LF entry
                if (retString.length() && retString[retString.length()-1] == '\r')
                {
                    retString.erase(retString.length()-1, 1);
                }

                // Found terminator, break out
                break;
            }
        }

        //if (trimAfter)
        //{
        //    StringUtil::trim(retString);
        //}

        return retString;
    }
    //-----------------------------------------------------------------------
    UInt32 CDataStream::readLine(CHAR* buf, UInt32 maxCount, const CXRString& delim)
    {
		// Deal with both Unix & Windows LFs
		Boolean trimCR = FALSE;
		if (delim.find_first_of('\n') != CXRString::npos)
		{
			trimCR = true;
		}

        CHAR tmpBuf[XR_STREAM_TEMP_SIZE];
        UInt32 chunkSize = XR_MIN(maxCount, (UInt32)XR_STREAM_TEMP_SIZE-1);
        UInt32 totalCount = 0;
        UInt32 readCount; 
        while (chunkSize && (readCount = read(tmpBuf, chunkSize)) != 0)
        {
            // Terminate
            tmpBuf[readCount] = '\0';

            // Find first delimiter
            UInt32 pos = strcspn(tmpBuf, delim.c_str());

            if (pos < readCount)
            {
                // Found terminator, reposition backwards
                skip((Long)(pos + 1 - readCount));
            }

            // Are we genuinely copying?
            if (buf)
            {
                memcpy(buf+totalCount, tmpBuf, pos);
            }
            totalCount += pos;

            if (pos < readCount)
            {
                // Trim off trailing CR if this was a CR/LF entry
                if (trimCR && totalCount && buf[totalCount-1] == '\r')
                {
                    --totalCount;
                }

                // Found terminator, break out
                break;
            }

            // Adjust chunkSize for next time
            chunkSize = XR_MIN(maxCount-totalCount, (UInt32)XR_STREAM_TEMP_SIZE-1);
        }

        // Terminate
        buf[totalCount] = '\0';

        return totalCount;
    }
    //-----------------------------------------------------------------------
    UInt32 CDataStream::skipLine(const CXRString& delim)
    {
        CHAR tmpBuf[XR_STREAM_TEMP_SIZE];
        UInt32 total = 0;
        UInt32 readCount;
        // Keep looping while not hitting delimiter
        while ((readCount = read(tmpBuf, XR_STREAM_TEMP_SIZE-1)) != 0)
        {
            // Terminate string
            tmpBuf[readCount] = '\0';

            // Find first delimiter
            UInt32 pos = strcspn(tmpBuf, delim.c_str());

            if (pos < readCount)
            {
                // Found terminator, reposition backwards
                skip((Long)(pos + 1 - readCount));

                total += pos + 1;

                // break out
                break;
            }

            total += readCount;
        }

        return total;
    }
    //-----------------------------------------------------------------------
    CXRString CDataStream::getAsstring(void)
    {
        // Read the entire buffer - ideally in one read, but if the size of
        // the buffer is unknown, do multiple fixed size reads.
        UInt32 bufSize = (mSize > 0 ? mSize : 4096);
        CHAR* pBuf = Xr_malloc(CHAR,sizeof(CHAR)*bufSize);//OGRE_ALLOC_T(char, bufSize, MEMCATEGORY_GENERAL);
        // Ensure read from begin of stream
        seek(0);
        CXRString result;
        while (!eof())
        {
            UInt32 nr = read(pBuf, bufSize);
            result.append(pBuf, nr);
        }
        Xr_free(pBuf);//OGRE_FREE(pBuf, MEMCATEGORY_GENERAL);
        return result;
    }
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    CMemoryDataStream::CMemoryDataStream(void* pMem, UInt32 inSize, Boolean freeOnClose, Boolean readOnly)
		: CDataStream(static_cast<UInt16>(readOnly ? READ : (READ | WRITE)))
    {
        mData = mPos = static_cast<UChar*>(pMem);
        mSize = inSize;
        mEnd = mData + mSize;
        mFreeOnClose = freeOnClose;
        assert(mEnd >= mPos);
    }
    //-----------------------------------------------------------------------
    CMemoryDataStream::CMemoryDataStream(const CXRString& name, void* pMem, UInt32 inSize, 
        Boolean freeOnClose, Boolean readOnly)
        : CDataStream(name, static_cast<UInt16>(readOnly ? READ : (READ | WRITE)))
    {
        mData = mPos = static_cast<UChar*>(pMem);
        mSize = inSize;
        mEnd = mData + mSize;
        mFreeOnClose = freeOnClose;
        assert(mEnd >= mPos);
    }
    //-----------------------------------------------------------------------
    CMemoryDataStream::CMemoryDataStream(CDataStream& sourceStream, 
        Boolean freeOnClose, Boolean readOnly)
        : CDataStream(static_cast<UInt16>(readOnly ? READ : (READ | WRITE)))
    {
        // Copy data from incoming stream
        mSize = sourceStream.size();
        if (mSize == 0 && !sourceStream.eof())
        {
            // size of source is unknown, read all of it into memory
            CXRString contents = sourceStream.getAsstring();
            mSize = contents.size();
            mData = Xr_malloc(UChar,sizeof(UChar)*mSize);
            mPos = mData;
            memcpy(mData, contents.data(), mSize);
            mEnd = mData + mSize;
        }
        else
        {
            mData = Xr_malloc(UChar,sizeof(UChar)*mSize);
            mPos = mData;
            mEnd = mData + sourceStream.read(mData, mSize);
            mFreeOnClose = freeOnClose;
        }
        assert(mEnd >= mPos);
    }
   
    //-----------------------------------------------------------------------
    CMemoryDataStream::CMemoryDataStream(const CXRString& name, CDataStream& sourceStream, 
        Boolean freeOnClose, Boolean readOnly)
        : CDataStream(name, static_cast<UInt16>(readOnly ? READ : (READ | WRITE)))
    {
        // Copy data from incoming stream
        mSize = sourceStream.size();
        if (mSize == 0 && !sourceStream.eof())
        {
            // size of source is unknown, read all of it into memory
            CXRString contents = sourceStream.getAsstring();
            mSize = contents.size();
            mData =  Xr_malloc(UChar,sizeof(UChar)*mSize);
            mPos = mData;
            memcpy(mData, contents.data(), mSize);
            mEnd = mData + mSize;
        }
        else
        {
            mData =  Xr_malloc(UChar,sizeof(UChar)*mSize);
            mPos = mData;
            mEnd = mData + sourceStream.read(mData, mSize);
            mFreeOnClose = freeOnClose;
        }
        assert(mEnd >= mPos);
    }
   
    //-----------------------------------------------------------------------
    CMemoryDataStream::CMemoryDataStream(UInt32 inSize, Boolean freeOnClose, Boolean readOnly)
        : CDataStream(static_cast<UInt16>(readOnly ? READ : (READ | WRITE)))
    {
        mSize = inSize;
        mFreeOnClose = freeOnClose;
        mData =  Xr_malloc(UChar,sizeof(UChar)*mSize);
        mPos = mData;
        mEnd = mData + mSize;
        assert(mEnd >= mPos);
    }
    //-----------------------------------------------------------------------
    CMemoryDataStream::CMemoryDataStream(const CXRString& name, UInt32 inSize, 
        Boolean freeOnClose, Boolean readOnly)
        : CDataStream(name, static_cast<UInt16>(readOnly ? READ : (READ | WRITE)))
    {
        mSize = inSize;
        mFreeOnClose = freeOnClose;
        mData =  Xr_malloc(UChar,sizeof(UChar)*mSize);
        mPos = mData;
        mEnd = mData + mSize;
        assert(mEnd >= mPos);
    }
    //-----------------------------------------------------------------------
    CMemoryDataStream::~CMemoryDataStream()
    {
        close();
    }
    //-----------------------------------------------------------------------
    UInt32 CMemoryDataStream::read(void* buf, UInt32 count)
    {
        UInt32 cnt = count;
        // Read over end of memory?
        if (mPos + cnt > mEnd)
            cnt = mEnd - mPos;
        if (cnt == 0)
            return 0;

        assert (cnt<=count);

        memcpy(buf, mPos, cnt);
        mPos += cnt;
        return cnt;
    }
	//---------------------------------------------------------------------
	UInt32 CMemoryDataStream::write(const void* buf, UInt32 count)
	{
		UInt32 written = 0;
		if (isWriteable())
		{
			written = count;
			// we only allow writing within the extents of allocated memory
			// check for buffer overrun & disallow
			if (mPos + written > mEnd)
				written = mEnd - mPos;
			if (written == 0)
				return 0;

			memcpy(mPos, buf, written);
			mPos += written;
		}
		return written;
	}
    //-----------------------------------------------------------------------
    UInt32 CMemoryDataStream::readLine(CHAR* buf, UInt32 maxCount, 
        const CXRString& delim)
    {
        // Deal with both Unix & Windows LFs
		Boolean trimCR = FALSE;
		if (delim.find_first_of('\n') != CXRString::npos)
		{
			trimCR = true;
		}

        UInt32 pos = 0;

        // Make sure pos can never go past the end of the data 
        while (pos < maxCount && mPos < mEnd)
        {
			if (delim.find_first_of(*mPos) != CXRString::npos)
            {
                // Trim off trailing CR if this was a CR/LF entry
                if (trimCR && pos && buf[pos-1] == '\r')
                {
                    // terminate 1 character early
                    --pos;
                }

                // Found terminator, skip and break out
                ++mPos;
                break;
            }

            buf[pos++] = *mPos++;
        }

        // terminate
        buf[pos] = '\0';

        return pos;
    }
    //-----------------------------------------------------------------------
    UInt32 CMemoryDataStream::skipLine(const CXRString& delim)
    {
        UInt32 pos = 0;

        // Make sure pos can never go past the end of the data 
        while (mPos < mEnd)
        {
            ++pos;
			if (delim.find_first_of(*mPos++) != CXRString::npos)
            {
                // Found terminator, break out
                break;
            }
        }

        return pos;

    }
    //-----------------------------------------------------------------------
    void CMemoryDataStream::skip(Long count)
    {
        UInt32 newpos = (UInt32)( ( mPos - mData ) + count );
        assert( mData + newpos <= mEnd );        

        mPos = mData + newpos;
    }
    //-----------------------------------------------------------------------
    void CMemoryDataStream::seek( UInt32 pos )
    {
        assert( mData + pos <= mEnd );
        mPos = mData + pos;
    }
    //-----------------------------------------------------------------------
    UInt32 CMemoryDataStream::tell(void) const
	{
		//mData is start, mPos is current location
		return mPos - mData;
	}
	//-----------------------------------------------------------------------
    Boolean CMemoryDataStream::eof(void) const
    {
        return mPos >= mEnd;
    }
    //-----------------------------------------------------------------------
    void CMemoryDataStream::close(void)    
    {
        if (mFreeOnClose && mData)
        {
            Xr_free(mData);
            mData = 0;
        }

    }

    CFileHandleDataStream::CFileHandleDataStream(FILE* handle, UInt16 accessMode)
        : CDataStream(accessMode), mFileHandle(handle)
    {
		// Determine size
		fseek(mFileHandle, 0, SEEK_END);
		mSize = ftell(mFileHandle);
		fseek(mFileHandle, 0, SEEK_SET);
    }
    //-----------------------------------------------------------------------
    CFileHandleDataStream::CFileHandleDataStream(const CXRString& name, FILE* handle, UInt16 accessMode)
        : CDataStream(name, accessMode), mFileHandle(handle)
    {
		// Determine size
		fseek(mFileHandle, 0, SEEK_END);
		mSize = ftell(mFileHandle);
		fseek(mFileHandle, 0, SEEK_SET);
    }
	CFileHandleDataStream::CFileHandleDataStream(const CXRString& name, UInt16 accessMode)
		: CDataStream(accessMode), mFileHandle(NULL)
	{
		this->mFileHandle = fopen(name.c_str(),AccessModeToString(accessMode).c_str());
		fseek(mFileHandle, 0, SEEK_END);
		mSize = ftell(mFileHandle);
		fseek(mFileHandle, 0, SEEK_SET);
	}
    //-----------------------------------------------------------------------
    CFileHandleDataStream::~CFileHandleDataStream()
    {
        close();
    }
    //-----------------------------------------------------------------------
    UInt32 CFileHandleDataStream::read(void* buf, UInt32 count)
    {
        return fread(buf, 1, count, mFileHandle);
    }
	//-----------------------------------------------------------------------
	UInt32 CFileHandleDataStream::write(const void* buf, UInt32 count)
	{
		if (!isWriteable())
			return 0;
		else
			return fwrite(buf, 1, count, mFileHandle);
	}
	//---------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void CFileHandleDataStream::skip(Long count)
    {
        fseek(mFileHandle, count, SEEK_CUR);
    }
    //-----------------------------------------------------------------------
    void CFileHandleDataStream::seek( UInt32 pos )
    {
        fseek(mFileHandle, static_cast<Long>(pos), SEEK_SET);
    }
    //-----------------------------------------------------------------------
    UInt32 CFileHandleDataStream::tell(void) const
	{
		return ftell( mFileHandle );
	}
	//-----------------------------------------------------------------------
    Boolean CFileHandleDataStream::eof(void) const
    {
        return feof(mFileHandle) != 0;
    }
    //-----------------------------------------------------------------------
    void CFileHandleDataStream::close(void)
    {
		if (mFileHandle != 0)
		{
			fclose(mFileHandle);
			mFileHandle = 0;
		}
    }
    //-----------------------------------------------------------------------

