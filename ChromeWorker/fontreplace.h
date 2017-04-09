#ifndef FONTREPLACE_H
#define FONTREPLACE_H

#include <vector>
#include <string>

class FontReplace
{
    private:
        bool IsHookInstalled = false;
        bool IsFontsInstalled = false;
        bool IsFontsCollectedSystem = false;
        bool IsFontsCollectedAdditional = false;
        std::vector<std::wstring> fonts;
        std::vector<std::wstring> fonts_available;

    public:
        static FontReplace& GetInstance()
        {
            static FontReplace instance;
            return instance;
        }
    private:
        FontReplace(){}
        FontReplace(FontReplace const&);
        void operator=(FontReplace const&);
        void InstallFonts();
        void UninstallFonts();
        void CollectFonts();
    public:
        bool Initialize();
        bool Hook();
        bool Uninitialize();
        bool UnHook();

        void SetFonts(const std::string& fonts);

        void AddFontPresentInSystem(const std::wstring& font);
        bool IsFontIsPresentInSystem(const std::wstring& font);
        bool IsStandartFont(const std::wstring& font);
        bool NeedDisplayFont(const std::wstring& font);



};

#endif // FONTREPLACE_H
