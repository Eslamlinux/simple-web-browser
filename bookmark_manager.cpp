#include "bookmark_manager.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "browser_constants.h"

BookmarkManager::BookmarkManager()
    : m_bookmarksList(nullptr),
      m_removeButton(nullptr)
{
    // تحميل الإشارات المرجعية المحفوظة
    LoadBookmarks();
}

BookmarkManager::~BookmarkManager() {
    // حفظ الإشارات المرجعية عند الخروج
    SaveBookmarks();
}

bool BookmarkManager::AddBookmark(const wxString& title, const wxString& url) {
    // التحقق من عدم وجود الإشارة المرجعية بالفعل
    if (HasBookmark(url)) {
        return false;
    }
    
    // التحقق من عدم وجود عنوان فارغ
    wxString bookmarkTitle = title;
    if (bookmarkTitle.IsEmpty()) {
        bookmarkTitle = BrowserConstants::UNTITLED_BOOKMARK;
    }
    
    // إضافة إشارة مرجعية جديدة
    m_bookmarks.emplace_back(bookmarkTitle, url);
    
    // تحديث واجهة المستخدم
    UpdateUI();
    
    // حفظ الإشارات المرجعية
    SaveBookmarks();
    
    return true;
}

bool BookmarkManager::RemoveBookmark(size_t index) {
    if (index >= m_bookmarks.size()) {
        return false;
    }
    
    m_bookmarks.erase(m_bookmarks.begin() + index);
    
    // تحديث واجهة المستخدم
    UpdateUI();
    
    // حفظ الإشارات المرجعية
    SaveBookmarks();
    
    return true;
}

bool BookmarkManager::HasBookmark(const wxString& url) const {
    return std::any_of(m_bookmarks.begin(), m_bookmarks.end(),
                      [&url](const Bookmark& bookmark) { return bookmark.GetUrl() == url; });
}

const std::vector<Bookmark>& BookmarkManager::GetBookmarks() const {
    return m_bookmarks;
}

void BookmarkManager::CreateBookmarksUI(wxWindow* parent, IBookmarkObserver* observer) {
    // إضافة المراقب
    if (observer) {
        AddObserver(observer);
    }
    
    // إنشاء عناصر واجهة المستخدم
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // إنشاء قائمة الإشارات المرجعية
    m_bookmarksList = new wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                    wxLC_REPORT | wxLC_SINGLE_SEL);
    
    // إضافة الأعمدة
    m_bookmarksList->InsertColumn(0, wxT("العنوان"), wxLIST_FORMAT_LEFT, 200);
    m_bookmarksList->InsertColumn(1, wxT("الرابط"), wxLIST_FORMAT_LEFT, 300);
    
    // إضافة زر الحذف
    m_removeButton = new wxButton(parent, BrowserConstants::ID_REMOVE_BOOKMARK, wxT("حذف"));
    m_removeButton->Enable(false);
    
    // إضافة العناصر إلى التخطيط
    mainSizer->Add(m_bookmarksList, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(m_removeButton, 0, wxALL, 5);
    
    parent->SetSizer(mainSizer);
    
    // ربط الأحداث
    m_bookmarksList->Bind(wxEVT_LIST_ITEM_SELECTED, &BookmarkManager::OnBookmarkSelected, this);
    m_bookmarksList->Bind(wxEVT_LIST_ITEM_ACTIVATED, &BookmarkManager::OnBookmarkActivated, this);
    m_removeButton->Bind(wxEVT_BUTTON, &BookmarkManager::OnRemoveBookmark, this);
    
    // تحديث القائمة
    UpdateBookmarksList();
}

void BookmarkManager::AddObserver(IBookmarkObserver* observer) {
    if (observer && std::find(m_observers.begin(), m_observers.end(), observer) == m_observers.end()) {
        m_observers.push_back(observer);
    }
}

void BookmarkManager::RemoveObserver(IBookmarkObserver* observer) {
    auto it = std::find(m_observers.begin(), m_observers.end(), observer);
    if (it != m_observers.end()) {
        m_observers.erase(it);
    }
}

void BookmarkManager::UpdateUI() {
    if (m_bookmarksList) {
        UpdateBookmarksList();
    }
}

void BookmarkManager::UpdateBookmarksList() {
    if (!m_bookmarksList) {
        return;
    }
    
    // مسح القائمة
    m_bookmarksList->DeleteAllItems();
    
    // إضافة الإشارات المرجعية
    for (size_t i = 0; i < m_bookmarks.size(); ++i) {
        const auto& bookmark = m_bookmarks[i];
        
        // التأكد من عدم وجود عناوين فارغة
        wxString title = bookmark.GetTitle();
        if (title.IsEmpty()) {
            title = BrowserConstants::UNTITLED_BOOKMARK;
        }
        
        long itemIndex = m_bookmarksList->InsertItem(i, title);
        m_bookmarksList->SetItem(itemIndex, 1, bookmark.GetUrl());
    }
}

void BookmarkManager::SaveBookmarks() {
    // الحصول على مسار الملف
    wxString filePath = GetBookmarksFilePath();
    
    // إنشاء المجلد إذا لم يكن موجوداً
    wxString dirPath = wxFileName(filePath).GetPath();
    wxFileName::Mkdir(dirPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
    
    // فتح الملف للكتابة
    std::ofstream file(filePath.ToStdString());
    if (!file.is_open()) {
        wxLogError("فشل في فتح ملف الإشارات المرجعية للكتابة: %s", filePath);
        return;
    }
    
    // كتابة الإشارات المرجعية
    for (const auto& bookmark : m_bookmarks) {
        file << bookmark.GetTitle().ToUTF8() << "\t"
             << bookmark.GetUrl().ToUTF8() << "\t"
             << bookmark.GetDateAdded().FormatISODate().ToUTF8() << "\n";
    }
    
    file.close();
}

void BookmarkManager::LoadBookmarks() {
    // الحصول على مسار الملف
    wxString filePath = GetBookmarksFilePath();
    
    // التحقق من وجود الملف
    if (!wxFileExists(filePath)) {
        return;
    }
    
}
