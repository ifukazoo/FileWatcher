#pragma once

namespace FileWatcher {

class FileWatcherAdapter
{
public:
    FileWatcherAdapter(HWND);
    void StartWatching(const std::string&, const std::vector<std::string>&);
    void StopWatching();
    void OnChanged(System::Object ^, System::IO::FileSystemEventArgs^);
private:
    HWND receiver_;
    std::vector<std::string> watchingFiles_;
    gcroot<System::IO::FileSystemWatcher^> gcWatcher_;
};

/// <summary>
/// <para>�}�l�[�W�f���Q�[�g�ɃC���X�^���X���\�b�h��ݒ肷��ۂ́C�C���X�^���X�I�u�W�F�N�g��n���K�v�����邪</para>
/// <para>�A���}�l�[�W�C���X�^���X�͓n���Ȃ��̂Ń��b�p�[�����K�v������</para>
/// </summary>
ref class FileSystemEventHandlerAdapter
{
public:
    FileSystemEventHandlerAdapter(FileWatcherAdapter*);
    void OnChanged(System::Object ^, System::IO::FileSystemEventArgs ^);
private:
    FileWatcherAdapter * adapter_;
};
}
