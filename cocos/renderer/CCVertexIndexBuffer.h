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

#ifndef __CC_VERTEX_INDEX_BUFFER_H__
#define __CC_VERTEX_INDEX_BUFFER_H__

#include <vector>
#include "base/CCRef.h"
#include "platform/CCGL.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class EventListenerCustom;

/**
@class VertexBuffer
@brief
@~english
VertexBuffer is an abstraction of low level openGL Vertex Buffer Object.
It is used to save an array of vertices.
 * @~chinese 
VertexBuffer��openGL�ײ�Ķ��㻺��VBO�ĳ�����������һ�鶥�����ݡ�
*@js NA
*/
class CC_DLL VertexBuffer : public Ref
{
public:
    /**@~english
    Create an instance of VertexBuffer.
     * @~chinese 
     * ����VertexBuffer��һ��ʵ����
    @param sizePerVertex @~english Size in bytes of one vertex.
     * @~chinese һ��������ֽ�����
    @param vertexNumber @~english The number of vertex.
     * @~chinese ����ĸ�����
    @param usage @~english A hint to indicate whether the vertexBuffer are updated frequently or not to let GL optimise it.
     * @~chinese ���ײ������ı�ʾ������VertexBuffer�Ƿ񾭳����£���������Ǳ�ڵ���openGL�Ż������ܡ�
    */
    static VertexBuffer* create(int sizePerVertex, int vertexNumber, GLenum usage = GL_STATIC_DRAW);
    /**
    @~english Get the size in bytes of one vertex. 
    @~chinese �õ�һ��������ֽ�����
    */
    int getSizePerVertex() const;
    /**
    @~english Get the number of vertices. 
    @~chinese �õ������������
    */
    int getVertexNumber() const;
    /**@~english
    Update all or part of vertices data, if the range specified exceeds the vertex buffer, it will be clipped.
     * @~chinese 
     * �������л򲿷ֶ�������,���ָ���ķ�Χ�����˶��㻺����,�������ضϡ�
    @param verts @~english The pointer of the vertex data.
     * @~chinese �������ݵ�ָ�롣
    @param count @~english The number of vertices to update.
     * @~chinese ������µ�������
    @param begin @~english The first vertex to update.
     * @~chinese Ҫ���µĵ�һ�������λ�á�
    */
    bool updateVertices(const void* verts, int count, int begin);

    /**@~english
    Get the size of the vertex array in bytes, equals getSizePerVertex() * getVertexNumber().
     * @~chinese 
     * �õ�����vertexBuffer�����ж���Ĵ�С�����ֽ�Ϊ��λ����ͬ��getSizePerVertex() * getVertexNumber()��
    */
    int getSize() const;
    /**@~english
    Get the internal openGL handle.
     * @~chinese 
     * �õ��ڲ�openGL�����
    */
    GLuint getVBO() const;
    
protected:
    /**@~english
    Constructor.
    @~chinese ���캯����
    */
    VertexBuffer();
    /**@~english
    Destructor.
    @~chinese ����������
    */
    virtual ~VertexBuffer();
    /**@~english
    Init the storage of vertex buffer.
     * @~chinese 
     * ��ʼ���洢���㻺������
    @param sizePerVertex @~english Size in bytes of one vertex.
     * @~chinese һ��������ֽ�����
    @param vertexNumber @~english The number of vertex.
     * @~chinese ����ĸ�����
    @param usage @~english A hint to indicate whether the vertexBuffer are updated frequently or not to let GL optimise it.
     * @~chinese ���ײ������ı�ʾ������VertexBuffer�Ƿ񾭳����£���������Ǳ�ڵ���openGL�Ż������ܡ�
    */
    bool init(int sizePerVertex, int vertexNumber, GLenum usage = GL_STATIC_DRAW);
protected:
    /**@~english
    Event handler for foreground.
    */
    void recreateVBO() const;
    /**@~english
    Event listener for foreground.
    */
    EventListenerCustom* _recreateVBOEventListener;
protected:
    /**@~english
    Internal handle for openGL.
    */
    mutable GLuint _vbo;
    /**@~english
    Size in bytes for one vertex.
    */
    int _sizePerVertex;
    /**@~english
    Number of vertices.
    */
    int _vertexNumber;
    /**@~english
    Buffer used for shadow copy.
    */
    std::vector<unsigned char> _shadowCopy;
    /**@~english
    Hint for optimisation in GL.
    */
    GLenum _usage;
protected:
    /**@~english
    Static member to indicate that use _shadowCopy or not. 
    if it is true, a memory copy is used to update the openGL resource, 
    used for platform when GL context could be lost, such as android.
    */
    static bool _enableShadowCopy;
public:
    /**@~english
    Static getter for shadowCopy.
     * @~chinese 
     * �õ�ShdowCopy�Ŀ���״̬�������������ô��Ҫ���ڴ汣��һ������������openGL��Դ��
    */
    static bool isShadowCopyEnabled() { return _enableShadowCopy; }
    /**@~english
     Static setter for shadowCopy.
     * @~chinese 
     * ����ShdowCopy�Ŀ���״̬�������������ô��Ҫ���ڴ汣��һ������������openGL��Դ��
     */
    static void enableShadowCopy(bool enabled) { _enableShadowCopy = enabled; }
};

/**
@class IndexBuffer
@brief
@~english
IndexBuffer is an abstraction of low level openGL Buffer Object.
It used to save an array of indices.
 * @~chinese 
 * ��VertexBuffer��IndexBufferҲ�ǵײ�openGL��������ķ�װ��
 * �����ڱ����������顣
@js NA
*/
class CC_DLL IndexBuffer : public Ref
{
public:
    /**@~english
    Enum for the type of index, short indices and int indices could be used.
     * @~chinese 
     * ö�����͵�ָ��,ÿһ������������short��int���͡�
    */
    enum class IndexType
    {
        /**@~english Short index will be used. @~chinese ��ʹ��short��Ϊ������*/
        INDEX_TYPE_SHORT_16,
        /**@~english Int index will be used. @~chinese ��ʹ��Int��Ϊ������*/
        INDEX_TYPE_UINT_32
    };
    
public:
    /**@~english
    Create an instance of IndexBuffer.
     * @~chinese 
     * ����һ��IndexBufferʵ����
    @param type @~english type of index.
     * @~chinese ���������͡�
    @param number @~english The number of indices.
     * @~chinese ������������
    @param usage @~english A hint to indicate whether the indexBuffer are updated frequently or not to let GL optimise it.
     @~chinese ���ײ������ı�ʾ������indexBuffer�Ƿ񾭳����£���������Ǳ�ڵ���openGL�Ż������ܡ�
    */
    static IndexBuffer* create(IndexType type, int number, GLenum usage = GL_STATIC_DRAW);
    /**@~english
    Getter for type of indices.
     * @~chinese 
     * �õ����������͡�
    */
    IndexType getType() const;
    /**@~english
    Get the size in bytes for one index, will be 2 for INDEX_TYPE_SHORT_16 and 4 for INDEX_TYPE_UINT_32.
     * @~chinese 
     * ���һ�������Ĵ�С(���ֽ�Ϊ��λ��,short���͵ķ���2��int���͵ķ���4��
    */
    int getSizePerIndex() const;
    /**@~english
    Get the number of indices.
     * @~chinese 
     * �õ�������������
    */
    int getIndexNumber() const;
    /**@~english
    Update all or part of indices data, if the range specified exceeds the vertex buffer, it will be clipped.
     * @~chinese 
     * �������л򲿷�ָ������,���ָ���ķ�Χ�����˶��㻺����,�������ضϡ�
    @param indices @~english The pointer of the index data.
     * @~chinese �������ݵ�ָ�롣
    @param count @~english The number of indices to update.
     * @~chinese Ҫ���µ���������.
    @param begin @~english The start index to update.
     * @~chinese ��һ��Ҫ���µ�����λ�á�
    */
    bool updateIndices(const void* indices, int count, int begin);
    /**@~english
    Get the size in bytes of the array of indices.
     * @~chinese 
     * �õ����������Ĵ�С�����ֽ�Ϊ��λ��
    */
    int getSize() const;
    /**@~english
    Get the openGL handle for index buffer.
     * @~chinese 
     * ����ڲ�openGL�����
    */
    GLuint getVBO() const;

protected:
    /**@~english
    Constructor.
     * @~chinese 
     * ���캯����
    */
    IndexBuffer();
    /**@~english
    Destructor.
     * @~chinese 
     * ����������
    */
    virtual ~IndexBuffer();
    /**@~english
    Init the storage of IndexBuffer.
     * @~chinese 
     * ��ʼ��IndexBuffer�Ĵ洢��
    @param type @~english type of index.
     * @~chinese ���������͡�
    @param number @~english The number of indices.
     * @~chinese ������������
    @param usage @~english A hint to indicate whether the indexBuffer are updated frequently or not to let GL optimise it.
     @~chinese ���ײ������ı�ʾ������indexBuffer�Ƿ񾭳����£���������Ǳ�ڵ���openGL�Ż������ܡ�
    */
    bool init(IndexType type, int number, GLenum usage = GL_STATIC_DRAW);
    
protected:
    /**@~english
    Handle for openGL.
    */
    mutable GLuint _vbo;
    /**@~english
    Type for index.
    */
    IndexType _type;
    /**@~english
    Number of indices.
    */
    int _indexNumber;
    
protected:
    /**@~english
    Event handler for foreground.
    */
    void recreateVBO() const;
    /**@~english
    Event listener for foreground.
    */
    EventListenerCustom* _recreateVBOEventListener;
    /**@~english
    Buffer used for shadow copy.
    */
    std::vector<unsigned char> _shadowCopy;
    /**@~english
    Hint for optimisation in GL.
    */
    GLenum _usage;
protected:
    /**@~english
    Static member to indicate that use _shadowCopy or not. 
    if it is true, a memory copy is used to update the openGL resource, 
    used for platform when GL context could be lost, such as android.
    */
    static bool _enableShadowCopy;
public:
    /**@~english
    Static getter for shadowCopy.
     * @~chinese 
     * �õ�ShdowCopy�Ŀ���״̬�������������ô��Ҫ���ڴ汣��һ������������openGL��Դ��
    */
    static bool isShadowCopyEnabled() { return _enableShadowCopy; }
    /**@~english
     Static setter for shadowCopy.
     * @~chinese 
     * ����ShdowCopy�Ŀ���״̬�������������ô��Ҫ���ڴ汣��һ������������openGL��Դ��
     */
    static void enableShadowCopy(bool enabled) { _enableShadowCopy = enabled; }
};


NS_CC_END

/**
 end of support group
 @}
 */
#endif /* __CC_VERTEX_INDEX_BUFFER_H__*/
