# Base Debian slim
FROM debian:stable-slim

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8
ENV SHELL=/usr/bin/zsh
WORKDIR /project

# Installa strumenti di sviluppo, clang-tidy, neovim e Zsh
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    clang-tidy \
    cmake \
    bear \
    libcurl4-openssl-dev \
    libcjson-dev \
    pkg-config \
    git \
    neovim \
    curl \
    ca-certificates \
    zsh \
    sudo && \
    rm -rf /var/lib/apt/lists/*

# Default shell: zsh, senza config predefinita
CMD ["zsh"]

