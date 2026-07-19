# System-wide and user packages, split out from configuration.nix
{ pkgs, ... }:

{
  # List packages installed in system profile. To search, run:
  # $ nix search wget
  environment.systemPackages = with pkgs; [
  #  vim # Do not forget to add an editor to edit configuration.nix! The Nano editor is also installed by default.
    wget
    emacs
    git
    ripgrep
    fd
    curl
    unzip
    # helix
    # zed-editor
    # typescript-language-server
    bash-language-server
    # nil
    # markdown-oxide
    # flameshot
    nitrogen
    #mpvpaper
    #xwinwrap
    varia
    mpv
    qbittorrent
    motrix
    pkgs.yadm
  ];

  # Per-user packages for abeh
  users.users."abeh".packages = with pkgs; [
    kdePackages.kate
    thunderbird
    unzip
    neovim
  ];

  fonts.packages = with pkgs; [
    nerd-fonts.jetbrains-mono
  ];
}
