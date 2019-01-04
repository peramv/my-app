#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_gen_ctrl_trade_deflt_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_gen_ctrl_trade_deflt_does_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_gen_ctrl_trade_deflt_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GEN_CTRL_TRADE_DEFLT_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Generic controls for Trade Defaults does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Generic controls for Trade Defaults does not exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les contrôles génériques pour les valeurs par défaut de la transaction sont inexistants.")); }

        // Actions
	};
}



