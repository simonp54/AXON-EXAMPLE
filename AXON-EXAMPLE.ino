// INITIAL FILE CREATED JANUARY 2018 by Simon Peace
// This is an example of how the objects of the Axon Library can be used to build
// a functioning Axon Footcontroller

/*
	****************************************************************
	* Example Arduino Sketch for the Axon Midi Controller Platform *
	****************************************************************
*/

// HARDWARE
#include "AxonKeyScanner.h"
#include "AxonExprScanner.h"
#include "AxonMidi.h"
#include "AxonTouchScreen.h"

// ACTIONS
#include "AxonSendMidiCCAction.h"
#include "AxonSendMidiPCAction.h"
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

// new ACTIONS yet to be "fully accepted"
#include "AxonLabelDisplayAction.h"
#include "AxonMomentarySwitchAction.h"
#include "AxonLatchingSwitchAction.h"
#include "AxonRadioSwitchAction.h"
#include "AxonRadioSwitchGroupAction.h"
#include "AxonAFXXLPSysExAction.h"
#include "AxonU2BabyMemoryMapAction.h"

//EVENTS
#include "AxonHardwareSwitchEvent.h"
#include "AxonSoftwareSwitchEvent.h"
#include "AxonSysExMidiEvent.h"
#include "AxonAFXXLPSceneNumberEvent.h"
#include "AxonCCMidiEvent.h"
#include "AxonPCMidiEvent.h"
#include "AxonSongSelectMidiEvent.h"

#include "AxonDebugDefines.h"
#include "AxonCheckMem.h"

void TAP_TEMPO_FEATURE()
{
	Serial.println("TAP_TEMPO_FEATURE");
	// ACTIONS
	// *** AXEFX TAP TEMPO
	AxonSendMidiCCAction *AFXTapTempo = new AxonSendMidiCCAction();       // action to send a MIDI control Change
	AFXTapTempo->setNetwork( 0 );                                         // use network "0" MIDI physical port on rear of Axon
	AFXTapTempo->setChannel( 1 );                                         // my AFX is configured to be on MIDI Channel 1
	AFXTapTempo->setCC( 14 );                                             // AFX Tap Tempo is initiated with controller number 14
	AFXTapTempo->setVal( 0 );                                             // lets be good and initialise the value to ZERO ( not really required )  

	// LOGIC BLOCKS
	AxonLabelDisplayAction *aScribble = new AxonLabelDisplayAction( 0, "TEMPO", "TEMPO" );	// create a display ZERO renderer with labels

	AxonMomentarySwitchAction *aSwitch = new AxonMomentarySwitchAction();
	aSwitch->setOnAction( AFXTapTempo );
	aSwitch->setChangeAction( aScribble );
	AxonKeyScanner::instance()->setOnKeyScan0( aSwitch );
}

void BAND_CONFIG_FEATURE()
{
	Serial.println("BAND_CONFIG_FEATURE");
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
	AxonLabelDisplayAction *aScribble = new AxonLabelDisplayAction( 1, "CFG", "CFG" );                     // create a display ONE renderer with labels

	AxonMomentarySwitchAction *aSwitch = new AxonMomentarySwitchAction();
	aSwitch->setOnAction( ExternCTRLMacro );
	aSwitch->setChangeAction( aScribble );
	AxonKeyScanner::instance()->setOnKeyScan1( aSwitch );
}

void PRESET_FEATURE()
{
	Serial.println("PRESET_FEATURE");
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
	AxonLabelDisplayAction *PresetDownScribble = new AxonLabelDisplayAction( 2, "DOWN", "DOWN" );

	AxonLabelDisplayAction *PresetUpScribble = new AxonLabelDisplayAction( 5, "UP", "UP" );

	AxonMomentarySwitchAction *PrevPresetSw = new AxonMomentarySwitchAction();
	PrevPresetSw->setOnAction( AFXXLPPresetDownMacro );
	PrevPresetSw->setChangeAction( PresetDownScribble );
	AxonKeyScanner::instance()->setOnKeyScan2( PrevPresetSw );
	
	AxonMomentarySwitchAction *NextPresetSw = new AxonMomentarySwitchAction();
	NextPresetSw->setOnAction( AFXXLPPresetUpMacro );
	NextPresetSw->setChangeAction( PresetUpScribble );
	AxonKeyScanner::instance()->setOnKeyScan5( NextPresetSw );
}

void SWAP_GUITAR_FEATURE()
{
	Serial.println("SWAP_GUITAR_FEATURE");

	// LOGIC BLOCKS
	AxonLabelDisplayAction *GtrSwapScribble = new AxonLabelDisplayAction( 6, "G75", "G75" );

	AxonMomentarySwitchAction *aSwitch = new AxonMomentarySwitchAction();
	aSwitch->setOnAction( NULL );
	aSwitch->setChangeAction( GtrSwapScribble );
	AxonKeyScanner::instance()->setOnKeyScan6( aSwitch );
}

void TUNER_FEATURE()
{
	Serial.println("TUNER_FEATURE");
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

	
	AxonLabelDisplayAction *TunerScribble = new AxonLabelDisplayAction( 7, "TUNER", "TUNER" );

	AxonLatchingSwitchAction *aSwitch = new AxonLatchingSwitchAction();
	aSwitch->setOnAction( TunerOnMacro );
	aSwitch->setOffAction( TunerOffMacro );
	aSwitch->setChangeAction( TunerScribble );
	AxonKeyScanner::instance()->setOnKeyScan7( aSwitch );
}

void DHOLD_FEATURE()
{
	Serial.println("DHOLD_FEATURE");
	// ACTIONS
	// *** CONFIGURE EXTERN 12
	AxonSendMidiCCAction *AFXExtern12 = new AxonSendMidiCCAction();       // action to send a MIDI control Change
	AFXExtern12->setNetwork( 0 );                                         // use network "0" MIDI physical port on rear of Axon
	AFXExtern12->setChannel( 1 );                                         // my AFX is configured to be on MIDI Channel 1
	AFXExtern12->setCC( 27 );                                             // AFX EXPR12 initiated with controller number 27
	AFXExtern12->setVal( 0 );                                             // lets be good and initialise the value to ZERO ( not really required )

	// LOGIC BLOCKS
	AxonLabelDisplayAction *DHoldScribble = new AxonLabelDisplayAction( 8, "D HLD", "D HLD" );               // middle row etc...

	AxonLatchingSwitchAction *aSwitch = new AxonLatchingSwitchAction();
	aSwitch->setOnAction( AFXExtern12 );
	aSwitch->setOffAction( AFXExtern12 );
	aSwitch->setChangeAction( DHoldScribble );
	AxonKeyScanner::instance()->setOnKeyScan8( aSwitch );
}

void CONTRAST_FEATURE()
{
	Serial.println("CONTRAST_FEATURE");
	// ACTIONS
	// *** ACTIONS TO ADJUST CONTRAST OF MAIN SCREEN
	AxonContrastUpAction *TSContrastUp = new AxonContrastUpAction();
	AxonContrastDownAction *TSContrastDown = new AxonContrastDownAction();
	AxonContrastSetAction *TSSetContrast = new AxonContrastSetAction();

	// LOGIC BLOCKS
	AxonLabelDisplayAction *ContrastDownScribble = new AxonLabelDisplayAction( 10, "C DN", "C DN" );                 // etc...
	AxonLabelDisplayAction *ContrastUpScribble = new AxonLabelDisplayAction( 11, "C UP", "C UP" );                 // etc...

	AxonMomentarySwitchAction *ContrastDownSw = new AxonMomentarySwitchAction();
	ContrastDownSw->setOnAction( TSContrastDown );
	ContrastDownSw->setChangeAction( ContrastDownScribble );
	AxonKeyScanner::instance()->setOnKeyScan10( ContrastDownSw );

	AxonMomentarySwitchAction *ContrastUpSw = new AxonMomentarySwitchAction();
	ContrastUpSw->setOnAction( TSContrastUp );
	ContrastUpSw->setChangeAction( ContrastUpScribble );
	AxonKeyScanner::instance()->setOnKeyScan11( ContrastUpSw );
}

void BANDHELPER_PREV_FEATURE()
{
	Serial.println("BANDHELPER_PREV_FEATURE");
	// ACTIONS
	// *** BANDHELPER GENERAL BUTTON 80
	AxonSendMidiCCAction *BandhelperGeneral1 = new AxonSendMidiCCAction();  // action to send a MIDI Control Change
	BandhelperGeneral1->setNetwork( 1 );                                    // use network "1" (the 2nd) MIDI physical port on rear of Axon
	BandhelperGeneral1->setChannel( 1 );                                    // Bandhelper is configured to be on MIDI Channel 1
	BandhelperGeneral1->setCC( 80 );                                        // General Button 1 is CC 80
	BandhelperGeneral1->setVal( 0 );                                        // lets be good and initialise the value to ZERO ( not really required )

	// LOGIC BLOCKS
	AxonLabelDisplayAction *BandHelperPrevScribble = new AxonLabelDisplayAction( 12, "PREV", "PREV" );                 // etc...

	AxonMomentarySwitchAction *BandhelperPreviousSw = new AxonMomentarySwitchAction();
	BandhelperPreviousSw->setOnAction( BandhelperGeneral1 );
	BandhelperPreviousSw->setChangeAction( BandHelperPrevScribble );
	AxonKeyScanner::instance()->setOnKeyScan12( BandhelperPreviousSw );
}

void BANDHELPER_STOP_FEATURE()
{
	Serial.println("BANDHELPER_STOP_FEATURE");
	// ACTIONS
	AxonSendMidiCCAction *BandhelperGeneral2 = new AxonSendMidiCCAction();  // action to send a MIDI Control Change
	BandhelperGeneral2->setNetwork( 1 );                                    // use network "1" (the 2nd) MIDI physical port on rear of Axon
	BandhelperGeneral2->setChannel( 1 );                                    // Bandhelper is configured to be on MIDI Channel 1
	BandhelperGeneral2->setCC( 82 );                                        // General Button 2 is CC 81
	BandhelperGeneral2->setVal( 0 );                                        // lets be good and initialise the value to ZERO ( not really required )

	// LOGIC BLOCKS
	AxonLabelDisplayAction *BandHelperStopScribble = new AxonLabelDisplayAction( 13, "STOP", "STOP" );                 // etc...

	AxonMomentarySwitchAction *BandhelperStopSw = new AxonMomentarySwitchAction();
	BandhelperStopSw->setOnAction( BandhelperGeneral2 );
	BandhelperStopSw->setChangeAction( BandHelperStopScribble );
	AxonKeyScanner::instance()->setOnKeyScan13( BandhelperStopSw );
}

void BANDHELPER_NEXT_FEATURE()
{
	Serial.println("BANDHELPER_NEXT_FEATURE");
	// ACTIONS
	// *** BANDHELPER GENERAL BUTTON 82
	AxonSendMidiCCAction *BandhelperGeneral3 = new AxonSendMidiCCAction();  // action to send a MIDI Control Change
	BandhelperGeneral3->setNetwork( 1 );                                    // use network "1" (the 2nd) MIDI physical port on rear of Axon
	BandhelperGeneral3->setChannel( 1 );                                    // Bandhelper is configured to be on MIDI Channel 1
	BandhelperGeneral3->setCC( 81 );                                        // General Button 3 is CC 82
	BandhelperGeneral3->setVal( 0 );                                        // lets be good and initialise the value to ZERO ( not really required )

	// LOGIC BLOCKS
	AxonLabelDisplayAction *BandHelperNextScribble = new AxonLabelDisplayAction( 14, "NEXT", "NEXT" );                 // etc...

	AxonMomentarySwitchAction *BandhelperNextSw = new AxonMomentarySwitchAction();
	BandhelperNextSw->setOnAction( BandhelperGeneral3 );
	BandhelperNextSw->setChangeAction( BandHelperNextScribble );
	
	AxonKeyScanner::instance()->setOnKeyScan14( BandhelperNextSw );
}

void BANDHELPER_START_FEATURE()
{
	Serial.println("BANDHELPER_START_FEATURE");
	// ACTIONS
	// *** BANDHELPER GENERAL BUTTON 83
	AxonSendMidiCCAction *BandhelperGeneral4 = new AxonSendMidiCCAction();  // action to send a MIDI Control Change
	BandhelperGeneral4->setNetwork( 1 );                                    // use network "1" (the 2nd) MIDI physical port on rear of Axon
	BandhelperGeneral4->setChannel( 1 );                                    // Bandhelper is configured to be on MIDI Channel 1
	BandhelperGeneral4->setCC( 83 );                                        // General Button 4 is CC 83
	BandhelperGeneral4->setVal( 0 );                                        // lets be good and initialise the value to ZERO ( not really required )

	// LOGIC BLOCKS
	AxonLabelDisplayAction *BandHelperStartScribble = new AxonLabelDisplayAction( 15, "START", "START" );               // etc...

	AxonMomentarySwitchAction *BandhelperStartSw = new AxonMomentarySwitchAction();
	BandhelperStartSw->setOnAction( BandhelperGeneral4 );
	BandhelperStartSw->setChangeAction( BandHelperStartScribble );
	AxonKeyScanner::instance()->setOnKeyScan15( BandhelperStartSw );
}

void EXPRESSION_PEDAL1_FEATURE()
{
	Serial.println("EXPRESSION_PEDAL1_FEATURE");
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
	Serial.println("EXPRESSION_PEDAL2_FEATURE");
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
	Serial.println("EXPRESSION_PEDAL3_FEATURE");
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
	Serial.println("EXPRESSION_PEDAL4_FEATURE");
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
	AxonSendMidiCCAction *AFXSendSceneChange = new AxonSendMidiCCAction();    // action to send a MIDI Control Change
	AFXSendSceneChange->setNetwork( 0 );                                      // use network "0" MIDI physical port on rear of Axon
	AFXSendSceneChange->setChannel( 1 );                                      // my AFX is configured to be on MIDI Channel 1
	AFXSendSceneChange->setCC( 34 );                                          // AFX Scene Changes are initiated with controller number 34
	AFXSendSceneChange->setVal( 0 );                                          // lets be good and initialise the value to ZERO ( not really required )

	AxonLabelDisplayAction *d1Action = new AxonLabelDisplayAction( 16, "S1", "-----" );
	AxonLabelDisplayAction *d2Action = new AxonLabelDisplayAction( 17, "S2", "-----" );
	AxonLabelDisplayAction *d3Action = new AxonLabelDisplayAction( 18, "S3", "-----" );
	AxonLabelDisplayAction *d4Action = new AxonLabelDisplayAction( 19, "S4", "-----" );
	AxonLabelDisplayAction *d5Action = new AxonLabelDisplayAction( 20, "S5", "-----" );
	AxonLabelDisplayAction *d6Action = new AxonLabelDisplayAction( 21, "S6", "-----" );
	AxonLabelDisplayAction *d7Action = new AxonLabelDisplayAction( 22, "S7", "-----" );
	AxonLabelDisplayAction *d8Action = new AxonLabelDisplayAction( 23, "S8", "-----" );
	
	AxonRadioSwitchGroupAction *group1 = new AxonRadioSwitchGroupAction();
	group1->setChangeAction( AFXSendSceneChange );
	
	AxonRadioSwitchAction *switch1 = new AxonRadioSwitchAction();	switch1->setOnAction( group1 ); switch1->setChangeAction( d1Action );
	AxonRadioSwitchAction *switch2 = new AxonRadioSwitchAction();	switch2->setOnAction( group1 ); switch2->setChangeAction( d2Action );
	AxonRadioSwitchAction *switch3 = new AxonRadioSwitchAction();	switch3->setOnAction( group1 ); switch3->setChangeAction( d3Action );
	AxonRadioSwitchAction *switch4 = new AxonRadioSwitchAction();	switch4->setOnAction( group1 ); switch4->setChangeAction( d4Action );
	AxonRadioSwitchAction *switch5 = new AxonRadioSwitchAction();	switch5->setOnAction( group1 ); switch5->setChangeAction( d5Action );
	AxonRadioSwitchAction *switch6 = new AxonRadioSwitchAction();	switch6->setOnAction( group1 ); switch6->setChangeAction( d6Action );
	AxonRadioSwitchAction *switch7 = new AxonRadioSwitchAction();	switch7->setOnAction( group1 ); switch7->setChangeAction( d7Action );
	AxonRadioSwitchAction *switch8 = new AxonRadioSwitchAction();	switch8->setOnAction( group1 ); switch8->setChangeAction( d8Action );

	group1->addSwitch( switch1 );
	group1->addSwitch( switch2 );
	group1->addSwitch( switch3 );
	group1->addSwitch( switch4 );
	group1->addSwitch( switch5 );
	group1->addSwitch( switch6 );
	group1->addSwitch( switch7 );
	group1->addSwitch( switch8 );

	AxonKeyScanner::instance()->setOnKeyScan16( switch1 );
	AxonKeyScanner::instance()->setOnKeyScan17( switch2 );
	AxonKeyScanner::instance()->setOnKeyScan18( switch3 );
	AxonKeyScanner::instance()->setOnKeyScan19( switch4 );
	AxonKeyScanner::instance()->setOnKeyScan20( switch5 );
	AxonKeyScanner::instance()->setOnKeyScan21( switch6 );
	AxonKeyScanner::instance()->setOnKeyScan22( switch7 );
	AxonKeyScanner::instance()->setOnKeyScan23( switch8 );
	
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

	AxonMacroAction *PresetNumberRxAction = new AxonMacroAction();	   // When a Preset Number is received...
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
	AxonAFXXLPSysExAction *AFXXLPSysExAction = new AxonAFXXLPSysExAction();  			// Class which handles all AXEFX System Exclusive messages generating both events and action plug points
	AFXXLPSysExAction->onTunerInfoRxd( AFXTunerInfoRxdAction );                        // when tuner information is received run the macro
	AFXXLPSysExAction->onFrontPanelChangeRxd( AFXXLPPresetBlocksDataRequestAction );   // when front panel change messages are received ask for updated blocks this also generates a scene number message
	AFXXLPSysExAction->onPresetNumberRxd( PresetNumberRxAction );                      // when a preset number is received run the macro
	AFXXLPSysExAction->onPresetNameRxd( PresetNameRxAction );                          // when a preset name is received run the macro
	AFXXLPSysExAction->onSceneNumberRxd( SceneNumberRxAction );                        // when scene number received run the macro
	AFXXLPSysExAction->onSceneRxd( group1 );					  						// when a scene is decoded run this action (duplicate interface point of above)

	//  AFXXLPSysExAction->onPresetBlocksDataRxd                                           // when block information received run the macro
	
	AxonMidi::instance()->setSysExAction( AFXXLPSysExAction );
}

void SONG_SELECT()
{
	Serial.println("SONG_SELECT");
	// ACTIONS
	AxonSendMidiCCAction *Regen1 = new AxonSendMidiCCAction();        // action to send a MIDI control Change
	Regen1->setNetwork( 1 );                                          // use network "0" MIDI physical port on rear of Axon
	Regen1->setChannel( 2 );                                          // my AFX is configured to be on MIDI Channel 1
	Regen1->setCC( 7 );                                              // Extern5 is initiated with controller number 20
	Regen1->setVal( 0 );                                              // lets be good and initialise the value to ZERO ( not really required )

	AxonSendMidiPCAction *RegenPC = new AxonSendMidiPCAction();        // action to send a MIDI control Change
	RegenPC->setNetwork( 0 );                                          // use network "0" MIDI physical port on rear of Axon
	RegenPC->setChannel( 1 );                                          // my AFX is configured to be on MIDI Channel 1
	RegenPC->setPC( 4 );                                              // Extern5 is initiated with controller number 20
	
	AxonU2BabyMemoryMapAction *U2BabyMemoryMapAction = new AxonU2BabyMemoryMapAction();
	
	AxonMidi::instance()->setSongSelectAction( U2BabyMemoryMapAction );
//	AxonMidi::instance()->setCCAction( Regen1 );
//	AxonMidi::instance()->setPCAction( RegenPC );
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
  SONG_SELECT();
#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
	

// CONFIGURATION CODE COMPLETE...
    
  AxonTouchScreen::instance()->showMainScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  static AxonKeyScanner *KeyScanner = AxonKeyScanner::instance();           // hold a static.....           ..to the singleton KeyScanner
  static AxonExprScanner *ExprScanner = AxonExprScanner::instance();        // ...........                  ..to the singleton Expression Pedal Scanner
  static AxonMidi *MidiScanner = AxonMidi::instance();                      // .................           ...to the singleton MIDI implementation
  
  KeyScanner->check();                                                      // self throttled and generates all the hardware events from physical switches
  ExprScanner->check();                                                     // self throttled and generates hardware events from the analog input ports
  MidiScanner->read();                                                      // process incoming MIDI messaging from serial ports

#ifdef DEBUG_OBJECT_CREATE_DESTROY
AxonCheckMem::instance()->check();
#endif
}
