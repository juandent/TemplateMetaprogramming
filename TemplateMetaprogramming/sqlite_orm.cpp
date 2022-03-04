
#include <string>
#include <type_traits>
#include <memory>
#include <optional>



namespace sqlite_orm {

    /**
     *  This is class that tells `sqlite_orm` that type is nullable. Nullable types
     *  are mapped to sqlite database as `NULL` and not-nullable are mapped as `NOT NULL`.
     *  Default nullability status for all types is `NOT NULL`. So if you want to map
     *  custom type as `NULL` (for example: boost::optional) you have to create a specialiation
     *  of type_is_nullable for your type and derive from `std::true_type`.
     */
    template<class T>
    struct type_is_nullable : public std::false_type {
        bool operator()(const T&) const {
            return true;
        }
    };

    /**
     *  This is a specialization for std::shared_ptr. std::shared_ptr is nullable in sqlite_orm.
     */
    template<class T>
    struct type_is_nullable<std::shared_ptr<T>> : public std::true_type {
        bool operator()(const std::shared_ptr<T>& t) const {
            return static_cast<bool>(t);
        }
    };

    /**
     *  This is a specialization for std::unique_ptr. std::unique_ptr is nullable too.
     */
    template<class T>
    struct type_is_nullable<std::unique_ptr<T>> : public std::true_type {
        bool operator()(const std::unique_ptr<T>& t) const {
            return static_cast<bool>(t);
        }
    };

    // #ifdef SQLITE_ORM_OPTIONAL_SUPPORTED
        /**
         *  This is a specialization for std::optional. std::optional is nullable.
         */
    template<class T>
    struct type_is_nullable<std::optional<T>> : public std::true_type {
        bool operator()(const std::optional<T>& t) const {
            return t.has_value();
        }
    };
    // #endif  // SQLITE_ORM_OPTIONAL_SUPPORTED

    struct column_base {

        /**
         *  Column name. Specified during construction in `make_column`.
         */
        const std::string name;
    };



    /**
             *  This class stores single column info. column_t is a pair of [column_name:member_pointer] mapped to a storage
             *  O is a mapped class, e.g. User
             *  T is a mapped class'es field type, e.g. &User::name
             *  Op... is a constraints pack, e.g. primary_key_t, autoincrement_t etc
             */
    template<class O, class T, class G /* = const T& (O::*)() const*/, class S /* = void (O::*)(T)*/, class... Op>
    struct column_t : column_base {
        using object_type = O;
        using field_type = T;
        using constraints_type = std::tuple<Op...>;
        using member_pointer_t = field_type object_type::*;
        using getter_type = G;
        using setter_type = S;

        /**
         *  Member pointer used to read/write member
         */
        member_pointer_t member_pointer /* = nullptr*/;

        /**
         *  Getter member function pointer to get a value. If member_pointer is null than
         *  `getter` and `setter` must be not null
         */
        getter_type getter /* = nullptr*/;

        /**
         *  Setter member function
         */
        setter_type setter /* = nullptr*/;

        /**
         *  Constraints tuple
         */
        constraints_type constraints;

        column_t(std::string name_,
            member_pointer_t member_pointer_,
            getter_type getter_,
            setter_type setter_,
            constraints_type constraints_) :
            column_base{ std::move(name_) },
            member_pointer(member_pointer_), getter(getter_), setter(setter_), constraints(move(constraints_)) {}

        /**
         *  Simplified interface for `NOT NULL` constraint
         */
        bool not_null() const {
            return !type_is_nullable<field_type>::value;
        }

        template<class Opt>
        constexpr bool has() const {
            return tuple_helper::tuple_contains_type<Opt, constraints_type>::value;
        }

        template<class O1, class O2, class... Opts>
        constexpr bool has_every() const {
            if (has<O1>() && has<O2>()) {
                return true;
            }
            else {
                return has_every<Opts...>();
            }
        }

        template<class O1>
        constexpr bool has_every() const {
            return has<O1>();
        }

        /**
         *  Simplified interface for `DEFAULT` constraint
         *  @return string representation of default value if it exists otherwise nullptr
         */
        std::unique_ptr<std::string> default_value() const {
            std::unique_ptr<std::string> res;
            iterate_tuple(this->constraints, [&res](auto& v) {
                auto dft = internal::default_value_extractor()(v);
                if (dft) {
                    res = std::move(dft);
                }
                });
            return res;
        }
    };



        template<class T>
    struct is_column : public std::false_type {};

    /**
     *  Column traits. Specialized case case.
     */
    template<class O, class T, class... Op>
    struct is_column<column_t<O, T, Op...>> : public std::true_type {};


    namespace internal {

        static inline decltype(auto) empty_callable() {
            static auto res = [](auto &&...) {};
            return (res);
        }

        template<typename T, typename F>
        decltype(auto) static_if(std::true_type, const T& t, const F&) {
            return (t);
        }

        template<typename T, typename F>
        decltype(auto) static_if(std::false_type, const T&, const F& f) {
            return (f);
        }

        template<bool B, typename T, typename F>
        decltype(auto) static_if(const T& t, const F& f) {
            return static_if(std::integral_constant<bool, B>{}, t, f);
        }

        template<bool B, typename T>
        decltype(auto) static_if(const T& t) {
            return static_if(std::integral_constant<bool, B>{}, t, empty_callable());
        }

        template<typename T>
        using static_not = std::integral_constant<bool, !T::value>;
    }

    template<class L>
    void for_each_column(const L& l) const {
        iterate_tuple(this->columns, [&l](auto& column) {
            using column_type = typename std::decay<decltype(column)>::type;
            static_if < is_column<column_type>{} > (l)(column);
            });
    }

	

}

	