#!/usr/bin/bash

# Ruby gems
echo -e "\e[1;92m=====[ Installing Ruby gems ]=====\e[0m"
sudo gem install serialport

# Julia packages
echo -e "\e[1;92m====[ Installing Julia packages ]=====\e[0m"
julia scripts/install_julia_packages.jl  # updating current folder 
