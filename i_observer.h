
/**
 * واجهة المراقب الأساسية
 * تستخدم كأساس لجميع واجهات المراقب في المتصفح
 */
class IObserver {
public:
    /**
     * الهادم الافتراضي
     */
    virtual ~IObserver() = default;
};
