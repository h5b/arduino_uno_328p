Chef::Log.info("[Customising: /etc/motd]")
template "/etc/update-motd.d/99-banner" do
  source "motd.ascii.banner"
  mode "0755"
  owner "root"
  group "root"
end

Chef::Log.info("[Adding: udev Rule for AVRISP-MKII Programmer]")
template "/etc/udev/rules.d/30-avrisp.rules" do
  source "30-avrisp.rules"
  mode "0644"
  owner "root"
  group "root"
  action :create_if_missing
end

