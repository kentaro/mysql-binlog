Gem::Specification.new do |gem|
  gem.version       = "0.0.1"

  gem.authors       = ["Kentaro Kuribayashi"]
  gem.email         = ["kentarok@gmail.com"]
  gem.description   = %q{This is a Ruby binding to libreplication which enables us to read binary logs from MySQL through its API.}
  gem.summary       = %q{A Ruby binding to libreplication}
  gem.homepage      = "http://github.com/kentaro/mysql-binlog"

  gem.extensions    = ["ext/mysql/binlog/extconf.rb"]
  gem.files         = `git ls-files`.split($\)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.name          = "mysql-binlog"
  gem.require_paths = ["lib"]

  gem.add_development_dependency 'rake'
  gem.add_development_dependency 'rake-compiler'
  gem.add_development_dependency 'rspec', '~> 2.11.0'
end
