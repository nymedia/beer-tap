# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.box_url = "https://vagrantcloud.com/ubuntu/boxes/trusty64"
  config.vm.provision :shell, :path => "environment/provision.sh", :args => ENV['SHELL_ARGS']
  config.vm.network :forwarded_port, guest: 80, host: 8777, auto_correct: true # IMPORTANT: Configure port
  config.vm.network :forwarded_port, guest: 22, host: 2777, auto_correct: true # IMPORTANT: Configure port
  config.vm.network :private_network, ip: '192.168.50.50' # IMPORTANT: Look out for collisions
  config.ssh.forward_agent = true

  config.vm.synced_folder "./", "/project", id: "project-folder",
    nfs: true

  config.vm.provider :virtualbox do |vb|
    vb.customize ["modifyvm", :id, "--memory", "1024"]
    vb.customize ["modifyvm", :id, "--natdnshostresolver1", "on"]
    vb.customize ["modifyvm", :id, "--natdnsproxy1", "on"]
  end

end
