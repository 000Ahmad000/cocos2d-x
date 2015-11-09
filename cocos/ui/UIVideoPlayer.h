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

#ifndef __COCOS2D_UI_VIDEOWEIGTH_H_
#define __COCOS2D_UI_VIDEOWEIGTH_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "ui/UIWidget.h"

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN
namespace experimental{
    namespace ui{

        /**
         * @class VideoPlayer
         * @brief @~english Displays a video file.
         * @~chinese һ��������Ƶ�ļ��Ŀؼ���
         * 
         * @note @~english VideoPlayer displays a video file base on system widget.
         * It's mean VideoPlayer displays a video file above all graphical elements of cocos2d-x.
         * @~chinese VideoPlayer����ϵͳ�ؼ�ʵ�ֵ���Ƶ���ţ�����ζ����Ƶ�ᱻ��ʾ��cocos2d-x������ͼ��Ԫ��֮�ϡ�
         * @js NA
         */
        class VideoPlayer : public cocos2d::ui::Widget
        {
        public:
            /**
             * @~english Videoplayer play event type.
             * @~chinese Videoplayer��Ƶ�����¼���
             */
            enum class EventType
            {
                PLAYING = 0,
                PAUSED,
                STOPPED,
                COMPLETED
            };

            /**
             * @~english A callback which will be called after specific VideoPlayer event happens.
             * @~chinese VideoPlayer��������¼�����ʱ�Ļص���
             */
            typedef std::function<void(Ref*,VideoPlayer::EventType)> ccVideoPlayerCallback;

            /**@~english
             * Static create method for instancing a VideoPlayer.
             * @~chinese 
             * һ��ʵ����VideoPlayer�ľ�̬����������
             */
            CREATE_FUNC(VideoPlayer);

            /**@~english
             * Sets a file path as a video source for VideoPlayer.
             * @~chinese 
             * ����һ����Ƶ�ļ�·����ΪVideoPlayer����ƵԴ��
             */
            virtual void setFileName(const std::string& videoPath);
            
            /**
             * @brief @~english Get the filie path of video source.
             * @~chinese ��ȡ��ƵԴ���ļ�·����
             * 
             * @return @~english The video file path.
             * @~chinese ��Ƶ��Ƶ�ļ���·����
             */
            virtual const std::string& getFileName() const { return _videoURL;}

            /**@~english
             * Sets a URL as a video source for VideoPlayer.
             * @~chinese 
             * ����һ��URL��ַ��ΪVideoPlayer����ƵԴ��
             */
            virtual void setURL(const std::string& _videoURL);

            
            /**
             * @brief @~english Get the URL of video source.
             *
             * @~chinese ��ȡ��ƵԴ��URL��
             * 
             * @return @~english A URL address.
             * @~chinese һ��URL��ַ��
             */
            virtual const std::string& getURL() const { return _videoURL;}

            /**
             * @~english Starts playback.
             * @~chinese ��ʼ���š�
             */
            virtual void play();

            /**
             * @~english Pauses playback.
             * @~chinese ��ͣ���š�
             */
            virtual void pause()override;

            /**
             * @~english Resumes playback.
             * @~chinese �ָ����š�
             */
            virtual void resume()override;

            /**
             * @~english Stops playback.
             * @~chinese ֹͣ���š�
             */
            virtual void stop();

            /**
             * @~english Seeks to specified time position.
             * @~chinese ��ת��ָ����ʱ��λ�á�
             * 
             * @param sec @~english The offset in seconds from the start to seek to.
             * @~chinese �����ʼλ�õ�ƫ����������Ϊ��λ��
             */
            virtual void seekTo(float sec);

            /**
             * @~english Checks whether the VideoPlayer is playing.
             * @~chinese ���VideoPlayer��ǰ�Ƿ����ڲ��š�
             * 
             * @return @~english True if currently playing, false otherwise.
             * @~chinese VideoPlayer������ڲ��ŷ���true�����򷵻�false��
             */
            virtual bool isPlaying() const;

            /**
             * @~english Causes the video player to keep aspect ratio or no when displaying the video.
             * @~chinese ������Ƶ����ʱ�Ƿ񱣳ֳ���ȡ�
             * 
             * @param enable @~english Specify true to keep aspect ratio or false to scale the video until 
             * both dimensions fit the visible bounds of the view exactly.
             * @~chinese ����Ϊtrueʱ���ֳ���ȣ�������Ƶ�ᱻ�����������������ſؼ���
             */
            virtual void setKeepAspectRatioEnabled(bool enable);

            /**@~english
             * Indicates whether the video player keep aspect ratio when displaying the video.
             * @~chinese ��ȡ��Ƶ�����Ƿ񱣳ֳ����
             */
            virtual bool isKeepAspectRatioEnabled()const { return _keepAspectRatioEnabled;}

            /**
             * @~english Causes the video player to enter or exit full-screen mode.
             * @~chinese ������Ƶ�����Ƿ�ȫ��ģʽ��
             * 
             * @param fullscreen @~english Specify true to enter full-screen mode or false to exit full-screen mode.
             * @~chinese ָ��trueʱ����ȫ������ģʽ��
             */
            virtual void setFullScreenEnabled(bool fullscreen);

            /**
             * @~english Indicates whether the video player is in full-screen mode.
             * @~chinese ��ȡ��Ƶ�������Ƿ����ȫ��ģʽ��
             * 
             * @return @~english True if the video player is in full-screen mode, false otherwise.
             * @~chinese �����Ƶ��������ȫ������ģʽ�·���true,���򷵻�false��
             */
            virtual bool isFullScreenEnabled()const;

            /**
             * @~english Register a callback to be invoked when the video state is updated.
             * @~chinese ע����Ƶ����״̬�ı�ʱ�Ļص���
             * 
             * @param callback @~english a callback.
             * @~chinese �ص���
             */
            virtual void addEventListener(const VideoPlayer::ccVideoPlayerCallback& callback);
            
            /**
             * @~english A function which will be called when video the video state is updated.
             * @~chinese ��Ƶ״̬�ı�ʱ�����õ�һ����Ա������
             * 
             * @param event @~english event code. @~chinese �¼����롣
             * @see VideoPlayer::EventType.
             */
            virtual void onPlayEvent(int event);

            virtual void setVisible(bool visible) override;
            virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;

        protected:
            virtual cocos2d::ui::Widget* createCloneInstance() override;
            virtual void copySpecialProperties(Widget* model) override;
            
        CC_CONSTRUCTOR_ACCESS:
            VideoPlayer();
            virtual ~VideoPlayer();

        protected:
#if CC_VIDEOPLAYER_DEBUG_DRAW
            DrawNode *_debugDrawNode;
#endif

            enum class Source
            {
                FILENAME = 0,
                URL
            };

            bool _isPlaying;
            bool _fullScreenDirty;
            bool _fullScreenEnabled;
            bool _keepAspectRatioEnabled;

            std::string _videoURL;
            Source _videoSource;

            int _videoPlayerIndex;
            ccVideoPlayerCallback _eventCallback;

            void* _videoView;
        };
    }
}

NS_CC_END
// end group
/// @}
#endif
#endif
