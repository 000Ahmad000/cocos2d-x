/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CC_EXTENTIONS_CCCOMAUDIO_H__
#define __CC_EXTENTIONS_CCCOMAUDIO_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

 /** 
 @���� ComAudio
 @���� �������
 @ϸ�� ���������ļ�·������װ���ű������֣�Ч���ӿڣ����������ʽ��̣���Ͻ���cocos studio 1.x�����༭������������
 @�� ���
 */
class CC_STUDIO_DLL ComAudio : public cocos2d::Component
{

    DECLARE_CLASS_COMPONENT_INFO

public:
    /**
     * @js ctor
     */
    /**
    @���� ����������캯��
    */
    ComAudio(void);
    /**
     * @js NA
     * @lua NA
     */
    /**
    @���� ���������������
    */
    virtual ~ComAudio(void);
    
public:
    /**
    @���� ��ʼ���������
    @���� true ��ʼ���ɹ�������false
    */
    virtual bool init() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @���� node����onEnter��ʱ�򣬻���������onEnter
    @���� ��
    */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @���� node����onExit��ʱ�򣬻���������onExit
    @���� ��
    */
    virtual void onExit() override;
    /**
    @���� �ж���������Ƿ����
    @���� ���÷���true�����򷵻�false
    */
    virtual bool isEnabled() const override;
    /**
    @���� ���õ�ǰ��������Ƿ����
    @���� b trueΪ���ã�falseΪ������
    @���� ��
    */
    virtual void setEnabled(bool b) override;
    /**
    @���� ����cocos studio 1.x �����༭��������json���ݷ����л�����
    @���� r SerData����ָ��
    @���� true �����л��ɹ���false �����л�ʧ��
    */
    virtual bool serialize(void* r) override;
   /**
    @���� �����������
    @���� �������ָ��
    */
    static ComAudio* create(void);
   
public:
   /**
    @���� �ͷ������������ֹͣ�������б���������Ч
    @���� ��
    */
    void end();
    /**
    @���� Ԥ���ر�������
    @���� pszFilePath ��������·��
    @���� ��
    */
    void preloadBackgroundMusic(const char* pszFilePath);
    /**
    @���� ���ű������֣��������û��Ԥ���ش����֣�����Ԥ���أ�Ȼ��ִ�в���
    @���� pszFilePath ��������·��
    @���� bLoop true ѭ������ false ����һ��
    @���� ��
    */
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);
    /**
    @���� ���ű������֣��������û��Ԥ���ش����֣�����Ԥ���أ�Ȼ�󲥷ţ����ݳ�Ա����_loop�ж��Ƿ�ѭ������
    @���� pszFilePath ��������·��
    @���� ��
    */
    void playBackgroundMusic(const char* pszFilePath);
    /**
    @���� ����_filePath��_loop�����ű�������
    @���� ��
    */
    void playBackgroundMusic();
    /**
    @���� ֹͣ���ű������ֲ��Ƿ��ͷ����ֻ���
    @���� bReleaseData true ֹͣ���ͷŻ��� false ��ֹͣ����
    @���� ��
    */
    void stopBackgroundMusic(bool bReleaseData);
    /**
    @���� ֹͣ���ű�������
    @���� ��
    */
    void stopBackgroundMusic();
    /**
    @���� ��ͣ���ű�������
    @���� ��
    */
    void pauseBackgroundMusic();
    /**
    @���� �ָ���ͣ���������ű�������
    @���� ��
    */
    void resumeBackgroundMusic();
    /**
    @���� �������ű�������
    @���� ��
    */
    void rewindBackgroundMusic();
    /**
    @���� ���������Ƿ���Խ�Ҫ����
    @���� true ���Բ��� false �����ܲ���
    */
    bool willPlayBackgroundMusic();
    /**
    @���� ���������Ƿ����ڲ���
    @���� true ���ڲ��� ���� false
    */
    bool isBackgroundMusicPlaying();
    /**
    @���� ��ȡ������������
    @���� �������ֵ�����
    */
    float getBackgroundMusicVolume();
    /**
    @���� ���ñ�����������
    @���� volume ������С
    @���� ��
    */
    void setBackgroundMusicVolume(float volume);
    /**
    @���� ��ȡЧ����������
    @���� ����Ч��������
    */
    float getEffectsVolume();
    /**
    @���� ����Ч����������
    @���� volume ������С
    @���� ��
    */
    void setEffectsVolume(float volume);
    /**
    @���� ����Ч�����֣��������û��Ԥ���ش����֣�����Ԥ���أ�Ȼ�󲥷�
    @���� pszFilePath Ч������·��
    @���� bLoop true ѭ������ false ����һ��
    @���� Ч������ID
    */
    unsigned int playEffect(const char* pszFilePath, bool bLoop);
    /**
    @���� ����Ч�����֣��������û��Ԥ���ش����֣�����Ԥ���أ�Ȼ�󲥷ţ����ݳ�Ա����_loop�ж��Ƿ�ѭ������
    @���� pszFilePath ��������·��
    @���� Ч������ID
    */
    unsigned int playEffect(const char* pszFilePath);
    /**
    @���� ����_filePath��_loop�����Ų�������
    @���� Ч������ID
    */
    unsigned int playEffect();
    /**
    @���� ��ͣ����Ч������
    @���� nSoundID Ч������ID
    @���� ��
    */
    void pauseEffect(unsigned int nSoundId);
    /**
    @���� ��ͣ����Ч������
    @���� ��
    */
    void pauseAllEffects();
    /**
    @���� �ָ���ͣЧ�����֣���������
    @���� nSoundID Ч������ID
    @���� ��
    */
    void resumeEffect(unsigned int nSoundId);
    /**
    @���� �ָ���ͣ������Ч�����֣���������
    @���� ��
    */
    void resumeAllEffects();
    /**
    @���� ֹͣ����Ч������
    @���� nSoundID Ч������ID
    @���� ��
    */
    void stopEffect(unsigned int nSoundId);
    /**
    @���� ֹͣ����Ч������
    @���� ��
    */
    void stopAllEffects();
    /**
    @���� Ԥ����Ч������
    @���� pszFilePath ��������·��
    @���� ��
    */
    void preloadEffect(const char* pszFilePath);
    /**
    @���� �ͷ�Ԥ����Ч�����ֻ���
    @���� pszFilePath ��������·��
    @���� ��
    */
    void unloadEffect(const char* pszFilePath);
    /**
    @���� ��������·��
    @���� pszFilePath ����·��
    @���� ��
    */
    void setFile(const char* pszFilePath);
    /**
    @���� ��ȡ����·��
    @���� _filePath ����·��
    */
    const char* getFile();
    /**
    @���� �����Ƿ�ѭ��
    @���� bLoop �Ƿ�ѭ��
    @���� ��
    */
    void setLoop(bool bLoop);
    /**
    @���� �ж��Ƿ�ѭ��
    @���� true ѭ�� false ��ѭ��
    */
    bool isLoop();
private:
	std::string _filePath;
	bool _loop;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
