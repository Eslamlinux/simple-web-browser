#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/aui/aui.h>
#include <vector>
#include <memory>
#include "browser_tab.h"
#include "bookmark_manager.h"
#include "i_browser_tab_observer.h"
#include "i_bookmark_observer.h"
#include "i_settings_observer.h"
#include "browser_constants.h"

/**
 * النافذة الرئيسية للمتصفح
 * تمثل النافذة الرئيسية للمتصفح وتتعامل مع علامات التبويب والقوائم
 */
class BrowserFrame : public wxFrame, public IBrowserTabObserver, public IBookmarkObserver, public ISettingsObserver {
public:
    /**
     * المنشئ
     */
    BrowserFrame();
    
    /**
     * الهادم
     */
    virtual ~BrowserFrame();
    
    // تنفيذ واجهة مراقب علامة التبويب
    virtual void OnTitleChanged(wxWindow* tab, const wxString& title) override;
    virtual void OnURLChanged(wxWindow* tab, const wxString& url) override;
    virtual void OnBookmarkAdded(const wxString& title, const wxString& url) override;
    
    // تنفيذ واجهة مراقب الإشارات المرجعية
    virtual void OnBookmarkSelected(const Bookmark& bookmark) override;
    virtual void OnBookmarkActivated(const Bookmark& bookmark) override;
    
    // تنفيذ واجهة مراقب الإعدادات
    virtual void OnSettingsChanged() override;
    
private:
    // مكونات واجهة المستخدم
    wxNotebook* m_notebook;                         ///< دفتر علامات التبويب
    wxMenuBar* m_menuBar;                           ///< شريط القوائم
    wxToolBar* m_toolBar;                           ///< شريط الأدوات
    wxAuiManager m_auiManager;                      ///< مدير AUI
    
    // مدراء المتصفح
    std::unique_ptr<BookmarkManager> m_bookmarkManager;  ///< مدير الإشارات المرجعية
    
    // حالة المتصفح
    bool m_isPrivateBrowsing;                       ///< ما إذا كان المتصفح في وضع التصفح الخاص
    
    /**
     * إنشاء واجهة المستخدم
     */
    void CreateUI();
    
    /**
     * إنشاء شريط القوائم
     */
    void CreateMenuBar();
    
    /**
     * إنشاء شريط الأدوات
     */
    void CreateBrowserToolBar();
    
    /**
     * إنشاء شريط الحالة
     */
    void CreateStatusBar();
    
    /**
     * إنشاء اللوحات الجانبية
     */
    void CreateSidePanels();
    
    /**
     * إضافة علامة تبويب جديدة
     * @param url عنوان URL المراد تحميله
     * @param select ما إذا كان يجب تحديد علامة التبويب الجديدة
     * @return مؤشر إلى علامة التبويب الجديدة
     */
    BrowserTab* AddBrowserTab(const wxString& url = BrowserConstants::DEFAULT_HOMEPAGE, bool select = true);
    
    // معالجات الأحداث
    void OnNewTab(wxCommandEvent& event);
    void OnCloseTab(wxCommandEvent& event);
    void OnBookmarks(wxCommandEvent& event);
    void OnTogglePrivateBrowsing(wxCommandEvent& event);
    void OnToggleReaderMode(wxCommandEvent& event);
    void OnSettings(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    
    /**
     * الحصول على علامة التبويب الحالية
     * @return مؤشر إلى علامة التبويب الحالية، أو nullptr إذا لم تكن هناك علامة تبويب
     */
    BrowserTab* GetCurrentTab() const;
    
    /**
     * حفظ الجلسة
     */
    void SaveSession();
    
    /**
     * استعادة الجلسة
     */
    void RestoreSession();
    
    /**
     * التحقق من صحة عناصر القائمة
     * التأكد من أن جميع عناصر القائمة لها تسميات غير فارغة
     */
    void ValidateMenuItems();
    
    wxDECLARE_EVENT_TABLE();
};
