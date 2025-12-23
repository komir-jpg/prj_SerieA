FROM debian:stable-slim

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8
ENV SHELL=/usr/bin/zsh

# Installa strumenti di sviluppo C e utilities
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    clang-tidy \
    make \
    cmake \
    bear \
    libcurl4-openssl-dev \
    libcjson-dev \
    pkg-config \
    git \
    neovim \
    curl \
    wget \
    ca-certificates \
    zsh \
    ripgrep \
    fd-find \
    fzf \
    sudo \
    nodejs \
    npm \
    doctest-dev \
    libavdevice-dev \
    libdeflate-dev \
    libgpm-dev \
    libncurses-dev \
    libswscale-dev \
    pandoc \
    libunistring-dev \
    libgtk-4-dev \
    libadwaita-1-dev \
    libcairo2-dev \
    libpango1.0-dev \
    libgdk-pixbuf-2.0-dev \
    libx11-dev \
    libxext-dev \
    libxrender-dev \
    libxrandr-dev \
    x11-apps \
    clang-format \
    && rm -rf /var/lib/apt/lists/*

# Build notcurses
RUN cd /tmp && \
    git clone --depth=1 https://github.com/dankamongmen/notcurses.git && \
    cd notcurses && mkdir build && cd build && \
    cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DUSE_MULTIMEDIA=ffmpeg \
    -DUSE_DEFLATE=on && \
    make -j$(nproc) && \
    make install && \
    ldconfig && \
    cd / && rm -rf /tmp/notcurses

# Installa tema Typewritten via npm
RUN npm install -g typewritten

# Crea utente non-root
RUN useradd -m -s /usr/bin/zsh devuser && \
    echo "devuser ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER devuser
WORKDIR /home/devuser

# Installa Oh My Zsh
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended

# Installa plugin Zsh popolari
RUN git clone --depth=1 https://github.com/zsh-users/zsh-autosuggestions \
    ${HOME}/.oh-my-zsh/custom/plugins/zsh-autosuggestions && \
    git clone --depth=1 https://github.com/zsh-users/zsh-syntax-highlighting \
    ${HOME}/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting


# Copia configurazioni dall'host
COPY --chown=devuser:devuser ./dotfiles/.zshrc /home/devuser/.zshrc
COPY --chown=devuser:devuser ./dotfiles/.config/nvim /home/devuser/.config/nvim

# Pre-installa plugin Neovim (supporta lazy.nvim, packer, vim-plug)
RUN nvim --headless "+Lazy! sync" +qa 2>/dev/null || \
    nvim --headless "+PackerSync" +qa 2>/dev/null || \
    nvim --headless "+PlugInstall" +qa 2>/dev/null || true

WORKDIR /home/devuser/project

CMD ["/usr/bin/zsh"]
