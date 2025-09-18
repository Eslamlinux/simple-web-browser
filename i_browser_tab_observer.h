#pragma once

#include <wx/wx.h>
#include "i_observer.h"

/**
 * واجهة مراقب علامة التبويب
 * تستخدم للإشعار بأحداث علامة التبويب
 */
class IBrowserTabObserver : public IObserver {
public:
    /**
     * يتم استدعاؤها عند تغيير عنوان الصفحة
     * @param tab علامة التبويب التي تغير عنوانها
     * @param title العنوان الجديد
     */
    virtual void OnTitleChanged(wxWindow* tab, const wxString& title) = 0;
    
    /**
     * يتم استدعاؤها عند تغيير URL الصفحة
     * @param tab علامة التبويب التي تغير URL الخاص بها
     * @param url العنوان الجديد
     */
    virtual void OnURLChanged(wxWindow* tab, const wxString& url) = 0;
    
    /**
     * يتم استدعاؤها عند إضافة إشارة مرجعية
     * @param title عنوان الإشارة المرجعية
     * @param url رابط الإشارة المرجعية
     */
    virtual void OnBookmarkAdded(const wxString& title, const wxString& url) = 0;
};
