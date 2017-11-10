// Implementation of tf::overload is borrowed from Boost.Hana.

#include <type_traits>

namespace tf {

  namespace dtl_ {
    template <typename T, typename U = typename std::remove_reference<T>::type>
    struct decay {
      using type = typename std::remove_cv<U>::type;
    };

    template <typename T, typename U>
    struct decay<T, U[]> {
      using type = U *;
    };
    template <typename T, typename U, std::size_t N>
    struct decay<T, U[N]> {
      using type = U *;
    };

    template <typename T, typename R, typename... A>
    struct decay<T, R(A...)> {
      using type = R (*)(A...);
    };
    template <typename T, typename R, typename... A>
    struct decay<T, R(A..., ...)> {
      using type = R (*)(A..., ...);
    };
  } // namespace dtl_

  template <typename F, typename... G>
  struct overload_t : overload_t<F>::type, overload_t<G...>::type {
    using type = overload_t;
    using overload_t<F>::type::operator();
    using overload_t<G...>::type::operator();

    template <typename F_, typename... G_>
    constexpr explicit overload_t(F_ &&f, G_ &&... g)
        : overload_t<F>::type(static_cast<F_ &&>(f)),
          overload_t<G...>::type(static_cast<G_ &&>(g)...) {}
  };

  template <typename F>
  struct overload_t<F> {
    using type = F;
  };

  template <typename R, typename... Args>
  struct overload_t<R (*)(Args...)> {
    using type = overload_t;
    R (*fptr_)(Args...);

    explicit constexpr overload_t(R (*fp)(Args...)) : fptr_(fp) {}

    constexpr R operator()(Args... args) const {
      return fptr_(static_cast<Args &&>(args)...);
    }
  };

  struct make_overload_t {
    template <typename... F, typename Overload = typename overload_t<
                                 typename dtl_::decay<F>::type...>::type>
    constexpr Overload operator()(F &&... f) const {
      return Overload(static_cast<F &&>(f)...);
    }
  };

  constexpr make_overload_t overload{};

} // namespace tf