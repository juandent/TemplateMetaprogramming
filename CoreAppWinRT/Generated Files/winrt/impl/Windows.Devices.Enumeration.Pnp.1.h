// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Devices_Enumeration_Pnp_1_H
#define WINRT_Windows_Devices_Enumeration_Pnp_1_H
#include "winrt/impl/Windows.Devices.Enumeration.Pnp.0.h"
WINRT_EXPORT namespace winrt::Windows::Devices::Enumeration::Pnp
{
    struct __declspec(empty_bases) IPnpObject :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IPnpObject>
    {
        IPnpObject(std::nullptr_t = nullptr) noexcept {}
        IPnpObject(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IPnpObject(IPnpObject const&) noexcept = default;
        IPnpObject(IPnpObject&&) noexcept = default;
        IPnpObject& operator=(IPnpObject const&) & noexcept = default;
        IPnpObject& operator=(IPnpObject&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IPnpObjectStatics :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IPnpObjectStatics>
    {
        IPnpObjectStatics(std::nullptr_t = nullptr) noexcept {}
        IPnpObjectStatics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IPnpObjectStatics(IPnpObjectStatics const&) noexcept = default;
        IPnpObjectStatics(IPnpObjectStatics&&) noexcept = default;
        IPnpObjectStatics& operator=(IPnpObjectStatics const&) & noexcept = default;
        IPnpObjectStatics& operator=(IPnpObjectStatics&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IPnpObjectUpdate :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IPnpObjectUpdate>
    {
        IPnpObjectUpdate(std::nullptr_t = nullptr) noexcept {}
        IPnpObjectUpdate(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IPnpObjectUpdate(IPnpObjectUpdate const&) noexcept = default;
        IPnpObjectUpdate(IPnpObjectUpdate&&) noexcept = default;
        IPnpObjectUpdate& operator=(IPnpObjectUpdate const&) & noexcept = default;
        IPnpObjectUpdate& operator=(IPnpObjectUpdate&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IPnpObjectWatcher :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IPnpObjectWatcher>
    {
        IPnpObjectWatcher(std::nullptr_t = nullptr) noexcept {}
        IPnpObjectWatcher(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IPnpObjectWatcher(IPnpObjectWatcher const&) noexcept = default;
        IPnpObjectWatcher(IPnpObjectWatcher&&) noexcept = default;
        IPnpObjectWatcher& operator=(IPnpObjectWatcher const&) & noexcept = default;
        IPnpObjectWatcher& operator=(IPnpObjectWatcher&&) & noexcept = default;
    };
}
#endif
