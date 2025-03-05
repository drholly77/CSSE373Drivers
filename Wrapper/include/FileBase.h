#pragma once
#pragma warning( disable : 26495 )

// Simple File
// Author: Dr. Holly

class FileBase
{
public: // Standard Operations
	FileBase ();
	~FileBase ();
	void clear (void);
	void transferFrom(FileBase& source);

/*
	tuple of
		fileOpened : Boolean
		ioDirection : Integer
		eof : Boolean

  exemplar
		f

	initially
		!f.fileOpened  and  f.ioDirection = read  and  f.eof
*/

	enum {
		// File_Io_Constants
		openForRead			= 0,
		openForWrite		= 1,
		total			= 2
	};

	// FileBase Specific Operations
	void openFile (Text& fileName, Integer ioDirection, Boolean& successful);
	//! restores fileName, ioDirection
	//! replaces successful
	//! requires: !f.fileOpened  and
	//!		(f.ioDirection = read  or  f.ioDirection = write)
	//! ensures:
	//!		(f.fileOpened  and  successful
	//!		 or
	//!		!f.fileOpened  and  !successful) 
	//!		and  f.ioDirection = ioDirection
	//!		and  f.eof  iff at end of file

	void closeFile (Boolean& successful);
	//! replaces successful
	//! requires: f.fileOpened
	//! ensures:
	//!		f.fileOpened

	Boolean fileOpened (void);
	//! ensures:
	//!		fileOpened = f.fileOpened

	Integer ioDirection (void);
	//! requires: f.fileOpened
	//! ensures:
	//!		ioDirection = f.ioDirection

	Boolean endOfFile (void);
	//! requires: f.fileOpened
	//! ensures:
	//!		endOfFile = f.eof
	
	void read (Boolean& x, Boolean& successful);
	//! replaces x, successful
	//! requires: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Boolean  where y is
	//!		next formatted item to be read from the file
	//! ensures:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void read (Character& x, Boolean& successful);
	//! replaces x, successful
	//! requires: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Character  where y is
	//!		next formatted item to be read from the file
	//! ensures:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void read (Float& x, Boolean& successful);
	//! replaces x, successful
	//! requires: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Float  where y is
	//!		next formatted item to be read from the file
	//! ensures:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void read (Integer& x, Boolean& successful);
	//! replaces x, successful
	//! requires: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Integer  where y is
	//!		next formatted item to be read from the file
	//! ensures:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void read (LongInteger& x, Boolean& successful);
	//! replaces x, successful
	//! requires: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : LongInteger  where y is
	//!		next formatted item to be read from the file
	//! ensures:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly


	void read (Text& s, Boolean& successful);
	//! replaces s, successful
	//! requires: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Text  where y is
	//!		next formatted item to be read from the file
	//! ensures:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void write (Boolean x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a formatted Boolean
	//!		and  successful if x was written correctly

	void write (Character x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a formatted Character
	//!		and  successful if x was written correctly

	void write (Float x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a formatted Float
	//!		and  successful if x was written correctly

	void write (Integer x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a formatted Integer
	//!		and  successful if x was written correctly

	void write (LongInteger x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a formatted LongInteger
	//!		and  successful if x was written correctly

	void write (Text& s, Boolean& successful);
	//! restores s
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a formatted Text
	//!		and  successful if x was written correctly


	void writeRaw (Boolean x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a unformatted Boolean
	//!		and  successful if x was written correctly

	void writeRaw (Character x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a unformatted Character
	//!		and  successful if x was written correctly

	void writeRaw (Float x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a unformatted Float
	//!		and  successful if x was written correctly

	void writeRaw (Integer x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a unformatted Integer
	//!		and  successful if x was written correctly

	void writeRaw (LongInteger x, Boolean& successful);
	//! restores x
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a unformatted LongInteger
	//!		and  successful if x was written correctly

	void writeRaw (Text& s, Boolean& successful);
	//! restores s
	//! replaces successful
	//! requires: f.fileOpened  and  f.ioDirection = write
	//! ensures:
	//!		x has been written to file the file as a unformatted Text
	//!		and  successful if x was written correctly


private: // Representation
	class fileRep {
	public:
		FILE* file;
		Boolean fileOpen;
		Integer ioDirection;

		fileRep() {};
	};
	fileRep* rep;

	// Disallowed FileBase Operations
	FileBase& operator = (const FileBase& rhs);
	FileBase (const FileBase& s);
	FileBase* operator & (void) {return (this);};
	const FileBase* operator & (void) const {return (this);};
};	// end FileBase


