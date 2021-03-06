/* Copyright (c) 2020, Dyssol Development Team. All rights reserved. This file is part of Dyssol. See LICENSE file for license information. */

#include "FlowsheetParameters.h"
#include "DyssolStringConstants.h"

const unsigned CFlowsheetParameters::m_cnSaveVersion = 4;

CFlowsheetParameters::CFlowsheetParameters()
{
	cachePath = L"./cache/";
	Initialize();
}

void CFlowsheetParameters::Initialize()
{
	absTol = DEFAULT_A_TOL;
	relTol = DEFAULT_R_TOL;

	minFraction = DEFAULT_MIN_FRACTION;

	initTimeWindow = DEFAULT_INIT_TIME_WINDOW;
	minTimeWindow = DEFAULT_MIN_TIME_WINDOW;
	maxTimeWindow = DEFAULT_MAX_TIME_WINDOW;
	maxItersNumber = DEFAULT_MAX_ITERATIONS_NUMBER;
	itersUpperLimit = DEFAULT_ITERS_UPPER_LIMIT;
	itersLowerLimit = DEFAULT_ITERS_LOWER_LIMIT;
	iters1stUpperLimit = DEFAULT_ITERS_1ST_UPPER_LIMIT;
	magnificationRatio = DEFAULT_WINDOW_MAGNIFICATION_RATIO;

	convergenceMethod = CM_WEGSTEIN;
	wegsteinAccelParam = DEFAULT_WEGSTEIN_ACCEL_PARAM;
	relaxationParam = DEFAULT_RELAXATION_PARAM;

	extrapolationMethod = EExtrapMethod::EM_SPLINE;

	saveTimeStep = 0;
	saveTimeStepFlagHoldups = true;

	cacheFlagStreams = DEFAULT_CACHE_FLAG_STREAMS;
	cacheFlagHoldups = DEFAULT_CACHE_FLAG_HOLDUPS;
	cacheFlagInternal = DEFAULT_CACHE_FLAG_INTERNAL;
	cacheWindow = DEFAULT_CACHE_WINDOW;
	cacheFlagStreamsAfterReload = DEFAULT_CACHE_FLAG_STREAMS;
	cacheFlagHoldupsAfterReload = DEFAULT_CACHE_FLAG_HOLDUPS;
	cacheFlagInternalAfterReload = DEFAULT_CACHE_FLAG_INTERNAL;
	cacheWindowAfterReload = DEFAULT_CACHE_WINDOW;

	fileSingleFlag = true;
}

void CFlowsheetParameters::SaveToFile(CH5Handler& _h5File, const std::string& _sPath)
{
	if (!_h5File.IsValid())	return;

	// current version of save procedure
	_h5File.WriteAttribute(_sPath, StrConst::FlPar_H5AttrSaveVersion, m_cnSaveVersion);

	// save tolerances
	_h5File.WriteData(_sPath, StrConst::FlPar_H5ATol, absTol);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5RTol, relTol);

	// save minimal fraction
	_h5File.WriteData(_sPath, StrConst::FlPar_H5MinFrac, minFraction);

	// save time window parameters
	_h5File.WriteData(_sPath, StrConst::FlPar_H5InitTimeWin, initTimeWindow);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5MinTimeWin, minTimeWindow);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5MaxTimeWin, maxTimeWindow);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5MaxStepsNum, maxItersNumber);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5MagnificRatio, magnificationRatio);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5UpperLimit, itersUpperLimit);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5LowerLimit, itersLowerLimit);
	_h5File.WriteData(_sPath, StrConst::FlPar_H51stUpperLimit, iters1stUpperLimit);

	// save convergence and extrapolation parameters
	_h5File.WriteData(_sPath, StrConst::FlPar_H5ConvMethod, static_cast<unsigned>(convergenceMethod));
	_h5File.WriteData(_sPath, StrConst::FlPar_H5WegsteinParam, wegsteinAccelParam);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5RelaxParam, relaxationParam);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5ExtrapMethod, static_cast<unsigned>(static_cast<EExtrapMethod>(extrapolationMethod)));

	// save compression
	_h5File.WriteData(_sPath, StrConst::FlPar_H5SaveTimeStep, saveTimeStep);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5SaveTimeStepFlagHoldups, saveTimeStepFlagHoldups);

	// save cache parameters
	_h5File.WriteData(_sPath, StrConst::FlPar_H5CacheFlagStreams, cacheFlagStreamsAfterReload);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5CacheFlagHoldups, cacheFlagHoldupsAfterReload);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5CacheFlagInternal, cacheFlagInternalAfterReload);
	_h5File.WriteData(_sPath, StrConst::FlPar_H5CacheWindow, cacheWindowAfterReload);

	// save file saving parameters
	_h5File.WriteData(_sPath, StrConst::FlPar_H5FileSingleFlag, fileSingleFlag);

	// save tear streams initialization parameters
	_h5File.WriteData(_sPath, StrConst::FlPar_H5InitTearStreamsFlag, initializeTearStreamsAutoFlag);
}

void CFlowsheetParameters::LoadFromFile(CH5Handler& _h5File, const std::string& _sPath)
{
	// load version of save procedure
	const int nVer = _h5File.ReadAttribute(_sPath, StrConst::FlPar_H5AttrSaveVersion);

	// load tolerances
	_h5File.ReadData(_sPath, StrConst::FlPar_H5ATol, absTol.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5RTol, relTol.data);

	// load minimal fraction
	_h5File.ReadData(_sPath, StrConst::FlPar_H5MinFrac, minFraction.data);

	// load time window parameters
	_h5File.ReadData(_sPath, StrConst::FlPar_H5InitTimeWin, initTimeWindow.data);
	if (nVer == 0)
		minTimeWindow = DEFAULT_MIN_TIME_WINDOW;
	else
		_h5File.ReadData(_sPath, StrConst::FlPar_H5MinTimeWin, minTimeWindow.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5MaxTimeWin, maxTimeWindow.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5MaxStepsNum, maxItersNumber.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5MagnificRatio, magnificationRatio.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5UpperLimit, itersUpperLimit.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5LowerLimit, itersLowerLimit.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H51stUpperLimit, iters1stUpperLimit.data);

	// load convergence and extrapolation parameters
	unsigned nTemp;
	_h5File.ReadData(_sPath, StrConst::FlPar_H5ConvMethod, nTemp);
	convergenceMethod = static_cast<EConvMethod>(nTemp);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5WegsteinParam, wegsteinAccelParam.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5RelaxParam, relaxationParam.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5ExtrapMethod, nTemp);
	extrapolationMethod = static_cast<EExtrapMethod>(nTemp);

	// load compression
	if (nVer < 3)
	{
		saveTimeStep = 0;
		saveTimeStepFlagHoldups = true;
	}
	else
	{
		_h5File.ReadData(_sPath, StrConst::FlPar_H5SaveTimeStep, saveTimeStep.data);
		_h5File.ReadData(_sPath, StrConst::FlPar_H5SaveTimeStepFlagHoldups, saveTimeStepFlagHoldups.data);
	}

	// load cache parameters
	_h5File.ReadData(_sPath, StrConst::FlPar_H5CacheFlagStreams, cacheFlagStreams.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5CacheFlagHoldups, cacheFlagHoldups.data);
	_h5File.ReadData(_sPath, StrConst::FlPar_H5CacheFlagInternal, cacheFlagInternal.data);
	cacheFlagStreamsAfterReload = cacheFlagStreams;
	cacheFlagHoldupsAfterReload = cacheFlagHoldups;
	cacheFlagInternalAfterReload = cacheFlagInternal;
	_h5File.ReadData(_sPath, StrConst::FlPar_H5CacheWindow, cacheWindow.data);
	cacheWindowAfterReload = cacheWindow;

	// load file saving parameters
	if(nVer < 2)
		fileSingleFlag = true;
	else
		_h5File.ReadData(_sPath, StrConst::FlPar_H5FileSingleFlag, fileSingleFlag.data);

	// load tear streams  initialization parameters
	if (nVer < 4)
		initializeTearStreamsAutoFlag = true;
	else
		_h5File.ReadData(_sPath, StrConst::FlPar_H5InitTearStreamsFlag, initializeTearStreamsAutoFlag.data);
}

void CFlowsheetParameters::AbsTol(double val)
{
	absTol = val > 0. ? val : 0.;
}

void CFlowsheetParameters::RelTol(double val)
{
	relTol = val > 0. ? val : 0.;
}

void CFlowsheetParameters::MinFraction(double val)
{
	minFraction = val > 0. ? val : 0.;
}

void CFlowsheetParameters::InitTimeWindow(double val)
{
	if (val > 0)
		initTimeWindow = val;
}

void CFlowsheetParameters::MinTimeWindow(double val)
{
	if (val > 0)
		minTimeWindow = val;
}

void CFlowsheetParameters::MaxTimeWindow(double val)
{
	if (val > 0)
		maxTimeWindow = val;
}

void CFlowsheetParameters::MaxItersNumber(unsigned val)
{
	if (val > 0)
		maxItersNumber = val;
}

void CFlowsheetParameters::ItersUpperLimit(unsigned val)
{
	itersUpperLimit = val;
}

void CFlowsheetParameters::ItersLowerLimit(unsigned val)
{
	itersLowerLimit = val;
}

void CFlowsheetParameters::Iters1stUpperLimit(unsigned val)
{
	iters1stUpperLimit = val;
}

void CFlowsheetParameters::MagnificationRatio(double val)
{
	magnificationRatio = val > 0. ? val : 1.;
}

void CFlowsheetParameters::ConvergenceMethod(EConvMethod val)
{
	convergenceMethod = val;
}

void CFlowsheetParameters::WegsteinAccelParam(double val)
{
	// [-5; 1]
	if (val < -5)		wegsteinAccelParam = -5;
	else if (val > 1)	wegsteinAccelParam = 1;
	else				wegsteinAccelParam = val;
}

void CFlowsheetParameters::RelaxationParam(double val)
{
	// (0; 1]
	if ((val > 0) && (val <= 1))
		relaxationParam = val;
}

void CFlowsheetParameters::ExtrapolationMethod(EExtrapMethod val)
{
	extrapolationMethod = val;
}

void CFlowsheetParameters::SaveTimeStep(double val)
{
	saveTimeStep = val > 0. ? val : 0;
}

void CFlowsheetParameters::SaveTimeStepFlagHoldups(bool val)
{
	saveTimeStepFlagHoldups = val;
}

void CFlowsheetParameters::CachePath(std::wstring val)
{
	cachePath = val;
}

void CFlowsheetParameters::CacheFlagStreams(bool val)
{
	cacheFlagStreams = val;
}

void CFlowsheetParameters::CacheFlagHoldups(bool val)
{
	cacheFlagHoldups = val;
}

void CFlowsheetParameters::CacheFlagInternal(bool val)
{
	cacheFlagInternal = val;
}

void CFlowsheetParameters::CacheFlagStreamsAfterReload(bool val)
{
	cacheFlagStreamsAfterReload = val;
}

void CFlowsheetParameters::CacheFlagHoldupsAfterReload(bool val)
{
	cacheFlagHoldupsAfterReload = val;
}

void CFlowsheetParameters::CacheFlagInternalAfterReload(bool val)
{
	cacheFlagInternalAfterReload = val;
}

void CFlowsheetParameters::CacheWindow(unsigned val)
{
	if (val > 0)
		cacheWindow = val;
}

void CFlowsheetParameters::CacheWindowAfterReload(unsigned val)
{
	if (val > 0)
		cacheWindowAfterReload = val;
}

void CFlowsheetParameters::FileSingleFlag(bool val)
{
	fileSingleFlag = val;
}

void CFlowsheetParameters::InitializeTearStreamsAutoFlag(bool val)
{
	initializeTearStreamsAutoFlag = val;
}
