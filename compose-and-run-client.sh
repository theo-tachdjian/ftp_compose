#!/bin/bash
docker compose run \
    --rm \
    -v .:/home/client \
    lpf-client $@
