#pragma once

/*
	Checking Version of File
	Author: Dr. Holly
*/

template <class StandardFile>
class FileChecking1:
	public StandardFile
{
public:
	void openFile (Text& fileName, Integer ioDirection, Boolean& successful);
	void closeFile (Boolean& successful);

	Integer ioDirection (void);

	Boolean endOfFile (void);

	void read (Boolean& x, Boolean& successful);
	void read (Character& x, Boolean& successful);
	void read (Float& x, Boolean& successful);
	void read (LongInteger& x, Boolean& successful);
	void read (Integer& x, Boolean& successful);
	void read (Text& s, Boolean& successful);

	void write (Boolean x, Boolean& successful);
	void write (Character x, Boolean& successful);
	void write (Float x, Boolean& successful);
	void write (LongInteger x, Boolean& successful);
	void write (Integer x, Boolean& successful);
	void write (Text& s, Boolean& successful);

	void writeRaw (Boolean x,Boolean& successful);
	void writeRaw (Character x, Boolean& successful);
	void writeRaw (Float x, Boolean& successful);
	void writeRaw (LongInteger x, Boolean& successful);
	void writeRaw (Integer x, Boolean& successful);
	void writeRaw (Text& s,	Boolean& successful);
};


//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------


template <class StandardFile>
void FileChecking1<StandardFile>::openFile(Text& fileName, Integer ioDirection, Boolean& successful)
{
	// Assert that file is not open
	if (StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: openFile\n");
		OutputDebugString (L"Assertion failed: !fileOpened\n");
		DebugBreak ();
	}	// end if 

	// Assert that ioDirection is correct
	if (!(ioDirection == StandardFile::openForRead || ioDirection == StandardFile::openForWrite)) {
		OutputDebugString (L"Operation: openFile\n");
		OutputDebugString (L"Assertion failed: correct ioDirection\n");
		DebugBreak ();
	}	// end if

	StandardFile::openFile (fileName, ioDirection, successful);
}	// openFile

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::closeFile(Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: closeFile\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	StandardFile::closeFile (successful);
}	// closeFile

//-------------------------------------------------------------------

template <class StandardFile>
Integer FileChecking1<StandardFile>::ioDirection (void)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: ioDirection\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	return (StandardFile::ioDirection ());
}	// ioDirection

//-------------------------------------------------------------------

template <class StandardFile>
Boolean FileChecking1<StandardFile>::endOfFile (void)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: endOfFile\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	return (StandardFile::endOfFile ());
}	// endOfFile

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (Boolean& x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (Character& x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (Float& x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (LongInteger& x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (Integer& x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (Text& s, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString (L"Operation: read\n");
		OutputDebugString (L"Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (s, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (Boolean x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (Character x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (Float x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (LongInteger x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (Integer x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (Text& s, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: write\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (s, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (Boolean x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (Character x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (Float x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (LongInteger x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (Integer x, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (Text& s, Boolean& successful)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString (L"Operation: writeRaw\n");
		OutputDebugString (L"Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (s, successful);
}	// writeRaw

