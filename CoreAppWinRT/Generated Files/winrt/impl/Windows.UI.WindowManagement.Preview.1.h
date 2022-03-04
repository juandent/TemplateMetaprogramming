// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_UI_WindowManagement_Preview_1_H
#define WINRT_Windows_UI_WindowManagement_Preview_1_H
#include "winrt/impl/Windows.UI.WindowManagement.Preview.0.h"
WINRT_EXPORT namespace winrt::Windows::UI::WindowManagement::Preview
{
    struct __declspec(empty_bases) IWindowManagementPreview :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWindowManagementPreview>
    {
        IWindowManagementPreview(std::nullptr_t = nullptr) noexcept {}
        IWindowManagementPreview(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWindowManagementPreview(IWindowManagementPreview const&) noexcept = default;
        IWindowManagementPreview(IWindowManagementPreview&&) noexcept = default;
        IWindowManagementPreview& operator=(IWindowManagementPreview const&) & noexcept = default;
        IWindowManagementPreview& operator=(IWindowManagementPreview&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWindowManagementPreviewStatics :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWindowManagementPreviewStatics>
    {
        IWindowManagementPreviewStatics(std::nullptr_t = nullptr) noexcept {}
        IWindowManagementPreviewStatics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWindowManagementPreviewStatics(IWindowManagementPreviewStatics const&) noexcept = default;
        IWindowManagementPreviewStatics(IWindowManagementPreviewStatics&&) noexcept = default;
        IWindowManagementPreviewStatics& operator=(IWindowManagementPreviewStatics const&) & noexcept = default;
        IWindowManagementPreviewStatics& operator=(IWindowManagementPreviewStatics&&) & noexcept = default;
    };
}
#endif
