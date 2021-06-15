#if !defined(AFX_PROFILE_H__9727648F_2E45_4F46_9386_117F540772DD__INCLUDED_)
#define AFX_PROFILE_H__9727648F_2E45_4F46_9386_117F540772DD__INCLUDED_

#include <dhnetsdk.h>

class CProfile
{
public:
    CProfile();
    virtual ~CProfile();

public: // interface
    static DWORD GetPrivateProfileString(
                const char* lpAppName,        // section name
                const char* lpKeyName,        // key name
                const char* lpDefault,        // default string
                char *lpReturnedString,  // destination buffer
        DWORD nSize,              // size of destination buffer
                const char* lpFileName        // initialization file name
        );
};

#endif // PROFILE_H
