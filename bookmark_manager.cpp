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

