#pragma once

#include "i_observer.h"
#include "bookmark.h"

/**
 * واجهة مراقب الإشارات المرجعية
 * تستخدم للإشعار بأحداث الإشارات المرجعية
 */
class IBookmarkObserver : public IObserver {
public:
    /**
     * يتم استدعاؤها عند تحديد إشارة مرجعية
     * @param bookmark الإشارة المرجعية المحددة
     */
    virtual void OnBookmarkSelected(const Bookmark& bookmark) = 0;
    
    /**
     * يتم استدعاؤها عند تنشيط إشارة مرجعية (مثل النقر المزدوج)
     * @param bookmark الإشارة المرجعية المنشطة
     */
    virtual void OnBookmarkActivated(const Bookmark& bookmark) = 0;
};
