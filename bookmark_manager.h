#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <memory>
#include "bookmark.h"
#include "i_bookmark_observer.h"

/**
 * مدير الإشارات المرجعية
 * يتعامل مع إضافة وإزالة وعرض الإشارات المرجعية
 */
class BookmarkManager {
public:
    /**
     * المنشئ
     */
    BookmarkManager();
    
    /**
     * الهادم
     */
    ~BookmarkManager();
    
    /**
     * إضافة إشارة مرجعية جديدة
     * @param title عنوان الإشارة المرجعية
     * @param url رابط الإشارة المرجعية
     * @return true إذا تمت الإضافة بنجاح، false إذا كانت الإشارة المرجعية موجودة بالفعل
     */
    bool AddBookmark(const wxString& title, const wxString& url);
    
    /**
     * حذف إشارة مرجعية
     * @param index فهرس الإشارة المرجعية المراد حذفها
     * @return true إذا تم الحذف بنجاح، false إذا كان الفهرس غير صالح
     */
    bool RemoveBookmark(size_t index);
    
    /**
     * التحقق من وجود إشارة مرجعية
     * @param url رابط الإشارة المرجعية
     * @return true إذا كانت الإشارة المرجعية موجودة، false إذا لم تكن موجودة
     */
    bool HasBookmark(const wxString& url) const;
    
    /**
     * الحصول على قائمة الإشارات المرجعية
     * @return مرجع ثابت لقائمة الإشارات المرجعية
     */
    const std::vector<Bookmark>& GetBookmarks() const;
    
    /**
     * إنشاء واجهة مستخدم الإشارات المرجعية
     * @param parent النافذة الأم
     * @param observer مراقب الإشارات المرجعية
     */
    void CreateBookmarksUI(wxWindow* parent, IBookmarkObserver* observer);
    
    /**
     * إضافة مراقب للإشارات المرجعية
     * @param observer المراقب المراد إضافته
     */
    void AddObserver(IBookmarkObserver* observer);
    
    /**
     * إزالة مراقب للإشارات المرجعية
     * @param observer المراقب المراد إزالته
     */
    void RemoveObserver(IBookmarkObserver* observer);


};
