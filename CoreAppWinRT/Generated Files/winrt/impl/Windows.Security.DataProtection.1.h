// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Security_DataProtection_1_H
#define WINRT_Windows_Security_DataProtection_1_H
#include "winrt/impl/Windows.Security.DataProtection.0.h"
WINRT_EXPORT namespace winrt::Windows::Security::DataProtection
{
    struct __declspec(empty_bases) IUserDataAvailabilityStateChangedEventArgs :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataAvailabilityStateChangedEventArgs>
    {
        IUserDataAvailabilityStateChangedEventArgs(std::nullptr_t = nullptr) noexcept {}
        IUserDataAvailabilityStateChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataAvailabilityStateChangedEventArgs(IUserDataAvailabilityStateChangedEventArgs const&) noexcept = default;
        IUserDataAvailabilityStateChangedEventArgs(IUserDataAvailabilityStateChangedEventArgs&&) noexcept = default;
        IUserDataAvailabilityStateChangedEventArgs& operator=(IUserDataAvailabilityStateChangedEventArgs const&) & noexcept = default;
        IUserDataAvailabilityStateChangedEventArgs& operator=(IUserDataAvailabilityStateChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IUserDataBufferUnprotectResult :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataBufferUnprotectResult>
    {
        IUserDataBufferUnprotectResult(std::nullptr_t = nullptr) noexcept {}
        IUserDataBufferUnprotectResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataBufferUnprotectResult(IUserDataBufferUnprotectResult const&) noexcept = default;
        IUserDataBufferUnprotectResult(IUserDataBufferUnprotectResult&&) noexcept = default;
        IUserDataBufferUnprotectResult& operator=(IUserDataBufferUnprotectResult const&) & noexcept = default;
        IUserDataBufferUnprotectResult& operator=(IUserDataBufferUnprotectResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IUserDataProtectionManager :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataProtectionManager>
    {
        IUserDataProtectionManager(std::nullptr_t = nullptr) noexcept {}
        IUserDataProtectionManager(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataProtectionManager(IUserDataProtectionManager const&) noexcept = default;
        IUserDataProtectionManager(IUserDataProtectionManager&&) noexcept = default;
        IUserDataProtectionManager& operator=(IUserDataProtectionManager const&) & noexcept = default;
        IUserDataProtectionManager& operator=(IUserDataProtectionManager&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IUserDataProtectionManagerStatics :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataProtectionManagerStatics>
    {
        IUserDataProtectionManagerStatics(std::nullptr_t = nullptr) noexcept {}
        IUserDataProtectionManagerStatics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataProtectionManagerStatics(IUserDataProtectionManagerStatics const&) noexcept = default;
        IUserDataProtectionManagerStatics(IUserDataProtectionManagerStatics&&) noexcept = default;
        IUserDataProtectionManagerStatics& operator=(IUserDataProtectionManagerStatics const&) & noexcept = default;
        IUserDataProtectionManagerStatics& operator=(IUserDataProtectionManagerStatics&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IUserDataStorageItemProtectionInfo :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataStorageItemProtectionInfo>
    {
        IUserDataStorageItemProtectionInfo(std::nullptr_t = nullptr) noexcept {}
        IUserDataStorageItemProtectionInfo(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataStorageItemProtectionInfo(IUserDataStorageItemProtectionInfo const&) noexcept = default;
        IUserDataStorageItemProtectionInfo(IUserDataStorageItemProtectionInfo&&) noexcept = default;
        IUserDataStorageItemProtectionInfo& operator=(IUserDataStorageItemProtectionInfo const&) & noexcept = default;
        IUserDataStorageItemProtectionInfo& operator=(IUserDataStorageItemProtectionInfo&&) & noexcept = default;
    };
}
#endif
