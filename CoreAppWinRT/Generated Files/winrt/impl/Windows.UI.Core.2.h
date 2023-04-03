// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_UI_Core_2_H
#define WINRT_Windows_UI_Core_2_H
#include "winrt/impl/Windows.Foundation.2.h"
#include "winrt/impl/Windows.UI.Core.1.h"
WINRT_EXPORT namespace winrt::Windows::UI::Core
{
    struct DispatchedHandler : Windows::Foundation::IUnknown
    {
        DispatchedHandler(std::nullptr_t = nullptr) noexcept {}
        DispatchedHandler(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        DispatchedHandler(DispatchedHandler const&) noexcept = default;
        DispatchedHandler(DispatchedHandler&&) noexcept = default;
        DispatchedHandler& operator=(DispatchedHandler const&) & noexcept = default;
        DispatchedHandler& operator=(DispatchedHandler&&) & noexcept = default;
        template <typename L> DispatchedHandler(L lambda);
        template <typename F> DispatchedHandler(F* function);
        template <typename O, typename M> DispatchedHandler(O* object, M method);
        template <typename O, typename M> DispatchedHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> DispatchedHandler(weak_ref<O>&& object, M method);
        auto operator()() const;
    };
    struct IdleDispatchedHandler : Windows::Foundation::IUnknown
    {
        IdleDispatchedHandler(std::nullptr_t = nullptr) noexcept {}
        IdleDispatchedHandler(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        IdleDispatchedHandler(IdleDispatchedHandler const&) noexcept = default;
        IdleDispatchedHandler(IdleDispatchedHandler&&) noexcept = default;
        IdleDispatchedHandler& operator=(IdleDispatchedHandler const&) & noexcept = default;
        IdleDispatchedHandler& operator=(IdleDispatchedHandler&&) & noexcept = default;
        template <typename L> IdleDispatchedHandler(L lambda);
        template <typename F> IdleDispatchedHandler(F* function);
        template <typename O, typename M> IdleDispatchedHandler(O* object, M method);
        template <typename O, typename M> IdleDispatchedHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> IdleDispatchedHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::UI::Core::IdleDispatchedHandlerArgs const& e) const;
    };
    struct CorePhysicalKeyStatus
    {
        uint32_t RepeatCount;
        uint32_t ScanCode;
        bool IsExtendedKey;
        bool IsMenuKeyDown;
        bool WasKeyDown;
        bool IsKeyReleased;
    };
    inline bool operator==(CorePhysicalKeyStatus const& left, CorePhysicalKeyStatus const& right) noexcept
    {
        return left.RepeatCount == right.RepeatCount && left.ScanCode == right.ScanCode && left.IsExtendedKey == right.IsExtendedKey && left.IsMenuKeyDown == right.IsMenuKeyDown && left.WasKeyDown == right.WasKeyDown && left.IsKeyReleased == right.IsKeyReleased;
    }
    inline bool operator!=(CorePhysicalKeyStatus const& left, CorePhysicalKeyStatus const& right) noexcept
    {
        return !(left == right);
    }
    struct CoreProximityEvaluation
    {
        int32_t Score;
        winrt::Windows::Foundation::Point AdjustedPoint;
    };
    inline bool operator==(CoreProximityEvaluation const& left, CoreProximityEvaluation const& right) noexcept
    {
        return left.Score == right.Score && left.AdjustedPoint == right.AdjustedPoint;
    }
    inline bool operator!=(CoreProximityEvaluation const& left, CoreProximityEvaluation const& right) noexcept
    {
        return !(left == right);
    }
    struct __declspec(empty_bases) AcceleratorKeyEventArgs : winrt::Windows::UI::Core::IAcceleratorKeyEventArgs,
        impl::require<AcceleratorKeyEventArgs, winrt::Windows::UI::Core::IAcceleratorKeyEventArgs2>
    {
        AcceleratorKeyEventArgs(std::nullptr_t) noexcept {}
        AcceleratorKeyEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IAcceleratorKeyEventArgs(ptr, take_ownership_from_abi) {}
        AcceleratorKeyEventArgs(AcceleratorKeyEventArgs const&) noexcept = default;
        AcceleratorKeyEventArgs(AcceleratorKeyEventArgs&&) noexcept = default;
        AcceleratorKeyEventArgs& operator=(AcceleratorKeyEventArgs const&) & noexcept = default;
        AcceleratorKeyEventArgs& operator=(AcceleratorKeyEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) AutomationProviderRequestedEventArgs : winrt::Windows::UI::Core::IAutomationProviderRequestedEventArgs
    {
        AutomationProviderRequestedEventArgs(std::nullptr_t) noexcept {}
        AutomationProviderRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IAutomationProviderRequestedEventArgs(ptr, take_ownership_from_abi) {}
        AutomationProviderRequestedEventArgs(AutomationProviderRequestedEventArgs const&) noexcept = default;
        AutomationProviderRequestedEventArgs(AutomationProviderRequestedEventArgs&&) noexcept = default;
        AutomationProviderRequestedEventArgs& operator=(AutomationProviderRequestedEventArgs const&) & noexcept = default;
        AutomationProviderRequestedEventArgs& operator=(AutomationProviderRequestedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) BackRequestedEventArgs : winrt::Windows::UI::Core::IBackRequestedEventArgs
    {
        BackRequestedEventArgs(std::nullptr_t) noexcept {}
        BackRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IBackRequestedEventArgs(ptr, take_ownership_from_abi) {}
        BackRequestedEventArgs(BackRequestedEventArgs const&) noexcept = default;
        BackRequestedEventArgs(BackRequestedEventArgs&&) noexcept = default;
        BackRequestedEventArgs& operator=(BackRequestedEventArgs const&) & noexcept = default;
        BackRequestedEventArgs& operator=(BackRequestedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CharacterReceivedEventArgs : winrt::Windows::UI::Core::ICharacterReceivedEventArgs
    {
        CharacterReceivedEventArgs(std::nullptr_t) noexcept {}
        CharacterReceivedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ICharacterReceivedEventArgs(ptr, take_ownership_from_abi) {}
        CharacterReceivedEventArgs(CharacterReceivedEventArgs const&) noexcept = default;
        CharacterReceivedEventArgs(CharacterReceivedEventArgs&&) noexcept = default;
        CharacterReceivedEventArgs& operator=(CharacterReceivedEventArgs const&) & noexcept = default;
        CharacterReceivedEventArgs& operator=(CharacterReceivedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ClosestInteractiveBoundsRequestedEventArgs : winrt::Windows::UI::Core::IClosestInteractiveBoundsRequestedEventArgs
    {
        ClosestInteractiveBoundsRequestedEventArgs(std::nullptr_t) noexcept {}
        ClosestInteractiveBoundsRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IClosestInteractiveBoundsRequestedEventArgs(ptr, take_ownership_from_abi) {}
        ClosestInteractiveBoundsRequestedEventArgs(ClosestInteractiveBoundsRequestedEventArgs const&) noexcept = default;
        ClosestInteractiveBoundsRequestedEventArgs(ClosestInteractiveBoundsRequestedEventArgs&&) noexcept = default;
        ClosestInteractiveBoundsRequestedEventArgs& operator=(ClosestInteractiveBoundsRequestedEventArgs const&) & noexcept = default;
        ClosestInteractiveBoundsRequestedEventArgs& operator=(ClosestInteractiveBoundsRequestedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CoreAcceleratorKeys : winrt::Windows::UI::Core::ICoreAcceleratorKeys
    {
        CoreAcceleratorKeys(std::nullptr_t) noexcept {}
        CoreAcceleratorKeys(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ICoreAcceleratorKeys(ptr, take_ownership_from_abi) {}
        CoreAcceleratorKeys(CoreAcceleratorKeys const&) noexcept = default;
        CoreAcceleratorKeys(CoreAcceleratorKeys&&) noexcept = default;
        CoreAcceleratorKeys& operator=(CoreAcceleratorKeys const&) & noexcept = default;
        CoreAcceleratorKeys& operator=(CoreAcceleratorKeys&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CoreComponentInputSource : winrt::Windows::UI::Core::ICoreInputSourceBase,
        impl::require<CoreComponentInputSource, winrt::Windows::UI::Core::ICorePointerInputSource, winrt::Windows::UI::Core::ICoreKeyboardInputSource, winrt::Windows::UI::Core::ICoreComponentFocusable, winrt::Windows::UI::Core::ICoreTouchHitTesting, winrt::Windows::UI::Core::ICoreClosestInteractiveBoundsRequested, winrt::Windows::UI::Core::ICoreKeyboardInputSource2, winrt::Windows::UI::Core::ICorePointerInputSource2>
    {
        CoreComponentInputSource(std::nullptr_t) noexcept {}
        CoreComponentInputSource(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ICoreInputSourceBase(ptr, take_ownership_from_abi) {}
        CoreComponentInputSource(CoreComponentInputSource const&) noexcept = default;
        CoreComponentInputSource(CoreComponentInputSource&&) noexcept = default;
        CoreComponentInputSource& operator=(CoreComponentInputSource const&) & noexcept = default;
        CoreComponentInputSource& operator=(CoreComponentInputSource&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CoreCursor : winrt::Windows::UI::Core::ICoreCursor
    {
        CoreCursor(std::nullptr_t) noexcept {}
        CoreCursor(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ICoreCursor(ptr, take_ownership_from_abi) {}
        CoreCursor(winrt::Windows::UI::Core::CoreCursorType const& type, uint32_t id);
        CoreCursor(CoreCursor const&) noexcept = default;
        CoreCursor(CoreCursor&&) noexcept = default;
        CoreCursor& operator=(CoreCursor const&) & noexcept = default;
        CoreCursor& operator=(CoreCursor&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CoreDispatcher : winrt::Windows::UI::Core::ICoreDispatcher,
        impl::require<CoreDispatcher, winrt::Windows::UI::Core::ICoreDispatcherWithTaskPriority, winrt::Windows::UI::Core::ICoreDispatcher2>
    {
        CoreDispatcher(std::nullptr_t) noexcept {}
        CoreDispatcher(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ICoreDispatcher(ptr, take_ownership_from_abi) {}
        CoreDispatcher(CoreDispatcher const&) noexcept = default;
        CoreDispatcher(CoreDispatcher&&) noexcept = default;
        CoreDispatcher& operator=(CoreDispatcher const&) & noexcept = default;
        CoreDispatcher& operator=(CoreDispatcher&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CoreIndependentInputSource : winrt::Windows::UI::Core::ICoreInputSourceBase,
        impl::require<CoreIndependentInputSource, winrt::Windows::UI::Core::ICorePointerInputSource, winrt::Windows::UI::Core::ICorePointerInputSource2>
    {
        CoreIndependentInputSource(std::nullptr_t) noexcept {}
        CoreIndependentInputSource(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ICoreInputSourceBase(ptr, take_ownership_from_abi) {}
        CoreIndependentInputSource(CoreIndependentInputSource const&) noexcept = default;
        CoreIndependentInputSource(CoreIndependentInputSource&&) noexcept = default;
        CoreIndependentInputSource& operator=(CoreIndependentInputSource const&) & noexcept = default;
        CoreIndependentInputSource& operator=(CoreIndependentInputSource&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CoreWindow : winrt::Windows::UI::Core::ICoreWindow,
        impl::require<CoreWindow, winrt::Windows::UI::Core::ICoreWindow2, winrt::Windows::UI::Core::ICorePointerRedirector, winrt::Windows::UI::Core::ICoreWindow3, winrt::Windows::UI::Core::ICoreWindow4, winrt::Windows::UI::Core::ICoreWindow5, winrt::Windows::UI::Core::ICoreWindowWithContext>
    {
        CoreWindow(std::nullptr_t) noexcept {}
        CoreWindow(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ICoreWindow(ptr, take_ownership_from_abi) {}
        CoreWindow(CoreWindow const&) noexcept = default;
        CoreWindow(CoreWindow&&) noexcept = default;
        CoreWindow& operator=(CoreWindow const&) & noexcept = default;
        CoreWindow& operator=(CoreWindow&&) & noexcept = default;
        using winrt::Windows::UI::Core::ICoreWindow::PointerPosition;
        using impl::consume_t<CoreWindow, winrt::Windows::UI::Core::ICoreWindow2>::PointerPosition;
        static auto GetForCurrentThread();
    };
    struct __declspec(empty_bases) CoreWindowEventArgs : winrt::Windows::UI::Core::ICoreWindowEventArgs
    {
        CoreWindowEventArgs(std::nullptr_t) noexcept {}
        CoreWindowEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ICoreWindowEventArgs(ptr, take_ownership_from_abi) {}
        CoreWindowEventArgs(CoreWindowEventArgs const&) noexcept = default;
        CoreWindowEventArgs(CoreWindowEventArgs&&) noexcept = default;
        CoreWindowEventArgs& operator=(CoreWindowEventArgs const&) & noexcept = default;
        CoreWindowEventArgs& operator=(CoreWindowEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CoreWindowResizeManager : winrt::Windows::UI::Core::ICoreWindowResizeManager,
        impl::require<CoreWindowResizeManager, winrt::Windows::UI::Core::ICoreWindowResizeManagerLayoutCapability>
    {
        CoreWindowResizeManager(std::nullptr_t) noexcept {}
        CoreWindowResizeManager(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ICoreWindowResizeManager(ptr, take_ownership_from_abi) {}
        CoreWindowResizeManager(CoreWindowResizeManager const&) noexcept = default;
        CoreWindowResizeManager(CoreWindowResizeManager&&) noexcept = default;
        CoreWindowResizeManager& operator=(CoreWindowResizeManager const&) & noexcept = default;
        CoreWindowResizeManager& operator=(CoreWindowResizeManager&&) & noexcept = default;
        static auto GetForCurrentView();
    };
    struct __declspec(empty_bases) IdleDispatchedHandlerArgs : winrt::Windows::UI::Core::IIdleDispatchedHandlerArgs
    {
        IdleDispatchedHandlerArgs(std::nullptr_t) noexcept {}
        IdleDispatchedHandlerArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IIdleDispatchedHandlerArgs(ptr, take_ownership_from_abi) {}
        IdleDispatchedHandlerArgs(IdleDispatchedHandlerArgs const&) noexcept = default;
        IdleDispatchedHandlerArgs(IdleDispatchedHandlerArgs&&) noexcept = default;
        IdleDispatchedHandlerArgs& operator=(IdleDispatchedHandlerArgs const&) & noexcept = default;
        IdleDispatchedHandlerArgs& operator=(IdleDispatchedHandlerArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) InputEnabledEventArgs : winrt::Windows::UI::Core::IInputEnabledEventArgs
    {
        InputEnabledEventArgs(std::nullptr_t) noexcept {}
        InputEnabledEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IInputEnabledEventArgs(ptr, take_ownership_from_abi) {}
        InputEnabledEventArgs(InputEnabledEventArgs const&) noexcept = default;
        InputEnabledEventArgs(InputEnabledEventArgs&&) noexcept = default;
        InputEnabledEventArgs& operator=(InputEnabledEventArgs const&) & noexcept = default;
        InputEnabledEventArgs& operator=(InputEnabledEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) KeyEventArgs : winrt::Windows::UI::Core::IKeyEventArgs,
        impl::require<KeyEventArgs, winrt::Windows::UI::Core::IKeyEventArgs2>
    {
        KeyEventArgs(std::nullptr_t) noexcept {}
        KeyEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IKeyEventArgs(ptr, take_ownership_from_abi) {}
        KeyEventArgs(KeyEventArgs const&) noexcept = default;
        KeyEventArgs(KeyEventArgs&&) noexcept = default;
        KeyEventArgs& operator=(KeyEventArgs const&) & noexcept = default;
        KeyEventArgs& operator=(KeyEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) PointerEventArgs : winrt::Windows::UI::Core::IPointerEventArgs
    {
        PointerEventArgs(std::nullptr_t) noexcept {}
        PointerEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IPointerEventArgs(ptr, take_ownership_from_abi) {}
        PointerEventArgs(PointerEventArgs const&) noexcept = default;
        PointerEventArgs(PointerEventArgs&&) noexcept = default;
        PointerEventArgs& operator=(PointerEventArgs const&) & noexcept = default;
        PointerEventArgs& operator=(PointerEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SystemNavigationManager : winrt::Windows::UI::Core::ISystemNavigationManager,
        impl::require<SystemNavigationManager, winrt::Windows::UI::Core::ISystemNavigationManager2>
    {
        SystemNavigationManager(std::nullptr_t) noexcept {}
        SystemNavigationManager(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ISystemNavigationManager(ptr, take_ownership_from_abi) {}
        SystemNavigationManager(SystemNavigationManager const&) noexcept = default;
        SystemNavigationManager(SystemNavigationManager&&) noexcept = default;
        SystemNavigationManager& operator=(SystemNavigationManager const&) & noexcept = default;
        SystemNavigationManager& operator=(SystemNavigationManager&&) & noexcept = default;
        static auto GetForCurrentView();
    };
    struct __declspec(empty_bases) TouchHitTestingEventArgs : winrt::Windows::UI::Core::ITouchHitTestingEventArgs
    {
        TouchHitTestingEventArgs(std::nullptr_t) noexcept {}
        TouchHitTestingEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::ITouchHitTestingEventArgs(ptr, take_ownership_from_abi) {}
        TouchHitTestingEventArgs(TouchHitTestingEventArgs const&) noexcept = default;
        TouchHitTestingEventArgs(TouchHitTestingEventArgs&&) noexcept = default;
        TouchHitTestingEventArgs& operator=(TouchHitTestingEventArgs const&) & noexcept = default;
        TouchHitTestingEventArgs& operator=(TouchHitTestingEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) VisibilityChangedEventArgs : winrt::Windows::UI::Core::IVisibilityChangedEventArgs
    {
        VisibilityChangedEventArgs(std::nullptr_t) noexcept {}
        VisibilityChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IVisibilityChangedEventArgs(ptr, take_ownership_from_abi) {}
        VisibilityChangedEventArgs(VisibilityChangedEventArgs const&) noexcept = default;
        VisibilityChangedEventArgs(VisibilityChangedEventArgs&&) noexcept = default;
        VisibilityChangedEventArgs& operator=(VisibilityChangedEventArgs const&) & noexcept = default;
        VisibilityChangedEventArgs& operator=(VisibilityChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) WindowActivatedEventArgs : winrt::Windows::UI::Core::IWindowActivatedEventArgs
    {
        WindowActivatedEventArgs(std::nullptr_t) noexcept {}
        WindowActivatedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IWindowActivatedEventArgs(ptr, take_ownership_from_abi) {}
        WindowActivatedEventArgs(WindowActivatedEventArgs const&) noexcept = default;
        WindowActivatedEventArgs(WindowActivatedEventArgs&&) noexcept = default;
        WindowActivatedEventArgs& operator=(WindowActivatedEventArgs const&) & noexcept = default;
        WindowActivatedEventArgs& operator=(WindowActivatedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) WindowSizeChangedEventArgs : winrt::Windows::UI::Core::IWindowSizeChangedEventArgs
    {
        WindowSizeChangedEventArgs(std::nullptr_t) noexcept {}
        WindowSizeChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Core::IWindowSizeChangedEventArgs(ptr, take_ownership_from_abi) {}
        WindowSizeChangedEventArgs(WindowSizeChangedEventArgs const&) noexcept = default;
        WindowSizeChangedEventArgs(WindowSizeChangedEventArgs&&) noexcept = default;
        WindowSizeChangedEventArgs& operator=(WindowSizeChangedEventArgs const&) & noexcept = default;
        WindowSizeChangedEventArgs& operator=(WindowSizeChangedEventArgs&&) & noexcept = default;
    };
}
#endif