{ config, pkgs, ... }:

{
  services.xserver.windowManager.dwm = {
    enable = true;
    package = pkgs.dwm.overrideAttrs (old: {
      src = /home/abeh/Suckless/dwm;
      patches = [ ];
      preBuild = "make clean || true";
      postPatch = "";
      makeFlags = [ "PREFIX=${placeholder "out"}" ];
      buildInputs = old.buildInputs ++ [
        pkgs.imlib2
        pkgs.libXext
      ];
    });
  };

  environment.systemPackages = with pkgs; [
    (dmenu.overrideAttrs (old: {
      preBuild = "make clean || true";
      src = /home/abeh/Suckless/dmenu;
    }))

    (st.overrideAttrs (old: {
      preBuild = "make clean || true";
      src = /home/abeh/Suckless/st;
    }))

    (slstatus.overrideAttrs (old: {
      preBuild = "make clean || true";
      src = /home/abeh/Suckless/slstatus;
    }))
  ];
}
