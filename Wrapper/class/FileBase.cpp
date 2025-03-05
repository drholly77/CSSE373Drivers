// Simple File
// Author: Dr. Holly

#include "wrapper.h"
#pragma warning( disable : 4267)
//-----------------------------------------------------------------------
//	Local Operations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
//	Exported Operations
//-----------------------------------------------------------------------

FileBase::FileBase ()
{
   rep = new fileRep;
   rep->file = NULL;
}	// FileBase

//-----------------------------------------------------------------------

FileBase::~FileBase ()
{
	if (rep->fileOpen) {
		fclose (rep->file);
	}  // end if
	delete rep;
}	// ~FileBase

//-----------------------------------------------------------------------

void FileBase::transferFrom(FileBase& source)
{
	rep->file = source.rep->file;
	source.rep->file = NULL;

	rep->fileOpen.transferFrom(source.rep->fileOpen);
	rep->ioDirection.transferFrom(source.rep->ioDirection);
} // transferFrom

//-----------------------------------------------------------------------

void FileBase::clear (void)
{
	if (rep->fileOpen) {
		fclose (rep->file);
	}  // end if
	delete rep;
	rep = new fileRep;
	rep->file = NULL;
}	// clear

//-----------------------------------------------------------------------

void FileBase::openFile (
			Text& fileName,
			Integer ioDirection,
			Boolean& successful
		)
{
	Integer readWrite, i, z;

	rep->ioDirection = ioDirection;
	switch (ioDirection) {
		case openForRead:
			WIN32_FIND_DATA findData;
			HANDLE fileHandle;

			// See if file exists, if not successful will be set to false
			fileHandle = FindFirstFile (fileName, &findData);
			successful = (fileHandle != INVALID_HANDLE_VALUE);
			if (successful) {
				FindClose (fileHandle);
				rep->file = _wfopen (fileName, L"r");
				successful = (rep->file != NULL);
			}	// end if
			break;
		case openForWrite:
			rep->file = _wfopen (fileName, L"w");
			successful = (rep->file != NULL);
			break;
	}	// end switch

	if (successful)
		rep->fileOpen = true;
}	// openFile

//-----------------------------------------------------------------------

void FileBase::closeFile (
			Boolean& successful
		)
{
	const int successfulClose = 0;
	Integer return_code;

	rep->fileOpen = false;
	return_code = fclose (rep->file);
	successful = (return_code == successfulClose);
}	// closeFile

//-----------------------------------------------------------------------

Boolean FileBase::fileOpened (void)
{
	return rep->fileOpen;
}	// fileOpened

//-----------------------------------------------------------------------

Integer FileBase::ioDirection (void)
{
	return rep->ioDirection;
}	// ioDirection

//-----------------------------------------------------------------------

Boolean FileBase::endOfFile (void)
{
	// feof does not detect being at the end of the file unless a read has tried to
	// read past the end of file
	// To detect end of file:
	// 1) Get current file position
	// 2) Execute a read
	// 3) Call feof to record if the previous read tried to read past the end of file
	// 4) Set current file position back to position recorded in #1
	// 5) return true/false based on what was recorded in #3
	Boolean eof;

	wchar_t charArray[2];
	fpos_t pos;
	fgetpos(rep->file, &pos);
	fread(charArray, sizeof(wchar_t), 1, rep->file);
	
	eof = (feof(rep->file) == 0) ? false : true;
	fsetpos(rep->file, &pos);
	return eof;
}	// endOfFile

//-----------------------------------------------------------------------

void FileBase::read (
			Character& x,
			Boolean& successful
		)
{
	wchar_t charArray[2];
	LongInteger itemsRead;

	// read the string, then copy to Text
	itemsRead = fread(charArray, sizeof(wchar_t), 1, rep->file);
	successful = ((itemsRead == 1) && !ferror (rep->file));

	if (successful) {
		x = (char)charArray[0];
	}	// end if
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Character x,
			Boolean& successful
		)
{
	Integer itemsWritten;
	Text s;

	s.add (0, x);

	itemsWritten = fwrite (s, sizeof(wchar_t), 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			Float& x,
			Boolean& successful
		)
{
	wchar_t* cString;
	float value;
	Integer stringLength;
	Integer itemsRead;

	// read string length, then convert to Integer
	read (stringLength, successful);
	if (successful) {
		cString = (wchar_t *)new wchar_t[stringLength + 1];

		// read the string, then copy to Text
		itemsRead = fread (cString, sizeof(wchar_t), stringLength, rep->file);
		successful = ((itemsRead == stringLength) && !ferror (rep->file));

		if (successful) {
			cString[stringLength] = '\0';
			swscanf (cString, L"%f", &value);
			x = value;
		}	// end if
		delete [] cString;
	}	// end if
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Float x,
			Boolean& successful
		)
{
	const int floatWidth = 30;
	wchar_t cString[floatWidth];
	Integer length;
	Integer itemsWritten;

	length = swprintf (cString, floatWidth, L"%#.10f", (float)x);
	write (length, successful);
	itemsWritten = fwrite (cString, sizeof(wchar_t), length, rep->file);
	successful = ((itemsWritten == length) && !ferror (rep->file));
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			Integer& x,
			Boolean& successful
		)
{
	static const int integerLengthWidth = 6;
	wchar_t cString[integerLengthWidth + 1];
	int value;
	Integer itemsRead;

	// read value as string, then convert to Integer
	itemsRead = fread (cString, sizeof(wchar_t), integerLengthWidth, rep->file);
	successful = ((itemsRead == integerLengthWidth) && !ferror (rep->file));
	cString[integerLengthWidth] = '\0';
	swscanf (cString, L"%d", &value);
	x = value;
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Integer x,
			Boolean& successful
		)
{
	static const int integerLengthWidth = 6;
	wchar_t cString[integerLengthWidth + 1];
	Integer length;
	Integer itemsWritten;

	length = swprintf (cString, integerLengthWidth + 1, L"%6d", (int)x);
	itemsWritten = fwrite (cString, sizeof(wchar_t), length, rep->file);
	successful = ((itemsWritten == length) && !ferror (rep->file));
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			LongInteger& x,
			Boolean& successful
		)
{
	static const int integerLengthWidth = 25;
	wchar_t cString[integerLengthWidth + 1];
	long value;
	Integer itemsRead;

	// read value as string, then convert to Integer
	itemsRead = fread (cString, sizeof(wchar_t), integerLengthWidth, rep->file);
	successful = ((itemsRead == integerLengthWidth) && !ferror (rep->file));
	cString[integerLengthWidth] = '\0';
	swscanf (cString, L"%ld", &value);
	x = value;
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			LongInteger x,
			Boolean& successful
		)
{
	static const int longIntegerLengthBytes = 25;
	wchar_t cString[longIntegerLengthBytes + 1];
	Integer length;
	Integer itemsWritten;

	length = swprintf (cString, longIntegerLengthBytes + 1, L"%25ld", (long)x);
	itemsWritten = fwrite (cString, sizeof(wchar_t), length, rep->file);
	successful = ((itemsWritten == length) && !ferror (rep->file));
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			Boolean& x,
			Boolean& successful
		)
{
	Integer i;

	read (i, successful);
	x = (i == 1);
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Boolean x,
			Boolean& successful
		)
{
	Integer i;

	if (x) {
		i = 1;
		write (i, successful);
	} else {
		i = 0;
		write (i, successful);
	} // end if
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			Text& s,
			Boolean& successful
		)
{
	Integer stringLength;

	// read string length, then convert to Integer
	read (stringLength, successful);
	if (successful) {
		wchar_t* cString;
		Integer itemsRead;

		cString = (wchar_t *)new wchar_t[stringLength + 1];

		// read the string, then copy to Text
		itemsRead = fread (cString, sizeof(wchar_t), stringLength, rep->file);
		successful = ((itemsRead == stringLength) && !ferror (rep->file));

		if (successful) {
			cString[stringLength] = '\0';
			s = cString;
		}	// end if
		delete [] cString;
	}	// end if
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Text& s,
			Boolean& successful
		)
{
	Integer itemsWritten;
	Integer stringLength;

	stringLength = s.size ();
	write (stringLength, successful);
	if (successful) {
		itemsWritten = fwrite (s, sizeof(wchar_t), stringLength, rep->file);
		successful = ((itemsWritten == stringLength) && !ferror (rep->file));
	}	// end if
}	// write

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Boolean x,
			Boolean& successful
		)
{
	Integer itemsWritten;
	Text t (L"true");
	Text f (L"false");

	if (x) {
		itemsWritten = fwrite (t, sizeof(wchar_t), t.size(), rep->file);
		successful = ((itemsWritten == t.size()) && !ferror(rep->file));
	} else {
		itemsWritten = fwrite (f, sizeof(wchar_t), f.size(), rep->file);
		successful = ((itemsWritten == f.size()) && !ferror(rep->file));
	}	// end if
	
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Character x,
			Boolean& successful
		)
{
	Integer itemsWritten;
	Text s;

	s.add (0, x);

	itemsWritten = fwrite (s, sizeof(wchar_t), 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Float x,
			Boolean& successful
		)
{

	static const int rawFloatLengthWidth = 30;
	wchar_t cString[rawFloatLengthWidth];
	Integer length;
	Integer itemsWritten;

	length = swprintf (cString, rawFloatLengthWidth, L"%f", (float)x);
	itemsWritten = fwrite (cString, sizeof(wchar_t), length, rep->file);
	successful = ((itemsWritten == length) && !ferror (rep->file));
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Integer x,
			Boolean& successful
		)
{
	static const int rawIntegerLengthWidth = 30;
	wchar_t cString[rawIntegerLengthWidth];
	Integer length;
	Integer itemsWritten;

	length = swprintf (cString, rawIntegerLengthWidth, L"%d", (int)x);
	itemsWritten = fwrite (cString, sizeof(wchar_t), length, rep->file);
	successful = ((itemsWritten == length) && !ferror (rep->file));
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			LongInteger x,
			Boolean& successful
		)
{
	static const int rawLongIntegerLengthWidth = 30;
	wchar_t cString[rawLongIntegerLengthWidth];
	Integer length;
	Integer itemsWritten;

	length = swprintf (cString, rawLongIntegerLengthWidth, L"%ld", (long)x);
	itemsWritten = fwrite (cString, sizeof(wchar_t), length, rep->file);
	successful = ((itemsWritten == length) && !ferror (rep->file));
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Text& s,
			Boolean& successful
		)
{
	Integer itemsWritten;

	itemsWritten = fwrite (s, sizeof(wchar_t), s.size(), rep->file);
	successful = ((itemsWritten == s.size()) && !ferror (rep->file));
}	// writeRaw

