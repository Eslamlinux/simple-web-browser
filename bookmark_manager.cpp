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
    
