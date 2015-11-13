/****************************************************************************
Copyright (c) 2010 ForzeField Studios S.L. http://forzefield.com
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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
#ifndef __CCVECTOR_H__
#define __CCVECTOR_H__

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include <vector>
#include <functional>
#include <algorithm> // for std::find

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN

/*
 * @~english
 * Similar to std::vector, but it will manage reference count automatically internally.
 * Which means it will invoke Ref::retain() when adding an element, and invoke Ref::release() when removing an element.
 * @~chinese 
 * ������std::vector,�������ڲ��Զ��������ü�����
 * ����ζ��������ӵ�ʱ�򽫵���Ref::retain()����ɾ����ʱ�򽫵���Ref::release()��
 * @warn @~english The element should be `Ref` or its sub-class.
 * @~chinese Ԫ��Ӧ��Ϊ��Ref���������ࡣ
 * @lua NA
 */
template<class T>
class Vector
{
public:
    // ------------------------------------------
    // Iterators
    // ------------------------------------------
    
    /** @~english Iterator, can be used to loop the Vector.  @~chinese ������,������ѭ������Vector��*/
    typedef typename std::vector<T>::iterator iterator;

    /** @~english Const iterator, can be used to loop the Vector.  @~chinese ����������,������ѭ������Vector��*/
    typedef typename std::vector<T>::const_iterator const_iterator;
    
    /** @~english Reversed iterator, can be used to loop the Vector in reverse sequence.  @~chinese ���������,�����ڷ���ѭ������Vector���С�*/
    typedef typename std::vector<T>::reverse_iterator reverse_iterator;

    /** @~english Reversed iterator, can be used to loop the Vector in reverse sequence.  @~chinese ���������,�����ڷ���ѭ������Vector���С�*/
    typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
    
    /** @~english Returns an iterator pointing the first element of the Vector.  @~chinese ����һ��������ָ��Vector�ĵ�һ��Ԫ�ء�*/
    iterator begin() { return _data.begin(); }

    /** @~english Returns an iterator pointing the first element of the Vector.  @~chinese ����һ��������ָ��Vector�ĵ�һ��Ԫ�ء�*/
    const_iterator begin() const { return _data.begin(); }
    
    /**
     * @~english
     * Returns an iterator referring to the `past-the-end` element in the Vector container.
     * The past-the-end element is the theoretical element that would follow the last element in the Vector.
     * It does not point to any element, and thus shall not be dereferenced.
     * @~chinese 
     * ����һ�������������еĵ�past-the-endԪ�ء�
     * past-the-endԪ���ǰ���Vector�е����һ��Ԫ�ء�
     * ����ָ���κ�Ԫ��,��˲��ܷ������á�
     */
    iterator end() { return _data.end(); }

    /**
     * @~english
     * Returns iterator referring to the `past-the-end` element in the Vector container.
     * The past-the-end element is the theoretical element that would follow the last element in the Vector.
     * It does not point to any element, and thus shall not be dereferenced.
     * @~chinese 
     * ����һ�������������еĵ�past-the-endԪ�ء�
     * past-the-endԪ���ǰ���Vector�е����һ��Ԫ�ء�
     * ����ָ���κ�Ԫ��,��˲��ܷ������á�
     */
    const_iterator end() const { return _data.end(); }
    
    /** @~english Returns a const_iterator pointing the first element of the Vector.  @~chinese ����һ��const_iteratorָ��Vector�ĵ�һ��Ԫ�ء�*/
    const_iterator cbegin() const { return _data.cbegin(); }

    /** @~english Returns a const_iterator pointing the `past-the-end` element of the Vector.  @~chinese ����һ��const_iteratorָ��Vector��past-the-endԪ�ء�*/
    const_iterator cend() const { return _data.cend(); }
    
    /** @~english Returns a reverse iterator pointing to the last element of the Vector.  @~chinese ����һ�����������ָ��Vector�����һ��Ԫ�ء�*/
    reverse_iterator rbegin() { return _data.rbegin(); }

    /** @~english Returns a reverse iterator pointing to the last element of the Vector.  @~chinese ����һ�����������ָ��Vector�����һ��Ԫ�ء�*/
    const_reverse_iterator rbegin() const { return _data.rbegin(); }
    
    /**
     * @~english Returns a reverse iterator pointing to the theoretical element preceding the
     * first element of the vector (which is considered its reverse end).
     * @~chinese ����һ�������������ָ��Vector�ĵ�һԪ��ǰ���theoreticalԪ�أ��ⱻ��Ϊ�����ķ������һ������
     */
    reverse_iterator rend() { return _data.rend(); }

    /**
     * @~english Returns a reverse iterator pointing to the theoretical element preceding the
     * first element of the vector (which is considered its reverse end).
     * @~chinese ����һ�������������ָ��Vector�ĵ�һԪ��ǰ���theoreticalԪ�أ��ⱻ��Ϊ�����ķ������һ������
     */
    const_reverse_iterator rend() const { return _data.rend(); }
    
    /** @~english Returns a const_reverse_iterator pointing to the last element in the container  @~chinese ����һ��const_reverse_iteratorָ�����һ��Ԫ�ص����� */
    const_reverse_iterator crbegin() const { return _data.crbegin(); }

    /**
     * @~english Returns a const_reverse_iterator pointing to the theoretical element preceding the first element in
     * the container (which is considered its reverse end). 
     * @~chinese ����һ��const_reverse_iteratorָ�������е�һ��theoreticalԪ�أ��ⱻ��Ϊ�����ķ������һ����
     */
    const_reverse_iterator crend() const { return _data.crend(); }
    
    /** @~english Constructor.  @~chinese ���캯���� */
    Vector<T>()
    : _data()
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
    }
    
    /**
     * @~english
     * Constructor with a capacity. 
     * @~chinese 
     * ���캯����ʹ��capacity���졣
     * @param capacity @~english Capacity of the Vector.
     * @~chinese Vector��Capacity��
     */
    explicit Vector<T>(ssize_t capacity)
    : _data()
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
        CCLOGINFO("In the default constructor with capacity of Vector.");
        reserve(capacity);
    }

    /** @~english Destructor.  @~chinese ���������� */
    ~Vector<T>()
    {
        CCLOGINFO("In the destructor of Vector.");
        clear();
    }

    /** @~english Copy constructor.  @~chinese �������캯���� */
    Vector<T>(const Vector<T>& other)
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
        CCLOGINFO("In the copy constructor!");
        _data = other._data;
        addRefForAllObjects();
    }
    
    /** @~english Constructor with std::move semantic.  @~chinese ʹ��std::move���졣*/
    Vector<T>(Vector<T>&& other)
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
        CCLOGINFO("In the move constructor of Vector!");
        _data = std::move(other._data);
    }
    
    /** @~english Copy assignment operator.  @~chinese ������ֵ������� */
    Vector<T>& operator=(const Vector<T>& other)
    {
        if (this != &other) {
            CCLOGINFO("In the copy assignment operator!");
            clear();
            _data = other._data;
            addRefForAllObjects();
        }
        return *this;
    }
    
    /** @~english Copy assignment operator with std::move semantic.  @~chinese ������ֵ�������std::move���塣*/
    Vector<T>& operator=(Vector<T>&& other)
    {
        if (this != &other) {
            CCLOGINFO("In the move assignment operator!");
            clear();
            _data = std::move(other._data);
        }
        return *this;
    }
    
// Don't uses operator since we could not decide whether it needs 'retain'/'release'.
//    T& operator[](int index)
//    {
//        return _data[index];
//    }
//    
//    const T& operator[](int index) const
//    {
//        return _data[index];
//    }
    
    /**
     * @~english
     * Requests that the vector capacity be at least enough to contain n elements.
     * @~chinese 
     * Ҫ�����������������԰���n��Ԫ�ء�
     * @param capacity @~english Minimum capacity requested of the Vector.
     * @~chinese Ҫ��Vector����С������
     */
    void reserve(ssize_t n)
    {
        _data.reserve(n);
    }
    
    /**
     * @brief @~english Returns the size of the storage space currently allocated for the Vector, expressed in terms of elements.
     * @~chinese ���ص�ǰ�����Vector�Ĵ洢�ռ�Ĵ�С��
     *  @note @~english This capacity is not necessarily equal to the Vector size.
     *        It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
     * @~chinese ����capacity����һ������Vector�Ĵ�С��
     * ��������Ȼ��߸���,����Ŀռ������������������Ҫ��ÿ�������ʱ�����·��䡣
     *  @return @~english The size of the currently allocated storage capacity in the Vector, measured in terms of the number elements it can hold.
     * @~chinese ��ǰ����洢����Vector�еĴ�С,���������ɵ�Ԫ��������
     */
    ssize_t capacity() const
    {
        return _data.capacity();
    }
    
    /**
     * @brief @~english Returns the number of elements in the Vector.
     * @~chinese ����Vector��Ԫ�ص�������
     *  @note @~english This is the number of actual objects held in the Vector, which is not necessarily equal to its storage capacity.
     * @~chinese ����ʵ�ʶ����Vector������,����һ���������Ĵ洢������
     *  @return @~english The number of elements in the Vector.
     * @~chinese Vector�е�Ԫ�ص�������
     */
    ssize_t size() const
    {
        return  _data.size();
    }
    
    /** @brief @~english Returns whether the Vector is empty (i.e. whether its size is 0).
     * @~chinese ����Vector�Ƿ�Ϊ��(���������СΪ0)��
     *  @note @~english This function does not modify the container in any way. To clear the content of a vector, see Vector<T>::clear.
     * @~chinese �˹��ܲ����޸��������κη�ʽ��Ҫ���һ����������ݣ������Vector<T>::clear��
     */
    bool empty() const
    {
        return _data.empty();
    }
    
    /** @~english Returns the maximum number of elements that the Vector can hold.  @~chinese ����Vector�������ɵ����Ԫ�������� */
    ssize_t max_size() const
    {
        return _data.max_size();
    }
    
    /** @~english Returns index of a certain object, return UNIT_MAX if doesn't contain the object  @~chinese ���������Ķ���,��������������򷵻�UNIT_MAX */
    ssize_t getIndex(T object) const
    {
        auto iter = std::find(_data.begin(), _data.end(), object);
        if (iter != _data.end())
            return iter - _data.begin();

        return -1;
    }

    /**
     * @brief @~english Find the object in the Vector.
     * @~chinese ����Vector�еĶ���
     *  @param object @~english The object to find.
     * @~chinese ���Ҷ���
     *  @return @~english Returns an iterator which refers to the element that its value is equals to object.
     *          Returns Vector::end() if not found.
     * @~chinese ����һ��ָ��Ԫ�ص�iterator��
     * ����������򷵻�Vector::end()
     */
    const_iterator find(T object) const
    {
        return std::find(_data.begin(), _data.end(), object);
    }
    
    /** @brief @~english Find the object in the Vector.
     * @~chinese ����Vector�еĶ���
     *  @param object @~english The object to find.
     * @~chinese ���Ҷ���
     *  @return @~english Returns an iterator which refers to the element that its value is equals to object.
     *          Returns Vector::end() if not found.
     * @~chinese ����һ��ָ��Ԫ�ص�iterator��
     * ����������򷵻�Vector::end()
     */
    iterator find(T object)
    {
        return std::find(_data.begin(), _data.end(), object);
    }
    
    /** @~english Returns the element at position 'index' in the Vector.  @~chinese ����Ԫ����Vector�е�λ��������*/
    T at(ssize_t index) const
    {
        CCASSERT( index >= 0 && index < size(), "index out of range in getObjectAtIndex()");
        return _data[index];
    }

    /** @~english Returns the first element in the Vector.  @~chinese ����Vector�еĵ�һ��Ԫ�ء� */
    T front() const
    {
        return _data.front();
    }
    
    /** @~english Returns the last element of the Vector.  @~chinese ����Vector�����һ��Ԫ�ء�*/
    T back() const
    {
        return _data.back();
    }

    /** @~english Returns a random element of the Vector.  @~chinese ����Vector�е�һ�����Ԫ�ء�*/
    T getRandomObject() const
    {
        if (!_data.empty())
        {
            ssize_t randIdx = rand() % _data.size();
            return *(_data.begin() + randIdx);
        }
        return nullptr;
    }

    /**
     * @~english
     * Checks whether an object is in the container.
     * @~chinese 
     * ���һ�������Ƿ��������С�
     * @param object @~english The object to be checked.
     * @~chinese �����Ķ���
     * @return @~english True if the object is in the container, false if not.
     * @~chinese ��������������ﷵ��true��������ڣ��򷵻�false��
     */
    bool contains(T object) const
    {
        return( std::find(_data.begin(), _data.end(), object) != _data.end() );
    }

    /**
     * @~english
     * Checks whether two vectors are equal.
     * @~chinese 
     * �������Vector�Ƿ���ȡ�
     * @param other @~english The vector to be compared.
     * @~chinese �Ƚϵ�vector����
     * @return @~english True if two vectors are equal, false if not.
     * @~chinese �������Vector����ȵ��򷵻�true,���������򷵻�false��
     */
    bool equals(const Vector<T> &other)
    {
        ssize_t s = this->size();
        if (s != other.size())
            return false;
        
        for (ssize_t i = 0; i < s; i++)
        {
            if (this->at(i) != other.at(i))
            {
                return false;
            }
        }
        return true;
    }

    // Adds objects
    
    /** @~english Adds a new element at the end of the Vector.  @~chinese ���һ����Ԫ�ص�Vector�ڡ�*/
    void pushBack(T object)
    {
        CCASSERT(object != nullptr, "The object should not be nullptr");
        _data.push_back( object );
        object->retain();
    }
    
    /** @~english Push all elements of an existing Vector to the end of current Vector.  @~chinese ������Vector����󣬲���ָ��Vector��Ԫ�ء�*/
    void pushBack(const Vector<T>& other)
    {
        for(const auto &obj : other) {
            _data.push_back(obj);
            obj->retain();
        }
    }

    /**
     * @~english
     * Insert an object at certain index.
     * @~chinese 
     * ���ض���������һ������
     * @param index @~english The index to be inserted at.
     * @~chinese �������������
     * @param object @~english The object to be inserted.
     * @~chinese ������Ķ���
     */
    void insert(ssize_t index, T object)
    {
        CCASSERT(index >= 0 && index <= size(), "Invalid index!");
        CCASSERT(object != nullptr, "The object should not be nullptr");
        _data.insert((std::begin(_data) + index), object);
        object->retain();
    }
    
    // Removes Objects

    /** @~english Removes the last element in the Vector.  @~chinese ɾ��Vector�е����һ��Ԫ�ء�*/
    void popBack()
    {
        CCASSERT(!_data.empty(), "no objects added");
        auto last = _data.back();
        _data.pop_back();
        last->release();
    }
    
    /**
     * @~english Remove a certain object in Vector.
     * @~chinese ɾ��Vector�е�һ���ض�����
     *  @param object @~english The object to be removed.
     * @~chinese Ҫɾ���Ķ���
     *  @param removeAll @~english Whether to remove all elements with the same value.
     *                   If its value is 'false', it will just erase the first occurrence.
     * @~chinese Vector���Ƿ������Ҫɾ���Ķ���
     * �������ֵ��false����ֻ��ɾ����һ��ƥ���Ԫ�ء�
     */
    void eraseObject(T object, bool removeAll = false)
    {
        CCASSERT(object != nullptr, "The object should not be nullptr");
        
        if (removeAll)
        {
            for (auto iter = _data.begin(); iter != _data.end();)
            {
                if ((*iter) == object)
                {
                    iter = _data.erase(iter);
                    object->release();
                }
                else
                {
                    ++iter;
                }
            }
        }
        else
        {
            auto iter = std::find(_data.begin(), _data.end(), object);
            if (iter != _data.end())
            {
                _data.erase(iter);
                object->release();
            }
        }
    }

    /**
     * @brief @~english Removes from the vector with an iterator.
     * @~chinese ��Vector������ɾ����
     *  @param position @~english Iterator pointing to a single element to be removed from the Vector.
     * @~chinese ��������ָ���Vector��ɾ����һ��Ԫ�ء�
     *  @return @~english An iterator pointing to the new location of the element that followed the last element erased by the function call.
     *          This is the container end if the operation erased the last element in the sequence.
     * @~chinese һ������ָ���Ԫ�ص��µ�λ�ã�������������������ɾ�������һ��Ԫ�ء�
     * �����������β����������������е����һ��Ԫ�ء�
     */
    iterator erase(iterator position)
    {
        CCASSERT(position >= _data.begin() && position < _data.end(), "Invalid position!");
        (*position)->release();
        return _data.erase(position);
    }
    
    /**
     * @brief @~english Removes from the Vector with a range of elements (  [first, last)  ).
     * @~chinese ��Vector���Ƴ���һϵ�е�Ԫ��([��һ��Ԫ��, ���һ��Ԫ��))��
     *  @param first @~english The beginning of the range.
     * @~chinese ��ʼ�ķ�Χ��
     *  @param last @~english The end of the range, the 'last' will not be removed, it's only for indicating the end of range.
     * @~chinese �����ķ�Χ,����󡱲��ᱻɾ��,��ֻ������ָʾ�����ķ�Χ��
     *  @return @~english An iterator pointing to the new location of the element that followed the last element erased by the function call.
     *          This is the container end if the operation erased the last element in the sequence.
     * @~chinese ������ָ��Ԫ�ص���λ��,���������������������һ��Ԫ�ء�
     * �����������β����������������е����һ��Ԫ�ء�
     */
    iterator erase(iterator first, iterator last)
    {
        for (auto iter = first; iter != last; ++iter)
        {
            (*iter)->release();
        }
        
        return _data.erase(first, last);
    }
    
    /**
     * @brief @~english Removes from the Vector by index.
     * @~chinese ��Vectorɾ��������
     *  @param index @~english The index of the element to be removed from the Vector.
     * @~chinese ��Vector��ɾ����Ԫ��������
     *  @return @~english An iterator pointing to the successor of Vector[index].
     * @~chinese һ��������ָ��Vector[index]������ߡ�
     */
    iterator erase(ssize_t index)
    {
        CCASSERT(!_data.empty() && index >=0 && index < size(), "Invalid index!");
        auto it = std::next( begin(), index );
        (*it)->release();
        return _data.erase(it);
    }

    /**
     * @brief @~english Removes all elements from the Vector (which are destroyed), leaving the container with a size of 0.
     * @~chinese ��Vector��ɾ������Ԫ��,ʹ�����Ĵ�С��Ϊ0��
     *  @note @~english All the elements in the Vector will be released (reference count will be decreased).
     * @~chinese ����Vector�е�Ԫ�ؽ����ͷţ�reference�������٣���
     */
    void clear()
    {
        for( auto it = std::begin(_data); it != std::end(_data); ++it ) {
            (*it)->release();
        }
        _data.clear();
    }

    // Rearranging Content

    /** @~english Swap the values object1 and object2.  @~chinese ����Object1��Object2��ֵ��*/
    void swap(T object1, T object2)
    {
        ssize_t idx1 = getIndex(object1);
        ssize_t idx2 = getIndex(object2);

        CCASSERT(idx1>=0 && idx2>=0, "invalid object index");

        std::swap( _data[idx1], _data[idx2] );
    }
    
    /** @~english Swap two elements by indexes.  @~chinese ��������Ԫ�ص�������*/
    void swap(ssize_t index1, ssize_t index2)
    {
        CCASSERT(index1 >=0 && index1 < size() && index2 >= 0 && index2 < size(), "Invalid indices");

        std::swap( _data[index1], _data[index2] );
    }

    /** @~english Replace value at index with given object.  @~chinese �ڶ������и��������滻ֵ��*/
    void replace(ssize_t index, T object)
    {
        CCASSERT(index >= 0 && index < size(), "Invalid index!");
        CCASSERT(object != nullptr, "The object should not be nullptr");
        
        _data[index]->release();
        _data[index] = object;
        object->retain();
    }

    /** @~english Reverses the Vector.  @~chinese �ߵ�Vector��*/
    void reverse()
    {
        std::reverse( std::begin(_data), std::end(_data) );
    }
    
    /** @~english Requests the container to reduce its capacity to fit its size.  @~chinese ������������������С. */
    void shrinkToFit()
    {
        _data.shrink_to_fit();
    }
    
protected:
    
    /** @~english Retains all the objects in the vector  @~chinese �����������е����ж��� */
    void addRefForAllObjects()
    {
        for(const auto &obj : _data) {
            obj->retain();
        }
    }
    
    std::vector<T> _data;
};

// end of base group
/** @} */

NS_CC_END

#endif // __CCVECTOR_H__
