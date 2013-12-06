/* ================================================================== */
/*
 * SDL_mixer.c
 * Dummy DLL for SDL_mixer.
 *
 * This file is part of LuaSDL.
 *
 * PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
 */
/* ================================================================== */

/* ================================================================== */
/*
 * NOTE:
 * - No error messages are set, so your app should know that it's
 *   never going to use SDL_mixer.
 */
/* ================================================================== */

#include "SDL_mixer.h"

const SDL_version *Mix_Linked_Version(void)
{
    static SDL_version linked_version;
    linked_version.major = 0;
    linked_version.minor = 0;
    linked_version.patch = 0;
    return(&linked_version);
}

int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
{
    return -1;
}

int Mix_AllocateChannels(int numchans)
{
    return 0;
}

int Mix_QuerySpec(int *frequency,Uint16 *format,int *channels)
{
    return 0;
}

Mix_Chunk * Mix_LoadWAV_RW(SDL_RWops *src, int freesrc)
{
    return 0;
}

Mix_Music * Mix_LoadMUS(const char *file)
{
    return 0;
}

Mix_Music * Mix_LoadMUS_RW(SDL_RWops *rw)
{
    return 0;
}

Mix_Chunk * Mix_QuickLoad_WAV(Uint8 *mem)
{
    return 0;
}

Mix_Chunk * Mix_QuickLoad_RAW(Uint8 *mem, Uint32 len)
{
    return 0;
}

void Mix_FreeChunk(Mix_Chunk *chunk)
{
}

void Mix_FreeMusic(Mix_Music *music)
{
}

Mix_MusicType Mix_GetMusicType(const Mix_Music *music)
{
    return 0;
}

void Mix_SetPostMix(void (*mix_func) (void *udata, Uint8 *stream, int len), void *arg)
{
}

void Mix_HookMusic(void (*mix_func) (void *udata, Uint8 *stream, int len), void *arg)
{
}

void Mix_HookMusicFinished(void (*music_finished)(void))
{
}

void * Mix_GetMusicHookData(void)
{
    return 0;
}

void Mix_ChannelFinished(void (*channel_finished)(int channel))
{
}

int Mix_RegisterEffect(int chan, Mix_EffectFunc_t f, Mix_EffectDone_t d, void *arg)
{
    return 0;
}

int Mix_UnregisterEffect(int channel, Mix_EffectFunc_t f)
{
    return 0;
}

int Mix_UnregisterAllEffects(int channel)
{
    return 0;
}

int Mix_SetPanning(int channel, Uint8 left, Uint8 right)
{
    return 0;
}

int Mix_SetPosition(int channel, Sint16 angle, Uint8 distance)
{
    return 0;
}

int Mix_SetDistance(int channel, Uint8 distance)
{
    return 0;
}

int Mix_SetReverseStereo(int channel, int flip)
{
    return 0;
}

int Mix_ReserveChannels(int num)
{
    return 0;
}

int Mix_GroupChannel(int which, int tag)
{
    return 0;
}

int Mix_GroupChannels(int from, int to, int tag)
{
    return 0;
}

int Mix_GroupAvailable(int tag)
{
    return 0;
}

int Mix_GroupCount(int tag)
{
    return 0;
}

int Mix_GroupOldest(int tag)
{
    return 0;
}

int Mix_GroupNewer(int tag)
{
    return 0;
}

int Mix_PlayChannelTimed(int channel, Mix_Chunk *chunk, int loops, int ticks)
{
    return 0;
}

int Mix_PlayMusic(Mix_Music *music, int loops)
{
    return 0;
}

int Mix_FadeInMusic(Mix_Music *music, int loops, int ms)
{
    return 0;
}

int Mix_FadeInMusicPos(Mix_Music *music, int loops, int ms, double position)
{
    return 0;
}

int Mix_FadeInChannelTimed(int channel, Mix_Chunk *chunk, int loops, int ms, int ticks)
{
    return 0;
}

int Mix_Volume(int channel, int volume)
{
    return 0;
}

int Mix_VolumeChunk(Mix_Chunk *chunk, int volume)
{
    return 0;
}

int Mix_VolumeMusic(int volume)
{
    return 0;
}

int Mix_HaltChannel(int channel)
{
    return 0;
}

int Mix_HaltGroup(int tag)
{
    return 0;
}

int Mix_HaltMusic(void)
{
    return 0;
}

int Mix_ExpireChannel(int channel, int ticks)
{
    return 0;
}

int Mix_FadeOutChannel(int which, int ms)
{
    return 0;
}

int Mix_FadeOutGroup(int tag, int ms)
{
    return 0;
}

int Mix_FadeOutMusic(int ms)
{
    return 0;
}

Mix_Fading Mix_FadingMusic(void)
{
    return 0;
}

Mix_Fading Mix_FadingChannel(int which)
{
    return 0;
}

void Mix_Pause(int channel)
{
}

void Mix_Resume(int channel)
{
}

int Mix_Paused(int channel)
{
    return 0;
}

void Mix_PauseMusic(void)
{
}

void Mix_ResumeMusic(void)
{
}

void Mix_RewindMusic(void)
{
}

int Mix_PausedMusic(void)
{
    return 0;
}

int Mix_SetMusicPosition(double position)
{
    return 0;
}

int Mix_Playing(int channel)
{
    return 0;
}

int Mix_PlayingMusic(void)
{
    return 0;
}

int Mix_SetMusicCMD(const char *command)
{
    return 0;
}

int Mix_SetSynchroValue(int value)
{
    return 0;
}

int Mix_GetSynchroValue(void)
{
    return 0;
}

Mix_Chunk * Mix_GetChunk(int channel)
{
    return 0;
}

void Mix_CloseAudio(void)
{
}
