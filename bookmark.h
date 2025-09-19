#pragma once

#include <wx/wx.h>
#include <wx/datetime.h>

/**
 * فئة الإشارة المرجعية
 * تمثل إشارة مرجعية واحدة في المتصفح
 */
class Bookmark {
public:
    /**
     * المنشئ
     * @param title عنوان الإشارة المرجعية
     * @param url رابط الإشارة المرجعية
     */
    Bookmark(const wxString& title, const wxString& url)
        : m_title(title), m_url(url), m_dateAdded(wxDateTime::Now()) {}
    
    /**
     * الحصول على عنوان الإشارة المرجعية
     * @return عنوان الإشارة المرجعية
     */
    const wxString& GetTitle() const { return m_title; }
    
    /**
     * الحصول على رابط الإشارة المرجعية
     * @return رابط الإشارة المرجعية
     */
    const wxString& GetUrl() const { return m_url; }
    
    /**
     * الحصول على تاريخ إضافة الإشارة المرجعية
     * @return تاريخ الإضافة
     */
    const wxDateTime& GetDateAdded() const { return m_dateAdded; }
    
    /**
     * تعيين تاريخ إضافة الإشارة المرجعية
     * @param date التاريخ الجديد
     */
    void SetDateAdded(const wxDateTime& date) { m_dateAdded = date; }

private:
    wxString m_title;       ///< عنوان الإشارة المرجعية
    wxString m_url;         ///< رابط الإشارة المرجعية
    wxDateTime m_dateAdded; ///< تاريخ إضافة الإشارة المرجعية
};
