﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_insufficent_units_for_uc_transfer_trades : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_insufficent_units_for_uc_transfer_trades() { }
		~CIFast_IFast_ifastcbo_err_insufficent_units_for_uc_transfer_trades() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not enough units avilable for Fund %FUNDNAME%  and  Class %CLASSNAME% for the trade type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pas assez d’unités disponibles pour le fonds %FUNDNAME% et la catégorie %CLASSNAME% pour ce type de transaction.")); }

        // Actions
	};
}



