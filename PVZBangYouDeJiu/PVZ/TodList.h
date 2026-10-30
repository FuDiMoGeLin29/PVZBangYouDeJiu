#ifndef __TODLIST_H__
#define __TODLIST_H__

#define MAX_GLOBAL_ALLOCATORS 128

#include "TodCommon.h"
#include "TodDebug.h"

struct TodAllocator
{
    void*				mFreeList;
    void*				mBlockList;
    int					mGrowCount;
    int					mTotalItems;
    int					mItemSize;

    //void                Initialize(int theGrowCount, int theItemSize);
    //void                Dispose();
    //void                FreeAll();
    //void*               Alloc(int theItemSize);
    //void*               Calloc(int theItemSize);
    //void                Free(void* theItem, int theItemSize);
    //void                Grow();
    //bool                IsPointerFromAllocator(void* theItem);
    //bool                IsPointerOnFreeList(void* theItem);
};

//extern int gNumGlobalAllocators;
//extern TodAllocator gGlobalAllocators[MAX_GLOBAL_ALLOCATORS];

template <typename T> class TodListNode
{
public:
	T					mValue;
	TodListNode<T>*		mNext;
	TodListNode<T>*		mPrev;
};

template <typename T> class TodList
{
public:
    using value_type        = T;
    using size_type         = int;
    using node_type         = TodListNode<value_type>;
    using node_pointer      = node_type*;
    using iterator          = void*;
    using reference         = value_type&;
    using const_reference   = const value_type&;

public:
    node_pointer		    mHead;
    node_pointer		    mTail;
    size_type			    mSize;
	TodAllocator*		    mpAllocator;

public:
    //TodList()
    //{
    //    mHead = nullptr;
    //    mTail = nullptr;
    //    mSize = 0;
    //    mpAllocator = nullptr;
    //}

    //TodList(TodAllocator* theAllocator)
    //{
    //    mHead = nullptr;
    //    mTail = nullptr;
    //    mSize = 0;
    //    mpAllocator = theAllocator;
    //}

    //~TodList()
    //{
    //    RemoveAll();
    //}

    //void SetAllocator(TodAllocator* theAllocator)
    //{
    //    TOD_ASSERT(mSize == 0);
    //    mpAllocator = theAllocator;
    //}

    //TodList& operator=(const TodList& theList)
    //{
    //    if (this == std::addressof(theList))
    //        return *this;
    //    
    //    RemoveAll();
    //    SetAllocator(theList.mpAllocator);

    //    for (node_pointer aNode = theList->mHead; aNode; aNode = aNode->mNext)
    //    {
    //        AddHead(aNode->mValue);
    //    }

    //    return *this;
    //}

    //TodList& operator=(TodList&& theList)
    //{
    //    RemoveAll();
    //    SetAllocator(theList.mpAllocator);
    //    
    //    mHead = theList.mHead; theList.mHead = nullptr;
    //    mTail = theList.mTail; theList.mTail = nullptr;
    //    mSize = theList.mSize; theList.mSize = 0;

    //    return *this;
    //}

    //size_type GetSize()
    //{
    //    return mSize;
    //}

    //bool IsEmpty()
    //{
    //    return GetSize() == 0;
    //}

    //reference GetHead()
    //{
    //    TOD_ASSERT(mHead != nullptr);
    //    return mHead->mValue;
    //}

    //reference GetTail()
    //{
    //    TOD_ASSERT(mTail != nullptr);
    //    return mTail->mValue;
    //}

    //void AddHead(const_reference theHead)
    //{
    //    if (mpAllocator == nullptr)
    //        mpAllocator = FindGlobalAllocator(sizeof(node_type));

    //    node_pointer aNode = (node_pointer)mpAllocator->Calloc(sizeof(node_type));
    //    if (aNode)
    //        aNode->mValue = theHead;
    //    aNode->mNext = mHead;  // 新节点的下一个节点指向原节点
    //    aNode->mPrev = nullptr;  // 新节点作为头部，不存在上一个节点
    //    if (mHead)
    //        mHead->mPrev = aNode;  // 已存在头部节点时，令原头部节点的上一个节点指向该新节点
    //    else
    //        mTail = aNode;  // 不存在头部节点时，尾部节点也为该新节点
    //    mSize++;
    //    mHead = aNode;
    //}

    //void AddTail(const_reference theTail)
    //{
    //    if (mpAllocator == nullptr)
    //        mpAllocator = FindGlobalAllocator(sizeof(node_type));

    //    node_pointer aNode = (node_pointer)mpAllocator->Calloc(sizeof(node_type));
    //    if (aNode)
    //        aNode->mValue = theTail;
    //    aNode->mNext = nullptr;
    //    aNode->mPrev = mTail;
    //    if (mTail)
    //        mTail->mNext = aNode;
    //    else
    //        mHead = aNode;
    //    mSize++;
    //    mTail = aNode;
    //}

    //value_type RemoveHead()
    //{
    //    node_pointer aHead = mHead;
    //    node_pointer aSecNode = aHead->mNext;
    //    mHead = aSecNode;
    //    if (aSecNode)  // 如果移除后还剩有节点
    //        aSecNode->mPrev = nullptr;
    //    else  // 如果移除了最后一个节点
    //        mTail = nullptr;
    //    
    //    value_type aVal = aHead->mValue;
    //    mSize--;
    //    mpAllocator->Free(aHead, sizeof(node_type));
    //    return aVal;
    //}

    //value_type RemoveTail()
    //{
    //    node_pointer aTail = mTail;
    //    node_pointer aSecTail = aTail->mPrev;
    //    mTail = aSecTail;
    //    if (aSecTail)  // 如果移除后还剩有节点
    //        aSecTail->mNext = nullptr;
    //    else  // 如果移除了最后一个节点
    //        mHead = nullptr;

    //    value_type aVal = aTail->mValue;
    //    mSize--;
    //    mpAllocator->Free(aTail, sizeof(node_type));
    //    return aVal;
    //}

    //iterator InsertBefore(iterator theWhere, const_reference theItem)
    //{
    //    node_pointer aWhereNod = (node_pointer)theWhere;

    //    TOD_ASSERT(mpAllocator);
    //    node_pointer aNode = (node_pointer)mpAllocator->Calloc(sizeof(node_type));
    //    if (aNode)
    //        aNode->mValue = theItem;

    //    if (aWhereNod->mPrev)
    //    {
    //        aWhereNod->mPrev->mNext = aNode;
    //        aNode->mPrev = aWhereNod->mPrev;
    //    }
    //    else
    //        mHead = aNode;

    //    aWhereNod->mPrev = aNode;
    //    aNode->mNext = aWhereNod;
    //    mSize++;

    //    return iterator(aNode);
    //}

    //void InsertList(iterator theWhere, const TodList& theList)
    //{
    //    for (node_pointer aNode = theList.mHead; aNode; aNode = aNode->mNext)
    //    {
    //        InsertBefore(theWhere, aNode->mValue);
    //    }
    //}

    //iterator RemoveAt(iterator theWhere)
    //{
    //    node_pointer aWhereNod = (node_pointer)theWhere;

    //    if (aWhereNod->mPrev != nullptr)
    //        aWhereNod->mPrev->mNext = aWhereNod->mNext;
    //    else
    //        mHead = aWhereNod->mNext;

    //    if (aWhereNod->mNext != nullptr)
    //        aWhereNod->mNext->mPrev = aWhereNod->mPrev;
    //    else
    //        mTail = aWhereNod->mPrev;

    //    mSize--;
    //    mpAllocator->Free(aWhereNod, sizeof(node_type));
    //    return iterator(aWhereNod->mNext);
    //}

    //iterator Find(const_reference theItem) const
    //{
    //    for (node_pointer aNode = mHead; aNode != nullptr; aNode = aNode->mNext)
    //        if (aNode->mValue == theItem)
    //            return iterator(aNode);
    //    return iterator(nullptr);
    //}

    //iterator GetHeadIter()
    //{
    //    return iterator(mHead);
    //}

    //iterator GetTailIter()
    //{
    //    return iterator(mTail);
    //}

    //reference GetNextIter(iterator& theIter)
    //{
    //    node_pointer aWhereNod = (node_pointer)theIter;
    //    reference aValue = aWhereNod->mValue;
    //    theIter = iterator(aWhereNod->mNext);
    //    return aValue;
    //}

    //reference GetPrevIter(iterator& theIter)
    //{
    //    node_pointer aWhereNod = (node_pointer)theIter;
    //    reference aValue = aWhereNod->mValue;
    //    theIter = iterator(aWhereNod->mPrev);
    //    return aValue;
    //}

    //void RemoveAll()
    //{
    //    node_pointer aNode = mHead;
    //    while (aNode)
    //    {
    //        node_pointer temp = aNode;
    //        aNode = aNode->mNext;
    //        mpAllocator->Free(temp, sizeof(node_type));
    //    }

    //    mSize = 0;
    //    mHead = nullptr;
    //    mTail = nullptr;
    //}
};

#endif
