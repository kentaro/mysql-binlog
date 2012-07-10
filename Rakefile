#!/usr/bin/env rake
require "bundler/gem_tasks"

require 'rspec/core'
require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec) do |spec|
  spec.pattern = FileList['spec/**/*_spec.rb']
end

task :default => :spec

require "rake/extensiontask"

# I want to locate my binary at mysql/binlog/client.{bundle,so} not at
# mysql/binlog/mysql-binlog.{bundle,so}
class Rake::ExtensionTask
  attr_accessor :binary_name

  def binary(platform = nil)
    ext = case platform
          when /darwin/
            'bundle'
          when /mingw|mswin|linux/
            'so'
          when /java/
            'jar'
          else
            RbConfig::CONFIG['DLEXT']
          end
    "#{binary_name}.#{ext}"
  end
end

Rake::ExtensionTask.new do |ext|
  ext.name        = "mysql-binlog"
  ext.binary_name = "client"
  ext.ext_dir     = "ext/mysql/binlog"
  ext.lib_dir     = "lib/mysql/binlog"
end
