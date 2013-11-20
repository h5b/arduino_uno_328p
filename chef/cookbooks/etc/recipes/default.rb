Chef::Log.info("[Customising: /etc/motd]")
template "/etc/motd.tail" do
  source "motd.tail"
  mode "0644"
  owner "root"
  group "root"
  action :create_if_missing
end

Chef::Log.info("[Adding: udev Rule for AVRISP-MKII Programmer]")
template "/etc/udev/rules.d/30-avrisp.rules" do
  source "30-avrisp.rules"
  mode "0644"
  owner "root"
  group "root"
  action :create_if_missing
end

