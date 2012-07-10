require 'mysql/binlog/client'

module MySQL
  class Binlog
    attr_reader :url, :client

    def initialize (url)
      @url    = url
      @client = MySQL::Binlog::Client.new(@url)
    end

    def connect ()
      @client.connect
    end

    def wait_for_next_event ()
      @client.wait_for_next_event
    end

    def set_position (position)
      @client.set_position(position)
    end

    def get_position ()
      @client.get_position()
    end
  end
end
