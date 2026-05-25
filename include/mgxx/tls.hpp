#ifndef MGXX_TLS_HPP
#define MGXX_TLS_HPP

#include <string_view>
#include <vector>

namespace mgxx {

namespace http {
class remote_context;
class request;
class async_request;
}  // namespace http

class tls_cert_info {
  std::vector<char> buffer;

  std::string_view subject_name;
  std::string_view issuer_name;
  std::string_view serial_number;

  std::string_view not_before;
  std::string_view not_after;

  std::string_view fingerprint;

  [[nodiscard]] bool is_present() const;

  friend class mgxx::http::remote_context;
  friend class mgxx::http::request;
  friend class mgxx::http::async_request;

 public:
  tls_cert_info() = default;
  ~tls_cert_info() = default;

  tls_cert_info(const tls_cert_info& rhs);
  tls_cert_info& operator=(const tls_cert_info& rhs);

  tls_cert_info(tls_cert_info&&) noexcept = default;
  tls_cert_info& operator=(tls_cert_info&&) noexcept = default;

  [[nodiscard]] std::string_view get_subject_name() const;
  [[nodiscard]] std::string_view get_issuer_name() const;
  [[nodiscard]] std::string_view get_serial_number() const;
  [[nodiscard]] std::string_view get_not_before() const;
  [[nodiscard]] std::string_view get_not_after() const;
  [[nodiscard]] std::string_view get_fingerprint() const;
};
}  // namespace mgxx

#endif  // MGXX_TLS_HPP
