// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Media_Capture_2_H
#define WINRT_Windows_Media_Capture_2_H
#include "winrt/impl/Windows.Foundation.1.h"
#include "winrt/impl/Windows.Storage.Streams.1.h"
#include "winrt/impl/Windows.Media.Capture.1.h"
WINRT_EXPORT namespace winrt::Windows::Media::Capture
{
    struct MediaCaptureFailedEventHandler : Windows::Foundation::IUnknown
    {
        MediaCaptureFailedEventHandler(std::nullptr_t = nullptr) noexcept {}
        MediaCaptureFailedEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        MediaCaptureFailedEventHandler(MediaCaptureFailedEventHandler const&) noexcept = default;
        MediaCaptureFailedEventHandler(MediaCaptureFailedEventHandler&&) noexcept = default;
        MediaCaptureFailedEventHandler& operator=(MediaCaptureFailedEventHandler const&) & noexcept = default;
        MediaCaptureFailedEventHandler& operator=(MediaCaptureFailedEventHandler&&) & noexcept = default;
        template <typename L> MediaCaptureFailedEventHandler(L lambda);
        template <typename F> MediaCaptureFailedEventHandler(F* function);
        template <typename O, typename M> MediaCaptureFailedEventHandler(O* object, M method);
        template <typename O, typename M> MediaCaptureFailedEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> MediaCaptureFailedEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Media::Capture::MediaCapture const& sender, winrt::Windows::Media::Capture::MediaCaptureFailedEventArgs const& errorEventArgs) const;
    };
    struct RecordLimitationExceededEventHandler : Windows::Foundation::IUnknown
    {
        RecordLimitationExceededEventHandler(std::nullptr_t = nullptr) noexcept {}
        RecordLimitationExceededEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        RecordLimitationExceededEventHandler(RecordLimitationExceededEventHandler const&) noexcept = default;
        RecordLimitationExceededEventHandler(RecordLimitationExceededEventHandler&&) noexcept = default;
        RecordLimitationExceededEventHandler& operator=(RecordLimitationExceededEventHandler const&) & noexcept = default;
        RecordLimitationExceededEventHandler& operator=(RecordLimitationExceededEventHandler&&) & noexcept = default;
        template <typename L> RecordLimitationExceededEventHandler(L lambda);
        template <typename F> RecordLimitationExceededEventHandler(F* function);
        template <typename O, typename M> RecordLimitationExceededEventHandler(O* object, M method);
        template <typename O, typename M> RecordLimitationExceededEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> RecordLimitationExceededEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Media::Capture::MediaCapture const& sender) const;
    };
    struct WhiteBalanceGain
    {
        double R;
        double G;
        double B;
    };
    inline bool operator==(WhiteBalanceGain const& left, WhiteBalanceGain const& right) noexcept
    {
        return left.R == right.R && left.G == right.G && left.B == right.B;
    }
    inline bool operator!=(WhiteBalanceGain const& left, WhiteBalanceGain const& right) noexcept
    {
        return !(left == right);
    }
    struct __declspec(empty_bases) AdvancedCapturedPhoto : winrt::Windows::Media::Capture::IAdvancedCapturedPhoto,
        impl::require<AdvancedCapturedPhoto, winrt::Windows::Media::Capture::IAdvancedCapturedPhoto2>
    {
        AdvancedCapturedPhoto(std::nullptr_t) noexcept {}
        AdvancedCapturedPhoto(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IAdvancedCapturedPhoto(ptr, take_ownership_from_abi) {}
        AdvancedCapturedPhoto(AdvancedCapturedPhoto const&) noexcept = default;
        AdvancedCapturedPhoto(AdvancedCapturedPhoto&&) noexcept = default;
        AdvancedCapturedPhoto& operator=(AdvancedCapturedPhoto const&) & noexcept = default;
        AdvancedCapturedPhoto& operator=(AdvancedCapturedPhoto&&) & noexcept = default;
    };
    struct __declspec(empty_bases) AdvancedPhotoCapture : winrt::Windows::Media::Capture::IAdvancedPhotoCapture
    {
        AdvancedPhotoCapture(std::nullptr_t) noexcept {}
        AdvancedPhotoCapture(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IAdvancedPhotoCapture(ptr, take_ownership_from_abi) {}
        AdvancedPhotoCapture(AdvancedPhotoCapture const&) noexcept = default;
        AdvancedPhotoCapture(AdvancedPhotoCapture&&) noexcept = default;
        AdvancedPhotoCapture& operator=(AdvancedPhotoCapture const&) & noexcept = default;
        AdvancedPhotoCapture& operator=(AdvancedPhotoCapture&&) & noexcept = default;
    };
    struct __declspec(empty_bases) AppCapture : winrt::Windows::Media::Capture::IAppCapture
    {
        AppCapture(std::nullptr_t) noexcept {}
        AppCapture(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IAppCapture(ptr, take_ownership_from_abi) {}
        AppCapture(AppCapture const&) noexcept = default;
        AppCapture(AppCapture&&) noexcept = default;
        AppCapture& operator=(AppCapture const&) & noexcept = default;
        AppCapture& operator=(AppCapture&&) & noexcept = default;
        static auto GetForCurrentView();
        static auto SetAllowedAsync(bool allowed);
    };
    struct __declspec(empty_bases) CameraCaptureUI : winrt::Windows::Media::Capture::ICameraCaptureUI
    {
        CameraCaptureUI(std::nullptr_t) noexcept {}
        CameraCaptureUI(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::ICameraCaptureUI(ptr, take_ownership_from_abi) {}
        CameraCaptureUI();
        CameraCaptureUI(CameraCaptureUI const&) noexcept = default;
        CameraCaptureUI(CameraCaptureUI&&) noexcept = default;
        CameraCaptureUI& operator=(CameraCaptureUI const&) & noexcept = default;
        CameraCaptureUI& operator=(CameraCaptureUI&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CameraCaptureUIPhotoCaptureSettings : winrt::Windows::Media::Capture::ICameraCaptureUIPhotoCaptureSettings
    {
        CameraCaptureUIPhotoCaptureSettings(std::nullptr_t) noexcept {}
        CameraCaptureUIPhotoCaptureSettings(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::ICameraCaptureUIPhotoCaptureSettings(ptr, take_ownership_from_abi) {}
        CameraCaptureUIPhotoCaptureSettings(CameraCaptureUIPhotoCaptureSettings const&) noexcept = default;
        CameraCaptureUIPhotoCaptureSettings(CameraCaptureUIPhotoCaptureSettings&&) noexcept = default;
        CameraCaptureUIPhotoCaptureSettings& operator=(CameraCaptureUIPhotoCaptureSettings const&) & noexcept = default;
        CameraCaptureUIPhotoCaptureSettings& operator=(CameraCaptureUIPhotoCaptureSettings&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CameraCaptureUIVideoCaptureSettings : winrt::Windows::Media::Capture::ICameraCaptureUIVideoCaptureSettings
    {
        CameraCaptureUIVideoCaptureSettings(std::nullptr_t) noexcept {}
        CameraCaptureUIVideoCaptureSettings(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::ICameraCaptureUIVideoCaptureSettings(ptr, take_ownership_from_abi) {}
        CameraCaptureUIVideoCaptureSettings(CameraCaptureUIVideoCaptureSettings const&) noexcept = default;
        CameraCaptureUIVideoCaptureSettings(CameraCaptureUIVideoCaptureSettings&&) noexcept = default;
        CameraCaptureUIVideoCaptureSettings& operator=(CameraCaptureUIVideoCaptureSettings const&) & noexcept = default;
        CameraCaptureUIVideoCaptureSettings& operator=(CameraCaptureUIVideoCaptureSettings&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CapturedFrame : winrt::Windows::Media::Capture::ICapturedFrame,
        impl::require<CapturedFrame, winrt::Windows::Media::Capture::ICapturedFrameWithSoftwareBitmap, winrt::Windows::Media::Capture::ICapturedFrame2>
    {
        CapturedFrame(std::nullptr_t) noexcept {}
        CapturedFrame(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::ICapturedFrame(ptr, take_ownership_from_abi) {}
        CapturedFrame(CapturedFrame const&) noexcept = default;
        CapturedFrame(CapturedFrame&&) noexcept = default;
        CapturedFrame& operator=(CapturedFrame const&) & noexcept = default;
        CapturedFrame& operator=(CapturedFrame&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CapturedFrameControlValues : winrt::Windows::Media::Capture::ICapturedFrameControlValues,
        impl::require<CapturedFrameControlValues, winrt::Windows::Media::Capture::ICapturedFrameControlValues2>
    {
        CapturedFrameControlValues(std::nullptr_t) noexcept {}
        CapturedFrameControlValues(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::ICapturedFrameControlValues(ptr, take_ownership_from_abi) {}
        CapturedFrameControlValues(CapturedFrameControlValues const&) noexcept = default;
        CapturedFrameControlValues(CapturedFrameControlValues&&) noexcept = default;
        CapturedFrameControlValues& operator=(CapturedFrameControlValues const&) & noexcept = default;
        CapturedFrameControlValues& operator=(CapturedFrameControlValues&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CapturedPhoto : winrt::Windows::Media::Capture::ICapturedPhoto
    {
        CapturedPhoto(std::nullptr_t) noexcept {}
        CapturedPhoto(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::ICapturedPhoto(ptr, take_ownership_from_abi) {}
        CapturedPhoto(CapturedPhoto const&) noexcept = default;
        CapturedPhoto(CapturedPhoto&&) noexcept = default;
        CapturedPhoto& operator=(CapturedPhoto const&) & noexcept = default;
        CapturedPhoto& operator=(CapturedPhoto&&) & noexcept = default;
    };
    struct __declspec(empty_bases) LowLagMediaRecording : winrt::Windows::Media::Capture::ILowLagMediaRecording,
        impl::require<LowLagMediaRecording, winrt::Windows::Media::Capture::ILowLagMediaRecording2, winrt::Windows::Media::Capture::ILowLagMediaRecording3>
    {
        LowLagMediaRecording(std::nullptr_t) noexcept {}
        LowLagMediaRecording(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::ILowLagMediaRecording(ptr, take_ownership_from_abi) {}
        LowLagMediaRecording(LowLagMediaRecording const&) noexcept = default;
        LowLagMediaRecording(LowLagMediaRecording&&) noexcept = default;
        LowLagMediaRecording& operator=(LowLagMediaRecording const&) & noexcept = default;
        LowLagMediaRecording& operator=(LowLagMediaRecording&&) & noexcept = default;
    };
    struct __declspec(empty_bases) LowLagPhotoCapture : winrt::Windows::Media::Capture::ILowLagPhotoCapture
    {
        LowLagPhotoCapture(std::nullptr_t) noexcept {}
        LowLagPhotoCapture(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::ILowLagPhotoCapture(ptr, take_ownership_from_abi) {}
        LowLagPhotoCapture(LowLagPhotoCapture const&) noexcept = default;
        LowLagPhotoCapture(LowLagPhotoCapture&&) noexcept = default;
        LowLagPhotoCapture& operator=(LowLagPhotoCapture const&) & noexcept = default;
        LowLagPhotoCapture& operator=(LowLagPhotoCapture&&) & noexcept = default;
    };
    struct __declspec(empty_bases) LowLagPhotoSequenceCapture : winrt::Windows::Media::Capture::ILowLagPhotoSequenceCapture
    {
        LowLagPhotoSequenceCapture(std::nullptr_t) noexcept {}
        LowLagPhotoSequenceCapture(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::ILowLagPhotoSequenceCapture(ptr, take_ownership_from_abi) {}
        LowLagPhotoSequenceCapture(LowLagPhotoSequenceCapture const&) noexcept = default;
        LowLagPhotoSequenceCapture(LowLagPhotoSequenceCapture&&) noexcept = default;
        LowLagPhotoSequenceCapture& operator=(LowLagPhotoSequenceCapture const&) & noexcept = default;
        LowLagPhotoSequenceCapture& operator=(LowLagPhotoSequenceCapture&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCapture : winrt::Windows::Media::Capture::IMediaCapture,
        impl::require<MediaCapture, winrt::Windows::Media::Capture::IMediaCaptureVideoPreview, winrt::Windows::Media::Capture::IMediaCapture2, winrt::Windows::Foundation::IClosable, winrt::Windows::Media::Capture::IMediaCapture3, winrt::Windows::Media::Capture::IMediaCapture4, winrt::Windows::Media::Capture::IMediaCapture5, winrt::Windows::Media::Capture::IMediaCapture6, winrt::Windows::Media::Capture::IMediaCapture7>
    {
        MediaCapture(std::nullptr_t) noexcept {}
        MediaCapture(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCapture(ptr, take_ownership_from_abi) {}
        MediaCapture();
        MediaCapture(MediaCapture const&) noexcept = default;
        MediaCapture(MediaCapture&&) noexcept = default;
        MediaCapture& operator=(MediaCapture const&) & noexcept = default;
        MediaCapture& operator=(MediaCapture&&) & noexcept = default;
        static auto IsVideoProfileSupported(param::hstring const& videoDeviceId);
        static auto FindAllVideoProfiles(param::hstring const& videoDeviceId);
        static auto FindConcurrentProfiles(param::hstring const& videoDeviceId);
        static auto FindKnownVideoProfiles(param::hstring const& videoDeviceId, winrt::Windows::Media::Capture::KnownVideoProfile const& name);
    };
    struct __declspec(empty_bases) MediaCaptureDeviceExclusiveControlStatusChangedEventArgs : winrt::Windows::Media::Capture::IMediaCaptureDeviceExclusiveControlStatusChangedEventArgs
    {
        MediaCaptureDeviceExclusiveControlStatusChangedEventArgs(std::nullptr_t) noexcept {}
        MediaCaptureDeviceExclusiveControlStatusChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCaptureDeviceExclusiveControlStatusChangedEventArgs(ptr, take_ownership_from_abi) {}
        MediaCaptureDeviceExclusiveControlStatusChangedEventArgs(MediaCaptureDeviceExclusiveControlStatusChangedEventArgs const&) noexcept = default;
        MediaCaptureDeviceExclusiveControlStatusChangedEventArgs(MediaCaptureDeviceExclusiveControlStatusChangedEventArgs&&) noexcept = default;
        MediaCaptureDeviceExclusiveControlStatusChangedEventArgs& operator=(MediaCaptureDeviceExclusiveControlStatusChangedEventArgs const&) & noexcept = default;
        MediaCaptureDeviceExclusiveControlStatusChangedEventArgs& operator=(MediaCaptureDeviceExclusiveControlStatusChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCaptureFailedEventArgs : winrt::Windows::Media::Capture::IMediaCaptureFailedEventArgs
    {
        MediaCaptureFailedEventArgs(std::nullptr_t) noexcept {}
        MediaCaptureFailedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCaptureFailedEventArgs(ptr, take_ownership_from_abi) {}
        MediaCaptureFailedEventArgs(MediaCaptureFailedEventArgs const&) noexcept = default;
        MediaCaptureFailedEventArgs(MediaCaptureFailedEventArgs&&) noexcept = default;
        MediaCaptureFailedEventArgs& operator=(MediaCaptureFailedEventArgs const&) & noexcept = default;
        MediaCaptureFailedEventArgs& operator=(MediaCaptureFailedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCaptureFocusChangedEventArgs : winrt::Windows::Media::Capture::IMediaCaptureFocusChangedEventArgs
    {
        MediaCaptureFocusChangedEventArgs(std::nullptr_t) noexcept {}
        MediaCaptureFocusChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCaptureFocusChangedEventArgs(ptr, take_ownership_from_abi) {}
        MediaCaptureFocusChangedEventArgs(MediaCaptureFocusChangedEventArgs const&) noexcept = default;
        MediaCaptureFocusChangedEventArgs(MediaCaptureFocusChangedEventArgs&&) noexcept = default;
        MediaCaptureFocusChangedEventArgs& operator=(MediaCaptureFocusChangedEventArgs const&) & noexcept = default;
        MediaCaptureFocusChangedEventArgs& operator=(MediaCaptureFocusChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCaptureInitializationSettings : winrt::Windows::Media::Capture::IMediaCaptureInitializationSettings,
        impl::require<MediaCaptureInitializationSettings, winrt::Windows::Media::Capture::IMediaCaptureInitializationSettings2, winrt::Windows::Media::Capture::IMediaCaptureInitializationSettings3, winrt::Windows::Media::Capture::IMediaCaptureInitializationSettings4, winrt::Windows::Media::Capture::IMediaCaptureInitializationSettings5, winrt::Windows::Media::Capture::IMediaCaptureInitializationSettings6, winrt::Windows::Media::Capture::IMediaCaptureInitializationSettings7>
    {
        MediaCaptureInitializationSettings(std::nullptr_t) noexcept {}
        MediaCaptureInitializationSettings(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCaptureInitializationSettings(ptr, take_ownership_from_abi) {}
        MediaCaptureInitializationSettings();
        MediaCaptureInitializationSettings(MediaCaptureInitializationSettings const&) noexcept = default;
        MediaCaptureInitializationSettings(MediaCaptureInitializationSettings&&) noexcept = default;
        MediaCaptureInitializationSettings& operator=(MediaCaptureInitializationSettings const&) & noexcept = default;
        MediaCaptureInitializationSettings& operator=(MediaCaptureInitializationSettings&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCapturePauseResult : winrt::Windows::Media::Capture::IMediaCapturePauseResult,
        impl::require<MediaCapturePauseResult, winrt::Windows::Foundation::IClosable>
    {
        MediaCapturePauseResult(std::nullptr_t) noexcept {}
        MediaCapturePauseResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCapturePauseResult(ptr, take_ownership_from_abi) {}
        MediaCapturePauseResult(MediaCapturePauseResult const&) noexcept = default;
        MediaCapturePauseResult(MediaCapturePauseResult&&) noexcept = default;
        MediaCapturePauseResult& operator=(MediaCapturePauseResult const&) & noexcept = default;
        MediaCapturePauseResult& operator=(MediaCapturePauseResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCaptureRelativePanelWatcher : winrt::Windows::Media::Capture::IMediaCaptureRelativePanelWatcher,
        impl::require<MediaCaptureRelativePanelWatcher, winrt::Windows::Foundation::IClosable>
    {
        MediaCaptureRelativePanelWatcher(std::nullptr_t) noexcept {}
        MediaCaptureRelativePanelWatcher(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCaptureRelativePanelWatcher(ptr, take_ownership_from_abi) {}
        MediaCaptureRelativePanelWatcher(MediaCaptureRelativePanelWatcher const&) noexcept = default;
        MediaCaptureRelativePanelWatcher(MediaCaptureRelativePanelWatcher&&) noexcept = default;
        MediaCaptureRelativePanelWatcher& operator=(MediaCaptureRelativePanelWatcher const&) & noexcept = default;
        MediaCaptureRelativePanelWatcher& operator=(MediaCaptureRelativePanelWatcher&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCaptureSettings : winrt::Windows::Media::Capture::IMediaCaptureSettings,
        impl::require<MediaCaptureSettings, winrt::Windows::Media::Capture::IMediaCaptureSettings2, winrt::Windows::Media::Capture::IMediaCaptureSettings3>
    {
        MediaCaptureSettings(std::nullptr_t) noexcept {}
        MediaCaptureSettings(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCaptureSettings(ptr, take_ownership_from_abi) {}
        MediaCaptureSettings(MediaCaptureSettings const&) noexcept = default;
        MediaCaptureSettings(MediaCaptureSettings&&) noexcept = default;
        MediaCaptureSettings& operator=(MediaCaptureSettings const&) & noexcept = default;
        MediaCaptureSettings& operator=(MediaCaptureSettings&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCaptureStopResult : winrt::Windows::Media::Capture::IMediaCaptureStopResult,
        impl::require<MediaCaptureStopResult, winrt::Windows::Foundation::IClosable>
    {
        MediaCaptureStopResult(std::nullptr_t) noexcept {}
        MediaCaptureStopResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCaptureStopResult(ptr, take_ownership_from_abi) {}
        MediaCaptureStopResult(MediaCaptureStopResult const&) noexcept = default;
        MediaCaptureStopResult(MediaCaptureStopResult&&) noexcept = default;
        MediaCaptureStopResult& operator=(MediaCaptureStopResult const&) & noexcept = default;
        MediaCaptureStopResult& operator=(MediaCaptureStopResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCaptureVideoProfile : winrt::Windows::Media::Capture::IMediaCaptureVideoProfile,
        impl::require<MediaCaptureVideoProfile, winrt::Windows::Media::Capture::IMediaCaptureVideoProfile2>
    {
        MediaCaptureVideoProfile(std::nullptr_t) noexcept {}
        MediaCaptureVideoProfile(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCaptureVideoProfile(ptr, take_ownership_from_abi) {}
        MediaCaptureVideoProfile(MediaCaptureVideoProfile const&) noexcept = default;
        MediaCaptureVideoProfile(MediaCaptureVideoProfile&&) noexcept = default;
        MediaCaptureVideoProfile& operator=(MediaCaptureVideoProfile const&) & noexcept = default;
        MediaCaptureVideoProfile& operator=(MediaCaptureVideoProfile&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaCaptureVideoProfileMediaDescription : winrt::Windows::Media::Capture::IMediaCaptureVideoProfileMediaDescription,
        impl::require<MediaCaptureVideoProfileMediaDescription, winrt::Windows::Media::Capture::IMediaCaptureVideoProfileMediaDescription2>
    {
        MediaCaptureVideoProfileMediaDescription(std::nullptr_t) noexcept {}
        MediaCaptureVideoProfileMediaDescription(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IMediaCaptureVideoProfileMediaDescription(ptr, take_ownership_from_abi) {}
        MediaCaptureVideoProfileMediaDescription(MediaCaptureVideoProfileMediaDescription const&) noexcept = default;
        MediaCaptureVideoProfileMediaDescription(MediaCaptureVideoProfileMediaDescription&&) noexcept = default;
        MediaCaptureVideoProfileMediaDescription& operator=(MediaCaptureVideoProfileMediaDescription const&) & noexcept = default;
        MediaCaptureVideoProfileMediaDescription& operator=(MediaCaptureVideoProfileMediaDescription&&) & noexcept = default;
    };
    struct __declspec(empty_bases) OptionalReferencePhotoCapturedEventArgs : winrt::Windows::Media::Capture::IOptionalReferencePhotoCapturedEventArgs
    {
        OptionalReferencePhotoCapturedEventArgs(std::nullptr_t) noexcept {}
        OptionalReferencePhotoCapturedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IOptionalReferencePhotoCapturedEventArgs(ptr, take_ownership_from_abi) {}
        OptionalReferencePhotoCapturedEventArgs(OptionalReferencePhotoCapturedEventArgs const&) noexcept = default;
        OptionalReferencePhotoCapturedEventArgs(OptionalReferencePhotoCapturedEventArgs&&) noexcept = default;
        OptionalReferencePhotoCapturedEventArgs& operator=(OptionalReferencePhotoCapturedEventArgs const&) & noexcept = default;
        OptionalReferencePhotoCapturedEventArgs& operator=(OptionalReferencePhotoCapturedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) PhotoCapturedEventArgs : winrt::Windows::Media::Capture::IPhotoCapturedEventArgs
    {
        PhotoCapturedEventArgs(std::nullptr_t) noexcept {}
        PhotoCapturedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IPhotoCapturedEventArgs(ptr, take_ownership_from_abi) {}
        PhotoCapturedEventArgs(PhotoCapturedEventArgs const&) noexcept = default;
        PhotoCapturedEventArgs(PhotoCapturedEventArgs&&) noexcept = default;
        PhotoCapturedEventArgs& operator=(PhotoCapturedEventArgs const&) & noexcept = default;
        PhotoCapturedEventArgs& operator=(PhotoCapturedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) PhotoConfirmationCapturedEventArgs : winrt::Windows::Media::Capture::IPhotoConfirmationCapturedEventArgs
    {
        PhotoConfirmationCapturedEventArgs(std::nullptr_t) noexcept {}
        PhotoConfirmationCapturedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IPhotoConfirmationCapturedEventArgs(ptr, take_ownership_from_abi) {}
        PhotoConfirmationCapturedEventArgs(PhotoConfirmationCapturedEventArgs const&) noexcept = default;
        PhotoConfirmationCapturedEventArgs(PhotoConfirmationCapturedEventArgs&&) noexcept = default;
        PhotoConfirmationCapturedEventArgs& operator=(PhotoConfirmationCapturedEventArgs const&) & noexcept = default;
        PhotoConfirmationCapturedEventArgs& operator=(PhotoConfirmationCapturedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) VideoStreamConfiguration : winrt::Windows::Media::Capture::IVideoStreamConfiguration
    {
        VideoStreamConfiguration(std::nullptr_t) noexcept {}
        VideoStreamConfiguration(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Capture::IVideoStreamConfiguration(ptr, take_ownership_from_abi) {}
        VideoStreamConfiguration(VideoStreamConfiguration const&) noexcept = default;
        VideoStreamConfiguration(VideoStreamConfiguration&&) noexcept = default;
        VideoStreamConfiguration& operator=(VideoStreamConfiguration const&) & noexcept = default;
        VideoStreamConfiguration& operator=(VideoStreamConfiguration&&) & noexcept = default;
    };
}
#endif
