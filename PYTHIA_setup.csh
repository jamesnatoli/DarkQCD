#!/bin/csh
setenv MYLOCATION  `pwd`
echo $MYLOCATION


setenv CMSSCE /home/eno/CMSSW_5_3_29/

cd $CMSSCE
cmsenv
cd $MYLOCATION
setenv PYTHIA8DATA /data/users/eno/pythiaDARK8183/xmldoc
setenv PYTHIA8 /data/users/eno/pythiaDARK8183/

setenv  LD_LIBRARY_PATH ${PYTHIA8}/lib:${LD_LIBRARY_PATH}

echo "done"
