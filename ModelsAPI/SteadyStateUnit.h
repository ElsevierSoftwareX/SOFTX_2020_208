/* Copyright (c) 2020, Dyssol Development Team. All rights reserved. This file is part of Dyssol. See LICENSE file for license information. */

#pragma once

#include "BaseUnit.h"

class CSteadyStateUnit : public CBaseUnit
{
public:
	CSteadyStateUnit();
	~CSteadyStateUnit();

	/**	Calculates unit on a time point (for steady-state units).
	 *	\param _dTime Time point to calculate*/
	virtual void Simulate(double _dTime) = 0;
};
