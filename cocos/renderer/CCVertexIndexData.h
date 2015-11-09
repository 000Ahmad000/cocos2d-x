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

#ifndef __CC_VERTEX_INDEX_DATA_H__
#define __CC_VERTEX_INDEX_DATA_H__

#include "base/CCRef.h"
#include <map>

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class VertexBuffer;
/**
@class VertexStreamAttribute
@brief
@~english
VertexStreamAttribute is used to specify the vertex attribute for drawing, which is correspondent to
glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr).

 _semantic  ->  index
 _size      ->  size
 _type      ->  type
 _normalize ->  normalized
 _offset is used to compute the start offset in a interleaved array, take a V3F_C4B_T2F array,
 offset of vertex will be 0, offset of color would be 0 + sizeof(float) * 3 = 12, 
 offset of texture coord would be 12 + sizeof(char) * 4 = 16.
 * @~chinese 
 * VertexStreamAttribute����ָ����Ⱦ���ݵĶ������ԣ��ͺ���
 * glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)�е�
 * ������Ӧ��
 * 
 * _semantic ->index��
 * _size ->size��
 * _type ->type��
 * _normalize ->normalized��
 * _offset���ڼ��㽻�����������ƫ��ֵ,��V3F_C4B_T2F����Ϊ��,
 * �������Ե�ƫ����0,��ɫ���Ե�ƫ����0 + sizeof(float)*3 = 12
 * �����������Ե�ƫ���� 12 + sizeof(char)*4=16
 @js NA
*/
struct CC_DLL VertexStreamAttribute
{
    /**@~english
     Constructor.
     * @~chinese 
     * ���캯����
     */
    VertexStreamAttribute()
    : _normalize(false),_offset(0),_semantic(0),_type(0),_size(0)
    {
    }
    /**@~english
     Constructor
     * @~chinese 
     * ���캯����
     * @param offset @~english The offset of the attribute.
     * @~chinese ���Ե�ƫ��
     @param semantic @~english The semantic (Position, Texcoord, Color etc) of attribute.
     * @~chinese �������Ե�����,��λ�á���ɫ�ȡ�
     @param type @~english The type of attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
     * @~chinese �������Ե�����,������GL_FLOAT,GL_UNSIGNED_BYTE�ȵȡ�
     @param size @~english Describe how many elements of type in the attribute.
     * @~chinese ���԰������ٸ�type���͵�Ԫ�ء�
     */
    VertexStreamAttribute(int offset, int semantic, int type, int size)
    : _normalize(false),_offset(offset),_semantic(semantic),_type(type),_size(size)
    {
    }
    /**@~english
     Constructor
     * @~chinese 
     * ���캯����
     @param offset @~english The offset of the attribute.
     * @~chinese ���Ե�ƫ��
     @param semantic @~english The semantic (Position, Texcoord, Color etc) of attribute.
     * @~chinese �������Ե�����,��λ�á���ɫ�ȡ�
     @param type @~english The type of attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
     * @~chinese �������Ե�����,������GL_FLOAT,GL_UNSIGNED_BYTE�ȵȡ�
     @param size @~english Describe how many elements of type in the attribute.
     * @~chinese ���԰������ٸ�type���͵�Ԫ�ء�
     @param normalize @~english If true, the data will be normalized by deviding 255.
     * @~chinese �������,���ݽ�����255����һ����
     */
    VertexStreamAttribute(int offset, int semantic, int type, int size, bool normalize)
    : _normalize(normalize),_offset(offset),_semantic(semantic),_type(type),_size(size)
    {
    }
    /**@~english
     Whether the attribute should be normalized or not.
     * @~chinese 
     * �Ƿ�Ӧ�ù淶�����ԡ�
     */
    bool _normalize;
    /**@~english
     The offset of the attribute in the buffer.
     * @~chinese 
     * ���Ե�ƫ�ơ�
     */
    int _offset;
    /**@~english
     Describe that the attribute usage, could be Position, Color etc.
     * @~chinese 
     * �������Ե�����,��λ�á���ɫ�ȡ�
     */
    int _semantic;
    /**@~english
     Describe the type of attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
     * @~chinese 
     * �������Ե�����,������GL_FLOAT,GL_UNSIGNED_BYTE�ȵȡ�
     */
    int _type;
    /**@~english
     Describe how many elements of type in the attribute.
     * @~chinese 
     * �������԰������ٸ�type���͵�Ԫ�ء�
     */
    int _size;
};

/**
@class VertexData
@brief
@~english
VertexData is a class used for specify input streams for GPU rendering pipeline,
a VertexData will be composed by several streams, every stream will contain a VertexStreamAttribute
and the binding VertexBuffer. Streams will be identified by semantic.
 * @~chinese 
 * VertexData������ָ����������GPU��Ⱦ����,
 * VertexData���ɼ��������,ÿһ��������������������VertexStreamAttribute�У������ڰ󶨵�VertexBuffer��
 * �����֮���������ʾ��
@js NA
*/

class CC_DLL VertexData : public Ref
{
public:
    /**@~english
    Create function, used to create a instance of VertexData.
     * @~chinese 
     * ��������,����һ��VertexDataʵ����
    */
    static VertexData* create();
    
    /**@~english
    Get the number of streams in the VertexData.
     * @~chinese 
     * �õ�VertexData����������
    */
    size_t getVertexStreamCount() const;
    /**@~english
    Set a stream to VertexData,given that stream is identified by semantic, so if the semantic is not
    specified before, it will add a stream, or it will override the old one.
     * @~chinese 
     * ����һ���µ������������������֮ǰ�����ڣ��ͻ��½�һ��������������Ḳ��֮ǰ����
    @param buffer @~english The binding buffer of the stream.
     * @~chinese ���󶨵�VertexBuffer
    @param stream @~english The binding vertex attribute, its member semantic will be used as the identifier.
     * @~chinese �������ԡ�
    */
    bool setStream(VertexBuffer* buffer, const VertexStreamAttribute& stream);
    /**@~english
    Remove the given streams.
     * @~chinese 
     * ɾ����������������
    @param semantic @~english The semantic of the stream.
     * @~chinese Ҫɾ�����������塣
    */
    void removeStream(int semantic);
    /**@~english
    Get the attribute of stream, const version.
     * @~chinese 
     * �õ���������,const�汾��
    @param semantic @~english The semantic of the stream.
     * @~chinese Ҫ�õ����������塣
    */
    const VertexStreamAttribute* getStreamAttribute(int semantic) const;
    /**@~english
    Get the attribute of stream.
     * @~chinese 
     * �õ���������
    @param semantic @~english The semantic of the stream.
     * @~chinese Ҫ�õ����������塣
    */
    VertexStreamAttribute* getStreamAttribute(int semantic);
    /**@~english
    Get the binded buffer of the stream.
     * @~chinese 
     * �õ����󶨵�VertexBuffer��
    @param semantic @~english The semantic of the stream.
     * @~chinese Ҫ�õ����������塣
    */
    VertexBuffer* getStreamBuffer(int semantic) const;
    
    /**@~english
    Called for rendering, it will bind the state of vertex data to current rendering pipeline.
     * @~chinese 
     * �ڻ���ʱ����,���Ὣ�������ݵİ󶨵���ǰ��Ⱦ�ܵ���
    */
    void use();
protected:
    /**@~english
    Constructor.
     * @~chinese 
     * ���캯����
    */
    VertexData();
    /**@~english
    Destructor.
     * @~chinese 
     * ����������
    */
    virtual ~VertexData();
protected:
    /**
    Simple struct to bundle buffer and attribute.
    */
    struct BufferAttribute
    {
        VertexBuffer* _buffer;
        VertexStreamAttribute _stream;
    };
    
    /**
    Streams in the VertexData.
    */
    std::map<int, BufferAttribute> _vertexStreams;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif //__CC_VERTEX_INDEX_DATA_H__
