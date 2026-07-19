{ config, pkgs, ... }:

{
  nixpkgs.config.allowUnfree = true;

  environment.systemPackages = with pkgs; [
    # Changed from jetbrains.idea-ultimate -> jetbrains.idea
    jetbrains.idea                       
    
    # Changed from jetbrains.pycharm-professional -> jetbrains.pycharm
    jetbrains.pycharm                    
    
    # These generally remain the same, but update if others throw similar errors
    #jetbrains.clion
    #jetbrains.webstorm
    #jetbrains.datagrip
    #jetbrains.rider
   ];
}
