#include "mgxx/tls.hpp"

namespace mgxx {
tls_cert_info::tls_cert_info(const tls_cert_info& rhs) { *this = rhs; }

tls_cert_info& tls_cert_info::operator=(const tls_cert_info& rhs) {
  if (this == &rhs) {
    return *this;
  }

  buffer = rhs.buffer;

  ptrdiff_t delta = buffer.data() - rhs.buffer.data();
  const auto rebase = [delta](std::string_view view) -> std::string_view {
    if (view.empty()) {
      return {};
    }

    return {view.data() + delta, view.size()};
  };

  subject_name = rebase(rhs.subject_name);
  issuer_name = rebase(rhs.issuer_name);
  serial_number = rebase(rhs.serial_number);
  not_before = rebase(rhs.not_before);
  not_after = rebase(rhs.not_after);
  fingerprint = rebase(rhs.fingerprint);

  return *this;
}

bool tls_cert_info::is_present() const { return !buffer.empty(); }

std::string_view tls_cert_info::get_subject_name() const {
  return subject_name;
}

std::string_view tls_cert_info::get_issuer_name() const { return issuer_name; }

std::string_view tls_cert_info::get_serial_number() const {
  return serial_number;
}

std::string_view tls_cert_info::get_not_before() const { return not_before; }

std::string_view tls_cert_info::get_not_after() const { return not_after; }

std::string_view tls_cert_info::get_fingerprint() const { return fingerprint; }
}  // namespace mgxx