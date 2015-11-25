/*	File:		MoreQuickDraw.h	Contains:		Written by:	Pete Gontier	Copyright:	Copyright (c) 1998 Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):         <4>     20/3/00    Quinn   Implement CreateNewPort and DisposePort for non-Carbon clients.         <3>      2/9/99    PCG     more TARGET_CARBON         <2>    11/11/98    PCG     fix headers         <1>    11/10/98    PCG     first big re-org at behest of Quinn	Old Change History (most recent first):         <5>    10/11/98    Quinn   Convert "MorePrefix.h" to "MoreSetup.h".         <4>      9/9/98    PCG     re-work import and export pragmas         <3>     8/28/98    PCG     add IsColorGrafPort         <2>     7/24/98    PCG	    coddle linker (C++, CFM-68K)         <1>     6/16/98    PCG     initial checkin*/#pragma once#include "MoreSetup.h"#include <QuickDraw.h>#ifdef __cplusplus	extern "C" {#endif#pragma import on // for clients#pragma export on // for building a librarypascal OSErr	InitMoreQuickDraw	(void);pascal Boolean	HaveColorQuickDraw	(void);pascal Boolean	IsColorGrafPort		(GrafPtr);pascal OSErr	ShowWatchCursor		(void);pascal void		SetArrowCursor		(void);#pragma import reset // for clients#pragma export reset // for building a library#if !TARGET_API_MAC_CARBON	pascal QDGlobalsPtr GetQDGlobalsPtr (void);#	define GetQDGlobalsArrow(x) do { *(x)=GetQDGlobalsPtr()->arrow; } while (false)#	define SetQDGlobalsArrow(x) do { GetQDGlobalsPtr()->arrow=*(x); } while (false)#	define GetRegionBounds(rgn,rect) do { *(rect) = (**(rgn)).rgnBBox; } while (false)	extern pascal CGrafPtr CreateNewPort(void);	extern pascal void DisposePort(CGrafPtr port);#endif#ifdef __cplusplus	}#endif