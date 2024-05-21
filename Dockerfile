FROM    ubuntu:latest

RUN     apt-get update &&       \
        apt-get install -y      \
        g++ make less           \
        libcurl4-openssl-dev    \
        libjsoncpp-dev          \
        libxml2-dev

WORKDIR /root
COPY    include include
COPY    src src
COPY    Makefile Makefile

RUN     make

CMD     ["sleep", "infinity"]
