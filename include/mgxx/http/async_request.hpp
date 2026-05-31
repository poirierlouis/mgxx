#ifndef MGXX_HTTP_ASYNC_REQUEST_HPP
#define MGXX_HTTP_ASYNC_REQUEST_HPP

#include <mongoose.h>

#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "mgxx/internal/remote_context.hpp"
#include "mgxx/tls.hpp"

namespace mgxx::http {
class async_request {
  mg_http_message m_msg{};
  std::vector<mg_str> m_groups;
  std::string m_ip;
  tls_cert_info m_tls_cert_info;

 public:
  explicit async_request(const mg_http_message* msg);
  explicit async_request(const mg_http_message* msg, std::vector<mg_str> groups,
                         std::string_view ip, tls_cert_info tls_cert_info);
  ~async_request();

  async_request(const async_request&) = delete;
  async_request& operator=(const async_request&) = delete;

  async_request(async_request&& rhs) noexcept;
  async_request& operator=(async_request&& rhs) noexcept;

  [[nodiscard]] std::string_view get_remote_ip() const;
  [[nodiscard]] bool is_mtls() const;
  [[nodiscard]] const tls_cert_info& get_tls_cert_info() const;

  [[nodiscard]] std::string_view method() const;
  [[nodiscard]] std::string_view uri() const;
  [[nodiscard]] std::optional<std::string_view> get_param(size_t index) const;
  [[nodiscard]] std::string_view query() const;
  [[nodiscard]] std::optional<std::string_view> get_query_param(
      std::string_view name) const;
  [[nodiscard]] std::string_view version() const;
  [[nodiscard]] std::optional<std::string_view> get_header(
      const std::string& name) const;
  [[nodiscard]] std::string_view body() const;
};
}  // namespace mgxx::http

#endif  // MGXX_HTTP_ASYNC_REQUEST_HPP
