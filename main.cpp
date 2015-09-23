#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include "ImfInputFile.h"
#include "ImfRgbaFile.h"
#include "ImfArray.h"
#include "ImfChannelList.h"

#include <set>
#include <string>
#include <vector>

#define FILENAME "img\\Ocean.exr"
//#define FILENAME "img\\MambaTutorials-com_EXR_exampleFile.exr"
//#define FILENAME "img\\tree.pt.exr"


void loadTest( const char* fileName );
void loadFileInfo( const char* fileName );

int main() {

    loadTest( FILENAME );
    loadFileInfo( FILENAME );

    return 0;
}


void loadTest( const char* fileName ) {
    using namespace Imf;
    using namespace Imath;
    try {
        RgbaInputFile in(fileName);
        Box2i wm = in.header().dataWindow();
        V2i dim( wm.max.x-wm.min.x+1, wm.max.y-wm.min.y+1 );
        Rgba* pixels = new Rgba[ dim.x * dim.y ];

        in.setFrameBuffer( pixels, 1, dim.x );
        in.readPixels( wm.min.y, wm.max.y );

        delete[] pixels;
        pixels = 0;
    } catch( Iex::ErrnoExc& e ) {
        printf( e.what() );
#if _DEBUG
        OutputDebugStringA( e.what() );
#endif
    }
}

void loadFileInfo( const char* fileName ) {
    using namespace Imf;
    using namespace Imath;
    try {
        InputFile in(fileName);
    } catch( Iex::ErrnoExc& e ) {
        printf( e.what() );
#if _DEBUG
        OutputDebugStringA( e.what() );
#endif
    }
}
