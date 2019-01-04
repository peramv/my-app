#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_supp_code_not_allowed_for_trans_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_supp_code_not_allowed_for_trans_type() { }
		~CIFast_IFast_ifastcbo_err_supp_code_not_allowed_for_trans_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SUPP_CODE_NOT_ALLOWED_FOR_TRANS_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Suppress Code not allowed for Transaction Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Suppress Code not allowed for Transaction Type.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Suppress Code not allowed for Transaction Type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de suppression non autorisé pour le type de transaction")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please choose a different Suppress Code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please choose a different Suppress Code.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please choose a different Suppress Code.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez sélectionner un code de suppression différent.")); }
	};
}



