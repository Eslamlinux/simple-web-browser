#pragma once

#include <wx/wx.h>
#include <wx/webview.h>
#include "bookmark_manager.h"
#include "i_browser_tab_observer.h"
#include "settings_manager.h"

/**
 * علامة تبويب المتصفح
 * تمثل علامة تبويب واحدة في المتصفح
 */
class BrowserTab : public wxPanel {
public:
    /**
     * المنشئ
     * @param parent النافذة الأم
     * @param bookmarkManager مدير الإشارات المرجعية
     * @param observer مراقب علامة التبويب
     * @param privateBrowsing ما إذا كانت علامة التبويب في وضع التصفح الخاص
     */
    BrowserTab(wxWindow* parent, BookmarkManager* bookmarkManager, IBrowserTabObserver* observer, bool privateBrowsing = false);
    
    /**
     * الهادم
     */
    virtual ~BrowserTab();
    
    /**
     * تحميل URL
     * @param url عنوان URL المراد تحميله
     */
    void LoadURL(const wxString& url);
    
    /**
     * الحصول على URL الحالي
     * @return عنوان URL الحالي
     */
    wxString GetCurrentURL() const;
    
    /**
     * الحصول على العنوان الحالي
     * @return العنوان الحالي
     */
    wxString GetCurrentTitle() const;
    
    /**
     * الحصول على عنصر عرض الويب
     * @return مؤشر إلى عنصر عرض الويب
     */
    wxWebView* GetWebView() const;
    
    /**
     * تبديل وضع القراءة
     * @param enable ما إذا كان يجب تمكين وضع القراءة
     */
    void ToggleReaderMode(bool enable);
    
    /**
     * تعيين وضع التصفح الخاص
     * @param enable ما إذا كان يجب تمكين وضع التصفح الخاص
     */
    void SetPrivateBrowsing(bool enable);
    
    /**
     * تطبيق إعدادات المتصفح
     */
    void ApplySettings();
    
private:
    // مكونات واجهة المستخدم
    wxWebView* m_webView;           ///< عنصر عرض الويب
    wxTextCtrl* m_addressBar;       ///< شريط العناوين
    wxButton* m_backButton;         ///< زر الرجوع
    wxButton* m_forwardButton;      ///< زر التقدم
    wxButton* m_refreshButton;      ///< زر التحديث
    wxButton* m_bookmarkButton;     ///< زر الإشارة المرجعية
    wxButton* m_readerModeButton;   ///< زر وضع القراءة
    
    // المدراء والمراقبون
    BookmarkManager* m_bookmarkManager;  ///< مدير الإشارات المرجعية
    IBrowserTabObserver* m_observer;     ///< مراقب علامة التبويب
    
    // الحالة
    bool m_isPrivateBrowsing;       ///< ما إذا كانت علامة التبويب في وضع التصفح الخاص
    bool m_isReaderMode;            ///< ما إذا كانت علامة التبويب في وضع القراءة
    wxString m_originalContent;     ///< المحتوى الأصلي للصفحة (للاستخدام في وضع القراءة)
    wxString m_currentTitle;        ///< العنوان الحالي للصفحة
    
    /**
     * إنشاء واجهة المستخدم
     */
    void CreateUI();
    
    /**
     * تهيئة أحداث علامة التبويب
     */
    void InitializeEvents();
    
    // معالجات الأحداث
    void OnAddressEnter(wxCommandEvent& event);
    void OnBack(wxCommandEvent& event);
    void OnForward(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);
    void OnBookmark(wxCommandEvent& event);
    void OnReaderMode(wxCommandEvent& event);
    void OnNavigating(wxWebViewEvent& event);
    void OnNavigated(wxWebViewEvent& event);
    void OnTitleChanged(wxWebViewEvent& event);
    void OnError(wxWebViewEvent& event);
    
    /**
     * تطبيق وضع القراءة
     */
    void ApplyReaderMode();
    
    /**
     * تنظيف الكوكيز والبيانات
     */
    void ClearBrowsingData();
};
