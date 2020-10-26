# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "hashicorp/bionic64"

  config.vm.hostname = "avr-dev"
  config.vm.provider "virtualbox" do |v|
    v.name = "avr-dev"
    # Enable USB Support with EHCI and Device Filtering to support AVRISP-MKII
    # and Arduino UNO's/Duemilanove's USB-to-Serial Port
    v.customize ['modifyvm', :id, '--usb', 'on']
    v.customize ['modifyvm', :id, '--usbehci', 'on']
    v.customize ['usbfilter', 'add', '0', '--target', :id, '--name', 'AVRISP mkII', '--vendorid', '0x03eb']
    v.customize ['usbfilter', 'add', '1', '--target', :id, '--name', 'Uno Serial', '--vendorid', '0x2341']
    v.customize ['usbfilter', 'add', '2', '--target', :id, '--name', 'Duemilanove Serial', '--vendorid', '0x0403']
  end

  config.ssh.forward_agent = true

  config.vm.provision "chef_solo" do |chef|
    chef.cookbooks_path = "chef/cookbooks"
    chef.add_recipe "apt"
    chef.add_recipe "avr"
    chef.add_recipe "avr::vagrant"
    chef.add_recipe "git"
    chef.add_recipe "vim"
    chef.add_recipe "etc"
    chef.arguments = '--chef-license accept'
  end

end
