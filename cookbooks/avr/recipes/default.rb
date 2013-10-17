# Run upgrade before adding any package at all
execute "apt-get upgrade -y"

Chef::Log.info("[Adding Basic Development Packages]")
[
  "build-essential",
  "gcc",
  "git-core",
  "vim",
].each do |p|
  package p
end

Chef::Log.info("[Adding AVR Development Packages]")
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

Chef::Log.info("[Adding udev Rule for AVRISP-MKII programmer]")
template "/etc/udev/rules.d/30-avrisp.rules" do
  source "30-avrisp.rules"
  mode "0644"
  owner "root"
  group "root"
end

Chef::Log.info("[Adding User 'vagrant' to group 'dialout']")
group "dialout" do
  action :modify
  members "vagrant"
  append true
end
