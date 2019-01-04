#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_bfdbrkr_err_switch_settlement_error : public CConditionObject
	{
	public:
		CIFast_IFast_bfdbrkr_err_switch_settlement_error() { }
		~CIFast_IFast_bfdbrkr_err_switch_settlement_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SWITCH_SETTLEMENT_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Out side of trade has not been selected for settlement. Please select out side first.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La partie sortante de la transaction n'a pas été sélectionnée pour le règlement. Veuillez d'abord sélectionner la partie sortante.")); }

        // Actions
	};
}



