// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Foundation_Metadata_1_H
#define WINRT_Windows_Foundation_Metadata_1_H
#include "winrt/impl/Windows.Foundation.Metadata.0.h"
WINRT_EXPORT namespace winrt::Windows::Foundation::Metadata
{
    struct __declspec(empty_bases) IApiInformationStatics :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IApiInformationStatics>
    {
        IApiInformationStatics(std::nullptr_t = nullptr) noexcept {}
        IApiInformationStatics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IApiInformationStatics(IApiInformationStatics const&) noexcept = default;
        IApiInformationStatics(IApiInformationStatics&&) noexcept = default;
        IApiInformationStatics& operator=(IApiInformationStatics const&) & noexcept = default;
        IApiInformationStatics& operator=(IApiInformationStatics&&) & noexcept = default;
    };
}
#endif
