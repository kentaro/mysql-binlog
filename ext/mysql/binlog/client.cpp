#include "ruby.h"
#include "binlog_api.h"

VALUE mysql_module, binlog_class, client_class;

typedef mysql::Binary_log* binlog_t;
typedef mysql::system::Binary_log_driver* driver_t;

VALUE mysql_binlog_client_initialize (VALUE self, VALUE url)
{
  driver_t driver = mysql::system::create_transport(StringValuePtr(url));
  if (!driver) {
    rb_raise(rb_eRuntimeError, "Cannot parse driver");
  }
  rb_ivar_set(self, rb_intern("mysql_binlog_client_driver"), (VALUE)driver);

  binlog_t binlog = new mysql::Binary_log(driver);
  rb_ivar_set(self, rb_intern("mysql_binlog_client_binlog"), (VALUE)binlog);

  return Qnil;
}

VALUE
mysql_binlog_client_connect (VALUE self, char *url)
{
  driver_t driver = (driver_t)rb_ivar_get(self, rb_intern("mysql_binlog_client_driver"));
  driver->connect();

  return Qnil;
}

VALUE
mysql_binlog_client_set_position (VALUE self, VALUE position)
{
  binlog_t binlog = (binlog_t)rb_ivar_get(self, rb_intern("mysql_binlog_client_binlog"));
  binlog->set_position((int)position);

  return Qnil;
}

VALUE
mysql_binlog_client_get_position (VALUE self)
{
  binlog_t binlog = (binlog_t)rb_ivar_get(self, rb_intern("mysql_binlog_client_binlog"));
  return INT2NUM(binlog->get_position());
}

VALUE
mysql_binlog_client_wait_for_next_event(VALUE self)
{
  driver_t driver = (driver_t)rb_ivar_get(self, rb_intern("mysql_binlog_client_driver"));
  mysql::Binary_log_event *event;
  int result = driver->wait_for_next_event(&event);

  if (result == ERR_EOF) {
    return Qnil;
  }
  else {
    return Qtrue; //(VALUE)event; <- せぐふぉる…
  }
}

extern "C" {
  void Init_client () {

    mysql_module = rb_define_module("MySQL");
    binlog_class = rb_define_class_under(mysql_module, "Binlog", rb_cObject);
    client_class = rb_define_class_under(binlog_class, "Client", rb_cObject);

    rb_define_private_method (client_class, "initialize", RUBY_METHOD_FUNC(mysql_binlog_client_initialize), 1);
    rb_define_method(client_class, "connect", RUBY_METHOD_FUNC(mysql_binlog_client_connect), 0);
    rb_define_method(client_class, "set_position", RUBY_METHOD_FUNC(mysql_binlog_client_set_position), 1);
    rb_define_method(client_class, "get_position", RUBY_METHOD_FUNC(mysql_binlog_client_get_position), 0);
    rb_define_method(client_class, "wait_for_next_event", RUBY_METHOD_FUNC(mysql_binlog_client_wait_for_next_event), 0);
  }
}
