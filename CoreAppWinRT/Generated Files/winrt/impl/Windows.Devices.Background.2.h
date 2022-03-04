// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Devices_Background_2_H
#define WINRT_Windows_Devices_Background_2_H
#include "winrt/impl/Windows.Devices.Background.1.h"
WINRT_EXPORT namespace winrt::Windows::Devices::Background
{
    struct __declspec(empty_bases) DeviceServicingDetails : winrt::Windows::Devices::Background::IDeviceServicingDetails
    {
        DeviceServicingDetails(std::nullptr_t) noexcept {}
        DeviceServicingDetails(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::Background::IDeviceServicingDetails(ptr, take_ownership_from_abi) {}
        DeviceServicingDetails(DeviceServicingDetails const&) noexcept = default;
        DeviceServicingDetails(DeviceServicingDetails&&) noexcept = default;
        DeviceServicingDetails& operator=(DeviceServicingDetails const&) & noexcept = default;
        DeviceServicingDetails& operator=(DeviceServicingDetails&&) & noexcept = default;
    };
    struct __declspec(empty_bases) DeviceUseDetails : winrt::Windows::Devices::Background::IDeviceUseDetails
    {
        DeviceUseDetails(std::nullptr_t) noexcept {}
        DeviceUseDetails(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::Background::IDeviceUseDetails(ptr, take_ownership_from_abi) {}
        DeviceUseDetails(DeviceUseDetails const&) noexcept = default;
        DeviceUseDetails(DeviceUseDetails&&) noexcept = default;
        DeviceUseDetails& operator=(DeviceUseDetails const&) & noexcept = default;
        DeviceUseDetails& operator=(DeviceUseDetails&&) & noexcept = default;
    };
}
#endif
