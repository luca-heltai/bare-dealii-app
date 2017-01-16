#!/bin/bash
IMG=`grep image .gitlab-ci.yml | awk '{print $2}'` 
echo $IMG

CMD=`grep -e '- ' .gitlab-ci.yml | sed 's/- //'`

docker run -v `pwd`:/builds/luca-heltai/dealii-bare-app $IMG /bin/sh -c "$CMD" 
