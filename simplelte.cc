/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Manuel Requena <manuel.requena@cttc.es>
 */

 // to save a template default attribute file run it like this:
  // ./waf --command-template="%s --ns3::ConfigStore::Filename=input-defaults.txt --ns3::ConfigStore::Mode=Save --ns3::ConfigStore::FileFormat=RawText" --run scratch/simplelte
  //
  // to load a previously created default attribute file
  // ./waf --command-template="%s --ns3::ConfigStore::Filename=input-defaults.txt --ns3::ConfigStore::Mode=Load --ns3::ConfigStore::FileFormat=RawText" --run scratch/simplelte


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/config-store.h"
#include <ns3/buildings-helper.h>
#include "ns3/config-store.h"
 //#include "okumura-hata-propagation-loss-model.h"


using namespace ns3;

int main (int argc, char *argv[])
{	
  CommandLine cmd;
  cmd.Parse (argc, argv);
  ConfigStore inputConfig;
  inputConfig.ConfigureDefaults ();
  cmd.Parse (argc, argv);
  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();

  // Uncomment to enable logging
  // lteHelper->EnableLogComponents ();

  // Create Nodes: eNodeB and UE
  NodeContainer enbNodes;
  NodeContainer ueNodes;
  enbNodes.Create (2);
  ueNodes.Create (9);
   
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
  positionAlloc->Add (Vector(0.0,0.0,70.0));
  positionAlloc->Add (Vector(2500.0,0.0,70.0));
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator(positionAlloc);
  mobility.Install(enbNodes);

  Ptr<ListPositionAllocator> positionAlloc2 = CreateObject<ListPositionAllocator>();
  positionAlloc2->Add (Vector(1.0,1.0,68.0));
  positionAlloc2->Add (Vector(2.0,2.0,67.0));
  positionAlloc2->Add (Vector(3.0,1.0,66.0));
  positionAlloc2->Add (Vector(4.0,0.0,67.0));
  positionAlloc2->Add (Vector(2495.0,3.0,70.0));
  positionAlloc2->Add (Vector(2490.0,6.0,70.0));
  positionAlloc2->Add (Vector(2488.0,6.0,70.0));
  positionAlloc2->Add (Vector(2489.0,10.0,65.0));
  positionAlloc2->Add (Vector(2484.0,3.0,69.0));
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator(positionAlloc2);
  mobility.Install(ueNodes);
  
  // Install Mobility Model
  //mobility;
  //mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  //mobility.Install (enbNodes);
  //BuildingsHelper::Install (enbNodes);
  //mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  //mobility.Install (ueNodes);
  //BuildingsHelper::Install (ueNodes);

  // Create Devices and install them in the Nodes (eNB and UE)
  NetDeviceContainer enbDevs;
  NetDeviceContainer ueDevs;
  // Default scheduler is PF, uncomment to use RR
  //lteHelper->SetSchedulerType ("ns3::RrFfMacScheduler");

  enbDevs = lteHelper->InstallEnbDevice (enbNodes);
  ueDevs = lteHelper->InstallUeDevice (ueNodes);

  // Attach a UE to a eNB
  int indexer = 0;
  for(int i=0;i<9;i++){
  if (i==4) indexer = 1;
  lteHelper->Attach (ueDevs.Get(i), enbDevs.Get (indexer));
  }


  // Activate a data radio bearer
  enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
  EpsBearer bearer (q);
  lteHelper->ActivateDataRadioBearer (ueDevs, bearer);
  lteHelper->EnableTraces ();

  Simulator::Stop (Seconds (0.05));
  
  lteHelper->EnablePhyTraces();
  lteHelper->EnableMacTraces();
    
  Simulator::Run ();

  // GtkConfigStore config;
  // config.ConfigureAttributes ();

  Simulator::Destroy ();
  return 0;
}
