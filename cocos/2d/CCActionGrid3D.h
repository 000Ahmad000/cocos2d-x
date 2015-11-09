/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
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
#ifndef __ACTION_CCGRID3D_ACTION_H__
#define __ACTION_CCGRID3D_ACTION_H__

#include "2d/CCActionGrid.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** 
@brief @~english Waves3D action.
 * @~chinese Waves3D������
 * @details @~english This action is used for making 3D waves effect on the target node.
        You can control the effect by these parameters:
        duration, grid size, waves count, amplitude.
 * @~chinese �ö���������Ŀ��ڵ�������3D����Ч����
 * ����Կ�����Щ������Ӱ��Ч��:
 * ����ʱ�䡢�����С�����˵������������
*/
class CC_DLL Waves3D : public Grid3DAction
{
public:
    /**
    @brief @~english Create an action with duration, grid size, waves and amplitude.
     * @~chinese ʹ�ó���ʱ�䡢�����С�����˵����������������һ��Wave3D������
    @param duration @~english Specify the duration of the Waves3D action. It's a value in seconds.
     * @~chinese ָ���ĳ���ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param waves @~english Specify the waves count of the Waves3D action.
     * @~chinese ���˵�������
    @param amplitude @~english Specify the amplitude of the Waves3D action.
     * @~chinese �����
    @return @~english If the creation sucess, return a pointer of Waves3D action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��ָ��Waves3D���������򣬷��ؿ�ָ�롣
    */
    static Waves3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese ��ȡWave3D��Ч�������
    @return @~english Return the amplitude of the effect.
     * @~chinese ���������
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese ����Wave3D��Ч�������
    @param amplitude @~english The value of amplitude will be set.
     * @~chinese �����ֵ��
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese ������˥���ʡ�
    @return @~english Return the amplitude rate of the effect.
     * @~chinese �������˥���ʡ�
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese �������˥���ʡ�
    @param amplitudeRate @~english The value of amplitude rate will be set.
     * @~chinese ���˥���ʡ�
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

	// Overrides
	virtual Waves3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Waves3D() {}
    virtual ~Waves3D() {}

    /** 
    @brief @~english Initializes an action with duration, grid size, waves and amplitude.
     * @~chinese ʹ�ó���ʱ�䡢�����С�����˵��������������ʼ��һ��Wave3D������
    @param duration @~english Specify the duration of the Waves3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param waves @~english Specify the waves count of the Waves3D action.
     * @~chinese ���˵�������
    @param amplitude @~english Specify the amplitude of the Waves3D action.
     * @~chinese �����
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�������true�����򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Waves3D);
};

/**
@brief @~english FlipX3D action.
 * @~chinese FlipX3D�ж���
@details @~english This action is used for flipping the target node on the x axis.
 * @~chinese �ö������ڽ�Ŀ��ڵ���x����з�ת��
*/
class CC_DLL FlipX3D : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with duration.
     * @~chinese �ó���ʱ�䴴��FlipX3D������
    @param duration @~english Specify the duration of the FilpX3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @return @~english If the creation sucess, return a pointer of FilpX3D action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��ָ��FilpX3D���������򣬷��ؿ�ָ�롣
    */
    static FlipX3D* create(float duration);

    // Override
	virtual FlipX3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipX3D() {}
    virtual ~FlipX3D() {}

    /** 
    @brief @~english Initializes an action with duration.
     * @~chinese �ó���ʱ���ʼ��FlipX3D������
    @param duration @~english Specify the duration of the FlipX3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�������true�����򷵻�false��
    */
    bool initWithDuration(float duration);

    /** 
    @brief @~english Initializes an action with duration and grid size.
     * @~chinese �ó���ʱ��������С��ʼ��Flip3D������
    @param gridSize @~english Specify the grid size of the FlipX3D action.
     * @~chinese ����Ĵ�С.
    @param duration @~english Specify the duration of the FlipX3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�������true�����򷵻�false��
    */
    virtual bool initWithSize(const Size& gridSize, float duration);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipX3D);
};

/**
@brief @~english FlipY3D action.
 * @~chinese FlipY3D�ж���
@details @~english This action is used for flipping the target node on the y axis.
 * @~chinese �ö������ڽ�Ŀ��ڵ���y����з�ת��
*/
class CC_DLL FlipY3D : public FlipX3D
{
public:
    /**
    @brief @~english Create the action with duration.
     * @~chinese �ó���ʱ�䴴��FlipY3D������
    @param duration @~english Specify the duration of the FlipY3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @return @~english If the creation sucess, return a pointer of FlipY3D action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��ָ��FlipY3D���������򣬷��ؿ�ָ�롣
    */
    static FlipY3D* create(float duration);

    // Overrides
    virtual void update(float time) override;
	virtual FlipY3D* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    FlipY3D() {}
    virtual ~FlipY3D() {}
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipY3D);
};

/**
@brief @~english Lens3D action.
 * @~chinese Lens3D������
 * @details @~english This action is used for take effect on the target node as lens.
        You can create the action by these parameters:
        duration, grid size, center position of lens, radius of lens.
        Also you can change the lens effect value & whether effect is concave by the setter methods.
 * @~chinese �ö���������Ŀ��ڵ��ϲ���3D��ͷ��Ч��
 * ���������Щ�������ƶ���:
 * ����ʱ�䡢����ߴ硢��ͷ������λ�á���ͷ�İ뾶��
 * Ҳ��������͸��ֵ��ѡ��ͷЧ���Ƿ��ǰ���ġ�
*/
class CC_DLL Lens3D : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with center position, radius, a grid size and duration.
     * @~chinese �þ�ͷ����λ�ã��뾶������Ĵ�С�ͳ���ʱ�䴴��һ��Lens3D������
    @param duration @~english Specify the duration of the Lens3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param position @~english Specify the center position of the lens.
     * @~chinese ��ͷ������λ�á�
    @param radius @~english Specify the radius of the lens.
     * @~chinese ��ͷ�İ뾶��
    @return @~english If the creation sucess, return a pointer of Lens3D action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��ָ��Lens3D���������򣬷��ؿ�ָ�롣
    */
    static Lens3D* create(float duration, const Size& gridSize, const Vec2& position, float radius);

    /**
    @brief @~english Get the value of lens effect. Default value is 0.7.
     * @~chinese ��ȡ͸��ֵ��Ĭ��ֵ��0.7��
    @return @~english The value of lens effect.
     * @~chinese ͸��ֵ��
    */
    inline float getLensEffect() const { return _lensEffect; }

    /**
    @brief @~english Set the value of lens effect.
     * @~chinese ����͸��ֵ��
    @param lensEffect @~english The value of lens effect will be set.
     * @~chinese ͸��ֵ��
    */
    inline void setLensEffect(float lensEffect) { _lensEffect = lensEffect; }

    /**
    @brief @~english Set whether lens is concave.
     * @~chinese ���þ�ͷ�Ƿ�Ϊ���档
    @param concave @~english Whether lens is concave.
     * @~chinese ��ͷ�Ƿ�Ϊ���档
    */
    inline void setConcave(bool concave) { _concave = concave; }

    /**
    @brief @~english Get the center position of lens effect.
     * @~chinese ��ȡ��ͷ������λ�á�
    @return @~english The center position of lens effect.
     * @~chinese ��ͷ������λ�á�
    */
    inline const Vec2& getPosition() const { return _position; }

    /**
    @brief @~english Set the center position of lens effect.
     * @~chinese ���þ�ͷ������λ�á�
    @param position @~english The center position will be set.
     * @~chinese ��ͷ������λ�á�
    */
    void setPosition(const Vec2& position);

    // Overrides
	virtual Lens3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Lens3D() {}
    virtual ~Lens3D() {}

    /**
    @brief @~english Initializes the action with center position, radius, grid size and duration.
     * @~chinese �þ�ͷ����λ�ã��뾶������Ĵ�С�ͳ���ʱ���ʼ��һ��Lens3D������
    @param duration @~english Specify the duration of the Lens3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param position @~english Specify the center position of the lens.
     * @~chinese ��ͷ������λ�á�
    @param radius @~english Specify the radius of the lens.
     * @~chinese ��ͷ�İ뾶��
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�������true�����򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, const Vec2& position, float radius);

protected:
    /* @~english lens center position  @~chinese ��ͷ������λ�� */
    Vec2 _position;
    float _radius;
    /** @~english lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect  @~chinese ͸��ֵ��Ĭ��Ϊ0.7 - 0��ζ��û��Ч����1�Ǻ�ǿ��Ч��*/
    float _lensEffect;
    /** @~english lens is concave. (true = concave, false = convex) default is convex  @~chinese ��ͷ�ǰ���ġ�(true=��,false=͹)Ĭ����͹��� */
    bool _concave;

    bool _dirty;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Lens3D);
};

/**
@brief @~english Ripple3D action.
 * @~chinese 3D���ƣ�Ripple3D��������
 * @details @~english This action is used for take effect on the target node as ripple.
        You can create the action by these parameters:
        duration, grid size, center position of ripple,
        radius of ripple, waves count, amplitude.
 * @~chinese �ö���������Ŀ��ڵ��ϲ���������Ч��
 * ���������Щ��������Ч��:
 * ����ʱ�䡢�����С�����Ƶ�����λ�á����Ƶİ뾶�����Ƶ������������
*/
class CC_DLL Ripple3D : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with center position, radius, number of waves, amplitude, a grid size and duration.
     * @~chinese ������λ�ã��뾶�����Ƶ����������������Ĵ�С�ͳ���ʱ��������һ��Ripple3D������
    @param duration @~english Specify the duration of the Ripple3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param position @~english Specify the center position of the ripple effect.
     * @~chinese ���Ƶ�����λ�á�
    @param radius @~english Specify the radius of the ripple effect.
     * @~chinese ���Ƶİ뾶.
    @param waves @~english Specify the waves count of the ripple effect.
     * @~chinese ���Ƶ�������
    @param amplitude @~english Specify the amplitude of the ripple effect.
     * @~chinese ���Ƶ������
    @return @~english If the creation sucess, return a pointer of Ripple3D action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��Ripple3D�ж������򣬷��ؿ�ָ�롣
    */
    static Ripple3D* create(float duration, const Size& gridSize, const Vec2& position, float radius, unsigned int waves, float amplitude);

    /**
    @brief @~english Get the center position of ripple effect.
     * @~chinese ��ȡ���Ƶ�����λ�á�
    @return @~english The center position of ripple effect.
     * @~chinese ��������λ�á�
    */
    inline const Vec2& getPosition() const { return _position; }
    /**
    @brief @~english Set the center position of ripple effect.
     * @~chinese ���ò��Ƶ�����λ�á�
    @param position @~english The center position of ripple effect will be set.
     * @~chinese ���Ƶ�����λ�á�
    */
    void setPosition(const Vec2& position);

    /**
    @brief @~english Get the amplitude of ripple effect.
     * @~chinese ��ȡ�Ĳ��Ƶ������
    @return @~english The amplitude of ripple effect.
     * @~chinese ���Ƶ������
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude of ripple effect.
     * @~chinese ���ò��Ƶ������
    @param fAmplitude @~english The amplitude of ripple effect.
     * @~chinese ���Ƶ������
    */
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    /**
    @brief @~english Get the amplitude rate of ripple effect.
     * @~chinese ��ȡ���Ƶ����˥���ʡ�
    @return @~english The amplitude rate of ripple effect.
     * @~chinese ���˥���ʡ�
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the amplitude rate of ripple effect.
     * @~chinese ���ò��Ƶ����˥���ʡ�
    @param fAmplitudeRate @~english The amplitude rate of ripple effect.
     * @~chinese ���˥���ʡ�
    */
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    // Override
	virtual Ripple3D* clone() const override;
    virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
    Ripple3D() {}
    virtual ~Ripple3D() {}

    /**
    @brief @~english Initializes the action with center position, radius, number of waves, amplitude, a grid size and duration.
     * @~chinese ������λ�ã��뾶�����Ƶ����������������Ĵ�С�ͳ���ʱ������ʼ��һ��Ripple3D������
    @param duration @~english Specify the duration of the Ripple3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param position @~english Specify the center position of the ripple effect.
     * @~chinese ���Ƶ�����λ�á�
    @param radius @~english Specify the radius of the ripple effect.
     * @~chinese ���Ƶİ뾶.
    @param waves @~english Specify the waves count of the ripple effect.
     * @~chinese ���Ƶ�������
    @param amplitude @~english Specify the amplitude of the ripple effect.
     * @~chinese ���Ƶ������
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�������true�����򷵻�false��
     */
    bool initWithDuration(float duration, const Size& gridSize, const Vec2& position, float radius, unsigned int waves, float amplitude);

protected:
    /* @~english The center position of the ripple effect  @~chinese ���Ƶ�����λ�� */
    Vec2 _position;
    /* @~english The radius of the ripple effect  @~chinese ���Ƶİ뾶 */
    float _radius;
    /* @~english The wave count of the ripple effect  @~chinese ���Ƶ����� */
    unsigned int _waves;
    /* @~english The amplitude of the ripple effect  @~chinese ���Ƶ���� */
    float _amplitude;
    /* @~english The amplitude rate of the ripple effect  @~chinese ���Ƶ����˥���� */
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Ripple3D);
};

/**
@brief @~english Shaky3D action.
 * @~chinese 3Dҡ�Σ�Shaky3D��������
 * @details @~english This action is used for take effect on the target node as shaky.
        You can create the action by these parameters:
        duration, grid size, range, whether shake on the z axis.
 * @~chinese �ö���������Ŀ��ڵ�������ҡ�ε��Ӿ���Ч��
 * ����Ըı���Щ����������Ч��:
 * ����ʱ�䡢�����С����Χ���Ƿ���z��ҡ�Ρ�
*/
class CC_DLL Shaky3D : public Grid3DAction
{
public:
    /** 
    @brief @~english Create the action with duration, grid size, range and whether shake on Z axis.
     * @~chinese �ó���ʱ�䡢�����С����Χ���Ƿ���z��ҡ�εȲ���������һ��Shaky3D������
    @param initWithDuration @~english Specify the duration of the Shaky3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param range @~english Specify the range of the shaky effect.
     * @~chinese �ζ���Ч�ķ�Χ��
    @param shakeZ @~english Specify whether shake on the z axis.
     * @~chinese ָ���Ƿ���z��ζ���
    @return @~english If the creation sucess, return a pointer of Shaky3D action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��Shaky3D���������򣬷��ؿ�ָ�롣
    */
    static Shaky3D* create(float initWithDuration, const Size& gridSize, int range, bool shakeZ);

    // Overrides
	virtual Shaky3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Shaky3D() {}
    virtual ~Shaky3D() {}
    
    /** 
    @brief @~english Initializes the action with duration, grid size, range and whether shake on Z axis.
     * @~chinese �ó���ʱ�䡢�����С����Χ���Ƿ���z��ҡ�εȲ�������ʼ��һ��Shaky3D������
    @param duration @~english Specify the duration of the Shaky3D action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param range @~english Specify the range of the shaky effect.
     * @~chinese �ζ���Ч�ķ�Χ��
    @param shakeZ @~english Specify whether shake on the z axis.
     * @~chinese ָ���Ƿ���z��ζ���
    @return @~english If the creation sucess, return a pointer of Shaky3D action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��Shaky3D���������򣬷��ؿ�ָ�롣
    */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ);

protected:
    int _randrange;
    bool _shakeZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Shaky3D);
};

/**
@brief @~english Liquid action.
 * @~chinese Һ�壨Liquid��������
 * @details @~english This action is used for take effect on the target node as liquid.
        You can create the action by these parameters:
        duration, grid size, waves count, amplitude of the liquid effect.
 * @~chinese �ö���������Ŀ��ڵ�������Һ��Ч����
 * ���������Щ����������Ч:
 * ����ʱ�䡢�����С������������Һ����Ч�������
*/
class CC_DLL Liquid : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with duration, grid size, waves count and amplitude.
     * @~chinese �ó���ʱ�䡢�����С���������������������һ��Liquid������
    @param duration @~english Specify the duration of the Liquid action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param waves @~english Specify the waves count of the Liquid action.
     * @~chinese ����������
    @param amplitude @~english Specify the amplitude of the Liquid action.
     * @~chinese Liquid�����������
    @return @~english If the creation sucess, return a pointer of Liquid action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��Liquid���������򣬷��ؿ�ָ�롣
    */
    static Liquid* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese ��ȡ�����
    @return @~english Return the amplitude of the effect.
     * @~chinese �����
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese ���������
    @param amplitude @~english The value of amplitude will be set.
     * @~chinese �����
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese ������˥���ʡ�
    @return @~english Return the amplitude rate of the effect.
     * @~chinese ���˥���ʡ�
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese �������˥���ʡ�
    @param amplitudeRate @~english The value of amplitude rate will be set.
     * @~chinese ���˥���ʡ�
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Overrides
	virtual Liquid* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Liquid() {}
    virtual ~Liquid() {}
    
    /**
    @brief @~english Initializes the action with duration, grid size, waves count and amplitude.
     * @~chinese �ó���ʱ�䡢�����С���������������������һ��Liquid������
    @param duration @~english Specify the duration of the Liquid action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param waves @~english Specify the waves count of the Liquid action.
     * @~chinese ����������
    @param amplitude @~english Specify the amplitude of the Liquid action.
     * @~chinese Liquid�����������
    @return @~english If the initialization sucess, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�������true�����򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Liquid);
};

/**
@brief @~english Waves action.
 * @~chinese ������Ч������
 * @details @~english This action is used for take effect on the target node as waves.
        You can control the effect by these parameters:
        duration, grid size, waves count, amplitude,
        whether waves on horizontal and whether waves on vertical.
 * @~chinese �ö���������Ŀ��ڵ������첨����Ч��
 * ����Կ�����Щ������������Ч:
 * ����ʱ�䡢�����С�����˵�����������������Ƿ���ˮƽ�����Ϻʹ�ֱ�����ϡ�
 */
class CC_DLL Waves : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with duration, grid size, waves count, amplitude, whether waves on horizontal and on vertical.
     * @~chinese �ó���ʱ�䣬�����С�����˵�����������������Ƿ���ˮƽ�����Ϻʹ�ֱ������������һ��Waves������
    @param duration @~english Specify the duration of the Waves action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param waves @~english Specify the waves count of the Waves action.
     * @~chinese ���˵�������
    @param amplitude @~english Specify the amplitude of the Waves action.
     * @~chinese ���˵������
    @param horizontal @~english Specify whether waves on horizontal.
     * @~chinese ָ��ˮƽ�����Ƿ��в��ˡ�
    @param vertical @~english Specify whether waves on vertical.
     * @~chinese ָ����ֱ�����Ƿ��в��ˡ�
    @return @~english If the creation sucess, return a pointer of Waves action; otherwise, return nil.
     * @~chinese ��������ɹ�,����һ��Waves���������򣬷��ؿ�ָ�롣
    */
    static Waves* create(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese ��ȡ�����
    @return @~english Return the amplitude of the effect.
     * @~chinese �����
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese ���������
    @param amplitude @~english The value of amplitude will be set.
     * @~chinese �����
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese ��ȡ���˥���ʡ�
    @return @~english Return the amplitude rate of the effect.
     * @~chinese �������˥���ʡ�
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese �������˥���ʡ�
    @param amplitudeRate @~english The value of amplitude rate will be set.
     * @~chinese ���˥���ʡ�
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Overrides
	virtual Waves* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Waves() {}
    virtual ~Waves() {}
    
    /**
    @brief @~english Initializes the action with duration, grid size, waves count, amplitude, whether waves on horizontal and on vertical.
     * @~chinese �ó���ʱ�䣬�����С�����˵�����������������Ƿ���ˮƽ�����Ϻʹ�ֱ������������һ��Waves������
    @param duration @~english Specify the duration of the Waves action. It's a value in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param waves @~english Specify the waves count of the Waves action.
     * @~chinese ���˵�������
    @param amplitude @~english Specify the amplitude of the Waves action.
     * @~chinese ���˵������
    @param horizontal @~english Specify whether waves on horizontal.
     * @~chinese ָ��ˮƽ�����Ƿ��в��ˡ�
    @param vertical @~english Specify whether waves on vertical.
     * @~chinese ָ����ֱ�����Ƿ��в��ˡ�
    @return @~english If the initialization sucess, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�������true�����򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
    bool _vertical;
    bool _horizontal;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Waves);
};

/**
@brief @~english Twirl action.
 * @~chinese ���У�Twirl��������
@details @~english This action is used for take effect on the target node as twirl.
        You can control the effect by these parameters:
        duration, grid size, center position, twirls count, amplitude.
 * @~chinese �ö���������Ŀ��ڵ��ϲ�������Ч����
 * ����Կ�����Щ������������Ч:
 * ����ʱ�䡢�����С������λ�á����м��������ȡ�
*/
class CC_DLL Twirl : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with duration, grid size, center position, number of twirls and amplitude.
     * @~chinese �ó���ʱ�䡢�����С������λ�á����м���������������һ��Twirl����
    @param duration @~english Specify the duration of the Twirl action. It's a value in seconds.
     * @~chinese ����ʱ�䡣
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param position @~english Specify the center position of the twirl action.
     * @~chinese ���е�����λ�á�
    @param twirls @~english Specify the twirls count of the Twirl action.
     * @~chinese ���е�������
    @param amplitude @~english Specify the amplitude of the Twirl action.
     * @~chinese ���ж����ķ��ȡ�
    @return @~english If the creation sucess, return a pointer of Twirl action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��Twirl���������򣬷��ؿ�ָ�롣
    */
    static Twirl* create(float duration, const Size& gridSize, Vec2 position, unsigned int twirls, float amplitude);

    /**
    @brief @~english Get the center position of twirl action.
     * @~chinese ��ȡ���е�����λ�á�
    @return @~english The center position of twirl action.
     * @~chinese ���е�����λ�á�
    */
    inline const Vec2& getPosition() const { return _position; }
    /**
    @brief @~english Set the center position of twirl action.
     * @~chinese �������е�����λ�á�
    @param position @~english The center position of twirl action will be set.
     * @~chinese ���е�����λ�á�
    */
    void setPosition(const Vec2& position);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese ��ȡ������Ч�ķ��ȡ�
    @return @~english Return the amplitude of the effect.
     * @~chinese ������Ч�ķ��ȡ�
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese ����������Ч�ķ��ȡ�
    @param amplitude @~english The value of amplitude will be set.
     * @~chinese ������Ч�ķ��ȡ�
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese ���������Ч�ķ��ȱ��ʡ�
    @return @~english Return the amplitude rate of the effect.
     * @~chinese ������Ч�ķ��ȱ��ʡ�
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese ����������Ч�ķ��ȱ��ʡ�
    @param amplitudeRate @~english The value of amplitude rate will be set.
     * @~chinese ������Ч�ķ��ȱ��ʡ�
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }


    // Overrides
	virtual Twirl* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Twirl() {}
    virtual ~Twirl() {}

    /**
    @brief @~english Initializes the action with duration, grid size, center position, number of twirls and amplitude.
     * @~chinese �ó���ʱ�䡢�����С������λ�á����м���������������һ��Twirl����
    @param duration @~english Specify the duration of the Twirl action. It's a value in seconds.
     * @~chinese ����ʱ�䡣
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ����Ĵ�С��
    @param position @~english Specify the center position of the twirl action.
     * @~chinese ���е�����λ�á�
    @param twirls @~english Specify the twirls count of the Twirl action.
     * @~chinese ���е���ת������
    @param amplitude @~english Specify the amplitude of the Twirl action.
     * @~chinese ���ж����ķ��ȡ�
    @return @~english If the initialization sucess, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�������true�����򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, Vec2 position, unsigned int twirls, float amplitude);

protected:
    /* @~english The twirl center position @~chinese ���е�����λ�� */
    Vec2 _position;
    /* @~english The twirls count  @~chinese ���е����� */
    unsigned int _twirls;
    /* @~english The twirls amplitude  @~chinese ������Ч�ķ��� */
    float _amplitude;
    /* @~english The twirls amplitude rate @~chinese ������Ч�ķ��ȱ��� */
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Twirl);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID3D_ACTION_H__
