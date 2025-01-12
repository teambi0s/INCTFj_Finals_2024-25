FROM ubuntu:22.04

RUN apt-get -y update && \
    apt-get -y upgrade

RUN useradd -m ctf
RUN echo "ctf:ctf" | chpasswd
WORKDIR /home/ctf

COPY Choc_Shop .
COPY flag.txt .
COPY ynetd .

RUN chown -R root:root /home/ctf
RUN chmod -R 555 /home/ctf

USER ctf
EXPOSE 1338
CMD ./ynetd -p 1338 ./Choc_Shop
