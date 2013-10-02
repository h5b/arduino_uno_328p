# prerequisite of custom proxy
if node['proxy']['http_proxy']
  Chef::Log.info(node['http_proxy'])
  proxy = "Acquire::http::Proxy \""
  proxy += node['proxy']['http_proxy']
  proxy += "\";\n"
  file "/etc/apt/apt.conf.d/01proxy" do
    owner "root"
    group "root"
    mode 00644
    content proxy
    action :create
  end
else
  Chef::Log.info("No http_proxy found.")
  file "/etc/apt/apt.conf.d/01proxy" do
    action :delete
    only_if {::File.exists?("/etc/apt/apt.conf.d/01proxy")}
  end
end
