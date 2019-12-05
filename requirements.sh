#!/bin/bash
wget http://us-east-1.ec2.archive.ubuntu.com/ubuntu/pool/main/g/gmp/libgmpxx4ldbl_5.0.2+dfsg-2ubuntu1_amd64.deb http://us-east-1.ec2.archive.ubuntu.com/ubuntu/pool/main/g/gmp/libgmp10_5.0.2+dfsg-2ubuntu1_amd64.deb http://us-east-1.ec2.archive.ubuntu.com/ubuntu/pool/main/g/gmp/libgmp-dev_5.0.2+dfsg-2ubuntu1_amd64.deb http://us-east-1.ec2.archive.ubuntu.com/ubuntu/pool/main/g/gmp/libgmp3-dev_5.0.2+dfsg-2ubuntu1_amd64.deb
dpkg -i libgmpxx4ldbl_5.0.2+dfsg-2ubuntu1_amd64.deb libgmp10_5.0.2+dfsg-2ubuntu1_amd64.deb libgmp-dev_5.0.2+dfsg-2ubuntu1_amd64.deb libgmp3-dev_5.0.2+dfsg-2ubuntu1_amd64.deb

rm libgmpxx4ldbl_5.0.2+dfsg-2ubuntu1_amd64.deb libgmp10_5.0.2+dfsg-2ubuntu1_amd64.deb libgmp-dev_5.0.2+dfsg-2ubuntu1_amd64.deb libgmp3-dev_5.0.2+dfsg-2ubuntu1_amd64.deb
