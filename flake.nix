{
  description = "NQueens solutions";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    pre-commit-hooks = {
      url = "github:cachix/pre-commit-hooks.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    # Utility functions to configure for multiple systems
    flake-utils.url = "github:numtide/flake-utils";
  };

  # `inputs @` allows all the inputs to be accessed later if they're unnamed in the args.
  outputs = {
    self,
    flake-utils,
    nixpkgs,
    pre-commit-hooks,
    ...
  }:
    with flake-utils;
      lib.eachSystem [lib.system.aarch64-linux lib.system.x86_64-linux] (system: let
        pkgs = import nixpkgs {inherit system;};
      in {
        # Install devshell packages
        devShells.default = pkgs.mkShell {
          inherit (self.checks.${system}.pre-commit) shellHook;
          packages = with pkgs; [
            # General formatters/tools
            deadnix
            nixfmt
            nodePackages.prettier
            statix
            shellcheck

            # Generic C++ packages
            cmake
            gcc
            ninja
            clang

            # Boost is needed for this repo
            # (boost159.override { enableStatic = true; })
            (boost.override {
              enableStatic = true;
              enableShared = true;
              components = [
                "unit_test_framework"
              ];
            })
            pkg-config
          ];
          CMAKE_GENERATOR = "Ninja";
        };

        checks = {
          # Add pre-commit-hooks. Note that these only run on the files in a commit unless running `nix flake check`.
          pre-commit = pre-commit-hooks.lib.${system}.run {
            src = ./.;
            default_stages = ["commit"];
            hooks = {
              # Format any nix files
              alejandra.enable = true;

              # Lint/format the shell files.
              shellcheck.enable = true;

              # Format any changed files
              # Formatting settings are contained in .clang-format
              clang-format = {
                enable = true;
                types_or = ["c" "c++"];
                excludes = ["catch.hpp"];
              };
            };
          };
        };
      });
}
