FROM ubuntu:22.04

RUN export TERM="xterm-256color"

RUN apt-get -y update && \
    apt-get -y upgrade

RUN useradd -m ctf
RUN echo "ctf:ctf" | chpasswd
WORKDIR /home/ctf

COPY woogie-woogie .
COPY almost.txt .
COPY ynetd .
COPY - .
COPY ld-linux-x86-64.so.2 .
COPY libc.so.6 .

RUN chown -R root:root /home/ctf
RUN chmod -R 555 /home/ctf

USER ctf
EXPOSE 1338
CMD ./ynetd -p 1338 ./woogie-woogie
