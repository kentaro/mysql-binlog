require "spec_helper"
require "mysql/binlog"

shared_context "binlog instance" do
  let(:client) { MySQL::Binlog.new("mysql://msandbox:msandbox@127.0.0.1:21580") }
  subject { client }
end

describe MySQL::Binlog do
  describe "#new" do
    include_context "binlog instance"

    it { expect(subject).to be_an_instance_of MySQL::Binlog }
  end

  describe "#url" do
    include_context "binlog instance"

    it { expect(subject.url).to eq("mysql://msandbox:msandbox@127.0.0.1:21580") }
  end

  describe "#client" do
    include_context "binlog instance"

    it { expect(subject.client).to be_an_instance_of MySQL::Binlog::Client }
  end

  describe "(set|get)position" do
    include_context "binlog instance"

    it 'should set and get position' do
      expect { subject.set_position(0) }.to change{ subject.get_position }.from(4).to(1)
      expect { subject.set_position(1) }.to change{ subject.get_position }.from(1).to(3)
    end
  end

  describe "#wait_for_next_event" do
    include_context "binlog instance"
    before { subject.connect }

    it { expect(subject.wait_for_next_event).to be_true }
  end
end
