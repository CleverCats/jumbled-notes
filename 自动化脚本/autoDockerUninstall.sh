# For unistall in Ubuntu
sudo apt-get purge docker.io 
# This will erase all your container images
sudo rm -rf /var/lib/docker
# This will erase all docker configs
sudo rm -rf /etc/docker/
sudo apt-get purge docker.io

# link: https://qastack.cn/ubuntu/709699/unable-to-locate-package-docker-engine