#!/bin/bash

VNUM=$1

cd client
yarn build
cd ..
docker build -t pleebz/pokemon-hex-generator:$VNUM .
docker push pleebz/pokemon-hex-generator:$VNUM
kubectl apply -f deploy/service.yaml
