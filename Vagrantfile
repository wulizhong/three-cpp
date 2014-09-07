# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

$script = <<SCRIPT
sudo apt-get -qq update
sudo apt-get install -y -qq python-software-properties
sudo apt-add-repository --yes ppa:zoogie/sdl2-snapshots 
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get -qq update
sudo apt-get install -qq g++-4.8
export CXX="g++-4.8" CC="gcc-4.8"
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 90
sudo apt-get -qq install build-essential libsdl2-dev gcc-multilib gcc-4.8-multilib g++-4.8-multilib cmake
SCRIPT

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

  config.vm.box = "hashicorp/precise32"

  config.vm.provision :shell, inline: $script

end
