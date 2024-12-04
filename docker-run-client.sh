sudo docker run \
    -i \
    --name lpf-client \
    -v .:/home/client \
    --network lpf-ftpnet \
    --rm \
    lpf-client $@
