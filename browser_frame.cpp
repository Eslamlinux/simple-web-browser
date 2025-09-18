BrowserFrame::BrowserFrame()
    : wxFrame(nullptr, wxID_ANY, BrowserConstants::APP_NAME, 
             wxDefaultPosition, wxSize(BrowserConstants::DEFAULT_WINDOW_WIDTH, BrowserConstants::DEFAULT_WINDOW_HEIGHT)),
      m_isPrivateBrowsing(false),
      m_bookmarkManager(std::make_unique<BookmarkManager>())
{
    // تهيئة مدير AUI
    m_auiManager.SetManagedWindow(this);
    
    // إضافة المتصفح كمراقب للإعدادات
    SettingsManager::GetInstance().AddObserver(this);
    
    // إنشاء واجهة المستخدم
    CreateUI();
    
    // التحقق من عناصر القائمة
    ValidateMenuItems();
    
    // استعادة الجلسة السابقة إذا كان مسموحًا
    if (SettingsManager::GetInstance().GetBoolSetting("restore_session", true)) {
        RestoreSession();
    }
    
    // إذا لم تكن هناك علامات تبويب، أضف واحدة جديدة
    if (m_notebook->GetPageCount() == 0) {
        AddBrowserTab();
    }
    
    // تحديث واجهة المستخدم
    m_auiManager.Update();
}

