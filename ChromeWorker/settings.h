#ifndef SETTINGS_H
#define SETTINGS_H


class settings
{
    bool use_flash;
    int skip_frames;
public:
    settings();
    bool UseFlash();
    int SkipFrames();
};

#endif // SETTINGS_H
