///////////////////////////////////////////////////////////////////////////////
//                                 MAIN.CPP                                  //
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \mainpage BEATSATION-MUSIX Documentation
///
/// BEAT$ATION-MU$IX MP3 PLAYER (C) Koushtav Chakrabarty\n\n
/// Author      :       Koushtav Chakrabarty\n
/// Class       :       XII-SCI\n
/// Language    :       C++\n
/// IDE         :       Code::Blocks 12.11\n
/// Compiler    :       MinGW (Minimalist GNU for Windows)\n
///
/// This is a simple, yet  poweful  Mp3 player written in C++. This
/// also  uses  the  non-standard  libraries  SFML (Simple and Fast
/// Multimedia  Library),  TGUI (Texus' Graphical User Interface) &
/// irrKlang (a powerful 2D & 3D sound engine) to achive the modest
/// goal of this project - to play Mp3 files and make the listening
/// experience pleasant.
///
/// Though this Mp3 player seems to use a lot of non-standard stuff,
/// it is written in the most simple way.
///
/// When I wanted to play Mp3 files, I needed a good audio library.
/// So,  I Googled 'audio libraries for C++' and the topmost result
/// was irrKlang. Firstly, I checked the online tutorials of irrKlang
/// and also its documentation to make sure that I get accustomed
/// to this library. Then I started making a console mp3 player.
/// I succeeded but I wasn't satisfied. I wanted my Mp3 player  to
/// be  more  beautiful than just blank console apps. So, I grabbed
/// SFML,  an  easy-to-use API (Application Programming Interface).
/// Now,  I  could  add visual delight like defining a button class
/// and  using it to play/pause/stop/resume. But I was still greedy
/// and wanted  more features. Hence, I used TGUI, a widget library
/// based on SFML  that  has  button,  checkbox, listbox, label and
/// many more classes defined in it. I  used  its  rich features to
/// customise my Mp3 player even more. And after systematic development
/// , lots  of testing, debugging and getting my code reviewed
/// by other programmers, I've completed this successfully.
///
/// Though this Mp3 player isn't written in the most efficient way
/// to utilize CPU and resources, it plays quite satisfactorily.
///
/// CREDITS for helping me whenever I was stuck goes to :
///
/// 1. Ms. Kavita Hazra, PGT (Comp. Sc.), K.V. No.1, BBSR
///    [ for ushering me into the wonderful world of programming
///      and clearing my doubts ]
///
/// 2. Bruno Van de Valen, Student, University of Untwerp, Belgium
///    (and the creator of TGUI)
///    [ for helping me test my code and for helping me with
///      using TGUI ]
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////
//    HEADER FILES    //
////////////////////////

#include <iostream>             // for using various C++ Standard Library objects
#include <fstream>              // for using C++'s data file handling capability
#include <sstream>              // for displaying the time as a std::sstream object
#include <SFML/Graphics.hpp>    // for using SFML's graphics classes and their methods
#include <TGUI/TGUI.hpp>        // for using TGUI's widget classes and their methods
#include "AudioPlayer.hpp"      // a custom audio class (defined by me)
#include "Constants.hpp"        // a custom class containg program constants (defined by me)


//////////////////////////////     main() method     ///////////////////////////////

int main()
{
    /* Declaring a fstream object and calling its ctor for opening the file (myPlaylist.bsm) containing file names of the mp3 tracks */
    std::fstream m_playList(PLAYLIST, std::ios::in | std::ios::out);
    if (!m_playList)    /* Checking if the file opened correctly or not. If value return is false, then the program returns 1 and exits */
    {
        std::cout << "\nERROR : Unable to open \"myPlaylist.txt\"!" << std::endl;
        return EXIT_FAILURE;
    }

    /* Declaring a fstream object and calling its ctor for opening the file (playlistInfo.bsm) containing the number of mp3 tracks in m_playlist*/
    std::fstream m_playListInfo(PLAY_INFO, std::ios::in | std::ios::out);
    if (!m_playListInfo)    /* Checking if the file opened correctly or not. If value return is false, then the program returns 1 and exits */
    {
        std::cout << "\nERROR : Unable to open \"PlaylistInfo.txt\"!" << std::endl;
        return EXIT_FAILURE;
    }

    /* Declaring a variable of type integer for storing the value (the number of mp3 tracks) obtained from playlistInfo.bsm */
    int m_trackCount = 0;

    /* Inputting the value from playlistInfo.bsm to m_trackCount */
    m_playListInfo >> m_trackCount;

    /* Declaring a 2D character array of dimensions m_trackCount x 500 to store the song names */
    char m_tracks[m_trackCount][MAX_NAME_LENGTH];    // each track name can be upto 500 characters long

    /* Looping to store all the song names one by one int the array just declared above */
    for (int I = 0; I < m_trackCount; I++)
    {
        m_playList.getline(m_tracks[I], MAX_NAME_LENGTH);
    }

    /* Declaring an object of class RenderWindow which is defined in the 'sf' namespace (scope).
       A RenderWindow object creates a window on which 2D graphic elements (like lines, polygons,
       etc) could be drawn. For more details, check out the SFML documentation.
    */
    sf::RenderWindow m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP),
                              WINDOW_TITLE, sf::Style::Close);

    /* Declaring an object of class Event which is defined in the 'sf' namespace (scope).
       A Event object holds the info about a system event (like a keypress, mouse movement, etc.)
       that just happened. For more details, check out the SFML documentation.
    */
    sf::Event m_event;

    /* Declaring an object of class Texture which is defined in the 'sf' namespace (scope).
       A Texture object stores an image (png/jpg/bmp/tga/gif/psd/hdr/pic) in the grahics card.
       For more details, check out the SFML documentation.

       Here, two objects of the sf::Texture class are declared - the first one stores the
       background image and the second one the image of the name of application - both in png format.
    */
    sf::Texture m_backgroundTexture, m_nameTexture, m_aboutTexture;
    /* Declaring an object of class Sprite which is defined in the 'sf' namespace (scope).
       A Sprite object is an instance of the drawable representation of that image.
       For more details, check out the SFML documentation.

       Here. two objects of sf::Sprite class are declared - so that the textures can be drawn to the
       sf::RenderWindow object.
    */
    sf::Sprite m_backgroundSprite, m_nameSprite, m_aboutSprite;;

    /* Loading the image from the computer's hardrive to the sf::Texture objects */
    if (!m_backgroundTexture.loadFromFile(BG_TEXTURE))      /* If failed to open image, display error msg and return 1 */
    {
        std::cout << "\nERROR : Unable to open \"background_texture.png\"!" << std::endl;
        return EXIT_FAILURE;
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);     /* The background texture is assigned to the background sprite */
    m_backgroundSprite.setScale(0.7f, 0.7f);                /* The scale of the texture is set to ratio of 0.7 to the original length
                                                               and breadth of the texture.
                                                            */

    if (!m_nameTexture.loadFromFile(NAME_TEXTURE))          /* If  */
    {
        std::cout << "\nERROR : Unable to open \"name.png\"!" << std::endl;
        return EXIT_FAILURE;
    }
    m_nameSprite.setTexture(m_nameTexture);
    m_nameSprite.setScale(0.8f, 0.8f);
    m_nameSprite.setRotation(90.f);
    m_nameSprite.setPosition(WINDOW_WIDTH - 20.f, 55.f);

    if (!m_aboutTexture.loadFromFile(ABT_TEXTURE))
    {
        std::cout << "\nERROR : Unable to open \"about.png\"!" << std::endl;
        return EXIT_FAILURE;
    }
    /* Declaring an object of class Font which is defined in the 'sf' namespace (scope).
       A Font object can be used for loading and manipulating the characters of a font
       (supported types - TrueType, Type 1, CFF, OpenType, SFNT, X11 PCF, Windows FNT,
       BDF, PFR and Type 42). I'm using TrueType(.ttf) fonts. For more details, check
       out the SFML documentation.
    */
    sf::Font m_defaultFont;
    if (!m_defaultFont.loadFromFile(GLOBAL_FONT))   /* If failed to open font file, display error msg and return 1 */
    {
        std::cout << "\nERROR : Unable to open \"sansation.ttf\"!" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Font customFont1;
    if (!customFont1.loadFromFile(CUSTOM_FONT_1))
    {
        std::cout << "\nERROR : Unable to open \"ARLRDBD.ttf\"!" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Font customFont2;
    if (!customFont2.loadFromFile(CUSTOM_FONT_2))
    {
        std::cout << "\nERROR : Unable to open \"BankGothic.ttf\"!" << std::endl;
        return EXIT_FAILURE;
    }

    /* Declaring an object of class Gui defined under the 'tgui' namespace (scope) and
       calling its ctor to initialise the GUI (Graphical User Interface) in the RenderWindow.
       A Gui object is the main entity which contains all other GUI widgets (like buttons,
       checkboxes, labels, etc). For more info, check out the TGUI documentation.
    */
    tgui::Gui m_gui(m_window);

    if (!m_gui.setGlobalFont(GLOBAL_FONT)) /* If failed to assign font, display error msg and return 1 */
    {
        std::cout << "\nERROR : Unable to open \"sansation.ttf\"!" << std::endl;
        return EXIT_FAILURE;
    }

    /* Declaring an object of class Menu which is defined in the 'tgui' namespace (scope).
       A Menu object which serves the functionality of a menu bar.The appropriate member
       functions have been called to initialize required class members. For more info,
       check out the TGUI documentation.
    */

    tgui::MenuBar::Ptr m_menu(m_gui);
    m_menu->load(WHITE_THEME);
    m_menu->setSize(m_window.getSize().x, 30.f);
    m_menu->addMenu("File");
    m_menu->addMenuItem("File", "Add a New Song...");
    m_menu->addMenuItem("File", "Exit");
    m_menu->addMenu("Help");
    m_menu->addMenuItem("Help", "How to Add Songs...");
    m_menu->addMenuItem("Help", "About");
    m_menu->setCallbackId(WidgetCallbacks::MENU_CALLBACK_ID);
    m_menu->bindCallback(tgui::MenuBar::MenuBarCallbacks::MenuItemClicked);

    /* Declaring an object of class ListBox which is defined in the 'tgui' namespace (scope).
       The listbox stores the name of tracks as a list. The appropriate member functions have
       been called to initialize required class members. For more info, check out the TGUI
       documentation.
    */
    tgui::ListBox::Ptr m_trackList(m_gui);
    m_trackList->load(WHITE_THEME);
    m_trackList->setSize(300, 250);
    m_trackList->setItemHeight(25);
    m_trackList->setPosition(580, 160);

    for (int I = 0; I < m_trackCount; I++)
    {
        m_trackList->addItem(m_tracks[I]);
    }

    m_trackList->setCallbackId(WidgetCallbacks::LISTBOX_CALLBACK_ID);
    m_trackList->bindCallback(tgui::ListBox::ListBoxCallbacks::ItemSelected);

    /* Declaring an object of class Text which is defined in the 'sf' namespace (scope).
       A Text object can be used for drawing a graphical text to a RenderWindow object.
       For more details, check out the SFML documentation.

       The appropriate functions to initialize required class members have been called.
    */
    sf::Text m_nameOfTracks("Tracks on Playlist:", m_defaultFont, 30);
    m_nameOfTracks.setPosition(580, 100);
    m_nameOfTracks.setRotation(-10);
    m_nameOfTracks.setColor(sf::Color(44, 127, 255));

    /* Declaring an object of class ChildWindow which is defined in the 'tgui' namespace (scope).
       This window pops up to display info about the application. The appropriate member functions
       have been called to initialize required class members. For more info, check out the TGUI
       documentation.
    */
    tgui::ChildWindow::Ptr m_aboutWindow(m_gui);
    m_aboutWindow->load(BLACK_THEME);
    m_aboutWindow->hide();
    m_aboutWindow->setSize(500, 300);
    m_aboutWindow->setBackgroundColor(sf::Color(79, 0, 79));
    m_aboutWindow->setBackgroundTexture(&m_aboutTexture);
    m_aboutWindow->setPosition(280, 100);
    m_aboutWindow->setTitle("About");
    m_aboutWindow->setCallbackId(WidgetCallbacks::CHILDWINDOW_CALLBACK_ID);
    m_aboutWindow->bindCallback(tgui::ChildWindow::ChildWindowCallbacks::Closed);

    /* Declaring an object of class Label which is defined in the 'tgui' namespace (scope).
       The Label class enables to display text in the tgui::Gui object. The appropriate
       member functions have been called to initiailze required class members. For more
       info, check out the TGUI documentation.
    */
    tgui::Label::Ptr m_aboutInfo(*m_aboutWindow);
    m_aboutInfo->load(BLACK_THEME);
    m_aboutInfo->setSize(330.f, 20.f);
    m_aboutInfo->setTextFont(customFont1);
    m_aboutInfo->setTextColor(sf::Color(44, 127, 255));
    m_aboutInfo->setText("BEAT$ATION-MU$IX MP3 PLAYER");
    m_aboutInfo->setTextSize(20.f);
    m_aboutInfo->setPosition(85.f, 20.f);

    tgui::Label::Ptr m_info1(*m_aboutWindow);
    m_info1->load(BLACK_THEME);
    m_info1->setSize(255.f, 20.f);
    m_info1->setTextFont(customFont2);
    m_info1->setTextColor(sf::Color(44, 127, 255));
    m_info1->setText("(C) Koushtav Chakrabarty");
    m_info1->setTextSize(18.f);
    m_info1->setPosition(120.f, 50.f);

    tgui::Label::Ptr m_info2(*m_aboutWindow);
    m_info2->load(BLACK_THEME);
    m_info2->setSize(315.f, 20.f);
    m_info2->setTextFont(m_defaultFont);
    m_info2->setTextColor(sf::Color(44, 127, 255));
    m_info2->setText("E-mail : lostsoulofthegeek@gmail.com");
    m_info2->setTextSize(16.f);
    m_info2->setPosition(105.f, 80.f);

    tgui::Label::Ptr m_info3(*m_aboutWindow);
    m_info3->load(BLACK_THEME);
    m_info3->setSize(400.f, 100.f);
    m_info3->setTextFont(customFont1);
    m_info3->setTextColor(sf::Color::Black);
    m_info3->setText(MSG_1);
    m_info3->setTextSize(17.f);
    m_info3->setPosition(60.f, 120.f);

    tgui::Label::Ptr m_website(*m_aboutWindow);
    m_website->load(BLACK_THEME);
    m_website->setSize(500.f, 20.f);
    m_website->setTextFont(m_defaultFont);
    m_website->setTextColor(sf::Color::Red);
    m_website->setText(MSG_3);
    m_website->setTextSize(17.f);
    m_website->setPosition(45.f, 254.f);

    tgui::ChildWindow::Ptr m_helpWindow(m_gui);
    m_helpWindow->load(BLACK_THEME);
    m_helpWindow->hide();
    m_helpWindow->setSize(465, 462);
    m_helpWindow->setPosition(290, 100);
    m_helpWindow->setTitle("How to Add Songs...");
    m_helpWindow->setCallbackId(WidgetCallbacks::CHILDWINDOW_CALLBACK_ID);
    m_helpWindow->bindCallback(tgui::ChildWindow::ChildWindowCallbacks::Closed);

    tgui::Label::Ptr m_helpInfo(*m_helpWindow);
    m_helpInfo->load(BLACK_THEME);
    m_helpInfo->setSize(465, 462);
    m_helpInfo->setTextColor(sf::Color::White);
    m_helpInfo->setText(MSG_2);
    m_helpInfo->setTextSize(20.f);
    m_helpInfo->setPosition(20.f, 20.f);

    tgui::ChildWindow::Ptr m_addWindow(m_gui);
    m_addWindow->load(BLACK_THEME);
    m_addWindow->hide();
    m_addWindow->setSize(570, 200);
    m_addWindow->setPosition(260, 140);
    m_addWindow->setTitle("Add new song...");
    m_addWindow->setBackgroundColor(sf::Color(200, 200, 200));
    m_addWindow->setCallbackId(WidgetCallbacks::CHILDWINDOW_CALLBACK_ID);
    m_addWindow->bindCallback(tgui::ChildWindow::ChildWindowCallbacks::Closed);

    tgui::Label::Ptr m_addBoxInfo(*m_addWindow);
    m_addBoxInfo->load(BLACK_THEME);
    m_addBoxInfo->setTextSize(25);
    m_addBoxInfo->setSize(200, 25);
    m_addBoxInfo->setPosition(20, 10);
    m_addBoxInfo->setTextColor(sf::Color::Black);
    m_addBoxInfo->setText("Enter song name:");

    /* Declaring an object of class Textbox which is defined in the 'tgui' namespace (scope).
       The TextBox object proides a text field on which text can written/edited/deleted. The
       appropriate member functions have been called to initialize required class members.
       For more info, check out the TGUI documentation.
    */
    tgui::TextBox::Ptr m_songNameField(*m_addWindow);
    m_songNameField->load(BLACK_THEME);
    m_songNameField->setSize(530, 19);
    m_songNameField->setTextSize(20);
    m_songNameField->setPosition(20, 40);
    m_songNameField->setTextColor(sf::Color(200, 250, 250));

    tgui::Label::Ptr m_fileInfo(*m_addWindow);
    m_fileInfo->load(BLACK_THEME);
    m_fileInfo->setTextSize(20);
    m_fileInfo->setSize(530, 50);
    m_fileInfo->setPosition(30, 90);
    m_fileInfo->setTextColor(sf::Color::Red);
    m_fileInfo->setText("[  If song is not in project directory, include the path as\nwell or see Help -> How to Add Songs  ]");

    /* Declaring an object of class Button which is defined in the 'tgui' namespace (scope).
       The Button object provides the funcationality of a clickable button. Pressing a button
       can be used to trigger a command (like playing or pausing music). The appropriate
       member functions have been called to initialize required class members. For more info,
       check out the TGUI documentation.
    */
    tgui::Button::Ptr m_addButton(*m_addWindow);
    m_addButton->load(BABY_BLUE_THEME);
    m_addButton->setSize(100, 30);
    m_addButton->setPosition(450, 150);
    m_addButton->setText("Add");
    m_addButton->setCallbackId(WidgetCallbacks::BUTTON_CALLBACK_ID);
    m_addButton->bindCallback(tgui::Button::ClickableWidgetCallbacks::LeftMouseClicked);

    tgui::Button::Ptr m_cancelButton(*m_addWindow);
    m_cancelButton->load(BABY_BLUE_THEME);
    m_cancelButton->setSize(100, 30);
    m_cancelButton->setPosition(330, 150);
    m_cancelButton->setText("Cancel");
    m_cancelButton->setCallbackId(WidgetCallbacks::BUTTON_CALLBACK_ID);
    m_cancelButton->bindCallback(tgui::Button::ClickableWidgetCallbacks::LeftMouseClicked);

    tgui::ChildWindow::Ptr m_errorWindow(m_gui);
    m_errorWindow->load(BLACK_THEME);
    m_errorWindow->hide();
    m_errorWindow->setSize(620, 200);
    m_errorWindow->setPosition(230, 200);
    m_errorWindow->setTitle("Error in adding file!");
    m_errorWindow->setBackgroundColor(sf::Color(200, 200, 200));
    m_errorWindow->setCallbackId(WidgetCallbacks::CHILDWINDOW_CALLBACK_ID);
    m_errorWindow->bindCallback(tgui::ChildWindow::ChildWindowCallbacks::Closed);

    tgui::Label::Ptr errInfo1(*m_errorWindow);
    errInfo1->load(BLACK_THEME);
    errInfo1->setTextSize(17);
    errInfo1->setSize(570, 50);
    errInfo1->setPosition(30, 20);
    errInfo1->setText("Couldn't find the file (make sure that you entered the file name correctly) : ");
    errInfo1->setTextColor(sf::Color::Red);

    tgui::ChatBox::Ptr errInfo2(*m_errorWindow);
    errInfo2->load(BLACK_THEME);
    errInfo2->setTextSize(20);
    errInfo2->setSize(550, 150);
    errInfo2->setPosition(30, 40);

    tgui::Button::Ptr m_playButton(m_gui);
    m_playButton->load(BABY_BLUE_THEME);
    m_playButton->setSize(250, 40);
    m_playButton->setPosition(50, 100);
    m_playButton->setText("Play");
    m_playButton->setTextColor(sf::Color(44, 127, 255));
    m_playButton->setCallbackId(WidgetCallbacks::BUTTON_CALLBACK_ID);
    m_playButton->bindCallback(tgui::Button::ClickableWidgetCallbacks::LeftMouseClicked);

    tgui::Button::Ptr m_pauseButton(m_gui);
    m_pauseButton->load(BABY_BLUE_THEME);
    m_pauseButton->setSize(250, 40);
    m_pauseButton->setPosition(50, 155);
    m_pauseButton->setText("Pause");
    m_pauseButton->setTextColor(sf::Color(44, 127, 255));
    m_pauseButton->setCallbackId(WidgetCallbacks::BUTTON_CALLBACK_ID);
    m_pauseButton->bindCallback(tgui::Button::ClickableWidgetCallbacks::LeftMouseClicked);

    tgui::Button::Ptr m_stopButton(m_gui);
    m_stopButton->load(BABY_BLUE_THEME);
    m_stopButton->setSize(250, 40);
    m_stopButton->setPosition(50, 210);
    m_stopButton->setText("Stop");
    m_stopButton->setTextColor(sf::Color(44, 127, 255));
    m_stopButton->setCallbackId(WidgetCallbacks::BUTTON_CALLBACK_ID);
    m_stopButton->bindCallback(tgui::Button::ClickableWidgetCallbacks::LeftMouseClicked);

    /* Declaring an object of class AudioPlayer defined in the 'audioplayer' namespace.
       The AudioPlayer object provides all necessary methods and members that can be
       used to playback Mp3 files.
    */
    audioplayer::AudioPlayer m_Mp3Player;

    int n = 0;

    /* The following do-while loop iterates until it encounters a legal filename that can be streamed.
    */
    do      /* do - initialization of the object... */
    {
        if (!m_Mp3Player.Init(m_tracks[n], audioplayer::INIT_VOLUME))
        {
            std::cout << "\nERROR : Couldn't initialize AudioPlayer object" << std::endl;
        }
        ++n;
    } while (!m_Mp3Player.IsLoadable());    /* ... until a streamable filepath is encountered. */

    std::cout << "\n" << m_Mp3Player.GetFileName() << std::endl;

    m_Mp3Player.Play();     /* Play the sound. */
    m_Mp3Player.Stop();     /* Stop the sound. */

    /* Declaration & initialization of a Slider object defined in the 'tgui' namespace.
       The slider can be used to scroll the position of the sound being played.
    */
    tgui::Slider::Ptr m_seekBar(m_gui);
    m_seekBar->load(BABY_BLUE_THEME);
    m_seekBar->setVerticalScroll(false);
    m_seekBar->setSize(600, 10);
    m_seekBar->setPosition(50, 470);
    m_seekBar->setCallbackId(WidgetCallbacks::SLIDER_CALLBACK_ID);
    m_seekBar->bindCallback(tgui::Slider::SliderCallbacks::ValueChanged);
    m_seekBar->setValue(m_Mp3Player.GetCurrentPosition());

    /* Declaration & initialization of a Slider object defined in the 'tgui' namespace.
       The slider can be used to scroll the volume of the sound being played.
    */
    tgui::Slider::Ptr m_volumeBar(m_gui);
    m_volumeBar->load(BABY_BLUE_THEME);
    m_volumeBar->setVerticalScroll(false);
    m_volumeBar->setSize(100, 10);
    m_volumeBar->setPosition(50, 610);
    m_volumeBar->setCallbackId(WidgetCallbacks::SLIDER_CALLBACK_ID);
    m_volumeBar->bindCallback(tgui::Slider::SliderCallbacks::ValueChanged);
    m_volumeBar->setMaximum(100);
    m_volumeBar->setValue(m_Mp3Player.GetCurrentVolume() * 100);

    /* Declaration & initialization of a Checkbox object defined in the 'tgui' namespace.
       The checkbox can be used to mute/unmute the sound being played.
    */
    tgui::Checkbox::Ptr m_muteCheckbox(m_gui);
    m_muteCheckbox->load(BABY_BLUE_THEME);
    m_muteCheckbox->setPosition(50, 640);
    m_muteCheckbox->setText("Mute");
    m_muteCheckbox->setTextColor(sf::Color(44, 127, 255));
    m_muteCheckbox->setSize(20, 20);
    m_muteCheckbox->setCallbackId(WidgetCallbacks::CHECKBOX_CALLBACK_ID);
    m_muteCheckbox->bindCallback(tgui::Checkbox::CheckboxCallbacks::Unchecked);

    /* A Text object to store the current volume of the sound as a printable string.
    */
    sf::Text m_volume("50", m_defaultFont, 20);
    m_volume.setColor(sf::Color(44, 127, 255));
    m_volume.setPosition(157, 602);

    sf::Text m_nowPlaying("Now playing : ", m_defaultFont, 20);
    m_nowPlaying.setColor(sf::Color(44, 127, 255));
    m_nowPlaying.setPosition(50, 410);

    /* A Text object to store the current sound name as a printable string.
    */
    sf::Text m_musicName(m_tracks[0], m_defaultFont, 20);
    m_musicName.setColor(sf::Color::White);
    m_musicName.setPosition(50, 435);

    /* A Text object to store the elapsed time of the sound as a printable string.
    */
    sf::Text m_timeElapsed("0.0", m_defaultFont, 15);
    m_timeElapsed.setColor(sf::Color(44, 127, 255));
    m_timeElapsed.setPosition(50, 490);

    ///////////////////////////////////////////////
    //   The main controal loop of the program   //
    ///////////////////////////////////////////////
    while (m_window.isOpen())
    {
        //////////////////////////////////////////////////////////////////////////////////////////
        //   While the sf::RenderWindow object is open, the following statements get executed   //
        //////////////////////////////////////////////////////////////////////////////////////////
        while(m_window.pollEvent(m_event))
        {
            /* The sf::Event object 'polls' all events occuring in the sf::RenderWindow one by one in
               the order they occur. Here, only the event of closing a sf::RenderWindow is being polled.
               If the close button (X button) on the window is pressed, the sf::RenderWindow object
               ceases to exist.
            */
            if ((m_event.type == sf::Event::EventType::Closed))
                m_window.close();

            /* The events occuring in the tgui objects are handled by the function handleEvent(sf::Event),
               which is a member function of a tgui::Gui object.
            */
            m_gui.handleEvent(m_event);
        }

        /* A tgui::Callback object 'polls' the events relevant to the tgui objects in a similar way to that
           pollEvent() does for sfml objects. It stores and executes the tgui object behaviour correspnding
           to a particular event. E.g. : a left mouse click on a button is polled by pollCallBack() and a
           piece of code to react to that pressing of byutton is executed.
        */
        tgui::Callback m_callback;
        while (m_gui.pollCallback(m_callback))
        {
            /* A switch case to execute a certain code for a certain event.
            */
            switch (m_callback.id)
            {
                /* When a button is pressed, this case checks the text of the button and executes the
                   corresponding code. E.g. : If the user presses a play button, the switch case
                   firstly checks what tgui event occured. If it was a button press, what was the text
                   of the button. If it was 'Play' then start playing the audio.
                */
                case WidgetCallbacks::BUTTON_CALLBACK_ID:
                    {
                        if (m_callback.text == "Cancel")
                            m_addWindow->hide();
                        else if (m_callback.text == "Play")
                        {
                            if (!m_Mp3Player.isAudioPlaying()
                                && m_Mp3Player.GetAudioState() == audioplayer::AudioState::STOPPED)
                            m_Mp3Player.Play();
                        }
                        else if (m_callback.text == "Pause")
                        {
                            m_Mp3Player.Pause();
                        }
                        else if (m_callback.text == "Resume")
                        {
                            m_Mp3Player.Resume();
                        }
                        else if (m_callback.text == "Stop")
                        {
                            m_Mp3Player.Stop();
                        }
                        /* If the add button was pressed, the program first gets whatever filename is on the
                           texfield and then checks if the filename is a legal sound source. If it is, the
                           filename is written to 'MyPlaylist.bsm'. If not, then an appropriate error message
                           is displayed.
                        */
                        else if (m_callback.text == "Add")
                        {
                            std::string newTrackName = m_songNameField->getText();

                            char *tempFilename = m_Mp3Player.GetFileName();
                            float tempPosition = m_Mp3Player.GetCurrentPosition();

                            m_Mp3Player.Stop();

                            if (m_Mp3Player.Init((char *)newTrackName.c_str(), m_Mp3Player.GetCurrentVolume()))
                            {
                                if (!m_Mp3Player.IsLoadable())
                                {
                                    system("cls");
                                    std::cout << "Unloadable!\n";

                                    m_addWindow->hide();

                                    errInfo2->removeAllLines();
                                    errInfo2->addLine((char *)newTrackName.c_str(), sf::Color(44, 127, 255));
                                    m_errorWindow->show();
                                    m_errorWindow->moveToFront();


                                    m_Mp3Player.Init(tempFilename, m_Mp3Player.GetCurrentVolume());
                                    m_Mp3Player.Play();
                                    m_Mp3Player.SetCurrentPosition(tempPosition);
                                    m_Mp3Player.SetCurrentVolume(m_Mp3Player.GetCurrentVolume());
                                }
                                else
                                {
                                    system("cls");
                                    std::cout << "Loaded!\n";

                                    m_playList << newTrackName.c_str() << "\n";

                                    m_trackCount++;

                                    m_playListInfo.seekg(0);
                                    m_playListInfo << m_trackCount;

                                    m_addWindow->hide();

                                    m_Mp3Player.Init(tempFilename, m_Mp3Player.GetCurrentVolume());
                                    m_Mp3Player.Play();
                                    m_Mp3Player.SetCurrentPosition(tempPosition);
                                    m_Mp3Player.SetCurrentVolume(m_Mp3Player.GetCurrentVolume());
                                }
                            }
                        }

                    } break;

                case WidgetCallbacks::MENU_CALLBACK_ID:
                    {
                        if (m_callback.text == "Add a New Song...")
                        {
                            m_songNameField->setText("");
                            if (!m_addWindow->isVisible())
                                m_addWindow->setPosition(260, 140);
                            m_addWindow->show();
                            m_addWindow->moveToFront();
                        }
                        else if (m_callback.text == "Exit")
                        {
                            m_window.close();
                        }
                        else if (m_callback.text == "How to Add Songs...")
                        {
                            if (!m_helpWindow->isVisible())
                                m_helpWindow->setPosition(290, 100);
                            m_helpWindow->show();
                            m_helpWindow->moveToFront();
                        }
                        else if (m_callback.text == "About")
                        {
                            if (!m_aboutWindow->isVisible())
                                m_aboutWindow->setPosition(280, 100);
                            m_aboutWindow->show();
                            m_aboutWindow->moveToFront();
                        }
                    } break;

                /* When a list item (i.e., a song name) on the listbox is selected, the
                   corresponding sound file gets played.
                */
                case WidgetCallbacks::LISTBOX_CALLBACK_ID:
                    {
                        for (int I = 0; I < m_trackCount; I++)
                        {
                            if (m_callback.text == m_tracks[I])
                            {
                                m_Mp3Player.Stop();
                                m_Mp3Player.Reset();

                                int num = I;

                                system("cls");

                                m_Mp3Player.Init(m_tracks[num], m_Mp3Player.GetCurrentVolume());

                                std::cout << "\nAudio file : " << m_tracks[num] << std::endl;

                                /* This while loop iterates until a legal sound file is encountered in 'MyPlaylist.bsm'.
                                   In this way no illegal/incorrect file gets played/loaded even if someone edits
                                   MyPlaylist.bsm manually.
                                */
                                while (!m_Mp3Player.IsLoadable())
                                {
                                    m_Mp3Player.Init(m_tracks[num], m_Mp3Player.GetCurrentVolume());
                                    ++num;
                                }

                                m_musicName.setString(m_Mp3Player.GetFileName());
                                m_Mp3Player.Play();
                            }
                        }
                    } break;

                case WidgetCallbacks::CHILDWINDOW_CALLBACK_ID:
                    {
                        m_aboutWindow->hide();
                        m_helpWindow->hide();
                        m_addWindow->hide();
                        m_errorWindow->hide();
                    } break;

                case WidgetCallbacks::CHECKBOX_CALLBACK_ID:
                    {
                        m_Mp3Player.SetVolume(m_Mp3Player.GetMuteVolume());
                    } break;
            }
        }

        m_trackList->setSelectedItem(m_Mp3Player.GetFileName());    /* Highlight the currently playing sound. */
        m_seekBar->setMaximum(m_Mp3Player.GetAudioLength());        /* Update the position of the seek bar according to the sound's current position. */

        /* Update the volume of the sound. */
        std::stringstream CurrentVolume;
        CurrentVolume << m_volumeBar->getValue();
        m_volume.setString(CurrentVolume.str());

        /* Calculate/Display/Update the time elapsed. */
        std::stringstream time;
        int m_totalTime = m_Mp3Player.GetCurrentPosition() / 1000;
        int m_seconds = 0, m_minutes = 0;
        m_seconds = m_totalTime % 60;
        m_minutes += m_totalTime / 60;
        time << m_minutes / 10 << m_minutes % 10 << " : " << m_seconds / 10 << m_seconds % 10;
        m_timeElapsed.setString(time.str());

        /* Set the default audio state when no sound is playing. */
        if (!m_Mp3Player.isAudioPlaying() && m_Mp3Player.GetAudioState() == audioplayer::AudioState::PLAYING)
        {
            m_Mp3Player.SetAudioState(audioplayer::AudioState::STOPPED);
        }

        /* Update the text/status of the play/pause/stop buttons depending upon the audio state. */
        switch (m_Mp3Player.GetAudioState())
        {
            case audioplayer::AudioState::PLAYING:
                {
                    m_playButton->setText("Playing...");
                    m_playButton->setTextColor(sf::Color::Red);
                    m_pauseButton->setText("Pause");
                    m_pauseButton->setTextColor(sf::Color(44, 127, 255));
                    m_stopButton->setText("Stop");
                    m_stopButton->setTextColor(sf::Color(44, 127, 255));
                } break;
            case audioplayer::AudioState::PAUSED:
                {
                    m_pauseButton->setText("Paused");
                    m_pauseButton->setTextColor(sf::Color::Red);
                    m_playButton->setText("Resume");
                    m_playButton->setTextColor(sf::Color(44, 127, 255));
                    m_stopButton->setText("Stop");
                    m_stopButton->setTextColor(sf::Color(44, 127, 255));
                } break;
            case audioplayer::AudioState::STOPPED:
                {
                    m_stopButton->setText("Stopped");
                    m_stopButton->setTextColor(sf::Color::Red);
                    m_playButton->setText("Play");
                    m_playButton->setTextColor(sf::Color(44, 127, 255));
                    m_pauseButton->setText("Pause");
                    m_pauseButton->setTextColor(sf::Color(44, 127, 255));
                } break;
        }

        /* Increase volume if the add key (+) is pressed. */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        {
            m_Mp3Player.VolumeUp(VOL_STEP * 1);
        }

        /* Decrease volume if the subtract key (-) is pressed. */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
            m_Mp3Player.VolumeDown(VOL_STEP * 1);
        }

        /* Update the values of the seek bar and the volume bar. */
        m_volumeBar->setValue(m_Mp3Player.GetCurrentVolume() * 100);
        m_seekBar->setValue(m_Mp3Player.GetCurrentPosition());

        /* If the mutebox is checked, set the audio sound to zero. */
        if(m_muteCheckbox->isChecked())
            m_Mp3Player.SetVolume(0.f);

        /* Change the sound position and the volume if the user uses a mouse and changes
           the value of the seek bar and the volume bar.
        */
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(m_window);

            if (mousePos.x >= 50 && mousePos.x <= 651
                && mousePos.y >= 464 && mousePos.y <= 464 + 20)
            {
                // bar length is the number of pixels spanning horizontally accross the seek bar //
                float barLength = 600;
                float offset = m_Mp3Player.GetAudioLength() / barLength;
                m_Mp3Player.SetCurrentPosition(mousePos.x * offset - 15000.f);
                /* 15000.f is a random value chosen by trial and error method to give near perfect results.
                   The seek bar is yet to give precise results.
                */
            }

            else if (mousePos.x >= 50 && mousePos.x <= 150
                && mousePos.y >= 603 && mousePos.y <= 623)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    float barLength = 100.f;
                    float offset = 100.f / barLength;
                    float tempVolume = mousePos.x * offset - 50.f;
                    m_Mp3Player.SetVolume(tempVolume / 100.f);
                    m_Mp3Player.SetMuteVolume(tempVolume / 100.f);
                }
            }
        }

        m_window.clear(sf::Color::Black);       /* Clear the sf::RenderWindow with black colour (RGB values of black are (0, 0, 0)). */

        m_window.draw(m_backgroundSprite);      /* draw the background sprite. */
        m_window.draw(m_nameSprite);            /* draw the logo sprite. */
        m_window.draw(m_nameOfTracks);
        m_window.draw(m_volume);                /* draw the current volume text. */
        m_window.draw(m_timeElapsed);           /* draw the elapsed time text. */
        m_window.draw(m_nowPlaying);
        m_window.draw(m_musicName);             /* draw the current sound name text. */

        m_gui.draw();                           /* draw all the tgui objects. */

        ////////////////////////////////////////////////////////////////////////////////
        //   This is a major difference in cide implementation in SFML & TGUI. SFML   //
        //   requires  to  individually draw all its objects but TGUI does the same   //
        //   with its objects only with one single call to draw() function which is   //
        //   a member of tgui::Gui class.                                             //
        ////////////////////////////////////////////////////////////////////////////////

        m_window.display();                     /* Update everything drawn on the sf::RenderWindow object. */
        sf::sleep(sf::milliseconds(1));         /* Give the CPU a break of 1 millisecond. */
    }

    m_playList.close();                         /* Close the data files containg the music library info. */
    m_playListInfo.close();

    return EXIT_SUCCESS;                        /* Return 0 to the OS. */
}


/************************************************************************************/
//////////////////////////////     end of main.cpp     ///////////////////////////////
/************************************************************************************/
