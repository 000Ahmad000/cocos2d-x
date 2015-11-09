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

#ifndef __CCSKELETON3D_H__
#define __CCSKELETON3D_H__

#include "3d/CCBundle3DData.h"
#include "base/CCRef.h"
#include "base/CCVector.h"


NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @class Bone3D
 * @brief @~english Defines a basic hierachial structure of transformation spaces.
 * @~chinese Bone3D(3D����)�ඨ���˹��������ı任�Ĳ�νṹ����һ���������������ӹ��������ǵı任���ղ�νṹ���㣬���౸���ڹ���������
 * @lua NA
 */
class CC_DLL Bone3D : public Ref
{
    friend class Skeleton3D;
    friend class MeshSkin;
public:
    
    /**
     * @~english Returns the inverse bind pose matrix for this joint.
     * @~chinese ��ȡ��ǰ�������Դ�����任����
     * @return @~english Inverse bind pose matrix.
     * @~chinese ����̬�������
     */
    const Mat4& getInverseBindPose();
    
    /**
     * @~english Update own world matrix and children's
     * @~chinese ���¸ù����Լ��ù����������ӹ�������������任����
     */
    void updateWorldMat();
    
    /**
     * @~english Get world matrix.
     * @~chinese ��õ���������ϵ�ı任����
     * @return @~english The world matrix.
     * @~chinese ��������ϵ�任����
     **/
    const Mat4& getWorldMat();
    
    /**
     * @~english Get bone name.
     * @~chinese ��ȡ��������
     * @return @~english  The bone's name string.
     * @~chinese �����������Ƶ��ַ���
     */
    const std::string& getName() const { return _name; }
    
    /**
     * @~english Set animation value
     * @~chinese ���ù����Ķ�������
     * @param trans @~english Translate vector
     * @~chinese  ƽ������
     * @param rot   @~english Rotation quaternion
     * @~chinese ��ת��Ԫ��
     * @param scale @~english Scale vector
     * @~chinese ��������
     * @param tag @~english unique tag, only blend animation between different tags
     * @~chinese tag(��ǩ)���ڼ����϶���ʱֻ���в�ͬ��ǩ�Ĺ�����Ч
     * @param weight @~english blend weight
     */
    void setAnimationValue(float* trans, float* rot, float* scale, void* tag = nullptr, float weight = 1.0f);
    
    /**
     * @~english Clear bone blend states.
     * @~chinese �����ǰ�����Ļ��״̬.
     * */
    void clearBoneBlendState();
    /**
     * @~english Creates Bone3D object from the specified ID string.
     * @~chinese ͨ���������ַ���ID������Bone3D����.
     * @param id @~english The specified ID.
     * @~chinese ������ID.
     * @return @~english The Bone3D object.
     * @~chinese ��������Bone3D����
     */
    static Bone3D* create(const std::string& id);
    
    /**
     * @~english Sets the inverse bind pose matrix.
     * @~chinese ���ù����İ���̬����任����.
     * @param m @~english Mat4 representing the inverse bind pose for this Bone.
     * @~chinese ����̬����任����.
     */
    void setInverseBindPose(const Mat4& m);
    
    /**
     * @~english Sets the bone's original pose.
     * @~chinese ���ù����ĳ�ʼ��̬
     * @param m @~english Mat4 representing the original pose for this Bone.
     * @~chinese �����ĳ�ʼ��̬�任����
     */
    void setOriPose(const Mat4& m);
    
    /**
     * @~english Reset pose to origin
     * @~chinese ��������ǰ�İ���̬����Ϊ��ʼ��̬.
     */
    void resetPose();
    
    /**
     * @~english Updates the joint matrix.
     * @~chinese ���¹�����Joint����Joint�������ڽ���ǰ�ؽڱ任���丸�ڵ�
     * @param matrixPalette @~english The matrix palette to update.
     * @~chinese �����õĹ����任��������
     */
    void updateJointMatrix(Vec4* matrixPalette);
    
    /**
     * @~english Get the parent Bone.
     * @~chinese ��ȡ�ù����ĸ�����
     * @return @~english The parent Bone3D object.
     * @~chinese ������
     * @note @~english bone tree, we do not inherit from Node, Node has too many properties that we do not need. A clean Node is needed.
     * @~chinese ��ΪNode��������ͣ�Bone3D�ಢ�Ǽ̳���Node
     */
    Bone3D* getParentBone();

    /**
     * @~english Get child bone count.
     * @~chinese ��ȡ�ù������ӹ�����
     * @return @~english The child bone count.
     * @~chinese �ӹ�����
     */
    ssize_t getChildBoneCount() const;

    /**
     * @~english Get the specified child bone by index
     * @~chinese ͨ��������������ȡ��ȡ�ӹ���
     * @param index @~english The child bone index.
     * @~chinese �ӹ�������
     * @return @~english The Bone3D object.
     * @~chinese Bone3D����
     */
    Bone3D* getChildBoneByIndex(int index) const;

    /**
     * @~english Add the specified bone as skeleton's child.
     * @~chinese ��Ӹ����Ĺ�����Ϊ��ǰ�������ӹ���
     * @param bone @~english The specified bone.
     * @~chinese ָ����Bone3D�Ķ���
     */
    void addChildBone(Bone3D* bone);
    /**
     * @~english Remove child bone by index.
     * @~chinese ͨ������������ɾ���ӹ���
     * @param index @~english The specified index
     * @~chinese �����Ĺ�������
     */
    void removeChildBoneByIndex(int index);
    /**
     * @~english Remove the specified child bone.
     * @~chinese ɾ��ָ�����ӹ���
     * @param bone @~english The specified child bone.
     * @~chinese ָ�����ӹ���
     */
    void removeChildBone(Bone3D* bone);

    /**
     * @~english Remove all child bone.
     * @~chinese ɾ�������ӹ���
     */
    void removeAllChildBone();
    
    
    
protected:
    /**
     * @~english The BoneBlendState struct
     * @brief @~english Store the transformation and weight for bone blending
     */
    struct BoneBlendState
    {
        Vec3          localTranslate;
        Quaternion    localRot;
        Vec3          localScale;
        float         weight;
        void*         tag; //
        BoneBlendState()
        : localRot(Quaternion::identity())
        , localScale(Vec3::ONE)
        , weight(1.f)
        , tag(nullptr)
        {
            
        }
    };
	/**
     * Constructor.
     */
    Bone3D(const std::string& id);
    
	/**
     * Destructor.
     */
    virtual ~Bone3D();
    
    /**
     * Update local matrix
     */
    void updateLocalMat();
    
    /**set world matrix dirty flag*/
    void setWorldMatDirty(bool dirty = true);
    
    std::string _name; // bone name
    /**
     * The Mat4 representation of the Joint's bind pose.
     */
    Mat4 _invBindPose;
    
    Mat4 _oriPose; //original bone pose
    
    Bone3D* _parent; //parent bone
    
    Vector<Bone3D*> _children;
    
    bool          _worldDirty;
    Mat4          _world;
    Mat4          _local;
    
    std::vector<BoneBlendState> _blendStates;
    
};

/**
 * @~english Skeleton, a set contain all bones.
 * @~chinese �Ǽ��࣬���������й����ļ���
 * @class Skeleton3D
 */
class CC_DLL Skeleton3D: public Ref
{
public:
    /**
     * @~english Create Skeleton3D object by skeleton data array.
     * @~chinese ͨ���Ǽ��������鴴��һ��Skeleton3D����
     * @param skeletondata @~english The skeleton data array.
     * @~chinese �Ǽ���������
     * @return The created Skeleton3D object.
     * @lua NA
     */
    static Skeleton3D* create(const std::vector<NodeData*>& skeletondata);
    
    /**
     * @~english Get total bone count.
     * @~chinese ��ȡ�Ǽ������й���������
     * @return @~english The bone count.
     * @~chinese ��������
     */
    ssize_t getBoneCount() const;
    
    /**
     * @~english Get bone by the specified index.
     * @~chinese ͨ��ָ����������ȡ����
     * @param index @~english The specified index.
     * @~chinese ָ��������
     * @return @~english The Bone3D object.
     * @~chinese Bone3D ����
     */
    Bone3D* getBoneByIndex(unsigned int index) const;

    /**
    * @~english Get bone by the specified id(name).
    * @~chinese ͨ��ָ����id(����)����ȡ����
    * @param id @~english The specified id(name).
    * @~chinese ָ����id�����ƣ�
    * @return @~english The Bone3D object.
    * @~chinese Bone3D ����
    */
    Bone3D* getBoneByName(const std::string& id) const;
    
    /**
    * @~english Get root bones count.
    * @~chinese ��ȡ�Ǽ�����Ϊ���ڵ�Ĺ�������
    * @return @~english The root bones count.
    * @~chinese ���ڵ��������
    */
    ssize_t getRootCount() const;

    /**
    * @~english Get the specified root bone by index.
    * @~chinese ͨ��ָ������������ȡ���ڵ����
    * @param index The index.
    * @~chinese ����
    * @return The specified root bone.
    * @~chinese ���ڵ����
    */
    Bone3D* getRootBone(int index) const;
    
    /**
     * @~english Get bone index.
     * @~chinese ͨ��ָ����Bone3D���󣬻�ȡ���ڹǼ��ڵ�����
     * @param bone @~english The specified Bone3D object.
     * @~chinese ָ����Bone3D����
     * @return @~english The bone index.
     * @~chinese ����
     */
    int getBoneIndex(Bone3D* bone) const;
    
    /**
     * @~english Refresh all bones world matrix.
     * @~chinese ���¸������й�������������任����
     */
    void updateBoneMatrix();
    
CC_CONSTRUCTOR_ACCESS:
    
    Skeleton3D();
    
    ~Skeleton3D();
    
    /**
     * @~english Remove all bones
     * @~chinese ɾ�����йǼ��µ����й���.
     */
    void removeAllBones();
    
    /**
     * @~english Add the specified bone into the skeleton.
     * @~chinese ��Ǽ������ָ����.
     */
    void addBone(Bone3D* bone);
    
    /** 
     * @~english Create a Bone3D object from the specified NodeData object, then add it into the skeleton.
     * @~chinese ͨ��������NodeData ���󴴽�Bone3D����Ȼ������뵽�Ǽ���.
     * @param nodedata @~english The NodeData object.
     * @~chinese  ָ����NodeData����.
     * @return @~english The Bone3D object.
     * @~chinese  ��������Bone3D����.
     */
    Bone3D* createBone3D(const NodeData& nodedata);
    
protected:
    
    Vector<Bone3D*> _bones; // bones

    Vector<Bone3D*> _rootBones;
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCSKELETON3D_H__
