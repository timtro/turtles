# `either-monad-turtle`

Monadic bind for the Either monad:
  mbind :: EirtherM<A> → (A → EitherM<B>) → EitherN<B>
where
  EitherM<T> = std::variant<T, errorType>
Expect the payload to be the first (0th) term in the variant type.
Expect the error type to be the second term in the variant type: