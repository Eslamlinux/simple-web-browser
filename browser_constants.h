#pragma once

#include <wx/wx.h>

/**
 * ثوابت المتصفح
 * فئة تحتوي على جميع الثوابت المستخدمة في المتصفح
 */
namespace BrowserConstants {
    // معرفات الأحداث
    enum EventIds {
        ID_NEW_TAB = wxID_HIGHEST + 1000,
        ID_CLOSE_TAB,
        ID_BOOKMARKS,
        ID_PRIVATE_BROWSING,
        ID_READER_MODE,
        ID_SETTINGS,
        ID_REMOVE_BOOKMARK
    };
    
    // ثوابت عامة
    const wxString APP_NAME = wxT("متصفح الويب الخفيف");
    const wxString DEFAULT_HOMEPAGE = wxT("https://www.google.com");
    const wxString DEFAULT_SEARCH_ENGINE = wxT("https://www.google.com/search?q=");
    const wxString DEFAULT_TAB_TITLE = wxT("صفحة جديدة");
    const wxString LOADING_TITLE = wxT("جاري التحميل...");
    const wxString UNTITLED_PAGE = wxT("صفحة بدون عنوان");
    const wxString UNTITLED_BOOKMARK = wxT("إشارة مرجعية بدون عنوان");
    const wxString PRIVATE_MODE_SUFFIX = wxT(" (وضع التصفح الخاص)");
    const wxString READER_MODE_SUFFIX = wxT(" (وضع القراءة)");
    
    // أبعاد النافذة الافتراضية
    const int DEFAULT_WINDOW_WIDTH = 1024;
    const int DEFAULT_WINDOW_HEIGHT = 768;
    
    // إعدادات افتراضية
    const int DEFAULT_FONT_SIZE = 16;
    const bool DEFAULT_ENABLE_JAVASCRIPT = true;
    const bool DEFAULT_BLOCK_POPUPS = true;
    const bool DEFAULT_CLEAR_HISTORY_ON_EXIT = false;
    const bool DEFAULT_RESTORE_SESSION = true;
}
