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

  config.vm.provision "chef_solo" do |chef|
    #chef.add_recipe "proxy"
    chef.add_recipe "avr"

    #chef.json = {
    #  :proxy => {
    #    :http_proxy => "$HOST:$PORT",
    #  },
    #}

    # Provide udev Rule to match AVRISP-MKII
    chef.json = {
      :udev_avr => {
        :udev_subsys => 'SUBSYSTEM!="usb_device", ACTION!="add", GOTO="avrisp_end"',
        :udev_attrib => 'ATTR{idVendor}=="03eb", ATTR{idProduct}=="2104", MODE="660", GROUP="dialout"',
        :udev_label => 'LABEL="avrisp_end"',
      },
    }
  end

end
