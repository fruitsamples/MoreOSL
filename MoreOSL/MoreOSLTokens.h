/*	File:		MoreOSLTokens.h	Contains:	Token definition for MoreOSL.	Written by:	Quinn	Copyright:	Copyright � 2000 by Apple Computer, Inc., all rights reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):         <2>     20/3/00    Quinn   Added InitPropertyMOSLTokenFromOtherProperty.         <1>      6/3/00    Quinn   First checked in.*/#pragma once/////////////////////////////////////////////////////////////////// MoreIsBetter Setup#include "MoreSetup.h"// Mac OS Interfaces#include <AppleEvents.h>/////////////////////////////////////////////////////////////////// Big Picture// -----------// MOSLToken in the OSL token type used by MoreOSL (MOSL).  In general, the OSL// token for an application is the application�s responsibility.  However,// in MoreOSL I�ve designed a fairly generic token structure that maps well// to common application structures.  I�ve then made this token structure// part of MOSL so that MOSL can do more than the vanilla OSL (hence the name).// You sacrifice some flexibility of token design, but you get a lot of extra// functionality back.//// However, I do recognise that there may be circumstances under which you want// to keep MOSL but expand the token format.  So, I�ve broken the MOSLToken// data structure, and the routines that directly operate upon it, out of the// "MoreOSL.[hc]" files and placed them here.  This way you can take updates// to MOSL while preserving any token structure modifications you need.//// MOSLToken Structure// -------------------// A MOSLToken can either represent an object, or an object�s property.// Various fields of the record are used in various ways depending on// what the token represents.//// 	  o	tokType is either the type of the object that this token represents,//      or typeProperty for properties.  If tokType is not typeProperty, it //      must be the same as tokObjType.//    o	tokObjType is the type of the object or, if tokType is typeProperty,//		the type of the object that has the property.  This value is always//      the same four character code as the classID field of a class in the//		class table.  You can look up this value in the class table//		to determine the appropriate accessors to call for this token,//		regardless of whether its an object or a property.//    o tokPropName is either the name of the property that this token//		represents, or 0 if the token represents an object.//    o tokData is a pointer to the application �native� object represented//      by this token.  MOSL does not look at or modify this field (other//		than in the token init routines described below).  You might store// 		a C++ object pointer in this field.struct MOSLToken {	DescType tokType;			// type of object, typeProperty for properties	DescType tokObjType;		// type of object, when tokType is typeProperty, this is the type of the parent object, otherwise same as tokType	DescType tokPropName;		// when tokType is typeProperty, this is the property name, otherwise n/a	void     *tokData;			// pointer to application object};typedef struct MOSLToken MOSLToken, *MOSLTokenPtr;#if MORE_DEBUG	extern pascal void BBLogMOSLToken(ConstStr255Param tag, const MOSLToken *tok);		// Logs a textual representation of the token to BBEdit.		// This routine is very much like the data logging routines		// in MoreBBLog, but it resides here to avoid layer breaking		// (I don�t want "MoreBBLog.[hc]" being dependent on "MoreOSLTokens.h").#else	#define BBLogMOSLToken(tag, tok)#endifextern pascal void     InitObjectMOSLToken(MOSLToken *tok, DescType tokType, void *tokData);	// Initialises a token to reference an object of type tokType whose	// native object pointer is tokData.	extern pascal void     InitPropertyMOSLToken(MOSLToken *tok, DescType tokObjType, DescType tokPropName, void *tokData);	// Initialises a token to reference a property of name tokPropName of	// an object whose type is tokType and whose native object pointer is tokData.	extern pascal void     InitPropertyMOSLTokenFromContainer(MOSLToken *tok, const MOSLToken *containerTok, DescType tokPropName);	// Initialises a token which references the property named tokPropName	// of the object referenced by containerTok.  containerTok must not be	// a property token.extern pascal void     InitPropertyMOSLTokenFromOtherProperty(MOSLToken *tok, const MOSLToken *propertyTok, DescType tokPropName);	// Initialises a token which references a property within the same object	// as an existing property token. propertyTok must be a property token.extern pascal OSStatus MOSLTokenToDesc(const MOSLToken *tok, AEDesc *desc);	// Places a token in a descriptor.  The resulting descriptor type is always	// the same as tok->tokType.extern pascal void     DescToMOSLToken(const AEDesc *tokDesc, MOSLToken *tok);	// Extracts a token from a descriptor containing a token.  tokDesc must	// contain a valid MOSLToken, typically placed there by MOSLTokenToDesc.	// Typically this routine is only called by code in "MoreOSL.c", which	// can consult the class table to ensure that the descriptor actually	// contains a token.	extern pascal OSStatus CompareMOSLTokens(DescType oper, const MOSLToken *tok1, const MOSLToken *tok2, Boolean *result);	// Compares two tokens using the given operator.  Currently only	// the kAEEquals operator is supported, and it assumes that the tokData	// field of the token is comparable.  You may need to modify this if	// you add extra fields to the token or you store weird native object	// pointers in the token or you want to support operators other than	// kAEEquals.