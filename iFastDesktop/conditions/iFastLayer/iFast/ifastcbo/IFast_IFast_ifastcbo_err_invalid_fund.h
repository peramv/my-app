#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_fund() { }
		~CIFast_IFast_ifastcbo_err_invalid_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund does not exist, please enter an existing one or leave it blank and select a valid fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund does not exist, please enter an existing one or leave it blank and select a valid fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds inexistant, veuillez entrer un fonds existant ou laisser ce champ vide et sélectionner un fonds valide.")); }

        // Actions
	};
}



