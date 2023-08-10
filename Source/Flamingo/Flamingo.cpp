// Fill out your copyright notice in the Description page of Project Settings.

#include "Flamingo.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogFL);

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Flamingo, "Flamingo" );

namespace FLConst {
	const ETraceTypeQuery TraceTypeQuery_Visibility = ETraceTypeQuery::TraceTypeQuery1;
}