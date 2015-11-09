/**************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#ifndef __PHYSICS_3D_SHAPE_H__
#define __PHYSICS_3D_SHAPE_H__

#include "base/CCRef.h"
#include "base/ccConfig.h"
#include "math/CCMath.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

class btCollisionShape;

NS_CC_BEGIN
/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_3d
 * @{
*/

/**
    @brief @~english Create a physical shape(box, sphere, cylinder, capsule, convexhull, mesh and heightfield)
    @~chinese ����һ��������״���У����棬���棬���Ҽ���͹������������heightfield ��
*/
class CC_DLL Physics3DShape : public Ref
{
public:
    enum class ShapeType
    {
        UNKNOWN = 0,
        BOX,
        SPHERE,
        CYLINDER,
        CAPSULE,
        CONVEX,
        MESH,
        HEIGHT_FIELD,
        COMPOUND
    };

    /** @~english get shape type
        @~chinese �õ�����״����
    */
    virtual ShapeType getShapeType() const;

    /** @~english create box shape
        @~chinese ����������״
        @param extent @~english  The extent of sphere. @~chinese ����ĳ̶ȡ�
    */
    static Physics3DShape* createBox(const cocos2d::Vec3& extent);

    /** @~english create sphere shape
        @~chinese ����������״
        @param radius @~english  The radius of sphere. @~chinese ��뾶��
    */
    static Physics3DShape* createSphere(float radius);

    /** @~english create cylinder shape
        @~chinese ����Բ����
        @param radius @~english  The radius of cylinder. @~chinese Բ����İ뾶��
        @param height @~english  The height. @~chinese �߶ȡ�
    */
    static Physics3DShape* createCylinder(float radius, float height);

    /** @~english create capsule shape
        @~chinese �������ҵ���״
        @param radius @~english  The radius of casule. @~chinese �Խ��ҵİ뾶��
        @param height @~english  The height (cylinder part). @~chinese �߶ȣ�Ͳ����
    */
    static Physics3DShape* createCapsule(float radius, float height);

    /** @~english create convex hull
        @~chinese ����͹��
        @param points @~english  The vertices of convex hull @~chinese ͹�ǵĶ���
        @param numPoints @~english  The number of vertices. @~chinese ���������
    */
    static Physics3DShape* createConvexHull(const cocos2d::Vec3* points, int numPoints);

    /** @~english create mesh
        @~chinese ��������
        @param triangles @~english  The pointer of triangle list @~chinese �������б��ָ��
        @param numTriangles @~english  The number of triangles. @~chinese ����������

    */
    static Physics3DShape* createMesh(const cocos2d::Vec3* triangles, int numTriangles);

    /** @~english create heightfield
        @~chinese ��������
        @param heightStickWidth @~english  The Width of heightfield @~chinese �Ե��εĿ��
        @param heightStickLength @~english  The Length of heightfield. @~chinese �Ե��εĳ��ȡ�
        @param heightfieldData @~english  The Data of heightfield. @~chinese �Ե������ݡ�
        @param heightScale @~english  heightScale��. @~chinese heightScale��
        @param minHeight @~english  The minHeight of heightfield. @~chinese �Ե��ε�minheight��
        @param maxHeight @~english  The maxHeight of heightfield. @~chinese �Ե��ε����߶ȡ�
        @param useFloatDatam @~english  useFloatDatam @~chinese useFloatDatam
        @param flipQuadEdges @~english  if flip QuadEdges @~chinese ���quadedges��ת
        @param useDiamondSubdivision @~english  useDiamondSubdivision @~chinese useDiamondSubdivision

    */
    static Physics3DShape* createHeightfield(int heightStickWidth,int heightStickLength
            , const void* heightfieldData, float heightScale
            , float minHeight, float maxHeight
            , bool useFloatDatam, bool flipQuadEdges, bool useDiamondSubdivision = false);

    /** @~english create Compound Shape
        @~chinese ����������״
        @param shapes @~english  The list of child shape @~chinese ��ͯ��״�б�
    */
    static Physics3DShape* createCompoundShape(const std::vector<std::pair<Physics3DShape*, Mat4>>& shapes);


#if CC_ENABLE_BULLET_INTEGRATION
    btCollisionShape* getbtShape() const
    {
        return _btShape;
    }
#endif
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DShape();
    ~Physics3DShape();

    bool initBox(const cocos2d::Vec3& ext);
    bool initSphere(float radius);
    bool initCylinder(float radius, float height);
    bool initCapsule(float radius, float height);
    bool initConvexHull(const cocos2d::Vec3* points, int numPoints);
    bool initMesh(const cocos2d::Vec3* triangles, int numTriangles);
    bool initHeightfield(int heightStickWidth,int heightStickLength
        , const void* heightfieldData, float heightScale
        , float minHeight, float maxHeight
        , bool useFloatDatam, bool flipQuadEdges
        , bool useDiamondSubdivision);
    bool initCompoundShape(const std::vector<std::pair<Physics3DShape *, Mat4>> &shapes);
    
protected:
    ShapeType _shapeType; //shape type

#if (CC_ENABLE_BULLET_INTEGRATION)
    btCollisionShape*  _btShape;
    unsigned char* _heightfieldData;
    std::vector<Physics3DShape*> _compoundChildShapes;
#endif
};

// end of physics_3d group
/// @}
// end of physics group
/// @}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_SHAPE_H__
