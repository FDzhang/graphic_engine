#ifndef _CDATASTREAM_H
#define _CDATASTREAM_H
#include "../External/xrTypes.h"
#include "../Platform/XrOS.h"
#include "../Common/XrInternal.h"

	class  CDataStream 
	{
	public:
		enum AccessMode
		{
			READ = 1, 
			WRITE = 2
		};
	protected:
		/// The name (e.g. resource name) that can be used to identify the source fot his data (optional)
		CXRString mName;		
        /// Size of the data in the stream (may be 0 if size cannot be determined)
        UInt32 mSize;
		/// What type of access is allowed (AccessMode)
		UInt16 mAccess;

        #define XR_STREAM_TEMP_SIZE 128
	public:
		/// Constructor for creating unnamed streams
        CDataStream(UInt16 accessMode = READ) : mSize(0), mAccess(accessMode) {}
		/// Constructor for creating named streams
		CDataStream(const CXRString& name, UInt16 accessMode = READ) 
			: mName(name), mSize(0), mAccess(accessMode) {}
		/// Returns the name of the stream, if it has one.
		const CXRString& getName(void) { return mName; }
		/// Gets the access mode of the stream
		UInt16 getAccessMode() const { return mAccess; }
		/** Reports whether this stream is readable. */
		virtual Boolean isReadable() const { return (mAccess & READ) != 0; }
		/** Reports whether this stream is writeable. */
		virtual Boolean isWriteable() const { return (mAccess & WRITE) != 0; }
        virtual ~CDataStream() {}
		// Streaming operators
        template<typename T> CDataStream& operator>>(T& val);
		/** Read the requisite number of bytes from the stream, 
			stopping at the end of the file.
		@param buf Reference to a buffer pointer
		@param count Number of bytes to read
		@returns The number of bytes read
		*/
		virtual UInt32 read(void* buf, UInt32 count) = 0;
		/** Write the requisite number of bytes from the stream (only applicable to 
			streams that are not read-only)
		@param buf Pointer to a buffer containing the bytes to write
		@param count Number of bytes to write
		@returns The number of bytes written
		*/
		virtual UInt32 write(const void* buf, UInt32 count)
		{
                        (void)buf;
                        (void)count;
			// default to not supported
			return 0;
		}

		/** Get a single line from the stream.
		@remarks
			The delimiter character is not included in the data
			returned, and it is skipped over so the next read will occur
			after it. The buffer contents will include a
			terminating character.
        @note
            If you used this function, you <b>must</b> open the stream in <b>binary mode</b>,
            otherwise, it'll produce unexpected results.
		@param buf Reference to a buffer pointer
		@param maxCount The maximum length of data to be read, excluding the terminating character
		@param delim The delimiter to stop at
		@returns The number of bytes read, excluding the terminating character
		*/
		virtual UInt32 readLine(CHAR* buf, UInt32 maxCount, const CXRString& delim = "\n");
		
	    /** Returns a string containing the next line of data, optionally 
		    trimmed for whitespace. 
	    @remarks
		    This is a convenience method for text streams only, allowing you to 
		    retrieve a string object containing the next line of data. The data
		    is read up to the next newline character and the result trimmed if
		    required.
        @note
            If you used this function, you <b>must</b> open the stream in <b>binary mode</b>,
            otherwise, it'll produce unexpected results.
	    @param 
		    trimAfter If TRUE, the line is trimmed for whitespace (as in 
		    string.trim(TRUE,TRUE))
	    */
	    virtual CXRString getLine( Boolean trimAfter = TRUE );

	    /** Returns a string containing the entire stream. 
	    @remarks
		    This is a convenience method for text streams only, allowing you to 
		    retrieve a string object containing all the data in the stream.
	    */
	    virtual CXRString getAsstring(void);

		/** Skip a single line from the stream.
        @note
            If you used this function, you <b>must</b> open the stream in <b>binary mode</b>,
            otherwise, it'll produce unexpected results.
		@param delim The delimiter(s) to stop at
		@returns The number of bytes skipped
		*/
		virtual UInt32 skipLine(const CXRString& delim = "\n");

		/** Skip a defined number of bytes. This can also be a negative value, in which case
		the file pointer rewinds a defined number of bytes. */
		virtual void skip(Long count) = 0;
	
		/** Repositions the read point to a specified byte.
	    */
	    virtual void seek( UInt32 pos ) = 0;
		
		/** Returns the current byte offset from beginning */
	    virtual UInt32 tell(void) const = 0;

		/** Returns TRUE if the stream has reached the end.
	    */
	    virtual Boolean eof(void) const = 0;

		/** Returns the total size of the data to be read from the stream, 
			or 0 if this is indeterminate for this stream. 
		*/
        UInt32 size(void) const { return mSize; }

        /** Close the stream; this makes further operations invalid. */
        virtual void close(void) = 0;
		

	};

	
	/** Common subclass of CDataStream for handling data from chunks of memory.
	*/
	class CMemoryDataStream : public CDataStream
	{
	protected:
        /// Pointer to the start of the data area
	    UChar* mData;
        /// Pointer to the current position in the memory
	    UChar* mPos;
        /// Pointer to the end of the memory
	    UChar* mEnd;
        /// Do we delete the memory on close
		Boolean mFreeOnClose;			
	public:
		
		/** Wrap an existing memory chunk in a stream.
		@param pMem Pointer to the existing memory
		@param size The size of the memory chunk in bytes
		@param freeOnClose If TRUE, the memory associated will be destroyed
			when the stream is destroyed. Note: it's important that if you set
			this option to TRUE, that you allocated the memory using OGRE_ALLOC_T
			with a category of MEMCATEGORY_GENERAL ensure the freeing of memory 
			matches up.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		CMemoryDataStream(void* pMem, UInt32 size, Boolean freeOnClose = FALSE, Boolean readOnly = FALSE);
		
		/** Wrap an existing memory chunk in a named stream.
		@param name The name to give the stream
		@param pMem Pointer to the existing memory
		@param size The size of the memory chunk in bytes
		@param freeOnClose If TRUE, the memory associated will be destroyed
			when the stream is destroyed. Note: it's important that if you set
			this option to TRUE, that you allocated the memory using OGRE_ALLOC_T
			with a category of MEMCATEGORY_GENERAL ensure the freeing of memory 
			matches up.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		CMemoryDataStream(const CXRString& name, void* pMem, UInt32 size, 
				Boolean freeOnClose = FALSE, Boolean readOnly = FALSE);

		/** Create a stream which pre-buffers the contents of another stream.
		@remarks
			This constructor can be used to intentionally read in the entire
			contents of another stream, copying them to the internal buffer
			and thus making them available in memory as a single unit.
		@param sourceStream Another CDataStream which will provide the source
			of data
		@param freeOnClose If TRUE, the memory associated will be destroyed
			when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		CMemoryDataStream(CDataStream& sourceStream, 
				Boolean freeOnClose = TRUE, Boolean readOnly = FALSE);
		
	

		/** Create a named stream which pre-buffers the contents of 
			another stream.
		@remarks
			This constructor can be used to intentionally read in the entire
			contents of another stream, copying them to the internal buffer
			and thus making them available in memory as a single unit.
		@param name The name to give the stream
		@param sourceStream Another CDataStream which will provide the source
			of data
		@param freeOnClose If TRUE, the memory associated will be destroyed
			when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		CMemoryDataStream(const CXRString& name, CDataStream& sourceStream, 
				Boolean freeOnClose = TRUE, Boolean readOnly = FALSE);


        /** Create a stream with a brand new empty memory chunk.
		@param size The size of the memory chunk to create in bytes
		@param freeOnClose If TRUE, the memory associated will be destroyed
			when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		CMemoryDataStream(UInt32 size, Boolean freeOnClose = TRUE, Boolean readOnly = FALSE);
		/** Create a named stream with a brand new empty memory chunk.
		@param name The name to give the stream
		@param size The size of the memory chunk to create in bytes
		@param freeOnClose If TRUE, the memory associated will be destroyed
			when the stream is destroyed.
		@param readOnly Whether to make the stream on this memory read-only once created
		*/
		CMemoryDataStream(const CXRString& name, UInt32 size, 
				Boolean freeOnClose = TRUE, Boolean readOnly = FALSE);

		~CMemoryDataStream();

		/** Get a pointer to the start of the memory block this stream holds. */
		UChar* getPtr(void) { return mData; }
		
		/** Get a pointer to the current position in the memory block this stream holds. */
		UChar* getCurrentPtr(void) { return mPos; }
		
		/** @copydoc CDataStream::read
		*/
		UInt32 read(void* buf, UInt32 count);

		/** @copydoc CDataStream::write
		*/
		UInt32 write(const void* buf, UInt32 count);

		/** @copydoc CDataStream::readLine
		*/
		UInt32 readLine(CHAR* buf, UInt32 maxCount, const CXRString& delim = "\n");
		
		/** @copydoc CDataStream::skipLine
		*/
		UInt32 skipLine(const CXRString& delim = "\n");

		/** @copydoc CDataStream::skip
		*/
		void skip(Long count);
	
		/** @copydoc CDataStream::seek
		*/
	    void seek( UInt32 pos );
		
		/** @copydoc CDataStream::tell
		*/
	    UInt32 tell(void) const;

		/** @copydoc CDataStream::eof
		*/
	    Boolean eof(void) const;

        /** @copydoc CDataStream::close
        */
        void close(void);

		/** Sets whether or not to free the encapsulated memory on close. */
		void setFreeOnClose(Boolean free) { mFreeOnClose = free; }
	};

  
   
	class CFileHandleDataStream : public CDataStream
	{
	protected:
		FILE* mFileHandle;
	public:
		/// Create stream from a C file handle
		CFileHandleDataStream(FILE* handle, UInt16 accessMode = READ);
		/// Create named stream from a C file handle
		CFileHandleDataStream(const CXRString& name, FILE* handle, UInt16 accessMode = READ);
		/// create stream from a file name 
		CFileHandleDataStream(const CXRString& name, UInt16 accessMode = READ);
        ~CFileHandleDataStream();

		/** @copydoc CDataStream::read
		*/
		UInt32 read(void* buf, UInt32 count);

		/** @copydoc CDataStream::CFileHandleDataStream
		*/
		UInt32 write(const void* buf, UInt32 count);

		/** @copydoc CDataStream::skip
		*/
		void skip(Long count);
	
		/** @copydoc CDataStream::seek
		*/
	    void seek( UInt32 pos );

		/** @copydoc CDataStream::tell
		*/
		UInt32 tell(void) const;

		/** @copydoc CDataStream::eof
		*/
	    Boolean eof(void) const;

        /** @copydoc CDataStream::close
        */
        void close(void);

	};

#endif