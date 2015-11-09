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

#ifndef __CC_PRIMITIVE_H__
#define __CC_PRIMITIVE_H__

#include "renderer/CCVertexIndexData.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class IndexBuffer;

/**@class Primitive
@brief
@~english
 Primitive can support sending points, lines and triangles to glpipeline, which is an abstraction
 of primitive data.
 * @~chinese 
 * Primitive����֧�ֵ�,�ߺ������ε���Ⱦ, ����Ⱦ����ͼԪ�ĳ���
 */
class CC_DLL Primitive : public Ref
{
public:
    /**@~english
     Create an instance of primitive.
     * @~chinese 
     * ����һ��Primitiveʵ����
     @param verts @~english VertexData used in the primitive.
     * @~chinese ͼԪʹ�õ�VertexData��
     @param indices @~english Optional index data, null will means that no indices needed.
     * @~chinese �������壬�����null����ʾû��������
     @param type @~english The type (Points, Lines, Triangles) used.
     * @~chinese openGL��ö�ٵ�ͼԪ����(�㡢�ߡ�������)��
     */
    static Primitive* create(VertexData* verts, IndexBuffer* indices, int type);
    /**@~english Get the vertexData. @~chinese �õ�VertexData��*/
    const VertexData* getVertexData() const;
    /**@~english Get the optional index data, will return null if index data is not used. @~chinese ��ѡ����������,�����ʹ���������ݽ�����null��*/
    const IndexBuffer* getIndexData() const;
    /**@~english Get the primitive type. @~chinese ͼԪ�����͡�*/
    int getType() const { return _type; }
    
    /**@~english called by rendering framework, will send the data to GLPipeline. @~chinese ����Ⱦ���,����GLPipeline�������ݡ�*/
    void draw();
    
    /**@~english Get the start index of primtive. @~chinese ���Ƶ���ʼ����λ�á�*/
    int getStart() const { return _start; }
    /**@~english Get the number of vertices or indices used for drawing. @~chinese ���ڻ��ƵĶ����������������У�����Ŀ��*/
    int getCount() const { return _count; }
    /**@~english Setter for the start index. @~chinese ���ÿ�ʼ������λ�á�*/
    void setStart(int start);
    /**@~english Setter for the count.  @~chinese ���û��ƵĶ���������ĸ�����*/
    void setCount(int count);
    
protected:
    Primitive();
    virtual ~Primitive();
    
    bool init(VertexData* verts, IndexBuffer* indices, int type);
    
protected:
    VertexData* _verts;
    IndexBuffer* _indices;
    int _start;
    int _count;
    int _type;
};

NS_CC_END

/**
 end of support group
 @}
 */
#endif //__CC_PRIMITIVE_H__
