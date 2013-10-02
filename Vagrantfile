# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "precise64"
  config.vm.box_url = "http://files.vagrantup.com/precise64.box"

  config.vm.hostname = "avr-dev"
  config.vm.provider "virtualbox" do |v|
    v.name = "avr-dev"
  end

  config.vm.provision "chef_solo" do |chef|
    #chef.add_recipe "proxy"
    chef.add_recipe "avr"

    #chef.json = {
    #  :proxy => {
    #    :http_proxy => "$HOST:$PORT",
    #  },
    #}
  end

end
