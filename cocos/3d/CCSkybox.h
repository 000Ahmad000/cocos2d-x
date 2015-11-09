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
 ****************************************************************************/

#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "base/ccTypes.h"
#include "platform/CCPlatformMacros.h"
#include "renderer/CCCustomCommand.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

/**
    @addtogroup _3d
    @{
*/

class TextureCube;

/** @class Skybox
    @brief @~english Sky box technology usually used to simulate infinity sky, mountains and other phenomena.
    @~chinese ��պм���ͨ������ģ�����޵���գ�ɽ������������
*/
class CC_DLL Skybox : public Node
{
public:
    CREATE_FUNC(Skybox);

    /** @~english create skybox from 6 textures.
        @~chinese ʹ��6����������պС�
        @param positive_x @~english  texture for the right side of the texture cube face. @~chinese ��������Ҳ�����
        @param negative_x @~english  texture for the left side of the texture cube face. @~chinese ��������������
        @param positive_y @~english  texture for the top side of the texture cube face @~chinese ��������ϲ�����
        @param negative_y @~english  texture for the bottom side of the texture cube face @~chinese ��������²�����
        @param positive_z @~english  texture for the forward side of the texture cube face. @~chinese �������ǰ������
        @param negative_z @~english  texture for the rear side of the texture cube face. @~chinese ������ĺ������
        @return @~english  A new skybox inited with given parameters. @~chinese ����һ���µ�Skybox��
    */
    static Skybox* create(const std::string& positive_x, const std::string& negative_x,
                          const std::string& positive_y, const std::string& negative_y,
                          const std::string& positive_z, const std::string& negative_z);

    /** @~english texture getter and setter
        @~chinese �����getter��setter
        @param textureCube @~english  cube texture @~chinese ������ͼ
    */
    void setTexture(TextureCube* textureCube);

    /** @~english draw Skybox object
        @~chinese ������������
    */
    virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;

    /** @~english reload sky box after GLESContext reconstructed.
        @~chinese glescontext��װ���ؽ���պС�
    */
    void reload();

CC_CONSTRUCTOR_ACCESS:
    /** @~english Constructor.
        @~chinese ���캯����
    */
    Skybox();

    /** @~english Destructor.
        @~chinese ����������
    */
    virtual ~Skybox();

    /** @~english init Skybox.
        @~chinese ��ʼ��Skybox��
    */
    virtual bool init() override;
    
    /** @~english initialize with texture path
        @~chinese ����·����ʼ��
    */
    bool init(const std::string& positive_x, const std::string& negative_x,
              const std::string& positive_y, const std::string& negative_y,
              const std::string& positive_z, const std::string& negative_z);

protected:
    void initBuffers();

    void onDraw(const Mat4& transform, uint32_t flags);

    GLuint      _vao;
    GLuint      _vertexBuffer;
    GLuint      _indexBuffer;

    CustomCommand _customCommand;

    TextureCube*  _texture;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Skybox);
};

// end of 3d group
/// @}

NS_CC_END

#endif // __SKYBOX_H__
