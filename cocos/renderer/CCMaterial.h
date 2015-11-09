/****************************************************************************
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

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/
 ****************************************************************************/

#ifndef __cocos2d_libs__CCMaterial__
#define __cocos2d_libs__CCMaterial__

#include <string>

#include "renderer/CCRenderState.h"
#include "renderer/CCTechnique.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Mat4.h"
#include "platform/CCPlatformMacros.h"


NS_CC_BEGIN

class Technique;
class Pass;
class GLProgramState;
class Node;
class Properties;

/**
 * @addtogroup support
 * @{
 */

/**
 * @class Material
 * @brief
 * @~english
 * Material defines the apperance of the objects. It contains shaders, uniform values, and OpenGL states. Material can be create from files.
 * @~chinese ���ʶ������������ۣ�������ʹ�õ�shader��uniform��ֵ�Լ�OpenGL״̬�����ʿ��Դ��ļ�������
 */
class CC_DLL Material : public RenderState
{
    friend class Node;
    friend class Technique;
    friend class Pass;
    friend class MeshCommand;
    friend class Renderer;
    friend class Mesh;

public:
    /**
     * @~english Creates a Material using the data from the Properties object defined at the specified URL,
     * where the URL is of the format "<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>"
     * (and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).
     * @~chinese �Ӷ���ܶ����ԵĲ����ļ�����һ�����ʣ������ļ��ĸ�ʽ�������ģ�"<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>"
     * (and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).
     * @param path @~english The URL pointing to the Properties object defining the material. @~chinese �����ļ���·����
     *
     * @return @~english A new Material or NULL if there was an error. @~chinese �´����Ĳ��ʣ����ʧ�ܷ��ؿ�ָ�롣
     */
    static Material* createWithFilename(const std::string& path);

    /** @~english Creates a Material with a GLProgramState.
     It will only contain one Technique and one Pass.
     Added in order to support legacy code.
     * @~chinese ��GLProgramState�����µĲ��ʡ��´����Ĳ���ֻ����һ��Technique��һ��Pass�������Ҫ��Ϊ�˸�֮ǰ�İ汾���ݡ�
     * @param programState @~english programState used to create material. @~chinese �����������ʵ�programState��
     */
    static Material* createWithGLStateProgram(GLProgramState* programState);

    /**
     * @~english Creates a material from the specified properties object.
     * @~chinese ��Properties�������������ʡ�
     * @param materialProperties @~english The properties object defining the
     *      material (must have namespace equal to 'material'). @~chinese ���Զ��󣬶����˲��ʣ����ֿռ��б����С�material������
     * @return @~english A new Material. @~chinese �´����Ĳ��ʡ�
     */
    static Material* createWithProperties(Properties* materialProperties);

    /**
     * @~english Gets the material name
     * @~chinese ��ȡ�������ơ�
     * @return @~english Material name. @~chinese �������ơ�
     */
    std::string getName() const;
    /**
     * @~english Sets the material name
     * @~chinese ���ò������ơ�
     * @param name @~english Material name. @~chinese �������ơ�
     */
    void setName(const std::string& name);

    /** @~english Gets a Technique by its name.
     * @~chinese ͨ�����ƻ�ȡһ��Technique��
     * @param name @~english Technique name. @~chinese Technique���ơ�
     * @return @~english `nullptr` if the Technique can't be found. @~chinese �ҵ���Technique�����򷵻ؿ�ָ�롣
     */
    Technique* getTechniqueByName(const std::string& name);

    /** @~english Gets a Technique by index.
     * @~chinese ͨ��������ȡһ��Technique��
     * @param index @~english technique index. @~chinese Technique������
     * @return @~english `nullptr` if the index is invalid. @~chinese �ҵ���Technique��������Чʱ���ؿ�ָ�롣
     */
    Technique* getTechniqueByIndex(ssize_t index);

    /** @~english Gets the Technique used by the Material.
     * @~chinese ��ȡMaterial��ʹ�õ�Technique��
     * @return @~english Technique used by material. @~chinese ʹ�õ�Technique��
     */
    Technique* getTechnique() const;

    /** @~english Gets the list of Techniques.
     * @~chinese ��ȡTechnique�б�
     * @return @~english Technique list. @~chinese Technique�б�
     */
    const Vector<Technique*>& getTechniques() const;

    /** @~english Gets the number of Techniques in the Material.
     * @~chinese ��ȡTechnique����Ŀ��
     * @return @~english Technique number. @~chinese Technique��Ŀ��
     */
    ssize_t getTechniqueCount() const;

    /** @~english Adds a Technique into the Material.
     * @~chinese ���һ��Technique��
     * @param technique @~english Technique being added. @~chinese ����ӵ�Technique��
     */
    void addTechnique(Technique* technique);

    /** @~english Sets the current technique.
     * @~chinese ���õ�ǰʹ�õ�Technique��
     * @param techniqueName @~english Technique name being current technique. @~chinese ����Ϊ��ǰTechnique�����ơ�
     */
    void setTechnique(const std::string& techniqueName);

    /** @~english Clone (deep-copy) of the material.
     * @~chinese �������ʣ���ȿ�������
     * @return @~english Copy of material. @~chinese ���ʵĿ�����
     */
    virtual Material* clone() const;

protected:
    Material();
    ~Material();
    bool initWithGLProgramState(GLProgramState* state);
    bool initWithFile(const std::string& file);
    bool initWithProperties(Properties* materialProperties);

    void setTarget(Node* target);

    bool parseProperties(Properties* properties);
    bool parseTechnique(Properties* properties);
    bool parsePass(Technique* technique, Properties* properties);
    bool parseShader(Pass* pass, Properties* properties);
    bool parseSampler(GLProgramState* glProgramState, Properties* properties);
    bool parseUniform(GLProgramState* programState, Properties* properties, const char* uniformName);
    bool parseRenderState(RenderState* renderState, Properties* properties);
    
    
    // material name
    std::string _name;

    // array of techniques
    Vector<Technique*> _techniques;

    // weak pointer since it is being help by _techniques
    Technique* _currentTechnique;

    // weak reference
    Node* _target;
};

/**
 end of support group
 @}
 */

NS_CC_END


#endif /* defined(__cocos2d_libs__CCMaterial__) */
