require "mkmf"

have_library("replication")

libs = %W[replication stdc++]

if RUBY_PLATFORM =~ /darwin/
  libs << "boost_system-mt"
else
  libs << "boost_system"
end

libs.each do |l|
  $LDFLAGS << " -l#{l}"
end

create_makefile("client")
