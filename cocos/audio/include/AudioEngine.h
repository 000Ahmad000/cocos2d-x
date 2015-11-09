/****************************************************************************
 Copyright (c) 2014-2015 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#ifndef __AUDIO_ENGINE_H_
#define __AUDIO_ENGINE_H_

#include <functional>
#include <list>
#include <string>
#include <unordered_map>

#include "platform/CCPlatformMacros.h"
#include "Export.h"

#ifdef ERROR
#undef ERROR
#endif // ERROR

/**
 * @addtogroup audio
 * @{
 */

NS_CC_BEGIN
    namespace experimental{

/**
 * @class AudioProfile
 * @js NA
 */
class EXPORT_DLL AudioProfile
{
public:
    //Profile name can't be empty.
    std::string name;
    //The maximum number of simultaneous audio instance.
    unsigned int maxInstances;
    
    /* @~english Minimum delay in between sounds  @~chinese ��С����֮����ӳ�*/
    double minDelay;
    
    /**@~english
     * Default constructor
     *
     * @~chinese 
     * Ĭ�Ϲ��캯��
     * 
     * @lua new
     */
    AudioProfile()
    : maxInstances(0)
    , minDelay(0.0)
    {
        
    }
};

class AudioEngineImpl;

/**
 * @class AudioEngine
 * 
 * @brief @~english Offers a interface to play audio.
 *
 * @~chinese �ṩ��һ����Ƶ���Žӿڡ�
 * 
 * @note @~english Make sure to call AudioEngine::end() when the audio engine is not needed anymore to release resources.
 * @~chinese ����Ƶ���治����Ҫʱȷ������AudioEngine::end()���ͷ���Դ��
 * @js NA
 */
class EXPORT_DLL AudioEngine
{
public:
    /** @~english AudioState enum,all possible states of an audio instance. @~chinese ��Ƶ״̬ö��,��Ƶ�����п���״̬��*/
    enum class AudioState
    {
        ERROR  = -1,
        INITIALZING,
        PLAYING,
        PAUSED
    };
    
    static const int INVALID_AUDIO_ID;

    static const float TIME_UNKNOWN;

    static bool lazyInit();

    /**@~english
     * Release objects relating to AudioEngine.
     *
     * @~chinese 
     * �ͷ���Ƶ�������ض���.
     * 
     * @warning @~english It must be called before the application exit.
     * @~chinese ��Ӧ�ó����˳�֮ǰ����Ҫ��������
     */
    static void end();
    
    /**  @~english
     * Gets the default profile of audio instances.
     *
     * @~chinese 
     * �õ���Ƶ��Ĭ�ϵ����á�
     * 
     * @return @~english The default profile of audio instances.
     * @~chinese ��Ƶ��Ĭ�ϵ����á�
     */
    static AudioProfile* getDefaultProfile();
    
    /** @~english
     * Play 2d sound.
     *
     * @~chinese 
     * Play 2d sound.
     * 
     * @param filePath @~english The path of an audio file.
     * @~chinese һ����Ƶ�ļ���·����
     * @param loop @~english Whether audio instance loop or not.
     * @~chinese ��Ƶ�Ƿ�ѭ�����š�
     * @param volume @~english Volume value (range from 0.0 to 1.0).
     * @~chinese ����ֵ(��Χ��0.0��1.0)��
     * @param profile @~english A profile for audio instance. When profile is not specified, default profile will be used.
     * @~chinese ��Ƶ��һ�������ļ�����û��ָ�������ļ�,��ʹ��Ĭ�ϵ����á�
     * @return @~english An audio ID. It allows you to dynamically change the behavior of an audio instance on the fly.
     *
     * @~chinese һ����ƵID������������̬�ظı�һ����Ƶʵ������Ϊ��
     * 
     * @see `AudioProfile`
     */
    static int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, const AudioProfile *profile = nullptr);
    
    /** @~english
     * Sets whether an audio instance loop or not.
     *
     * @~chinese 
     * ����һ����Ƶʵ���Ƿ�ѭ�����š�
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @param loop @~english Whether audio instance loop or not.
     * @~chinese �Ƿ�ѭ�����š�
     */
    static void setLoop(int audioID, bool loop);

    /** @~english
     * Checks whether an audio instance is loop.
     *
     * @~chinese 
     * ���һ����Ƶʵ���Ƿ�ѭ�����š�
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @return @~english Whether or not an audio instance is loop.
     * @~chinese �Ƿ�ѭ�����š�
     */
    static bool isLoop(int audioID);

    /** @~english
     * Sets volume for an audio instance.
     *
     * @~chinese 
     * ����һ����Ƶʵ����������С��
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @param volume @~english Volume value (range from 0.0 to 1.0).
     * @~chinese ����ֵ(��Χ��0.0��1.0)��
     */
    static void setVolume(int audioID, float volume);

    /** @~english
     * Gets the volume value of an audio instance.
     *
     * @~chinese 
     * ����һ����Ƶʵ��������ֵ��
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @return @~english Volume value (range from 0.0 to 1.0).
     * @~chinese ����ֵ(��Χ��0.0��1.0)��
     */
    static float getVolume(int audioID);

    /** @~english
     * Pause an audio instance.
     *
     * @~chinese 
     * ��ͣһ����Ƶʵ����
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     */
    static void pause(int audioID);

    /** @~english Pause all playing audio instances.  @~chinese ��ͣ�������ڲ��ŵ���Ƶʵ���� */
    static void pauseAll();

    /** @~english
     * Resume an audio instance.
     *
     * @~chinese 
     * �ָ�һ������ͣ����Ƶʵ����
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     */
    static void resume(int audioID);

    /** @~english Resume all suspended audio instances.  @~chinese �ָ�������ͣ��Ƶʵ����*/
    static void resumeAll();

    /** @~english
     * Stop an audio instance.
     *
     * @~chinese 
     * ֹͣһ����Ƶʵ����
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     */
    static void stop(int audioID);

    /** @~english Stop all audio instances.  @~chinese ֹͣ������Ƶʵ����*/
    static void stopAll();

    /**@~english
     * Sets the current playback position of an audio instance.
     *
     * @~chinese 
     * ����һ����Ƶʵ���ĵ�ǰ����λ�á�
     * 
     * @param audioID   @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @param sec       @~english The offset in seconds from the start to seek to.
     * @~chinese ����Ϊ��λ������ڿ�ʼλ�õ�ƫ������
     * @return 
     */
    static bool setCurrentTime(int audioID, float sec);

    /** @~english
     * Gets the current playback position of an audio instance.
     *
     * @~chinese 
     * ����һ����Ƶʵ���ĵ�ǰ����λ�á�
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @return @~english The current playback position of an audio instance.
     * @~chinese ��Ƶʵ���ĵ�ǰ����λ�á�
     */
    static float getCurrentTime(int audioID);

    /** @~english
     * Gets the duration of an audio instance.
     *
     * @~chinese 
     * �õ�һ����Ƶʵ���ĳ���ʱ�䡣
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @return @~english The duration of an audio instance.
     * @~chinese һ����Ƶ�ĳ���ʱ�䡣
     */
    static float getDuration(int audioID);

    /** @~english
     * Returns the state of an audio instance.
     *
     * @~chinese 
     * ����һ����Ƶʵ����״̬��
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @return @~english The status of an audio instance.
     * @~chinese ��Ƶʵ����״̬��
     */
    static AudioState getState(int audioID);

    /** @~english
     * Register a callback to be invoked when an audio instance has completed playing.
     *
     * @~chinese 
     * ����һ������Ƶʵ���������ʱҪ���еĻص���
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @param callback @~english callback
     * @~chinese �ص�
     */
    static void setFinishCallback(int audioID, const std::function<void(int,const std::string&)>& callback);
    
    /**@~english
     * Gets the maximum number of simultaneous audio instance of AudioEngine.
     * @~chinese 
     * ������Ƶ�������󲢷�����
     */
    static int getMaxAudioInstance() {return _maxInstances;}
    
    /**@~english
     * Sets the maximum number of simultaneous audio instance for AudioEngine.
     *
     * @~chinese 
     * ������Ƶ�������󲢷�����
     * 
     * @param maxInstances @~english The maximum number of simultaneous audio instance.
     * @~chinese ͬʱ�ɲ��ŵ���Ƶʵ�����������
     */
    static bool setMaxAudioInstance(int maxInstances);
    
    /** @~english
     * Uncache the audio data from internal buffer.
     * AudioEngine cache audio data on ios,mac, and win32 platform.
     *
     * @~chinese 
     * ���ڲ�������ȡ��һ����Ƶ���ݵĻ��档
     * ��Ƶ�������ios��mac��win32ƽ̨�ϻ�����Ƶ���ݡ�
     * 
     * @warning @~english This can lead to stop related audio first.
     * @~chinese ����ܵ���ֹͣ��ص���Ƶ��
     * @param filePath @~english Audio file path.
     * @~chinese ��Ƶ�ļ�·����
     */
    static void uncache(const std::string& filePath);
    
    /** @~english
     * Uncache all audio data from internal buffer.
     *
     * @~chinese 
     * ���ڲ�������ȡ��������Ƶ�������ݡ�
     * 
     * @warning @~english All audio will be stopped first.
     * @~chinese ������Ƶ����ֹͣ��
     */
    static void uncacheAll();
    
    /**  @~english
     * Gets the audio profile by id of audio instance.
     *
     * @~chinese 
     * ͨ����ƵID�����������á�
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese һ��play2d�������ص���ƵID��
     * @return @~english The audio profile.
     * @~chinese ��Ƶ���á�
     */
    static AudioProfile* getProfile(int audioID);

    /**  @~english
     * Gets an audio profile by name.
     *
     * @~chinese 
     * ͨ����Ƶ�����ļ�����һ����Ƶ���á�
     * 
     * @param profileName @~english A name of audio profile.
     * @~chinese ��Ƶ�����ļ���
     * @return @~english The audio profile.
     * @~chinese ��Ƶ���á�
     */
    static AudioProfile* getProfile(const std::string &profileName);

    /**
     * Preload audio file.
     * @param filePath The file path of an audio.
     */
    static void preload(const std::string& filePath) { preload(filePath, nullptr); }

    /**
     * Preload audio file.
     * @param filePath The file path of an audio.
     * @param callback A callback which will be called after loading is finished.
     */
    static void preload(const std::string& filePath, std::function<void(bool isSuccess)> callback);

protected:
    static void addTask(const std::function<void()>& task);
    static void remove(int audioID);
    
    struct ProfileHelper
    {
        AudioProfile profile;

        std::list<int> audioIDs;

        double lastPlayTime;

        ProfileHelper()
            : lastPlayTime(0.0)
        {

        }
    };
    
    struct AudioInfo
    {
        const std::string* filePath;
        ProfileHelper* profileHelper;
        
        float volume;
        bool loop;
        float duration;
        AudioState state;

        AudioInfo()
            : profileHelper(nullptr)
            , duration(TIME_UNKNOWN)
            , state(AudioState::INITIALZING)
        {

        }
    };

    //audioID,audioAttribute
    static std::unordered_map<int, AudioInfo> _audioIDInfoMap;
    
    //audio file path,audio IDs
    static std::unordered_map<std::string,std::list<int>> _audioPathIDMap;
    
    //profileName,ProfileHelper
    static std::unordered_map<std::string, ProfileHelper> _audioPathProfileHelperMap;
    
    static unsigned int _maxInstances;
    
    static ProfileHelper* _defaultProfileHelper;
    
    static AudioEngineImpl* _audioEngineImpl;

    class AudioEngineThreadPool;
    static AudioEngineThreadPool* s_threadPool;
    
    friend class AudioEngineImpl;
};

}
NS_CC_END

// end group
/// @}

#endif // __AUDIO_ENGINE_H_
#endif
