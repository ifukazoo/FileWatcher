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
/// <para>マネージデリゲートにインスタンスメソッドを設定する際は，インスタンスオブジェクトを渡す必要があるが</para>
/// <para>アンマネージインスタンスは渡せないのでラッパーを作る必要がある</para>
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
