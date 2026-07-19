# modules/gtk-theme.nix
{ pkgs, ... }:

{
  environment.systemPackages = with pkgs; [
    lxappearance
    catppuccin-gtk.override {
      accents = [ "blue" ];
      size = "standard";
      variant = "mocha";
    }
    papirus-icon-theme
  ];

  # Sets GTK_THEME globally so apps launched from dwm pick it up
  # even without a session manager exporting it.
  environment.sessionVariables = {
    GTK_THEME = "Catppuccin-Mocha-Standard-Blue-Dark";
  };

  # Optional: system-wide GTK3 default, so new users / no ~/.config
  # entry still get a sane theme before lxappearance is ever run.
  environment.etc."xdg/gtk-3.0/settings.ini".text = ''
    [Settings]
    gtk-theme-name=Catppuccin-Mocha-Standard-Blue-Dark
    gtk-icon-theme-name=Papirus-Dark
    gtk-application-prefer-dark-theme=1
  '';
}
