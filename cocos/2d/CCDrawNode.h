/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Code copied & pasted from SpacePatrol game https://github.com/slembcke/SpacePatrol
 *
 * Renamed and added some changes for cocos2d
 *
 */

#ifndef __CCDRAWNODES_CCDRAW_NODE_H__
#define __CCDRAWNODES_CCDRAW_NODE_H__

#include "2d/CCNode.h"
#include "base/ccTypes.h"
#include "renderer/CCCustomCommand.h"
#include "math/CCMath.h"

NS_CC_BEGIN

static const int DEFAULT_LINE_WIDTH = 2;

class PointArray;
/**
 * @addtogroup _2d
 * @{
 */


/** @class DrawNode
 * @brief @~english Node that draws dots, segments and polygons.
 * Faster than the "drawing primitives" since they draws everything in one single batch.
 * @~chinese ���Ƶ㡢�߶κͶ���εĽڵ㡣
 * ������ʹ����"������"��Batch draw������������Ƶ㡢�߶Ρ�����ζ�Ҫ�ȡ�drawing primitives���졣
 * @since v2.1
 */
class CC_DLL DrawNode : public Node
{
public:
    /** @~english creates and initialize a DrawNode node.
     * @~chinese ��������ʼ��DrawNode�ڵ�.
     * @return @~english Return an autorelease object.
     * @~chinese ����һ���Զ��ͷŶ���.
     */
    static DrawNode* create(int defaultLineWidth = DEFAULT_LINE_WIDTH);
    
    /** @~english Draw a point.
     *
     * @~chinese ��һ���㡣
     * 
     * @param point @~english A Vec2 point.
     * @~chinese һ��Vec2���͵ĵ�
     * @param pointSize @~english The point size.
     * @~chinese ��Ĵ�С
     * @param color @~english The point color.
     * @~chinese �����ɫ
     * @js NA
     */
    void drawPoint(const Vec2& point, const float pointSize, const Color4F &color);
    
    /** @~english Draw a group point.
     *
     * @~chinese ��һ��㡣
     * 
     * @param position @~english A Vec2 pointer.
     * @~chinese һ��Vec2ָ�롣
     * @param numberOfPoints @~english The number of points.
     * @~chinese ���������
     * @param color @~english The point color.
     * @~chinese �����ɫ��
     * @js NA
     */
    void drawPoints(const Vec2 *position, unsigned int numberOfPoints, const Color4F &color);
    
    /** @~english Draw a group point.
     *
     * @~chinese ��һ��㡣
     * 
     * @param position @~english A Vec2 pointer.
     * @~chinese һ��Vec2ָ�롣
     * @param numberOfPoints @~english The number of points.
     * @~chinese ���������
     * @param pointSize @~english The point size.
     * @~chinese ��Ĵ�С��
     * @param color @~english The point color.
     * @~chinese �����ɫ��
     * @js NA
     */
    void drawPoints(const Vec2 *position, unsigned int numberOfPoints, const float pointSize, const Color4F &color);
    
    /** @~english Draw an line from origin to destination with color. 
     * 
     * @~chinese ʹ��ָ����ɫ��һ������ʼ�㵽Ŀ�ĵص���ߡ�
     * 
     * @param origin @~english The line origin.
     * @~chinese ��ʼ�������
     * @param destination @~english The line destination.
     * @~chinese Ŀ�ĵص������
     * @param color @~english The line color.
     * @~chinese �ߵ���ɫ��
     * @js NA
     */
    void drawLine(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** @~english Draws a rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @~chinese ����һ����ʼ�������Ŀ�ĵص����껭һ�����Σ�����ĵ�λ�ǡ�Point��
     * ��ʼ�������Ŀ�ĵص����겻����ͬ��
     * 
     * @param origin @~english The rectangle origin.
     * @~chinese ���ε�ԭ�����ꡣ
     * @param destination @~english The rectangle destination.
     * @~chinese ���ε�Ŀ�ĵص����ꡣ
     * @param color @~english The rectangle color.
     * @~chinese ���ε���ɫ��
     */
    void drawRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** @~english Draws a polygon given a pointer to point coordinates and the number of vertices measured in points.
     * The polygon can be closed or open.
     *
     * @~chinese ����һ��ָ��һ��������ָ�����������������ƶ����
     * ����ο��Ապϣ�Ҳ���Բ��պϡ�
     * 
     * @param poli @~english A pointer to point coordinates.
     * @~chinese һ��ָ��һ��������ָ��
     * @param numberOfPoints @~english The number of vertices measured in points.
     * @~chinese ���������.
     * @param closePolygon @~english The polygon can be closed or open.
     * @~chinese ������Ƿ�պ�
     * @param color @~english The polygon color.
     * @~chinese ����ε���ɫ��
     */
    void drawPoly(const Vec2 *poli, unsigned int numberOfPoints, bool closePolygon, const Color4F &color);
    
    /** @~english Draws a circle given the center, radius, number of segments and a border color.
     *
     * @~chinese ����Բ������,�뾶���߶��������߶���ɫ������һ��Բ�����Ҫ���ƴ����ɫ��Բ����ʹ�� drawSolidCircle������
     * 
     * @param center @~english The circle center point.
     * @~chinese Բ���ĵ㡣
     * @param radius @~english The circle rotate of radius.
     * @~chinese Բ�İ뾶
     * @param angle  @~english The circle angle.
     * @~chinese Բ�ĽǶ�
     * @param segments @~english The number of segments.
     * @~chinese �߶ε�������
     * @param drawLineToCenter @~english Whether or not draw the line from the origin to center.
     * @~chinese �Ƿ��ԭ�������ĵ㻭һ���ߡ�
     * @param scaleX @~english The scale value in x.
     * @~chinese x������ֵ��
     * @param scaleY @~english The scale value in y.
     * @~chinese y������ֵ��
     * @param color @~english Set the circle color.
     * @~chinese Բ����ɫ��
     */
    void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY, const Color4F &color);
    
    /** @~english Draws a circle given the center, radius and number of segments.
     *
     * @~chinese ����Բ������,�뾶���߶�����������һ��Բ��
     * 
     * @param center @~english The circle center point.
     * @~chinese Բ���ĵ㡣
     * @param radius @~english The circle rotate of radius.
     * @~chinese Բ�İ뾶
     * @param angle  @~english The circle angle.
     * @~chinese Բ�ĽǶ�
     * @param segments @~english The number of segments.
     * @~chinese �߶ε�������
     * @param drawLineToCenter @~english Whether or not draw the line from the origin to center.
     * @~chinese �Ƿ��ԭ�������ĵ㻭һ����
     * @param color @~english Set the circle color.
     * @~chinese Բ����ɫ
     */
    void drawCircle(const Vec2 &center, float radius, float angle, unsigned int segments, bool drawLineToCenter, const Color4F &color);
    
    /** @~english Draws a quad bezier path.
     *
     * @~chinese ����һ���Ĵα���������·����
     * 
     * @param origin @~english The origin of the bezier path.
     * @~chinese ����������·����ԭ�㡣
     * @param control @~english The control of the bezier path.
     * @~chinese ���������ߵĿ��Ƶ㡣
     * @param destination @~english The destination of the bezier path.
     * @~chinese ���������ߵ��յ�
     * @param segments @~english The The number of segments.
     * @~chinese �߶ε�������
     * @param color @~english Set the quad bezier color.
     * @~chinese �����Ĵα��������ߵ���ɫ��
     */
    void drawQuadBezier(const Vec2 &origin, const Vec2 &control, const Vec2 &destination, unsigned int segments, const Color4F &color);

    /** @~english Draw a cubic bezier curve with color and number of segments
     *
     * @~chinese ʹ�ø����������߶κ���ɫ����һ�����α��������ߡ�
     * 
     * @param origin @~english The origin of the bezier path.
     * @~chinese ����������·����ԭ�㡣
     * @param control1 @~english The first control of the bezier path.
     * @~chinese ����������·���ĵ�һ�����Ƶ㡣
     * @param control2 @~english The second control of the bezier path.
     * @~chinese ����������·���ĵڶ������Ƶ㡣
     * @param destination @~english The destination of the bezier path.
     * @~chinese ����������·����Ŀ�ĵص㡣
     * @param segments @~english The The number of segments.
     * @~chinese �߶ε�������
     * @param color @~english Set the cubic bezier color.
     * @~chinese �������α��������ߵ���ɫ��
     */
    void drawCubicBezier(const Vec2 &origin, const Vec2 &control1, const Vec2 &control2, const Vec2 &destination, unsigned int segments, const Color4F &color);
    
    /** @~english Draws a Cardinal Spline path.
     *
     * @~chinese ����һ����������·����
     * 
     * @param config @~english A array point.
     * @~chinese һ�������顣
     * @param tension @~english The tension of the spline.
     * @~chinese ������������
     * @param segments @~english The The number of segments.
     * @~chinese �߶ε�������
     * @param color @~english Set the Spline color.
     * @~chinese ������������ɫ��
     */
    void drawCardinalSpline(PointArray *config, float tension,  unsigned int segments, const Color4F &color);
    
    /** @~english Draws a Catmull Rom path.
     *
     * @~chinese ����һ������Ī����(Catmull Rom)·����
     * 
     * @param points @~english A point array  of control point.
     * @~chinese һ�����Ƶ����顣
     * @param segments @~english The The number of segments.
     * @~chinese �߶ε�������
     * @param color @~english The Catmull Rom color.
     * @~chinese ����Ī���޵���ɫ��
     */
    void drawCatmullRom(PointArray *points, unsigned int segments, const Color4F &color);
    
    /** @~english draw a dot at a position, with a given radius and color. 
     *
     * @~chinese �ڸ�������㡢�뾶����ɫֵ��һ���㡣
     * 
     * @param pos @~english The dot center.
     * @~chinese �����ġ�
     * @param radius @~english The dot radius.
     * @~chinese ��뾶��
     * @param color @~english The dot color.
     * @~chinese �����ɫ��
     */
    void drawDot(const Vec2 &pos, float radius, const Color4F &color);
    
    /** @~english Draws a rectangle with 4 points.
     *
     * @~chinese ��һ������4������ľ���
     * 
     * @param p1 @~english The rectangle vertex point.
     * @~chinese ���εĶ��㡣
     * @param p2 @~english The rectangle vertex point.
     * @~chinese ���εĶ��㡣
     * @param p3 @~english The rectangle vertex point.
     * @~chinese ���εĶ��㡣
     * @param p4 @~english The rectangle vertex point.
     * @~chinese ���εĶ��㡣
     * @param color @~english The rectangle color.
     * @~chinese ���ε���ɫ��
     */
    void drawRect(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2& p4, const Color4F &color);
    
    /** @~english Draws a solid rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @~chinese ʹ�ø�����ԭ���Ŀ�ĵص����һ��ʵ�ľ��Ρ�
     * ԭ���Ŀ�ĵص㲻������ͬ��x��y���ꡣ
     * 
     * @param origin @~english The rectangle origin.
     * @~chinese ���ε�ԭ�㡣
     * @param destination @~english The rectangle destination.
     * @~chinese ���ε�Ŀ�ĵء�
     * @param color @~english The rectangle color.
     * @~chinese ���ε���ɫ��
     * @js NA
     */
    void drawSolidRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** @~english Draws a solid polygon given with a pointer to coordinates, the number of vertices measured in points, and a color.
     *
     * @~chinese ����һ������㻭һ��ʵ�Ķ����,�������ݰ�����������ɫ.
     * 
     * @param poli @~english A pointer to Vec2 coordinates.
     * @~chinese һ��ָ��Vec2�����ָ�롣
     * @param numberOfPoints @~english The number of vertices measured in points.
     * @~chinese ���������,��λ�ǡ�Point��
     * @param color @~english The solid polygon color.
     * @~chinese ʵ�Ķ���ε���ɫ��
     * @js NA
     */
    void drawSolidPoly(const Vec2 *poli, unsigned int numberOfPoints, const Color4F &color);
    
    /** @~english Draws a solid circle given the center, radius and number of segments.
     * @~chinese ����Բ������,�뾶���߶ε���������һ��ʵ��Բ��
     * @param center @~english The circle center point.
     * @~chinese Բ���ĵ㡣
     * @param radius @~english The circle rotate of radius.
     * @~chinese Բ�İ뾶��
     * @param angle  @~english The circle angle.
     * @~chinese Բ�ĽǶȡ�
     * @param segments @~english The number of segments.
     * @~chinese �߶ε�������
     * @param scaleX @~english The scale value in x.
     * @~chinese x������ֵ
     * @param scaleY @~english The scale value in y.
     * @~chinese y������ֵ
     * @param color @~english The solid circle color.
     * @~chinese ʵ��Բ����ɫ��
     * @js NA
     */
    void drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY, const Color4F &color);
    
    /** @~english Draws a solid circle given the center, radius and number of segments.
     * @~chinese ����Բ������,�뾶���߶ε���������һ��ʵ��Բ��
     * @param center @~english The circle center point.
     * @~chinese Բ���ĵ㡣
     * @param radius @~english The circle rotate of radius.
     * @~chinese Բ�İ뾶��
     * @param angle  @~english The circle angle.
     * @~chinese Բ�ĽǶȡ�
     * @param segments @~english The number of segments.
     * @~chinese �߶ε�������
     * @param color @~english The solid circle color.
     * @~chinese ʵ��Բ����ɫ��
     * @js NA
     */
    void drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, const Color4F& color);
    
    /** @~english draw a segment with a radius and color. 
     *
     * @~chinese ʹ��ָ���뾶����ɫ����һ���߶Ρ�
     * 
     * @param from @~english The segment origin.
     * @~chinese �߶ε�ԭ�㡣
     * @param to @~english The segment destination.
     * @~chinese �߶ε�Ŀ�ĵص㡣
     * @param radius @~english The segment radius.
     * @~chinese �߶ΰ뾶��
     * @param color @~english The segment color.
     * @~chinese �߶ε���ɫ��
     */
    void drawSegment(const Vec2 &from, const Vec2 &to, float radius, const Color4F &color);
    
    /** @~english draw a polygon with a fill color and line color
    * @~chinese ʹ�ø����������ɫ��������ɫ����һ������Ρ�
    *
    * @param verts @~english A pointer to point coordinates.
    * @~chinese һ��ָ�򶥵������ָ�롣
    * @param count @~english The number of verts measured in points.
     * @~chinese ���������
    * @param fillColor @~english The color will fill in polygon.
     * @~chinese ����ε������ɫ��
    * @param borderWidth @~english The border of line width.
     * @~chinese ����ε��߿�
    * @param borderColor @~english The border of line color.
     * @~chinese ����ε��߿����ɫ��
    * @js NA
    */
    void drawPolygon(const Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor);
	
    /** @~english draw a triangle with color, the color will fill in the triangle.
     *
     * @~chinese ʹ�ø�����ɫ����һ��������,����ɫ�������Ρ�
     * 
     * @param p1 @~english The triangle vertex point.
     * @~chinese �����εĶ��㡣
     * @param p2 @~english The triangle vertex point.
     * @~chinese �����εĶ��㡣
     * @param p3 @~english The triangle vertex point.
     * @~chinese �����εĶ��㡣
     * @param color @~english The triangle color.
     * @~chinese �����ε���ɫ��
     * @js NA
     */
    void drawTriangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Color4F &color);

    /** @~english draw a quadratic bezier curve with color and number of segments, use drawQuadBezier instead.
     *
     * @~chinese �����߶���ɫ���߶�������һ�����α���������. �ú����Ѳ��Ƽ�ʹ�ã�ʹ��drawQuadBezier���档
     * 
     * @param from @~english The origin of the bezier path.
     * @~chinese ����������·����ԭ�㡣
     * @param control @~english The control of the bezier path.
     * @~chinese ����������·���Ŀ��Ƶ㡣
     * @param to @~english The destination of the bezier path.
     * @~chinese ���������ߵ�·��Ŀ�ĵ�����㡣
     * @param segments @~english The The number of segments.
     * @~chinese �߶ε�������
     * @param color @~english The quadratic bezier color.
     * @~chinese ���α��������ߵ���ɫ��
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void drawQuadraticBezier(const Vec2& from, const Vec2& control, const Vec2& to, unsigned int segments, const Color4F &color);
    
    /** @~english Clear the geometry in the node's buffer.  @~chinese ����ڵ�Ļ������еļ������ݡ�*/

    void clear();

    /** @~english Get the color mixed mode.
     * @~chinese ��ȡ��ɫ���ģʽ��
    * @lua NA
    */
    const BlendFunc& getBlendFunc() const;

    /** @~english Set the color mixed mode.
     * @~chinese ������ɫ���ģʽ��
    * @lua NA
    */
    void setBlendFunc(const BlendFunc &blendFunc);

    /**
     * @js NA
     */
    virtual void onDraw(const Mat4 &transform, uint32_t flags);
    /**
     * @js NA
     */
    virtual void onDrawGLLine(const Mat4 &transform, uint32_t flags);
    /**
     * @js NA
     */
    virtual void onDrawGLPoint(const Mat4 &transform, uint32_t flags);
    
    // Overrides
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    void setLineWidth(int lineWidth);

    // Get CocosStudio guide lines width.
    float getLineWidth();

CC_CONSTRUCTOR_ACCESS:
    DrawNode(int lineWidth = DEFAULT_LINE_WIDTH);
    virtual ~DrawNode();
    virtual bool init() override;

protected:
    void ensureCapacity(int count);
    void ensureCapacityGLPoint(int count);
    void ensureCapacityGLLine(int count);

    GLuint      _vao;
    GLuint      _vbo;
    GLuint      _vaoGLPoint;
    GLuint      _vboGLPoint;
    GLuint      _vaoGLLine;
    GLuint      _vboGLLine;

    int         _bufferCapacity;
    GLsizei     _bufferCount;
    V2F_C4B_T2F *_buffer;
    
    int         _bufferCapacityGLPoint;
    GLsizei     _bufferCountGLPoint;
    V2F_C4B_T2F *_bufferGLPoint;
    Color4F     _pointColor;
    int         _pointSize;
    
    int         _bufferCapacityGLLine;
    GLsizei     _bufferCountGLLine;
    V2F_C4B_T2F *_bufferGLLine;

    BlendFunc   _blendFunc;
    CustomCommand _customCommand;
    CustomCommand _customCommandGLPoint;
    CustomCommand _customCommandGLLine;

    bool        _dirty;
    bool        _dirtyGLPoint;
    bool        _dirtyGLLine;
    
    int         _lineWidth;

    int  _defaultLineWidth;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(DrawNode);
};
/** @} */

NS_CC_END

#endif // __CCDRAWNODES_CCDRAW_NODE_H__
