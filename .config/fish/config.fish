set fish_greeting
set -gx EDITOR nvim

# NixOS system management (non-flake)
abbr -a rebuild 'sudo nixos-rebuild switch'
abbr -a rebuild-boot 'sudo nixos-rebuild boot'
abbr -a rebuild-test 'sudo nixos-rebuild test'
abbr -a channel-update 'sudo nix-channel --update'
abbr -a channel-list 'nix-channel --list'
abbr -a gens 'sudo nix-env --list-generations --profile /nix/var/nix/profiles/system'
abbr -a gc 'sudo nix-collect-garbage -d'
abbr -a gc-old 'sudo nix-collect-garbage --delete-older-than 14d'
abbr -a edit-nix 'sudo nvim /etc/nixos/configuration.nix'
abbr -a edit-hardware 'sudo nvim /etc/nixos/hardware-configuration.nix'
abbr -a edit-fish 'sudo nvim /etc/nixos/modules/fish.nix'
abbr -a edit-suckless 'sudo nvim /etc/nixos/modules/suckless.nix'
abbr -a edit-awesome 'sudo nvim /etc/nixos/modules/awesomewm.nix'
abbr -a edit-jetbrains 'sudo nvim /etc/nixos/modules/jetbrains.nix'
abbr -a edit-picom 'sudo nvim /etc/nixos/modules/picom.nix'

# Suckless
abbr -a dwm-build 'cd ~/Suckless/dwm-flexipatch && sudo make clean install'
abbr -a st-build 'cd ~/Suckless/st && sudo make clean install'
abbr -a dmenu-build 'cd ~/Suckless/dmenu && sudo make clean install'
abbr -a slstatus-build 'cd ~/Suckless/slstatus && sudo make clean install'

# Git / yadm
abbr -a gs 'git status'
abbr -a ga 'git add'
abbr -a gcm 'git commit -m'
abbr -a gp 'git push'
abbr -a gl 'git log --oneline --graph --decorate'
abbr -a yd 'yadm'
abbr -a yds 'yadm status'
abbr -a ydp 'yadm push'

# Navigation
abbr -a ll 'ls -lah'
abbr -a la 'ls -A'
abbr -a ... 'cd ../..'

# Editors
abbr -a v 'nvim'
abbr -a doom-sync '~/.config/emacs/bin/doom sync'
abbr -a doom-upgrade '~/.config/emacs/bin/doom upgrade'

# Custom functions
function mkcd
    mkdir -p $argv[1]; and cd $argv[1]
end

function flake-search
    nix search nixpkgs $argv[1]
end
