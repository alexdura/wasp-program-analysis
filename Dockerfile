FROM ubuntu:18.04

RUN useradd -m phasar && echo phasar:phasar | chpasswd && \
	usermod -aG sudo phasar

ENV DEBIAN_FRONTEND="noninteractive"

# General-purpose utilities
RUN apt-get update && apt-get -y install \
	git \
	build-essential \
	gdb \
	python3 \
	gcc \
	emacs \
	vim \
	nano \
	tmux \
	sudo \
	cmake \
	libncurses5-dev \
	colortest
RUN apt-get install -y zlib1g zlib1g-dev sqlite3 libsqlite3-dev python3 doxygen graphviz \
	python python-dev python3-pip python-pip libxml2 libxml2-dev libncurses5-dev libncursesw5-dev \
	swig build-essential g++ cmake libedit-dev python-sphinx libcurl4-openssl-dev


RUN apt-get -y install python-pip python3-pip

RUN apt-get -y install wget libpcre2-dev libpcre++-dev

RUN apt-get -y install zlib1g-dev libncurses5-dev sqlite3 libsqlite3-dev bear python3 doxygen graphviz

RUN apt-get -y install wget gcc g++

RUN apt-get -y install software-properties-common

RUN apt-get -y install make libcurl4-gnutls-dev git

RUN pip install Pygments
RUN pip install pyyaml
RUN pip3 install wllvm


ADD --chown=phasar:phasar ./phasar /phasar_src/
RUN cd /phasar_src && bash ./bootstrap_boost.sh

RUN apt-get -y install libc6-dev
ADD ./llvm /phasar_src/llvm-project
RUN cd /phasar_src && bash ./bootstrap_llvm.sh
RUN cd /phasar_src && bash ./bootstrap_phasar.sh


# # Libraries needed to build GCC
# RUN apt-get -y install \
# 	libmpfr-dev \
# 	libgmp-dev \
# 	libmpc-dev

# ENV PHASAR_TOOLS=/tools

# RUN mkdir -p /phasar/src
# RUN mkdir -p /phasar/build

# ADD --chown=phasar:phasar ./arch /toolbuild
