/****************************************************************************
Copyright 2011 Jeff Lamarche
Copyright 2012 Goffredo Marocchi
Copyright 2012 Ricardo Quesada
Copyright 2012 cocos2d-x.org
Copyright 2013-2014 Chukong Technologies Inc.


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

#ifndef __CCGLPROGRAM_H__
#define __CCGLPROGRAM_H__

#include <unordered_map>
#include <string>

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "platform/CCGL.h"
#include "math/CCMath.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class GLProgram;
class Director;
//FIXME: these two typedefs would be deprecated or removed in version 4.0.
typedef void (*GLInfoFunction)(GLuint program, GLenum pname, GLint* params);
typedef void (*GLLogFunction) (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);

/**
@struct VertexAttrib
@brief
@~english VertexAttrib is a structure to encapsulate data got from glGetActiveAttrib. 
@~chinese VertexAttrib���ڷ�װ�������ԣ������Դ�glGetActiveAttrib�л�ȡ��
*/
struct VertexAttrib
{
    /**
    @~english Index of attribute, start from 0. 
    @~chinese ����������,��0��ʼ��
    */
    GLuint index;
    /**
    @~english Number of Data type in the attribute, could range from 1-4. 
    @~chinese ����ֵ����ĸ���,��Χ��1 - 4��
    */
    GLint size;
    /**
    @~english Data type of the attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc. 
    @~chinese ��������,������GL_FLOAT��GL_UNSIGNED_BYTE�ȵȡ�
    */
    GLenum type;
    /**
    @~english The string name in vertex shader. 
    @~chinese ��vertex shader�е��ַ���.
    */
    std::string name;
};
/**
@struct Uniform
@brief
@~english Uniform is a structure to encapsulate data got from glGetActiveUniform and glGetUniformLocation. 
@~chinese Uniform��һ���ṹ����������װ��glGetActiveUniform��glGetUniformLocation�л�õ����ݡ�
*/
struct Uniform
{
    /**
    @~english The place where the uniform placed, starts from 0. 
    @~chinese Uniform��shader�еĴ洢λ��,��0��ʼ��
    */
    GLint location;
    /**
    @~english Number of data type in Uniform. 
    @~chinese Unifrom��ֵ�е����ݸ�����
    */
    GLint size;
    /**
    @~english Data type of the Uniform. 
    @~chinese �������͡�
    */
    GLenum type;
    /**
    @~english String of the uniform name. 
    @~chinese Shader�е�Unifrom���֡�*/
    std::string name;
};

/** 
@class GLProgram
@brief
@~english 
 Class that implements a openGL Program


 * @~chinese
 * ��װopenGL Program����
 * 
 * 
 @since v2.0.0
 */
class CC_DLL GLProgram : public Ref
{
    friend class GLProgramState;
    friend class VertexAttribBinding;

public:
    /**
    @~english Enum the preallocated vertex attribute.  
    @~chinese ö��Ԥ�ȷ���Ķ������ԡ�*/
    enum
    {
        /**@~english Index 0 will be used as Position. @~chinese ����0��������λ�á�*/
        VERTEX_ATTRIB_POSITION,
        /**@~english Index 1 will be used as Color. @~chinese ָ��1����������ɫ��*/
        VERTEX_ATTRIB_COLOR,
        /**@~english Index 2 will be used as Tex coord unit 0. @~chinese ָ��2����������0���������ꡣ*/
        VERTEX_ATTRIB_TEX_COORD,
        /**@~english Index 3 will be used as Tex coord unit 1. @~chinese ָ��3����������1���������ꡣ*/
        VERTEX_ATTRIB_TEX_COORD1,
        /**@~english Index 4 will be used as Tex coord unit 2. @~chinese ָ��4����������2���������ꡣ*/
        VERTEX_ATTRIB_TEX_COORD2,
        /**@~english Index 5 will be used as Tex coord unit 3. @~chinese ָ��5����������3���������ꡣ*/
        VERTEX_ATTRIB_TEX_COORD3,
        /**@~english Index 6 will be used as Normal. @~chinese ָ��6�����������ߡ�*/
        VERTEX_ATTRIB_NORMAL,
        /**@~english Index 7 will be used as Blend weight for hardware skin. @~chinese ָ��7��������Blend Weight,������Ƥ���㡣*/
        VERTEX_ATTRIB_BLEND_WEIGHT,
        /**@~english Index 8 will be used as Blend index. @~chinese ָ��8��������Blend Index��������Ƥ���㡣*/
        VERTEX_ATTRIB_BLEND_INDEX,
        /**Index 9 will be used as tangent.*/
        VERTEX_ATTRIB_TANGENT,
        /**Index 10 will be used as Binormal.*/
        VERTEX_ATTRIB_BINORMAL,
        VERTEX_ATTRIB_MAX,

        // backward compatibility
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
    };

    /**@~english Preallocated uniform handle. @~chinese Ԥ�ȷ����uniform���.*/
    enum
    {
        /**@~english Ambient color. @~chinese ��������ɫ��*/
        UNIFORM_AMBIENT_COLOR,
        /**@~english Projection matrix. @~chinese ͶӰ����*/
        UNIFORM_P_MATRIX,
        /**@~english Model view matrix. @~chinese ModelView����*/
        UNIFORM_MV_MATRIX,
        /**@~english Model view projection matrix. @~chinese ModelView��ͶӰ���˾���*/
        UNIFORM_MVP_MATRIX,
        /**@~english Normal matrix. @~chinese ���ߵı任����*/
        UNIFORM_NORMAL_MATRIX,
        /**@~english Time. @~chinese ʱ�䡣*/
        UNIFORM_TIME,
        /**@~english sin(Time). @~chinese ʱ���sinֵ��*/
        UNIFORM_SIN_TIME,
        /**@~english cos(Time). @~chinese ʱ���cosֵ��*/
        UNIFORM_COS_TIME,
        /**@~english Random number. @~chinese �������*/
        UNIFORM_RANDOM01,
        /** @~english Sampler 0, used for texture. @~chinese ������ 0, �����������.*/
        UNIFORM_SAMPLER0,
        /** @~english Sampler 1, used for texture. @~chinese ������ 1, �����������.*/
        UNIFORM_SAMPLER1,
        /** @~english Sampler 2, used for texture. @~chinese ������ 2, �����������.*/
        UNIFORM_SAMPLER2,
        /** @~english Sampler 3, used for texture. @~chinese ������ 3, �����������.*/
        UNIFORM_SAMPLER3,
        UNIFORM_MAX,
    };

    /**
    @name Built Shader types
    @{
    */

    /**
    @~english Built in shader for 2d. Support Position, Texture and Color vertex attribute. 
    @~chinese ����shader��֧��λ�ã���ɫ���������ꡣ
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR;
    /**
    @~english Built in shader for 2d. Support Position, Texture and Color vertex attribute, but without multiply vertex by MVP matrix. 
    @~chinese ����shader��֧��λ�ã���ɫ����������,�����㲻��Ҫ����MVP����
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP;
    /**
    @~english Built in shader for 2d. Support Position, Texture vertex attribute, but include alpha test. 
    @~chinese ����shader��֧��λ�ã��������꣬����alpha���ԡ�
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST;
    /**
    @~english Built in shader for 2d. Support Position, Texture and Color vertex attribute, include alpha test and without multiply vertex by MVP matrix. 
    @~chinese ����shader��֧��λ�ã��������꣬����alpha���ԡ����㲻��Ҫ����MVP����
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV;
    /**
    @~english Built in shader for 2d. Support Position, Color vertex attribute. 
    @~chinese ����shader��֧��λ�ã���ɫ��
    */
    static const char* SHADER_NAME_POSITION_COLOR;
    /**
    @~english Built in shader for 2d. Support Position, Color, Texture vertex attribute. texture coordinate will used as point size. 
    @~chinese ����shader��֧��λ�ã���ɫ���������꣬��������ᱻ����point sizeʹ�ã����ڻ��㡣
    */
    static const char* SHADER_NAME_POSITION_COLOR_TEXASPOINTSIZE;
    /**
    @~english Built in shader for 2d. Support Position, Color vertex attribute, without multiply vertex by MVP matrix. 
    @~chinese ����shader��֧��λ�ã���ɫ�����㲻��Ҫ����MVP����
    */
    static const char* SHADER_NAME_POSITION_COLOR_NO_MVP;
    /**
    @~english Built in shader for 2d. Support Position, Texture vertex attribute. 
    @~chinese ����shader��֧��λ�ã��������ꡣ
    */
    static const char* SHADER_NAME_POSITION_TEXTURE;
    /**
    @~english Built in shader for 2d. Support Position, Texture vertex attribute. with a specified uniform as color 
    @~chinese ����shader��֧��λ�ã��������꣬��ɫͨ��uniformָ����
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_U_COLOR;
    /**
    @~english Built in shader for 2d. Support Position, Texture and Color vertex attribute. but alpha will be the multiplication of color attribute and texture. 
    @~chinese ����shader��֧��λ�ã���ɫ���������꣬����alpha����ɫ���Ժ�����ĳ�ֵ��
    */
    static const char* SHADER_NAME_POSITION_TEXTURE_A8_COLOR;
    /**
    @~english Built in shader for 2d. Support Position, with color specified by a uniform. 
    @~chinese ����shader��֧��λ�ã���ɫͨ��uniformָ����
    */
    static const char* SHADER_NAME_POSITION_U_COLOR;
    /**
    @~english Built in shader for draw a sector with 90 degrees with center at bottom left point. 
    @~chinese ����shader�����ڻ�һ��90���Σ�Բ�������½ǡ�
    */
    static const char* SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR;

    /**
    @~english Built in shader for ui effects.
    @~chinese ����shader��������ȾUI�ı��Ч����
    */
    static const char* SHADER_NAME_POSITION_GRAYSCALE;
    /** @~english
        Built in shader for label.
     * @~chinese 
     * ����shader������Label����Ⱦ��
    */
    static const char* SHADER_NAME_LABEL_NORMAL;
    /** @~english
        Built in shader for label outline effects.
     * @~chinese 
     * ����shader������Label��ߵ���Ⱦ��
    */
    static const char* SHADER_NAME_LABEL_OUTLINE;
    /** @~english
        Built in shader for label based on DISTANCEFIELD.
     * @~chinese 
     * ����shader�����ڻ���DISTANCEFIELD���Ƶ�Label����Ⱦ��
    */
    static const char* SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL;
    /** @~english
        Built in shader for label based on DISTANCEFIELD.
     * @~chinese 
     * ����shader�����ڻ���DISTANCEFIELD���Ƶ�Label�Ĺ���Ч������Ⱦ��
    */
    static const char* SHADER_NAME_LABEL_DISTANCEFIELD_GLOW;

    /**
    @~english Built in shader used for 3D, support Position vertex attribute, with color specified by a uniform. 
    @~chinese ����shader��֧��λ�á���ɫͨ��uniformָ����
    */
    static const char* SHADER_3D_POSITION;
    /**
    @~english Built in shader used for 3D, support Position and Texture vertex attribute, with color specified by a uniform. 
    @~chinese ����shader��֧��λ�ã��������ꡣ��ɫͨ��uniformָ����
    */
    static const char* SHADER_3D_POSITION_TEXTURE;
    /**@~english
    Built in shader used for 3D, support Position (Skeletal animation by hardware skin) and Texture vertex attribute,
    with color specified by a uniform.
     * @~chinese 
     * ����shader��֧��λ�ã��������꣬��Ӳ������Ƥ����ɫͨ��uniformָ����
    */
    static const char* SHADER_3D_SKINPOSITION_TEXTURE;
    /**@~english
    Built in shader used for 3D, support Position and Normal vertex attribute, used in lighting. with color specified by a uniform.
     * @~chinese 
     * ����shader������3D������Ⱦ��֧�ֶ��㣬���ߡ���ɫͨ��uniformָ����
    */
    static const char* SHADER_3D_POSITION_NORMAL;
    /**@~english
    Built in shader used for 3D, support Position, Normal, Texture vertex attribute, used in lighting. with color specified by a uniform.
     * @~chinese 
     * ����shader������3D������Ⱦ��֧��λ�ã����ߣ��������ꡣ��ɫͨ��uniformָ����
    */
    static const char* SHADER_3D_POSITION_NORMAL_TEXTURE;
    /**@~english
    Built in shader used for 3D, support Position(skeletal animation by hardware skin), Normal, Texture vertex attribute,
    used in lighting. with color specified by a uniform.
     * @~chinese 
     * ����shader������3D������Ⱦ��֧�ֶ��㣬���ߣ��������꣬��Ӳ������Ƥ����ɫͨ��uniformָ����
    */
    static const char* SHADER_3D_SKINPOSITION_NORMAL_TEXTURE;
    /**@~english
    Built in shader used for 3D, support Position, Bumped Normal, Texture vertex attribute, used in lighting. with color specified by a uniform.
    */
    static const char* SHADER_3D_POSITION_BUMPEDNORMAL_TEXTURE;
    /**
    Built in shader used for 3D, support Position(skeletal animation by hardware skin), Bumped Normal, Texture vertex attribute,
    used in lighting. with color specified by a uniform.
    */
    static const char* SHADER_3D_SKINPOSITION_BUMPEDNORMAL_TEXTURE;
    /**
    Built in shader for particles, support Position and Texture, with a color specified by a uniform.
     * @~chinese 
     * ����shader������3D���ӣ���ͼ����Ⱦ��
    */
    static const char* SHADER_3D_PARTICLE_TEXTURE;
    /**@~english
    Built in shader for particles, support Position, with a color specified by a uniform.
     * @~chinese 
     * ����shader������3D���ӣ���ɫ����Ⱦ��
    */
    static const char* SHADER_3D_PARTICLE_COLOR;

    /**@~english
     Built in shader for skybox
     * @~chinese 
     * ����shader��������պС�
     */
    static const char* SHADER_3D_SKYBOX;

    /**@~english
     Built in shader for terrain
     * @~chinese 
     * ����shader�����ڵ��Ρ�
     */
    static const char* SHADER_3D_TERRAIN;
    
    /**@~english
     Built in shader for camera clear
     * @~chinese 
     * ����shader������camera���������
     */
    static const char* SHADER_CAMERA_CLEAR;
    /**
    end of built shader types.
    @}
    */

    /**
    @name Built uniform names
    @{
    */
    /**@~english Ambient Color uniform. @~chinese Uniformֵ: ��������ɫ��*/
    static const char* UNIFORM_NAME_AMBIENT_COLOR;
    /**@~english Projection Matrix uniform. @~chinese Uniformֵ: ͶӰ����*/
    static const char* UNIFORM_NAME_P_MATRIX;
    /**@~english Model view matrix uniform. @~chinese Uniformֵ: ModelView����*/
    static const char* UNIFORM_NAME_MV_MATRIX;
    /**@~english Model view projection uniform. @~chinese Uniformֵ: ModelView��ͶӰ��������ˡ�*/
    static const char* UNIFORM_NAME_MVP_MATRIX;
    /**@~english Normal matrix uniform. @~chinese Uniformֵ: ���ߵı任����*/
    static const char* UNIFORM_NAME_NORMAL_MATRIX;
    /**@~english Time uniform. @~chinese Uniformֵ: ʱ�䡣*/
    static const char* UNIFORM_NAME_TIME;
    /**@~english Sin time uniform. @~chinese Uniformֵ: ʱ���sinֵ��*/
    static const char* UNIFORM_NAME_SIN_TIME;
    /**@~english Cos time uniform. @~chinese Uniformֵ: ʱ���cosֵ��*/
    static const char* UNIFORM_NAME_COS_TIME;
    /**@~english Random number uniform. @~chinese Uniformֵ: �������*/
    static const char* UNIFORM_NAME_RANDOM01;
    /**@~englishSampler uniform 0, used for textures. @~chinese Uniformֵ: ������0��*/
    static const char* UNIFORM_NAME_SAMPLER0;
    /**@~englishSampler uniform 1, used for textures. @~chinese Uniformֵ: ������1��*/
    static const char* UNIFORM_NAME_SAMPLER1;
    /**@~englishSampler uniform 2, used for textures. @~chinese Uniformֵ: ������2��*/
    static const char* UNIFORM_NAME_SAMPLER2;
    /**@~englishSampler uniform 3, used for textures. @~chinese Uniformֵ: ������3��*/
    static const char* UNIFORM_NAME_SAMPLER3;
    /**@~english Alpha test value uniform. @~chinese Uniformֵ: Alpha Test��*/
    static const char* UNIFORM_NAME_ALPHA_TEST_VALUE;
    /**
    end of Built uniform names
    @}
    */

    /**
        @name Built Attribute names
        @{
    */
    /**@~english Attribute color. @~chinese ��ɫ���ԡ�*/
    static const char* ATTRIBUTE_NAME_COLOR;
    /**@~english Attribute position. @~chinese λ�����ԡ�*/
    static const char* ATTRIBUTE_NAME_POSITION;
    /**@~english Attribute Texcoord 0. @~chinese ������������0.*/
    static const char* ATTRIBUTE_NAME_TEX_COORD;
    /**@~english Attribute Texcoord 1. @~chinese ������������1.*/
    static const char* ATTRIBUTE_NAME_TEX_COORD1;
    /**@~english Attribute Texcoord 2. @~chinese ������������2.*/
    static const char* ATTRIBUTE_NAME_TEX_COORD2;
    /**@~english Attribute Texcoord 3. @~chinese ������������3.*/
    static const char* ATTRIBUTE_NAME_TEX_COORD3;

    /**@~english Attribute normal. @~chinese �������ԡ�*/
    static const char* ATTRIBUTE_NAME_NORMAL;
    /**@~english Attribute blend weight. @~chinese Blend Weight���ԡ�*/
    static const char* ATTRIBUTE_NAME_BLEND_WEIGHT;
    /**@~english Attribute blend index. @~chinese Blend index���ԡ�*/
    static const char* ATTRIBUTE_NAME_BLEND_INDEX;
    /**Attribute blend tangent.*/
    static const char* ATTRIBUTE_NAME_TANGENT;
    /**Attribute blend binormal.*/
    static const char* ATTRIBUTE_NAME_BINORMAL;
    /**
    end of Built Attribute names
    @}
    */

    /**@~english Constructor. @~chinese ���캯����*/
    GLProgram();
    /**@~english Destructor. @~chinese ����������*/
    virtual ~GLProgram();

    /** @~english
    Create the GLProgram with a vertex and fragment with bytes array.
     * @~chinese 
     * �Ӹ�����Դ�����ַ����д���GLProgram��
     @param vShaderByteArray @~english The source code of vertex shader. @~chinese VertexShaderԴ����.
     @param fShaderByteArray @~english The source code of fragment shader. @~chinese FragmentShaderԴ����.
     @return @~english The result GLProgram. @~chinese ������GLProgram��
     * @js initWithString.
     * @lua initWithString.
     */
    static GLProgram* createWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    /** @~english
    Init the GLProgram with a vertex and fragment with bytes array.
     * @~chinese 
     * �Ӹ�����Դ�����ַ����г�ʼ��GLProgram��
     @param vShaderByteArray @~english The source code of vertex shader. @~chinese VertexShaderԴ����.
     @param fShaderByteArray @~english The source code of fragment shader. @~chinese FragmentShaderԴ����.
     @return @~english The GLprogram is inited correctly or not. @~chinese GLProgram�Ƿ񱻳ɹ���ʼ����
     */
    bool initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    /** @~english
    Create the GLProgram with a vertex and fragment with bytes array.
     * @~chinese 
     * �Ӹ�����Դ�����ַ����д���GLProgram��
     @param vShaderByteArray @~english The source code of vertex shader. @~chinese VertexShaderԴ����.
     @param fShaderByteArray @~english The source code of fragment shader. @~chinese FragmentShaderԴ����.
     @param compileTimeDefines @~english compile macro and defines for shader. @~chinese ����ʱ��Ԥ����ֵ�ͺꡣ
     @return @~english The result GLProgram. @~chinese ������GLProgram��
     */
    static GLProgram* createWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray, const std::string& compileTimeDefines);
    /** @~english
    Init the GLProgram with a vertex and fragment with bytes array.
     * @~chinese 
     * �Ӹ�����Դ�����ַ����г�ʼ��GLProgram��
     @param vShaderByteArray @~english The source code of vertex shader. @~chinese VertexShaderԴ����.
     @param fShaderByteArray @~english The source code of fragment shader. @~chinese FragmentShaderԴ����.
     @param compileTimeDefines @~english compile macro and defines for shader. @~chinese ����ʱ��Ԥ����ֵ�ͺꡣ
     @return @~english The GLprogram is inited correctly or not. @~chinese GLProgram�Ƿ񱻳ɹ���ʼ����
     */
    bool initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray, const std::string& compileTimeDefines);

    /** @~english
    Create the GLProgram with a vertex and fragment file.
     * @~chinese 
     * �Ӹ�����Դ�����ļ��д���GLProgram��
     @param vShaderFilename @~english The source code file of vertex shader. @~chinese VertexShaderԴ�����ļ�.
     @param fShaderFilename @~english The source code file of fragment shader. @~chinese FragmentShaderԴ�����ļ�.
     @return @~english The result GLProgram. @~chinese ������GLProgram��
     * @js init
     * @lua init
     */
    static GLProgram* createWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename);
    /** @~english
    Init the GLProgram with a vertex and fragment file.
     * @~chinese 
     * �Ӹ�����Դ�����ļ��г�ʼ��GLProgram��
     @param vShaderFilename @~english The source code file of vertex shader. @~chinese VertexShaderԴ�����ļ�.
     @param fShaderFilename @~english The source code file of fragment shader. @~chinese FragmentShaderԴ�����ļ�.
     @return @~english The GLprogram is inited correctly or not. @~chinese GLProgram�Ƿ񱻳ɹ���ʼ����
     */
    bool initWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename);
    /** @~english
    Create the GLProgram with a vertex and fragment file.
     * @~chinese 
     * �Ӹ�����Դ�����ļ��д���GLProgram��
     @param vShaderFilename @~english The source code file of vertex shader. @~chinese VertexShaderԴ�����ļ�.
     @param fShaderFilename @~english The source code file of fragment shader. @~chinese FragmentShaderԴ�����ļ�.
     @param compileTimeDefines @~english compile macro and defines for shader. @~chinese ����ʱ��Ԥ����ֵ�ͺꡣ
     @return @~english The result GLProgram. @~chinese ������GLProgram��
     */
    static GLProgram* createWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename, const std::string& compileTimeDefines);
        /** @~english
    Init the GLProgram with a vertex and fragment file.
     * @~chinese 
     * �Ӹ�����Դ�����ļ��г�ʼ��GLProgram��
     @param vShaderFilename @~english The source code file of vertex shader. @~chinese VertexShaderԴ�����ļ�.
     @param fShaderFilename @~english The source code file of fragment shader. @~chinese FragmentShaderԴ�����ļ�.
     @param compileTimeDefines @~english compile macro and defines for shader. @~chinese ����ʱ��Ԥ����ֵ�ͺꡣ
     @return @~english The GLprogram is inited correctly or not. @~chinese GLProgram�Ƿ񱻳ɹ���ʼ����
     */
    bool initWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename, const std::string& compileTimeDefines);

    /**
    @~english Get the uniform by string name in shader, return null if it does not exist.
    @~chinese �������ּ���Uniform, ��������ڣ�������null
    */
    Uniform* getUniform(const std::string& name);
    /**
    @~english Get the vertex attribute by string name in shader, return null if it does not exist.
    @~chinese �������ּ�����������, ��������ڣ�������null
    */
    VertexAttrib* getVertexAttrib(const std::string& name);

    /**  
    @~english It will add a new attribute to the shader by calling glBindAttribLocation.  
    @~chinese ����glBindAttribLocation�����������԰󶨸�������λ�á�
    @param attributeName @~english the name of vertex attribute. @~chinese �������Ե����֡�
    @param index @~english the index location. @~chinese ������λ�á�
    */
    void bindAttribLocation(const std::string& attributeName, GLuint index) const;

    /** @~english Calls glGetAttribLocation.  @~chinese ����glGetAttribLocation��*/
    GLint getAttribLocation(const std::string& attributeName) const;

    /** @~english Calls glGetUniformLocation().  @~chinese ����glGetUniformLocation()��*/
    GLint getUniformLocation(const std::string& attributeName) const;

    /** @~english links the glProgram  @~chinese ����openGL Program��*/
    bool link();
    /** @~english it will call glUseProgram()  @~chinese ��������glUseProgram()��*/
    void use();
    /** @~english update the locations for built in uniforms.
    @~chinese ����Ԥ�����Uniform������λ�á�*/
    void updateUniforms();

    /** 
    @~english calls retrieves the named uniform location for this shader program.  
    @~chinese ��������ȥ����Uniform��λ�á�
    */
    GLint getUniformLocationForName(const char* name) const;

    /** @~english calls glUniform1i only if the values are different than the previous call for this same shader program.
     * @~chinese ������ֵ�и���ʱ������glUniform1i��
     * @js setUniformLocationI32
     * @lua setUniformLocationI32
     */
    void setUniformLocationWith1i(GLint location, GLint i1);

    /** 
    @~english calls glUniform2i only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniform2i��
    */
    void setUniformLocationWith2i(GLint location, GLint i1, GLint i2);

    /** 
    @~english calls glUniform3i only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniform3i��
    */
    void setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3);

    /** 
    @~english calls glUniform4i only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniform4i��
    */
    void setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4);

    /** 
    @~english calls glUniform2iv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniform2iv��
    */
    void setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform3iv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniform3iv��
    */
    void setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform4iv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniform4iv��
    */

    void setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** @~english calls glUniform1f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @~chinese ������ֵ�и���ʱ������glUniform1f��
     * ��js��lua,��ʹ��setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith1f(GLint location, GLfloat f1);

    /** @~english calls glUniform2f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @~chinese ������ֵ�и���ʱ������glUniform2f��
     * ��js��lua,��ʹ��setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2);

    /** @~english calls glUniform3f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @~chinese ������ֵ�и���ʱ������glUniform3f��
     * ��js��lua,��ʹ��setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);

    /** @~english calls glUniform4f only if the values are different than the previous call for this same shader program.
     * In js or lua,please use setUniformLocationF32
     * @~chinese ������ֵ�и���ʱ������glUniform4f��
     * ��js��lua,��ʹ��setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

    /** 
    @~english calls glUniformfv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniformfv��
    */
    void setUniformLocationWith1fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform2fv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniform2fv��
    */
    void setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform3fv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniform3fv��
    */
    void setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 
    @~english calls glUniform4fv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniform4fv��
    */
    void setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 
    @~english calls glUniformMatrix2fv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniformMatrix2fv��
    */
    void setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);

    /** 
    @~english calls glUniformMatrix3fv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniformMatrix3fv��
    */
    void setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);

    /** 
    @~english calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program.  
    @~chinese ������ֵ�и���ʱ������glUniformMatrix4fv��
    */
    void setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);

    /**@~english
     Update the builtin uniforms if they are different than the previous call for this same shader program.
     * @~chinese 
     * ����Shader��Ԥ�ȶ����Uniform,������ǵ������и��¡�
     */
    void setUniformsForBuiltins();
    /**@~english
     Update the builtin uniforms if they are different than the previous call for this same shader program.
     * @~chinese 
     * ����Shader��Ԥ�ȶ����Uniform,������ǵ������и��¡�
     @param modelView @~english modelView matrix applied to the built in uniform of the shader.
     * @~chinese ������Ҫ��ModelView����
     */
    void setUniformsForBuiltins(const Mat4 &modelView);

    /** @~english returns the vertexShader error log  @~chinese ����vertexShader������־*/
    std::string getVertexShaderLog() const;

    /** @~english returns the fragmentShader error log  @~chinese ����fragmentShader������־*/
    std::string getFragmentShaderLog() const;

    /** @~english returns the program error log  @~chinese ���س��������־*/
    std::string getProgramLog() const;

    /** @~english Reload all shaders, this function is designed for android
    when opengl context lost, so don't call it.
     * @~chinese ���¼�������Shader,���������Ϊandroid��Ƶ�
     * ��opengl�����Ķ�ʧ,���Բ�Ҫ���е��á�
    */
    void reset();
    /*
    @~english Get the built in openGL handle of the program. 
    @~chinese �õ�openGL Program�ľ����
    @return @~english openGL Program handle.
    @~chinese openGL Program�ľ����
    */
    inline const GLuint getProgram() const { return _program; }

    //DEPRECATED
    CC_DEPRECATED_ATTRIBUTE bool initWithVertexShaderByteArray(const GLchar* vertexByteArray, const GLchar* fragByteArray)
    { return initWithByteArrays(vertexByteArray, fragByteArray); }
    CC_DEPRECATED_ATTRIBUTE bool initWithVertexShaderFilename(const std::string &vertexFilename, const std::string& fragFilename)
    { return initWithFilenames(vertexFilename, fragFilename); }
    CC_DEPRECATED_ATTRIBUTE void addAttribute(const std::string &attributeName, GLuint index) const { return bindAttribLocation(attributeName, index); }


protected:
    /**@~english
    Update the uniform data in location.
     * @~chinese 
     * ����Uniform���ݵ�λ�á�
    @param location @~english The location of the uniform.
     * @~chinese Uniform��λ�á�
    @param data @~english Updated data.
     * @~chinese ���µ����ݡ�
    @oaram @~english bytes Data length in bytes to update.
     * @~chinese Ҫ���µ����ݳ��ȣ����ֽ�Ϊ��λ��
    */
    bool updateUniformLocation(GLint location, const GLvoid* data, unsigned int bytes);
    /**@~english Get a general description of the shader. @~chinese ��ɫ���ļ�������*/
    virtual std::string getDescription() const;

    /**@~english Bind the predefined vertex attributes to their specific slot. @~chinese ���������԰󶨵�Ԥ�ȶ����λ�á�*/
    void bindPredefinedVertexAttribs();
    /**@~english Parse user defined Vertex Attributes automatically. @~chinese �Զ������û�����Ķ������ԡ�*/
    void parseVertexAttribs();
    /**@~english Parse user defined uniform automatically. @~chinese �Զ������û������Uniform��*/
    void parseUniforms();
    /**@~english Compile the shader sources. @~chinese ����Shader��Դ���롣*/
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source, const std::string& convertedDefines);
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);

    /** OpenGL handle for program. */
    GLuint            _program;
    /** OpenGL handle for vertex shader.*/
    GLuint            _vertShader;
    /** OpenGL handle for fragment shader. */
    GLuint            _fragShader;
    /** Built in uniforms.*/
    GLint             _builtInUniforms[UNIFORM_MAX];
    /** Indicate whether it has a offline shader compiler or not.*/
    bool              _hasShaderCompiler;

    inline void clearShader();

    struct flag_struct {
        unsigned int usesTime:1;
        unsigned int usesNormal:1;
        unsigned int usesMVP:1;
        unsigned int usesMV:1;
        unsigned int usesP:1;
        unsigned int usesRandom:1;
        // handy way to initialize the bitfield
        flag_struct() { memset(this, 0, sizeof(*this)); }
    } _flags;

    /** User defined Uniforms.*/
    std::unordered_map<std::string, Uniform> _userUniforms;
    /** User defined vertex attributes.*/
    std::unordered_map<std::string, VertexAttrib> _vertexAttribs;
    /** Hash value of uniforms for quick access.*/
    std::unordered_map<GLint, std::pair<GLvoid*, unsigned int>> _hashForUniforms;
    //cached director pointer for calling
    Director* _director;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif /* __CCGLPROGRAM_H__ */
