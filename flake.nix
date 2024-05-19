{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }@inputs:
    let
      systems = [ "x86_64-linux" "aarch64-linux" ];
      systemAttrs = flake-utils.lib.eachSystem systems (system:
        let
          pkgs = import nixpkgs { inherit system; };
        in
        {
          devShells.default = import ./shell.nix { inherit pkgs; };
          formatter = pkgs.nixpkgs-fmt;
        });
    in
    systemAttrs;
}
