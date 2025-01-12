FROM node:18-slim

ENV allowedDomains="localhost"
ENV APP_URL="http://localhost:3000"
ENV FLAG="inctfj{P3RH4P5_E330RS_W3R3_TH3_W4Y_T0_5UCC33D}"

RUN apt-get update && apt-get install -y \
    wget \
    ca-certificates \
    fontconfig \
    libx11-dev \
    libxcomposite1 \
    libxrandr2 \
    libxtst6 \
    libappindicator3-1 \
    libnss3 \
    libgdk-pixbuf2.0-0 \
    libgbm1 \
    libxss1 \
    libasound2 \
    libatk-bridge2.0-0 \
    libatk1.0-0 \
    libnspr4 \
    libxdamage1 \
    libpangocairo-1.0-0 \
    libpango-1.0-0 \
    libgl1-mesa-glx \
    libegl1-mesa \
    libvulkan1 \
    --no-install-recommends \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

COPY ./src/package*.json ./

RUN npm install

COPY ./src .

EXPOSE 3000

CMD ["npm", "start"]

