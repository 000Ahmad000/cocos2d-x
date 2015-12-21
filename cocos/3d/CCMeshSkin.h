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
 ****************************************************************************/

#ifndef __CCMESHSKIN_H__
#define __CCMESHSKIN_H__

#include "3d/CCBundle3DData.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "math/CCMath.h"


NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

class Bone3D;
class Skeleton3D;

/**
 * @class MeshSkin
 * @brief @~english MeshSkin, A class maintain a collection of bones that affect Mesh vertex.
 * And it is responsible for computing matrix palettes that used by skin mesh rendering.
 * @~chinese MeshSkin��������һϵ����Ƥ�����ļ��ϣ�����Ϊ������Ƥ��Ⱦ��������������
 * @js NA
 * @lua NA
 */
class CC_DLL MeshSkin: public Ref
{
    friend class Mesh;
public:
    
    /**
     * @~english Create a new meshskin if do not want to share meshskin
     * @param skeleton @~english The specified skeleton.
     */
    static MeshSkin* create(Skeleton3D* skeleton, const std::string& filename, const std::string& name);
    
    /**
     * @~english Create a new meshskin if do not want to share meshskin
     * @~chinese ͨ���ǹ���ʽ����һ��MeshSkin����
     * @param skeleton @~english The specified skeleton.
     * @~chinese ָ����Skeleton3D����
     * @param boneNames @~english The bones names list.
     * @~chinese ������������
     * @param invBindPose @~english The bones' inverse binding pose.
     * @~chinese �����İ���̬�����
     * @return @~english The meshSkin object.
     * @~chinese ��������MeshSkin����
     */
    static MeshSkin* create(Skeleton3D* skeleton, const std::vector<std::string>& boneNames, const std::vector<Mat4>& invBindPose);
    
    /**
     * @~english Get total bone count. (skin bone + node bone)
     * @~chinese ��ȡ���й�������������Ƥ������ڵ����
     * @return @~english The bone count.
     * @~chinese ������
     */
    ssize_t getBoneCount() const;
    
    /**
     * @~english Get the specified bone by index.
     * @~chinese ͨ��������ȡ����
     * @param index @~english The index.
     * @~chinese ��������
     * @return @~english The Bone3D object.
     * @~chinese Bone3D ����
     */
    Bone3D* getBoneByIndex(unsigned int index) const;

    /**
    * @~english Get the specified bone by name.
    * @~chinese ͨ���������ƻ�ȡ����
    * @param id @~english The name.
    * @~chinese ��������
    * @return @~english The Bone3D object.
    * @~chinese Bone3D����
    */
    Bone3D* getBoneByName(const std::string& id) const;
    
    /**
     * @~english Get the specified bone index.
     * @~chinese ��ȡָ���Ĺ�������
     * @param bone @~english The specified Bone3D object.
     * @~chinese ָ����Bone3D����
     * @return @~english The index.
     * @~chinese ָ����Bone3D���������
     */
    int getBoneIndex(Bone3D* bone) const;
    
    /**
     * @~english Compute matrix palette used by gpu skin. The matrix palette is array of matrix which contatin
     * @~chinese ����һ��������(matrix palette)���Խ���GPU��Ƥ
     * @return @~english The matrix palette.
     * @~chinese �����任������
     */
    Vec4* getMatrixPalette();
    
    /**
     * @~english Get the MatrixPalette size.
     * @~chinese ��ȡ�����任������Ĵ�С
     * @return @~english The size.
     * @~chinese ��С
     * @note @~english Equal to the getSkinBoneCount() * 3
     * @~chinese ��getSkinBoneCount() * 3������
     */
    ssize_t getMatrixPaletteSize() const;
    
    /**
     * @~english Get the root bone of the skin.
     * @~chinese ��ȡ������
     * @return @~english The Bone3D object. 
     * @~chinese Bone3D����
     */
    Bone3D* getRootBone() const;
    
CC_CONSTRUCTOR_ACCESS:
    
    MeshSkin();
    
    ~MeshSkin();
    
    /**
     * @~english Remove all bones.
     * @~chinese ɾ�����й���
     */
    void removeAllBones();
    
    /**
     * @~english Add the specified skin bone
     * @~chinese ���һ����������Ƥ����
     * @param bone @~english The Bone3D object.
     * @~chinese Bone3D����
     */
    void addSkinBone(Bone3D* bone);
    
    /** 
     * @~english Get inverse bind pose by the specified Bone3D object.
     * @~chinese ��ȡָ�������İ���̬�������
     * @param bone @~english The Bone3d object.
     * @~chinese Bone3D ����
     * @return @~english The inverse bind pose matrix.
     * @~chinese ����̬�����
     */
    const Mat4& getInvBindPose(const Bone3D* bone);
    
protected:
    
    Vector<Bone3D*>    _skinBones; // bones with skin
    std::vector<Mat4>  _invBindPoses; //inverse bind pose of bone

    Bone3D* _rootBone;
    Skeleton3D*     _skeleton; //skeleton the skin referred
    
    // Pointer to the array of palette matrices.
    // This array is passed to the vertex shader as a uniform.
    // Each 4x3 row-wise matrix is represented as 3 Vec4's.
    // The number of Vec4's is (_skinBones.size() * 3).
    Vec4* _matrixPalette;
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCSKIN_H__
