#ifndef VG_HPP_INCLUDED_PSDOIJAA9FODIUSOI4JLAKJSDFLASKJASLKJFDASLKJASJKFLKJDFFFF
#define VG_HPP_INCLUDED_PSDOIJAA9FODIUSOI4JLAKJSDFLASKJASLKJFDASLKJASJKFLKJDFFFF

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <functional>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

namespace vg {

template<typename T>
struct singleton
{
  typedef T value_type;
  typedef singleton self_type;

  singleton(const self_type&) = delete;
  self_type& operator=(const self_type&) = delete;
  singleton(self_type&&) = delete;
  self_type& operator=(self_type&&) = delete;
  singleton() = delete;

private:
  struct constuctor
  {
    constuctor() noexcept { self_type::instance(); }
    inline void null_action() const noexcept {}
  };

  static constuctor constuctor_;

public:
  static value_type& instance() noexcept
  {
    static value_type instance_;
    constuctor_.null_action();
    return instance_;
  }
};

template<typename T>
typename singleton<T>::constuctor singleton<T>::constuctor_;

template<typename Return_Type, typename Engine>
struct normal
{
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef Engine engine_type;

  engine_type& e_;

  explicit normal(const seed_type sd = 0)
    : e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(); }

protected:
  return_type do_generation() const { return box_muller_method(); }

private:
  return_type kinderman_monahan_method() const
  {
    const final_type u = e_();
    const final_type v = (e_() - 0.5L) * 4.0L * u * std::sqrt(-std::log(u));
    return static_cast<return_type>(v / u);
  }

  return_type box_muller_method() const
  {
    final_type u1(0), u2(0);
    final_type v1(0), v2(0);
    final_type s(2);

    while (s > final_type(1)) {
      u1 = e_();
      u2 = e_();
      v1 = u1 + u1 - final_type(1);
      v2 = u2 + u2 - final_type(1);
      s = v1 * v1 + v2 * v2;
    }

    const final_type tmp = -std::log(s);
    const final_type ans = v1 * std::sqrt((tmp + tmp) / s);
    return static_cast<return_type>(ans);
  }
};

template<typename Return_Type, typename Engine>
struct gamma : private normal<Return_Type, Engine>
{
  typedef normal<Return_Type, Engine> normal_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef return_type value_type;
  typedef typename engine_type::size_type size_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  value_type a_;
  value_type b_;
  engine_type& e_;

  explicit gamma(const value_type a = value_type(1),
                 const value_type b = value_type(1),
                 const seed_type sd = 0)
    : a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    assert(b > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_, b_); }

protected:
  return_type do_generation(const final_type A, const final_type B) const
  {
    return marsaglia_tsang_method(A) * B;
  }

  return_type do_generation(const final_type A) const
  {
    return marsaglia_tsang_method(A);
  }

private:
  return_type marsaglia_tsang_method(const final_type A) const
  {
    const final_type a = A < final_type(1) ? A + final_type(1) : A;
    const final_type d = a - final_type(1) / final_type(3);
    const final_type c = final_type(1) / final_type(3) / std::sqrt(d);
    final_type u(0);
    final_type v(0);
    final_type x(0);

    for (;;) {
      for (;;) {
        x = normal_type::do_generation();
        v = final_type(1) + c * x;

        if (v > 0) {
          break;
        }
      }

      const final_type xx = x * x;
      v *= v * v;
      u = e_();

      if (u < final_type(1) - final_type(0.0331) * xx * xx) {
        break;
      }

      if (std::log(u) < 0.5 * xx + d * (final_type(1) - v + std::log(v))) {
        break;
      }
    }

    final_type ans = d * v;

    if (A < 1) {
      ans *= std::pow(e_(), final_type(1) / A);
    }

    return static_cast<return_type>(ans);
  }
};

template<typename Return_Type, typename Engine>
struct beta : private gamma<Return_Type, Engine>
{
  typedef gamma<Return_Type, Engine> gamma_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef return_type value_type;
  typedef typename engine_type::size_type size_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  value_type a_;
  value_type b_;
  engine_type& e_;

  explicit beta(const value_type a = value_type(1),
                const value_type b = value_type(1),
                const seed_type sd = 0) noexcept
    : a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    assert(a_ > 0);
    assert(b_ > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const noexcept { return do_generation(a_, b_); }

protected:
  return_type do_generation(const final_type A,
                            const final_type B) const noexcept
  {
    return direct_beta_impl(A, B);
  }

private:
  return_type direct_beta_impl(const final_type A,
                               const final_type B) const noexcept
  {
    const final_type a = gamma_type::do_generation(A);
    const final_type b = gamma_type::do_generation(B);
    return static_cast<return_type>(a / (a + b));
  }
};

template<typename Return_Type, typename Engine>
struct arcsine : private beta<Return_Type, Engine>
{
  typedef beta<Return_Type, Engine> beta_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef Engine engine_type;

  engine_type& e_;

  explicit arcsine(const seed_type sd = 0) noexcept
    : e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const noexcept { return do_generation(); }

protected:
  return_type do_generation() const noexcept { return beta_impl(); }

private:
  return_type beta_impl() const noexcept
  {
    return beta_type::do_generation(final_type(0.5), final_type(0.5));
  }

private:
  return_type direct_impl() const noexcept
  {
    const final_type u = e_();
    const final_type pi = 3.1415926535897932384626433L;
    const final_type ans = std::sin(pi * u);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct balding_nichols : private beta<typename Engine::final_type, Engine>
{
  typedef beta<typename Engine::final_type, Engine> beta_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  final_type f_;
  final_type p_;
  engine_type& e_;

  explicit balding_nichols(const final_type f = final_type(0.5),
                           const final_type p = final_type(0.5),
                           const seed_type sd = 0) noexcept
    : f_(f)
    , p_(p)
    , e_(singleton<engine_type>::instance())
  {
    assert(f > final_type{ 0 });
    assert(f < final_type{ 1 });
    assert(p > final_type{ 0 });
    assert(p < final_type{ 1 });
    e_.reset_seed(sd);
  }

  return_type operator()() const noexcept { return do_generation(f_, p_); }

protected:
  return_type do_generation(const final_type F,
                            const final_type P) const noexcept
  {
    return direct_balding_nichols_impl(F, P);
  }

private:
  return_type direct_balding_nichols_impl(const final_type F,
                                          const final_type P) const noexcept
  {
    const final_type l = final_type{ 1 };
    const final_type ans =
      beta_type::do_generation(P * (l - F) / F, (l - P) * (l - F) / F);
    return static_cast<return_type>(ans);
  }
};

template<typename Return_Type, typename Engine>
struct bernoulli
{
  typedef Engine engine_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;

  final_type p_;
  engine_type& e_;

  explicit bernoulli(final_type p = final_type(0.5),
                     const seed_type s = seed_type(0)) noexcept
    : p_(p)
    , e_(singleton<engine_type>::instance())
  {
    assert(p_ >= final_type(0));
    assert(p_ <= final_type(1));
    e_.reset_seed(s);
  }

  return_type operator()() const noexcept { return do_generation(p_); }

protected:
  return_type do_generation(const final_type P) const noexcept
  {
    return coin_flip_method(P);
  }

private:
  return_type coin_flip_method(const final_type P) const noexcept
  {
    if (e_() < P) {
      return 1;
    }

    return 0;
  }
};

template<typename Return_Type, typename Engine>
struct binomial : private beta<typename Engine::final_type, Engine>
{
  typedef beta<typename Engine::final_type, Engine> beta_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  size_type n_;
  final_type p_;
  engine_type& e_;

  explicit binomial(size_type n = size_type(1),
                    final_type p = final_type(0.5),
                    const seed_type sd = seed_type(0)) noexcept
    : n_(n)
    , p_(p)
    , e_(singleton<engine_type>::instance())
  {
    assert(n_ != size_type(0));
    assert(p_ > final_type(0));
    assert(p_ < final_type(1));
    e_.reset_seed(sd);
  }

  return_type operator()() const noexcept { return do_generation(n_, p_); }

protected:
  return_type do_generation(const size_type N,
                            const final_type P) const noexcept
  {
    if (0 == N)
      return 0;

    if (N < 8) {
      return coin_flip_method(N, P);
    }

    if (N * P < 16) {
      return second_waiting_time_method(N, P);
    }

    return rejection_method(N, P);
  }

private:
  return_type coin_flip_method(const size_type N,
                               const final_type P) const noexcept
  {
    value_type ans = 0;

    for (size_type i = 0; i < N; ++i)
      if (e_() < P) {
        ++ans;
      }

    return ans;
  }

private:
  return_type second_waiting_time_method(const size_type N,
                                         const final_type P) const noexcept
  {
    const final_type p = P > 0.5 ? 1 - P : P;
    const final_type q = -std::log(1.0 - p);
    return_type ans = 0;
    final_type sum = 0;

    for (;;) {
      const final_type e = -std::log(e_());
      sum += e / (N - ans);

      if (sum > q) {
        break;
      }

      ++ans;
    }

    return static_cast<return_type>(p_ > 0.5 ? N - ans : ans);
  }

private:
  return_type rejection_method(const size_type N,
                               const final_type P) const noexcept
  {
    size_type n = N;
    final_type p = P;
    size_type ans = 0;

    while (n > 8) {
      const size_type a = 1 + (n / 2);
      const size_type b = 1 + n - a;
      const final_type X =
        beta_type::do_generation(final_type(a), final_type(b));

      if (X >= p) {
        n = a - 1;
        p /= X;
      }

      else {
        ans += a;
        n = b - 1;
        p = (p - X) / (final_type(1) - X);
      }
    }

    ans += coin_flip_method(n, p);
    return static_cast<return_type>(ans);
  }
};

template<typename Input_Iterator>
typename std::iterator_traits<Input_Iterator>::value_type
mean(Input_Iterator first, Input_Iterator last) noexcept
{
  typedef typename std::iterator_traits<Input_Iterator>::value_type value_type;
  value_type const n = std::distance(first, last);
  return std::accumulate(first, last, value_type(0)) / n;
}

template<typename Input_Iterator>
typename std::iterator_traits<Input_Iterator>::value_type
kurtosis(Input_Iterator first, Input_Iterator last) noexcept
{
  typedef typename std::iterator_traits<Input_Iterator>::value_type value_type;
  std::vector<value_type> x2(first, last);
  std::for_each(x2.begin(), x2.end(), [](value_type& v) { v *= v; });
  std::vector<value_type> x4 = x2;
  std::for_each(x4.begin(), x4.end(), [](value_type& v) { v *= v; });
  value_type const mu_2 = mean(x2.begin(), x2.end());
  value_type const mu_4 = mean(x4.begin(), x4.end());
  return mu_4 / (mu_2 * mu_2) - value_type(3);
}

template<typename T, std::size_t Level = 0>
struct proxy;

template<typename T, std::size_t Level>
struct proxy : proxy<T, Level - 1>
{};

template<typename T>
struct proxy<T, 0> : T
{};

template<typename Input_Iterator>
typename std::iterator_traits<Input_Iterator>::value_type
variance(Input_Iterator first, Input_Iterator last) noexcept
{
  typedef typename std::iterator_traits<Input_Iterator>::value_type value_type;
  value_type const mu = mean(first, last);
  value_type const n = std::distance(first, last);
  std::vector<value_type> arr(first, last);
  std::for_each(arr.begin(), arr.end(), [mu](value_type& v) { v -= mu; });
  return std::inner_product(arr.begin(), arr.end(), arr.begin(), value_type()) /
         n;
}

template<typename Input_Iterator>
typename std::iterator_traits<Input_Iterator>::value_type
skewness(Input_Iterator first, Input_Iterator last) noexcept
{
  typedef typename std::iterator_traits<Input_Iterator>::value_type value_type;
  value_type const mu = mean(first, last);
  value_type const va = std::sqrt(variance(first, last));
  value_type const n = std::distance(first, last);
  std::vector<value_type> arr(first, last);
  std::for_each(arr.begin(), arr.end(), [mu, va](value_type& v) {
    v -= mu;
    v /= va;
    v *= v * v;
  });
  return std::accumulate(arr.begin(), arr.end(), value_type()) / n;
}

template<typename Return_Type, typename Engine>
struct beta_binomial
  : private proxy<beta<typename Engine::final_type, Engine>>
  , private proxy<binomial<Return_Type, Engine>>
{
  typedef proxy<beta<typename Engine::final_type, Engine>> beta_type;
  typedef proxy<binomial<Return_Type, Engine>> binomial_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef return_type value_type;
  typedef typename engine_type::size_type size_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  value_type n_;
  final_type a_;
  final_type b_;
  engine_type& e_;

  explicit beta_binomial(const value_type n = value_type(10),
                         const final_type a = final_type(1),
                         const final_type b = final_type(1),
                         const seed_type sd = 0) noexcept
    : n_(n)
    , a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    assert(n > 0);
    assert(a > 0);
    assert(b > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const noexcept { return do_generation(n_, a_, b_); }

protected:
  return_type do_generation(const value_type N,
                            const final_type A,
                            const final_type B) const noexcept
  {
    return direct_beta_binomial_impl(N, A, B);
  }

private:
  return_type direct_beta_binomial_impl(const value_type N,
                                        const final_type A,
                                        const final_type B) const noexcept
  {
    const final_type p =
      static_cast<final_type>(beta_type::do_generation(A, B));
    const final_type ans = static_cast<final_type>(
      binomial_type::do_generation(static_cast<size_type>(N), p));
    return static_cast<return_type>(ans);
  }
};

template<typename Return_Type, typename Engine>
struct poisson
  : private proxy<normal<Return_Type, Engine>>
  , private proxy<gamma<Return_Type, Engine>>
  , private proxy<binomial<Return_Type, Engine>>
{
  typedef proxy<normal<Return_Type, Engine>> normal_type;
  typedef proxy<gamma<Return_Type, Engine>> gamma_type;
  typedef proxy<binomial<Return_Type, Engine>> binomial_type;

  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef Engine engine_type;

  final_type lambda_;
  engine_type& e_;

  explicit poisson(const final_type lambda = 1, const seed_type sd = 0)
    : lambda_(lambda)
    , e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(lambda_); }

protected:
  return_type do_generation(const final_type lambda) const
  {
    if (lambda < final_type(10)) {
      return exponential_inter_arrival_times_method(lambda);
    }

    return rejection_method_from_kruth(lambda);
  }

private:
  return_type exponential_inter_arrival_times_method(
    const final_type lambda) const
  {
    return_type ans = 0;
    const final_type exp_lambda = std::exp(-lambda);
    final_type prod = e_();

    while (prod > exp_lambda) {
      prod *= e_();
      ++ans;
    }

    return ans;
  }

  return_type rejection_method_from_kruth(final_type lambda) const
  {
    std::size_t ans = 0;

    for (;;) {
      std::size_t M = static_cast<std::size_t>(lambda * 0.875);
      const final_type X =
        gamma_type::do_generation(static_cast<final_type>(M));

      if (X > lambda) {
        return static_cast<return_type>(
          ans + binomial_type::do_generation(M - 1, lambda / X));
      }

      else {
        ans += M;
        lambda -= X;
      }

      if (lambda < 10) {
        return static_cast<return_type>(
          ans + exponential_inter_arrival_times_method(lambda));
      }
    }
  }

  return_type rejection_method(const final_type lambda) const
  {
    const final_type mu = std::floor(lambda);
    const final_type delta = std::round(mu / final_type(2) + final_type(3));
    const final_type mu_mu_delta = mu + mu + delta;
    const final_type pi = 3.1415926535897932384626433L;
    const final_type c_1 = std::sqrt(pi * mu / final_type(2));
    const final_type c_2 = c_1 + std::sqrt(pi * mu_mu_delta / final_type(4)) *
                                   std::exp(final_type(1) / (mu_mu_delta));
    const final_type c_3 = c_2 + final_type(1);
    const final_type c_4 = c_3 + std::exp(final_type(1) / final_type(78));
    const final_type c = c_4 + (mu_mu_delta + mu_mu_delta) / delta *
                                 std::exp(-delta * (final_type(2) + delta) /
                                          (mu_mu_delta + mu_mu_delta));
    final_type W;
    final_type X;

    for (;;) {
      final_type U = c * e_();
      final_type E = -std::log(e_());

      if (U <= c_1) {
        const final_type N = normal_type::do_generation();
        const final_type Y = -std::fabs(N) * std::sqrt(mu);
        X = std::floor(Y);
        W = -N * N / final_type(2) - E - X * std::log(lambda / mu);

        if (X >= -mu) {
          W = std::numeric_limits<final_type>::max();
        }
      }

      else if (U <= c_2) {
        const final_type N = normal_type::do_generation();
        const final_type Y =
          final_type(1) + std::fabs(N) * std::sqrt(mu_mu_delta / final_type(2));
        X = std::ceil(Y);
        W = Y * (final_type(2) - Y) / mu_mu_delta - E - X * log(lambda / mu);

        if (X <= delta) {
          W = std::numeric_limits<final_type>::max();
        }
      }

      else if (U <= c_3) {
        X = final_type(0);
        W = -E;
      }

      else if (U <= c_4) {
        X = final_type(1);
        W = -E - std::log(lambda / mu);
      }

      else {
        const final_type V = -std::log(e_());
        const final_type Y = delta + (V + V) * mu_mu_delta / delta;
        X = std::ceil(Y);
        W = delta * (final_type(2) + Y) / (mu_mu_delta + mu_mu_delta) - E -
            X * std::log(lambda / mu);
      }

      if (W > X * std::log(lambda) + std::lgamma(mu) - std::lgamma(mu + X)) {
        break;
      }
    }

    return X + mu;
  }
};

template<typename Return_Type, typename Engine>
struct generalized_hypergeometric_b3
  : private proxy<gamma<typename Engine::final_type, Engine>, 1>
  , private proxy<poisson<typename Engine::final_type, Engine>, 2>
{
  typedef proxy<gamma<typename Engine::final_type, Engine>, 1> gamma_type;
  typedef proxy<poisson<typename Engine::final_type, Engine>, 2> poisson_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type a_;
  value_type b_;
  value_type c_;
  engine_type& e_;

  explicit generalized_hypergeometric_b3(value_type a = 1,
                                         value_type b = 1,
                                         value_type c = 1,
                                         seed_type s = 0)
    : a_(a)
    , b_(b)
    , c_(c)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    assert(b > 0);
    assert(c > 0);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(a_, b_, c_); }

protected:
  return_type do_generation(const value_type a,
                            const value_type b,
                            const value_type c) const
  {
    return direct_impl(a, b, c);
  }

private:
  return_type direct_impl(const value_type a,
                          const value_type b,
                          const value_type c) const
  {
    const final_type Ga = gamma_type::do_generation(a);
    const final_type Gb = gamma_type::do_generation(b);
    const final_type Gc = gamma_type::do_generation(c);
    const final_type ans = poisson_type::do_generation(Ga * Gb / Gc);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct beta_pascal : private generalized_hypergeometric_b3<Return_Type, Engine>
{
  typedef generalized_hypergeometric_b3<Return_Type, Engine> GHgB3_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type k_;
  value_type r_;
  engine_type& e_;

  explicit beta_pascal(value_type k = 3, value_type r = 3, seed_type s = 0)
    : k_(k)
    , r_(r)
    , e_(singleton<engine_type>::instance())
  {
    assert(k >= 2);
    assert(r >= k);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(k_, r_); }

protected:
  return_type do_generation(const value_type k, const value_type r) const
  {
    return direct_impl(k, r);
  }

private:
  return_type direct_impl(const value_type k, const value_type r) const
  {
    const final_type r_1 = r - final_type(1);
    const final_type ans =
      GHgB3_type::do_generation(final_type(1), k - r_1, r_1);
    return ans;
  }
};

template<typename T>
struct newton_raphson
{
  typedef std::size_t size_type;
  typedef T value_type;
  typedef std::function<value_type(value_type)> function_type;

  value_type first_;
  value_type last_;
  function_type f_;
  function_type df_;
  const size_type times_;

  newton_raphson(const value_type first,
                 const value_type last,
                 const function_type f,
                 const function_type df,
                 const size_type times = 20) noexcept
    : first_(first)
    , last_(last)
    , f_(f)
    , df_(df)
    , times_(times)
  {}

  value_type operator()() const noexcept
  {
    value_type ans = (first_ + last_) / value_type(2);

    for (size_type i = 0; i < times_; ++i) {
      assert((ans - first_) * (ans - last_) < value_type(0));
      ans -= f_(ans) / df_(ans);
    }

    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct burr
{
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef return_type value_type;
  typedef typename engine_type::size_type size_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  size_type n_;
  final_type c_;
  final_type k_;
  final_type r_;
  engine_type& e_;

  explicit burr(const size_type n = size_type(1),
                const final_type c = final_type(1),
                const final_type k = final_type(1),
                const final_type r = final_type(1),
                const seed_type sd = 0) noexcept
    : n_(n)
    , c_(c)
    , k_(k)
    , r_(r)
    , e_(singleton<engine_type>::instance())
  {
    assert(n > 0);
    assert(n < 13);
    assert(c > 0);
    assert(k > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const noexcept
  {
    return static_cast<return_type>(do_generation(n_, c_, k_, r_));
  }

protected:
  final_type do_generation(const size_type N,
                           const final_type C,
                           const final_type K,
                           const final_type R) const noexcept
  {
    return direct_burr_impl(N, C, K, R);
  }

private:
  final_type direct_burr_impl(const size_type N,
                              const final_type C,
                              const final_type K,
                              const final_type R) const noexcept
  {
    const final_type u = e_();
    static const final_type l(1);
    static const final_type ll(2);
    const std::function<final_type(
      final_type, final_type, final_type, final_type)>
      inverse_function[12] = {

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type { return u; },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          return -std::log(-l + std::pow(u, -l / r));
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          return std::pow((std::pow(u, -l / r) - l), -l / k);
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          return c / (l + std::pow(std::pow(u, -l / r) - l, c));
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          return std::atan(-std::log((std::pow(u, -l / r) - l) / k));
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          return std::asinh(-std::log((std::pow(u, -l / r) - l) / k));
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          return std::atanh(std::pow(std::pow(ll, r) * u, l / r) - l);
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          const final_type pi_2 = 1.5707963267948966142313216L;
          return std::log(std::tan(pi_2 * std::pow(u, l / r)));
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          return std::log(std::pow(l + (ll / (l - u) - l) / k, l / r) - l);
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          return std::sqrt(-std::log(-std::pow(u, l / r) + l));
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          const final_type two_pi = final_type(2) * 3.1415926535897932384626433;
          std::function<final_type(final_type)> f = [&](final_type x) {
            return std::pow(x - std::sin(two_pi * x) / two_pi, r);
          };
          std::function<final_type(final_type)> df = [&](final_type x) {
            return std::pow(x - std::sin(two_pi * x) / two_pi, r - l) *
                   (l - std::cos(two_pi * x));
          };
          const final_type ans =
            (newton_raphson<final_type>(final_type(0), final_type(1), f, df))();
          return ans;
        },

        [](const final_type u,
           const final_type c,
           const final_type k,
           const final_type r) noexcept -> final_type {
          return std::pow(std::pow(l - u, -l / k) - l, l / c);
        }
      };
    return inverse_function[N - 1](u, C, K, R);
  }
};

template<typename Return_Type, typename Engine>
struct cauchy
{
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type delta_;
  engine_type& e_;

  explicit cauchy(const return_type delta = 1, const seed_type sd = 0)
    : delta_(delta)
    , e_(singleton<engine_type>::instance())
  {
    assert(delta_ > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(delta_); }

protected:
  return_type do_generation(const final_type Delta) const
  {
    return cauchy_direct_impl(delta_);
  }

private:
  return_type cauchy_direct_impl(const final_type Delta) const
  {
    const final_type pi = 3.1415926535897932384626433L;

    for (;;) {
      const final_type u = e_();

      if (u != final_type(0.5)) {
        return Delta * std::tan(pi * u);
      }
    }
  }
};

template<typename Return_Type, typename Engine>
struct chi_square : private gamma<Return_Type, Engine>
{
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef gamma<Return_Type, Engine> gamma_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;
  typedef typename engine_type::size_type size_type;

  size_type k_;
  engine_type& e_;

  explicit chi_square(const size_type k = 10, const seed_type sd = 0) noexcept
    : k_(k)
    , e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const noexcept { return do_generation(k_); }

protected:
  return_type do_generation(const size_type K) const noexcept
  {
    return chi_square_direct_impl(K);
  }

private:
  return_type chi_square_direct_impl(const size_type K) const noexcept
  {
    const final_type ans =
      gamma_type::do_generation(final_type(K) / final_type(2));
    return static_cast<return_type>(ans + ans);
  }
};

namespace special_function {

struct digamma
{
  long double operator()(long double x) const noexcept
  {
    static const long double S = 1.0e-10L;
    static const long double C = 255.0L;

    if (x <= 0.0L)
      return 0.0L;

    if (x <= S)
      return less_than_s(x);

    if (x >= C)
      return greater_than_c(x);

    return between_s_and_c_se(x);
  }

  long double less_than_s(const long double x) const noexcept
  {
    static const long double euler_constant =
      0.57721566490153286060651209008240243104215933593992L;
    return euler_constant - 1.0L / x;
  }

  long double between_s_and_c(const long double x) const noexcept
  {
    return 1.0L / x + digamma()(x - 1.0L);
  }

  long double between_s_and_c_se(const long double x) const noexcept
  {
    return -1.0L / x + digamma()(x + 1.0L);
  }

  long double greater_than_c(const long double x) const noexcept
  {
    static const long double a1 = 0.5L;
    static const long double a2 = 1.0L / 12.0L;
    static const long double a4 = 1.0L / 120.0L;
    static const long double a6 = 1.0L / 252.0L;
    long double r = 1.0L / x;
    long double ans = std::log(x) - r * a1;
    r *= r;
    ans -= r * (a2 - r * (a4 - r * a6));
    return ans;
  }
};

} // namespace special_function

template<typename Return_Type, typename Engine>
struct digamma : private generalized_hypergeometric_b3<Return_Type, Engine>
{
  typedef generalized_hypergeometric_b3<Return_Type, Engine> GHgB3_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type a_;
  value_type c_;
  engine_type& e_;

  explicit digamma(value_type a = 3, value_type c = 3, seed_type s = 0)
    : a_(a)
    , c_(c)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    assert(c > 0);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(a_, c_); }

protected:
  return_type do_generation(const value_type a, const value_type c) const
  {
    if (c > final_type(1) && a < final_type(1))
      return sibuya_rejection_impl(a, c);

    if (a > c + final_type(1) && a > final_type(2))
      return joint_rejection_impl(a, c);

    if (a < final_type(0.125) && c > final_type(0.25))
      return sibuya_rejection_1979_impl(a, c);

    return simple_rejection_impl(a, c);
  }

private:
  return_type sibuya_rejection_impl(const value_type a,
                                    const value_type c) const
  {
    for (;;) {
      const final_type x =
        final_type(1) + GHgB3_type::do_generation(
                          final_type(1), a + final_type(1), c - final_type(1));
      const final_type u = e_();

      if (x * u < final_type(1)) {
        return x;
      }
    }
  }

  return_type simple_rejection_impl(const value_type a,
                                    const value_type c) const
  {
    for (;;) {
      const final_type x =
        final_type(1) + GHgB3_type::do_generation(a, final_type(1), c);
      const final_type u = e_();
      final_type xu = x * u;
      xu = a > final_type(1) ? a * xu : xu;

      if (xu + final_type(1) < a + x) {
        return x;
      }
    }
  }

  return_type joint_rejection_impl(const value_type a, const value_type c) const
  {
    const final_type t = (a - final_type(1)) / c;
    const final_type u = std::ceil(std::log(t) / std::log(final_type(2)));
    const final_type n =
      std::pow(final_type(2), u + final_type(1)) - final_type(1);
    const final_type delta = vg::special_function::digamma()(a + c) -
                             vg::special_function::digamma()(c);
    const final_type w = (u + final_type(1)) / delta;
    const final_type z = (a + n) / (c * delta * (n + final_type(1)));
    const final_type threshold = w / (w + z);

    for (;;) {
      const final_type U = e_();

      if (U < threshold) {
        const final_type y = std::floor(u * e_());
        const final_type py = std::pow(final_type(2), y);
        const final_type x = py * (final_type(1) + e_());
        const final_type px =
          std::exp(std::lgamma(a + x) + std::lgamma(a + c) - std::lgamma(a) -
                   std::lgamma(a + c + x)) /
          x / delta;
        const final_type v = e_();

        if (px > v * delta * std::pow(final_type(2), y)) {
          return x;
        }
      }

      else {
        const final_type y = GHgB3_type::do_generation(a, final_type(1), c);
        const final_type x = y + final_type(1);
        const final_type v = e_();

        if (x > n && (a + x - final_type(1)) > v * z * c * delta * x) {
          return x;
        }
      }
    }
  }

  return_type special_method_rejection_impl(const value_type a,
                                            const value_type c) const
  {
    const final_type delta =
      special_function::digamma()(a + c) - special_function::digamma()(c);
    const final_type d =
      std::max(a / delta / c,
               std::exp((final_type(6) * a + final_type(7)) * c /
                          final_type(12) / (final_type(1) + a) +
                        std::lgamma(a + c) - std::lgamma(c)) /
                 delta);

    for (;;) {
      const final_type u = e_();
      const final_type v = e_();
      const final_type y = std::pow((final_type(1) - u), -final_type(1) / c);
      const final_type x = std::ceil(y);
      const final_type w =
        v * std::pow(final_type(2) / y, c + final_type(1)) * d;
      const final_type px = std::exp(std::lgamma(a + x) + std::lgamma(a + c) -
                                     std::lgamma(a) - std::lgamma(a + c + x)) /
                            x / delta;

      if (px > w) {
        return x;
      }
    }
  }

  return_type sibuya_rejection_1979_impl(const value_type a,
                                         const value_type c) const
  {
    const final_type delta =
      special_function::digamma()(a + c) - special_function::digamma()(c);
    final_type p = a / (c - final_type(1)) / delta;
    final_type s = p;
    final_type x = final_type(1);

    while (s < e_()) {
      p *= x * (a + x);
      p /= (x + final_type(1)) * (a + c + x);
      s += p;
      ++x;
    }

    return x;
  }
};

template<typename Return_Type, typename Engine>
struct erlang : private gamma<Return_Type, Engine>
{
  typedef gamma<Return_Type, Engine> gamma_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;
  typedef typename engine_type::size_type size_type;

  return_type a_;
  return_type n_;
  engine_type& e_;

  explicit erlang(const return_type a = return_type(1),
                  const return_type n = return_type(10),
                  const seed_type sd = 0)
    : a_(a)
    , n_(n)
    , e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_, n_); }

protected:
  return_type do_generation(const final_type A, const final_type N) const
  {
    return erlang_direct_impl(a_, n_);
  }

private:
  return_type erlang_direct_impl(const final_type A, const final_type N) const
  {
    const final_type ans = gamma_type::do_generation(N, A);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct exponential
{
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type lambda_;
  engine_type& e_;

  explicit exponential(const return_type lambda = 1, const seed_type sd = 0)
    : lambda_(lambda)
    , e_(singleton<engine_type>::instance())
  {
    assert(lambda_ > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(lambda_); }

protected:
  return_type do_generation(const final_type Lambda) const
  {
    return direct_exponential_impl(Lambda);
  }

private:
  return_type direct_exponential_impl(const final_type Lambda) const
  {
    const final_type u = e_();
    const final_type ans = -std::log(u) / Lambda;
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct laplace
{
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef Engine engine_type;

  return_type mu_;
  return_type b_;
  engine_type& e_;

  explicit laplace(const return_type mu = 1,
                   const return_type b = 1,
                   const seed_type sd = 0)
    : mu_(mu)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(mu_, b_); }

protected:
  return_type do_generation(const return_type mu, const return_type b) const
  {
    return direct_invertion_method(mu, b);
  }

private:
  return_type direct_invertion_method(const return_type mu,
                                      const return_type b) const
  {
    for (;;) {
      const final_type u = e_() - final_type(0.5);

      if (final_type(0) == u) {
        continue;
      }

      const final_type ans = u > final_type(0) ? mu - b * std::log(1 - u - u)
                                               : mu + b * std::log(1 + u + u);
      return ans;
    }
  }
};

template<typename Return_Type, typename Engine>
struct exponential_power
  : private gamma<Return_Type, Engine>
  , private laplace<Return_Type, Engine>
  , private proxy<normal<Return_Type, Engine>>
{
  typedef gamma<Return_Type, Engine> gamm_type;
  typedef laplace<Return_Type, Engine> laplace_type;
  typedef proxy<normal<Return_Type, Engine>> normal_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef return_type value_type;
  typedef typename engine_type::size_type size_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  value_type a_;
  value_type b_;
  engine_type& e_;

  explicit exponential_power(const value_type a = value_type(1),
                             const value_type b = value_type(1),
                             const seed_type sd = 0)
    : a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_, b_); }

protected:
  return_type do_generation(const final_type A, const final_type B) const
  {
    if (final_type(1) == B) {
      return laplace_impl(A);
    }

    if (B > final_type(1) && B < final_type(2)) {
      return laplace_reject_impl(A, B);
    }

    if (final_type(2) == B) {
      return gaussian_impl(A);
    }

    if (B > final_type(2) && B <= final_type(4)) {
      return gaussian_reject_impl(A, B);
    }

    return gamma_impl(A, B);
  }

private:
  return_type laplace_impl(const final_type A) const
  {
    return laplace_type::do_generation(final_type(), A);
  }

  return_type gaussian_impl(const final_type A) const
  {
    return normal_type::do_generation() * A /
           final_type(1.414213562373095048801688724209698);
  }

  return_type laplace_reject_impl(const final_type A, const final_type B) const
  {
    const final_type b = std::pow(final_type(1) / B, final_type(1) / B);

    for (;;) {
      const final_type x = laplace_type::do_generation(final_type(), b);
      final_type y = e_();

      while (final_type(0) == y) {
        y = e_();
      }

      const final_type z = std::fabs(x) / b - final_type(1) +
                           final_type(1) / B - std::pow(std::fabs(x), B);

      if (std::log(y) > z) {
        return A * x;
      }
    }
  }

  return_type gaussian_reject_impl(const final_type A, const final_type B) const
  {
    const final_type b = std::pow(final_type(1) / B, final_type(1) / B);

    for (;;) {
      const final_type x = normal_type::do_generation() * b;
      final_type y = e_();

      while (final_type(0) == y) {
        y = e_();
      }

      const final_type z = x * x / (final_type(2) * b * b) + final_type(1) / B -
                           final_type(0.5) - std::pow(std::fabs(x), B);

      if (std::log(y) > z) {
        return A * x;
      }
    }
  }

  return_type gamma_impl(const final_type A, const final_type B) const
  {
    const final_type x = e_();
    const final_type y =
      gamm_type::do_generation(final_type(1) / B, final_type(1));
    const final_type z = A * std::pow(y, final_type(1) / B);
    return x > final_type(0.5) ? z : -z;
  }
};

template<typename Return_Type, typename Engine>
struct extreme_value
{
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type mu_;
  return_type sigma_;
  return_type xi_;
  engine_type& e_;

  explicit extreme_value(const return_type mu = 0,
                         const return_type sigma = 1,
                         const return_type xi = 0,
                         const seed_type sd = 0)
    : mu_(mu)
    , sigma_(sigma)
    , xi_(xi)
    , e_(singleton<engine_type>::instance())
  {
    assert(sigma_ > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(mu_, sigma_, xi_); }

protected:
  return_type do_generation(const final_type Mu,
                            const final_type Sigma,
                            const final_type Xi) const
  {
    return direct_reverse_impl(Mu, Sigma, Xi);
  }

private:
  return_type direct_reverse_impl(const final_type Mu,
                                  const final_type Sigma,
                                  const final_type Xi) const
  {
    const final_type u = e_();
    const final_type ans =
      Mu +
      (std::exp(-Xi * std::log(-std::log(u))) - final_type(1)) * Sigma / Xi;
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct f : private gamma<Return_Type, Engine>
{
  typedef gamma<Return_Type, Engine> gamma_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef typename Engine::size_type size_type;
  typedef Engine engine_type;

  final_type mu1_;
  final_type mu2_;
  engine_type& e_;

  explicit f(const return_type mu1 = 2,
             const return_type mu2 = 2,
             const seed_type sd = 0)
    : mu1_(mu1)
    , mu2_(mu2)
    , e_(singleton<engine_type>::instance())
  {
    assert(mu1 > 0);
    assert(mu2 > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(mu1_, mu2_); }

protected:
  return_type do_generation(const return_type mu1, const return_type mu2) const
  {
    return direct_impl(mu1, mu2);
  }

private:
  return_type direct_impl(const return_type mu1, const return_type mu2) const
  {
    const final_type y1 =
      gamma_type::do_generation(mu1 / final_type(2), final_type(2));
    const final_type y2 =
      gamma_type::do_generation(mu2 / final_type(2), final_type(2));
    const final_type ans = y1 * mu2 / (y2 * mu1);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct factorial : private generalized_hypergeometric_b3<Return_Type, Engine>
{
  typedef generalized_hypergeometric_b3<Return_Type, Engine> GHgB3_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type k_;
  value_type r_;
  engine_type& e_;

  explicit factorial(value_type k = 3, value_type r = 3, seed_type s = 0)
    : k_(k)
    , r_(r)
    , e_(singleton<engine_type>::instance())
  {
    assert(k >= 2);
    assert(r >= k);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(k_, r_); }

protected:
  return_type do_generation(const value_type k, const value_type r) const
  {
    return direct_impl(k, r);
  }

private:
  return_type direct_impl(const value_type k, const value_type r) const
  {
    const final_type r_1 = r - final_type(1);
    const final_type ans =
      GHgB3_type::do_generation(final_type(1), k - r_1, r_1);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct gaussian : private normal<Return_Type, Engine>
{
  typedef normal<Return_Type, Engine> normal_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename normal_type::final_type final_type;
  typedef typename normal_type::seed_type seed_type;

  return_type mean_;
  return_type variance_;
  engine_type& e_;

  explicit gaussian(const return_type mean = 0,
                    const return_type variance = 1,
                    const seed_type sd = 0)
    : mean_(mean)
    , variance_(variance)
    , e_(singleton<engine_type>::instance())
  {
    assert(variance > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(variance_, mean_); }

protected:
  return_type do_generation(const final_type Variance,
                            const final_type Mean) const
  {
    return gaussian_direct_impl(Variance, Mean);
  }

private:
  return_type gaussian_direct_impl(const final_type Variance,
                                   const final_type Mean) const
  {
    const final_type ans = normal_type::do_generation() * Variance + Mean;
    return static_cast<return_type>(ans);
  }
};

template<typename Return_Type, typename Engine>
struct gaussian_tail : private normal<Return_Type, Engine>
{
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef normal<return_type, engine_type> normal_type;

  typedef typename normal_type::final_type final_type;
  typedef typename normal_type::seed_type seed_type;

  return_type a_;
  return_type variance_;
  engine_type& e_;

  explicit gaussian_tail(const return_type a = 0,
                         const return_type variance = 1,
                         const seed_type sd = 0)
    : a_(a)
    , variance_(variance)
    , e_(singleton<engine_type>::instance())
  {
    assert(variance > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_, variance_); }

protected:
  return_type do_generation(const final_type A, const final_type Variance) const
  {
    if (Variance > A) {
      return gaussian_tail_direct_impl(A, Variance);
    }

    return rectangle_wedge_tail_method(A, Variance);
  }

private:
  return_type rectangle_wedge_tail_method(const final_type A,
                                          const final_type Variance) const
  {
    const final_type s = A / Variance;

    for (;;) {
      const final_type u = e_();
      const final_type v = e_();

      if (final_type(0) == u || final_type(0) == v) {
        continue;
      }

      const final_type x = std::sqrt(s * s - std::log(v));

      if (s >= x * u) {
        return x * Variance;
      }
    }
  }

  return_type gaussian_tail_direct_impl(const final_type A,
                                        const final_type Variance) const
  {
    const final_type s = A / Variance;

    for (;;) {
      const final_type ans = normal<Return_Type, Engine>::do_generation();

      if (ans >= s) {
        return ans;
      }
    }
  }
};

template<typename Return_Type, typename Engine>
struct generalized_waring
  : private generalized_hypergeometric_b3<Return_Type, Engine>
{
  typedef generalized_hypergeometric_b3<Return_Type, Engine> GHgB3_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type a_;
  value_type b_;
  value_type c_;
  engine_type& e_;

  explicit generalized_waring(value_type a = 1,
                              value_type b = 1,
                              value_type c = 1,
                              seed_type s = 0)
    : a_(a)
    , b_(b)
    , c_(c)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    assert(b > 0);
    assert(c > 0);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(a_, b_, c_); }

protected:
  return_type do_generation(const value_type a,
                            const value_type b,
                            const value_type c) const
  {
    return direct_impl(a, b, c);
  }

private:
  return_type direct_impl(const value_type a,
                          const value_type b,
                          const value_type c) const
  {
    const final_type ans = GHgB3_type::do_generation(a, b, c);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct geometric
{
  typedef Engine engine_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;

  final_type p_;
  engine_type& e_;

  explicit geometric(final_type p = final_type(0.5),
                     const seed_type s = seed_type(0))
    : p_(p)
    , e_(singleton<engine_type>::instance())
  {
    assert(p > final_type(0));
    assert(p < final_type(1));
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(p_); }

protected:
  return_type do_generation(const final_type P) const
  {
    return polar_method(P);
  }

private:
  return_type coin_flip_method(const final_type P) const
  {
    value_type ans = 1;

    while (e_() > P) {
      ++ans;
    }

    return ans;
  }

  return_type polar_method(const final_type P) const
  {
    const final_type u = e_();
    const final_type n = std::ceil(log(u) / log(final_type(1) - P));
    return n;
  }
};

template<typename Return_Type, typename Engine>
struct grassia : private gamma<Return_Type, Engine>
{
  typedef gamma<Return_Type, Engine> gamma_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef return_type value_type;
  typedef typename engine_type::size_type size_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  value_type a_;
  value_type b_;
  engine_type& e_;

  explicit grassia(const value_type a = value_type(1),
                   const value_type b = value_type(1),
                   const seed_type sd = 0)
    : a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    assert(b > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_, b_); }

protected:
  return_type do_generation(const final_type A, const final_type B) const
  {
    return direct_impl_method(A, B);
  }

private:
  return_type direct_impl_method(const final_type A, const final_type B) const
  {
    const final_type x = gamma_type::do_generation(A, B);
    const final_type ans = std::exp(-x);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct gumbel_1
{
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef typename Engine::size_type size_type;
  typedef Engine engine_type;

  final_type a_;
  final_type b_;
  engine_type& e_;

  explicit gumbel_1(const return_type a = 1,
                    const return_type b = 1,
                    const seed_type sd = 0)
    : a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    assert(b > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_, b_); }

protected:
  return_type do_generation(const return_type a, const return_type b) const
  {
    return direct_impl(a, b);
  }

private:
  return_type direct_impl(const return_type a, const return_type b) const
  {
    final_type x = e_();

    while (final_type(0) == x) {
      x = e_();
    }

    const final_type ans = (std::log(b) - std::log(-std::log(x))) / a;
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct gumbel_2
{
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef typename Engine::size_type size_type;
  typedef Engine engine_type;

  final_type a_;
  final_type b_;
  engine_type& e_;

  explicit gumbel_2(const return_type a = 1,
                    const return_type b = 1,
                    const seed_type sd = 0)
    : a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    assert(b > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_, b_); }

protected:
  return_type do_generation(const return_type a, const return_type b) const
  {
    return direct_impl(a, b);
  }

private:
  return_type direct_impl(const return_type a, const return_type b) const
  {
    final_type x = e_();

    while (final_type(0) == x) {
      x = e_();
    }

    const final_type ans = std::pow(-b / std::log(x), final_type(1) / a);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct hyperbolic_secant
{
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef Engine engine_type;

  engine_type& e_;

  explicit hyperbolic_secant(const seed_type sd = 0)
    : e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(); }

protected:
  return_type do_generation() const { return direct_impl_method(); }

private:
  return_type direct_impl_method() const
  {
    const final_type u = e_();
    const final_type pi_2 = 3.1415926535897932384626433L / 2.0L;
    const final_type ans = std::log(std::tan(u * pi_2));
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct hypergeometric
{
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  size_type n1_;
  size_type n2_;
  size_type k_;
  engine_type& e_;

  explicit hypergeometric(size_type n1 = 1,
                          size_type n2 = 0,
                          size_type k = 1,
                          seed_type s = 0)
    : n1_(n1)
    , n2_(n2)
    , k_(k)
    , e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(n1_, n2_, k_); }

protected:
  return_type do_generation(const size_type n1,
                            const size_type n2,
                            const size_type k) const
  {
    const size_type n = n1 + n2;

    if (k >= n) {
      return static_cast<return_type>(n1);
    }

    if (0 == n1) {
      return static_cast<return_type>(0);
    }

    if (0 == n2) {
      return static_cast<return_type>(k);
    }

    if (k < (n >> 1)) {
      return direct_impl(n1, n2, k);
    }

    return static_cast<return_type>(n1 - direct_impl(n1, n2, n - k));
  }

private:
  return_type direct_impl(const size_type n1,
                          const size_type n2,
                          const size_type k) const
  {
    size_type left_all = n1 + n2;
    size_type left_good = n1;
    size_type ans = 0;

    for (size_type i = 0; i < k; ++i) {
      if (e_() * final_type(left_all--) < final_type(left_good)) {
        ++ans;
        --left_good;

        if (ans == n1) {
          break;
        }
      }
    }

    return static_cast<return_type>(ans);
  }
};

template<typename Return_Type, typename Engine>
struct inverse_gaussian : private normal<Return_Type, Engine>
{
  typedef normal<Return_Type, Engine> normal_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename normal_type::final_type final_type;
  typedef typename normal_type::seed_type seed_type;

  return_type mu_;
  return_type lambda_;
  engine_type& e_;

  explicit inverse_gaussian(const return_type mu = 1,
                            const return_type lambda = 1,
                            const seed_type sd = 0)
    : mu_(mu)
    , lambda_(lambda)
    , e_(singleton<engine_type>::instance())
  {
    assert(mu > 0);
    assert(lambda > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(lambda_, mu_); }

protected:
  return_type do_generation(const final_type Lambda, const final_type Mu) const
  {
    return michael_schucany_haas_impl(Lambda, Mu);
  }

private:
  return_type michael_schucany_haas_impl(const final_type Lambda,
                                         const final_type Mu) const
  {
    const final_type N = normal_type::do_generation();
    const final_type Y = N * N;
    const final_type MY = Mu * Y;
    const final_type X =
      Mu + (MY - std::sqrt(MY * (Lambda * final_type(4) + MY))) * Mu /
             (Lambda + Lambda);
    const final_type U = e_();
    const final_type ans = (Mu >= (Mu + X) * U) ? X : (Mu * Mu / X);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct inverse_polya_eggenberger
  : private generalized_hypergeometric_b3<Return_Type, Engine>
{
  typedef generalized_hypergeometric_b3<Return_Type, Engine> GHgB3_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type a_;
  value_type b_;
  value_type c_;
  engine_type& e_;

  explicit inverse_polya_eggenberger(value_type a = 1,
                                     value_type b = 1,
                                     value_type c = 1,
                                     seed_type s = 0)
    : a_(a)
    , b_(b)
    , c_(c)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    assert(b > 0);
    assert(c > 0);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(a_, b_, c_); }

protected:
  return_type do_generation(const value_type a,
                            const value_type b,
                            const value_type c) const
  {
    return direct_impl(a, b, c);
  }

private:
  return_type direct_impl(const value_type a,
                          const value_type b,
                          const value_type c) const
  {
    const final_type ans = GHgB3_type::do_generation(a, b, c);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct lambda
{
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef Engine engine_type;

  final_type lambda1_;
  final_type lambda2_;
  final_type lambda3_;
  final_type lambda4_;
  engine_type& e_;

  explicit lambda(const return_type lambda1 = 1,
                  const return_type lambda2 = 1,
                  const return_type lambda3 = 1,
                  const return_type lambda4 = 1,
                  const seed_type sd = 0)
    : lambda1_(lambda1)
    , lambda2_(lambda2)
    , lambda3_(lambda3)
    , lambda4_(lambda4)
    , e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const
  {
    return do_generation(lambda1_, lambda2_, lambda3_, lambda4_);
  }

protected:
  return_type do_generation(const final_type lambda1,
                            const final_type lambda2,
                            const final_type lambda3,
                            const final_type lambda4) const
  {
    return direct_impl(lambda1, lambda2, lambda3, lambda4);
  }

private:
  return_type direct_impl(const final_type lambda1,
                          const final_type lambda2,
                          const final_type lambda3,
                          const final_type lambda4) const
  {
    const final_type U1 = e_();
    const final_type U2 = e_();
    const final_type ans =
      lambda1 + (std::pow(U1, lambda3) - std::pow(U2, lambda4)) / lambda2;
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct levy : private exponential<Return_Type, Engine>
{
  typedef exponential<Return_Type, Engine> exponential_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type c_;
  return_type alpha_;
  engine_type& e_;

  explicit levy(const return_type c = 1,
                const return_type alpha = 1,
                const seed_type sd = 0)
    : c_(c)
    , alpha_(alpha)
    , e_(singleton<engine_type>::instance())
  {
    assert(c > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(c_, alpha_); }

protected:
  return_type do_generation(const final_type c, const final_type alpha) const
  {
    if (final_type(1) == alpha) {
      return cauchy_impl(c);
    }

    if (final_type(2) == alpha) {
      return gaussian_impl(c);
    }

    return direct_impl(c, alpha);
  }

private:
  return_type cauchy_impl(const final_type c) const
  {
    final_type u = e_();

    while (final_type(0) == u || final_type(1) == u) {
      u = e_();
    }

    return c * std::tan((u - final_type(0.5)) * 3.1415926535897932384626433);
  }

  return_type gaussian_impl(const final_type c) const
  {
    const final_type u = (e_() - final_type(0.5)) * 3.1415926535897932384626433;
    final_type v = exponential_type::do_generation(final_type(1));

    while (final_type(0) == v) {
      v = exponential_type::do_generation(final_type(1));
    }

    const final_type ans = c * std::sin(u) * std::sqrt(v);
    return ans + ans;
  }

  return_type direct_impl(const final_type c, const final_type alpha) const
  {
    const final_type u = (e_() - final_type(0.5)) * 3.1415926535897932384626433;
    final_type v = exponential_type::do_generation(final_type(1));

    while (final_type(0) == v) {
      v = exponential_type::do_generation(final_type(1));
    }

    const final_type r_alpha = final_type(1) / alpha;
    const final_type u_alpha = u * alpha;
    const final_type ans =
      c * std::pow(std::cos(u - u_alpha) / v, r_alpha - final_type(1)) *
      std::sin(u_alpha) * std::pow(std::cos(u), -r_alpha);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct logarithmic
{
  typedef Engine engine_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;

  final_type p_;
  Engine& e_;

  explicit logarithmic(final_type p = final_type(0.5),
                       const seed_type s = seed_type(0))
    : p_(p)
    , e_(singleton<engine_type>::instance())
  {
    assert(p_ > final_type(0));
    assert(p_ < final_type(1));
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(p_); }

protected:
  return_type do_generation(const final_type P) const { return direct_impl(P); }

private:
  return_type direct_impl(const final_type P) const
  {
    final_type v = e_();

    while (final_type(0) == v) {
      v = e_();
    }

    final_type u = e_();

    while (final_type(0) == u) {
      u = e_();
    }

    const final_type c = std::log(final_type(1) - P);
    const final_type q = final_type(1) - std::exp(c * u);

    if (v >= P) {
      return 1;
    }

    if (q * q > v) {
      return final_type(1) + std::log(v) / std::log(q);
    }

    if (q >= v) {
      return 2;
    }

    return 1;
  }
};

template<typename Return_Type, typename Engine>
struct logistic : private beta<Return_Type, Engine>
{
  typedef beta<Return_Type, Engine> beta_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type a_;
  return_type b_;
  engine_type e_;

  explicit logistic(const return_type a = 1,
                    const return_type b = 1,
                    const seed_type sd = 0)
    : a_(a)
    , b_(b)
    , e_(sd)
  {
    assert(a > 0);
    assert(b > 0);
  }

  return_type operator()() const { return do_generation(a_, b_); }

protected:
  return_type do_generation(const final_type A, const final_type B) const
  {
    return beta_impl(A, B);
  }

private:
  return_type beta_impl(const final_type A, const final_type B) const
  {
    const final_type X = beta_type::do_generation(A, B);
    const final_type ans = std::log(X / (final_type(1) - X));
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct lognormal
{
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef typename Engine::size_type size_type;
  typedef Engine engine_type;

  final_type zeta_;
  final_type sigma_;
  engine_type& e_;

  explicit lognormal(const return_type zeta = 1,
                     const return_type sigma = 1,
                     const seed_type sd = 0)
    : zeta_(zeta)
    , sigma_(sigma)
    , e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(zeta_, sigma_); }

protected:
  return_type do_generation(const return_type zeta,
                            const return_type sigma) const
  {
    return direct_impl(zeta, sigma);
  }

private:
  return_type direct_impl(const return_type zeta, const return_type sigma) const
  {
    for (;;) {
      const final_type u = e_() * final_type(2) - final_type(1);
      const final_type v = e_() * final_type(2) - final_type(1);
      const final_type r = u * u + v * v;

      if (r <= final_type(1) && r != final_type(0)) {
        const final_type normal =
          u * std::sqrt(final_type(-2) * std::log(r) / r);
        const final_type ans = std::exp(sigma * normal + zeta);
        return ans;
      }
    }
  }
};

template<typename Return_Type, typename Engine>
struct mizutani : private generalized_hypergeometric_b3<Return_Type, Engine>
{
  typedef generalized_hypergeometric_b3<Return_Type, Engine> GHgB3_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type a_;
  engine_type& e_;

  explicit mizutani(value_type a = 1, seed_type s = 0)
    : a_(a)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(a_); }

protected:
  return_type do_generation(const value_type a) const { return direct_impl(a); }

private:
  return_type direct_impl(const value_type a) const
  {
    const final_type ans =
      GHgB3_type::do_generation(a, final_type(1), final_type(1));
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct negative_binomial
  : private proxy<gamma<typename Engine::final_type, Engine>, 1>
  , private proxy<poisson<typename Engine::final_type, Engine>, 2>
{
  typedef proxy<gamma<typename Engine::final_type, Engine>, 1> gamma_type;
  typedef proxy<poisson<typename Engine::final_type, Engine>, 2> poisson_type;

  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  size_type n_;
  final_type p_;
  engine_type& e_;

  explicit negative_binomial(size_type n = size_type(1),
                             final_type p = final_type(0.5),
                             const seed_type s = seed_type(0))
    : n_(n)
    , p_(p)
    , e_(singleton<engine_type>::instance())
  {
    assert(n != size_type(0));
    assert(p > final_type(0));
    assert(p < final_type(1));
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(n_, p_); }

protected:
  return_type do_generation(const size_type N, const final_type P) const
  {
    return direct_impl(N, P);
  }

private:
  return_type direct_impl(const size_type N, const final_type P) const
  {
    const final_type X = gamma_type::do_generation(N);
    const final_type ans = poisson_type::do_generation(X / P - X);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct negative_binomial_beta
  : private generalized_hypergeometric_b3<Return_Type, Engine>
{
  typedef generalized_hypergeometric_b3<Return_Type, Engine> GHgB3_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type a_;
  value_type b_;
  value_type c_;
  engine_type& e_;

  explicit negative_binomial_beta(value_type a = 1,
                                  value_type b = 1,
                                  value_type c = 1,
                                  seed_type s = 0)
    : a_(a)
    , b_(b)
    , c_(c)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    assert(b > 0);
    assert(c > 0);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(a_, b_, c_); }

protected:
  return_type do_generation(const value_type a,
                            const value_type b,
                            const value_type c) const
  {
    return direct_impl(a, b, c);
  }

private:
  return_type direct_impl(const value_type a,
                          const value_type b,
                          const value_type c) const
  {
    const final_type ans = GHgB3_type::do_generation(a, b, c);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct pareto
{
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type a_;
  return_type b_;
  engine_type& e_;

  explicit pareto(const return_type a = 1,
                  const return_type b = 2,
                  const seed_type sd = 0)
    : a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    assert(a_ > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_, b_); }

protected:
  return_type do_generation(const return_type A, const return_type B) const
  {
    return direct_impl(A, B);
  }

private:
  return_type direct_impl(const return_type A, const return_type B) const
  {
    const final_type u = e_();
    const final_type tmp = std::pow(u, final_type(1) / A);
    const final_type ans = B / tmp;
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct pascal : private negative_binomial<Return_Type, Engine>
{
  typedef negative_binomial<Return_Type, Engine> negative_binomial_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  size_type n_;
  final_type p_;
  engine_type& e_;

  explicit pascal(size_type n = size_type(1),
                  final_type p = final_type(0.5),
                  const seed_type s = seed_type(0))
    : n_(n)
    , p_(p)
    , e_(singleton<engine_type>::instance())
  {
    assert(n != size_type(0));
    assert(p > final_type(0));
    assert(p < final_type(1));
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(n_, p_); }

protected:
  return_type do_generation(const size_type N, const final_type P) const
  {
    return direct_impl(N, P);
  }

private:
  return_type direct_impl(const size_type N, const final_type P) const
  {
    const final_type ans = negative_binomial_type::do_generation(N, P);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct pearson
  : private proxy<gamma<typename Engine::final_type, Engine>, 1>
  , private proxy<exponential<typename Engine::final_type, Engine>, 2>
  , private proxy<normal<typename Engine::final_type, Engine>, 3>
  , private proxy<beta<typename Engine::final_type, Engine>, 4>
{
  typedef proxy<gamma<typename Engine::final_type, Engine>, 1> gamma_type;
  typedef proxy<exponential<typename Engine::final_type, Engine>, 2>
    exponential_type;
  typedef proxy<normal<typename Engine::final_type, Engine>, 3> normal_type;
  typedef proxy<beta<typename Engine::final_type, Engine>, 4> beta_type;

  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  size_type n_;
  final_type a_;
  final_type b_;
  final_type c_;
  final_type d_;
  engine_type& e_;

  explicit pearson(size_type n = size_type(1),
                   final_type a = final_type(1),
                   final_type b = final_type(1),
                   final_type c = final_type(1),
                   final_type d = final_type(1),
                   const seed_type s = seed_type(0))
    : n_(n)
    , a_(a)
    , b_(b)
    , c_(c)
    , d_(d)
    , e_(singleton<engine_type>::instance())
  {
    assert(n > 0);
    assert(n < 13);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(n_, a_, b_, c_, d_); }

protected:
  return_type do_generation(const size_type N,
                            const final_type A,
                            const final_type B,
                            const final_type C,
                            const final_type D) const
  {
    return direct_impl(N, A, B, C, D);
  }

private:
  return_type direct_impl(const size_type N,
                          const final_type A,
                          const final_type B,
                          const final_type C,
                          const final_type D) const
  {
    typedef std::function<final_type(
      final_type, final_type, final_type, final_type)>
      function_type;
    static const function_type impl_function_list[12] = {

      [](final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(a > final_type(0));
        assert(b > final_type(-1));
        assert(c > final_type(0));
        assert(d > final_type(-1));
        const final_type X = gamma_type::do_generation(b + final_type(1));
        const final_type Y = gamma_type::do_generation(d + final_type(1));
        const final_type ans = (a + c) * X / (X + Y) - a;
        return ans;
      },

      [](final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(a > final_type(0));
        assert(b > final_type(-1));
        const final_type X = gamma_type::do_generation(b + final_type(1));
        const final_type Y = gamma_type::do_generation(b + final_type(1));
        const final_type ans = a * (X - Y) / (X - Y);
        return ans;
      },

      [](final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(a * b > final_type(-1));
        assert(b > 0);
        const final_type X = gamma_type::do_generation(a * b + final_type(1));
        const final_type ans = X / b - a;
        return ans;
      },

      [](final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(a > 0);
        assert(b > final_type(0.5));
        const final_type X = gamma_type::do_generation(a);
        const final_type Y = gamma_type::do_generation(b);
        const final_type ans = X / Y;
        return ans;
      },

      [](final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(b > final_type(1));
        assert(c > 0);
        const final_type X = gamma_type::do_generation(b - final_type(1));
        const final_type ans = final_type(1) / (c * X);
        return ans;
      },

      [](final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(c > b + final_type(1));
        assert(c > 0);
        assert(a > 0);
        const final_type X = gamma_type::do_generation(c - b - final_type(1));
        const final_type Y = gamma_type::do_generation(b + final_type(1));
        const final_type ans = a + a * Y / X;
        return ans;
      },

      [](final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(b > final_type(0.5));
        assert(a > 0);
        const final_type N = normal_type::do_generation();
        const final_type X = gamma_type::do_generation(b - final_type(0.5));
        const final_type ans = N / std::sqrt(X / final_type(2));
        return ans;
      },

      [this](
        final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(b >= 0);
        assert(b <= final_type(1));
        assert(a > 0);
        const final_type U = ((*this).e_)();
        const final_type ans =
          a *
          (std::pow(U, -final_type(1) / (b - final_type(1))) - final_type(1));
        return ans;
      },

      [this](
        final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(b > 0);
        assert(a > 0);
        const final_type U = ((*this).e_)();
        const final_type ans =
          a *
          (std::pow(U, final_type(1) / (b + final_type(1))) - final_type(1));
        return ans;
      },

      [](final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(a > 0);
        const final_type E = exponential_type::do_generation(final_type(1));
        const final_type ans = a * E;
        return ans;
      },

      [this](
        final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(a > 0);
        assert(b > final_type(1));
        const final_type U = ((*this).e_)();
        const final_type ans =
          a * std::pow(U, -final_type(1) / (b - final_type(1)));
        return ans;
      },

      [](final_type a, final_type b, final_type c, final_type d) -> final_type {
        assert(a > b);
        assert(b > 0);
        assert(c >= 0);
        assert(c < final_type(1));
        const final_type X =
          beta_type::do_generation(c + final_type(1), final_type(1) - c);
        const final_type ans = (a + b) * X - a;
        return ans;
      }
    };
    return impl_function_list[N - 1](A, B, C, D);
  }
};

template<typename Return_Type, typename Engine>
struct zipf
{
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type a_;
  engine_type& e_;

  explicit zipf(const return_type a = 2, const seed_type sd = 0)
    : a_(a)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 1);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_); }

protected:
  return_type do_generation(const final_type A) const
  {
    return rejection_method(A);
  }

private:
  return_type rejection_method(const final_type A) const
  {
    const final_type a_1 = A - final_type(1);
    const final_type b = std::exp2(a_1);
    const final_type b_1 = b - final_type(1);

    for (;;) {
      const final_type u = e_();
      const final_type v = e_();
      const final_type x = std::pow(u, -final_type(1) / a_1);
      const final_type X = std::ceil(x);
      const final_type T = std::pow((X + final_type(1)) / X, a_1);
      const final_type T_1 = T - final_type(1);
      const final_type lhs = v * X * T_1 / b_1;
      const final_type rhs = T / b;

      if (lhs <= rhs)
        return X;
    }

    assert(!"zipf: should never reach here!");
    return return_type();
  }
};

template<typename Return_Type, typename Engine>
struct planck
  : private gamma<Return_Type, Engine>
  , private zipf<Return_Type, Engine>
{
  typedef gamma<Return_Type, Engine> gamma_type;
  typedef zipf<Return_Type, Engine> zipf_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef return_type value_type;
  typedef typename engine_type::size_type size_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  value_type a_;
  value_type b_;
  engine_type& e_;

  explicit planck(const value_type a = value_type(1),
                  const value_type b = value_type(1),
                  const seed_type sd = 0)
    : a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    assert(b > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_, b_); }

protected:
  return_type do_generation(const final_type A, const final_type B) const
  {
    return direct_impl(A, B);
  }

private:
  return_type direct_impl(const final_type A, const final_type B) const
  {
    const final_type A_1 = A + final_type(1);
    const final_type G = gamma_type::do_generation(A_1);
    const final_type Z = zipf_type::do_generation(A_1);
    return G / B / Z;
  }
};

template<typename Return_Type, typename Engine>
struct polya : private negative_binomial<Return_Type, Engine>
{
  typedef negative_binomial<Return_Type, Engine> negative_binomial_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  size_type n_;
  final_type p_;
  engine_type& e_;

  explicit polya(size_type n = size_type(1),
                 final_type p = final_type(0.5),
                 const seed_type s = seed_type(0))
    : n_(n)
    , p_(p)
    , e_(singleton<engine_type>::instance())
  {
    assert(n != size_type(0));
    assert(p > final_type(0));
    assert(p < final_type(1));
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(n_, p_); }

protected:
  return_type do_generation(const size_type N, const final_type P) const
  {
    return direct_impl(N, P);
  }

private:
  return_type direct_impl(const size_type N, const final_type P) const
  {
    const final_type ans = negative_binomial_type::do_generation(N, P);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct polya_aeppli
  : private proxy<poisson<Return_Type, Engine>, 1>
  , private proxy<gamma<Return_Type, Engine>, 2>
{
  typedef proxy<poisson<Return_Type, Engine>, 1> poisson_type;
  typedef proxy<gamma<Return_Type, Engine>, 2> gamma_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename poisson_type::final_type final_type;
  typedef typename poisson_type::seed_type seed_type;

  return_type beta_;
  return_type theta_;
  return_type lambda_;
  engine_type& e_;

  explicit polya_aeppli(const return_type beta = 1,
                        const return_type theta = 1,
                        const return_type lambda = 1,
                        const seed_type sd = 0)
    : beta_(beta)
    , theta_(theta)
    , lambda_(lambda)
    , e_(singleton<engine_type>::instance())
  {
    assert(beta > 0);
    assert(theta > 0);
    assert(lambda > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const
  {
    return do_generation(beta_, theta_, lambda_);
  }

protected:
  return_type do_generation(const final_type Beta,
                            const final_type Theta,
                            const final_type Lambda) const
  {
    return polya_aeppli_direct_impl(Beta, Theta, Lambda);
  }

private:
  return_type polya_aeppli_direct_impl(const final_type Beta,
                                       const final_type Theta,
                                       const final_type Lambda) const
  {
    const final_type z =
      poisson_type::do_generation(Beta * Beta / (4.0 * Theta));
    const final_type g = gamma_type::do_generation(z + Lambda);
    const final_type ans = g / Theta;
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct rademacher : private bernoulli<Return_Type, Engine>
{
  typedef bernoulli<Return_Type, Engine> bernoulli_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename bernoulli_type::final_type final_type;
  typedef typename bernoulli_type::seed_type seed_type;

  engine_type& e_;

  explicit rademacher(const seed_type sd = 0)
    : e_(singleton<engine_type>::instance())
  {
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(); }

protected:
  return_type do_generation() const { return rademacher_direct_impl(); }

private:
  return_type rademacher_direct_impl() const
  {
    if (bernoulli_type::do_generation(final_type(0.5)))
      return 1;

    return -1;
  }
};

template<typename Return_Type, typename Engine>
struct rayleigh
{
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type delta_;
  engine_type& e_;

  explicit rayleigh(const return_type delta = 1, const seed_type sd = 0)
    : delta_(delta)
    , e_(singleton<engine_type>::instance())
  {
    assert(delta_ > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(delta_); }

protected:
  return_type do_generation(const return_type delta) const
  {
    return direct_impl(delta);
  }

private:
  return_type direct_impl(const return_type delta) const
  {
    const final_type u = e_();
    const final_type tmp1 = -std::log(u);
    const final_type tmp2 = std::sqrt(tmp1);
    const final_type ans = delta * tmp2;
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct rayleigh_tail
{
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type delta_;
  engine_type& e_;

  explicit rayleigh_tail(const return_type delta = 1, const seed_type sd = 0)
    : delta_(delta)
    , e_(singleton<engine_type>::instance())
  {
    assert(delta_ > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(delta_); }

protected:
  return_type do_generation(const return_type delta) const
  {
    return direct_impl(delta);
  }

private:
  return_type direct_impl(const return_type delta) const
  {
    const final_type u = e_();
    const final_type tmp1 = std::log(u);
    const final_type tmp2 = delta * delta - tmp1 - tmp1;
    const final_type ans = std::sqrt(tmp2);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct singh_maddala : private burr<Return_Type, Engine>
{
  typedef burr<Return_Type, Engine> burr_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef return_type value_type;
  typedef typename engine_type::size_type size_type;
  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  final_type c_;
  final_type k_;
  final_type r_;
  engine_type& e_;

  explicit singh_maddala(const final_type c = final_type(1),
                         const final_type k = final_type(1),
                         const final_type r = final_type(1),
                         const seed_type sd = 0)
    : c_(c)
    , k_(k)
    , r_(r)
    , e_(singleton<engine_type>::instance())
  {
    assert(c > 0);
    assert(k > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(c_, k_, r_); }

protected:
  final_type do_generation(const final_type C,
                           const final_type K,
                           const final_type R) const
  {
    return direct_impl(C, K, R);
  }

private:
  final_type direct_impl(const size_type N,
                         const final_type C,
                         const final_type K,
                         const final_type R) const
  {
    return burr_type::do_generation(12, C, K, R);
  }
};

template<typename Return_Type, typename Engine>
struct t
  : private proxy<normal<Return_Type, Engine>>
  , private chi_square<Return_Type, Engine>
  , private exponential<Return_Type, Engine>
{
  typedef normal<Return_Type, Engine> normal_type;
  typedef proxy<normal_type> proxy_normal_type;
  typedef chi_square<Return_Type, Engine> chi_square_type;
  typedef exponential<Return_Type, Engine> exponential_type;

  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef typename Engine::size_type size_type;
  typedef Engine engine_type;

  final_type mu_;
  engine_type& e_;

  explicit t(const return_type mu = 1, const seed_type sd = 0)
    : mu_(mu)
    , e_(singleton<engine_type>::instance())
  {
    assert(mu > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(mu_); }

protected:
  return_type do_generation(const return_type mu) const
  {
    if (mu <= final_type(2)) {
      return direct_impl(mu);
    }

    return rejection_method(mu);
  }

private:
  return_type direct_impl(const return_type mu) const
  {
    const final_type y1 = proxy_normal_type::do_generation();
    const final_type y2 = chi_square_type::do_generation(mu);
    const final_type ans = y1 / std::sqrt(y2 / mu);
    return ans;
  }

  return_type rejection_method(const return_type mu) const
  {
    for (;;) {
      const final_type y1 = proxy_normal_type::do_generation();
      const final_type y2 =
        exponential_type::do_generation(final_type(mu - 2) / final_type(2));
      const final_type y3 = y1 * y1 / final_type(mu - 2);

      if ((y3 < 1) && (-std::log(final_type(1) - y3) < (y2 + y3))) {
        const final_type fac1 = final_type(mu - 2) / final_type(mu);
        const final_type fac2 = fac1 - fac1 * y3;
        const final_type ans = y1 / std::sqrt(fac2);
        return ans;
      }
    }
  }
};

template<typename Return_Type, typename Engine>
struct teichroew
  : private proxy<normal<Return_Type, Engine>, 1>
  , private proxy<gamma<Return_Type, Engine>, 2>
{
  typedef proxy<normal<Return_Type, Engine>, 1> normal_type;
  typedef proxy<gamma<Return_Type, Engine>, 2> gamma_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename normal_type::final_type final_type;
  typedef typename normal_type::seed_type seed_type;

  return_type alpha_;
  engine_type& e_;

  explicit teichroew(const return_type alpha = 1, const seed_type sd = 0)
    : alpha_(alpha)
    , e_(singleton<engine_type>::instance())
  {
    assert(alpha > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(alpha_); }

protected:
  return_type do_generation(const final_type Alpha) const
  {
    return teichroew_direct_impl(Alpha);
  }

private:
  return_type teichroew_direct_impl(const final_type Alpha) const
  {
    const final_type n = normal_type::do_generation();
    const final_type g = gamma_type::do_generation(Alpha);
    const final_type ans = n * std::sqrt(g + g);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct triangular
{
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type delta_;
  engine_type& e_;

  explicit triangular(const return_type delta = 1, const seed_type sd = 0)
    : delta_(delta)
    , e_(singleton<engine_type>::instance())
  {
    assert(delta_ > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(delta_); }

protected:
  return_type do_generation(const return_type delta) const
  {
    return direct_impl(delta);
  }

private:
  return_type direct_impl(const return_type delta) const
  {
    const final_type u = e_();
    const final_type tmp = return_type(1) - std::log(u);
    const final_type ans = delta * tmp;
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct trigamma
  : private proxy<generalized_hypergeometric_b3<Return_Type, Engine>, 1>
  , private proxy<digamma<Return_Type, Engine>, 2>
{
  typedef proxy<generalized_hypergeometric_b3<Return_Type, Engine>> GHgB3_type;
  typedef proxy<digamma<Return_Type, Engine>> digamma_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type c_;
  engine_type& e_;

  explicit trigamma(value_type c = 3, seed_type s = 0)
    : c_(c)
    , e_(singleton<engine_type>::instance())
  {
    assert(c > 0);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(c_); }

protected:
  return_type do_generation(const value_type c) const
  {
    if (c > final_type(1.14))
      return large_c_rejection_impl(c);

    return small_c_rejection_impl(c);
  }

private:
  return_type large_c_rejection_impl(const value_type c) const
  {
    for (;;) {
      const final_type x =
        final_type(1) + GHgB3_type::do_generation(
                          final_type(1), final_type(1), c - final_type(1));
      const final_type u = e_();

      if (x * u < final_type(1)) {
        return x;
      }
    }
  }

  return_type small_c_rejection_impl(const value_type c) const
  {
    return digamma_type::do_generation(0, c);
  }
};

template<typename Return_Type, typename Engine>
struct uniform
{
  typedef Engine engine_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;

  value_type lower_;
  value_type upper_;
  engine_type& e_;

  explicit uniform(const value_type lower = value_type(0),
                   const value_type upper = value_type(1),
                   const seed_type s = seed_type(0))
    : lower_(lower)
    , upper_(upper)
    , e_(singleton<engine_type>::instance())
  {
    assert(upper > lower);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(lower_, upper_); }

protected:
  return_type do_generation(const value_type lower,
                            const value_type upper) const
  {
    return direct_impl(lower, upper);
  }

private:
  return_type direct_impl(const value_type lower, const value_type upper) const
  {
    const final_type lower_f = static_cast<final_type>(lower);
    const final_type upper_f = static_cast<final_type>(upper);
    const final_type ans = lower_f + e_() * (upper_f - lower_f);
    return static_cast<return_type>(ans);
  }
};

template<typename Return_Type, typename Engine>
struct von_mises
{
  typedef Engine engine_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;

  value_type a_;
  value_type k_;
  engine_type& e_;

  explicit von_mises(const value_type a = value_type(0),
                     const value_type k = value_type(1),
                     const seed_type s = seed_type(0))
    : a_(a)
    , k_(k)
    , e_(singleton<engine_type>::instance())
  {
    asset(k > 0);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(a_, k_); }

protected:
  return_type do_generation(const value_type a, const value_type k) const
  {
    return direct_impl(a, k);
  }

private:
  return_type direct_impl(const value_type a, const value_type k) const
  {
    const final_type r =
      final_type(1) + std::sqrt(final_type(1) + k * k * final_type(4));
    const final_type rho = (r - std::sqrt(r + r)) / (k + k);
    const final_type s = (final_type(1) + rho * rho) / (rho + rho);

    for (;;) {
      const final_type u = e_();
      const final_type v = e_();
      const final_type pi = 3.1415926535897932384626433L;
      const final_type z = std::cos(pi * u);
      const final_type w = (final_type(1) + s * z) / (s + z);
      const final_type y = k * (s - w);
      const bool accept =
        (y + y >= y * y + v) ? true : (std::log(y / v) + final_type(1) >= y);

      if (accept)
        return a +
               (u > final_type(0.5L) ? final_type(1.0L) : final_type(-1.0L)) /
                 std::cos(w);
    }
  }
};

template<typename Return_Type, typename Engine>
struct wald : private inverse_gaussian<Return_Type, Engine>
{
  typedef inverse_gaussian<Return_Type, Engine> inverse_gaussian_type;
  typedef Return_Type return_type;
  typedef Engine engine_type;
  typedef typename inverse_gaussian_type::final_type final_type;
  typedef typename inverse_gaussian_type::seed_type seed_type;

  return_type mu_;
  return_type lambda_;
  engine_type& e_;

  explicit wald(const return_type mu = 1,
                const return_type lambda = 1,
                const seed_type sd = 0)
    : mu_(mu)
    , lambda_(lambda)
    , e_(singleton<engine_type>::instance())
  {
    assert(mu > 0);
    assert(lambda > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(lambda_, mu_); }

protected:
  return_type do_generation(const final_type Lambda, const final_type Mu) const
  {
    return direct_impl(Lambda, Mu);
  }

private:
  return_type direct_impl(const final_type Lambda, const final_type Mu) const
  {
    return inverse_gaussian_type::do_generation(Lambda, Mu);
  }
};

template<typename Return_Type, typename Engine>
struct waring : private generalized_hypergeometric_b3<Return_Type, Engine>
{
  typedef generalized_hypergeometric_b3<Return_Type, Engine> GHgB3_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef Return_Type value_type;
  typedef typename Engine::seed_type seed_type;
  typedef std::size_t size_type;
  typedef Engine engine_type;

  value_type a_;
  value_type b_;
  engine_type& e_;

  explicit waring(value_type a = 1, value_type b = 1, seed_type s = 0)
    : a_(a)
    , b_(b)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > 0);
    assert(b > 0);
    e_.reset_seed(s);
  }

  return_type operator()() const { return do_generation(a_, b_); }

protected:
  return_type do_generation(const value_type a, const value_type b) const
  {
    return direct_impl(a, b);
  }

private:
  return_type direct_impl(const value_type a, const value_type b) const
  {
    const final_type ans = GHgB3_type::do_generation(a, b, final_type(1));
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct weibull
{
  typedef Return_Type return_type;
  typedef Engine engine_type;

  typedef typename engine_type::final_type final_type;
  typedef typename engine_type::seed_type seed_type;

  return_type lambda_;
  return_type k_;
  engine_type& e_;

  explicit weibull(const return_type lambda = 1,
                   const return_type k = 1,
                   const seed_type sd = 0)
    : lambda_(lambda)
    , k_(k)
    , e_(singleton<engine_type>::instance())
  {
    assert(lambda_ > 0);
    assert(k_ > 0);
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(lambda_, k_); }

protected:
  return_type do_generation(const return_type lambda, const return_type k) const
  {
    return direct_impl(lambda, k);
  }

private:
  return_type direct_impl(const return_type lambda, const return_type k) const
  {
    const final_type tmp1 = e_();
    const final_type tmp2 = -std::log(-tmp1 + final_type(1)) / k;
    const final_type tmp3 = final_type(1) / lambda;
    const final_type ans = std::pow(tmp2, tmp3);
    return ans;
  }
};

template<typename Return_Type, typename Engine>
struct yule : private exponential<Return_Type, Engine>
{
  typedef exponential<Return_Type, Engine> exponential_type;
  typedef typename Engine::final_type final_type;
  typedef Return_Type return_type;
  typedef typename Engine::seed_type seed_type;
  typedef Engine engine_type;

  final_type a_;
  engine_type& e_;

  explicit yule(const final_type a = 2, const seed_type sd = 0)
    : a_(a)
    , e_(singleton<engine_type>::instance())
  {
    assert(a > final_type(1));
    e_.reset_seed(sd);
  }

  return_type operator()() const { return do_generation(a_); }

protected:
  return_type do_generation(const final_type a) const
  {
    return exponential_impl(a);
  }

private:
  return_type exponential_impl(const final_type a) const
  {
    const final_type e1 = -exponential_type::do_generation(final_type(1));
    const final_type e2 = -exponential_type::do_generation(final_type(1));
    const final_type a1 = a - final_type(1);
    const final_type a2 = -std::exp(e1 / a1);
    const final_type a3 = final_type(1) + a2;
    const final_type a4 = std::log(a3);
    const final_type ans = e2 / a4;
    return ans;
  }
};

struct default_seed
{
  typedef std::uint_fast64_t seed_type;

  seed_type operator()() const noexcept
  {
    const seed_type s = time(0);
    int* i = new int;
    seed_type ans = s + (reinterpret_cast<seed_type>(i) |
                         (reinterpret_cast<seed_type>(i) << 32));
    ans =
      (ans & 0x5555555555555555ULL) << 1 | (ans & 0xAAAAAAAAAAAAAAAAULL) >> 1;
    ans =
      (ans & 0x3333333333333333ULL) << 2 | (ans & 0xCCCCCCCCCCCCCCCCULL) >> 2;
    ans =
      (ans & 0x0F0F0F0F0F0F0F0FULL) << 4 | (ans & 0xF0F0F0F0F0F0F0F0ULL) >> 4;
    ans =
      (ans & 0x00FF00FF00FF00FFULL) << 8 | (ans & 0xFF00FF00FF00FF00ULL) >> 8;
    ans =
      (ans & 0x0000FFFF0000FFFFULL) << 16 | (ans & 0xFFFF0000FFFF0000ULL) >> 16;
    ans =
      (ans & 0x00000000FFFFFFFFULL) << 32 | (ans & 0xFFFFFFFF00000000ULL) >> 32;
    ans |= s;
    delete i;
    return ans;
  }
};

struct linear_congruential
{
  typedef linear_congruential self_type;
  typedef long double final_type;
  typedef std::uint_fast64_t value_type;
  typedef value_type seed_type;
  typedef std::size_t size_type;

private:
  static const value_type a_ = 6364136223846793005ULL;
  static const value_type c_ = 1442695040888963407ULL;
  value_type x_;

public:
  linear_congruential(const seed_type s = 0) noexcept
  {
    x_ = s ? s : default_seed()();
  }

  void reset_seed(const seed_type s = 0) noexcept
  {
    if (s) {
      x_ = s;
    }
  }

  final_type operator()() noexcept
  {
    x_ *= a_;
    x_ += c_;
    const final_type ans =
      static_cast<final_type>(x_) /
      static_cast<final_type>(std::numeric_limits<value_type>::max());
    return ans;
  }

private:
  linear_congruential(const self_type&);
  linear_congruential& operator=(const self_type&);
};

struct mitchell_moore
{
  typedef mitchell_moore self_type;
  typedef long double final_type;
  typedef std::uint_fast64_t value_type;
  typedef value_type seed_type;
  typedef std::size_t size_type;

private:
  static const value_type ini_seed_ = 161803398;
  value_type a_[56];
  size_type next_;
  size_type next_p_;

public:
  mitchell_moore(const seed_type s = 0) noexcept
    : next_(0)
    , next_p_(31)
  {
    std::fill(a_, a_ + 56, value_type(0));
    initial(s);
  }

  void reset_seed(const seed_type s = 0) noexcept
  {
    if (0 == s)
      return;

    initial(s);
  }

  final_type operator()() noexcept
  {
    if (++next_ == 56) {
      next_ = 1;
    }

    if (++next_p_ == 56) {
      next_p_ = 1;
    }

    value_type tmp = a_[next_] - a_[next_p_];
    a_[next_] = tmp;
    const final_type ans =
      static_cast<final_type>(tmp) /
      static_cast<final_type>(std::numeric_limits<value_type>::max());
    return ans;
  }

private:
  void initial(const seed_type s) noexcept
  {
    const seed_type seed = s ? s : default_seed()();
    value_type mj = ini_seed_ - seed;
    value_type mk = 1;
    a_[55] = mj;

    for (size_type i = 1; i < 55; i++) {
      const size_type ii = (21 * i) % 55;
      a_[ii] = mk;
      mk = mj - mk;
      mj = a_[ii];
    }

    for (size_type k = 1; k < 5; k++)
      for (size_type i = 1; i < 56; i++) {
        a_[i] -= a_[1 + (i + 30) % 55];
      }
  }

private:
  mitchell_moore(const self_type&);
  mitchell_moore& operator=(const self_type&);
};

struct mt19937
{
  typedef mt19937 self_type;
  typedef long double final_type;
  typedef std::uint_fast64_t value_type;
  typedef value_type seed_type;
  typedef std::size_t size_type;

private:
  value_type mt[312];
  value_type mag01[2];
  size_type mti;

public:
  mt19937(const seed_type s = 0) noexcept { init(s); }

  void reset_seed(const seed_type s = 0) noexcept
  {
    if (0 == s)
      return;

    init(s);
  }

private:
  void init(const seed_type s) noexcept
  {
    mt[0] = s ? s : default_seed()();
    mag01[0] = 0ULL;
    mag01[1] = 0xB5026F5AA96619E9ULL;

    for (mti = 1; mti < 312; ++mti) {
      mt[mti] = 6364136223846793005ULL * (mt[mti - 1] ^ (mt[mti - 1] >> 62));
      mt[mti] += mti;
    }
  }

public:
  final_type operator()() noexcept
  {
    value_type x;

    if (mti > 311) {
      for (size_type i = 0; i < 156; ++i) {
        x = (mt[i] & 0xFFFFFFFF80000000ULL) | (mt[i + 1] & 0x7FFFFFFFULL);
        mt[i] = mt[i + 156] ^ (x >> 1) ^ mag01[x & 1];
      }

      for (size_type i = 156; i < 311; ++i) {
        x = (mt[i] & 0xFFFFFFFF80000000ULL) | (mt[i + 1] & 0x7FFFFFFFULL);
        mt[i] = mt[i - 156] ^ (x >> 1) ^ mag01[x & 1];
      }

      x = (mt[311] & 0xFFFFFFFF80000000ULL) | (mt[0] & 0x7FFFFFFFULL);
      mt[311] = mt[155] ^ (x >> 1) ^ mag01[x & 1];
      mti = 0;
    }

    x = mt[mti++];
    x ^= (x >> 29) & 0x5555555555555555ULL;
    x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
    x ^= (x << 37) & 0xFFF7EEE000000000ULL;
    x ^= (x >> 43);
    const final_type ans =
      static_cast<final_type>(static_cast<final_type>(x)) /
      static_cast<final_type>(std::numeric_limits<value_type>::max());
    return ans;
  }

private:
  mt19937(const self_type&);
  mt19937& operator=(const self_type&);
};

struct lagged_fibonacci
{
  typedef lagged_fibonacci self_type;
  typedef long double final_type;
  typedef std::uint_fast64_t value_type;
  typedef value_type seed_type;
  typedef std::size_t size_type;

private:
  value_type data[44497];
  size_type mti;

public:
  lagged_fibonacci(const seed_type s = 0) noexcept { init(s); }

  void reset_seed(const seed_type s = 0) noexcept
  {
    if (0 == s)
      return;

    init(s);
  }

private:
  void refill() noexcept
  {
    std::copy(data + 21034, data + 44497, data);

    for (size_type index = 23463; index != 44497; ++index)
      data[index] = data[index - 2] + data[index - 1];

    mti = 0;
  }

  void init(const seed_type s) noexcept
  {
    mti = s ? s : default_seed{}();
    mti %= 21034;
    data[0] = 1;
    data[1] = 1;

    for (size_type index = 2; index != 44497; ++index)
      data[index] = data[index - 2] + data[index - 1];
  }

public:
  final_type operator()() noexcept
  {
    if (mti > 21034)
      refill();

    size_type const mtj = mti + 23463;
    value_type x = data[mti] + data[mtj];
    ++mti;
    const final_type ans =
      static_cast<final_type>(static_cast<final_type>(x)) /
      static_cast<final_type>(std::numeric_limits<value_type>::max());
    return ans;
  }

private:
  lagged_fibonacci(const self_type&);
  lagged_fibonacci& operator=(const self_type&);
};

template<class Return_Type = double,
         template<class, class> class Distribution = uniform,
         class Engine = mitchell_moore>
struct variate_generator
{
  typedef Distribution<Return_Type, Engine> distribution_type;
  typedef typename distribution_type::seed_type seed_type;
  typedef typename distribution_type::return_type return_type;
  typedef std::size_t size_type;
  typedef variate_generator self_type;

  distribution_type dt_;

  template<typename... Args>
  explicit variate_generator(Args&&... args) noexcept
    : dt_{ std::forward<Args>(args)... }
  {}

  return_type operator()() const noexcept { return dt_(); }
};

} // namespace vg

#endif // VG_HPP_INCLUDED_PSDOIJAA9FODIUSOI4JLAKJSDFLASKJASLKJFDASLKJASJKFLKJDFFFF
