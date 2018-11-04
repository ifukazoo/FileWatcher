#include "stdafx.h"
#include "FileWatcher.h"
#include "FileWatcherAdapter.h"

using namespace System;
using namespace System::IO;

namespace FileWatcher {

FileWatcherAdapter::FileWatcherAdapter(HWND receiver)
    : receiver_(receiver)
{
}
void FileWatcherAdapter::StartWatching(const std::string& dir, const std::vector<std::string>& files)
{
    std::copy(files.begin(), files.end(), std::back_inserter(watchingFiles_));

    gcWatcher_ = gcnew FileSystemWatcher();
    gcWatcher_->Path = gcnew String(dir.c_str());
    gcWatcher_->NotifyFilter = NotifyFilters::LastWrite | NotifyFilters::LastAccess | NotifyFilters::CreationTime | NotifyFilters::FileName;
    // ディレクトリ配下のファイルはすべて監視して自分でフィルターする
    gcWatcher_->Filter = "*";
    auto handler = gcnew FileSystemEventHandler(gcnew FileSystemEventHandlerAdapter(this), &FileSystemEventHandlerAdapter::OnChanged);
    gcWatcher_->Created += handler;
    gcWatcher_->Changed += handler;
    gcWatcher_->Deleted += handler;
    gcWatcher_->EnableRaisingEvents = true;
}
void FileWatcherAdapter::StopWatching()
{
    delete gcWatcher_;
    gcWatcher_ = nullptr;
    watchingFiles_.clear();
}
void FileWatcherAdapter::OnChanged(Object ^, FileSystemEventArgs ^args)
{
    try
    {
        // EnableRaisingEvents を このデリゲート内で false -> trueとしないと
        // ２回イベントが上がってしまう．
        gcWatcher_->EnableRaisingEvents = false;

        msclr::interop::marshal_context context;
        auto name = context.marshal_as<const char*>(args->Name);
        if (std::find(watchingFiles_.begin(), watchingFiles_.end(), name) != watchingFiles_.end())
        {
            auto path = context.marshal_as<const char*>(args->FullPath);
            auto changeType = static_cast<int>(args->ChangeType);

            // ローカル変数のポインタを送信するのでSendMessageする
            ::SendMessage(receiver_, WM_CHANGED, reinterpret_cast<WPARAM>(path), static_cast<LPARAM>(changeType));
        }
    }
    finally
    {
        gcWatcher_->EnableRaisingEvents = true;
    }
}
FileSystemEventHandlerAdapter::FileSystemEventHandlerAdapter(FileWatcherAdapter * adapter)
    :adapter_(adapter)
{
}
void FileSystemEventHandlerAdapter::OnChanged(Object ^ sender, FileSystemEventArgs ^ args)
{
    adapter_->OnChanged(sender, args);
}
}
