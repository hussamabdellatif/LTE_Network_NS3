# LTE_Network_NS3
An LTE network with 2 base stations, and 9 mobile stations, using Okumura-Hata propagation path-loss model for suburban areas.

<br>**********************************************************<br>
<br><br><h1>Instructions on how to simulate and execute: </h1><br>
<br>1) Move the file simplelte.cc into scratch directory inside ns-allinone-3.25/ns-3.25<br>
    2) Move the file input-defaults into ns-allinone-3.25/ns-3.25<br>
    3) Execute this command (in one line) inside the directory ns-allinone-3.25/ns-3.25 
          ./waf --command-template="%s --ns3::ConfigStore::Filename=input-defaults.txt --ns3::ConfigStore::Mode=Load --                  ns3::ConfigStore::FileFormat=RawText" --run scratch/simplelte 
 <br> 4) check output files....
     
