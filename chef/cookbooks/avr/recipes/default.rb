Chef::Log.info("[Adding: Basic Development Packages]")
[
  "build-essential",
  "gcc",
  "git-core",
  "vim",
].each do |p|
  package p
end

Chef::Log.info("[Adding: AVR Development Packages]")
[
  "avr-libc",
  "avrdude",
  "avrdude-doc",
  "binutils-avr",
  "check",
  "cu",
  "gcc-avr",
  "gdb-avr",
].each do |p|
  package p
end

Chef::Log.info("[Adding: User 'vagrant' to group 'dialout']")
group "dialout" do
  action :modify
  members "vagrant"
  append true
end
