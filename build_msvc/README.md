Building CCGO Core with Visual Studio
========================================

Introduction
---------------------
Solution and project files to build the CCGO Core applications `msbuild` or Visual Studio can be found in the build_msvc directory. The build has been tested with Visual Studio 2017 and 2019.

Building with Visual Studio is an alternative to the Linux based [cross-compiler build](https://github.com/vpubchain/virlces/blob/master/doc/build-windows.md).

Quick Start
---------------------
The minimal steps required to build CCGO Core with the msbuild toolchain are below. More detailed instructions are contained in the following sections.

```
vcpkg install --triplet x64-windows-static boost-filesystem boost-multi-index boost-signals2 boost-test boost-thread libevent zeromq berkeleydb rapidcheck double-conversion
py -3 build_msvc\msvc-autogen.py
msbuild /m build_msvc\virlces.sln /p:Platform=x64 /p:Configuration=Release /t:build
```

Quick Start
---------------------
The minimal steps required to build CCGO Core with the msbuild toolchain are below. More detailed instructions are contained in the following sections.

```
vcpkg install --triplet x64-windows-static boost-filesystem boost-multi-index boost-signals2 boost-test boost-thread libevent openssl zeromq berkeleydb rapidcheck double-conversion
py -3 build_msvc\msvc-autogen.py
msbuild /m build_msvc\virlces.sln /p:Platform=x64 /p:Configuration=Release /t:build
```

Dependencies
---------------------
A number of open source libraries are required in order to be able to build CCGO Core.

The external dependencies required for building are:

- Berkeley DB
- Boost
- DoubleConversion
- libevent
- Qt5
- RapidCheck
- ZeroMQ

Qt
---------------------
In order to build the CCGO Core a static build of Qt is required. The runtime library version (e.g. v141, v142) and platform type (x86 or x64) must also match.

A prebuilt version of Qt can be downloaded from [here](https://github.com/sipsorcery/qt_win_binary/releases). Please be aware this download is NOT an officially sanctioned CCGO Core distribution and is provided for developer convenience. It should NOT be used for builds that will be used in a production environment or with real funds.

To build Bitcoin Core without Qt unload or disable the `virlces-qt`, `libvirlces_qt` and `test_vircles-qt` projects.

Building
---------------------
The instructions below use `vcpkg` to install the dependencies.

- Install [`vcpkg`](https://github.com/Microsoft/vcpkg).
- Install the required packages (replace x64 with x86 as required). The list of required packages can be found in the `build_msvc\vcpkg-packages.txt` file. The PowerShell command below will work if run from the repository root directory and `vcpkg` is in the path. Alternatively the contents of the packages text file can be pasted in place of the `Get-Content` cmdlet.

```
PS >.\vcpkg install --triplet x64-windows-static $(Get-Content -Path build_msvc\vcpkg-packages.txt).split()
```

- Use Python to generate `*.vcxproj` from Makefile

```
PS >py -3 msvc-autogen.py
```

- An optional step is to adjust the settings in the build_msvc directory and the common.init.vcxproj file. This project file contains settings that are common to all projects such as the runtime library version and target Windows SDK version. The Qt directories can also be set.

- Build with Visual Studio 2017 or msbuild.

```
msbuild /m virlces.sln /p:Platform=x64 /p:Configuration=Release /p:PlatformToolset=v141 /t:build
```

- Build with Visual Studio 2019 or msbuild.

```
msbuild /m virlces.sln /p:Platform=x64 /p:Configuration=Release /t:build
```

AppVeyor
---------------------
The .appveyor.yml in the root directory is suitable to perform builds on [AppVeyor](https://www.appveyor.com/) Continuous Integration servers. The simplest way to perform an AppVeyor build is to fork CCGO Core and then configure a new AppVeyor Project pointing to the forked repository.

For safety reasons the CCGO Core .appveyor.yml file has the artifact options disabled. The build will be performed but no executable files will be available. To enable artifacts on a forked repository uncomment the lines shown below:

```
    #- 7z a virlces-%APPVEYOR_BUILD_VERSION%.zip %APPVEYOR_BUILD_FOLDER%\build_msvc\%platform%\%configuration%\*.exe
    #- path: virlces-%APPVEYOR_BUILD_VERSION%.zip
```
