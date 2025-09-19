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
    

};
