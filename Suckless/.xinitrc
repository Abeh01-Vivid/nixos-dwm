#!/bin/sh
#Merge X resources
[ -f ~/.Xresources ] && xrdb -merge ~/.Xresources
export PATH="$HOME/.nix-profile/bin:$PATH"
xset r rate 300 50
#pipewire &
#pipewire-pulse &
picom --daemon &

slstatus &
#dwmblocks &
nitrogen --restore &
[ -f ~/.config/dwm/autostart.sh ] && ~/.config/dwm/autostart.sh &


while true; do
     dwm 2>> ~/.local/share/dwm.log
   done
