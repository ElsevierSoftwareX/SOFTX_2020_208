/* Copyright (c) 2020, Dyssol Development Team. All rights reserved. This file is part of Dyssol. See LICENSE file for license information. */

#pragma once

#include "ui_BasicStreamEditor.h"
#include "SolidDistributionsEditor.h"
#include "MDMTable.h"
#include "DDTable.h"

class CBasicStreamEditor : public QWidget
{
	Q_OBJECT

private:
	Ui::CBasicStreamEditorClass ui;

	// TODO: make it const
	CFlowsheet* m_pFlowsheet; // pointer to the flowsheet
	bool m_bAvoidSignal;
	CStream* m_pSelectedHoldup; // pointer to the selected stream

	CDDTable* m_pDDTableMTP;
	CDDTable* m_pDDTablePhase;
	std::vector<CMDMTable*> m_vMDMTablePhases;
	CSolidDistributionsEditor* m_pSolidDistrEditor;

	// for save/restore view
	int m_nLastTab;
	int m_nLastTime;
	std::vector<int> m_vLastCombos;
	std::vector<int> m_vLastSliders;

public:
	CBasicStreamEditor(QWidget *parent = Q_NULLPTR);

	void SetFlowsheet(CFlowsheet* _pFlowsheet);
	void SetStream(CStream* _pStream);
	void SetEditable(bool _bEditable);				// Turn on/off edit possibility.

	void UpdateWholeView();

private slots:
	void setVisible(bool _bVisible) override;
	void ChangeData();

private:
	void InitializeConnections();

	void UpdateTabs();
	void UpdateTabContent(); // update content of the multitab widget
	void UpdateStreamMTPTab(); // updates content of the first tab
	void UpdatePhaseFractionsTab();
	void UpdatePhaseTab(unsigned _nIndex);
	void UpdateDistributionTab();
	void UpdateTimePointsTable(); // update the table where all time points are shown

	void AddTimePoint();
	void RemoveTimePoint();
	void RemoveAllTimePoints();
	void ChangeTimePoint();

	void TableTimeChanged(int _nRow, int _nCol, int _nPrevRow, int _nPrevCol);

	void SetControlsActivity(bool _bActive);

	void SaveViewState();
	void LoadViewState();

signals:
	void DataChanged();	// some information in holdup have been changed
};
