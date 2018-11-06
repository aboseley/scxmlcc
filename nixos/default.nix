with import <nixpkgs> {};
stdenv.mkDerivation rec {

  name = "scxmlcc-${version}";
  version = "0.8.7";

  meta = {
    description = "scxml state machine to c++ compiler";
    longDescription = ''
    The goal of scxmlcc is to make a Open Source full featured state machine 
    compiler that can generate simple and effective C++ state machines from 
    scxml state charts
    '';
    homepage = "https://github.com/jp-embedded/scxmlcc";
    license =  stdenv.lib.licenses.gpl3;
    maintainers = [ stdenv.lib.maintainers.aboseley ];
  };

  src = fetchFromGitHub {
    owner = "jp-embedded";
    repo  =  "scxmlcc";
    rev = "77dcd3b3c4ef9de8e64f6069117a7fd54687c9d1";
    sha256 = "0301gwvhi3mmpkh47kwdw5sr2xfgb3lf8mz7f9wv9qdz3lfwp7zx";
    fetchSubmodules = true;
    leaveDotGit = true;
  };

  nativeBuildInputs = [
     autorevision
     git
     cmake
  ];

  buildInputs = [
     libxslt
     boost
  ];

  cmakeFlags = [ "-DCMAKE_VERBOSE_MAKEFILE=1" ];

}

