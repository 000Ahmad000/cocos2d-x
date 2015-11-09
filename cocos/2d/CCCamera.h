/****************************************************************************
Copyright (c) 2014 Chukong Technologies Inc.

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

 Code based GamePlay3D's Camera: http://gameplay3d.org

 ****************************************************************************/
#ifndef _CCCAMERA_H__
#define _CCCAMERA_H__

#include "2d/CCNode.h"
#include "3d/CCFrustum.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCFrameBuffer.h"

NS_CC_BEGIN

class Scene;
class CameraBackgroundBrush;

/**@~english
 * Note: 
 * Scene creates a default camera. And the default camera mask of Node is 1, therefore it can be seen by the default camera.
 * During rendering the scene, it draws the objects seen by each camera in the added order except default camera. The default camera is the last one being drawn with.
 * It's usually a good idea to render 3D objects in a separate camera.
 * And set the 3d camera flag to CameraFlag::USER1 or anything else except DEFAULT. Dedicate The DEFAULT camera for UI, because it is rendered at last.
 * You can change the camera order to get different result when depth test is not enabled.
 * For each camera, transparent 3d sprite is rendered after opaque 3d sprite and other 2d objects.
 * @~chinese 
 * ע��:
 * ��������һ��Ĭ�ϵ�������ڵ��Ĭ�����������1,��������Ա�Ĭ�ϵ����������
 * ����Ⱦ�����ڼ䣬����Ĭ��������⣬���������ͨ�������˳�����������������л��ƣ�Ĭ�ϵ���������һ�����л��Ƶġ�
 * ���ʹ��һ���������������Ⱦ3d������˵��һ����������⡣
 * ����DEFAULT���⣬����ʹ��CameraFlag::USER1��������ֵ������3d�����ʶ����Ĭ�ϵ��������UI,����Ϊ�������Ⱦ��
 * ����������Ȳ���ʱ����Ըı�����Եõ���ͬ�Ľ����
 * ����ÿһ�����,������Ⱦ�겻͸����3d�����2d�����Ż���Ⱦ͸����3d���顣
 */
enum class CameraFlag
{
    DEFAULT = 1,
    USER1 = 1 << 1,
    USER2 = 1 << 2,
    USER3 = 1 << 3,
    USER4 = 1 << 4,
    USER5 = 1 << 5,
    USER6 = 1 << 6,
    USER7 = 1 << 7,
    USER8 = 1 << 8,
};

/**@~english
* Defines a camera .
 * @~chinese 
 * ������һ�������
*/
class CC_DLL Camera :public Node
{
    friend class Scene;
    friend class Director;
    friend class EventDispatcher;
public:
    /**@~english
    * The type of camera.
     * @~chinese 
     * ��������͡�
    */
    enum class Type
    {
        PERSPECTIVE = 1,
        ORTHOGRAPHIC = 2
    };
public:
    /**@~english
    * Creates a perspective camera.
    *
     * @~chinese 
     * ����һ��͸�������
     * 
    * @param fieldOfView @~english The field of view for the perspective camera (normally in the range of 40-60 degrees).
     * @~chinese ͸������Ŀ��ӽǶ� (һ������40-60��֮��).
    * @param aspectRatio @~english The aspect ratio of the camera (normally the width of the viewport divided by the height of the viewport).
     * @~chinese ����ĳ����(ͨ����ʹ���Ӵ��Ŀ�ȳ����Ӵ��ĸ߶�)��
    * @param nearPlane @~english The near plane distance.
     * @~chinese ��ƽ��ľ��롣
    * @param farPlane @~english The far plane distance.
     * @~chinese Զƽ��ľ��롣
    */
    static Camera* createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    /**@~english
    * Creates an orthographic camera.
    *
     * @~chinese 
     * ����һ�����������
     * 
    * @param zoomX @~english The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).
    * @~chinese ��x�������ͶӰ����������(����ͶӰ�Ŀ��)��
    * @param zoomY @~english The zoom factor along the Y-axis of the orthographic projection (the height of the ortho projection).
    * @~chinese ��y�������ͶӰ����������(����ͶӰ�ĸ߶�)��
    * @param nearPlane @~english The near plane distance.
     * @~chinese ��ƽ��ľ��롣
    * @param farPlane @~english The far plane distance.
     * @~chinese Զƽ��ľ��롣
    */
    static Camera* createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);

    /** @~english create default camera, the camera type depends on Director::getProjection, the depth of the default camera is 0
     * @~chinese ����Ĭ�ϵ����,���������ȡ����Director::getProjection,Ĭ�ϵ���������0*/
    static Camera* create();
    
    /**@~english
    * Gets the type of camera.
    *
     * @~chinese 
     * �õ���������͡�
     * 
    * @return @~english The camera type.
     * @~chinese ��������͡�
    */
    Camera::Type getType() const { return _type; }

    /**@~english get & set Camera flag @~chinese ��ȡ�����������ʶ*/
    CameraFlag getCameraFlag() const { return (CameraFlag)_cameraFlag; }
    void setCameraFlag(CameraFlag flag) { _cameraFlag = (unsigned short)flag; }

    /**@~english
    * Make Camera looks at target
    *
     * @~chinese 
     * ʹ�������Ŀ��
     * 
    * @param target @~english The target camera is point at
     * @~chinese Ŀ���λ��
    * @param up @~english The up vector, usually it's Y axis
     * @~chinese ������ϵ�����,ͨ������Y��
    */
    virtual void lookAt(const Vec3& target, const Vec3& up = Vec3::UNIT_Y);

    /**@~english
    * Gets the camera's projection matrix.
    *
     * @~chinese 
     * ��ȡ�����ͶӰ����
     * 
    * @return @~english The camera projection matrix.
     * @~chinese ���ͶӰ����
    */
    const Mat4& getProjectionMatrix() const;
    /**@~english
    * Gets the camera's view matrix.
    *
     * @~chinese 
     * ��ȡ�������ͼ����
     * 
    * @return @~english The camera view matrix.
     * @~chinese �����ͼ����
    */
    const Mat4& getViewMatrix() const;

    /**@~english get view projection matrix @~chinese �õ���ͼͶӰ����*/
    const Mat4& getViewProjectionMatrix() const;
    
    /** @~english convert the specified point of viewport from world-space coordinates into the screen-space coordinates.
     * Origin point at left top corner in screen-space.
     * @~chinese ��ָ����������������ת��Ϊ��Ļ���ꡣ
     * ԭ����GL��Ļ����ϵ�����½ǡ�
     * @param src @~english The world-space position.
     * @~chinese �����λ�á�
     * @return @~english The screen-space position.
     * @~chinese ��Ļ��λ�á�
     */
    Vec2 project(const Vec3& src) const;
    
    /**@~english
     * Convert the specified point of viewport from screen-space coordinate into the world-space coordinate.
     * Origin point at left top corner in screen-space.
     * @~chinese 
     * ��ָ����������Ļ����ת��Ϊ�������ꡣ
     * ԭ����GL��Ļ����ϵ�����½ǡ�
     * @param src @~english The screen-space position.
     * @~chinese ��Ļ��λ�á�
     * @return @~english The world-space position.
     * @~chinese �����λ�á�
     */
    Vec3 unproject(const Vec3& src) const;
    
    /** @~english convert the specified point in 3D world-space coordinates into the GL-screen-space coordinates.
     * Origin point at left bottom corner in GL-screen-space.
     * @~chinese ��ָ��������3D��������ת��Ϊ��Ļ���ꡣ
     * ԭ����GL��Ļ����ϵ�����½ǡ�
     * @param src @~english The 3D world-space position.
     * @~chinese 3D�����λ�á�
     * @return @~english The GL-screen-space position.
     * @~chinese GL��Ļ�ռ��λ�á�
     */
    Vec2 projectGL(const Vec3& src) const;
    
    /**@~english
     * Convert the specified point of GL-screen-space coordinate into the 3D world-space coordinate.
     * Origin point at left bottom corner in GL-screen-space.
     * @~chinese 
     * ��ָ����������Ļ����ת��Ϊ3D�������ꡣ
     * ԭ����GL��Ļ����ϵ�����½ǡ�
     * @param src @~english The GL-screen-space position.
     * @~chinese GL��Ļ�ռ��λ�á�
     * @return @~english The 3D world-space position.
     * @~chinese 3D�����λ�á�
     */
    Vec3 unprojectGL(const Vec3& src) const;

    /**@~english
     * Convert the specified point of viewport from screen-space coordinate into the world-space coordinate.
     * Origin point at left bottom corner in GL-screen-space.
     * @~chinese 
     * ��ָ����������Ļ����ת��Ϊ�������ꡣ
     * ԭ����GL��Ļ����ϵ�����½ǡ�
     *
     * @param size @~english The viewport size to use.
     * @~chinese ʹ�õ��Ӵ���С��
     * @param src @~english The screen-space position.
     * @~chinese ��Ļ��λ�á�
     * @param dst @~english The world-space position.
     * @~chinese �����λ�á�
     */
    void unproject(const Size& size, const Vec3* src, Vec3* dst) const;

    /**@~english
     * Convert the specified point of GL-screen-space coordinate into the 3D world-space coordinate.
     * Origin point at left bottom corner in GL-screen-space.
     * @~chinese 
     * ��ָ����������Ļ����ת��Ϊ3D�������ꡣ
     * ԭ����GL��Ļ����ϵ�����½ǡ�
     * @param size @~english The window size to use.
     * @~chinese ʹ�õĴ��ڴ�С��
     * @param src  @~english The GL-screen-space position.
     * @~chinese GL��Ļ�ռ��λ�á�
     * @param dst  @~english The 3D world-space position.
     * @~chinese 3D�����λ�á�
     */
    void unprojectGL(const Size& size, const Vec3* src, Vec3* dst) const;

    /**
     * Is this aabb visible in frustum
     * @~chinese 
     * aabb����׵�����Ƿ�ɼ�
     */
    bool isVisibleInFrustum(const AABB* aabb) const;
    
    /**@~english
     * Get object depth towards camera
     * @~chinese 
     * ��ȡ����������������
     */
    float getDepthInView(const Mat4& transform) const;
    
    /**@~english
     * set depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with CameraFlag::DEFAULT is 0, user defined camera is -1 by default
     * @~chinese
     * ������ȣ�������С�ģ���Ƚϴ�����������ڶ��ˣ���ʶ��CameraFlag::DEFAULT����������0���û������������Ĭ��Ϊ-1
     */
    void setDepth(int8_t depth);
    
    /**@~english
     * get depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with CameraFlag::DEFAULT is 0, user defined camera is -1 by default
     * @~chinese 
     * ��ȡ��ȣ�������С�ģ���Ƚϴ�����������ڶ��ˣ���ʶ��CameraFlag::DEFAULT����������0���û������������Ĭ��Ϊ-1
     */
    int8_t getDepth() const { return _depth; }
    
    /**
     get rendered order
     */
    int getRenderOrder() const;
    
    /**@~english
     * Get the frustum's far plane.
     * @~chinese 
     * ��ȡ��׵��Զƽ�档
     */
    float getFarPlane() const { return _farPlane; }

    /**@~english
     * Get the frustum's near plane.
     * @~chinese 
     * ��ȡ��׵���ƽ�档
     */
    float getNearPlane() const { return _nearPlane; }
    
    //override
    virtual void onEnter() override;
    virtual void onExit() override;

    /**@~english
     * Get the visiting camera , the visiting camera shall be set on Scene::render
     * @~chinese 
     * ��ȡ���Ƶ����,���Ƶ��������Scene::render�����á�
     */
    static const Camera* getVisitingCamera() { return _visitingCamera; }

    /**@~english
     * Get the default camera of the current running scene.
     * @~chinese 
     * ��ȡ����ǰ���г�����Ĭ�������
     */
    static Camera* getDefaultCamera();
    /**
     Before rendering scene with this camera, the background need to be cleared. It clears the depth buffer with max depth by default. Use setBackgroundBrush to modify the default behavior
     */
    void clearBackground();
    /**
     Apply the FBO, RenderTargets and viewport.
     */
    void apply();
    /**
     Set FBO, which will attach several render target for the rendered result.
    */
    void setFrameBufferObject(experimental::FrameBuffer* fbo);
    /**
     Set Viewport for camera.
     */
    void setViewport(const experimental::Viewport& vp) { _viewport = vp; }
    
    /**
     * Whether or not the viewprojection matrix was updated since the last frame.
     * @return True if the viewprojection matrix was updated since the last frame.
     */
    bool isViewProjectionUpdated() const {return _viewProjectionUpdated;}
    
    /**
     * set the background brush. See CameraBackgroundBrush for more information.
     * @param clearBrush Brush used to clear the background
     */
    void setBackgroundBrush(CameraBackgroundBrush* clearBrush);
    
    /**
     * Get clear brush
     */
    CameraBackgroundBrush* getBackgroundBrush() const { return _clearBrush; }
    
    virtual void visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
CC_CONSTRUCTOR_ACCESS:
    Camera();
    ~Camera();
    
    /**@~english
     * Set the scene,this method should not be invoke manually
     * @~chinese 
     * ���ó���,���������Ӧ���ֶ�����
     */
    void setScene(Scene* scene);
    
    /**@~english set additional matrix for the projection matrix, it multiplys mat to projection matrix when called, used by WP8
     * @~chinese ��ͶӰ�������ö���ľ���,��WP8ƽ̨ʹ��ʱ�����õ�ʱ���������ͶӰ����*/
    void setAdditionalProjection(const Mat4& mat);
    
    /** @~english init camera  @~chinese ��ʼ�����*/
    bool initDefault();
    bool initPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    bool initOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);
    void applyFrameBufferObject();
    void applyViewport();
protected:

    Scene* _scene; //Scene camera belongs to
    Mat4 _projection;
    mutable Mat4 _view;
    mutable Mat4 _viewInv;
    mutable Mat4 _viewProjection;
    Vec3 _up;
    Camera::Type _type;
    float _fieldOfView;
    float _zoom[2];
    float _aspectRatio;
    float _nearPlane;
    float _farPlane;
    mutable bool  _viewProjectionDirty;
    bool _viewProjectionUpdated; //Whether or not the viewprojection matrix was updated since the last frame.
    unsigned short _cameraFlag; // camera flag
    mutable Frustum _frustum;   // camera frustum
    mutable bool _frustumDirty;
    int8_t  _depth;                 //camera depth, the depth of camera with CameraFlag::DEFAULT flag is 0 by default, a camera with larger depth is drawn on top of camera with smaller depth
    static Camera* _visitingCamera;
    
    CameraBackgroundBrush* _clearBrush; //brush used to clear the back ground
    
    experimental::Viewport _viewport;
    
    experimental::FrameBuffer* _fbo;
protected:
    static experimental::Viewport _defaultViewport;
public:
    static const experimental::Viewport& getDefaultViewport() { return _defaultViewport; }
    static void setDefaultViewport(const experimental::Viewport& vp) { _defaultViewport = vp; }
};

NS_CC_END

#endif// __CCCAMERA_H_
