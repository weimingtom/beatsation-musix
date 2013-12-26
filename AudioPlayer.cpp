////////////////////////////////////////////////////////////////////////////
//                            AudioPlayer.cpp                             //
////////////////////////////////////////////////////////////////////////////

#include "AudioPlayer.hpp"

////////////////////////////////////////////////////////////////////////////
//             MEMBER FUNCTION DEFINITION OF CLASS AUDIOPLAYER            //
////////////////////////////////////////////////////////////////////////////

audioplayer::AudioPlayer::AudioPlayer() : m_SoundEngine(nullptr), m_Sound(nullptr), m_fileName(nullptr)
{
    m_currentVolume = 0.f;
    m_currentPosition = 0.f;
    m_isSoundPlaying = false;
    m_muteVolume = m_currentVolume;
}

bool audioplayer::AudioPlayer::Init(char *FILE_NAME, float VOLUME)
{
    m_SoundEngine = irrklang::createIrrKlangDevice();
    if(!m_SoundEngine)
    {
        std::cout << "\nERROR :: Unable to create an irrKlang::ISoundEngine object" << std::endl;
        return false;
    }
    m_currentPosition = 0.f;
    m_currentVolume = VOLUME;
    SetFileName(FILE_NAME);
    m_SoundEngine->play2D(m_fileName, false, true, true);
    m_SoundEngine->setSoundVolume(VOLUME);
    m_isSoundPlaying = false;
    m_muteVolume = m_currentVolume;

    return true;
}

bool audioplayer::AudioPlayer::IsLoadable()
{
    m_isSoundPlaying = true;
    m_audioState = AudioState::PLAYING;
    if (!(m_Sound = m_SoundEngine->play2D(m_fileName, false, true, true)))
    {
        std::cout << "\nERROR :: Unable to create an irrKlang::ISound object" << std::endl;
        m_isSoundPlaying = false;
        m_audioState = AudioState::STOPPED;
        return false;
    }
    return true;
}

void audioplayer::AudioPlayer::Play()
{
    m_isSoundPlaying = true;
    m_audioState = AudioState::PLAYING;
    m_Sound = m_SoundEngine->play2D(m_fileName, false, false, true);
    m_Sound->setVolume(m_currentVolume);
    m_currentPosition = m_Sound->getPlayPosition();
    m_currentVolume = m_Sound->getVolume();
    m_muteVolume = m_currentVolume;
}

void audioplayer::AudioPlayer::Pause()
{
    m_currentVolume = m_Sound->getVolume();
    m_currentPosition = m_Sound->getPlayPosition();
    m_audioState = AudioState::PAUSED;
    m_Sound->setIsPaused();
    m_muteVolume = m_currentVolume;
}


void audioplayer::AudioPlayer::Resume()
{
    m_audioState = AudioState::PLAYING;
    m_Sound = m_SoundEngine->play2D(m_fileName, false, false, true);
    m_Sound->setVolume(m_currentVolume);
    if(m_currentPosition >= 0)
        m_Sound->setPlayPosition(m_currentPosition);
    m_currentVolume = m_Sound->getVolume();
    m_muteVolume = m_currentVolume;
}


void audioplayer::AudioPlayer::Stop()
{
    m_currentVolume = m_Sound->getVolume();
    m_audioState = AudioState::STOPPED;
    m_Sound->stop();
    m_muteVolume = m_currentVolume;
}

void audioplayer::AudioPlayer::VolumeUp(float INCREMENT)
{
    m_currentVolume += INCREMENT;
    if(m_currentVolume > 1.f)
        m_currentVolume = 1.f;
    m_Sound->setVolume(m_currentVolume);
    m_muteVolume = m_currentVolume;
}

void audioplayer::AudioPlayer::VolumeDown(float DECREMENT)
{
    m_currentVolume -= DECREMENT;
    if(m_currentVolume < 0.f)
        m_currentVolume = 0.f;
    m_Sound->setVolume(m_currentVolume);
    m_muteVolume = m_currentVolume;
}

float audioplayer::AudioPlayer::GetCurrentVolume()
{
    return m_currentVolume;
}

float audioplayer::AudioPlayer::GetMuteVolume()
{
    return m_muteVolume;
}

void audioplayer::AudioPlayer::SetMuteVolume(float VOLUME)
{
    m_muteVolume = VOLUME;
}

void audioplayer::AudioPlayer::SetCurrentVolume(float VOLUME)
{
    m_currentVolume = VOLUME;
    m_muteVolume = m_currentVolume;
}

float audioplayer::AudioPlayer::GetAudioLength()
{
    return m_Sound->getPlayLength();
}

void audioplayer::AudioPlayer::SetVolume(float VOLUME)
{
    m_Sound->setVolume(VOLUME);
    m_currentVolume = m_Sound->getVolume();
}

void audioplayer::AudioPlayer::SetAudioState(AudioState STATE)
{
    m_audioState = STATE;
}

int audioplayer::AudioPlayer::GetAudioState()
{
    return m_audioState;
}

void audioplayer::AudioPlayer::SetFileName(char *FILE_NAME)
{
    m_fileName = FILE_NAME;
}

char *audioplayer::AudioPlayer::GetFileName()
{
    return m_fileName;
}

float audioplayer::AudioPlayer::GetCurrentPosition()
{
    return m_Sound->getPlayPosition();
}

void audioplayer::AudioPlayer::SetCurrentPosition(float POSITION)
{
    m_Sound->setPlayPosition(POSITION);
}

bool audioplayer::AudioPlayer::isAudioPlaying()
{
    if(!m_Sound->isFinished() && !m_Sound->getIsPaused())
        return true;
    return false;
}

void audioplayer::AudioPlayer::Reset()
{
    m_Sound->stop();
}

audioplayer::AudioPlayer::~AudioPlayer()
{
    if (m_Sound != nullptr && m_SoundEngine != nullptr)
    {
        m_Sound->drop();
        m_SoundEngine->drop();
    }
}


/*******************************************************************************************/
//////////////////////////////     end of AudioPlayer.cpp     ///////////////////////////////
/*******************************************************************************************/
