/****************************************************************************
Copyright 2014 Chukong Technologies Inc.
 
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
 
 Autobinding Interface from GamePlay3D: http://www.gameplay3d.org/
****************************************************************************/

#ifndef __CCGLPROGRAMSTATE_H__
#define __CCGLPROGRAMSTATE_H__

#include <unordered_map>

#include "base/ccTypes.h"
#include "base/CCVector.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class GLProgram;
class Texture2D;
struct Uniform;
struct VertexAttrib;
class EventListenerCustom;
class EventCustom;
class Node;

/**@class UniformValue
@brief
@~english
 * Uniform Value, which is used to store to value send to openGL pipe line by glUniformXXX.
 *
 * @~chinese 
 * Uniform��ֵ, �洢������ͨ��glUniformXXX�������͵�openGL��Ⱦ���ߡ�
 * 
 * @lua NA
 */
class CC_DLL UniformValue
{
    friend class GLProgram;
    friend class GLProgramState;
public:
    /**@~english
     Constructor. The Uniform and Glprogram will be nullptr.
     * @~chinese 
     * ���캯���������е�Uniform��GLProgram������null��
     */
    UniformValue();
    /**@~english
     Constructor with uniform and glprogram.
     * @~chinese 
     * ���캯����
     @param uniform @~english Uniform to apply the value.
     * @~chinese �����������ݵ�Uniform��
     @param glprogram @~english Specify the owner GLProgram of this uniform and uniform value.
     * @~chinese Uniform��Uniform Value�����ĸ�GLProgram��
     */
    UniformValue(Uniform *uniform, GLProgram* glprogram);

    /**@~english Destructor. @~chinese ����������*/
    ~UniformValue();
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param value @~english The float value @~chinese float���ݡ�
    */
    void setFloat(float value);
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param value @~english The int value @~chinese int���ݡ�
    */
    void setInt(int value);
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param size @~english The number of float. @~chinese float���ݵĸ�����
    @param pointer @~english The float value pointer @~chinese float����ָ�롣
    */
    void setFloatv(ssize_t size, const float* pointer);
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param value @~english The Vec2 value @~chinese Vec2���ݡ�
    */
    void setVec2(const Vec2& value);
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param size @~english The number of Vec2. @~chinese Vec2���ݵĸ�����
    @param pointer @~english The Vec2 value pointer @~chinese Vec2����ָ�롣
    */
    void setVec2v(ssize_t size, const Vec2* pointer);
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param value @~english The Vec2 value @~chinese Vec2���ݡ�
    */
    void setVec3(const Vec3& value);
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param size @~english The number of Vec3. @~chinese Vec3���ݵĸ�����
    @param pointer @~english The Vec3 value pointer @~chinese Vec3����ָ�롣
    */
    void setVec3v(ssize_t size, const Vec3* pointer);
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param value @~english The Vec2 value @~chinese Vec2���ݡ�
    */
    void setVec4(const Vec4& value);
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param size @~english The number of Vec4. @~chinese Vec4���ݵĸ�����
    @param pointer @~english The Vec4 value pointer @~chinese Vec4����ָ�롣
    */
    void setVec4v(ssize_t size, const Vec4* pointer);
    /**
    @~english Set Uniform value. @~chinese ����Uniform���ݡ�
    @param value @~english The Mat4 value @~chinese Mat4���ݡ�
    */
    void setMat4(const Mat4& value);
    /**
     @}
     */
    
    /**@~english
     Set call back to uniform value, which could be used for array and struct.
     * @~chinese 
     * ��UniformValue���ûص�������
     @param callback @~english Callback function to send data to OpenGL pipeline.
     * @~chinese �ص�������
     */
    void setCallback(const std::function<void(GLProgram*, Uniform*)> &callback);
    /**@~english
     Set texture to uniform value.
     * @~chinese 
     * ��������ֵ��UniformValue��
     @param textureId @~english The texture handle.
     * @~chinese ��������
     @param textureUnit @~english The binding texture unit to be used in shader.
     * @~chinese ����Ҫ���󶨵��ĸ��������ϡ�
    */
    void setTexture(GLuint textureId, GLuint textureUnit);
    
    /**
    @~english Apply the uniform value to openGL pipeline. 
    @~chinese ��uniform��ֵӦ�õ�openGL��Ⱦ���ߡ�
    */
    void apply();

protected:

    enum class Type {
        VALUE,
        POINTER,
        CALLBACK_FN     // CALLBACK is already defined in windows, can't use it.
    };

    /** Weak reference to Uniform.*/
	Uniform* _uniform;
    /** Weak reference to GLprogram.*/
    GLProgram* _glprogram;
    /** What kind of type is the Uniform*/
    Type _type;

    /**
     @name Uniform Value Uniform
     @{
     */
    union U{
        float floatValue;
        int intValue;
        float v2Value[2];
        float v3Value[3];
        float v4Value[4];
        float matrixValue[16];
        struct {
            GLuint textureId;
            GLuint textureUnit;
        } tex;
        struct {
            const float* pointer;
            GLsizei size;
        } floatv;
        struct {
            const float* pointer;
            GLsizei size;
        } v2f;
        struct {
            const float* pointer;
            GLsizei size;
        } v3f;
        struct {
            const float* pointer;
            GLsizei size;
        } v4f;
        std::function<void(GLProgram*, Uniform*)> *callback;

        U() { memset( this, 0, sizeof(*this) ); }
        ~U(){}
        U& operator=( const U& other ) {
            memcpy(this, &other, sizeof(*this));
            return *this;
        }
    } _value;
    /**
     @}
     */
};

/**
@class VertexAttribValue
@brief
@~english
 * Vertex Attribute Value, which is an abstraction of VertexAttribute and data pointer.
 *
 * @~chinese 
 * ��������ֵ,���ڳ����VertexAttribute�����ݡ�
 * 
 * @lua NA
 */
class CC_DLL VertexAttribValue
{
    friend class GLProgram;
    friend class GLProgramState;
    friend class VertexAttribBinding;

public:
    /**@~english
     Constructor.
     * @~chinese 
     * ���캯����
     @param vertexAttrib @~english VertexAttrib from shader.
     * @~chinese ��shader��������VertexAttrib��
    */
    VertexAttribValue(VertexAttrib *vertexAttrib);
    /**@~english
     Constructor.
     * @~chinese 
     * ���캯����
     */
    VertexAttribValue();
    /**@~english
     Destructor.
     * @~chinese 
     * ����������
     */
    ~VertexAttribValue();
    
    /**@~english
     Set the data pointer, which is similar as glVertexAttribPointer.
     * @~chinese 
     * ��������ָ��,��������glVertexAttribPointer��������ʹ�á�
     @param size @~english The number of type in the vertex attribute.
     * @~chinese �����������ݵ�������
     @param type @~english The type of data in vertex attribute.
     * @~chinese �����������ݵ����͡�
     @param normalized @~english If true, 0-255 data will be mapped to 0.0-1.0.
     * @~chinese ����������,0 - 255���ݽ���ӳ�䵽0.0��1.0��
     @param stride @~english The number of bytes if an interleaved vertex array is used. 0 means array is not interleaved.
     * @~chinese �����һ�����Խ���Ķ������飬���ʾ�������������ƫ��ֵ��0��ʾ�ǽ��涥�����顣
     @param pointer @~english The pointer to the vertex data.
     * @~chinese �������ݵ�ָ�롣
     */
	void setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    /**
    @~english Set a user call back for set VertexAttrib array. 
    @~chinese ����һ���û��ص������������ö������ԡ�
    */
    void setCallback(const std::function<void(VertexAttrib*)> &callback);
    /**
    @~english Apply the vertex attribute to the openGL pipeline. 
    @~chinese ����������Ӧ����openGL��Ⱦ���ߡ�
    */
    void apply();

protected:
	VertexAttrib* _vertexAttrib;  // weak ref
    bool _useCallback;
    bool _enabled;

    union U{
        struct {
            GLint size;
            GLenum type;
            GLboolean normalized;
            GLsizei stride;
            GLvoid *pointer;
        } pointer;
        std::function<void(VertexAttrib*)> *callback;

        U() { memset( this, 0, sizeof(*this) ); }
        ~U(){}
        U& operator=( const U& other ) {
            memcpy(this, &other, sizeof(*this));
            return *this;
        }
    } _value;
};


/**
@class GLProgramState
@brief
@~english
 GLProgramState holds the 'state' (uniforms and attributes) of the GLProgram.
 A GLProgram can be used by thousands of Nodes, but if different uniform values 
 are going to be used, then each node will need its own GLProgramState
 * @~chinese 
 * GLProgramState������Щ״̬������GLProgram��Uniform�Ͷ������ԡ�
 GLProgram���Ա��ܶ��Nodeʹ�ã��������Nodeʹ�õ�Unifrom��ֵ��ͬ�Ļ�����ôNode����Ҫ�����Լ���GLProgramState��
 */
class CC_DLL GLProgramState : public Ref
{
    friend class GLProgramStateCache;
public:

    /** 
    @~english returns a new instance of GLProgramState for a given GLProgram  
    @~chinese ��GLProgram�д���һ��GLProgramState����ʵ����
    */
    static GLProgramState* create(GLProgram* glprogram);
    /** 
    @~english gets-or-creates an instance of GLProgramState for a given GLProgram  
    @~chinese ��Cache�У�����GLProgramֵ���´������߻�ȡcache��GLProgramState��ʵ����
    */
    static GLProgramState* getOrCreateWithGLProgram(GLProgram* glprogram);

    /** 
    @~english gets-or-creates an instance of GLProgramState for a given GLProgramName  
    @~chinese ��Cache�У�����GLProgram�����֣��´������߻�ȡcache��GLProgramState��ʵ����
    */
    static GLProgramState* getOrCreateWithGLProgramName(const std::string &glProgramName );

    /** 
    @~english gets-or-creates an instance of GLProgramState for given shaders  
    @~chinese ��Cache�У�����VertexShader��FragmentShader��Դ���룬�´������߻�ȡcache��GLProgramState��ʵ����
    */
    static GLProgramState* getOrCreateWithShaders(const std::string& vertexShader, const std::string& fragShader, const std::string& compileTimeDefines);

    /** 
    @~english Returns a new copy of the GLProgramState. The GLProgram is reused  
    @~chinese ����һ���µ�GLProgramState�ĸ�����
    */
    GLProgramState* clone() const;

    /**@~english
     Apply GLProgram, attributes and uniforms.
     * @~chinese 
     * Ӧ��GLProgram,�������Ժ�Uniform��������Ⱦ���ߡ�
     @param modelView @~english The applied modelView matrix to shader.
     * @~chinese Ҫ���õ�ModelView����
     */
    void apply(const Mat4& modelView);
    /**@~english
     Apply GLProgram, and built in uniforms.
     * @~chinese 
     * Ӧ��GLProgram�����õ�Uniform������
     @param modelView @~english The applied modelView matrix to shader.
     * @~chinese Ҫ���õ�ModelView����
     */
    void applyGLProgram(const Mat4& modelView);
    /**@~english
     Apply attributes.
     * @~chinese 
     * Ӧ�ö������ԡ�
     @param applyAttribFlags @~english Call GL::enableVertexAttribs(_vertexAttribsFlags) or not.
     * @~chinese �Ƿ����GL::enableVertexAttribs������
     */
    void applyAttributes(bool applyAttribFlags = true);
    /**@~english
     Apply user defined uniforms.
     * @~chinese 
     * Ӧ���Զ���Uniform��ֵ��
     */
    void applyUniforms();

    /**
    @~english Set the binded GLProgram.
    @~chinese ���ð󶨵�GLProgram��
    */
    void setGLProgram(GLProgram* glprogram);
    /**
    @~english Get the binded GLProgram.
    @~chinese �õ��󶨵�GLProgram��
    */
    GLProgram* getGLProgram() const { return _glprogram; }
    
    /** 
    @~english Get the flag of vertex attribs used by OR operation. 
    @~chinese ����GLProgramState�������ԣ��õ�GL::enableVertexAttribs��flag������
    */
    uint32_t getVertexAttribsFlags() const;
    /**
    @~english Get the number of vertex attributes. 
    @~chinese �õ��������Ե�������
    */
    ssize_t getVertexAttribCount() const;
    /**@~english
     Set the vertex attribute value by calling callback.
     * @~chinese 
     * ͨ���ص��������ö�������ֵ��
     @param name @~english The name of Vertex attrib. @~chinese �������Ե�����
     @param callback @~english The callback for setting vertex attrib. @~chinese �������ԵĻص�������
     */
    void setVertexAttribCallback(const std::string &name, const std::function<void(VertexAttrib*)> &callback);
    /**@~english
     Set the vertex attribute value.
     * @~chinese 
     * ���ö�������ֵ��
     @param name @~english The vertex attrib name. @~chinese �������Ե����֡�
     @param size @~english The count of data in the vertex attrib, range from 0-4. @~chinese �������Ե�ֵ��������0-4��
     @param type @~english The type of data in the vertex attrib @~chinese �������ݵ����͡�
     @param normalized @~english Normalize the data or not 0-255 will be mapped to 0-1.0  @~chinese ���ݵĹ�һ����ǣ�0-255��ӳ�䵽0-1.0
     @param stride @~english The stride of the interleaved array.  @~chinese ���涥�����ԵĶ��������еĲ�����
     @param pointer @~english The data pointer  @~chinese ����ָ�롣
     */
    void setVertexAttribPointer(const std::string &name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    
    /**
    @~english Get the number of user defined uniform count. 
    @~chinese �û��Զ����Uniform�ĸ�����
    */
    ssize_t getUniformCount() const { return _uniforms.size(); }
    
    /** @{
     Setting user defined uniforms by uniform string name in the shader.
     */
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param value @~english The int value @~chinese int��ֵ
    */
    void setUniformInt(const std::string &uniformName, int value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param value @~english The float value @~chinese Uniform��float��ֵ��
    */
    void setUniformFloat(const std::string &uniformName, float value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param size @~english The count of value @~chinese float��ֵ�ĸ���
    @param pointer @~english The pointer of float value @~chinese Uniform��float��ֵָ��
    */
    void setUniformFloatv(const std::string &uniformName, ssize_t size, const float* pointer);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param value @~english The Vec2 value @~chinese Uniform��Vec2��ֵ��
    */
    void setUniformVec2(const std::string &uniformName, const Vec2& value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param size @~english The count of value @~chinese Vec2��ֵ�ĸ���
    @param pointer @~english The pointer of Vec2 value @~chinese Uniform��Vec2��ֵָ��
    */
    void setUniformVec2v(const std::string &uniformName, ssize_t size, const Vec2* pointer);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param value @~english The Vec3 value @~chinese Uniform��Vec3��ֵ��
    */
    void setUniformVec3(const std::string &uniformName, const Vec3& value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param size @~english The count of value @~chinese Vec3��ֵ�ĸ���
    @param pointer @~english The pointer of Vec3 value @~chinese Uniform��Vec3��ֵָ��
    */
    void setUniformVec3v(const std::string &uniformName, ssize_t size, const Vec3* pointer);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param value @~english The Vec4 value @~chinese Uniform��Vec4��ֵ��
    */
    void setUniformVec4(const std::string &uniformName, const Vec4& value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param size @~english The count of value @~chinese Vec4��ֵ�ĸ���
    @param pointer @~english The pointer of Vec4 value @~chinese Uniform��Vec4��ֵָ��
    */
    void setUniformVec4v(const std::string &uniformName, ssize_t size, const Vec4* pointer);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param value @~english The Mat4 value @~chinese Uniform��Mat4��ֵ
    */
    void setUniformMat4(const std::string &uniformName, const Mat4& value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param callback @~english callback function for uniform @~chinese Uniform�Ļص�������
    */
    void setUniformCallback(const std::string &uniformName, const std::function<void(GLProgram*, Uniform*)> &callback);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param texture @~english The texture value��the openGL handle will be used @~chinese Uniform������ֵ��
    */
    void setUniformTexture(const std::string &uniformName, Texture2D *texture);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformName @~english The name of uniform. @~chinese Uniform�����֡�
    @param textureId @~english The texture value @~chinese Uniform������ֵ��
    */
    void setUniformTexture(const std::string &uniformName, GLuint textureId);
    /**@}*/
    
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param value @~english The int value @~chinese int��ֵ
    */
    void setUniformInt(GLint uniformLocation, int value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param value @~english The float value @~chinese Uniform��float��ֵ��
    */
    void setUniformFloat(GLint uniformLocation, float value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param size @~english The count of value @~chinese float��ֵ�ĸ���
    @param pointer @~english The pointer of float value @~chinese Uniform��float��ֵָ��
    */
    void setUniformFloatv(GLint uniformLocation, ssize_t size, const float* pointer);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param value @~english The Vec2 value @~chinese Uniform��Vec2��ֵ��
    */
    void setUniformVec2(GLint uniformLocation, const Vec2& value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param size @~english The count of value @~chinese Vec2��ֵ�ĸ���
    @param pointer @~english The pointer of Vec2 value @~chinese Uniform��Vec2��ֵָ��
    */
    void setUniformVec2v(GLint uniformLocation, ssize_t size, const Vec2* pointer);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param value @~english The Vec3 value @~chinese Uniform��Vec3��ֵ��
    */
    void setUniformVec3(GLint uniformLocation, const Vec3& value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param size @~english The count of value @~chinese Vec3��ֵ�ĸ���
    @param pointer @~english The pointer of Vec3 value @~chinese Uniform��Vec3��ֵָ��
    */
    void setUniformVec3v(GLint uniformLocation, ssize_t size, const Vec3* pointer);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param value @~english The Vec4 value @~chinese Uniform��Vec4��ֵ��
    */
    void setUniformVec4(GLint uniformLocation, const Vec4& value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param size @~english The count of value @~chinese Vec4��ֵ�ĸ���
    @param pointer @~english The pointer of Vec4 value @~chinese Uniform��Vec4��ֵָ��
    */
    void setUniformVec4v(GLint uniformLocation, ssize_t size, const Vec4* pointer);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param value @~english The Mat4 value @~chinese Uniform��Mat4��ֵ
    */
    void setUniformMat4(GLint uniformLocation, const Mat4& value);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param callback @~english callback function for uniform @~chinese Uniform�Ļص�������
    */
    void setUniformCallback(GLint uniformLocation, const std::function<void(GLProgram*, Uniform*)> &callback);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param texture @~english The texture value��the openGL handle will be used @~chinese Uniform������ֵ��
    */
    void setUniformTexture(GLint uniformLocation, Texture2D *texture);
    /**
    @~english set the value for uniform.
    @~chinese ����Uniform��ֵ.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform��λ�á�
    @param textureId @~english The texture value @~chinese Uniform������ֵ��
    */
    void setUniformTexture(GLint uniformLocation, GLuint textureId);
    /**@}*/

    /** 
     * Returns the Node bound to the GLProgramState
     */
    Node* getNodeBinding() const;

    /**
     * Sets the node that this render state is bound to.
     *
     * The specified node is used to apply auto-bindings for the render state.
     * This is typically set to the node of the model that a material is
     * applied to.
     *
     * @param node The node to use for applying auto-bindings.
     */
    void setNodeBinding(Node* node);

    /**
     * Applies the specified custom auto-binding.
     *
     * @param uniformName Name of the shader uniform.
     * @param autoBinding Name of the auto binding.
     */
    void applyAutoBinding(const std::string& uniformName, const std::string& autoBinding);

    /**
     * Sets a uniform auto-binding.
     *
     * This method parses the passed in autoBinding string and attempts to convert it
     * to an enumeration value. If it matches to one of the predefined strings, it will create a
     * callback to get the correct value at runtime.
     *
     * @param uniformName The name of the material parameter to store an auto-binding for.
     * @param autoBinding A string matching one of the built-in AutoBinding enum constants.
     */
    void setParameterAutoBinding(const std::string& uniformName, const std::string& autoBinding);

    /**
     * An abstract base class that can be extended to support custom material auto bindings.
     *
     * Implementing a custom auto binding resolver allows the set of built-in parameter auto
     * bindings to be extended or overridden. Any parameter auto binding that is set on a
     * material will be forwarded to any custom auto binding resolvers, in the order in which
     * they are registered. If a registered resolver returns true (specifying that it handles
     * the specified autoBinding), no further code will be executed for that autoBinding.
     * This allows auto binding resolvers to not only implement new/custom binding strings,
     * but it also lets them override existing/built-in ones. For this reason, you should
     * ensure that you ONLY return true if you explicitly handle a custom auto binding; return
     * false otherwise.
     *
     * Note that the custom resolver is called only once for a GLProgramState object when its
     * node binding is initially set. This occurs when a material is initially bound to a
     * Node. The resolver is NOT called each frame or each time the GLProgramState is bound.
     *
     * If no registered resolvers explicitly handle an auto binding, the binding will attempt
     * to be resolved using the internal/built-in resolver, which is able to handle any
     * auto bindings found in the GLProgramState::AutoBinding enumeration.
     *
     * When an instance of a class that extends AutoBindingResolver is created, it is automatically
     * registered as a custom auto binding handler. Likewise, it is automatically unregistered
     * on destruction.
     *
     * @js NA
     * @lua NA
     */
    class CC_DLL AutoBindingResolver
    {
    public:

        /**
         * Destructor.
         */
        virtual ~AutoBindingResolver();

        /**
         * Called when an unrecognized uniform variable is encountered
         * during material loading.
         *
         * Implementations of this method should do a string comparison on the passed
         * in name parameter and decide whether or not they should handle the
         * parameter. If the parameter is not handled, false should be returned so
         * that other auto binding resolvers get a chance to handle the parameter.
         * Otherwise, the parameter should be set or bound and true should be returned.
         *
         * @param glProgramState The glProgramState
         * @param node The node that the material is attached to.
         * @param uniformName Name of the uniform
         * @param autoBinding Name of the auto binding to be resolved.
         *
         * @return True if the auto binding is handled and the associated parameter is
         *      bound, false otherwise.
         */
        virtual bool resolveAutoBinding(GLProgramState* glProgramState, Node* node, const std::string& uniformName, const std::string& autoBinding) = 0;

    protected:

        /**
         * Constructor.
         */
        AutoBindingResolver();
    };

protected:
    GLProgramState();
    ~GLProgramState();
    bool init(GLProgram* program);
    void resetGLProgram();
    void updateUniformsAndAttributes();
    VertexAttribValue* getVertexAttribValue(const std::string& attributeName);
    UniformValue* getUniformValue(const std::string& uniformName);
    UniformValue* getUniformValue(GLint uniformLocation);


    bool _uniformAttributeValueDirty;
    std::unordered_map<std::string, GLint> _uniformsByName;
    std::unordered_map<GLint, UniformValue> _uniforms;
    std::unordered_map<std::string, VertexAttribValue> _attributes;
    std::unordered_map<std::string, int> _boundTextureUnits;

    int _textureUnitIndex;
    uint32_t _vertexAttribsFlags;
    GLProgram* _glprogram;

    Node* _nodeBinding; // weak ref

    // contains uniform name and variable
    std::unordered_map<std::string, std::string> _autoBindings;

    // Map of custom auto binding resolvers.
    static std::vector<AutoBindingResolver*> _customAutoBindingResolvers;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _backToForegroundlistener;
#endif

};

NS_CC_END

/**
 end of support group
 @}
 */
#endif /* __CCGLPROGRAMSTATE_H__ */
