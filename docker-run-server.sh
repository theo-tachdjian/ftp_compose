sudo docker run \
    --name lpf-server \
    --network lpf-ftpnet \
    --rm \
    lpf-server $@
