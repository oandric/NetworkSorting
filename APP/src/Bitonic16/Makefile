# Root of the project directory tree
BASEDIR=../..
# Java package name
PACKAGE=Bitonic16
# Application name
APP=NetworkSort

# Names of your maxfiles
HWMAXFILE=$(APP).max
HOSTSIMMAXFILE=$(APP)HostSim.max

# Java application builders
HWBUILDER=$(APP)HWBuilder.java
HOSTSIMBUILDER=$(APP)HostSimBuilder.java
SIMRUNNER=$(APP)SimRunner.java

# C host code
HOSTCODE=$(APP)HostCode.c

# Include the master makefile.include
nullstring :=
space := $(nullstring) # comment 
MAXCOMPILERDIR_QUOTE:=$(subst $(space),\ ,$(MAXCOMPILERDIR))
include $(MAXCOMPILERDIR_QUOTE)/examples/common/Makefile.include
