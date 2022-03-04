// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Security_ExchangeActiveSyncProvisioning_1_H
#define WINRT_Windows_Security_ExchangeActiveSyncProvisioning_1_H
#include "winrt/impl/Windows.Security.ExchangeActiveSyncProvisioning.0.h"
WINRT_EXPORT namespace winrt::Windows::Security::ExchangeActiveSyncProvisioning
{
    struct __declspec(empty_bases) IEasClientDeviceInformation :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IEasClientDeviceInformation>
    {
        IEasClientDeviceInformation(std::nullptr_t = nullptr) noexcept {}
        IEasClientDeviceInformation(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IEasClientDeviceInformation(IEasClientDeviceInformation const&) noexcept = default;
        IEasClientDeviceInformation(IEasClientDeviceInformation&&) noexcept = default;
        IEasClientDeviceInformation& operator=(IEasClientDeviceInformation const&) & noexcept = default;
        IEasClientDeviceInformation& operator=(IEasClientDeviceInformation&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IEasClientDeviceInformation2 :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IEasClientDeviceInformation2>,
        impl::require<winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasClientDeviceInformation2, winrt::Windows::Security::ExchangeActiveSyncProvisioning::IEasClientDeviceInformation>
    {
        IEasClientDeviceInformation2(std::nullptr_t = nullptr) noexcept {}
        IEasClientDeviceInformation2(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IEasClientDeviceInformation2(IEasClientDeviceInformation2 const&) noexcept = default;
        IEasClientDeviceInformation2(IEasClientDeviceInformation2&&) noexcept = default;
        IEasClientDeviceInformation2& operator=(IEasClientDeviceInformation2 const&) & noexcept = default;
        IEasClientDeviceInformation2& operator=(IEasClientDeviceInformation2&&) & noexcept = default;
    };
}
#endif
