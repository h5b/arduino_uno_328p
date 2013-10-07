# Toolchain for AVR Development
[
  "avr-libc",
  "avrdude",
  "avrdude-doc",
  "binutils-avr",
  "build-essential",
  "check",
  "gcc-avr",
  "gdb-avr",
].each do |p|
  package p
end

if node['udev_avr']
  execute 'vagrant_to_group_dialout' do
    command "adduser vagrant dialout"
  end

  Chef::Log.info(node['udev_subsys'])
  avr_ispmk2 = node['udev_avr']['udev_subsys']
  avr_ispmk2 += "\n"
  avr_ispmk2 += node['udev_avr']['udev_attrib']
  avr_ispmk2 += "\n"
  avr_ispmk2 += node['udev_avr']['udev_label']
  avr_ispmk2 += "\n"
  file "/etc/udev/rules.d/10-avrisp.rules" do
    owner "root"
    group "root"
    content avr_ispmk2
    action :create
  end

else
  Chef::Log.info("No udev_avr found.")
  file "/etc/udev/rules.d/10-avrisp.rules" do
    action :delete
    only_if {::File.exists?("/etc/udev/rules.d/10-avrisp.rules")}
  end
end
