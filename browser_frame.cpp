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

BrowserFrame::~BrowserFrame() {
    // إزالة المتصفح من مراقبي الإعدادات
    SettingsManager::GetInstance().RemoveObserver(this);
    
    // إلغاء ارتباط مدير AUI
    m_auiManager.UnInit();
}

void BrowserFrame::CreateUI() {
    // إنشاء شريط القوائم
    CreateMenuBar();
    
    // إنشاء شريط الأدوات
    CreateBrowserToolBar();
    
    // إنشاء شريط الحالة
    CreateStatusBar();
    
    // إنشاء دفتر علامات التبويب
    m_notebook = new wxNotebook(this, wxID_ANY);
    m_auiManager.AddPane(m_notebook, wxAuiPaneInfo().Name("notebook").CenterPane().PaneBorder(false));
    
    // إنشاء اللوحات الجانبية
    CreateSidePanels();
}

void BrowserFrame::CreateMenuBar() {
    m_menuBar = new wxMenuBar();
    
    // قائمة ملف
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(BrowserConstants::ID_NEW_TAB, wxT("علامة تبويب جديدة\tCtrl+T"));
    fileMenu->Append(BrowserConstants::ID_CLOSE_TAB, wxT("إغلاق علامة التبويب\tCtrl+W"));
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, wxT("خروج\tAlt+F4"));
    m_menuBar->Append(fileMenu, wxT("ملف"));
    
    // قائمة عرض
    wxMenu* viewMenu = new wxMenu();
    viewMenu->AppendCheckItem(BrowserConstants::ID_BOOKMARKS, wxT("الإشارات المرجعية\tCtrl+B"));
    viewMenu->AppendCheckItem(BrowserConstants::ID_READER_MODE, wxT("وضع القراءة\tCtrl+R"));
    m_menuBar->Append(viewMenu, wxT("عرض"));
    
    // قائمة أدوات
    wxMenu* toolsMenu = new wxMenu();
    toolsMenu->AppendCheckItem(BrowserConstants::ID_PRIVATE_BROWSING, wxT("وضع التصفح الخاص\tCtrl+Shift+P"));
    toolsMenu->AppendSeparator();
    toolsMenu->Append(BrowserConstants::ID_SETTINGS, wxT("الإعدادات\tCtrl+,"));
    m_menuBar->Append(toolsMenu, wxT("أدوات"));
    
    SetMenuBar(m_menuBar);
}

void BrowserFrame::CreateBrowserToolBar() {
    m_toolBar = wxFrame::CreateToolBar(wxTB_FLAT | wxTB_HORIZONTAL);
    
    // إضافة أدوات شريط الأدوات مع أيقونات وتسميات غير فارغة
    m_toolBar->AddTool(BrowserConstants::ID_NEW_TAB, wxT("علامة تبويب جديدة"), 
                      wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR));
    m_toolBar->AddTool(BrowserConstants::ID_BOOKMARKS, wxT("الإشارات المرجعية"), 
                      wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_TOOLBAR));
    m_toolBar->AddTool(BrowserConstants::ID_SETTINGS, wxT("الإعدادات"), 
                      wxArtProvider::GetBitmap(wxART_HELP_SETTINGS, wxART_TOOLBAR));
    
    m_toolBar->Realize();
}

void BrowserFrame::CreateStatusBar() {
    wxFrame::CreateStatusBar();
    SetStatusText(wxT("جاهز"));
}

void BrowserFrame::CreateSidePanels() {
    // إنشاء لوحة الإشارات المرجعية
    wxPanel* bookmarksPanel = new wxPanel(this, wxID_ANY);
    m_bookmarkManager->CreateBookmarksUI(bookmarksPanel, this);
    
    // إضافة اللوحة إلى مدير AUI
    m_auiManager.AddPane(bookmarksPanel, wxAuiPaneInfo().Name("bookmarks")
                        .Caption(wxT("الإشارات المرجعية")).Right().Layer(1)
                        .MinSize(wxSize(200, 100)).Hide());
}

BrowserTab* BrowserFrame::AddBrowserTab(const wxString& url, bool select) {
    BrowserTab* tab = new BrowserTab(m_notebook, m_bookmarkManager.get(), this, m_isPrivateBrowsing);
    
    // تحميل URL
    tab->LoadURL(url);
    
    // إضافة علامة التبويب إلى الدفتر مع عنوان افتراضي
    wxString title = BrowserConstants::LOADING_TITLE;
    if (title.IsEmpty()) {
        title = wxT("جاري التحميل...");
    }
    m_notebook->AddPage(tab, title, select);
    
    return tab;
}

