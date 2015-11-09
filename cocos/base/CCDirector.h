/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#ifndef __CCDIRECTOR_H__
#define __CCDIRECTOR_H__

#include <stack>
#include <thread>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "2d/CCScene.h"
#include "math/CCMath.h"
#include "platform/CCGL.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

/**
 * @addtogroup base
 * @{
 */

/* Forward declarations.*/
class LabelAtlas;
//class GLView;
class DirectorDelegate;
class Node;
class Scheduler;
class ActionManager;
class EventDispatcher;
class EventCustom;
class EventListenerCustom;
class TextureCache;
class Renderer;
class Camera;

class Console;
namespace experimental
{
    class FrameBuffer;
}

/**
 * @brief @~english Matrix stack type.
 * @~chinese ����ջ���͡�
 */
enum class MATRIX_STACK_TYPE
{
    /// Model view matrix stack
    MATRIX_STACK_MODELVIEW,
    
    /// projection matrix stack
    MATRIX_STACK_PROJECTION,
    
    /// texture matrix stack
    MATRIX_STACK_TEXTURE
};

/**
 @brief @~english Class that creates and handles the main Window and manages how
 and when to execute the Scenes.
 
 The Director is also responsible for:
 - initializing the OpenGL context
 - setting the OpenGL buffer depth (default one is 0-bit)
 - setting the projection (default one is 3D)
 
 Since the Director is a singleton, the standard way to use it is by calling:
 * Director::getInstance()->methodName();
 * @~chinese �����࣬���𴴽��ʹ��������ڣ��Լ�������ִ�С�
 * 
 * ���ݻ�����:
 * -��ʼ��OpenGL������
 * -����OpenGL���������(Ĭ����0)
 * -����ͶӰ(Ĭ����3d)
 * 
 * Since the Director is a singleton, the standard way to use it is by calling:
 * ��������һ����������׼�ĵ��÷������£�
 * Director::getInstance()- > methodName();
 */
class CC_DLL Director : public Ref
{
public:
    /** @~english Director will trigger an event when projection type is changed.  @~chinese ��ͶӰ���ͱ仯ʱ���ݽ�����һ���¼���*/
    static const char* EVENT_PROJECTION_CHANGED;
    /** Director will trigger an event before Schedule::update() is invoked. */
    static const char* EVENT_BEFORE_UPDATE;
    /** @~english Director will trigger an event after Schedule::update() is invoked.  @~chinese �ڵ���Schedule::update()���ݻᴥ��һ���¼���*/
    static const char* EVENT_AFTER_UPDATE;
    /** @~english Director will trigger an event after Scene::render() is invoked.  @~chinese �ڵ���Scene::render()���ݽ�����һ���¼���*/
    static const char* EVENT_AFTER_VISIT;
    /** @~english Director will trigger an event after a scene is drawn, the data is sent to GPU.  @~chinese ��һ����������,���ݱ����͵�GPU���ݽ�����һ���¼���*/
    static const char* EVENT_AFTER_DRAW;

    /**
     * @brief @~english Possible OpenGL projections used by director
     * @~chinese ����ʹ�õĿ��ܵ�OpenGLͶӰ����
     */
    enum class Projection
    {
        /// Sets a 2D projection (orthogonal projection).
        _2D,
        
        /// Sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
        _3D,
        
        /// It calls "updateProjection" on the projection delegate.
        CUSTOM,
        
        /// Default projection is 3D projection.
        DEFAULT = _3D,
    };
    
    /** @~english
     * Returns a shared instance of the director. 
     * @~chinese 
     * ����һ�����ݵĵ�����
     * @js _getInstance
     */
    static Director* getInstance();

    /**
     * @deprecated Use getInstance() instead.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE static Director* sharedDirector() { return Director::getInstance(); }
    
    /**
     * @js ctor
     */
    Director();
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Director();
    virtual bool init();

    // attribute

    /** @~english Gets current running Scene. Director can only run one Scene at a time.  @~chinese �õ���ǰ���г���������һ��ֻ������һ��������*/
    inline Scene* getRunningScene() { return _runningScene; }

    /** @~english Gets the FPS value.  @~chinese �õ���FPS��ֵ��*/
    inline float getAnimationInterval() { return _animationInterval; }
    /** @~english Sets the FPS value. FPS = 1 @~chinese ����FPS��ֵ��FPS = 1 */
    virtual void setAnimationInterval(float interval) = 0;

    /** @~english Whether or not to display the FPS on the bottom-left corner.  @~chinese ���½��Ƿ�����ʾFPS��*/
    inline bool isDisplayStats() { return _displayStats; }
    /** @~english Display the FPS on the bottom-left corner.  @~chinese �����Ƿ������½���ʾFPS��*/
    inline void setDisplayStats(bool displayStats) { _displayStats = displayStats; }
    
    /** @~english Get seconds per frame.  @~chinese ��ȡÿ֡������롣*/
    inline float getSecondsPerFrame() { return _secondsPerFrame; }

    /** @~english
     * Get the GLView.
     * @~chinese 
     * ��ȡGLView��
     * @lua NA
     */
    inline GLView* getOpenGLView() { return _openGLView; }
    /** @~english
     * Sets the GLView. 
     * @~chinese 
     * ����GLView��
     * @lua NA
     */
    void setOpenGLView(GLView *openGLView);

    /*@~english
     * Gets singleton of TextureCache.
     * @~chinese 
     * ��ȡTextureCache������
     * @js NA
     */
    TextureCache* getTextureCache() const;

    /** @~english Whether or not `_nextDeltaTimeZero` is set to 0.  @~chinese ��_nextDeltaTimeZero���Ƿ�����Ϊ0��*/
    inline bool isNextDeltaTimeZero() { return _nextDeltaTimeZero; }
    /** @~english
     * Sets the delta time between current frame and next frame is 0.
     * This value will be used in Schedule, and will affect all functions that are using frame delta time, such as Actions.
     * This value will take effect only one time.
     * @~chinese 
     * ���õ�ǰ֡����һ��֮֡��ʱ��Ϊ0��
     * ���ֵ����Schedule,����Ӱ������ʹ��֡���ʱ��ĺ���,����Actions��
     * ���ֵֻ��Чһ�Ρ�
     */
    void setNextDeltaTimeZero(bool nextDeltaTimeZero);

    /** @~english Whether or not the Director is paused.  @~chinese �����Ƿ���ͣ��*/
    inline bool isPaused() { return _paused; }

    /** @~english How many frames were called since the director started  @~chinese ��ȡ���ݿ�ʼ������Ϸ���е���֡����*/
    inline unsigned int getTotalFrames() { return _totalFrames; }
    
    /** @~english Gets an OpenGL projection.
     * @~chinese ��ȡOpenGLͶӰ��
     * @since v0.8.2
     * @lua NA
     */
    inline Projection getProjection() { return _projection; }
    /** @~english Sets OpenGL projection.  @~chinese ����OpenGLͶӰ��*/
    void setProjection(Projection projection);
    
    /** @~english Sets the glViewport. @~chinese ����glViewport��*/
    void setViewport();    
    
    /** @~english Whether or not the replaced scene will receive the cleanup message.
     * If the new scene is pushed, then the old scene won't receive the "cleanup" message.
     * If the new scene replaces the old one, the it will receive the "cleanup" message.
     * @~chinese ��������ʱ�Ƿ����������Ϣ��
     * ����³����ǲ���push��ʽ����ģ���ô�ɵĳ�����������յ�"cleanup"��Ϣ��
     * ����³���ȡ���ɵĳ���,��������յ�"cleanup"��Ϣ��
     * @since v0.99.0
     */
    inline bool isSendCleanupToScene() { return _sendCleanupToScene; }

    /** @~english This object will be visited after the main scene is visited.
     * This object MUST implement the "visit" function.
     * Useful to hook a notification object, like Notifications (http://github.com/manucorporat/CCNotifications)
     * @~chinese ������󽫻�����������Ⱦ�����Ⱦ��
     * ����������ʵ�֡�visit�����ܡ�
     * ����hookһ��֪ͨ�ڵ������,���� Notifications (http://github.com/manucorporat/CCNotifications)
     * @since v0.99.5
     */
    Node* getNotificationNode() const { return _notificationNode; }
    /** @~english
     * Sets the notification node.
     * @~chinese 
     * ����֪ͨ�ڵ㡣
     * @see Director::getNotificationNode()
     */
    void setNotificationNode(Node *node);
    
    // window size

    /** @~english Returns the size of the OpenGL view in points.  @~chinese ����OpenGL��ͼ�Ĵ�С���Ե�Ϊ��λ��*/
    const Size& getWinSize() const;

    /** @~english Returns the size of the OpenGL view in pixels.  @~chinese ����OpenGL��ͼ�д�С��������Ϊ��λ��*/
    Size getWinSizeInPixels() const;
    
    /** @~english
     * Returns visible size of the OpenGL view in points.
     * The value is equal to `Director::getWinSize()` if don't invoke `GLView::setDesignResolutionSize()`.
     * @~chinese 
     * ���ؿɼ�OpenGL��ͼ��С���Ե�Ϊ��λ��
     * ���������GLView:setDesignResolutionSize"�Ļ�����ֵ���ڡ�Director::getWinSize()����
     */
    Size getVisibleSize() const;
    
    /** @~english Returns visible origin coordinate of the OpenGL view in points.  @~chinese ���ؿɼ�OpenGL��ͼ��ʼ�㣬�Ե�Ϊ��λ��*/
    Vec2 getVisibleOrigin() const;

    /** @~english
     * Converts a screen coordinate to an OpenGL coordinate.
     * Useful to convert (multi) touch coordinates to the current layout (portrait or landscape).
     * @~chinese 
     * ����Ļ����ת��Ϊһ��OpenGL���ꡣ
     * ���ڽ�(���)��������ת��Ϊ��ǰ����(���������)�����á�
     */
    Vec2 convertToGL(const Vec2& point);

    /** @~english
     * Converts an OpenGL coordinate to a screen coordinate.
     * Useful to convert node points to window points for calls such as glScissor.
     * @~chinese 
     * ת��һ��OpenGL���굽��Ļ���ꡣ
     * ���ڱ���glScissor���ý�node��ת�������ڵ�����á�
     */
    Vec2 convertToUI(const Vec2& point);

    /** @~english
     * Gets the distance between  camera and near clipping frame.
     * It is correct for default camera that near clipping frame is the same as screen.
     * @~chinese 
     * ��ȡcamera��near clipping frame�ľ��롣
     * Ĭ�ϵ�camera��near clipping frame�Ǻ�screenһ���ġ�
     */
    float getZEye() const;

    // Scene Management

    /** @~english
     * Enters the Director's main loop with the given Scene.
     * Call it to run only your FIRST scene.
     * Don't call it if there is already a running scene.
     *
     * It will call pushScene: and then it will call startAnimation
     * @~chinese 
     * ͨ�������ĳ������뵼�ݵ���ѭ����
     * ֻ����������ĵ�һ��������������
     * ������Ѿ���һ���������еĳ�����Ҫ��������
     * 
     * ��������pushScene:Ȼ�󽫵���startAnimation
     * @js NA
     */
    void runWithScene(Scene *scene);

    /** @~english
     * Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
     * The new scene will be executed.
     * Try to avoid big stacks of pushed scenes to reduce memory allocation. 
     * ONLY call it if there is a running scene.
     * @~chinese 
     * ��ͣ��ǰ���еĳ���,ѹ�뵽��ͣ�ĳ���ջ�С�
     * �³�������ִ�С�
     * ��������ѹ��󳡾�,�Լ����ڴ���䡣
     * ֻ���������г���ʱ��������
     */
    void pushScene(Scene *scene);

    /** @~english
     * Pops out a scene from the stack.
     * This scene will replace the running one.
     * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
     * ONLY call it if there is a running scene.
     * @~chinese 
     * �Ӷ�ջ�е�����һ��������
     * ��һ��������ȡ����ǰ���еĳ�����
     * ���г�������ɾ�����������ջû�и���ĳ����Ļ�ִ�н�����ֹ��
     * ֻ���������г���ʱ��������
     */
    void popScene();

    /** @~english
     * Pops out all scenes from the stack until the root scene in the queue.
     * This scene will replace the running one.
     * Internally it will call `popToSceneStackLevel(1)`.
     * @~chinese 
     * �Ӷ�ջ�е������г���������������
     * ��һ��������ȡ����ǰ���еĳ�����
     * �ڲ�����á�popToSceneStackLevel(1)����
     */
    void popToRootScene();

    /** @~english Pops out all scenes from the stack until it reaches `level`.
     If level is 0, it will end the director.
     If level is 1, it will pop all scenes until it reaches to root scene.
     If level is <= than the current stack level, it won't do anything.
     * @~chinese �Ӷ�ջ�е������г���,ֱ������ڡ�level������
     * �������Ϊ0,�����������ݵ�ִ�С�
     * ���������1,��ô�����������г���,ֱ��������ĳ�����
     * �������С�ڵ��ڱȵ�ǰ��ջ����,���������κ����顣
     */
 	void popToSceneStackLevel(int level);

    /** @~english Replaces the running scene with a new one. The running scene is terminated.
     * ONLY call it if there is a running scene.
     * @~chinese ���µĳ����滻���г�������ֹ�������еĳ�����
     * ֻ���������г���ʱ��������
     * @js NA
     */
    void replaceScene(Scene *scene);

    /** @~english Ends the execution, releases the running scene.
     * @~chinese ִ�н���,�ͷ����г�����
     * @lua endToLua
     */
    void end();

    /** @~english Pauses the running scene.
     * The running scene will be drawed, but all scheduled timers will be paused.
     * While paused, the draw rate will be 4 FPS to reduce CPU consumption.
     * @~chinese ��ͣ�������еĳ�����
     * ���г��������ƣ�������scheduled timers����ͣ��
     * һ����ͣ,FPS���ή����4�Լ���CPU���ġ�
     */
    void pause();

    /** @~english Resumes the paused scene.
     * The scheduled timers will be activated again.
     * The "delta time" will be 0 (as if the game wasn't paused).
     * @~chinese �ָ���ͣ������
     * scheduled timers���ٴα����
     * ��delta time������Ϊ0(��������Ϸû����ͣһ��)��
     */
    void resume();
    
    /*@~english
     * Restart the director. 
     * @~chinese 
     * �����������ݡ�
     * @js NA
     */
    void restart();

    /** @~english Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
     * If you don't want to pause your animation call [pause] instead.
     * @~chinese ֹͣ�����������л��ơ���ѭ�������ٱ�������
     * ����㲻����ͣ�����������[pause]��
     */
    virtual void stopAnimation() = 0;

    /** @~english The main loop is triggered again.
     * Call this function only if [stopAnimation] was called earlier.
     * @~chinese ��ѭ������һ�Ρ�
     * ֻ��֮ǰ���ù�stopAnimation�����ܵ������������
     * @warning @~english Don't call this function to start the main loop. To run the main loop call runWithScene.
     * @~chinese �����������������ʼ��ѭ���������runWithScene����ʼ��ѭ����
     */
    virtual void startAnimation() = 0;

    /** @~english Draw the scene.
     * This method is called every frame. Don't call it manually.
     * @~chinese ���Ƴ�����
     * ÿһ֡������ô˷�������Ҫ�ֶ���������
     */
    void drawScene();

    // Memory Helper

    /** @~english Removes all cocos2d cached data.
     * It will purge the TextureCache, SpriteFrameCache, LabelBMFont cache
     * @~chinese ɾ������cocos2d��������ݡ�
     * �������TextureCache��SpriteFrameCache��LabelBMFont����
     * @since v0.99.3
     */
    void purgeCachedData();

	/** @~english Sets the default values based on the Configuration info.  @~chinese ����Configuration��Ϣ����Ĭ��ֵ��*/
    void setDefaultValues();

    // OpenGL Helper

    /** @~english Sets the OpenGL default values.
     * It will enable alpha blending, disable depth test.
     * @~chinese ����OpenGLĬ��ֵ��
     * ��������alpha blending��������Ȳ��ԡ�
     * @js NA
     */
    void setGLDefaultValues();

    /** @~english Enables/disable alpha blending @~chinese ����/����alpha blending */
    void setAlphaBlending(bool on);
    
    /** @~english Sets clear values for the color buffers,
     * value range of each element is [0.0, 1.0].
     * @~chinese ����ɫ�����������ֵ,
     * ÿ��Ԫ�ص�ֵ��Χ��[0.0,1.0]��
     * @js NA
     */
    void setClearColor(const Color4F& clearColor);

    /** @~english Enable/disable depth test @~chinese ����/������Ȳ���  */
    void setDepthTest(bool on);

    virtual void mainLoop() = 0;

    /** @~english The size in pixels of the surface. It could be different than the screen size.
     * High-res devices might have a higher surface size than the screen size.
     * Only available when compiled using SDK >= 4.0.
     * @~chinese surface�Ĵ�С(������Ϊ��λ)�������ܻ���Ļ��С��ͬ��
     * �߷ֱ��ʵ��豸������Ļ�ߴ��С����������һ�����ߵ�surface��
     * ֻ�е�ʹ�ô���4.0��SDK�������Ч��
     * @since v0.99.4
     */
    void setContentScaleFactor(float scaleFactor);
    /**@~english
     * Gets content scale factor.
     * @~chinese 
     * ��ȡ�������ű�����
     * @see Director::setContentScaleFactor()
     */
    float getContentScaleFactor() const { return _contentScaleFactor; }

    /** @~english Gets the Scheduler associated with this director.
     * @~chinese ��ȡ�͵���������ĵ�������
     * @since v2.0
     */
    Scheduler* getScheduler() const { return _scheduler; }
    
    /** @~english Sets the Scheduler associated with this director.
     * @~chinese ���ú͵���������ĵ�������
     * @since v2.0
     */
    void setScheduler(Scheduler* scheduler);

    /** @~english Gets the ActionManager associated with this director.
     * @~chinese ��ȡ�͵���������Ķ�����������
     * @since v2.0
     */
    ActionManager* getActionManager() const { return _actionManager; }
    
    /** @~english Sets the ActionManager associated with this director.
     * @~chinese ���ú͵���������Ķ�����������
     * @since v2.0
     */
    void setActionManager(ActionManager* actionManager);
    
    /** @~english Gets the EventDispatcher associated with this director.
     * @~chinese ��ȡ�͵�����������¼��ַ�����
     * @since v3.0
     * @js NA
     */
    EventDispatcher* getEventDispatcher() const { return _eventDispatcher; }
    
    /** @~english Sets the EventDispatcher associated with this director.
     * @~chinese ���ú͵�����������¼��ַ�����
     * @since v3.0
     * @js NA
     */
    void setEventDispatcher(EventDispatcher* dispatcher);

    /** @~english Returns the Renderer associated with this director.
     * @~chinese ��ȡ�͵������������Ⱦ����
     * @since v3.0
     */
    Renderer* getRenderer() const { return _renderer; }

    /** @~english Returns the Console associated with this director.
     * @~chinese ��ȡ�͵���������Ŀ���̨��
     * @since v3.0
     * @js NA
     */
    Console* getConsole() const { return _console; }

    /* @~english Gets delta time since last tick to main loop.  @~chinese ��ȡmainloop����һ��tick��ʱ������*/
    float getDeltaTime() const;
    
    /**@~english
     *  Gets Frame Rate.
     * @~chinese 
     * ��ȡ֡���ʡ�
     * @js NA
     */
    float getFrameRate() const { return _frameRate; }

    /** @~english
     * Clones a specified type matrix and put it to the top of specified type of matrix stack.
     * @~chinese 
     * ��¡һ��ָ�����͵ľ���,�����ŵ�ָ�����͵ľ����ջ�Ķ�����
     * @js NA
     */
    void pushMatrix(MATRIX_STACK_TYPE type);
    /** @~english Pops the top matrix of the specified type of matrix stack.
     * @~chinese ����ָ�����͵ľ����ջ�Ķ�������
     * @js NA
     */
    void popMatrix(MATRIX_STACK_TYPE type);
    /** @~english Adds an identity matrix to the top of specified type of matrxi stack.
     * @~chinese ��ָ�����͵ľ����ջ�Ķ������һ����λ����
     * @js NA
     */
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);
    /**@~english
     * Adds a matrix to the top of specified type of matrix stack.
     * 
     * @~chinese 
     * ��ָ�����͵ľ����ջ�Ķ������һ������
     * 
     * @param type @~english Matrix type.
     * @~chinese �������͡�
     * @param mat @~english The matrix that to be added.
     * @~chinese Ҫ��ӵľ���
     * @js NA
     */
    void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    /**@~english
     * Multiplies a matrix to the top of specified type of matrix stack.
     *
     * @~chinese 
     * ��ָ�����͵ľ����ջ�Ķ���������г˷����㡣
     * 
     * @param type @~english Matrix type.
     * @~chinese �������͡�
     * @param mat @~english The matrix that to be multipied.
     * @~chinese Ҫ���г˷�����ľ���
     * @js NA
     */
    void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    /**@~english
     * Gets the top matrix of specified type of matrix stack.
     * @~chinese 
     * ��ȡָ�����͵ľ����ջ�����ľ���
     * @js NA
     */
    const Mat4& getMatrix(MATRIX_STACK_TYPE type);
    /**@~english
     * Clears all types of matrix stack, and add indentity matrix to these matrix stacks.
     * @~chinese 
     * ����������͵ľ����ջ,����ӵ�λ������Щ����ջ��
     * @js NA
     */
    void resetMatrixStack();

    /**
     * returns the cocos2d thread id.
     Useful to know if certain code is already running on the cocos2d thread
     */
    const std::thread::id& getCocos2dThreadId() const { return _cocos2d_thread_id; }

protected:
    void reset();
    
    void purgeDirector();
    bool _purgeDirectorInNextLoop; // this flag will be set to true in end()
    
    void restartDirector();
    bool _restartDirectorInNextLoop; // this flag will be set to true in restart()
    
    void setNextScene();
    
    void showStats();
    void createStatsLabel();
    void calculateMPF();
    void getFPSImageData(unsigned char** datapointer, ssize_t* length);
    
    /** @~english calculates delta time since last time it was called  @~chinese �������������ϴα���Ϊ*/    
    void calculateDeltaTime();

    //textureCache creation or release
    void initTextureCache();
    void destroyTextureCache();

    void initMatrixStack();

    std::stack<Mat4> _modelViewMatrixStack;
    std::stack<Mat4> _projectionMatrixStack;
    std::stack<Mat4> _textureMatrixStack;

    /** @~english Scheduler associated with this director
     * @~chinese ������������
     @since v2.0
     */
    Scheduler *_scheduler;
    
    /** @~english ActionManager associated with this director
     * @~chinese ActionManager������
     @since v2.0
     */
    ActionManager *_actionManager;
    
    /** @~english EventDispatcher associated with this director
     * @~chinese EventDispatcher������
     @since v3.0
     */
    EventDispatcher* _eventDispatcher;
    EventCustom *_eventProjectionChanged, *_eventAfterDraw, *_eventAfterVisit, *_eventBeforeUpdate, *_eventAfterUpdate;
        
    /* @~english delta time since last tick to main loop  @~chinese ��������ȥ�������ѭ��*/
	float _deltaTime;
    
    /* @~english The _openGLView, where everything is rendered, GLView is a abstract class,cocos2d-x provide GLViewImpl
     * @~chinese _openGLView,һ�г���,GLView��һ��������,cocos2d-x�ṩGLViewImpl
     which inherit from it as default renderer context,you can have your own by inherit from it*/
    GLView *_openGLView;

    //texture cache belongs to this director
    TextureCache *_textureCache;

    float _animationInterval;
    float _oldAnimationInterval;

    /* @~english landscape mode ?  @~chinese ����ģʽ?*/
    bool _landscape;
    
    bool _displayStats;
    float _accumDt;
    float _frameRate;
    
    LabelAtlas *_FPSLabel;
    LabelAtlas *_drawnBatchesLabel;
    LabelAtlas *_drawnVerticesLabel;
    
    /** @~english Whether or not the Director is paused  @~chinese �����Ƿ���ͣ*/
    bool _paused;

    /* @~english How many frames were called since the director started  @~chinese ���ݿ�ʼ�����ж���֡����Ϊ*/
    unsigned int _totalFrames;
    float _secondsPerFrame;
    
    /* @~english The running scene  @~chinese ���г���*/
    Scene *_runningScene;
    
    /* @~english will be the next 'runningScene' in the next frame
     * @~chinese ����Ϊ��һ����runningScene����һ�����
     nextScene is a weak reference. */
    Scene *_nextScene;
    
    /* @~english If true, then "old" scene will receive the cleanup message  @~chinese ����������,��ô���ɡ��ĳ������õ��������Ϣ*/
    bool _sendCleanupToScene;

    /* @~english scheduled scenes  @~chinese Ԥ���ĳ���*/
    Vector<Scene*> _scenesStack;
    
    /* @~english last time the main loop was updated  @~chinese ���һ�θ�����ѭ��*/
    struct timeval *_lastUpdate;

    /* @~english whether or not the next delta time will be zero  @~chinese �Ƿ���һ������ʱ�佫����*/
    bool _nextDeltaTimeZero;
    
    /* @~english projection used  @~chinese ͶӰʹ��*/
    Projection _projection;

    /* @~english window size in points  @~chinese ���ڴ�С�ĵ�*/
    Size _winSizeInPoints;
    
    /* @~english content scale factor  @~chinese ���ݱ�������*/
    float _contentScaleFactor;

    /* @~english This object will be visited after the scene. Useful to hook a notification node  @~chinese �ֳ�����Ⱦ����������õĹ�֪ͨ�ڵ�*/
    Node *_notificationNode;

    /* @~english Renderer for the Director  @~chinese ��Ⱦ���ĵ���*/
    Renderer *_renderer;
    
    /* Default FrameBufferObject*/
    experimental::FrameBuffer* _defaultFBO;

    /* @~english Console for the director  @~chinese ����̨�ĵ���*/
    Console *_console;

    bool _isStatusLabelUpdated;

    /* cocos2d thread id */
    std::thread::id _cocos2d_thread_id;

    // GLView will recreate stats labels to fit visible rect
    friend class GLView;
};

// end of base group
/** @~english @}  @~chinese @ }*/

/** 
 @brief @~english DisplayLinkDirector is a Director that synchronizes timers with the refresh rate of the display.
 
 Features and Limitations:
  - Scheduled timers & drawing are synchronizes with the refresh rate of the display
  - Only supports animation intervals of 1/60 1/30 & 1/15
 
 * @~chinese DisplayLinkDirector��һ������,ͬ������ʾ����ˢ���ʼ�ʱ����
 * 
 * ���Ժ�����:
 * ������ʱ��&ͼֽ����ʾ����ˢ��Ƶ��ͬ��
 * ��ֻ֧�ֶ������Ϊ1
 * 
 @since v0.8.2
 */
class DisplayLinkDirector : public Director
{
public:
    DisplayLinkDirector() 
        : _invalid(false)
    {}
    virtual ~DisplayLinkDirector(){}

    //
    // Overrides
    //
    virtual void mainLoop() override;
    virtual void setAnimationInterval(float value) override;
    virtual void startAnimation() override;
    virtual void stopAnimation() override;

protected:
    bool _invalid;
};

NS_CC_END

#endif // __CCDIRECTOR_H__
