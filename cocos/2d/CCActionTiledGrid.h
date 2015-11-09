/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
CopyRight (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __ACTION_CCTILEDGRID_ACTION_H__
#define __ACTION_CCTILEDGRID_ACTION_H__

#include "2d/CCActionGrid.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/**
@brief @~english ShakyTiles3D action.
 * @~chinese ShakyTiles3D������
@details @~english This action is make the target node shake with many tiles.
        You can create the action by these parameters:
        duration, grid size, range, whether shake on the z axis.
 * @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽ�ζ��Ķ�����
 * ����������Щ������������:
 * ����ʱ�䡢�����С����Χ���Ƿ���z���϶�ҡ��
 */
class CC_DLL ShakyTiles3D : public TiledGrid3DAction
{
public:
    /** 
    @brief @~english Create the action with a range, shake Z vertices, a grid and duration.
    * @~chinese ���ݶ�����Χ��Z�����Ƿ񶶶��������С�ͳ���ʱ�䴴��ShakyTiles3D������
    @param duration @~english Specify the duration of the ShakyTiles3D action. It's a value in seconds.
    * @~chinese ָ��ShakyTiles3D�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    @param gridSize @~english Specify the size of the grid.
    * @~chinese ָ������Ĵ�С��
    @param range @~english Specify the range of the shaky effect.
    * @~chinese ָ��ҡ��Ч���ķ�Χ��
    @param shakeZ @~english Specify whether shake on the z axis.
    * @~chinese ָ���Ƿ���z���϶�ҡ��
    @return @~english If the creation success, return a pointer of ShakyTiles3D action; otherwise, return nil.
     * @~chinese ��������ɹ�,����һ��ָ��ShakyTiles3D������ָ��;����,���ؿա�
    */
    static ShakyTiles3D* create(float duration, const Size& gridSize, int range, bool shakeZ);

    // Override
	virtual ShakyTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShakyTiles3D() {}
    virtual ~ShakyTiles3D() {}

    /** 
    @brief @~english Initializes the action with a range, shake Z vertices, grid size and duration.
     * @~chinese ���ݶ�����Χ��Z�����Ƿ񶶶��������С�ͳ���ʱ���ʼ��ShakyTiles3D������
    @param duration @~english Specify the duration of the ShakyTiles3D action. It's a value in seconds.
     * @~chinese ָ��ShakyTiles3D�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    @param range @~english Specify the range of the shaky effect.
     * @~chinese  ָ��ҡ��Ч���ķ�Χ��
    @param shakeZ @~english Specify whether shake on the z axis.
     * @~chinese ָ���Ƿ���z���϶�ҡ��

    @return @~english If the Initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�,����true,���򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ);

protected:
    int _randrange;
    bool _shakeZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShakyTiles3D);
};

/**
@brief @~english ShatteredTiles3D action.
 * @~chinese ShatteredTiles3D ������
@details @~english This action make the target node shattered with many tiles.
        You can create the action by these parameters:
        duration, grid size, range, whether shatter on the z axis.
        * @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽҡ���Ķ���
        * ����������Щ������������:
        * ����ʱ�䡢�����С����Χ���Ƿ���z���϶�ҡ��
*/
class CC_DLL ShatteredTiles3D : public TiledGrid3DAction
{
public:
    /** 
     * @brief @~english Create the action with a range, whether of not to shatter Z vertices, grid size and duration.
     * @~chinese ���ݶ�����Χ��Z�����Ƿ񶶶��������С�ͳ���ʱ�䴴��������
     * @param duration @~english Specify the duration of the ShatteredTiles3D action. It's a value in seconds.
     * @~chinese ָ��ShakyTiles3D�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
     * @param range @~english Specify the range of the shatter effect.
     * @~chinese ָ����Χ�ķ���Ч����
     * @param shatterZ @~english Specify whether shatter on the z axis.
     * @~chinese ָ��ҡ��Ч���ķ�Χ��
     * @return @~english If the creation success, return a pointer of ShatteredTiles3D action; otherwise, return nil.
     * @~chinese ��������ɹ�,����һ��ָ��ShatteredTiles3D��ָ�롣����,���ؿա�
     */
    static ShatteredTiles3D* create(float duration, const Size& gridSize, int range, bool shatterZ);

    // Override
	virtual ShatteredTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ShatteredTiles3D() {}
    virtual ~ShatteredTiles3D() {}

    /** 
    @brief @~english Initializes the action with a range, shatter Z vertices, grid size and duration.
    * @~chinese ���ݶ�����Χ��Z�����Ƿ񶶶��������С�ͳ���ʱ���ʼ��������
    @param duration @~english Specify the duration of the ShatteredTiles3D action. It's a value in seconds.
    * @~chinese ָ��ShakyTiles3D�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    @param range @~english Specify the range of the shatter effect.
    * @~chinese ָ����Χ�ķ���Ч����
    @param shatterZ @~english Specify whether shake on the z axis.
    * @~chinese ָ��ҡ��Ч���ķ�Χ��
    @return @~english If the Initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�,����true,���򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shatterZ);

protected:
    int _randrange;
    bool _once;
    bool _shatterZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShatteredTiles3D);
};

struct Tile;
/**
@brief @~english ShuffleTiles action.
 * @~chinese ShuffleTiles ������
@details @~english This action make the target node shuffle with many tiles in random order.
        You can create the action by these parameters:
        duration, grid size, the random seed.
 * @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽ���ϴ�ƵĶ���
 * ����������Щ������������:
 * ����ʱ�䡢�����С,������ӡ�
*/
class CC_DLL ShuffleTiles : public TiledGrid3DAction
{
public:
    /** 
    * @brief @~english Create the action with grid size, random seed and duration.
     * @~chinese ʹ�������С��,������Ӻͳ���ʱ�䴴��������
    * @param duration @~english Specify the duration of the ShuffleTiles action. It's a value in seconds.
    * @~chinese ָ��ShuffleTile�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    * @param seed @~english Specify the random seed.
     * @~chinese ָ��������ӡ�
    * @return @~english If the creation success, return a pointer of ShuffleTiles action; otherwise, return nil.
    * @~chinese ��������ɹ�,����һ��ָ��ShuffleTile��ָ�롣����,���ؿա�
    */
    static ShuffleTiles* create(float duration, const Size& gridSize, unsigned int seed);

    void shuffle(unsigned int *array, unsigned int len);
    Size getDelta(const Size& pos) const;
    void placeTile(const Vec2& pos, Tile *t);

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
	virtual ShuffleTiles* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    ShuffleTiles() {}
    virtual ~ShuffleTiles();

    /** 
    * @brief @~english Initializes the action with grid size, random seed and duration.
    * @~chinese ʹ�������С��,������Ӻͳ���ʱ���ʼ��������
    * @param duration @~english Specify the duration of the ShuffleTiles action. It's a value in seconds.
    * @~chinese ָ��ShuffleTile�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    * @param seed @~english Specify the random seed.
     * @~chinese ָ��������ӡ�
    * @return @~english If the Initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�,����true,���򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

protected:
    unsigned int _seed;
    unsigned int _tilesCount;
    unsigned int* _tilesOrder;
    Tile* _tiles;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ShuffleTiles);
};

/**
@brief @~english FadeOutTRTiles action.
 * @~chinese FadeOutTRTiles�ж���
@details @~english Fades out the target node with many tiles from Bottom-Left to Top-Right.
* @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽ�����µ����ϵ����Ķ�����
 */
class CC_DLL FadeOutTRTiles : public TiledGrid3DAction
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
     * @~chinese ʹ�������С�ͳ���ʱ�䴴��������
    * @param duration @~english Specify the duration of the FadeOutTRTiles action. It's a value in seconds.
    * @~chinese ָ��FadeOutTRTile�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    * @return @~english If the creation success, return a pointer of FadeOutTRTiles action; otherwise, return nil.
     * @~chinese ��������ɹ�,����һ��ָ��FadeOutTRTiles������ָ��;����,���ؿա�
    */
    static FadeOutTRTiles* create(float duration, const Size& gridSize);

    /**
    @brief @~english Calculate the percentage a tile should be shown.
     * @~chinese ����һ��tileӦ����ʾ�İٷֱȡ�
    @param pos @~english The position index of the tile.
     * @~chinese tile��λ��������
    @param time @~english The current percentage of the action.
     * @~chinese ��ǰ�����İٷֱȡ�
    @return @~english Return the percentage the tile should be shown.
     * @~chinese ����tileӦ����ʾ�İٷֱȡ�
    */
    virtual float testFunc(const Size& pos, float time);

    /**
    @brief @~english Show the tile at specified position.
     * @~chinese ��ʾָ��λ�õ�tile��
    @param pos @~english The position index of the tile should be shown.
     * @~chinese Ӧ����ʾ��tile��λ��������
    */
    void turnOnTile(const Vec2& pos);

    /**
    @brief @~english Hide the tile at specified position.
     * @~chinese ����ָ��λ�õ�tile��
    @param pos @~english The position index of the tile should be hide.
    * @~chinese Ӧ�����ص�tile��λ������
    */
    void turnOffTile(const Vec2& pos);

    /**
    @brief @~english Show part of the tile.
     * @~chinese չʾtile��һ���֡�
    @param pos @~english The position index of the tile should be shown.
    * @~chinese Ӧ����ʾ��tile��λ��������
    @param distance @~english The percentage that the tile should be shown.
    * @~chinese Ӧ����ʾ��tile�İٷֱȡ�
    */
    virtual void transformTile(const Vec2& pos, float distance);

    // Overrides
    virtual void update(float time) override;
	virtual FadeOutTRTiles* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    FadeOutTRTiles() {}
    virtual ~FadeOutTRTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutTRTiles);
};

/**
@brief @~english FadeOutBLTiles action.
 * @~chinese FadeOutBLTiles������
@details @~english Fades out the target node with many tiles from Top-Right to Bottom-Left.
* @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽ�����ϵ����µ����Ķ�����
 */
class CC_DLL FadeOutBLTiles : public FadeOutTRTiles
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
    * @~chinese ʹ�������С�ͳ���ʱ�䴴��������
    * @param duration @~english Specify the duration of the FadeOutBLTiles action. It's a value in seconds.
    * @~chinese ָ��FadeOutBLTiles�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    * @return @~english If the creation success, return a pointer of FadeOutBLTiles action; otherwise, return nil.
    * @~chinese ��������ɹ�,����һ��ָ��FadeOutBLTiles������ָ��;����,���ؿա�
    */
    static FadeOutBLTiles* create(float duration, const Size& gridSize);

    // Overrides
    virtual float testFunc(const Size& pos, float time) override;
	virtual FadeOutBLTiles* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    FadeOutBLTiles() {}
    virtual ~FadeOutBLTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutBLTiles);
};

/**
@brief @~english FadeOutUpTiles action.
 * @~chinese FadeOutUpTiles������
@details @~english Fades out the target node with many tiles from bottom to top.
* @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽ���µ��ϵ����Ķ���
 */
class CC_DLL FadeOutUpTiles : public FadeOutTRTiles
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
    * @~chinese  ʹ�������С�ͳ���ʱ�䴴��������
    * @param duration @~english Specify the duration of the FadeOutUpTiles action. It's a value in seconds.
    * @~chinese ָ��FadeOutUpTiles�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    * @param gridSize @~english Specify the size of the grid.
    * @~chinese ָ������Ĵ�С
    * @return @~english If the creation success, return a pointer of FadeOutUpTiles action; otherwise, return nil.
    * @~chinese ��������ɹ�,����һ��ָ��FadeOutUpTiles������ָ��;����,���ؿա�
    */
    static FadeOutUpTiles* create(float duration, const Size& gridSize);

    virtual void transformTile(const Vec2& pos, float distance) override;

    // Overrides
	virtual FadeOutUpTiles* clone() const override;
    virtual float testFunc(const Size& pos, float time) override;

CC_CONSTRUCTOR_ACCESS:
    FadeOutUpTiles() {}
    virtual ~FadeOutUpTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutUpTiles);
};

/**
@brief @~english FadeOutDownTiles action.
 * @~chinese FadeOutDownTiles������
@details @~english Fades out the target node with many tiles from top to bottom.
* @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽ���ϵ��µ����Ķ���
 */
class CC_DLL FadeOutDownTiles : public FadeOutUpTiles
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
    * @~chinese ʹ�������С�ͳ���ʱ�䴴������
    * @param duration @~english Specify the duration of the FadeOutDownTiles action. It's a value in seconds.
    * @~chinese ָ��FadeOutDownTiles�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    * @return @~english If the creation success, return a pointer of FadeOutDownTiles action; otherwise, return nil.
    * @~chinese ��������ɹ�,����һ��ָ��FadeOutDownTiles������ָ��;����,���ؿա�
    */
    static FadeOutDownTiles* create(float duration, const Size& gridSize);

    // Overrides
	virtual FadeOutDownTiles* clone() const override;
    virtual float testFunc(const Size& pos, float time) override;

CC_CONSTRUCTOR_ACCESS:
    FadeOutDownTiles() {}
    virtual ~FadeOutDownTiles() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutDownTiles);
};

/**
@brief @~english TurnOffTiles action.
 * @~chinese TurnOffTiles������
@details @~english Turn off the target node with many tiles in random order.
* @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽ����رյĶ���
 */
class CC_DLL TurnOffTiles : public TiledGrid3DAction
{
public:
    /** 
    * @brief @~english Create the action with the grid size and the duration.
    * @~chinese ʹ�������С�ͳ���ʱ�䴴��������
    * @param duration @~english Specify the duration of the TurnOffTiles action. It's a value in seconds.
    * @~chinese ָ��TurnOffTiles�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    * @return @~english If the creation success, return a pointer of TurnOffTiles action; otherwise, return nil.
    * @~chinese ��������ɹ�,����һ��ָ��TurnOffTiles������ָ��;����,���ؿա�
    */
    static TurnOffTiles* create(float duration, const Size& gridSize);
    /** 
    * @brief @~english Create the action with the grid size, the duration and random seed.
    * @~chinese ʹ�������С������ʱ���������Ӵ���������
    * @param duration @~english Specify the duration of the TurnOffTiles action. It's a value in seconds.
    * @~chinese ָ��TurnOffTiles�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    * @param seed @~english Specify the random seed.
     * @~chinese ָ��������ӡ�
    * @return @~english If the creation success, return a pointer of TurnOffTiles action; otherwise, return nil.
    * @~chinese ��������ɹ�,����һ��ָ��TurnOffTiles������ָ��;����,���ؿա�
    */
    static TurnOffTiles* create(float duration, const Size& gridSize, unsigned int seed);

    /**
    @brief @~english Shuffle the array specified.
     * @~chinese ָ����������顣
    @param array @~english The array will be shuffled.
     * @~chinese Ҫ��������ҵ����顣
    @param len @~english The size of the array.
     * @~chinese ����Ĵ�С��
    */
    void shuffle(unsigned int *array, unsigned int len);

    /**
    @brief @~english Show the tile at specified position.
     * @~chinese ��ʾָ��λ�õ�tile��
    @param pos @~english The position index of the tile should be shown.
     * @~chinese Ӧ����ʾ��tile��λ��������
    */
    void turnOnTile(const Vec2& pos);

    /**
    @brief @~english Hide the tile at specified position.
     * @~chinese ����ָ��λ�õ�tile��
    @param pos @~english The position index of the tile should be hide.
     * @~chinese Ӧ�����ص�tile��λ��������
    */
    void turnOffTile(const Vec2& pos);

    // Overrides
	virtual TurnOffTiles* clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TurnOffTiles() {}
    virtual ~TurnOffTiles();

    /** 
    * @brief @~english Initializes the action with grid size, random seed and duration.
    * @~chinese ʹ�������С������ʱ�䣬������ӳ�ʼ��������
    * @param duration @~english Specify the duration of the TurnOffTiles action. It's a value in seconds.
    * @~chinese ָ��TurnOffTiles�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    * @param seed @~english Specify the random seed.
     * @~chinese ָ��������ӡ�
    * @return @~english If the Initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�,����true,���򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int seed);

protected:
    unsigned int    _seed;
    unsigned int    _tilesCount;
    unsigned int*   _tilesOrder;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TurnOffTiles);
};

/**
@brief @~english WavesTiles3D action.
 * @~chinese WavesTiles3D������
@details @~english This action wave the target node with many tiles.
* @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽ�����Ķ���
*/
class CC_DLL WavesTiles3D : public TiledGrid3DAction
{
public:
    /** 
     * @brief @~english Create the action with a number of waves, the waves amplitude, the grid size and the duration.
     * @~chinese ʹ�ò���,�����,�����С�ͳ���ʱ��������������
     * @param duration @~english Specify the duration of the WavesTiles3D action. It's a value in seconds.
     * @~chinese  ָ��WavesTiles3D�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
     * @param waves @~english Specify the waves count of the WavesTiles3D action.
     * @~chinese ָ��WavesTiles3D�����Ĳ�����
     * @param amplitude @~english Specify the amplitude of the WavesTiles3D action.
     * @~chinese ָ��WavesTiles3D�����������
     * @return @~english If the creation success, return a pointer of WavesTiles3D action; otherwise, return nil.
     * @~chinese ��������ɹ�,����һ��ָ��WavesTiles3D������ָ��;����,���ؿա�
     */
    static WavesTiles3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

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
    * @~chinese �������õķ�ֵ��
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese �������ʡ�
    @return @~english Return the amplitude rate of the effect.
     * @~chinese ��������ʡ�
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese ����ampliture�ʡ�
    @param amplitudeRate @~english The value of amplitude rate will be set.
    * @~chinese �������õ�����ʡ�
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual WavesTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    WavesTiles3D() {}
    virtual ~WavesTiles3D() {}

    /** 
    @brief @~english Initializes an action with duration, grid size, waves count and amplitude.
    * @~chinese ʹ�ò���,�����,�����С�ͳ���ʱ���ʼ��������
    @param duration @~english Specify the duration of the WavesTiles3D action. It's a value in seconds.
    * @~chinese ָ��WavesTiles3D�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
    @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
    @param waves @~english Specify the waves count of the WavesTiles3D action.
    * @~chinese ָ��WavesTiles3D�����Ĳ�����
    @param amplitude @~english Specify the amplitude of the WavesTiles3D action.
    * @~chinese ָ��WavesTiles3D�����������
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�,����true,���򷵻�false��
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(WavesTiles3D);
};

/**
@brief @~english JumpTiles3D action.
 * @~chinese JumpTiles3D������
@details @~english Move the tiles of a target node across the Z axis.
* @~chinese ����һ����Ŀ��ڵ��Զ����Ƭ����ʽ��z���ƶ��Ķ���
*/
class CC_DLL JumpTiles3D : public TiledGrid3DAction
{
public:
    /** 
     * @brief @~english Create the action with the number of jumps, the sin amplitude, the grid size and the duration.
     * @~chinese ʹ����Ծ�����������,�����С�ͳ���ʱ�䴴��������
     * @param duration @~english Specify the duration of the JumpTiles3D action. It's a value in seconds.
     * @~chinese ָ��JumpTiles3D�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ����
     * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
     * @param numberOfJumps @~english Specify the jump tiles count.
     * @~chinese ָ����Ծ������
     * @param amplitude @~english Specify the amplitude of the JumpTiles3D action.
     * @~chinese ָ��JumpTiles3D�����������
     * @return @~english If the creation success, return a pointer of JumpTiles3D action; otherwise, return nil.
     * @~chinese ��������ɹ�,����һ��ָ��JumpTiles3D������ָ��;����,���ؿա�
     */
    static JumpTiles3D* create(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

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
    * @~chinese �������õķ���
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese �������ʡ�
    @return @~english Return the amplitude rate of the effect.
     * @~chinese ����ʡ�
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the amplitude rate of the effect.
     * @~chinese ������ָ����ʡ�
    @param amplitudeRate @~english The value of amplitude rate will be set.
    * @~chinese  �������õ�����ʡ�
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Override
	virtual JumpTiles3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    JumpTiles3D() {}
    virtual ~JumpTiles3D() {}

    /** 
     * @brief @~english Initializes the action with the number of jumps, the sin amplitude, the grid size and the duration.
     * @~chinese ʹ����Ծ��,�����,�����С�ͳ���ʱ���ʼ����������
     * @param duration @~english Specify the duration of the JumpTiles3D action. It's a value in seconds.
     * @~chinese ָ��JumpTiles3D�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param gridSize @~english Specify the size of the grid.
     * @~chinese ָ������Ĵ�С��
     * @param numberOfJumps @~english Specify the jump tiles count.
     * @~chinese ָ����Ծ������
     * @param amplitude @~english Specify the amplitude of the JumpTiles3D action.
     * @~chinese ָ��JumpTiles3D�����������
     * @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese �����ʼ���ɹ�,����true,���򷵻�false��
     */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude);

protected:
    unsigned int _jumps;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpTiles3D);
};

/**
@brief @~english SplitRows action.
 * @~chinese SplitRows������
@details @~english Split the target node in many rows.
        Then move out some rows from left, move out the other rows from right.
 * @~chinese ��Ŀ��ڵ�ָ�Ϊ���С�
 * Ȼ�������Ƴ�ȥһЩ��,���ұ��Ƴ�ȥ��һЩ�С�
*/
class CC_DLL SplitRows : public TiledGrid3DAction
{
public :
    /** 
     * @brief @~english Create the action with the number of rows and the duration.
     * @~chinese ʹ��ָ�������ͳ���ʱ�䴴��������
     * @param duration @~english Specify the duration of the SplitRows action. It's a value in seconds.
     * @~chinese ΪSplitRows����ָ������ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param rows @~english Specify the rows count should be splited.
     * @~chinese ָ��Ӧ�÷ָ��������
     * @return @~english If the creation success, return a pointer of SplitRows action; otherwise, return nil.
     * @~chinese ��������ɹ�,����һ��ָ��SplitRows����ָ��;����,���ؿա�
     */
    static SplitRows* create(float duration, unsigned int rows);

    // Overrides
	virtual SplitRows* clone() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitRows() {}
    virtual ~SplitRows() {}

    /** 
     * @brief @~english Initializes the action with the number rows and the duration.
     * @~chinese ʹ��ָ�������ͳ���ʱ���ʼ��������
     * @param duration @~english Specify the duration of the SplitRows action. It's a value in seconds.
     * @~chinese ΪSplitRows����ָ������ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param rows @~english Specify the rows count should be splited.
     * @~chinese ָ��Ӧ�÷ָ��������
     * @return @~english If the creation success, return true; otherwise, return false.
     * @~chinese ��������ɹ�,����true,���򷵻�false��
     */
    bool initWithDuration(float duration, unsigned int rows);

protected:
    unsigned int _rows;
    Size _winSize;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SplitRows);
};

/**
@brief @~english SplitCols action.
 * @~chinese SplitCols������
@details @~english Split the target node in many columns.
        Then move out some columns from top, move out the other columns from bottom.
 * @~chinese ��Ŀ��ڵ�ָ�Ϊ���С�
 * Ȼ����ϱ��Ƴ�ȥһЩ��,���±��Ƴ�ȥ��һЩ�С�
*/
class CC_DLL SplitCols : public TiledGrid3DAction
{
public:
    
    /** 
     * @brief @~english Create the action with the number of columns and the duration.
     * @~chinese ʹ��ָ�������ͳ���ʱ�䴴��������
     * @param duration @~english Specify the duration of the SplitCols action. It's a value in seconds.
     * @~chinese ָΪSplitCols����ָ������ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param cols @~english Specify the columns count should be splited.
     * @~chinese ָ��Ӧ�÷ָ��������
     * @return @~english If the creation success, return a pointer of SplitCols action; otherwise, return nil.
     * @~chinese ��������ɹ�,����һ��ָ��SplitCols������ָ��;����,�����㡣
     */
    static SplitCols* create(float duration, unsigned int cols);

    // Overrides
	virtual SplitCols* clone() const override;
    /**
     * @param time @~english in seconds
     * @~chinese ����Ϊ��λ
     */
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    SplitCols() {}
    virtual ~SplitCols() {}

    /** 
     * @brief @~english Initializes the action with the number columns and the duration.
     * @~chinese ʹ��ָ�������ͳ���ʱ���ʼ��������
     * @param duration @~english Specify the duration of the SplitCols action. It's a value in seconds.
     * @~chinese ΪSplitCols����ָ������ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param cols @~english Specify the columns count should be splited.
     * @~chinese ָ��Ӧ�÷ָ��������
     * @return @~english If the creation success, return true; otherwise, return false.
     * @~chinese ��������ɹ�,����true,���򷵻�false��
     */
    bool initWithDuration(float duration, unsigned int cols);

protected:
    unsigned int _cols;
    Size _winSize;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SplitCols);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCTILEDGRID_ACTION_H__
