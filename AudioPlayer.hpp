////////////////////////////////////////////////////////////////////////////
//                            AudioPlayer.hpp                             //
////////////////////////////////////////////////////////////////////////////


#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP

#include <iostream>
#include <irrKlang.h>


////////////////////////////////////////////////////////////////////////////
//                         audioplayer NAMESPACE                          //
////////////////////////////////////////////////////////////////////////////

namespace audioplayer
{

    ////////////////////////////////////////////////////////////////////////
    //                           INITIAL VOLUME                           //
    ////////////////////////////////////////////////////////////////////////
    const float INIT_VOLUME = 0.5f;

    ////////////////////////////////////////////////////////////////////////
    //                       AUDIO STATE ENUMERATION                      //
    ////////////////////////////////////////////////////////////////////////
    enum AudioState
    {
        STOPPED,
        PLAYING,
        PAUSED
    };

    ////////////////////////////////////////////////////////////////////////
    //                          CLASS AUDIOPLAYER                         //
    ////////////////////////////////////////////////////////////////////////
    class AudioPlayer
    {
        /////////////// PRIVATE MEMBERS ///////////////
        private:
            /* ISoundEngine object prvides an interface for loading & playing sounds. */
            irrklang::ISoundEngine *m_SoundEngine;

            /* ISound object is used to manipulate the mp3 files using the ISoundEngine object. */
            irrklang::ISound *m_Sound;

            /* String to store the file name of the current sound being played. */
            char *m_fileName;

            /* Current volume of the sound. */
            float m_currentVolume;

            /* Current position of the sound file during play. */
            float m_currentPosition;

            /* boolean variable to store if the sound is playig or not. */
            bool m_isSoundPlaying;

            /* Data member to store the audio state of the sound (Stopped/Playing/Paused) */
            AudioState  m_audioState;

            /* Data member to store the volume prior to muting the sound. */
            float m_muteVolume;

        //////////////// PUBLIC MEMBERS ////////////////
        public:

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Default constructor
            ///
            /// Initializes m_SoundEngine, m_Sound and m_fileName to nullptr. m_currentVolume & m_currentPosition are initialized to
            /// 0.f, m_isSoundPlaying to false m_muteVolume to m_currentVolume (i.e., 0.f). PLZ NOTE: AudioPlayer class uses no
            /// parameterized ctors since Init() and IsLoadable() are adequate to initialize data members to legal values.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            AudioPlayer();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to initialize the ISoundEngine object.
            ///
            /// Crates a new irrklang::ISoundEngine device and assigns it to m_SoundEngine. If it fails, then an error message is
            /// displayed and the function returns false. On the other hand, if the creation was successful, then m_currentPosition
            /// is assigned 0.f, m_currentVolume is assigned VOLUME, m_fileName is set to FILE_NAME, m_muteVolume is set to
            /// m_currentVolume. Also, the member function of m_SoundEngine, play2D() is also called and the m_SoundEngine's audio
            /// volume is set to VOLUME.
            ///
            /// \param
            /// FILE_NAME - The name of the mp3 file that is being tried to played.
            ///
            /// \param
            /// VOLUME - The initial volume of the m_Sound object at the time of initializing the m_Sound object.
            ///
            /// \return
            /// If everything is fine, then it returns true.
            ///
            /// \warning
            /// audioplayer::AudioPlayer::Init() only creates a new irrKlang sound device which can be manipulated to play/pause/stop
            /// mp3 files. It doesn't event bother if a legal or illegal file is being tried to be played. So, you must remember to
            /// call audioplayer::AudioPlayer::IsLoadable() in order to check if the file can be played or not.
            ///
            /// Usage example:
            /// \code
            /// char *file = "E:/MY MUSIC/Tum Hi Ho.mp3";
            /// float volume = 0.005f;
            /// audioplayer::AudioPlayer playerObject;
            /// if (playerObject.Init(file, volume))
            /// {
            ///     if (!playerObject.IsLoadable())
            ///     {
            ///         cout << "\nError in opening mp3 file " << file << " !" << endl;
            ///     }
            ///     else
            ///     {
            ///         playerObject.Play();
            ///     }
            /// }
            /// \endcode
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            bool Init(char *FILE_NAME, float VOLUME);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Accessor to check if the loaded file name can be streamed or not.
            ///
            /// This accessor checks if the loaded file is valid or not and whether it can be played or not. If the loaded file can't
            /// be played it sets m_isSoundPlaying to false and m_audioState to AudioState::STOPPED.
            ///
            /// \return
            /// Returns false if m_fileName points to an illegal file name. If m_fileName is a valid file name, it returns true.
            ///
            /// \warning
            /// This function must be called in order to check if m_fileName is a legal file path. If you fail to do so, then the
            /// behaviour is undefined and the program will simply crash (because m_SoundEngine will try to play a mp3 file that doesn't
            /// exist in the memory).
            /// (PLZ SEE THE USAGE EXAMPLES IN THE DOC FOR Init())
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            bool IsLoadable();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to play the sound using the ISound object.
            ///
            /// Plays the loaded mp3 file. Sets m_isSoundPlaying to true, m_audioState to AudioState::PLAYING, m_currentPosition to
            /// current position of m_Sound, m_currentVolume to current volume of m_Sound and m_muteVolume to m_currentVolume. Also,
            /// the member function play2D() of m_Sound is called to start playing the audio.
            ///
            /// \warning
            /// If you call play multiple times without checking if the sound is playing or not, then the same file will be played
            /// multiple times. You have to check if the sound is playing using isAudioPlaying() & GetAudioState() and then play the
            /// file accordingly.
            ///
            /// Usage example:
            /// \code
            /// if (!playerObject.isAudioPlaying() && playerObject.GetAudioState() == audioplayer::MusicState::STOPPED)
            /// {
            ///     playerObject.Play();
            /// }
            /// \endcode
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void Play();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to pause the sound using the ISound object.
            ///
            /// Pauses the audio (if it is already playing). Sets m_currentVolume to current volume of m_Sound, m_currentPosition to
            /// current position of m_Sound, m_audioState to AudioState::PAUSED and m_muteVolume to m_currentVolume.
            /// Also, the member function setIsPaused() of m_Sound is called to pause the audio.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void Pause();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to resume the sound using the ISound object.
            ///
            /// Resumes the audio (if it was paused). Sets m_audioState to AudioState::PLAYING, m_Sound to m_currentVolume,
            /// m_currentVolume to current volume of m_Sound, m_muteVolume to m_currentVolume. Also. if m_currentPosition is greater
            /// than 0, the member function of m_Sound, setPlayPosition() and sets its position to m_currentPosition.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void Resume();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to stop the sound using the ISound object.
            ///
            /// Sets m_currentVolume to current volume of m_Sound, m_audioState to AudioState::STOPPED and m_muteVolume to m_currentVolume.
            /// Also, the member funciton stop() of m_Sound is caled to stop playing the audio.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void Stop();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to increase volume by a certain factor.
            ///
            /// Increases the value of m_currentVolume by INCREMENT and assigns m_currentVolume to m_Sound->setVolume(float VOLUME).
            ///
            /// \param
            /// INCREMENT - The amount by which the volume is increased.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void VolumeUp(float INCREMENT);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to decrease volume by a certain factor.
            ///
            /// Decreases the value of m_currentVolume by DECREMENT and assigns m_currentVolume to m_Sound->setVolume(float VOLUME).
            ///
            /// \param
            /// DECREMENT - The amount by which the volume is decreased.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void VolumeDown(float DECREMENT);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to set the volume prior to muting.
            ///
            /// Assigns VOLUME to m_muteVolume.
            ///
            /// \param
            /// VOLUME - The volume amount to be stored before muting.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void SetMuteVolume(float VOLUME);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Accessor to return the volume prior to muting.
            ///
            /// \return
            /// Returns the value stored in m_muteVolume.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            float GetMuteVolume();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to set the current volume.
            ///
            /// Sets the value of m_currentVolume to VOLUME.
            ///
            /// \param
            /// VOLUME - The required volume to be set.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void  SetCurrentVolume(float VOLUME);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Accessor to return the current volume of the ISound object.
            ///
            /// \return
            /// Returns the value of m_currentVolume.
            ///
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            float GetCurrentVolume();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Accessor to return the current length of the audio file.
            ///
            /// \return
            /// Returns the value of m_Sound->getPlayLength();
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            float GetAudioLength();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to set the current volume of the ISound object.
            ///
            /// Sets the volume of m_Sound to VOLUME by calling its member function m_Sound->setVolume(float Volume).
            ///
            /// \param
            /// VOLUME - The volume to be set.
            ///
            /// \warning
            /// Setting the volume of an ISound object below 0 causes the volume to remain 0 and setting it beyond 1 causes the volume
            /// to remain full.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void SetVolume(float VOLUME);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to set the current audio state.
            ///
            /// Sets the value of m_audioState to STATE.
            ///
            /// \param
            /// STATE - The music state to be set.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void SetAudioState(AudioState STATE);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Accessor to return the current audio state.
            ///
            /// \return
            /// Returns the value stored in m_audioState.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            int GetAudioState();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to set the current file name.
            ///
            /// Sets m_fileName to FILE_NAME.
            ///
            /// \param
            /// FILE_NAME - The file name of the mp3 file.
            ///
            /// \warning
            /// The file name stored in m_fileName can be both legal and illegal. So, please check if it's legal using IsLoadable()
            /// funciton.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void SetFileName(char *FILE_NAME);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Accessor to return the current sound file name.
            ///
            /// \return
            /// Returns the string stored in m_fileName (i.e., the file name of the mp3 file).
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            char *GetFileName();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to set the current sound position.
            ///
            /// Sets m_currentPosition to POSITION.
            ///
            /// \param
            /// POSITION - the audio position to be set.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void SetCurrentPosition(float POSITION);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Accessor to get current position.
            ///
            /// \return
            /// Returns the value stored in m_currentPosition.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            float GetCurrentPosition();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Accessor to return a boolean value indicating whether a sound is playing or not.
            ///
            /// \return
            /// Returns true if the sound is playing or else returns false.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            bool isAudioPlaying();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Mutator to delete current sound stream and free memory so that a new one may be loaded.
            ///
            /// Resets m_Sound by calling its member function stop() and freeing the resources (memory) it occupies so that a new
            /// audio file can be loaded in its place.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            void Reset();

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Destructor
            ///
            /// If m_Sound and m_SoundEngine are pointing to a valid memory location, then it clears their memory plus it does the
            /// usual memory freeing task as a destructor.
            ///
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ~AudioPlayer();
    };
}

#endif // AUDIOPLAYER_HPP

/*******************************************************************************************/
//////////////////////////////     end of AudioPlayer.hpp     ///////////////////////////////
/*******************************************************************************************/
