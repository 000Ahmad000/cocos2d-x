/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
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

#ifndef __CCPHYSICS_WORLD_H__
#define __CCPHYSICS_WORLD_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include <list>
#include "base/CCVector.h"
#include "math/CCGeometry.h"
#include "physics/CCPhysicsBody.h"

struct cpSpace;

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsShape;
class PhysicsContact;

class Director;
class Node;
class Sprite;
class Scene;
class DrawNode;
class PhysicsDebugDraw;
class EventDispatcher;

class PhysicsWorld;

typedef struct PhysicsRayCastInfo
{
    PhysicsShape* shape;
    Vec2 start;
    Vec2 end;              //< in lua, it's name is "ended"
    Vec2 contact;
    Vec2 normal;
    float fraction;
    void* data;
}PhysicsRayCastInfo;

typedef std::function<bool(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)> PhysicsRayCastCallbackFunc;
typedef std::function<bool(PhysicsWorld&, PhysicsShape&, void*)> PhysicsQueryRectCallbackFunc;
typedef PhysicsQueryRectCallbackFunc PhysicsQueryPointCallbackFunc;

/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_2d
 * @{
 */

/**
 * @class PhysicsWorld CCPhysicsWorld.h
 * @brief @~english An PhysicsWorld object simulates collisions and other physical properties. You do not create PhysicsWorld objects directly; instead, you can get it from an Scene object.
 * @~chinese һ��PhysicsWorld����,����ģ��������ײ������������Ϊ���㲻��Ҫֱ�Ӵ���PhysicsWorld����;�෴,����Դ�һ�����������ȡ����
 */
class CC_DLL PhysicsWorld
{
public:
    static const int DEBUGDRAW_NONE;        ///< draw nothing
    static const int DEBUGDRAW_SHAPE;       ///< draw shapes
    static const int DEBUGDRAW_JOINT;       ///< draw joints
    static const int DEBUGDRAW_CONTACT;     ///< draw contact
    static const int DEBUGDRAW_ALL;         ///< draw all
    
public:
    /**@~english
     * Adds a joint to this physics world.
     *
     * This joint will be added to this physics world at next frame.
     * @~chinese 
     * ���һ���ؽڵ����������С�
     * 
     * ����ؽڽ�����һ��֡����ӵ����������С�
     * @attention @~english If this joint is already added to another physics world, it will be removed from that world first and then add to this world.
     * @~chinese �������ؽ��Ѿ���ӵ���һ����������,�������ȴ��Ǹ���������ɾ��,Ȼ������ӵ�����������硣
     * @param   joint   @~english A pointer to an existing PhysicsJoint object.
     * @~chinese һ��ָ������PhysicsJoint�����ָ��
     */
    virtual void addJoint(PhysicsJoint* joint);

    /**@~english
     * Remove a joint from this physics world.
     *
     * If this world is not locked, the joint is removed immediately, otherwise at next frame.
     * If this joint is connected with a body, it will be removed from the body also.
     * @~chinese 
     * �ѹؽڴ�����������ɾ����
     * 
     * �����������û�б���ס,��ô�˹ؽڻᱻ����ɾ��,����ȵ���һ֡��ɾ����
     * �������ؽ���һ��������������һ��,��ô��Ҳ���Ӹ�����ɾ��.
     * @param   joint   @~english A pointer to an existing PhysicsJoint object.
     * @~chinese һ�����е�PhysicsJoint�����ָ�롣
     * @param   destroy   @~english true this joint will be destroyed after remove from this world, false otherwise.
     * @~chinese True��ζ�Źؽڴ����������Ƴ��Ժ�ᱻ���٣�False���ʾ�����������Ƴ��󲢲������١�
     */
    virtual void removeJoint(PhysicsJoint* joint, bool destroy = true);

    /**@~english
     * Remove all joints from this physics world.
     *
     * @~chinese 
     * ����������ɾ�����йؽڡ�
     * 
     * @attention @~english This function is invoked in the destructor of this physics world, you do not use this api in common.
     * @~chinese �������������������������ʱ�򱻵���,һ��������㲻Ҫֱ��ʹ�����API��
     * @param   destroy   @~english true all joints will be destroyed after remove from this world, false otherwise.
     * @~chinese ��Ture����ζ�ŵ��ؽڴ���������ɾ�������Ƕ��ᱻ����,False���ʾ���ᱻ���١�
     */
    virtual void removeAllJoints(bool destroy = true);
    
    /**@~english
     * Remove a body from this physics world.
     *
     * If this world is not locked, the body is removed immediately, otherwise at next frame.
     * @~chinese 
     * �����������Ƴ�һ�����塣
     * 
     * �����������û����ס,����屻����ɾ��,����ȵ���һ֡��ɾ����
     * @attention @~english If this body has joints, those joints will be removed also.
     * @~chinese ��������������ؽ�,��ô��Щ�ؽ�Ҳ����ɾ����
     * @param   body   @~english A pointer to an existing PhysicsBody object.
     * @~chinese һ�����е�PhysicsBody�����ָ�롣
     */
    virtual void removeBody(PhysicsBody* body);
    
    /**@~english
     * Remove body by tag.
     *
     * If this world is not locked, the object is removed immediately, otherwise at next frame.
     * @~chinese 
     * ʹ��һ��tag���Ƴ�һ�����塣
     * 
     * �����������û�м���,������������ɾ��,���������һ֡��ɾ����
     * @attention @~english If this body has joints, those joints will be removed also.
     * @~chinese ��������������ؽ�,��ô��Щ�ؽ�Ҳ����ɾ����
     * @param   tag   @~english An interger number that identifies a PhysicsBody object.
     * @~chinese һ��������������ʶһ�� PhysicsBody����
     */
    virtual void removeBody(int tag);

    /**@~english
     * Remove all bodies from physics world.
     *
     * If this world is not locked, those body are removed immediately, otherwise at next frame.
     * @~chinese 
     * ɾ�����������е����еĸ��塣
     * 
     * �����������û�м���,��ô��Щ����ᱻ����ɾ��,����ȵ���һ֡��ɾ����
     */
    virtual void removeAllBodies();
    
    /**@~english
     * Searches for physics shapes that intersects the ray.
     *
     * Query this physics world along the line segment from start to end.
     * @~chinese 
     * �����������ཻ��������״��
     * 
     * �������ߵ�ʼ����յ㣬��ѯ��ǰ������������������ཻ��������״��
     * @param   func   @~english Func is called for each shape found.
     * @~chinese ÿ���ҵ�һ��������������״��ʱ�򣬸ú����ͻᱻ���á�
     * @param   start   @~english A Vec2 object contains the begin position of the ray.
     * @~chinese Vec2����,�������ߵ�ʼ��λ��
     * @param   end   @~english A Vec2 object contains the end position of the ray.
     * @~chinese Vec2����,�������ߵ��յ�λ��
     * @param   data   @~english User defined data, it is passed to func.
     * @~chinese �û����������,���������ص�������
     */
    void rayCast(PhysicsRayCastCallbackFunc func, const Vec2& start, const Vec2& end, void* data);
    
    /**@~english
     * Searches for physics shapes that contains in the rect.
     *
     * Query this physics world to find all shapes overlap rect.
     * @~chinese 
     * ��ѯ�����ھ����ڵ�������״��
     * 
     * ��ѯ����������������þ����н�����������״��
     * @param   func   @~english Func is called for each shape whose bounding box overlaps rect.
     * @~chinese ÿ���ҵ�һ��������������״��ʱ�򣬸ú����ͻᱻ����
     * @param   rect   @~english A Rect object contains a rectangle's x, y, width and height.
     * @~chinese һ�������������һ������ʼ��Ϳ����ɵĽṹ�塣
     * @param   data   @~english User defined data, it is passed to func.
     * @~chinese �û����������,���������ص�������
     */
    void queryRect(PhysicsQueryRectCallbackFunc func, const Rect& rect, void* data);
    
    /**@~english
     * Searches for physics shapes that contains the point.
     *
     * @~chinese 
     * ��ѯ����ָ������������е�������״��
     * 
     * @attention @~english The point must lie inside a shape.
     * @~chinese ����������һ����״�ڡ�
     * @param   func   @~english Func is called for each shape contains the point.
     * @~chinese ÿ���ҵ�һ�����������ĵ��ʱ�򣬸ú����ͻᱻ����
     * @param   point   @~english A Vec2 object contains the position of the point.
     * @~chinese һ��Vec2����
     * @param   data   @~english User defined data, it is passed to func.
     * @~chinese �û����������,���������ص�������
     */
    void queryPoint(PhysicsQueryPointCallbackFunc func, const Vec2& point, void* data);
    
    /**@~english
     * Get phsyics shapes that contains the point.
     *
     * All shapes contains the point will be pushed in a Vector<PhysicsShape*> object.
     * @~chinese 
     * ��ѯָ���������ϵ����е�������״��
     * 
     * ���а����˵��������״�ᱻ��ӵ�һ��Vector<PhysicsShape*>������ȥ��
     * @attention @~english The point must lie inside a shape.
     * @~chinese ����������һ��������״�ڡ�
     * @param   point   @~english A Vec2 object contains the position of the point.
     * @~chinese һ��Vec2����
     * @return @~english A Vector<PhysicsShape*> object contains all found PhysicsShape pointer.
     * @~chinese һ��Vector<PhysicsShape *>����,�����������ҵ���PhysicsShapeָ�롣
     */
    Vector<PhysicsShape*> getShapes(const Vec2& point) const;
    
    /**@~english
     * Get the nearest phsyics shape that contains the point.
     *
     * Query this physics world at point and return the closest shape.
     * @~chinese 
     * ��ȡ����ָ�������������������״��
     * 
     * ��ѯ���������а���ָ��������������������״��
     * @param   point   @~english A Vec2 object contains the position of the point.
     * @~chinese һ��Vec2����
     * @return @~english A PhysicsShape object pointer or nullptr if no shapes were found
     * @~chinese һ��PhysicsShape����ָ��; ���ߣ����û���ҵ�����������������״���򷵻�nullptr��
     */
    PhysicsShape* getShape(const Vec2& point) const;

    /**@~english
     * Get all the bodys that in this physics world.
     *
     * @~chinese 
     * ��ȡ�������������еĸ��塣
     * 
     * @return @~english A Vector<PhysicsBody*>& object contains all bodies in this physics world.
     * @~chinese һ��<PhysicsBody *>��������,�������������������еĸ��塣
     */
    const Vector<PhysicsBody*>& getAllBodies() const;

    /**@~english
     * Get a body by tag.
     *
     * @~chinese 
     * ͨ��һ��tag����ȡһ�����塣
     * 
     * @param   tag   @~english An interger number that identifies a PhysicsBody object.
     * @~chinese һ��������ʶ��
     * @return @~english A PhysicsBody object pointer or nullptr if no shapes were found.
     * @~chinese һ��PhysicsBody����ָ���nullptr
     */
    PhysicsBody* getBody(int tag) const;
    
    /**@~english
     * Get a scene contain this physics world.
     *
     * @~chinese 
     * ��ȡ������������ĳ�������
     * 
     * @attention @~english This value is initialized in constructor
     * @~chinese ���ֵ���ڹ��캯���г�ʼ����
     * @return @~english A Scene object reference.
     * @~chinese һ�������������á�
     */
    inline Scene& getScene() const { return *_scene; }
    
    /**@~english
     * Get the gravity value of this physics world.
     *
     * @~chinese 
     * ��ȡ�������������ֵ��
     * 
     * @return @~english A Vect object.
     * @~chinese һ��Vect���� @see Vec2
     */
    inline Vec2 getGravity() const { return _gravity; }
    
    /**@~english
     * set the gravity value of this physics world.
     *
     * @~chinese 
     * �����������������ֵ��
     * 
     * @param gravity @~english A gravity value of this physics world.
     * @~chinese �������������ֵ��
     */
    void setGravity(const Vec2& gravity);
    
    /**@~english
     * Set the speed of this physics world.
     *
     * @~chinese 
     * ������������ķ���ִ���ٶȡ�
     * 
     * @attention @~english if you setAutoStep(false), this won't work.
     * @~chinese ���setAutoStep(false),��ô����������������á�
     * @param speed  @~english A float number. Speed is the rate at which the simulation executes. default value is 1.0.
     * @~chinese һ�����������ٶ�ָ������������ִ���ٶȡ�Ĭ��ַ��1.0
     */
    inline void setSpeed(float speed) { if(speed >= 0.0f) { _speed = speed; } }
    
    /**@~english
     * Get the speed of this physics world.
     *
     * @~chinese 
     * �õ������������ִ���ٶ�
     * 
     * @return @~english A float number.
     * @~chinese һ��������
     */
    inline float getSpeed() { return _speed; }
    
    /**@~english
     * Set the update rate of this physics world
     * 
     * Update rate is the value of EngineUpdateTimes/PhysicsWorldUpdateTimes.
     * Set it higher can improve performance, set it lower can improve accuracy of physics world simulation.
     * @~chinese 
     * ������������ĸ�������
     * 
     * �������ʵ���EngineUpdateTimes/PhysicsWorldUpdateTimes
     * ���õ�ֵԽ�ߣ�Խ�����������,�������ͣ�����������������ķ��澫�ȡ�
     * @attention @~english if you setAutoStep(false), this won't work.
     * @~chinese ���������setAutoStep(false),��ô�ú����������á�
     * @param rate @~english An interger number, default value is 1.0.
     * @~chinese interger����,Ĭ��ֵ��1.0
     */
    inline void setUpdateRate(int rate) { if(rate > 0) { _updateRate = rate; } }


    /**@~english
     * Get the update rate of this physics world.
     *
     * @~chinese 
     * ��ȡ��������ĸ������ʡ�
     * 
     * @return @~english An interger number.
     * @~chinese һ��interger�����֡�
     */
    inline int getUpdateRate() { return _updateRate; }

    /**@~english
     * set the number of substeps in an update of the physics world.
     * 
     * One physics update will be divided into several substeps to increase its accuracy.
     * @~chinese 
     * ���ø�������������Ӳ����������
     * 
     * һ��������½�����Ϊ�����Ӳ���,���������������׼ȷ�ԡ�
     * @param steps @~english An interger number, default value is 1.
     * @~chinese һ��interger������,Ĭ��ֵ��1��
     */
    void setSubsteps(int steps);

    /**@~english
     * Get the number of substeps of this physics world.
     *
     * @~chinese 
     * ��ȡ����������Ӳ����������
     * 
     * @return @~english An interger number.
     * @~chinese һ��interger�����֡�
     */
    inline int getSubsteps() const { return _substeps; }

    /**@~english
     * Set the debug draw mask of this physics world.
     *
     * This physics world will draw shapes and joints by DrawNode acoording to mask.
     * @~chinese 
     * ������������ĵ��Ի�������
     * 
     * ���������������úõĵ��Ի������룬����DrawNode������������״������ؽڡ�
     * @param mask @~english Mask has four value:DEBUGDRAW_NONE, DEBUGDRAW_SHAPE, DEBUGDRAW_JOINT, DEBUGDRAW_CONTACT and DEBUGDRAW_ALL, default is DEBUGDRAW_NONE
     * @~chinese ����������4��ȡֵ: DEBUGDRAW_NONE DEBUGDRAW_SHAPE, DEBUGDRAW_JOINT, DEBUGDRAW_CONTACT and DEBUGDRAW_ALL, default is DEBUGDRAW_NONE
     */
    void setDebugDrawMask(int mask);

    /**@~english
     * Get the bebug draw mask.
     *
     * @~chinese 
     * ��ѯ���Ի������롣
     * 
     * @return @~english An interger number.
     * @~chinese һ��interger�����֡�
     */
    inline int getDebugDrawMask() { return _debugDrawMask; }
    
    /**@~english
     * To control the step of physics.
     *
     * If you want control it by yourself( fixed-timestep for example ), you can set this to false and call step by yourself.
     * @~chinese 
     * ������������ķ���
     * 
     * �������Ҫ�Լ����������������,����ʹ�ù̶�ʱ�䲽��(fixed-timestep)�ĵ�������,����Դ�False.
     * @attention @~english If you set auto step to false, setSpeed setSubsteps and setUpdateRate won't work, you need to control the time step by yourself.
     * @~chinese ���������False�Ļ�����ô`setSpeed`��`setSubsteps`,�Լ�`setUpdateRate`�������������������ˣ�������Щ��Ϊ�㶼�����Լ������ơ�
     * @param autoStep @~english A bool object, defaut value is true.
     * @~chinese һ��bool����,Ĭ��ֵΪTrue.
     */
    void setAutoStep(bool autoStep){ _autoStep = autoStep; }


    /**@~english
     * Get the auto step of this physics world.
     *
     * @~chinese 
     * ��ȡ���������Ƿ�ʹ���Զ�����������
     * 
     * @return @~english A bool object.
     * @~chinese һ��bool����
     */
    bool isAutoStep() { return _autoStep; }

    /**@~english
     * The step for physics world.
     *
     * The times passing for simulate the physics.
     * @~chinese 
     * ��������ĵ���������
     * 
     * ����һ��ģ����������Ҫ��ʱ�䡣
     * @attention @~english You need to setAutoStep(false) first before it can work.
     * @~chinese �����������Чǰ������Ҫ����setAutoStep(false)��
     * @param   delta   @~english A float number.
     * @~chinese һ��������
     */
    void step(float delta);
    
protected:
    static PhysicsWorld* construct(Scene* scene);
    bool init();
    
    
    virtual void addBody(PhysicsBody* body);
    virtual void addShape(PhysicsShape* shape);
    virtual void removeShape(PhysicsShape* shape);
    virtual void update(float delta, bool userCall = false);
    
    virtual void debugDraw();
    
    virtual int collisionBeginCallback(PhysicsContact& contact);
    virtual int collisionPreSolveCallback(PhysicsContact& contact);
    virtual void collisionPostSolveCallback(PhysicsContact& contact);
    virtual void collisionSeparateCallback(PhysicsContact& contact);
    
    virtual void doAddBody(PhysicsBody* body);
    virtual void doRemoveBody(PhysicsBody* body);
    virtual void doRemoveJoint(PhysicsJoint* joint);
    virtual void addBodyOrDelay(PhysicsBody* body);
    virtual void removeBodyOrDelay(PhysicsBody* body);
    virtual void updateBodies();
    virtual void updateJoints();
    
protected:
    Vec2 _gravity;
    float _speed;
    int _updateRate;
    int _updateRateCount;
    float _updateTime;
    int _substeps;
    cpSpace* _cpSpace;
    
    bool _updateBodyTransform;
    Vector<PhysicsBody*> _bodies;
    std::list<PhysicsJoint*> _joints;
    Scene* _scene;
    
    bool _autoStep;
    PhysicsDebugDraw* _debugDraw;
    int _debugDrawMask;
    
    EventDispatcher* _eventDispatcher;

    Vector<PhysicsBody*> _delayAddBodies;
    Vector<PhysicsBody*> _delayRemoveBodies;
    std::vector<PhysicsJoint*> _delayAddJoints;
    std::vector<PhysicsJoint*> _delayRemoveJoints;
    
protected:
    PhysicsWorld();
    virtual ~PhysicsWorld();
    
    void beforeSimulation(Node *node, const Mat4& parentToWorldTransform, float nodeParentScaleX, float nodeParentScaleY, float parentRotation);
    void afterSimulation(Node* node, const Mat4& parentToWorldTransform, float parentRotation);

    friend class Node;
    friend class Sprite;
    friend class Scene;
    friend class Director;
    friend class PhysicsBody;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class PhysicsWorldCallback;
    friend class PhysicsDebugDraw;
};

/** @~english A physics helper class. Draw physics shape, joint in debug mode. 
 *  You do not create PhysicsDebugDraw objects directly; Instead, you can activate it by PhysicsWorld::setDebugDrawMask.
 * @~chinese һ������ĸ����ࡣ�������ڵ���״̬�»�����״�͹ؽڡ�
 * �㲻��Ҫֱ�Ӵ���һ�� PhysicsDebugDraw���� �����ͨ������ `PhysicsWorld::setDebugDrawMask`�����������ö���
 */
class CC_DLL PhysicsDebugDraw
{
protected:
    virtual bool begin();
    virtual void end();
    virtual void drawShape(PhysicsShape& shape);
    virtual void drawJoint(PhysicsJoint& joint);
    virtual void drawContact();
    
protected:
    PhysicsDebugDraw(PhysicsWorld& world);
    virtual ~PhysicsDebugDraw();
    
protected:
    DrawNode* _drawNode;
    PhysicsWorld& _world;
    
    friend class PhysicsWorld;
};
extern const float CC_DLL PHYSICS_INFINITY;

/** @} */
/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_WORLD_H__
