#include <Windows.h>
#include "fontreplace.h"
#include "MinHook.h"
#include "converter.h"
#include "log.h"
#include "split.h"
#include "trim.h"
#include "multithreading.h"


typedef HFONT (WINAPI *BAS_TYPE_CreateFontIndirectW)(CONST LOGFONTW *);

BAS_TYPE_CreateFontIndirectW BAS_POINTER_CreateFontIndirectW = NULL;


HFONT WINAPI BAS_REPLACED_CreateFontIndirectW(CONST LOGFONTW *lplf)
{
    //WORKER_LOG(std::string(" <- CreateFontIndirectW ") + ws2s(lplf->lfFaceName));

    std::wstring OriginalFont;
    std::wstring Font(lplf->lfFaceName);

    if(FontReplace::GetInstance().IsStandartFont(Font))
    {
        //font is standart
    }else
    {
        if(!FontReplace::GetInstance().NeedDisplayFont(Font))
        {
            //No need to display font, change to standart
            OriginalFont.assign(lplf->lfFaceName);
            OriginalFont.push_back(0);
            std::wstring ReplaceFont(L"Times New Roman\0");
            wcsncpy((wchar_t*)lplf->lfFaceName, ReplaceFont.data(), ReplaceFont.length() + 1);
        }else
        {
            //need to display font
            /*if(FontReplace::GetInstance().IsFontIsPresentInSystem(Font))
            {
                //if font already present in system
            }else
            {
                //if not present in system, but need to display
                OriginalFont.assign(lplf->lfFaceName);
                OriginalFont.push_back(0);
                std::wstring ReplaceFont(L"Comic Sans MS\0");
                wcsncpy((wchar_t*)lplf->lfFaceName, ReplaceFont.data(), ReplaceFont.length() + 1);
            }*/
        }
    }

    //WORKER_LOG(std::string(" -> CreateFontIndirectW ") + ws2s(lplf->lfFaceName));


    HFONT res = BAS_POINTER_CreateFontIndirectW(lplf);

    if(!OriginalFont.empty())
    {
        wcsncpy((wchar_t*)lplf->lfFaceName, OriginalFont.data(), OriginalFont.length());
    }

    return res;
}

static int CALLBACK EnumFontFamExProc(ENUMLOGFONTEXW* logical_font,
                                      NEWTEXTMETRICEXW* physical_font,
                                      DWORD font_type,
                                      LPARAM lparam)
{
    FontReplace* font_replace =  reinterpret_cast<FontReplace*>(lparam);
    if (font_replace)
    {
        const LOGFONTW& lf = logical_font->elfLogFont;
        if (lf.lfFaceName[0] && lf.lfFaceName[0] != '@')
        {
            std::wstring face_name(lf.lfFaceName);
            font_replace->AddFontPresentInSystem(face_name);
        }
    }
    return 1;
}

void FontReplace::CollectFonts()
{
    if(IsFontsCollectedSystem)
        return;

    LOGFONTW logfont;
    memset(&logfont, 0, sizeof(logfont));
    logfont.lfCharSet = DEFAULT_CHARSET;

    HDC hdc = ::GetDC(NULL);
    EnumFontFamiliesExW(hdc, &logfont, (FONTENUMPROCW)&EnumFontFamExProc,(LPARAM)this, 0);
    ReleaseDC(NULL, hdc);

    IsFontsCollectedSystem = true;
}

void FontReplace::AddFontPresentInSystem(const std::wstring& font)
{
    if(IsFontIsPresentInSystem(font))
        return;

    std::wstring font_copy = font;
    std::transform(font_copy.begin(), font_copy.end(), font_copy.begin(), ::tolower);
    WORKER_LOG(std::string("Available font ") + ws2s(font_copy));

    fonts_available.push_back(font_copy);
}

bool FontReplace::IsFontIsPresentInSystem(const std::wstring& font)
{
    std::wstring font_copy = font;
    std::transform(font_copy.begin(), font_copy.end(), font_copy.begin(), ::tolower);
    return std::find(fonts_available.begin(), fonts_available.end(), font_copy) != fonts_available.end();
}

bool FontReplace::IsStandartFont(const std::wstring& font)
{
    std::wstring font_copy = font;
    std::transform(font_copy.begin(), font_copy.end(), font_copy.begin(), ::tolower);

    return font_copy == std::wstring(L"arial")
             || font_copy == std::wstring(L"times new roman")
             || font_copy == std::wstring(L"courier new")
             || font_copy == std::wstring(L"lucida console")
             || font_copy == std::wstring(L"georgia")
             || font_copy == std::wstring(L"")
             || font_copy.find(L"==") != std::wstring::npos;

}

bool FontReplace::NeedDisplayFont(const std::wstring& font)
{
    std::wstring font_copy = font;
    std::transform(font_copy.begin(), font_copy.end(), font_copy.begin(), ::tolower);

    LOCK_FONTS
    return std::find(fonts.begin(), fonts.end(), font_copy) != fonts.end();
}


void FontReplace::InstallFonts()
{
    if(IsFontsInstalled)
        return;

    WORKER_LOG(std::string("FontReplace::InstallFonts"));

    WIN32_FIND_DATA search_data;

    memset(&search_data, 0, sizeof(WIN32_FIND_DATA));

    HANDLE handle = FindFirstFile(L"fonts\\*", &search_data);

    while(handle != INVALID_HANDLE_VALUE)
    {
        search_data.cFileName;
        if(std::wstring(search_data.cFileName) != L"." && std::wstring(search_data.cFileName) != L"..")
        {
            std::wstring font(search_data.cFileName);
            /*if(!IsFontsCollectedAdditional)
            {
                std::string font_copy = ws2s(font);
                std::transform(font_copy.begin(), font_copy.end(), font_copy.begin(), ::tolower);
                font_copy = split(font_copy,'.')[0];

                AddFontPresentInSystem(s2ws(font_copy));
            }*/
            font = std::wstring(L"fonts\\") + font;
            AddFontResourceEx(font.c_str(), FR_PRIVATE /*| FR_NOT_ENUM*/, 0);
            WORKER_LOG(std::string("Found font ") + ws2s(font));
        }

        if(FindNextFile(handle, &search_data) == FALSE)
            break;
    }

    FindClose(handle);
    IsFontsInstalled = true;
    IsFontsCollectedAdditional = true;

}

void FontReplace::UninstallFonts()
{
    if(!IsFontsInstalled)
        return;
    WORKER_LOG(std::string("FontReplace::UninstallFonts"));


    WIN32_FIND_DATA search_data;

    memset(&search_data, 0, sizeof(WIN32_FIND_DATA));

    HANDLE handle = FindFirstFile(L"fonts\\*", &search_data);

    while(handle != INVALID_HANDLE_VALUE)
    {
        search_data.cFileName;
        if(std::wstring(search_data.cFileName) != L"." && std::wstring(search_data.cFileName) != L"..")
        {
            std::wstring font(search_data.cFileName);
            font = std::wstring(L"fonts\\") + font;
            RemoveFontResourceEx(font.c_str(), FR_PRIVATE /*| FR_NOT_ENUM*/, 0);
            WORKER_LOG(std::string("Remove font ") + ws2s(font));
        }

        if(FindNextFile(handle, &search_data) == FALSE)
            break;
    }

    FindClose(handle);
    IsFontsInstalled = false;
}

bool FontReplace::Initialize()
{


    if (MH_Initialize() != MH_OK)
    {
        WORKER_LOG("FontReplace::Initialize Failed MH_Initialize");
        return false;
    }

    if (MH_CreateHook(&CreateFontIndirectW, &BAS_REPLACED_CreateFontIndirectW, reinterpret_cast<LPVOID*>(&BAS_POINTER_CreateFontIndirectW)) != MH_OK)
    {
        WORKER_LOG("FontReplace::Initialize Failed MH_CreateHook");
        return false;
    }


    WORKER_LOG("FontReplace::Initialize Success");
    IsHookInstalled = false;
    return true;
}

bool FontReplace::Hook()
{
    if(IsHookInstalled)
        return true;

    InstallFonts();

    CollectFonts();


    if (MH_EnableHook(&CreateFontIndirectW) != MH_OK)
    {
        WORKER_LOG("FontReplace::Hook failed MH_EnableHook");
        return false;
    }

    WORKER_LOG("FontReplace::Hook Success");
    IsHookInstalled = true;
    return true;
}
void FontReplace::SetFonts(const std::string& fonts)
{
    LOCK_FONTS
    this->fonts.clear();
    std::vector<std::string> all = split(fonts,';');
    for(std::string& font: all)
    {
        std::string tf = trim(font);
        std::transform(tf.begin(), tf.end(), tf.begin(), ::tolower);

        if(tf.size() > 0)
            this->fonts.push_back(s2ws(tf));
    }
}

bool FontReplace::UnHook()
{
    if(!IsHookInstalled)
        return true;

    {
        LOCK_FONTS
        fonts.clear();
    }

    UninstallFonts();

    if (MH_DisableHook(&CreateFontIndirectW) != MH_OK)
    {
       WORKER_LOG("FontReplace::UnHook Failed MH_DisableHook");
       return false;
    }

    WORKER_LOG("FontReplace::UnHook Success");
    IsHookInstalled = false;
    return true;
}


bool FontReplace::Uninitialize()
{
    UnHook();

    if (MH_Uninitialize() != MH_OK)
    {
       WORKER_LOG("FontReplace::Uninitialize Failed MH_Uninitialize");
       return false;
    }

    WORKER_LOG("FontReplace::Uninitialize Success");
    return true;
}
