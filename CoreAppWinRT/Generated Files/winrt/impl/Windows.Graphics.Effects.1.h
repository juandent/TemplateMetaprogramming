// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Graphics_Effects_1_H
#define WINRT_Windows_Graphics_Effects_1_H
#include "winrt/impl/Windows.Graphics.Effects.0.h"
WINRT_EXPORT namespace winrt::Windows::Graphics::Effects
{
    struct __declspec(empty_bases) IGraphicsEffect :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IGraphicsEffect>,
        impl::require<winrt::Windows::Graphics::Effects::IGraphicsEffect, winrt::Windows::Graphics::Effects::IGraphicsEffectSource>
    {
        IGraphicsEffect(std::nullptr_t = nullptr) noexcept {}
        IGraphicsEffect(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IGraphicsEffect(IGraphicsEffect const&) noexcept = default;
        IGraphicsEffect(IGraphicsEffect&&) noexcept = default;
        IGraphicsEffect& operator=(IGraphicsEffect const&) & noexcept = default;
        IGraphicsEffect& operator=(IGraphicsEffect&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IGraphicsEffectSource :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IGraphicsEffectSource>
    {
        IGraphicsEffectSource(std::nullptr_t = nullptr) noexcept {}
        IGraphicsEffectSource(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IGraphicsEffectSource(IGraphicsEffectSource const&) noexcept = default;
        IGraphicsEffectSource(IGraphicsEffectSource&&) noexcept = default;
        IGraphicsEffectSource& operator=(IGraphicsEffectSource const&) & noexcept = default;
        IGraphicsEffectSource& operator=(IGraphicsEffectSource&&) & noexcept = default;
    };
}
#endif
