// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_ApplicationModel_Search_H
#define WINRT_Windows_ApplicationModel_Search_H
#include "winrt/base.h"
static_assert(winrt::check_version(CPPWINRT_VERSION, "2.0.210503.4"), "Mismatched C++/WinRT headers.");
#define CPPWINRT_VERSION "2.0.210503.4"
#include "winrt/Windows.ApplicationModel.h"
#include "winrt/impl/Windows.Foundation.Collections.2.h"
#include "winrt/impl/Windows.Storage.2.h"
#include "winrt/impl/Windows.Storage.Streams.2.h"
#include "winrt/impl/Windows.ApplicationModel.Search.2.h"
namespace winrt::impl
{
    template <typename D> WINRT_IMPL_AUTO(void) consume_Windows_ApplicationModel_Search_ILocalContentSuggestionSettings<D>::Enabled(bool value) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ILocalContentSuggestionSettings)->put_Enabled(value));
    }
    template <typename D> WINRT_IMPL_AUTO(bool) consume_Windows_ApplicationModel_Search_ILocalContentSuggestionSettings<D>::Enabled() const
    {
        bool value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ILocalContentSuggestionSettings)->get_Enabled(&value));
        return value;
    }
    template <typename D> WINRT_IMPL_AUTO(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Storage::StorageFolder>) consume_Windows_ApplicationModel_Search_ILocalContentSuggestionSettings<D>::Locations() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ILocalContentSuggestionSettings)->get_Locations(&value));
        return winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Storage::StorageFolder>{ value, take_ownership_from_abi };
    }
    template <typename D> WINRT_IMPL_AUTO(void) consume_Windows_ApplicationModel_Search_ILocalContentSuggestionSettings<D>::AqsFilter(param::hstring const& value) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ILocalContentSuggestionSettings)->put_AqsFilter(*(void**)(&value)));
    }
    template <typename D> WINRT_IMPL_AUTO(hstring) consume_Windows_ApplicationModel_Search_ILocalContentSuggestionSettings<D>::AqsFilter() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ILocalContentSuggestionSettings)->get_AqsFilter(&value));
        return hstring{ value, take_ownership_from_abi };
    }
    template <typename D> WINRT_IMPL_AUTO(winrt::Windows::Foundation::Collections::IVector<hstring>) consume_Windows_ApplicationModel_Search_ILocalContentSuggestionSettings<D>::PropertiesToMatch() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ILocalContentSuggestionSettings)->get_PropertiesToMatch(&value));
        return winrt::Windows::Foundation::Collections::IVector<hstring>{ value, take_ownership_from_abi };
    }
    template <typename D> WINRT_IMPL_AUTO(winrt::Windows::Foundation::Collections::IVectorView<hstring>) consume_Windows_ApplicationModel_Search_ISearchPaneQueryLinguisticDetails<D>::QueryTextAlternatives() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchPaneQueryLinguisticDetails)->get_QueryTextAlternatives(&value));
        return winrt::Windows::Foundation::Collections::IVectorView<hstring>{ value, take_ownership_from_abi };
    }
    template <typename D> WINRT_IMPL_AUTO(uint32_t) consume_Windows_ApplicationModel_Search_ISearchPaneQueryLinguisticDetails<D>::QueryTextCompositionStart() const
    {
        uint32_t value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchPaneQueryLinguisticDetails)->get_QueryTextCompositionStart(&value));
        return value;
    }
    template <typename D> WINRT_IMPL_AUTO(uint32_t) consume_Windows_ApplicationModel_Search_ISearchPaneQueryLinguisticDetails<D>::QueryTextCompositionLength() const
    {
        uint32_t value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchPaneQueryLinguisticDetails)->get_QueryTextCompositionLength(&value));
        return value;
    }
    template <typename D> WINRT_IMPL_AUTO(winrt::Windows::Foundation::Collections::IVectorView<hstring>) consume_Windows_ApplicationModel_Search_ISearchQueryLinguisticDetails<D>::QueryTextAlternatives() const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetails)->get_QueryTextAlternatives(&value));
        return winrt::Windows::Foundation::Collections::IVectorView<hstring>{ value, take_ownership_from_abi };
    }
    template <typename D> WINRT_IMPL_AUTO(uint32_t) consume_Windows_ApplicationModel_Search_ISearchQueryLinguisticDetails<D>::QueryTextCompositionStart() const
    {
        uint32_t value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetails)->get_QueryTextCompositionStart(&value));
        return value;
    }
    template <typename D> WINRT_IMPL_AUTO(uint32_t) consume_Windows_ApplicationModel_Search_ISearchQueryLinguisticDetails<D>::QueryTextCompositionLength() const
    {
        uint32_t value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetails)->get_QueryTextCompositionLength(&value));
        return value;
    }
    template <typename D> WINRT_IMPL_AUTO(winrt::Windows::ApplicationModel::Search::SearchQueryLinguisticDetails) consume_Windows_ApplicationModel_Search_ISearchQueryLinguisticDetailsFactory<D>::CreateInstance(param::iterable<hstring> const& queryTextAlternatives, uint32_t queryTextCompositionStart, uint32_t queryTextCompositionLength) const
    {
        void* value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetailsFactory)->CreateInstance(*(void**)(&queryTextAlternatives), queryTextCompositionStart, queryTextCompositionLength, &value));
        return winrt::Windows::ApplicationModel::Search::SearchQueryLinguisticDetails{ value, take_ownership_from_abi };
    }
    template <typename D> WINRT_IMPL_AUTO(uint32_t) consume_Windows_ApplicationModel_Search_ISearchSuggestionCollection<D>::Size() const
    {
        uint32_t value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchSuggestionCollection)->get_Size(&value));
        return value;
    }
    template <typename D> WINRT_IMPL_AUTO(void) consume_Windows_ApplicationModel_Search_ISearchSuggestionCollection<D>::AppendQuerySuggestion(param::hstring const& text) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchSuggestionCollection)->AppendQuerySuggestion(*(void**)(&text)));
    }
    template <typename D> WINRT_IMPL_AUTO(void) consume_Windows_ApplicationModel_Search_ISearchSuggestionCollection<D>::AppendQuerySuggestions(param::iterable<hstring> const& suggestions) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchSuggestionCollection)->AppendQuerySuggestions(*(void**)(&suggestions)));
    }
    template <typename D> WINRT_IMPL_AUTO(void) consume_Windows_ApplicationModel_Search_ISearchSuggestionCollection<D>::AppendResultSuggestion(param::hstring const& text, param::hstring const& detailText, param::hstring const& tag, winrt::Windows::Storage::Streams::IRandomAccessStreamReference const& image, param::hstring const& imageAlternateText) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchSuggestionCollection)->AppendResultSuggestion(*(void**)(&text), *(void**)(&detailText), *(void**)(&tag), *(void**)(&image), *(void**)(&imageAlternateText)));
    }
    template <typename D> WINRT_IMPL_AUTO(void) consume_Windows_ApplicationModel_Search_ISearchSuggestionCollection<D>::AppendSearchSeparator(param::hstring const& label) const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchSuggestionCollection)->AppendSearchSeparator(*(void**)(&label)));
    }
    template <typename D> WINRT_IMPL_AUTO(bool) consume_Windows_ApplicationModel_Search_ISearchSuggestionsRequest<D>::IsCanceled() const
    {
        bool value{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequest)->get_IsCanceled(&value));
        return value;
    }
    template <typename D> WINRT_IMPL_AUTO(winrt::Windows::ApplicationModel::Search::SearchSuggestionCollection) consume_Windows_ApplicationModel_Search_ISearchSuggestionsRequest<D>::SearchSuggestionCollection() const
    {
        void* collection{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequest)->get_SearchSuggestionCollection(&collection));
        return winrt::Windows::ApplicationModel::Search::SearchSuggestionCollection{ collection, take_ownership_from_abi };
    }
    template <typename D> WINRT_IMPL_AUTO(winrt::Windows::ApplicationModel::Search::SearchSuggestionsRequestDeferral) consume_Windows_ApplicationModel_Search_ISearchSuggestionsRequest<D>::GetDeferral() const
    {
        void* deferral{};
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequest)->GetDeferral(&deferral));
        return winrt::Windows::ApplicationModel::Search::SearchSuggestionsRequestDeferral{ deferral, take_ownership_from_abi };
    }
    template <typename D> WINRT_IMPL_AUTO(void) consume_Windows_ApplicationModel_Search_ISearchSuggestionsRequestDeferral<D>::Complete() const
    {
        check_hresult(WINRT_IMPL_SHIM(winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequestDeferral)->Complete());
    }
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Windows::ApplicationModel::Search::ILocalContentSuggestionSettings> : produce_base<D, winrt::Windows::ApplicationModel::Search::ILocalContentSuggestionSettings>
    {
        int32_t __stdcall put_Enabled(bool value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().Enabled(value);
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_Enabled(bool* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<bool>(this->shim().Enabled());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_Locations(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Storage::StorageFolder>>(this->shim().Locations());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall put_AqsFilter(void* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().AqsFilter(*reinterpret_cast<hstring const*>(&value));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_AqsFilter(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<hstring>(this->shim().AqsFilter());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_PropertiesToMatch(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Windows::Foundation::Collections::IVector<hstring>>(this->shim().PropertiesToMatch());
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Windows::ApplicationModel::Search::ISearchPaneQueryLinguisticDetails> : produce_base<D, winrt::Windows::ApplicationModel::Search::ISearchPaneQueryLinguisticDetails>
    {
        int32_t __stdcall get_QueryTextAlternatives(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Windows::Foundation::Collections::IVectorView<hstring>>(this->shim().QueryTextAlternatives());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_QueryTextCompositionStart(uint32_t* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<uint32_t>(this->shim().QueryTextCompositionStart());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_QueryTextCompositionLength(uint32_t* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<uint32_t>(this->shim().QueryTextCompositionLength());
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetails> : produce_base<D, winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetails>
    {
        int32_t __stdcall get_QueryTextAlternatives(void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Windows::Foundation::Collections::IVectorView<hstring>>(this->shim().QueryTextAlternatives());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_QueryTextCompositionStart(uint32_t* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<uint32_t>(this->shim().QueryTextCompositionStart());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_QueryTextCompositionLength(uint32_t* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<uint32_t>(this->shim().QueryTextCompositionLength());
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetailsFactory> : produce_base<D, winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetailsFactory>
    {
        int32_t __stdcall CreateInstance(void* queryTextAlternatives, uint32_t queryTextCompositionStart, uint32_t queryTextCompositionLength, void** value) noexcept final try
        {
            clear_abi(value);
            typename D::abi_guard guard(this->shim());
            *value = detach_from<winrt::Windows::ApplicationModel::Search::SearchQueryLinguisticDetails>(this->shim().CreateInstance(*reinterpret_cast<winrt::Windows::Foundation::Collections::IIterable<hstring> const*>(&queryTextAlternatives), queryTextCompositionStart, queryTextCompositionLength));
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Windows::ApplicationModel::Search::ISearchSuggestionCollection> : produce_base<D, winrt::Windows::ApplicationModel::Search::ISearchSuggestionCollection>
    {
        int32_t __stdcall get_Size(uint32_t* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<uint32_t>(this->shim().Size());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall AppendQuerySuggestion(void* text) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().AppendQuerySuggestion(*reinterpret_cast<hstring const*>(&text));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall AppendQuerySuggestions(void* suggestions) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().AppendQuerySuggestions(*reinterpret_cast<winrt::Windows::Foundation::Collections::IIterable<hstring> const*>(&suggestions));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall AppendResultSuggestion(void* text, void* detailText, void* tag, void* image, void* imageAlternateText) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().AppendResultSuggestion(*reinterpret_cast<hstring const*>(&text), *reinterpret_cast<hstring const*>(&detailText), *reinterpret_cast<hstring const*>(&tag), *reinterpret_cast<winrt::Windows::Storage::Streams::IRandomAccessStreamReference const*>(&image), *reinterpret_cast<hstring const*>(&imageAlternateText));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall AppendSearchSeparator(void* label) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().AppendSearchSeparator(*reinterpret_cast<hstring const*>(&label));
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequest> : produce_base<D, winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequest>
    {
        int32_t __stdcall get_IsCanceled(bool* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<bool>(this->shim().IsCanceled());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall get_SearchSuggestionCollection(void** collection) noexcept final try
        {
            clear_abi(collection);
            typename D::abi_guard guard(this->shim());
            *collection = detach_from<winrt::Windows::ApplicationModel::Search::SearchSuggestionCollection>(this->shim().SearchSuggestionCollection());
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall GetDeferral(void** deferral) noexcept final try
        {
            clear_abi(deferral);
            typename D::abi_guard guard(this->shim());
            *deferral = detach_from<winrt::Windows::ApplicationModel::Search::SearchSuggestionsRequestDeferral>(this->shim().GetDeferral());
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequestDeferral> : produce_base<D, winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequestDeferral>
    {
        int32_t __stdcall Complete() noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().Complete();
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
}
WINRT_EXPORT namespace winrt::Windows::ApplicationModel::Search
{
    inline LocalContentSuggestionSettings::LocalContentSuggestionSettings() :
        LocalContentSuggestionSettings(impl::call_factory_cast<LocalContentSuggestionSettings(*)(winrt::Windows::Foundation::IActivationFactory const&), LocalContentSuggestionSettings>([](winrt::Windows::Foundation::IActivationFactory const& f) { return f.template ActivateInstance<LocalContentSuggestionSettings>(); }))
    {
    }
    inline SearchQueryLinguisticDetails::SearchQueryLinguisticDetails(param::iterable<hstring> const& queryTextAlternatives, uint32_t queryTextCompositionStart, uint32_t queryTextCompositionLength) :
        SearchQueryLinguisticDetails(impl::call_factory<SearchQueryLinguisticDetails, ISearchQueryLinguisticDetailsFactory>([&](ISearchQueryLinguisticDetailsFactory const& f) { return f.CreateInstance(queryTextAlternatives, queryTextCompositionStart, queryTextCompositionLength); }))
    {
    }
}
namespace std
{
#ifndef WINRT_LEAN_AND_MEAN
    template<> struct hash<winrt::Windows::ApplicationModel::Search::ILocalContentSuggestionSettings> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::ISearchPaneQueryLinguisticDetails> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetails> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::ISearchQueryLinguisticDetailsFactory> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::ISearchSuggestionCollection> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequest> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::ISearchSuggestionsRequestDeferral> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::LocalContentSuggestionSettings> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::SearchPaneQueryLinguisticDetails> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::SearchQueryLinguisticDetails> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::SearchSuggestionCollection> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::SearchSuggestionsRequest> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::ApplicationModel::Search::SearchSuggestionsRequestDeferral> : winrt::impl::hash_base {};
#endif
}
#endif
