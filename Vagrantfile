# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "precise64"
  config.vm.box_url = "http://files.vagrantup.com/precise64.box"

  config.vm.hostname = "avr-dev"
  config.vm.provider "virtualbox" do |v|
    v.name = "avr-dev"
    # Enable USB Support with EHCI and Device Filtering to support AVRISP-MKII
    v.customize ['modifyvm', :id, '--usb', 'on']
    v.customize ['modifyvm', :id, '--usbehci', 'on']
    v.customize ['usbfilter', 'add', '0', '--target', :id, '--name', 'AVRISP mkII', '--vendorid', '0x03eb']
  end

  config.ssh.forward_agent = true

  config.vm.provision "chef_solo" do |chef|
    chef.cookbooks_path = "chef/cookbooks"
    chef.add_recipe "proxy"
    chef.add_recipe "apt"
    chef.add_recipe "avr"
    chef.add_recipe "etc"
  end

end
