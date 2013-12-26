////////////////////////////////////////////////////////////////////////////
//                             Constants.hpp                              //
////////////////////////////////////////////////////////////////////////////


#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED


////////////////////////////////////////////////////////////////////////////
//                       WINDOW RELATED CONSTANTS                         //
////////////////////////////////////////////////////////////////////////////

const  int   WINDOW_WIDTH   =  1080;
const  int   WINDOW_HEIGHT  =  680;
const  int   WINDOW_BPP     =  32;
const  char  *WINDOW_TITLE  =  "BEAT$ATION-MU$IX Mp3 Player";

////////////////////////////////////////////////////////////////////////////
//                     AUDIOPLAYER RELATED CONSTANTS                      //
////////////////////////////////////////////////////////////////////////////

const  float  VOL_STEP         =  0.0005f;
const  int    MAX_NAME_LENGTH  =  500;

////////////////////////////////////////////////////////////////////////////
//                         UI RELATED CONSTANTS                           //
////////////////////////////////////////////////////////////////////////////

const  char  *BLACK_THEME      =  "widgets/Black.conf";
const  char  *BABY_BLUE_THEME  =  "widgets/BabyBlue.conf";
const  char  *WHITE_THEME      =  "widgets/White.conf";

const  char  *GLOBAL_FONT      =  "Resources/Fonts/sansation.ttf";
const  char  *CUSTOM_FONT_1    =  "Resources/Fonts/ARLRDBD.ttf";
const  char  *CUSTOM_FONT_2    =  "Resources/Fonts/BankGothic.ttf";

enum WidgetCallbacks
{
    BUTTON_CALLBACK_ID = 1,
    MENU_CALLBACK_ID,
    LISTBOX_CALLBACK_ID,
    CHILDWINDOW_CALLBACK_ID,
    SLIDER_CALLBACK_ID,
    LABEL_CALLBACK_ID,
    TEXTBOX_CALLBACK_ID,
    CHECKBOX_CALLBACK_ID
};


const  char  *PLAYLIST   =  "myPlaylist.bsm";
const  char  *PLAY_INFO  =  "playlistInfo.bsm";

const  char  *BG_TEXTURE    =  "Resources/Images/backgroundtexture.png";
const  char  *NAME_TEXTURE  =  "Resources/Images/name.png";
const  char  *ABT_TEXTURE   =  "Resources/Images/abouttexture.png";

const  char  *MSG_1  =  "Powered by :\n\n   1. SFML (Simple and Fast Multimedia Library)\n   2. TGUI (Texus' Graphical User Interface)\n   3. Code::Blocks 12.11";
const  char  *MSG_2  =  "1. Click on File > Add a New Song...\n\n2. If the song is in the project directory, just type\n\tthe name of the mp3 file with the .mp3 exten-\n\tsion.\n\n3. If the song is NOT in the project directory, inc-\n\tlude the path before the file name also.\n\n\tFor example, if you have a mp3 file called\n\t'myaudio.mp3' in the folder\n\tE:/Music/Favourites/\n\tthen the valid file name you must type will be\n\tE:/Music/Favourites/myaudio.mp3\n\n4. Click Add to add it to the library.\n\n5. Then restart the application for changes to\n\ttake effect and enjoy :D";
const  char  *MSG_3  =  "Please visit     http://theillusionistmirage.weebly.com";

#endif // CONSTANTS_HPP_INCLUDED


/*******************************************************************************************/
//////////////////////////////     end of AudioPlayer.cpp     ///////////////////////////////
/*******************************************************************************************/
