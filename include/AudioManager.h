#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL3/SDL.h>
#include <string>
#include <map>

class AudioManager
{
public:
    // Initiera och stäng ner ljudsystemet
    static bool initialize();
    static void shutdown();
    

    // Ladda, spela och hantera ljud
    static bool loadSound(const std::string& name, const std::string& filepath);
    static void unloadSound(const std::string& name);
    
    static void playSound(const std::string& name, bool loop = false);
    static void stopSound(const std::string& name);
    static void stopAllSounds();
    
    static void setSoundVolume(const std::string& name, float volume);
    static void setMasterVolume(float volume);
    
    AudioManager() = delete;
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    
private:
    struct SoundData
    {
        Uint8* wavData;              // Rå ljuddata
        Uint32 wavDataLen;           // Längd på ljuddata
        SDL_AudioStream* audioStream;// Stream kopplad till enheten
        SDL_AudioSpec audioSpec;     // Format/specifikation för ljudet
        bool isLooping;              // Om ljudet ska loopas
    };
    
    static SDL_AudioDeviceID audioDevice;               // Aktiv audio-enhet
    static std::map<std::string, SoundData> sounds;     // Ljudcache per namn
    static float masterVolume;                          // Volym
    static bool initialized;                            // Init-flagga
};

#endif
