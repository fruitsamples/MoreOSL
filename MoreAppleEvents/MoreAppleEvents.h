/*	File:		MoreAppleEvents.h	Contains:		Written by:	Pete Gontier	Copyright:	Copyright (c) 1998 Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):         <9>     27/3/00    Quinn   Remove MoreAEDeleteItemFromRecord.  It's functionality is                                    covered by AEDeleteKeyDesc.         <8>     20/3/00    Quinn   Added routines to deal with "missing value".  Added                                    MoreAECopyDescriptorDataToHandle.  Fixed some copy and paste                                    errors in the comments.         <7>      3/9/00    GW      Intergrating AppleEvent Helper code         <6>      6/3/00    Quinn   Added a bunch of trivial wrapper routines.  George may come                                    along and change all these soon, but I needed them for MoreOSL.         <5>      1/3/00    Quinn   Change the signature for AEGetDescData to match the version we                                    actually shipped.         <4>     2/15/99    PCG     add AEGetDescDataSize for non-Carbon clients         <3>     1/29/99    PCG     add AEGetDescData         <2>    11/11/98    PCG     fix headers         <1>    11/10/98    PCG     first big re-org at behest of Quinn	Old Change History (most recent first):         <4>    10/11/98    Quinn   Convert "MorePrefix.h" to "MoreSetup.h".         <3>      9/9/98    PCG     re-work import and export pragmas         <2>     7/24/98    PCG	    coddle linker (C++, CFM-68K)         <1>     6/16/98    PCG     initial checkin*/#pragma once//********************************************************************************//	A private conditionals file to setup the build environment for this project.#include "MoreSetup.h"//********************************************************************************//	System includes#include <AERegistry.h>#include <AEObjects.h>#include <AEPackObject.h>#include <EPPC.h>#include <Gestalt.h>#include <Processes.h>//********************************************************************************#define	kFlagNotSet	-1//********************************************************************************#ifdef __cplusplus	extern "C" {#endif/********************************************************************************	Create and return an AEDesc for the process target with the specified PSN.	If no PSN is supplied the use the current process	pAEEventClass		input:	The class of the event to be created.	pAEEventID			input:	The ID of the event to be created.	pAppleEvent		input:	Pointer to an AppleEvent where the							event record will be returned.					output:	The Apple event.		RESULT CODES	____________	noErr			   0	No error		memFullErr		-108	Not enough room in heap zone		____________*/extern pascal OSErr MoreAECreateProcessTarget (ProcessSerialNumber *pPSN, AEDesc *target);/********************************************************************************	Create and return an AppleEvent of the given class and ID. The event will be	targeted at the current process, with an AEAddressDesc of type	typeProcessSerialNumber.	pAEEventClass		input:	The class of the event to be created.	pAEEventID			input:	The ID of the event to be created.	pAppleEvent		input:	Pointer to an AppleEvent where the							event record will be returned.					output:	The Apple event.		RESULT CODES	____________	noErr			   0	No error		memFullErr		-108	Not enough room in heap zone		____________*/extern pascal OSErr MoreAECreateAppleEventSelfTarget( AEEventClass pAEEventClass,							  AEEventID pAEEventID,							  AppleEvent *pAppleEvent );/********************************************************************************	Create and return an AppleEvent of the given class and ID. The event will be	targeted at the process specified by the target type and creator codes, 	with an AEAddressDesc of type typeProcessSerialNumber.	pType			input:	The file type of the process to be found.	pCreator		input:	The creator type of the process to be found.	pAEEventClass	input:	The class of the event to be created.	pAEEventID		input:	The ID of the event to be created.	pAppleEvent		input:	Pointer to an AppleEvent where the							event record will be returned.					output:	The Apple event.		RESULT CODES	____________	noErr			   0	No error		memFullErr		-108	Not enough room in heap zone		procNotFound	�600	No eligible process with specified descriptor	____________*/extern pascal OSErr	MoreAECreateAppleEventSignatureTarget( OSType pType,											 OSType pCreator,											 AEEventClass pAEEventClass,											 AEEventID pAEEventID,											 AppleEvent *pAppleEvent );/********************************************************************************	Create and return an AppleEvent of the given class and ID. The event will be	targeted at the application with the specific creator.	psnPtr			input:	Pointer to the PSN to target the event with.	pAEEventClass	input:	The class of the event to be created.	pAEEventID		input:	The ID of the event to be created.	pAppleEvent		input:	Pointer to an AppleEvent where the							event record will be returned.					output:	The Apple event.		RESULT CODES	____________	noErr			   0	No error		memFullErr		-108	Not enough room in heap zone		procNotFound	�600	No eligible process with specified descriptor	____________*/pascal OSStatus MoreAECreateAppleEventCreatorTarget(							const AEEventClass pAEEventClass,							const AEEventID pAEEventID,							const OSType pCreator,							AppleEvent *pAppleEvent);/********************************************************************************	Create and return an AppleEvent of the given class and ID. The event will be	targeted with the provided PSN.	psnPtr			input:	Pointer to the PSN to target the event with.	pAEEventClass	input:	The class of the event to be created.	pAEEventID		input:	The ID of the event to be created.	pAppleEvent		input:	Pointer to an AppleEvent where the							event record will be returned.					output:	The Apple event.		RESULT CODES	____________	noErr			   0	No error		memFullErr		-108	Not enough room in heap zone		procNotFound	�600	No eligible process with specified descriptor	____________*/extern pascal OSErr	MoreAECreateAppleEventProcessTarget( const ProcessSerialNumberPtr psnPtr,										   AEEventClass pAEEventClass,										   AEEventID pAEEventID,										   AppleEvent *pAppleEvent );/********************************************************************************	Create and return an AppleEvent of the given class and ID. The event will be	targeted with the provided TargetID.	pTargetID		input:	Pointer to the TargetID to target the event with.	pAEEventClass	input:	The class of the event to be created.	pAEEventID		input:	The ID of the event to be created.	pAppleEvent		input:	Pointer to an AppleEvent where the							event record will be returned.					output:	The Apple event.		RESULT CODES	____________	noErr			   0	No error		memFullErr		-108	Not enough room in heap zone		procNotFound	�600	No eligible process with specified descriptor	____________*/extern pascal OSErr	MoreAECreateAppleEventTargetID( const TargetID *pTargetID,									  AEEventClass pAEEventClass,									  AEEventID pAEEventID,									  AppleEvent *pAppleEvent );/********************************************************************************	Send the provided AppleEvent using the provided idle function.	Will wait for a reply if an idle function is provided, but no result will be returned.	pIdleProcUPP	input:	The idle function to use when sending the event.	pAppleEvent		input:	The event to be sent.		RESULT CODES	____________	noErr			   0	No error			and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr	MoreAESendEventNoReturnValue( const AEIdleUPP pIdleProcUPP,										   const AppleEvent *pAppleEvent );/********************************************************************************	Send the provided AppleEvent using the provided idle function.	Return data (at pDataPtr) of type pDesiredType	pIdleProcUPP	input:	The idle function to use when sending the event.	pAppleEvent		input:	The event to be sent.	theValue		output:	The value returned by the event.	RESULT CODES	____________	noErr			   0	No error		paramErr		 -50	No idle function provided	and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr MoreAESendEventReturnData(						const AEIdleUPP		pIdleProcUPP,						const AppleEvent	*pAppleEvent,						DescType			pDesiredType,						DescType*			pActualType,						void*		 		pDataPtr,						Size				pMaximumSize,						Size 				*pActualSize);/********************************************************************************	Send the provided AppleEvent using the provided idle function.	Return a SInt16 (typeSmallInteger).	pIdleProcUPP	input:	The idle function to use when sending the event.	pAppleEvent		input:	The event to be sent.	theValue		output:	The value returned by the event.		RESULT CODES	____________	noErr			   0	No error		paramErr		 -50	No idle function provided		and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr	MoreAESendEventReturnSInt16(					const AEIdleUPP pIdleProcUPP,					const AppleEvent *pAppleEvent,					SInt16 *theValue );/********************************************************************************	Send the provided AppleEvent using the provided idle function.	Returns a PString.	pIdleProcUPP	input:	The idle function to use when sending the event.	pAppleEvent		input:	The event to be sent.	pStr255		output:	The value returned by the event.	RESULT CODES	____________	noErr			   0	No error		paramErr		 -50	No idle function provided	and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr MoreAESendEventReturnPString(						const AEIdleUPP pIdleProcUPP,						const AppleEvent* pAppleEvent,						Str255 pStr255);/********************************************************************************	Send an AppleEvent of the specified Class & ID to myself using the 	provided idle function.  The actual target of the event is the	pSelection property of the application.	pIdleProcUPP	input:	The idle function to use when sending the event.	pEventID		input:	The event to be sent.	RESULT CODES	____________	noErr			   0	No error		and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr MoreAESendToSelfNoReturnValue(				const AEEventClass pEventClass,				const AEEventID pEventID);/********************************************************************************	Send an AppleEvent of the specified Class & ID to myself using the 	provided idle function. Wait for a reply and extract a SInt16 result.	The actual target of the event is the pSelection property of the 	application.	pIdleProcUPP	input:	The idle function to use when sending the event.	pEventID		input:	The event to be sent.	pValue			Output:	Where the return SInt16 will be stored.	RESULT CODES	____________	noErr			   0	No error		and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr MoreAESendToSelfReturnSInt16(				const AEEventClass pEventClass,				const AEEventID pEventID,				SInt16* pValue);/********************************************************************************	Send a get data (kAEGetData) AppleEvent to myself using the 	provided idle function. Wait for a reply and extract a SInt16 result.		pIdleProcUPP	input:	The idle function to use when sending the event.	pEventID		input:	The event to be sent.	pValue			Output:	Where the resulting SInt16 will be stored.	RESULT CODES	____________	noErr			   0	No error		and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr MoreAETellSelfToGetSInt16Property(				const DescType pPropType,				SInt16* pValue);/********************************************************************************	Send a get data (kAEGetData) AppleEvent to myself using the 	provided idle function. Wait for a reply and extract a Str255 result.	The actual target of the event is the pSelection property of the 	application.	pIdleProcUPP	input:	The idle function to use when sending the event.	pEventID		input:	The event to be sent.	pValue			Output:	Where the resulting Str255 will be stored.	RESULT CODES	____________	noErr			   0	No error		and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr MoreAETellSelfToGetStr255Property(				const DescType pPropType,				Str255 pValue);/********************************************************************************	Send a set data (kAESetData) AppleEvent to myself with a SInt16 parameter	and using the provided idle function.	pIdleProcUPP	input:	The idle function to use when sending the event.	pEventID		input:	The event to be sent.	pValue			Output:	Where the resulting SInt16 will be stored.	RESULT CODES	____________	noErr			   0	No error		and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr MoreAETellSelfToSetSInt16Property(				const DescType pPropType,				SInt16 pValue);/********************************************************************************	Send a set data (kAESetData) AppleEvent to myself with a SInt16 parameter	and using the provided idle function.	pIdleProcUPP	input:	The idle function to use when sending the event.	pEventID		input:	The event to be sent.	pValue			Output:	Where the resulting Str255 will be stored.	RESULT CODES	____________	noErr			   0	No error		and any other error that can be returned by AESend or the handler	in the application that gets the event.	____________*/extern pascal OSErr MoreAETellSelfToSetStr255Property(				const DescType pPropType,				Str255 pValue);//*******************************************************************************// Appends each of the items in pSourceList to the pDestList.extern pascal OSStatus MoreAEAppendListToList(const AEDescList *pSourceList, AEDescList *pDestList);//*******************************************************************************// This routine takes a result descriptor and an error.// If there is a result to add to the reply it makes sure the reply isn't// NULL itself then adds the error to the reply depending on the error// and the type of result.extern pascal OSErr MoreAEMoreAESetReplyErrorNumber (OSErr pOSErr, AppleEvent *pAEReply);//*******************************************************************************// This routine takes a result descriptor, a reply descriptor and an error.// If there is a result to add to the reply it makes sure the reply isn't// NULL itself then adds the result to the reply depending on the error// and the type of result.extern pascal OSErr MoreAEAddResultToReply(AEDesc* pResult, AEDesc* pAEReply, OSErr error);// ----------------------------------------------------------------------//	Name:		MoreAEGotRequiredParams//	Function:	Checks that all parameters defined as 'required' have been read// ----------------------------------------------------------------------extern pascal OSErr	MoreAEGotRequiredParams(const AppleEvent *theAppleEvent);/********************************************************************************	Takes a reply event checks it for any errors that may have been returned	by the event handler. A simple function, in that it only returns the error	number. You can often also extract an error string and three other error	parameters from a reply event.		Also see:		IM:IAC for details about returned error strings.		AppleScript developer release notes for info on the other error parameters.		pAEReply		input:	The reply event to be checked.	RESULT CODES	____________	noErr				    0	No error		????					??	Pretty much any error, depending on what the								event handler returns for it's errors.*/extern pascal OSErr	MoreAEGetHandlerError( const AppleEvent *pAEReply );/********************************************************************************	Get the class and ID from an AppleEvent.	pAppleEvent		input:	The event to get the class and ID from.	pAEEventClass	   output:	The event's class.	pAEEventID		   output:	The event's ID.		RESULT CODES	____________	noErr					    0	No error		memFullErr				 -108	Not enough room in heap zone		errAEDescNotFound 		-1701	Descriptor record was not found		errAENotAEDesc			-1704	Not a valid descriptor record		errAEReplyNotArrived	-1718	Reply has not yet arrived	*/	extern pascal OSErr MoreAEExtractClassAndID ( const AppleEvent *pAppleEvent,							 AEEventClass *pAEEventClass,							 AEEventID *pAEEventID );/********************************************************************************	A very simple idle function. It simply ignors any event it receives,	returns 30 for the sleep time and nil for the mouse region.		Your application should supply an idle function that handles any events it	might receive. This is especially important if your application has any windows.		Also see:		IM:IAC for details about idle functions.		Pending Update Perils technote for more about handling low-level events.*/	extern pascal Boolean	MoreAESimpleIdleFunction( EventRecord *event,									   long *sleepTime,									   RgnHandle *mouseRgn );/********************************************************************************	Is the Apple Event Manager present.		RESULT CODES	____________	true	The Apple Event Manager is present	false	It isn't*/extern pascal Boolean	MoreAEHasAppleEvents(void);//*******************************************************************************// Did this AppleEvent come from the Finder?extern pascal OSErr MoreAEIsSenderFinder (const AppleEvent *pAppleEvent, Boolean *pIsFinder);//*******************************************************************************// Initialises desc to the null descriptor (typeNull, nil).extern pascal void MoreAENullDesc(AEDesc *desc);//*******************************************************************************// Disposes of desc and initialises it to the null descriptor.extern pascal void MoreAEDisposeDesc(AEDesc *desc);//*******************************************************************************// These routines are only implemented in PreCarbon.o for PowerPC// So for 68K we had to write our own versions#if TARGET_CPU_68K || !ACCESSOR_CALLS_ARE_FUNCTIONSextern pascal Size AEGetDescDataSize( const AEDesc* pAEDesc);extern pascal OSErr AEGetDescData(					const AEDesc*	pAEDesc,					void*			pDataPtr,					Size 			pMaxSize);#endif TARGET_CPU_68K || !ACCESSOR_CALLS_ARE_FUNCTIONS/********************************************************************************	These are generic routines that are used to extract data of	different types from descriptor records.	pAEDesc			input:	The descriptor we want the data from	pDestPtr		output:	Where we want to store the data from this desc.	pMaxSize		input:	The maxium amount of data we can store.	pActualSize		output:	The actual amount of data stored.	RESULT CODES	____________	noErr			   0	No error		____________*/extern pascal void MoreAEGetRawDataFromDescriptor(const AEDesc* pAEDesc,							 Ptr     pDestPtr,							 Size    pMaxSize,							 Size    *pActualSize);extern pascal OSErr MoreAEGetPStringFromDescriptor(const AEDesc* pAEDesc, StringPtr pStringPtr);extern pascal OSErr MoreAEGetCStringFromDescriptor(const AEDesc* pAEDesc, char* pCharPtr);extern pascal OSErr MoreAEGetShortFromDescriptor(const AEDesc* pAEDesc, SInt16 *pResult);extern pascal OSErr MoreAEGetBooleanFromDescriptor(const AEDesc* pAEDesc,Boolean *pResult);extern pascal OSErr MoreAEGetLongFromDescriptor(const AEDesc* pAEDesc, long   *pResult);extern pascal OSErr MoreAEGetOSTypeFromDescriptor(const AEDesc* pAEDesc, OSType   *pResult);//*******************************************************************************// This routine creates a new handle and puts the contents of the desc// in that handle.  Carbon�s opaque AEDesc�s means that we need this// functionality a lot.extern pascal OSStatus MoreAECopyDescriptorDataToHandle(const AEDesc *desc, Handle *descData);//*******************************************************************************// This routine returns true if and only if desc is the "missing value" value.extern pascal Boolean MoreAEIsMissingValue(const AEDesc *desc);//*******************************************************************************// This routine creates a descriptor that represents the missing value.extern pascal OSStatus MoreAECreateMissingValue(AEDesc *desc);#ifdef __cplusplus}#endif