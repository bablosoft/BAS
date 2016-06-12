#ifndef SETTINGS_H
#define SETTINGS_H


class settings
{
    bool use_flash;
    int skip_frames;
    bool force_utf8;
public:
    settings();
    bool UseFlash();
    bool ForceUtf8();
    int SkipFrames();
};

#endif // SETTINGS_H
