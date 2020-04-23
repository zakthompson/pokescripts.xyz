FROM node:13-alpine

RUN apk add --update-cache build-base gcc-avr avr-libc && rm -rf /var/cache/apk/*

WORKDIR /app

COPY package.json ./

RUN yarn

COPY bots/ ./bots
COPY routes/ ./routes
COPY utils/ ./utils
COPY index.js .
COPY client/build/ ./client/build

EXPOSE 5000
CMD [ "node" , "index.js" ]

