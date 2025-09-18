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

BrowserTab* BrowserFrame::GetCurrentTab() const {
    int index = m_notebook->GetSelection();
    if (index != wxNOT_FOUND) {
        return static_cast<BrowserTab*>(m_notebook->GetPage(index));
    }
    return nullptr;
}

void BrowserFrame::OnNewTab(wxCommandEvent& event) {
    AddBrowserTab();
}

void BrowserFrame::OnCloseTab(wxCommandEvent& event) {
    int index = m_notebook->GetSelection();
    if (index != wxNOT_FOUND) {
        m_notebook->DeletePage(index);
        
        // إذا لم تعد هناك علامات تبويب، أضف واحدة جديدة
        if (m_notebook->GetPageCount() == 0) {
            AddBrowserTab();
        }
    }
}

void BrowserFrame::OnBookmarks(wxCommandEvent& event) {
    // تبديل عرض لوحة الإشارات المرجعية
    wxAuiPaneInfo& pane = m_auiManager.GetPane("bookmarks");
    pane.Show(!pane.IsShown());
    m_auiManager.Update();
    
    // تحديث حالة زر التبديل في القائمة
    wxMenuItem* item = m_menuBar->FindItem(BrowserConstants::ID_BOOKMARKS);
    if (item) {
        item->Check(pane.IsShown());
    }
}

void BrowserFrame::OnTogglePrivateBrowsing(wxCommandEvent& event) {
    m_isPrivateBrowsing = event.IsChecked();
    
    // تحديث علامات التبويب الحالية
    for (size_t i = 0; i < m_notebook->GetPageCount(); ++i) {
        BrowserTab* tab = static_cast<BrowserTab*>(m_notebook->GetPage(i));
        tab->SetPrivateBrowsing(m_isPrivateBrowsing);
    }
    
    // تحديث واجهة المستخدم
    if (m_isPrivateBrowsing) {
        SetTitle(BrowserConstants::APP_NAME + BrowserConstants::PRIVATE_MODE_SUFFIX);
        SetBackgroundColour(wxColour(50, 50, 60));
    } else {
        SetTitle(BrowserConstants::APP_NAME);
        SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    }
    
    Refresh();
}

void BrowserFrame::OnToggleReaderMode(wxCommandEvent& event) {
    BrowserTab* currentTab = GetCurrentTab();
    if (currentTab) {
        currentTab->ToggleReaderMode(event.IsChecked());
        
        // تحديث حالة زر التبديل في القائمة
        wxMenuItem* item = m_menuBar->FindItem(BrowserConstants::ID_READER_MODE);
        if (item) {
            item->Check(event.IsChecked());
        }
    }
}

void BrowserFrame::OnSettings(wxCommandEvent& event) {
    // فتح نافذة الإعدادات
    SettingsManager::GetInstance().ShowSettingsDialog(this);
}

void BrowserFrame::OnExit(wxCommandEvent& event) {
    Close();
}

void BrowserFrame::OnClose(wxCloseEvent& event) {
    // حفظ الجلسة قبل الإغلاق إذا لم نكن في وضع التصفح الخاص
    if (!m_isPrivateBrowsing) {
        SaveSession();
    }
    
    // مسح السجل عند الخروج إذا كان الإعداد مفعلًا
    if (SettingsManager::GetInstance().GetBoolSetting("clear_history_on_exit")) {
        for (size_t i = 0; i < m_notebook->GetPageCount(); ++i) {
            BrowserTab* tab = static_cast<BrowserTab*>(m_notebook->GetPage(i));
            if (tab) {
                tab->SetPrivateBrowsing(true); // يؤدي إلى مسح البيانات عند التدمير
            }
        }
    }
    
    event.Skip();
}

void BrowserFrame::SaveSession() {
    // حفظ الجلسة الحالية
    SessionManager sessionManager;
    sessionManager.ClearSession();
    
    for (size_t i = 0; i < m_notebook->GetPageCount(); ++i) {
        BrowserTab* tab = static_cast<BrowserTab*>(m_notebook->GetPage(i));
        sessionManager.AddTabURL(tab->GetCurrentURL());
    }
    
    sessionManager.SaveSession();
}

void BrowserFrame::RestoreSession() {
    // استعادة الجلسة السابقة فقط إذا لم نكن في وضع التصفح الخاص
    if (!m_isPrivateBrowsing) {
        SessionManager sessionManager;
        std::vector<wxString> urls = sessionManager.LoadSession();
        
        for (const auto& url : urls) {
            if (!url.IsEmpty()) {
                AddBrowserTab(url, false);
            }
        }
    }
}

void BrowserFrame::ValidateMenuItems() {
    if (!m_menuBar) return;
    
    // التحقق من جميع القوائم
    for (size_t i = 0; i < m_menuBar->GetMenuCount(); ++i) {
        wxMenu* menu = m_menuBar->GetMenu(i);
        wxString menuLabel = m_menuBar->GetMenuLabel(i);
        
        // التأكد من أن عنوان القائمة غير فارغ
        if (menuLabel.IsEmpty()) {
            wxLogWarning("تم العثور على قائمة بعنوان فارغ، الفهرس: %zu", i);
            m_menuBar->SetMenuLabel(i, wxString::Format("قائمة %zu", i+1));
        }
        
        // التحقق من عناصر القائمة
        wxMenuItemList& items = menu->GetMenuItems();
        for (size_t j = 0; j < items.size(); ++j) {
            wxMenuItem* item = items[j];
            
            // تخطي الفواصل
            if (item->IsSeparator()) continue;
            
            // التأكد من أن تسمية العنصر غير فارغة
            wxString label = item->GetItemLabelText();
            if (label.IsEmpty() && !wxIsStockID(item->GetId())) {
                wxLogWarning("تم العثور على عنصر قائمة بتسمية فارغة، المعرف: %d", item->GetId());
                item->SetItemLabel(wxString::Format("عنصر %zu", j+1));
            }
            
            // التحقق من القوائم الفرعية
            wxMenu* submenu = item->GetSubMenu();
            if (submenu) {
                wxMenuItemList& subItems = submenu->GetMenuItems();
                for (size_t k = 0; k < subItems.size(); ++k) {
                    wxMenuItem* subItem = subItems[k];
                    
                    // تخطي الفواصل
                    if (subItem->IsSeparator()) continue;
                    
                    // التأكد من أن تسمية العنصر الفرعي غير فارغة
                    wxString subLabel = subItem->GetItemLabelText();
                    if (subLabel.IsEmpty() && !wxIsStockID(subItem->GetId())) {
                        wxLogWarning("تم العثور على عنصر قائمة فرعي بتسمية فارغة، المعرف: %d", subItem->GetId());
                        subItem->SetItemLabel(wxString::Format("عنصر فرعي %zu", k+1));
                    }
                }
            }
        }
    }
}

// تنفيذ واجهة مراقب علامة التبويب
void BrowserFrame::OnTitleChanged(wxWindow* tab, const wxString& title) {
    int tabIndex = m_notebook->FindPage(tab);
    if (tabIndex != wxNOT_FOUND) {
        wxString pageTitle = title;
        if (pageTitle.IsEmpty()) {
            pageTitle = BrowserConstants::UNTITLED_PAGE;
            if (pageTitle.IsEmpty()) {
                pageTitle = wxT("صفحة بدون عنوان");
            }
        }
        m_notebook->SetPageText(tabIndex, pageTitle);
    }
}

void BrowserFrame::OnURLChanged(wxWindow* tab, const wxString& url) {
    // تحديث شريط الحالة بالـ URL الحالي
    SetStatusText(url);
}

void BrowserFrame::OnBookmarkAdded(const wxString& title, const wxString& url) {
    // يمكن إضافة منطق هنا للإشعار بإضافة إشارة مرجعية
    SetStatusText(wxString::Format(wxT("تمت إضافة الإشارة المرجعية: %s"), title));
}

// تنفيذ واجهة مراقب الإشارات المرجعية
void BrowserFrame::OnBookmarkSelected(const Bookmark& bookmark) {
    // يمكن إضافة منطق هنا للتعامل مع تحديد إشارة مرجعية
}

void BrowserFrame::OnBookmarkActivated(const Bookmark& bookmark) {
    // فتح الإشارة المرجعية في علامة التبويب الحالية
    BrowserTab* currentTab = GetCurrentTab();
    if (currentTab) {
        currentTab->LoadURL(bookmark.GetUrl());
    } else {
        AddBrowserTab(bookmark.GetUrl());
    }
}

// تنفيذ واجهة مراقب الإعدادات
void BrowserFrame::OnSettingsChanged() {
    // تحديث الإعدادات في جميع علامات التبويب
    for (size_t i = 0; i < m_notebook->GetPageCount(); ++i) {
        BrowserTab* tab = static_cast<BrowserTab*>(m_notebook->GetPage(i));
        if (tab) {
            tab->ApplySettings();
        }
    }
}
