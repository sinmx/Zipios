#include "zipios++/zipios-config.h"

#if defined (HAVE_STD_IOSTREAM) && defined (USE_STD_IOSTREAM)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#include "ziphead.h"

using namespace std ;
using namespace zipios ;

char *_progname ;

void printUsage() ;
void exitUsage( int exit_code ) ;

int main( int argc, char *argv[] ) {
  _progname = argv[ 0 ] ;
  if ( argc != 3 ) 
    exitUsage( 1 ) ;
  
  ofstream  exef( argv[ 1 ], ios::app ) ;
  if( ! exef ) {
    cout << "Error: Unable to open " << argv[ 1 ] << " for writing" << endl ;
    exitUsage( 1 ) ;
  }

  ifstream  zipf( argv[ 2 ] ) ;
  if( ! zipf ) {
    cout << "Error: Unable to open " << argv[ 2 ] << " for reading." << endl ;
    exitUsage( 1 ) ;
  }

  // get eof pos (to become zip file starting position).
  uint32 zip_start = exef.tellp() ;
  cout << "zip start will be at " << zip_start << endl ;

  // Append zip file to exe file

  exef << zipf.rdbuf() ;
  // write zipfile start offset to file
  writeUint32( zip_start, exef ) ;

  exef.close() ;
  zipf.close() ;
}


void printUsage() {
  cout << "Usage:  " << _progname << " exe-file zipfile" << endl ;
}

void exitUsage( int exit_code ) {
  printUsage() ;
  exit( exit_code ) ;
}

/** \file
    \anchor appendzip_anchor
    Source code to a small program appendzip that appends a zip 
    archive to another file. Run appendzip without arguments to
    get a helpful usage message.
*/

/*
  Zipios++ - a small C++ library that provides easy access to .zip files.
  Copyright (C) 2000  Thomas S�ndergaard
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/