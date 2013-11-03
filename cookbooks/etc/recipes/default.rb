Chef::Log.info("[Customising files in /etc]")
template "/etc/motd.tail" do
  source "motd.tail"
  mode "0644"
  owner "root"
  group "root"
end

Chef::Log.info("[Adding udev Rule for AVRISP-MKII programmer]")
template "/etc/udev/rules.d/30-avrisp.rules" do
  source "30-avrisp.rules"
  mode "0644"
  owner "root"
  group "root"
end

