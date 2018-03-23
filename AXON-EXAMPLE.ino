// INITIAL FILE CREATED JANUARY 2018 by Simon Peace
// This is an example of how the objects of the Axon Library can be used to build
// a functioning Axon Footcontroller

// HARDWARE
#include "AxonKeyScanner.h"
#include "AxonExprScanner.h"
#include "AxonMidi.h"
#include "AxonTouchScreen.h"

// ACTIONS
#include "AxonSendMidiCCAction.h"
#include "AxonMacroAction.h"
#include "AxonContrastUpAction.h"
#include "AxonContrastDownAction.h"
#include "AxonContrastSetAction.h"
#include "AxonAFXXLPPresetUpAction.h"
#include "AxonAFXXLPPresetDownAction.h"
#include "AxonAFXXLPPresetNumberRequestAction.h"
#include "AxonAFXXLPPresetNameRequestAction.h"
#include "AxonAFXXLPPresetBlocksDataRequestAction.h"
#include "AxonAFXXLPTunerInfoAction.h"
#include "AxonStoreAFXXLPPresetNumberAction.h"
#include "AxonStoreAFXXLPPresetNameAction.h"
#include "AxonStoreAFXXLPSceneNumberAction.h"
#include "AxonShowMainScreenAction.h"
#include "AxonShowPresetNameAction.h"
#include "AxonShowPresetNumberAction.h"
#include "AxonShowSceneNumberAction.h"
#include "AxonShowTunerScreenAction.h"
#include "AxonSpoofHardwareSwitchEventAction.h"

//EVENTS
#include "AxonHardwareSwitchEvent.h"
#include "AxonSoftwareSwitchEvent.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAFXXLPSceneNumberEvent.h"
#include "AxonCCMidiEvent.h"
#include "AxonPCMidiEvent.h"
#include "AxonSongSelectMidiEvent.h"

// LOGIC BLOCKS
#include "AxonMomentarySwitchEventClient.h"
#include "AxonLatchingSwitchEventClient.h"
#include "AxonRadioSwitchGroupEventClient.h"
#include "AxonActionEventClient.h"
#include "AxonAFXXLPSysExEventClient.h"
#include "AxonLabelDisplayEventClient.h"

// ROUTING
#include "AxonEventManager.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

void TAP_TEMPO_FEATURE()
{
  // ACTIONS
  // *** AXEFX TAP TEMPO
  AxonSendMidiCCAction *AFXTapTempo = new AxonSendMidiCCAction();       // action to send a MIDI control Change
  AFXTapTempo->setNetwork( 0 );                                         // use network "0" MIDI physical port on rear of Axon
  AFXTapTempo->setChannel( 1 );                                         // my AFX is configured to be on MIDI Channel 1
  AFXTapTempo->setCC( 14 );                                             // AFX Tap Tempo is initiated with controller number 14
  AFXTapTempo->setVal( 0 );                                             // lets be good and initialise the value to ZERO ( not really required )  

  // LOGIC BLOCKS
  AxonMomentarySwitchEventClient *aSwitch = new AxonMomentarySwitchEventClient(0);						
  aSwitch->setOnAction( AFXTapTempo );                                             					// link the onAction hook to the action we want to execute
  
  AxonLabelDisplayEventClient *aScribble = new AxonLabelDisplayEventClient( 0, "TEMPO", "TEMPO" );	// create a display ZERO renderer with labels
}

void BAND_CONFIG_FEATURE()
{
  // ACTIONS
  AxonSendMidiCCAction *AFXExtern3 = new AxonSendMidiCCAction();        // action to send a MIDI control Change
  AFXExtern3->setNetwork( 0 );                                          // use network "0" MIDI physical port on rear of Axon
  AFXExtern3->setChannel( 1 );                                          // my AFX is configured to be on MIDI Channel 1
  AFXExtern3->setCC( 18 );                                              // Extern3 is initiated with controller number 18
  AFXExtern3->setVal( 85 );                                            // initialise to our static value that will always be sent
  AFXExtern3->fixVal( true );                                           // make the value fixed

  AxonSendMidiCCAction *AFXExtern4 = new AxonSendMidiCCAction();        // action to send a MIDI control Change
  AFXExtern4->setNetwork( 0 );                                          // use network "0" MIDI physical port on rear of Axon
  AFXExtern4->setChannel( 1 );                                          // my AFX is configured to be on MIDI Channel 1
  AFXExtern4->setCC( 19 );                                              // Extern4 is initiated with controller number 19
  AFXExtern4->setVal( 108 );                                             // initialise to our static value that will always be sent
  AFXExtern4->fixVal( true );                                           // make the value fixed

  AxonSendMidiCCAction *AFXExtern5 = new AxonSendMidiCCAction();        // action to send a MIDI control Change
  AFXExtern4->setNetwork( 0 );                                          // use network "0" MIDI physical port on rear of Axon
  AFXExtern4->setChannel( 1 );                                          // my AFX is configured to be on MIDI Channel 1
  AFXExtern4->setCC( 20 );                                              // Extern4 is initiated with controller number 19
  AFXExtern4->setVal( 85 );                                             // initialise to our static value that will always be sent
  AFXExtern4->fixVal( true );                                           // make the value fixed

  AxonMacroAction *ExternCTRLMacro = new AxonMacroAction();               // a macro to load with two sub actions
  ExternCTRLMacro->add( AFXExtern3 );                                   // add action
  ExternCTRLMacro->add( AFXExtern4 );                                   // add action

  // LOGIC BLOCKS
  AxonMomentarySwitchEventClient *aSwitch = new AxonMomentarySwitchEventClient(1);             // switch logic
  aSwitch->setOnAction( ExternCTRLMacro );                              // link the onAction hook to the macro (action) we want to execute
  
  AxonLabelDisplayEventClient *aScribble = new AxonLabelDisplayEventClient( 1, "CFG", "CFG" );                     // create a display ONE renderer with labels
}

void PRESET_FEATURE()
{
  // ACTIONS
  AxonAFXXLPPresetUpAction *AFXXLPPresetUp = new AxonAFXXLPPresetUpAction();					// this just increments the number held in memory
  AxonAFXXLPPresetDownAction *AFXXLPPresetDown = new AxonAFXXLPPresetDownAction();				// this just decrements the number held in memory

  AxonAFXXLPPresetNumberRequestAction *AFXXLPPresetNumberRequest = new AxonAFXXLPPresetNumberRequestAction();  // sends CC and PC as appropriate for the bank select and preset number
  AFXXLPPresetNumberRequest->setNetwork( 0 );                                                                // use network "0" MIDI physical port on rear of Axon
  AFXXLPPresetNumberRequest->setChannel( 1 );                                                                // my AFX is configured to be on MIDI Channel 1
 
  AxonMacroAction *AFXXLPPresetUpMacro = new AxonMacroAction();            // select next (+1) preset
  AFXXLPPresetUpMacro->add( AFXXLPPresetUp );
  AFXXLPPresetUpMacro->add( AFXXLPPresetNumberRequest );
  
  AxonMacroAction *AFXXLPPresetDownMacro = new AxonMacroAction();          // select previous (-1) preset
  AFXXLPPresetDownMacro->add( AFXXLPPresetDown );
  AFXXLPPresetDownMacro->add( AFXXLPPresetNumberRequest );

  // LOGIC BLOCKS
  AxonMomentarySwitchEventClient *PrevPresetSw = new AxonMomentarySwitchEventClient(2);
  PrevPresetSw->setOnAction( AFXXLPPresetDownMacro );                      // link the OnAction hook to the actions we want to execute
  
  AxonMomentarySwitchEventClient *NextPresetSw = new AxonMomentarySwitchEventClient(5);          
  NextPresetSw->setOnAction( AFXXLPPresetUpMacro );                        // link the OnAction hook to the actions we want to execute
  
  AxonLabelDisplayEventClient *PresetDownScribble = new AxonLabelDisplayEventClient( 2, "DOWN", "DOWN" );
  
  AxonLabelDisplayEventClient *PresetUpScribble = new AxonLabelDisplayEventClient( 5, "UP", "UP" );
}

void SWAP_GUITAR_FEATURE()
{
  // ACTIONS
  AxonMomentarySwitchEventClient *G75GuitarSelectorSw = new AxonMomentarySwitchEventClient(6);

  // LOGIC BLOCKS
  AxonLabelDisplayEventClient *GtrSwapScribble = new AxonLabelDisplayEventClient( 6, "G75", "G75" );
}

void TUNER_FEATURE()
{
  // ACTIONS
  // *** AXEFX TUNER *** 
  AxonSendMidiCCAction *AFXSendTuner = new AxonSendMidiCCAction();      	// action to send a MIDI control Change
  AFXSendTuner->setNetwork( 0 );                                            // use network "0" MIDI physical port on rear of Axon
  AFXSendTuner->setChannel( 1 );                                            // my AFX is configured to be on MIDI Channel 1
  AFXSendTuner->setCC( 15 );                                                // AFX Tap Tempo is initiated with controller number 15
  AFXSendTuner->setVal( 0 );                                                // lets be good and initialise the value to ZERO ( not really required )

  AxonShowTunerScreenAction *ShowTunerScreen = new AxonShowTunerScreenAction();
  AxonShowMainScreenAction *ShowMainScreen = new AxonShowMainScreenAction();

  AxonMacroAction *TunerOnMacro = new AxonMacroAction();                 	// this macro 
  TunerOnMacro->add( ShowTunerScreen );                                  	// display the tuner screen
  TunerOnMacro->add( AFXSendTuner );                                    	// turn on the axefx tuner

  AxonMacroAction *TunerOffMacro = new AxonMacroAction();                 	// this macro 
  TunerOffMacro->add( AFXSendTuner );                                   	// turn off the axefx tuner
  TunerOffMacro->add( ShowMainScreen );                                   	// display the main screen
  
  // LOGIC BLOCKS
  AxonLatchingSwitchEventClient *AFXTunerSw = new AxonLatchingSwitchEventClient(7);
  AFXTunerSw->setOnAction( TunerOnMacro );                              	// link the OnAction hook to the actions we want to execute
  AFXTunerSw->setOffAction( TunerOffMacro );                            	// line the OffAction hook to the actions we want to execute 

  AxonLabelDisplayEventClient *TunerScribble = new AxonLabelDisplayEventClient( 7, "TUNER", "TUNER" );
}

void DHOLD_FEATURE()
{
  // ACTIONS
  // *** CONFIGURE EXTERN 12
  AxonSendMidiCCAction *AFXExtern12 = new AxonSendMidiCCAction();       // action to send a MIDI control Change
  AFXExtern12->setNetwork( 0 );                                         // use network "0" MIDI physical port on rear of Axon
  AFXExtern12->setChannel( 1 );                                         // my AFX is configured to be on MIDI Channel 1
  AFXExtern12->setCC( 27 );                                             // AFX EXPR12 initiated with controller number 27
  AFXExtern12->setVal( 0 );                                             // lets be good and initialise the value to ZERO ( not really required )

  // LOGIC BLOCKS
  AxonLatchingSwitchEventClient  *DelayHoldSw = new AxonLatchingSwitchEventClient(8);            // switch logic
  DelayHoldSw->setOnAction( AFXExtern12 );                              // link the onAction hook to the action we want to execute
  DelayHoldSw->setOffAction( AFXExtern12 );                             // line the OffAction hook to the actions we want to execute
  
  AxonLabelDisplayEventClient *DHoldScribble = new AxonLabelDisplayEventClient( 9, "<DHLD", "<DHLD" );               // middle row etc...
}

void CONTRAST_FEATURE()
{
  // ACTIONS
  // *** ACTIONS TO ADJUST CONTRAST OF MAIN SCREEN
  AxonContrastUpAction *TSContrastUp = new AxonContrastUpAction();
  AxonContrastDownAction *TSContrastDown = new AxonContrastDownAction();
  AxonContrastSetAction *TSSetContrast = new AxonContrastSetAction();

  // LOGIC BLOCKS
  AxonMomentarySwitchEventClient *ContrastDownSw = new AxonMomentarySwitchEventClient(10);        // switch logic
  ContrastDownSw->setOnAction( TSContrastDown );                          // link the onAction hook to the action we want to execute
  
  AxonMomentarySwitchEventClient *ContrastUpSw = new AxonMomentarySwitchEventClient(11);          // switch logic
  ContrastUpSw->setOnAction( TSContrastUp );                              // link the onAction hook to the action we want to execute
  

  AxonLabelDisplayEventClient *ContrastDownScribble = new AxonLabelDisplayEventClient( 10, "C DN", "C DN" );                 // etc...
  AxonLabelDisplayEventClient *ContrastUpScribble = new AxonLabelDisplayEventClient( 11, "C UP", "C UP" );                 // etc...
}

void BANDHELPER_PREV_FEATURE()
{
  // ACTIONS
  // *** BANDHELPER GENERAL BUTTON 80
  AxonSendMidiCCAction *BandhelperGeneral1 = new AxonSendMidiCCAction();  // action to send a MIDI Control Change
  BandhelperGeneral1->setNetwork( 1 );                                    // use network "1" (the 2nd) MIDI physical port on rear of Axon
  BandhelperGeneral1->setChannel( 1 );                                    // Bandhelper is configured to be on MIDI Channel 1
  BandhelperGeneral1->setCC( 80 );                                        // General Button 1 is CC 80
  BandhelperGeneral1->setVal( 0 );                                        // lets be good and initialise the value to ZERO ( not really required )

  // LOGIC BLOCKS
  AxonMomentarySwitchEventClient *BandhelperPreviousSw = new AxonMomentarySwitchEventClient(12);  // switch logic
  BandhelperPreviousSw->setOnAction( BandhelperGeneral1 );          // link the onAction hook to the action we want to execute
  AxonLabelDisplayEventClient *BandHelperPrevScribble = new AxonLabelDisplayEventClient( 12, "PREV", "PREV" );                 // etc...
}

void BANDHELPER_STOP_FEATURE()
{
  // ACTIONS
  AxonSendMidiCCAction *BandhelperGeneral2 = new AxonSendMidiCCAction();  // action to send a MIDI Control Change
  BandhelperGeneral2->setNetwork( 1 );                                    // use network "1" (the 2nd) MIDI physical port on rear of Axon
  BandhelperGeneral2->setChannel( 1 );                                    // Bandhelper is configured to be on MIDI Channel 1
  BandhelperGeneral2->setCC( 82 );                                        // General Button 2 is CC 81
  BandhelperGeneral2->setVal( 0 );                                        // lets be good and initialise the value to ZERO ( not really required )

  // LOGIC BLOCKS
  AxonMomentarySwitchEventClient *BandhelperStopSw = new AxonMomentarySwitchEventClient(13);      // switch logic
  BandhelperStopSw->setOnAction( BandhelperGeneral2 );              // link the onAction hook to the action we want to execute
  AxonLabelDisplayEventClient *BandHelperStopScribble = new AxonLabelDisplayEventClient( 13, "STOP", "STOP" );                 // etc...
}

void BANDHELPER_NEXT_FEATURE()
{
  // ACTIONS
  // *** BANDHELPER GENERAL BUTTON 82
  AxonSendMidiCCAction *BandhelperGeneral3 = new AxonSendMidiCCAction();  // action to send a MIDI Control Change
  BandhelperGeneral3->setNetwork( 1 );                                    // use network "1" (the 2nd) MIDI physical port on rear of Axon
  BandhelperGeneral3->setChannel( 1 );                                    // Bandhelper is configured to be on MIDI Channel 1
  BandhelperGeneral3->setCC( 81 );                                        // General Button 3 is CC 82
  BandhelperGeneral3->setVal( 0 );                                        // lets be good and initialise the value to ZERO ( not really required )

  // LOGIC BLOCKS
  AxonMomentarySwitchEventClient *BandhelperNextSw = new AxonMomentarySwitchEventClient(14);      // switch logic
  BandhelperNextSw->setOnAction( BandhelperGeneral3 );              // link the onAction hook to the action we want to execute
  AxonLabelDisplayEventClient *BandHelperNextScribble = new AxonLabelDisplayEventClient( 14, "NEXT", "NEXT" );                 // etc...
}

void BANDHELPER_START_FEATURE()
{
  // ACTIONS
  // *** BANDHELPER GENERAL BUTTON 83
  AxonSendMidiCCAction *BandhelperGeneral4 = new AxonSendMidiCCAction();  // action to send a MIDI Control Change
  BandhelperGeneral4->setNetwork( 1 );                                    // use network "1" (the 2nd) MIDI physical port on rear of Axon
  BandhelperGeneral4->setChannel( 1 );                                    // Bandhelper is configured to be on MIDI Channel 1
  BandhelperGeneral4->setCC( 83 );                                        // General Button 4 is CC 83
  BandhelperGeneral4->setVal( 0 );                                        // lets be good and initialise the value to ZERO ( not really required )

  // LOGIC BLOCKS
  AxonMomentarySwitchEventClient *BandhelperStartSw = new AxonMomentarySwitchEventClient(15);     // switch logic
  BandhelperStartSw->setOnAction( BandhelperGeneral4 );             // link the onAction hook to the action we want to execute
  AxonLabelDisplayEventClient *BandHelperStartScribble = new AxonLabelDisplayEventClient( 15, "START", "START" );               // etc...
}

void AXEFX_SCENES_FEATURE()
{
  // ACTIONS
  AxonSendMidiCCAction *AFXSendSceneChange = new AxonSendMidiCCAction();    // action to send a MIDI Control Change
  AFXSendSceneChange->setNetwork( 0 );                                      // use network "0" MIDI physical port on rear of Axon
  AFXSendSceneChange->setChannel( 1 );                                      // my AFX is configured to be on MIDI Channel 1
  AFXSendSceneChange->setCC( 34 );                                          // AFX Scene Changes are initiated with controller number 34
  AFXSendSceneChange->setVal( 0 );                                          // lets be good and initialise the value to ZERO ( not really required )
 
  // LOGIC BLOCKS
  AxonRadioSwitchGroupEventClient *AFXXLPSceneGroup = new AxonRadioSwitchGroupEventClient( 40 ); // group switch 40 is the output software virtual switch number...
  AFXXLPSceneGroup->addSwitch( 16 );              // Radio group reacts to and tracks each hardware input added
  AFXXLPSceneGroup->addSwitch( 17 );              // the order that the buttons are added to the group
  AFXXLPSceneGroup->addSwitch( 18 );              // is important as it affects the output value
  AFXXLPSceneGroup->addSwitch( 19 );              // of the radio group switch message
  AFXXLPSceneGroup->addSwitch( 20 );              // the output value is 0 through to the maximum
  AFXXLPSceneGroup->addSwitch( 21 );              // number of client registrations
  AFXXLPSceneGroup->addSwitch( 22 );              // in this case 0..7
  AFXXLPSceneGroup->addSwitch( 23 );              // which is what we want for the AXEFX Scene Change Action
  AFXXLPSceneGroup->setOnChangeAction( AFXSendSceneChange );             // link the onChangeAction hook to the action we want to execute
  
  AxonLabelDisplayEventClient *Scene1Scribble = new AxonLabelDisplayEventClient( 16, "SCN 1", "" );                    // bottom row etc...
  AxonLabelDisplayEventClient *Scene2Scribble = new AxonLabelDisplayEventClient( 17, "SCN 2", "" );                    // etc...
  AxonLabelDisplayEventClient *Scene3Scribble = new AxonLabelDisplayEventClient( 18, "SCN 3", "" );                    // etc...
  AxonLabelDisplayEventClient *Scene4Scribble = new AxonLabelDisplayEventClient( 19, "SCN 4", "" );                    // etc...
  AxonLabelDisplayEventClient *Scene5Scribble = new AxonLabelDisplayEventClient( 20, "SCN 5", "" );                    // etc...
  AxonLabelDisplayEventClient *Scene6Scribble = new AxonLabelDisplayEventClient( 21, "SCN 6", "" );                    // etc...
  AxonLabelDisplayEventClient *Scene7Scribble = new AxonLabelDisplayEventClient( 22, "SCN 7", "" );                    // etc...
  AxonLabelDisplayEventClient *Scene8Scribble = new AxonLabelDisplayEventClient( 23, "SCN 8", "" );                    // etc...
}

void EXPRESSION_PEDAL1_FEATURE()
{
  // ACTIONS
  AxonSendMidiCCAction *AFXExtern1 = new AxonSendMidiCCAction();        // action to send a MIDI control Change
  AFXExtern1->setNetwork( 0 );                                          // use network "0" MIDI physical port on rear of Axon
  AFXExtern1->setChannel( 1 );                                          // my AFX is configured to be on MIDI Channel 1
  AFXExtern1->setCC( 16 );                                              // Extern1 is initiated with controller number 16
  AFXExtern1->setVal( 0 );                                              // lets be good and initialise the value to ZERO ( not really required )

  AxonExprScanner::instance()->setOnExpr1Change( AFXExtern1 );
}

void EXPRESSION_PEDAL2_FEATURE()
{
  // ACTIONS
  AxonSendMidiCCAction *AFXExtern2 = new AxonSendMidiCCAction();        // action to send a MIDI control Change
  AFXExtern2->setNetwork( 0 );                                          // use network "0" MIDI physical port on rear of Axon
  AFXExtern2->setChannel( 1 );                                          // my AFX is configured to be on MIDI Channel 1
  AFXExtern2->setCC( 17 );                                              // Extern2 is initiated with controller number 17
  AFXExtern2->setVal( 0 );                                              // lets be good and initialise the value to ZERO ( not really required )

  AxonExprScanner::instance()->setOnExpr2Change( AFXExtern2 );
}

void EXPRESSION_PEDAL3_FEATURE()
{
  // ACTIONS
  AxonSendMidiCCAction *AFXExtern5 = new AxonSendMidiCCAction();        // action to send a MIDI control Change
  AFXExtern5->setNetwork( 0 );                                          // use network "0" MIDI physical port on rear of Axon
  AFXExtern5->setChannel( 1 );                                          // my AFX is configured to be on MIDI Channel 1
  AFXExtern5->setCC( 20 );                                              // Extern5 is initiated with controller number 20
  AFXExtern5->setVal( 0 );                                              // lets be good and initialise the value to ZERO ( not really required )

  AxonExprScanner::instance()->setOnExpr3Change( AFXExtern5 );
}

void EXPRESSION_PEDAL4_FEATURE()
{
  // ACTIONS
  AxonSendMidiCCAction *AFXExtern6 = new AxonSendMidiCCAction();        // action to send a MIDI control Change
  AFXExtern6->setNetwork( 0 );                                          // use network "0" MIDI physical port on rear of Axon
  AFXExtern6->setChannel( 1 );                                          // my AFX is configured to be on MIDI Channel 1
  AFXExtern6->setCC( 21 );                                              // Extern6 is initiated with controller number 21
  AFXExtern6->setVal( 0 );                                              // lets be good and initialise the value to ZERO ( not really required )

  AxonExprScanner::instance()->setOnExpr4Change( AFXExtern6 );
}

void AXEFX_CORE_FEATURES()
{
  // ACTIONS
  AxonAFXXLPTunerInfoAction *AFXTunerInfoRxdAction = new AxonAFXXLPTunerInfoAction();                   						// this updates the main screen parameters with Tuner Info

  AxonAFXXLPPresetBlocksDataRequestAction *AFXXLPPresetBlocksDataRequestAction = new AxonAFXXLPPresetBlocksDataRequestAction();	// requests blocks data from AxeFX XL Plus
  AFXXLPPresetBlocksDataRequestAction->setNetwork(0);

  AxonAFXXLPPresetNameRequestAction *AFXXLPPresetNameRequest = new AxonAFXXLPPresetNameRequestAction();    						// sends hardware specific SYSTEM EXCLUSIVE message to AFX
  AFXXLPPresetNameRequest->setNetwork( 0 );
  
  AxonStoreAFXXLPPresetNumberAction *StoreAFXXLPPresetNumberAction = new AxonStoreAFXXLPPresetNumberAction();					// stores an AxeFX Preset number when it is received from AFXXLP
  AxonStoreAFXXLPPresetNameAction *StoreAFXXLPPresetNameAction = new AxonStoreAFXXLPPresetNameAction();							// stores an AxeFX Preset name when received
  AxonShowPresetNumberAction *ShowPresetNumberAction = new AxonShowPresetNumberAction();										// shows the AxeFX Preset number (read from memory)
  AxonShowPresetNameAction *ShowPresetNameAction = new AxonShowPresetNameAction();												// shows the AxeFX Preset name (read from memory)
  AxonStoreAFXXLPSceneNumberAction *StoreAFXXLPSceneNumberAction = new AxonStoreAFXXLPSceneNumberAction();						// stores an AxeFX Scene number when received
  AxonShowSceneNumberAction *ShowSceneNumberAction = new AxonShowSceneNumberAction();											// shows the AxeFX Scene number (read from memory)
  
  AxonSpoofHardwareSwitchEventAction *spoofHardware16SwitchOnAction = new AxonSpoofHardwareSwitchEventAction();					// ability to make an input act like a switch was pressed at the
  spoofHardware16SwitchOnAction->setSwitchNumber( 16 );																			// hardware layer
  spoofHardware16SwitchOnAction->setSwitchState( true );																		// currently just a static state true or false supported
  
  AxonSpoofHardwareSwitchEventAction *spoofHardware17SwitchOnAction = new AxonSpoofHardwareSwitchEventAction(); 				// ability to make an input act like a switch was pressed at the
  spoofHardware17SwitchOnAction->setSwitchNumber( 17 );                                                         				// hardware layer
  spoofHardware17SwitchOnAction->setSwitchState( true );                                                        				// currently just a static state true or false supported
  
  AxonSpoofHardwareSwitchEventAction *spoofHardware18SwitchOnAction = new AxonSpoofHardwareSwitchEventAction(); 				// ability to make an input act like a switch was pressed at the
  spoofHardware18SwitchOnAction->setSwitchNumber( 18 );                                                         				// hardware layer
  spoofHardware18SwitchOnAction->setSwitchState( true );                                                        				// currently just a static state true or false supported

  AxonSpoofHardwareSwitchEventAction *spoofHardware19SwitchOnAction = new AxonSpoofHardwareSwitchEventAction(); 				// ability to make an input act like a switch was pressed at the
  spoofHardware19SwitchOnAction->setSwitchNumber( 19 );                                                         				// hardware layer
  spoofHardware19SwitchOnAction->setSwitchState( true );                                                        				// currently just a static state true or false supported

  AxonSpoofHardwareSwitchEventAction *spoofHardware20SwitchOnAction = new AxonSpoofHardwareSwitchEventAction(); 				// ability to make an input act like a switch was pressed at the
  spoofHardware20SwitchOnAction->setSwitchNumber( 20 );                                                         				// hardware layer
  spoofHardware20SwitchOnAction->setSwitchState( true );                                                        				// currently just a static state true or false supported

  AxonSpoofHardwareSwitchEventAction *spoofHardware21SwitchOnAction = new AxonSpoofHardwareSwitchEventAction(); 				// ability to make an input act like a switch was pressed at the
  spoofHardware21SwitchOnAction->setSwitchNumber( 21 );                                                         				// hardware layer
  spoofHardware21SwitchOnAction->setSwitchState( true );                                                        				// currently just a static state true or false supported

  AxonSpoofHardwareSwitchEventAction *spoofHardware22SwitchOnAction = new AxonSpoofHardwareSwitchEventAction(); 				// ability to make an input act like a switch was pressed at the
  spoofHardware22SwitchOnAction->setSwitchNumber( 22 );                                                         				// hardware layer
  spoofHardware22SwitchOnAction->setSwitchState( true );                                                        				// currently just a static state true or false supported

  AxonSpoofHardwareSwitchEventAction *spoofHardware23SwitchOnAction = new AxonSpoofHardwareSwitchEventAction(); 				// ability to make an input act like a switch was pressed at the
  spoofHardware23SwitchOnAction->setSwitchNumber( 23 );                                                         				// hardware layer
  spoofHardware23SwitchOnAction->setSwitchState( true );                                                        				// currently just a static state true or false supported

  AxonMacroAction *PresetNumberRxAction = new AxonMacroAction();	 // When a Preset Number is received...
  PresetNumberRxAction->add( StoreAFXXLPPresetNumberAction );        // store the preset number...
  PresetNumberRxAction->add( ShowPresetNumberAction );               // show on the main screen...
  PresetNumberRxAction->add( AFXXLPPresetNameRequest );              // ask to for an up to date preset name
  PresetNumberRxAction->add( AFXXLPPresetBlocksDataRequestAction );  // ask for preset blocks information

  AxonMacroAction *PresetNameRxAction = new AxonMacroAction();       // When a Preset Name is received...
  PresetNameRxAction->add( StoreAFXXLPPresetNameAction );            // store the preset name...
  PresetNameRxAction->add( ShowPresetNameAction );                   // show on the main screen.

  AxonMacroAction *SceneNumberRxAction = new AxonMacroAction();      // When scene number is received
  SceneNumberRxAction->add( StoreAFXXLPSceneNumberAction );          // store the scene number...
  SceneNumberRxAction->add( ShowSceneNumberAction );                 // show on the main screen.
	
  // LOGIC BLOCKS
  AxonAFXXLPSysExEventClient *AFXXLPSysExEventClient = new AxonAFXXLPSysExEventClient();  // Class which handles all AXEFX System Exclusive messages generating both events and action plug points
  AFXXLPSysExEventClient->onTunerInfoRxd( AFXTunerInfoRxdAction );                        // when tuner information is received run the macro
  AFXXLPSysExEventClient->onFrontPanelChangeRxd( AFXXLPPresetBlocksDataRequestAction );   // when front panel change messages are received ask for updated blocks this also generates a scene number message
  AFXXLPSysExEventClient->onPresetNumberRxd( PresetNumberRxAction );                      // when a preset number is received run the macro
  AFXXLPSysExEventClient->onPresetNameRxd( PresetNameRxAction );                          // when a preset name is received run the macro
  AFXXLPSysExEventClient->onSceneNumberRxd( SceneNumberRxAction );                        // when scene number received run the macro
  AFXXLPSysExEventClient->onScene1Rxd( spoofHardware16SwitchOnAction );					  // when a scene 1 is decoded run this action 
  AFXXLPSysExEventClient->onScene2Rxd( spoofHardware17SwitchOnAction );					  // when a scene 2 is decoded run this action
  AFXXLPSysExEventClient->onScene3Rxd( spoofHardware18SwitchOnAction );					  // when a scene 3 is decoded run this action
  AFXXLPSysExEventClient->onScene4Rxd( spoofHardware19SwitchOnAction );					  // when a scene 4 is decoded run this action 
  AFXXLPSysExEventClient->onScene5Rxd( spoofHardware20SwitchOnAction );					  // when a scene 5 is decoded run this action
  AFXXLPSysExEventClient->onScene6Rxd( spoofHardware21SwitchOnAction );					  // when a scene 6 is decoded run this action
  AFXXLPSysExEventClient->onScene7Rxd( spoofHardware22SwitchOnAction );					  // when a scene 7 is decoded run this action
  AFXXLPSysExEventClient->onScene8Rxd( spoofHardware23SwitchOnAction );					  // when a scene 8 is decoded run this action

//  AFXXLPSysExEventClient->onPresetBlocksDataRxd                                           // when block information received run the macro
}

void SJP_TESTING_FEATURES()
{
	// ACTIONS
	AxonSendMidiCCAction *Regen1 = new AxonSendMidiCCAction();        // action to send a MIDI control Change
	Regen1->setNetwork( 1 );                                          // use network "0" MIDI physical port on rear of Axon
	Regen1->setChannel( 2 );                                          // my AFX is configured to be on MIDI Channel 1
	Regen1->setCC( 7 );                                              // Extern5 is initiated with controller number 20
	Regen1->setVal( 0 );                                              // lets be good and initialise the value to ZERO ( not really required )

	AxonActionEventClient *aClient = new AxonActionEventClient();
	aClient->setOnChangeAction( Regen1 );


	AxonCCMidiEvent *CCEvent = new AxonCCMidiEvent();
	CCEvent->setNetwork( 1 );
	CCEvent->setChannel( 1 );
	CCEvent->setCC( 7 );
	AxonPCMidiEvent *PCEvent = new AxonPCMidiEvent();
	PCEvent->setNetwork( 1 );
	PCEvent->setChannel( 1 );
	PCEvent->setPC( 5 );
	AxonSongSelectMidiEvent *SSEvent = new AxonSongSelectMidiEvent();
	SSEvent->setNetwork( 1 );
	SSEvent->setSongNumber( 3 );
	
	AxonEventManager::instance()->clientRegister( aClient, SSEvent );
	AxonEventManager::instance()->clientRegister( aClient, PCEvent );
	AxonEventManager::instance()->clientRegister( aClient, CCEvent );
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println( "START..." );
  
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif

  AxonTouchScreen::instance()->initialise();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif

// CONFIGURATION CODE STARTS HERE...
  

  TAP_TEMPO_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  BAND_CONFIG_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  PRESET_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  SWAP_GUITAR_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  TUNER_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  DHOLD_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  CONTRAST_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  BANDHELPER_PREV_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  BANDHELPER_STOP_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  BANDHELPER_NEXT_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  BANDHELPER_START_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  AXEFX_SCENES_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  EXPRESSION_PEDAL1_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  EXPRESSION_PEDAL2_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  EXPRESSION_PEDAL3_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  EXPRESSION_PEDAL4_FEATURE();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  AXEFX_CORE_FEATURES();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
  SJP_TESTING_FEATURES();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif


	

// CONFIGURATION CODE COMPLETE...
    
  AxonTouchScreen::instance()->showMainScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  static AxonEventManager *EvMgr = AxonEventManager::instance();            // hold a static instance pointer to the singleton Event Manager (so we don't have to query all the time)
  static AxonKeyScanner *KeyScanner = AxonKeyScanner::instance();           // hold a static.....           ..to the singleton KeyScanner
  static AxonExprScanner *ExprScanner = AxonExprScanner::instance();        // ...........                  ..to the singleton Expression Pedal Scanner
  static AxonMidi *MidiScanner = AxonMidi::instance();                      // .................           ...to the singleton MIDI implementation
  
  KeyScanner->check();                                                      // self throttled and generates all the hardware events from physical switches
  EvMgr->processQueue();                                                    // Process the Event Queue
  ExprScanner->check();                                                     // self throttled and generates hardware events from the analog input ports
  MidiScanner->read();                                                      // process incoming MIDI messaging from serial ports

#ifdef DEBUG_OBJECT_CREATE_DESTROY
  AxonCheckMem::instance()->check();
#endif
}
